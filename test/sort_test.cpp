/**
 * @file
 *
 * Implementation for an sort class.
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

#include <genesis/sort.hpp>

#include <cstdio>
#include <cstring>

static const int STRSIZ = 6;

static int compare_int( const void* int1, const void* int2 ) 
{
  if( *( const int* )int1 > *( const int *) int2 ) {
    return 1;
  } else if( *( const int* )int1 < *( const int *) int2 ) {
    return -1;
  } else {
    return 0;
  }
}

static void print_idata( const int* array, int size ) 
{
  register int i = 0;

  // Display the array of integers.
  for( i = 0; i < size; i++ ) {
    fprintf( stdout, "A[%02d]=%d\n", i, array[i] );
  }

  return;
}

int main( int argc, char* argv[] ) 
{
  int iarray[10];
  int marray[10];
  int qarray[10];
  int carray[10];
  int rarray[10];
 
  char sarray[10][STRSIZ];
 
  register int size = 10;

  // Load the arrays with data to sort.
  iarray[0] = 0;
  iarray[1] = 5;
  iarray[2] = 1;
  iarray[3] = 7;
  iarray[4] = 3;
  iarray[5] = 2;
  iarray[6] = 8;
  iarray[7] = 9;
  iarray[8] = 4;
  iarray[9] = 6;

  std::memcpy( marray, iarray, size * sizeof( int ) );
  std::memcpy( qarray, iarray, size * sizeof( int ) );
  std::memcpy( carray, iarray, size * sizeof( int ) );

  rarray[0] = 11111323;
  rarray[1] = 99283743;
  rarray[2] = 98298383;
  rarray[3] = 99987444;
  rarray[4] = 43985209;
  rarray[5] = 99911110;
  rarray[6] = 11111324;
  rarray[7] = 39842329;
  rarray[8] = 97211029;
  rarray[9] = 99272928;

  strcpy( sarray[0], "ebcde" );
  strcpy( sarray[1], "ghidj" );
  strcpy( sarray[2], "ghiea" );
  strcpy( sarray[3], "abaae" );
  strcpy( sarray[4], "abaaa" );
  strcpy( sarray[5], "abcde" );
  strcpy( sarray[6], "abbcd" );
  strcpy( sarray[7], "ddaab" );
  strcpy( sarray[8], "faeja" );
  strcpy( sarray[9], "aaaaa" );

  // Perform insertion sort.
  fprintf( stdout, "Test ==> Before sort::issort ...\n" );
  print_idata( iarray, size );

  if( genesis::sort::issort( iarray, size, sizeof( int ), compare_int ) != 0 ) {
    return 1;
  }

  fprintf( stdout, "Test ==> After sort::issort ...\n" );
  print_idata( iarray, size );

  // Perform isort ct.
  if( genesis::sort::ct( carray, size, 10 ) != 0 ) {
    return 1;
  }

  fprintf( stdout, "Test ==> After sort::ct ...\n" );
  print_idata( carray, size );

  return 0;  
}
