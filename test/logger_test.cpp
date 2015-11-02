/**
 * @file
 *
 * Tests for an logger class.
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

#include <genesis/logger.hpp>

int main( int argc, char* argv[] ) 
{
  GEN_LOG_MSG( "Genesis logger in main()." );

  double const a = 1.0;
  std::string const str = "test";
  std::pair<std::string, double> p( "PI", 3.1415 );
  std::pair<unsigned long, std::string> q( 10, "EUR" );

  GEN_LOG( a );
  GEN_LOG( str );
  //GEN_LOG( p );

  if( true ) {
    //GEN_LOG( q ); 
  } else {
    GEN_LOG( str );
  }

  int param = 7;
  GEN_TRUE_OR_ERROR( param == 6, "Invalid size!" );

  double res = 0.;
  GEN_ASSERT( res >= 0. );

  GEN_ASSERT( a >= 0. );

  int n = 20;
  GEN_ASSERT( n >= 0 );

  GEN_WARN( "Invalid format!" );
  return 0;
}
