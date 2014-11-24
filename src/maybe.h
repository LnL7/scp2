
using std::shared_ptr;
using std::function;


#ifndef MAYBE_H
#define MAYBE_H

template<typename A>
struct Maybe
{
  enum Kind { kNothing = 0, kJust };
  using Ptr  = shared_ptr<const A>;
  const Kind k;
  const Ptr  just;

  Maybe () : k(kNothing), just(nullptr) {}
  Maybe (Ptr a) : k(kJust), just(a) {}
  Maybe (const A& a) : k(kJust), just(Ptr (new A (a))) {}

  // a -> Maybe a
  struct Return
  { const Maybe m;
    Return (const A& a) : m(Maybe (a)) {} };

  // a -> Maybe a -> a
  struct FromJust
  { const A a;
    FromJust (const A& a, const Maybe& m) : a(maybe (a, m)) {}
  private:
    A maybe (const A& a, const Maybe& m) const
    { switch (m.k)
      { case kNothing: return a;
        case kJust:    return * m.just; }}};

  // (a -> Maybe b) -> Maybe a -> Maybe b
  template<typename R>
  struct Bind
  { const Maybe<R> m;
    using Fun = function<Maybe<R>(A)>;
    Bind (Fun& f, const Maybe& m) : m(binds (f, m)) {}
  private:
    Maybe<R> binds (Fun& f, const Maybe& m) const
    { switch (m.k)
      { case kNothing: return Maybe<R>();
        case kJust:    return f(* m.just); }}};

  // (a -> b) -> Maybe a -> Maybe b
  template<typename R>
  struct Fmap
  { const Maybe<R> m;
    using Fun = function<R(A)>;
    Fmap (Fun& f, const Maybe& m) : m(fmaps (f, m)) {}
  private:
    Maybe<R> fmaps (Fun& f, const Maybe& m) const
    { switch (m.k)
      { case kNothing: return Maybe<R>();
        case kJust:    return Maybe<R>(f (* m.just)); }}};
};

#endif
