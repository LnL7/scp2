#include <catalogue.h>

string Catalogue::Show::show (const map<long, shared_ptr<Entry>>& entries) const
{ ostringstream os;
  for (auto& kv : entries)
    os << Entry::Show(* kv.second).s;
  return os.str(); }

string Catalogue::Read::read (istream& is, map<long, shared_ptr<Entry>>& entries) const
{ while (is)
  { string s;
    getline(is, s);
    if (s.empty())
      break;
    istringstream buf(s);
    shared_ptr<Entry> e = Entry::Read(buf).e;
    entries[e->barcode] = e; }

  return "Catalogue loaded.\n"; }

shared_ptr<Entry> Catalogue::Get::get (long k, map<long, shared_ptr<Entry>>& entries) const
{ return entries[k]; }

shared_ptr<Entry> Catalogue::Add::add (shared_ptr<Entry> e, map<long, shared_ptr<Entry>>& entries) const
{ if (e == nullptr)
    return nullptr;
  if (entries[e->barcode] != nullptr)
    return nullptr;
  entries[e->barcode] = e;
  return e; }

string Catalogue::Add::message () const
{ if (e == nullptr)
    return "Artikel niet toegevoegd.\n";
  ostringstream os = ostringstream()
    << "Artikel " << e->barcode
    << " ("       << e->name
    << ") toegevoegd.\n";
  return os.str(); }

shared_ptr<Entry> Catalogue::Remove::remove (long key, map<long, shared_ptr<Entry>>& entries) const
{ shared_ptr<Entry> e = entries[key];
  if (e == nullptr)
    return nullptr;
  entries.erase (key);
  return e; }

string Catalogue::Remove::message () const
{ if (e == nullptr)
    return "Artikel niet verwijderd.\n";
  ostringstream os = ostringstream()
    << "Artikel " << e->barcode
    << " ("       << e->name
    << ") verwijderd.\n";
  return os.str(); }
