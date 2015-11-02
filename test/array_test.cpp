/**
 * @file
 *
 * Tests for an array class.
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

#include <genesis/array.hpp>
#include <genesis/tests.hpp>

// Test array method vector.
static int vector_test( void )
{
  GEN_MSG( "Create Vector." );

  int failed = 0;

  double* a = genesis::array::vector::create_vector<double>( 1, 10 );

  a[1] = 23.4;
  a[10] = 56.7;

  genesis::array::vector::free_vector( a, 1 );

  int* b = genesis::array::vector::create_vector<int>( 20, 30 );

  b[20] = 4;
  b[30] = 5;

  genesis::array::vector::free_vector( b, 20 );

  //char* c = genesis::array::vector::create_vector<char>( 11 );

  GEN_MSG( "End: Array Vector.\n" );

  return failed;
}

// Test matrix.
static bool matrix_test( void )
{
  GEN_MSG( "Create Matrix.\n" );

  int failed = 0;

  int** A = genesis::array::matrix::create_matrix<int>( 5, 3 );

  register int j = 0;
  register int i = 0;

  for( j = 0; j < 5; j++ ) {
    for( i = 0; i < 3; i++ ) {
      A[j][i] = i * j;
    }
  }

  int* B = A[0];
  for( i = 0; i < 15; i++ ) {
    fprintf( stdout, " %d", B[i] );
  }

  genesis::array::matrix::free_matrix( A );

  GEN_MSG( "\n\nEnd: Array Matrix.\n" );

  return failed;
}

// Test array cube.
static int cube_test( void )
{
  GEN_MSG( "Create Cube.\n" );

  int failed = 0;

  char*** c = genesis::array::matrix::create_cube<char>( 2,4,6 );

  register int i = 0;
  register int j = 0;
  register int k = 0;

  for( i = 0; i < 6; i++ ) {
    for( j = 0; j < 4; j++ ) {
      for( k = 0; k < 2; k++ ) {
        c[k][j][i] = i+j+k;
      }
    }
  }

  for( i = 0; i < ( 6*4 ); i++ ) {
    if( i % 6 == 0 ) {
      printf( "  " );
    }
    printf( "%hhd ", c[0][0][i] );
  }

  GEN_MSG( "" );

  for( i = 6*4; i < 6*4*2; i++ ) {
    if( i % 6 == 0 ) {
      printf( "  " );
    }
    printf( "%hhd ", c[0][0][i] );
  }

  GEN_MSG( "" );

  genesis::array::matrix::free_cube<char>( c );

  GEN_MSG( "\nEnd: Array Cube.\n" );

  return failed;
}

// Test array method binary_search.
static int binary_search_test( void )
{
  GEN_MSG( "Binary Search Elements.\n" );

  // For tests.
  int failed = 0;

  double key = 0.;

  std::vector<double> v;

  v.push_back( 20060721151401.231 ); // 1
  v.push_back( 20060721151401.717 ); // 2
  v.push_back( 20060721151402.220 ); // 3
  v.push_back( 20060721151402.716 ); // 4
  v.push_back( 20060721151404.227 ); // 5
  v.push_back( 20060721151404.717 ); // 6
  v.push_back( 20060721151405.217 ); // 7
  v.push_back( 20060721151405.726 ); // 8
  v.push_back( 20060721151406.224 ); // 9
  v.push_back( 20060721151406.717 ); // 10

  // Search position element 1.
  key = 20060721151402.716;
  GEN_MSG( "Search Value: 20060721151402.716" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 1: ", 4, 4, 0 );

  // Search position element 2.
  key = 20060721151404.227;
  GEN_MSG( "Search Value: 20060721151404.227" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 2: ", 5, 5, 0 );

  // Search position element 3.
  key = 20060721151406.224;
  GEN_MSG( "Search Value: 20060721151406.224" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 3: ", 9, 9, 0 );

  // Search position element 4.
  key = 20060721151401.717;
  GEN_MSG( "Search Value: 20060721151401.717" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 4: ", 2, 2, 0 );

  // Search position element 5.
  key = 20060721151405.217;
  GEN_MSG( "Search Value: 20060721151405.217" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 5: ", 7, 7, 0 );

  // Search position element 6.
  key = 20060721151401.231;
  GEN_MSG( "Search Value: 20060721151401.231" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 6: ", 1, 1, 0 );

  // Search position element 7.
  key = 20060721151402.220;
  GEN_MSG( "Search Value: 20060721151402.220" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 7: ", 3, 3, 0 );

  // Search position element 8.
  key = 20060721151404.717;
  GEN_MSG( "Search Value: 20060721151404.717" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 8: ", 6, 6, 0 );

  // Search position element 9.
  key = 20060721151406.224;
  GEN_MSG( "Search Value: 20060721151406.224" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 9: ", 9, 9, 0 );

  // Search position element 10.
  key = 20060721151406.717;
  GEN_MSG( "Search Value: 20060721151406.717" );
  genesis::array::vector::binary_search<double>( v, key );
  failed += GEN_TEST_RESULT( "(Binary Search) Location Element 10: ", 
                             10, 10, 0 );

  GEN_MSG( "End: Binary Search.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += vector_test();
  failed += matrix_test();
  failed += cube_test();
  failed += binary_search_test();

  GEN_TEST_PRINT_RESULT( "array", failed );

  return( failed > 0 );
}
