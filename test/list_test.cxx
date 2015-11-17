/**
 * @file
 *
 * Implementation for an list class.
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

#include <genesis/list.hxx>

#include <cstdio>
#include <cstdlib>

static void print_list( const genesis::proto_list::linked* str_list ) 
{
  genesis::proto_list::elements* str_element;

  int* data;
  int i = 0;

  fprintf( stdout, "List size is %d\n", GEN_LIST_SIZE( str_list ) );

  str_element = GEN_LIST_HEAD( str_list );

  while( true ) {

    data = ( int* )GEN_LIST_DATA( str_element );

    fprintf( stdout, "List[%03d]=%03d\n", i, *data );

    i++;

    if( GEN_LIST_IS_TAIL( str_element ) ) {
      break;
    } else {
      str_element = GEN_LIST_NEXT( str_element );
    }

  }

  return;
}

int main( int argc, char *argv[] )
{
  genesis::proto_list::linked str_list;
  genesis::proto_list::elements* str_element;

  int* data;
  int i = 0;

  // Initialize the linked list.
  genesis::list::init( &str_list, std::free );

  // Perform some linked list operations.
  str_element = GEN_LIST_HEAD( &str_list );

  for( i = 10; i > 0; i-- ) {

    data = new int;

    if( data == 0 ) {
      return 1;
    }

    *data = i;
    
    if( genesis::list::ins_next( &str_list, 0, data ) != 0 ) {
      return 1;
    }
  }

  print_list( &str_list );

  str_element = GEN_LIST_HEAD( &str_list );

  for( i = 0; i < 7; i++ ) {
    str_element = GEN_LIST_NEXT( str_element );
  }

  data = ( int * )GEN_LIST_DATA( str_element );
  fprintf( stdout, "Removing an element after the one containing %03zu\n", (size_t)data );

  if( genesis::list::rem_next( &str_list, str_element, ( void** )&data ) != 0 ) {
    return 1;
  }

  print_list( &str_list );

  fprintf( stdout, "Inserting 011 at the tail of the list\n" );

  *data = 11;
  if( genesis::list::ins_next( &str_list, GEN_LIST_TAIL( &str_list ), data ) != 0 ) {
    return 1;
  }

  print_list( &str_list );

  fprintf( stdout, "Removing an element after the first element\n" );

  str_element = GEN_LIST_HEAD( &str_list );
  if( genesis::list::rem_next( &str_list, str_element, ( void** )&data ) != 0 ) {
    return 1;
  }

  print_list( &str_list );

  fprintf( stdout, "Inserting 012 at the head of the list\n" );

  *data = 12;
  if( genesis::list::ins_next( &str_list, NULL, data ) != 0 ) {
    return 1;
  }

  print_list( &str_list );

  fprintf( stdout, "Iterating and removing the fourth element\n" );

  str_element = GEN_LIST_HEAD( &str_list );
  str_element = GEN_LIST_NEXT( str_element );
  str_element = GEN_LIST_NEXT( str_element );

  if( genesis::list::rem_next( &str_list, str_element, ( void** )&data ) != 0 ) {
    return 1;
  }

  print_list( &str_list );

  fprintf( stdout, "Inserting 013 after the first element\n" );

  *data = 13;
  if( genesis::list::ins_next( &str_list, GEN_LIST_HEAD( &str_list ), data ) != 0 ) {
   return 1;
  }

  print_list( &str_list );

  i = GEN_LIST_IS_HEAD( &str_list, GEN_LIST_HEAD( &str_list ) );
  fprintf( stdout, "Testing GEN_LIST_IS_HEAD... Value=%d (1=OK)\n", i );

  i = GEN_LIST_IS_HEAD( &str_list, GEN_LIST_TAIL( &str_list ) );
  fprintf( stdout, "Testing GEN_LIST_IS_HEAD... Value=%d (0=OK)\n", i );

  i = GEN_LIST_IS_TAIL( GEN_LIST_TAIL( &str_list ) );
  fprintf( stdout, "Testing GEN_LIST_IS_TAIL... Value=%d (1=OK)\n", i );

  i = GEN_LIST_IS_TAIL( GEN_LIST_HEAD( &str_list ) );
  fprintf( stdout, "Testing GEN_LIST_IS_TAIL... Value=%d (0=OK)\n", i );
  
  // Destroy the linked list.
  fprintf( stdout, "Destroying the list\n" );
  genesis::list::destroy( &str_list );
  
  return 0;
}
