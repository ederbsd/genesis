/**
 * @file
 *
 * Test for an maths class.
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

#include <genesis/maths.hpp>
#include <genesis/geometry.hpp>
#include <genesis/logger.hpp>
#include <genesis/tests.hpp>

#include <iomanip>
#include <iostream>

// Define the maximum size of arrays.
static const short int SIZE = 50;

// F.
static double f( double x )
{
  return( std::pow( x, 3.0 )) - ( std::pow( x, 2.0 )) - ( 3.0 * x ) + 1.8;
}

// G.
static double g( double x )
{
  return( 3.0 * std::pow( x, 2.0 ) ) - ( 2.0 * x ) - 3.0;
}

// Test method base facts
static int factor_test( void )
{
  GEN_MSG( "Computer the factorials of several numbers.\n" );

  register int n = 0;

  for( n = 0; n <= 13; n++ ) {
    fprintf( stdout, "%2d! Recursive: %-10d ", n,
      genesis::maths::base::compute_fact( n ) );
    fprintf( stdout, "Tail Recursive: %-10d\n",
      genesis::maths::base::compute_fact_tail( n, 1 ) );
  }

  GEN_MSG( "" );

  // Set for test.
  n = 1932053504;

  int failed = 0;
  //failed += genesis::tests::result( "(Factor) Recursive:   ", n, 1932053504, 0 );
  failed += GEN_TEST_RESULT( "(Factor) Recursive:   ", n, 1932053504, 0 );


  GEN_MSG( "Compute the prime factors of several numbers.\n" );

  // 10000
  for( n = 1; n <= 100; n++ ) {
    fprintf( stdout, "Factoring %d\n", n );
    genesis::maths::base::compute_factor( n, n, 2 );
  }

  GEN_MSG( "" );

  // Set for test.
  n = 83;
  
  failed += GEN_TEST_RESULT( "(Factor) Is prime:   ", n, 83, 0 );

  GEN_MSG( "End: Compute factors.\n" );

  return failed;
}

// Test method linear interpolation.
static int linear_interpolation_test( void )
{
    GEN_MSG( "Perform Linear polynomial interpolation.\n" );

    static const int N = 12;

    double x[N];
    double y[N];

    register int i = 0;
    register int n_out = 20;
 
    double xx = GEN_GEOMETRY_PI;
    double step = 4 * GEN_GEOMETRY_PI / ( N - 1 );

    for( i = 0; i < N; ++i, xx += step ) {
        x[i] = xx;
        y[i] = std::sin( 2 * xx ) / xx;
    }
 
    genesis::maths::interpolation::linear( x, y, N );
 
    xx = GEN_GEOMETRY_PI;
    step = ( 3 * GEN_GEOMETRY_PI ) / ( n_out - 1 );

    for( i = 0; i < n_out; ++i, xx += step ) {
      std::cout << "x = " << std::setw( 7 ) << xx << "  y = ";
      std::cout << std::setw( 13 ) 
                << genesis::maths::interpolation::linear_get_y( xx ) 
                << std::endl;
  }

  GEN_MSG( "" );
 
  int failed = 0;
  failed += GEN_TEST_RESULT( "(Linear) Value xx:   ", xx, 13.06241156, 0.00001 );

  GEN_MSG( "End: Linear Interpolation.\n" );

  return failed;

}

// Test method lagrange interpolation.
static int lagrange_interpolation_test( void )
{
  GEN_MSG( "Perform Lagrange polynomial interpolation.\n" );

  static const int N = 12;

  register int i = 0;
  register int n_out = 20;

  double x[N];
  double y[N];

  double xx = GEN_GEOMETRY_PI;
  double step = 4 * GEN_GEOMETRY_PI / ( N - 1 );

  for( i = 0; i < N; ++i, xx += step ) {
        x[i] = xx;
        y[i] = std::sin( 2 * xx ) / xx;
  }

  genesis::maths::interpolation::lagrange( x, y, N );

  xx = GEN_GEOMETRY_PI; 
  step = ( 3 * GEN_GEOMETRY_PI ) / ( n_out - 1 );

  for( i = 0; i < n_out; ++i, xx += step ) {
    std::cout << "x = " << std::setw( 7 ) << xx << "  y = ";
    std::cout << std::setw( 13 ) 
              << genesis::maths::interpolation::lagrange_get_y( xx ) 
              << std::endl;
  }

  GEN_MSG( "" );

  int failed = 0;
  failed += GEN_TEST_RESULT( "(Lagrange) Value xx:   ", xx, 13.06241156, 0.00001 );

  GEN_MSG( "End: Lagrange Interpolation.\n" );

  return failed;
}

// Test method least square.
static int least_square_test( void )
{
  double x[SIZE], y[SIZE];

  double b1 = 0.0;
  double b0 = 0.0;

  register int i = 0;
  
  GEN_MSG( "Perform least-squares estimation.\n" );

  x[0] =  4.0; y[0] =  197.0;
  x[1] =  6.0; y[1] =  272.0;
  x[2] =  2.0; y[2] =  100.0;
  x[3] =  5.0; y[3] =  228.0;
  x[4] =  7.0; y[4] =  327.0;
  x[5] =  6.0; y[5] =  279.0;
  x[6] =  3.0; y[6] =  148.0;
  x[7] =  8.0; y[7] =  377.0;
  x[8] =  5.0; y[8] =  238.0;
  x[9] =  3.0; y[9] =  142.0;
  x[10] = 1.0; y[10] =  66.0;
  x[11] = 5.0; y[11] = 239.0;

  for( i = 0; i < 12; i++ ) {
    fprintf( stdout, "x[%02d]=%+1.6e, y[%02d]=%+1.6e\n", i, x[i], i, y[i] );
  }

  GEN_ASSERT( b1 >= 0. );
  GEN_ASSERT( b0 >= 0. );

  genesis::maths::interpolation::least_square( x, y, 12, &b1, &b0 );

  fprintf( stdout, "b1=%+1.6e, b0=%+1.6e\n", b1, b0 );

  GEN_MSG( "" );

  int failed = 0;
  failed += GEN_TEST_RESULT( "(Least Square) Value b1:   ", b1, +0.000000e+00, 0.00000 );
  failed += GEN_TEST_RESULT( "(Least Square) Value b0:   ", b0, +0.000000e+00, 0.00000 );

  GEN_MSG( "End: Least Square.\n" );

  return failed;
}

// Test method root Newton.
static int root_newton_test( void )
{
  double x[SIZE];
 
  register int retval = 0;
  register int i = 0;
  register int n = 0; 

  GEN_MSG( "Finding the roots of an equation.\n" );

  n = 10;
  x[0] = -2.0;

  retval = genesis::maths::root::newton( f, g, x, &n, 0.0001 );

  for( i = 0; i < n; i++ ) {
    fprintf( stdout, "x[%d]=%+1.6e\n", i, x[i] );
  }

  GEN_TRUE_OR_ERROR( retval == 0, "Did not find a root!" );
  fprintf( stdout, "Found a root at: %+1.6e\n\n", x[n - 1] );

  n = 10;
  x[0] = 0.5;

  retval = genesis::maths::root::newton( f, g, x, &n, 0.0001 );

  for( i = 0; i < n; i++ ) {
    fprintf( stdout, "x[%d]=%+1.6e\n", i, x[i] );
  }

  GEN_TRUE_OR_ERROR( retval == 0, "Did not find a root!" );
  fprintf( stdout, "Found a root at: %+1.6e\n\n", x[n - 1] );

  n = 10;
  x[0] = 2.0;

  retval = genesis::maths::root::newton( f, g, x, &n, 0.0001 );

  for( i = 0; i < n; i++ ) {
    fprintf( stdout, "x[%d]=%+1.6e\n", i, x[i] );
  }

  GEN_TRUE_OR_ERROR( retval == 0, "Did not find a root!" );
  fprintf( stdout, "Found a root at: %+1.6e\n", x[n - 1] );

  GEN_MSG( "" );

  // Set for test.
  double root = -4.51496;

  int failed = 0;
  failed += GEN_TEST_RESULT( "(Root Newton) Value b1:   ", root, -4.51496, 0.00000 );

  GEN_MSG( "End: Root Newton.\n" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += factor_test();
  failed += linear_interpolation_test();
  failed += lagrange_interpolation_test();
  failed += least_square_test();
  failed += root_newton_test();

  GEN_TEST_PRINT_RESULT( "maths", failed );

  return( failed > 0 );
}
