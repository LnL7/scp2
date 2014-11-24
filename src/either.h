
using std::shared_ptr;
using std::function;


#ifndef EITHER_H
#define EITHER_H

template<typename A,typename B>
struct Either
{
  enum Kind { kLeft, kRight };
  using PtrA = shared_ptr<const A>;
  using PtrB = shared_ptr<const B>;
  const Kind k;
  const PtrA left;
  const PtrB right;

  Either (PtrA a) : k(kLeft), left(a), right(nullptr) {}
  Either (PtrB b) : k(kRight), left(nullptr), right(b) {}
  Either (const A& a) : k(kLeft), left(PtrA (new A (a))), right(nullptr) {}
  Either (const B& b) : k(kRight), left(nullptr), right(PtrB (new B (b))) {}

  // b -> Either a b
  struct Return
  { const Either<A,B> e;
    Return (const B& b) : e(Either<A,B> (b)) {} };

  // a -> Either a b -> a
  struct FromLeft
  { const A a;
    FromLeft (const A& a, const Either& e) : a(maybe (a, e)) {}
  private:
    A maybe (const A& a, const Either& e) const
    { switch (e.k)
      { case kLeft:  return * e.left;
        case kRight: return a; }}};

  // b -> Either a b -> b
  struct FromRight
  { const B b;
    FromRight (const B& b, const Either& e) : b(maybe (b, e)) {}
  private:
    B maybe (const B& b, const Either& e) const
    { switch (e.k)
      { case kLeft:  return b;
        case kRight: return * e.right; }}};

  // (b -> Either a c) -> Either a b -> Either a c
  template<typename R>
  struct Bind
  { const Either<A,R> e;
    using Fun = function<Either<A,R>(B)>;
    Bind (Fun f, const Either& e) : e(binds (f, e)) {}
  private:
    Either<A,R> binds(Fun f, const Either& e) const
    { switch (e.k)
      { case kLeft:  return Either<A,R>(e.left);
        case kRight: return f(* e.right); }}};

  // (b -> c) -> Either a b -> Either a c
  template<typename R>
  struct Fmap
  { const Either<A,R> e;
    using Fun = function<Either<A,R>(B)>;
    Fmap (Fun f, const Either& e) : e(fmaps (f, e)) {}
  private:
    Either<A,R> fmaps(Fun f, const Either& e) const
    { switch (e.k)
      { case kLeft:  return Either<A,R>(e.left);
        case kRight: return Either<A,R>(f (* e.right)); }}};
};

#endif
