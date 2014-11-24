#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE foo
#include <boost/test/unit_test.hpp>

#include "catalogue.h"

BOOST_AUTO_TEST_CASE (catalogue)
{
  shared_ptr<Entry> entryA(new Entry(5449000000995, 24, 1.00, "Coca-cola 33cl blik"));
  Catalogue catalogueA({{5449000000995, entryA}});
  BOOST_CHECK
    ( catalogueA.entries[5410041014600] == nullptr );
  BOOST_CHECK_EQUAL
    ( catalogueA.entries[5449000000995]->name
    , "Coca-cola 33cl blik" );

  shared_ptr<Entry> entryB(new Entry(5410041014600, 5, 0.30, "Cent wafels"));
  BOOST_CHECK_EQUAL
    ( Catalogue::Add(entryB, catalogueA).s
    , "Artikel 5410041014600 (Cent wafels) toegevoegd.\n" );
  BOOST_CHECK_EQUAL
    ( Catalogue::Add(entryB, catalogueA).s
    , "Artikel niet toegevoegd.\n" );

  BOOST_CHECK_EQUAL
    ( Catalogue::Remove(5410041014600, catalogueA).s
    , "Artikel 5410041014600 (Cent wafels) verwijderd.\n" );
  BOOST_CHECK_EQUAL
    ( Catalogue::Remove(5410041014600, catalogueA).s
    , "Artikel niet verwijderd.\n" );

  BOOST_CHECK
    ( catalogueA.entries[5410041014600] == nullptr );
}

