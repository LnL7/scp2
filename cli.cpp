#include <fstream>
#include <iostream>
#include <sstream>
#include "catalogue.h"

#ifndef CLI_H
#define CLI_H

using std::istream;
using std::ostream;

using std::ifstream;
using std::ofstream;

using std::ostringstream;
using std::istringstream;
using std::string;

using std::endl;


struct Cli
{
  Catalogue catalogue;
  istream& is;
  ostream& os;
  string&  file;

  Cli (istream& is, ostream& os, string& file)
    : catalogue(map<long,shared_ptr<Entry>>()), is(is), os(os), file(file) {}

  int operator() ()
  { bool changes(false);
    os << load();

    while (is)
    { string s, command;
      getline(is, s);
      istringstream buf(s);
      buf >> command;

      if (command == "l" || command == "list")
      { os << Catalogue::Show(catalogue).s;
        continue; }
      if (command == "a" || command == "add")
      { long barcode;
        buf >> barcode;
        shared_ptr<Entry> e = Entry::Create(barcode, is, os).e;
        os << Catalogue::Add(e, catalogue).s;
        changes = true;
        continue; }
      if (command == "r" || command == "remove")
      { long barcode;
        buf >> barcode;
        os << Catalogue::Remove(barcode, catalogue).s;
        changes = true;
        continue; }
      if (command == "e" || command == "edit")
      { long barcode;
        buf >> barcode;
        shared_ptr<Entry> e = Catalogue::Get(barcode, catalogue).e;
        os << Entry::Update(is, os, e).s;
        changes = true;
        continue; }
      if (command == "stock")
      { long   barcode;
        string stock;
        buf >> barcode;
        buf >> stock;
        shared_ptr<Entry> e = Catalogue::Get(barcode, catalogue).e;
        os << Entry::Update(stock, e).s;
        changes = true;
        continue; }
      if (command == "s" || command == "save")
      { os << save();
        changes = false;
        continue; }
      if (command == "q" || command == "quit")
      { if (changes)
        { os << "Save? [Yes]" << endl;
          getline(is, command);
          if (! command.empty ())
            save();
        }
        return 0; }

      os << "Invalid Command" << endl; }
    return 1; }

  string load()
  { ifstream fs(file);
    return Catalogue::Read(fs, catalogue).s; }

  string save()
  { ofstream fs(file);
    fs << Catalogue::Show(catalogue).s;
    return "Catalogue saved.\n"; }
};


#endif

int main (int argc, char** argv) {
  string file("prijslijst.txt");
  if (argc == 2)
    file = argv[1];

  Cli client (std::cin, std::cout, file);
  return client ();
}
