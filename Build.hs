{-# LANGUAGE DeriveDataTypeable, GeneralizedNewtypeDeriving #-}
import Development.Shake
import Development.Shake.Classes
import Development.Shake.Command
import Development.Shake.FilePath
import Development.Shake.Util

import Control.Monad


newtype Sources = Sources () deriving (Show,Typeable,Eq,Hashable,Binary,NFData)

main :: IO ()
main = shakeArgs shakeOptions{shakeFiles = ".shake/"} $ do
  want ["test"]

  let cxx       = "clang++"
  let cxx_flags = ["-Isrc", "-std=c++11", "-g", "-Wall", "-pedantic"]
  let lib_flags = ["-lboost_unit_test_framework"]

  "clean" ~> removeFilesAfter ".shake" ["//*"]

  "cli" ~> do
    let x = "bin/cli" <.> exe
    need [x]
    cmd x

  "test" ~> do
    need ["foo", "maybe", "either"]
    cmd "echo No tests..."

  "maybe" ~> do
    let x = "bin/maybe_test" <.> exe
    need [x]
    cmd x

  "either" ~> do
    let x = "bin/either_test" <.> exe
    need [x]
    cmd x

  "foo" ~> do
    let x = "bin/foo_test" <.> exe
    need [x]
    cmd x

  "bin/cli" <.> exe *> \o -> do
    cs <- getDirectoryFiles "" ["src//*.cpp"]
    let os = ["_build" </> c -<.> "o" | c <- cs]
    need os
    let c = "cli.cpp"
    need [c]
    cmd cxx cxx_flags "-o" (o:os) [c]

  "bin/*_test" <.> exe *> \o -> do
    cs <- getDirectoryFiles "" ["src//*.cpp"]
    let os = ["_build" </> c -<.> "o" | c <- cs]
    need os
    let c = "tests" </> dropDirectory1 (o -<.> "cpp")
    need [c]
    hs <- getDirectoryFiles "" ["//*.h"]
    need hs
    cmd cxx cxx_flags "-o" (o:os) lib_flags [c]

  "_build//*.o" *> \o -> do
    hs <- getDirectoryFiles "" ["src//*.h"]
    need hs
    let c = dropDirectory1 (o -<.> "cpp")
    need [c]
    cmd cxx cxx_flags "-c" [c] "-o" [o]
