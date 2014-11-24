#include <sstream>

#ifndef ENTRY_H
#define ENTRY_H

using std::shared_ptr;
using std::string;

using std::istream;
using std::ostream;
using std::istringstream;
using std::ostringstream;

using std::endl;


struct Entry
{
  long   barcode;
  int    stock;
  double price;
  string name;

  Entry (long barcode, int stock, double price, string name)
    : barcode(barcode), stock(stock), price(price), name(name) {}

  struct Show
  { const string s;
    Show (const Entry& e) : s(show (e)) {}

  private:
    string show (const Entry& e) const; };

  struct Read
  { shared_ptr<Entry> e;
    Read (istream& is) : e(read (is)) {}

  private:
    shared_ptr<Entry> read (istream& is) const; };

  struct Create
  { const shared_ptr<Entry> e;
    Create (long k, istream& is, ostream& os) : e(create (k, is, os)) {}

  private:
    shared_ptr<Entry> create (long k, istream& is, ostream& os) const; };

  struct Update
  { const shared_ptr<Entry> e;
    const string s;
    Update (istream& is, ostream& os, shared_ptr<Entry> e) : e(update (is, os, e)), s(message ()) {}
    Update (string& s, shared_ptr<Entry> e) : e(update (s, e)), s(message (0)) {}

  private:
    shared_ptr<Entry> update (istream& is, ostream& os, shared_ptr<Entry> e) const;
    shared_ptr<Entry> update(string& s, shared_ptr<Entry> e) const;
    string message () const;
    string message (int) const; };
};

#endif
