/**
 * @file
 *
 * Tests for convex_hull class.
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

#include <genesis/convex_hull.hpp>

#include <iostream>

int main( int argc, char *argv[] ) 
{
  std::ofstream gnuplot_file( "gnuplot.cmd" );
  const int N = 20;

  genesis::convex_hull C( N, 0, 200, 0, 200 );

  C.print_raw_points( gnuplot_file, std::cout, true );
  C.print_partitioned_points( gnuplot_file, std::cout, true );
  C.print_hull( gnuplot_file, std::cout, true );

  return 0;
}
