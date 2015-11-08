/**
 * @file
 *
 * Tests for an set class.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/set.hxx>
#include <genesis/logger.hxx>

#include <cstring>

static void print_set( const genesis::proto_list::set_list_linked* set ) 
{
  genesis::proto_list::elements* ptr_member;

  int* data;

  int size = 0;
  int i = 0;

  fprintf( stdout, "Set size is %d\n", size = GEN_SET_SIZE( set ) );

  ptr_member = GEN_LIST_HEAD( set );

  while( i < size ) {
   data = ( int* )GEN_LIST_DATA( ptr_member );
   fprintf( stdout, "Set[%03d]=%03d\n", i, *data );
   ptr_member = GEN_LIST_NEXT( ptr_member );
   i++;
  }

  return;
}

static int match_int( const void* key1, const void* key2 ) 
{
  return !memcmp( key1, key2, sizeof( int ) );
}

int main( int argc, char* argv[] ) 
{
  genesis::proto_list::set_list_linked set;
  genesis::proto_list::set_list_linked set1;
  genesis::proto_list::set_list_linked set2;

  int* data = 0;
  int retval = 0;
  int i = 0;

  genesis::set::init( &set, match_int, std::free );

  GEN_MSG( "Inserting 10 members" );

  for( i = 9; i >= 0; i-- ) {

    data = new int;

    if( data == 0 ) {
      return 1;
    }

    *data = i + 1;

    if(( retval = genesis::set::insert( &set, data ) ) < 0 ) {
      return 1;
    } else if( retval == 1 ) {
      delete data;
    }
  }

  print_set( &set );

  GEN_MSG( "Inserting the same members again" );

  for( i = 9; i >= 0; i-- ) {

    data = new int;

    if( data == NULL ) { 
      return 1;
    }

    *data = i + 1;

    if(( retval = genesis::set::insert( &set, data )) < 0 ) {
      return 1;
    } else if( retval == 1 ) {
      delete data;
    }

  }

  print_set( &set );

  GEN_MSG( "Inserting 200 and 100" );

  data = new int;

  if( data == 0 ) {
    return 1;
  }

  *data = 200;

  if(( retval = genesis::set::insert( &set, data )) < 0 ) {
    return 1;
  } else if( retval == 1 ) {
    delete data;
  }

  data = new int;

  if( data == 0 ) {
    return 1;
  }

  *data = 100;

  if(( retval = genesis::set::insert( &set, data )) < 0 ) {
    return 1;
  } else if( retval == 1 ) {
    delete data;
  }

  print_set( &set );
 
  GEN_MSG( "Removing 100, 5, and 11" );

  i = 100;
  data = &i;

  if( genesis::set::remove( &set, ( void** )&data ) == 0 ) {
    delete data;
  }

  i = 5;
  data = &i;

  if( genesis::set::remove( &set, ( void** )&data ) == 0 ) {
    delete data;
  }

  i = 11;
  data = &i;

  if( genesis::set::remove( &set, ( void** )&data ) == 0 ) {
    delete data;
  }

  print_set( &set );

  GEN_MSG( "Removing three members" );

  if( genesis::list::rem_next( &set, 0, ( void** )&data ) == 0 ) {
    delete data;
  }

  if( genesis::list::rem_next( &set, 0, ( void** )&data ) == 0 ) {
    delete data;
  }

  if( genesis::list::rem_next( &set, 0, ( void** )&data ) == 0 ) {
    delete data;
  }

  print_set( &set );

  GEN_MSG( "Removing all members" );

  while( GEN_SET_SIZE( &set ) > 0 ) {

    if( genesis::list::rem_next( &set, 0, ( void** )&data ) == 0 ) {
      delete data;
    }
  }

  print_set( &set );

  // Initialize two sets.
  genesis::set::init( &set1, match_int, std::free );
  genesis::set::init( &set2, match_int, std::free );

  // Perform some set operations.   
  for( i = 9; i >= 0; i-- ) {

    data = new int;

    if( data == 0 ) {
      return 1;
    }

    *data = i + 1;

    if(( retval = genesis::set::insert( &set1, data )) < 0 ) {
      return 1;
    } else if( retval == 1 ) {
      delete data;
    }

    if( i == 5 || i == 6 || i == 7 ) {

      data = new int;

      if( data == 0 ) {
        return 1;
      }

      *data = i * 10;

      if(( retval = genesis::set::insert( &set2, data )) < 0 ) {
        return 1;
      } else if( retval == 1 ) {
        delete data;
      }

    } else if( i == 3 || i == 1 ) {

        data = new int;

        if( data == 0 ) {
          return 1;
        }

        *data = i;

        if(( retval = genesis::set::insert( &set2, data )) < 0 ) {
          return 1;
        } else if( retval == 1 ) {
          delete data;
        }
    }
  }

  GEN_MSG( "Set 1 for testing unions, intersections, and differences" );
  print_set( &set1 );

  GEN_MSG( "Set 2 for testing unions, intersections, and differences" );
  print_set( &set2 );

  GEN_MSG( "Determining the union of the two sets" );

  if( genesis::set::s_union( &set, &set1, &set2 ) != 0 ) {
    return 1;
  }
  
  print_set( &set );

  GEN_MSG( "Destroying the union" );
  genesis::set::destroy( &set );

  GEN_MSG( "Determining the intersection of the two sets" );

  if( genesis::set::intersection( &set, &set1, &set2 ) != 0 ) {
    return 1;
  }

  print_set( &set );

  fprintf( stdout, "Testing whether the intersection equals Set 1...Value=%d "
             "(0=OK)\n", genesis::set::is_equal( &set, &set1 ) );

  fprintf( stdout, "Testing whether Set 1 equals itself...Value=%d (1=OK)\n",
             genesis::set::is_equal( &set1, &set1 ) );

  fprintf( stdout, "Testing whether the intersection is a subset of Set 1..."
             "Value=%d (1=OK)\n", genesis::set::is_subset( &set, &set1 ) );

  fprintf( stdout, "Testing whether Set 2 is a subset of Set 1...Value=%d "
             "(0=OK)\n", genesis::set::is_subset( &set2, &set1 ) );

  GEN_MSG( "Destroying the intersection" );
  genesis::list::destroy( &set );

  GEN_MSG( "Determining the difference of the two sets" );

  if( genesis::set::difference( &set, &set1, &set2 ) != 0 ) {
    return 1;
  }

  print_set( &set );

  i = 3;
  fprintf( stdout, "Testing whether %03d is in difference...Value=%d (0=OK)\n", i,
             genesis::set::is_member( &set, &i ) );

  i = 5;
  fprintf( stdout, "Testing whether %03d is in difference...Value=%d (1=OK)\n", i,
             genesis::set::is_member( &set, &i ) );

  // Destroy the sets.
  GEN_MSG( "Destroying the sets" );
  genesis::list::destroy( &set );
  genesis::list::destroy( &set1 );
  genesis::list::destroy( &set2 );

  return 0;
}
