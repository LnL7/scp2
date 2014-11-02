import Development.Shake
import Development.Shake.Command
import Development.Shake.FilePath
import Development.Shake.Util


main :: IO ()
main = shakeArgs shakeOptions{shakeFiles="_build/"} $ do
  want ["_build/run" <.> exe]

  let cpp = "clang++ -Ilib -std=c++11 -g -Wall -pedantic"

  "clean" ~> do
    putNormal "Cleaning files in _build"
    removeFilesAfter "_build" ["//*"]

  "run" ~> do
    let x = "_build/run" <.> exe
    need [x]
    cmd x

  "foo_test" ~> do
    let x = "_build/tests/foo_test" <.> exe
    need [x]
    cmd x


  let _gmock = ("_build/gmock-1.7.0" </>)
  let _gtest = ("_build/gmock-1.7.0/gtest" </>)

  "_build/tests/foo_test" <.> exe *> \f -> do
    cs <- getDirectoryFiles "" ["lib//*.cpp"]
    hs <- getDirectoryFiles "" ["lib//*.h"]
    need hs
    let os = ["_build" </> c -<.> "o" | c <- cs]
    need os
    let c = dropDirectory1 f <.> "cpp"
    let m = f -<.> "m"
    need [c, "_build/gmock-1.7.0/libgmock.a"]
    cmd cpp "-isystem gmock-1.7.0/gtest/include -isystem gmock-1.7.0/include -pthread" (c:cs) [_gmock "libgmock.a"] "-o" [f]

  _gmock "libgmock.a" *> \f -> do
    let os = [_gtest "src/gtest-all.o", _gmock "src/gmock-all.o"]
    need os
    cmd "ar -rv" [f] os

  _gtest "src/gtest-all.o" *> \f -> do
    let cc = dropDirectory1 f -<.> "cc"
    need [cc]
    cmd cpp "-isystem gmock-1.7.0/include -Igmock-1.7.0 -isystem gmock-1.7.0/gtest/include -Igmock-1.7.0/gtest -pthread -c" [cc] "-o" [f]

  _gmock "src/gmock-all.o" *> \f -> do
    let cc = dropDirectory1 f -<.> "cc"
    need [cc]
    cmd cpp "-isystem gmock-1.7.0/gtest/include -Igmock-1.7.0/gtest -isystem gmock-1.7.0/include -Igmock-1.7.0 -pthread -c" [cc] "-o" [f]

  "_build/run" <.> exe *> \f -> do
    cs <- getDirectoryFiles "" ["lib//*.cpp"]
    hs <- getDirectoryFiles "" ["lib//*.h"]
    need hs
    let os = ["_build" </> c -<.> "o" | c <- ("run.cpp":cs)]
    need os
    cmd "clang++ -o" [f] os

  "_build//*.o" *> \f -> do
    let c = dropDirectory1 f -<.> "cpp"
    let m = f -<.> "m"
    () <- cmd cpp "-c" [c] "-o" [f] "-MMD -MF" [m]
    needMakefileDependencies m
