#include <map>
#include <sstream>
#include "entry.h"

#ifndef CATALOGUE_H
#define CATALOGUE_H

using std::shared_ptr;
using std::string;

using std::map;

using std::istream;
using std::ostream;
using std::istringstream;
using std::ostringstream;

using std::endl;


struct Catalogue
{
  map<long, shared_ptr<Entry>> entries;

  Catalogue (map<long, shared_ptr<Entry>> entries)
    : entries(entries) {}

  struct Show
  { const string s;
    Show (const Catalogue& c) : s(show (c.entries)) {}

  private:
    string show (const map<long, shared_ptr<Entry>>& entries) const; };

  struct Read
  { const string s;
    Read (istream& is, Catalogue& c) : s(read (is, c.entries)) {}

  private:
    string read (istream& is, map<long, shared_ptr<Entry>>& entries) const; };

  struct Get
  { const shared_ptr<Entry> e;
    Get (long k, Catalogue& c) : e(get (k, c.entries)) {}

  private:
    shared_ptr<Entry> get (long k, map<long, shared_ptr<Entry>>& entries) const; };

  struct Add
  { const shared_ptr<Entry> e;
    const string s;
    Add (shared_ptr<Entry> e, Catalogue& c)
      : e(add (e, c.entries)), s(message ()) {}

  private:
    shared_ptr<Entry> add (shared_ptr<Entry> e, map<long, shared_ptr<Entry>>& entries) const;
    string message () const; };


  struct Remove
  { const shared_ptr<Entry> e;
    const string s;
    Remove (long k, Catalogue& c)
      : e(remove (k, c.entries)), s(message ()) {}

  private:
    shared_ptr<Entry> remove (long key, map<long, shared_ptr<Entry>>& entries) const;
    string message () const; };
};

#endif
