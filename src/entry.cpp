#include "entry.h"

string Entry::Show::show (const Entry& e) const
{ ostringstream os;
  os.setf(std::ios::fixed);
  os.precision(2);
  os << e.barcode << "\t"
     << e.stock   << "\t"
     << e.price   << "\t"
     << e.name    << "\n";
  return os.str(); }

shared_ptr<Entry> Entry::Read::read (istream& is) const
{ long   barcode;
  int    stock;
  double price;
  string name;

  is >> barcode;
  is >> stock;
  is >> price;

  // Remove \t
  char c;
  is.get(c);

  getline(is, name);
  return shared_ptr<Entry>(new Entry (barcode, stock, price, name)); };

shared_ptr<Entry> Entry::Create::create (long k, istream& is, ostream& os) const
{ string s;
  int    stock;
  double price;
  string name;

  os << "Naam?" << endl;
  getline(is, name);
  if (name.empty ())
    return nullptr;

  os << "Prijs?" << endl;
  getline(is, s);
  if (s.empty ())
    return nullptr;
  istringstream(s) >> price;
  if (price <= 0)
    return nullptr;

  os << "Voorraad?" << endl;
  getline(is, s);
  if (s.empty ())
    return nullptr;
  istringstream(s) >> stock;
  if (stock < 0)
    return nullptr;

  return shared_ptr<Entry>(new Entry (k, stock, price, name)); }


shared_ptr<Entry> Entry::Update::update (istream& is, ostream& os, shared_ptr<Entry> e) const
{ string s;

  if (e == nullptr)
    return nullptr;

  os << "Naam? [" << e->name << "]" << endl;
  getline(is, s);
  if (! s.empty ())
    e->name = s;

  os << "Prijs? [" << e->price << "]" << endl;
  getline(is, s);
  if (! s.empty ())
  { double price;
    istringstream(s) >> price;
    if (price <= 0)
      return nullptr;
    e->price = price; }

  os << "Voorraad? [" << e->stock << "]" << endl;
  getline(is, s);
  if (! s.empty ())
  { int stock;
    istringstream(s) >> stock;
    if (stock < 0)
      return nullptr;
    e->stock = stock; }

  return e; }

shared_ptr<Entry> Entry::Update::update(string& s, shared_ptr<Entry> e) const
{ int i;
  if (e == nullptr)
    return nullptr;
  if (s.empty ())
    return nullptr;

  if (s[0] == '-')
  { istringstream(s.erase (0, 1)) >> i;
    i = -i;
    i += e->stock; }
  else if (s[0] == '+')
  { istringstream(s.erase (0, 1)) >> i;
    i += e->stock; }
  else
    istringstream(s) >> i;

  if (i < 0)
    return nullptr;

  e->stock = i;
  return e; }

string Entry::Update::message () const
{ if (e == nullptr)
    return "Artikel niet aangepast.\n";
  ostringstream os = ostringstream()
    << "Artikel " << e->barcode
    << " ("       << e->name
    << ") aangepast.\n";
  return os.str(); }

string Entry::Update::message (int) const
{ if (e == nullptr)
    return "Stock niet aangepast.\n";
  ostringstream os = ostringstream()
    << "Stock voor " << e->barcode
    << " ("          << e->name
    << ") is nu "    << e->stock
    << ".\n";
  return os.str(); }
