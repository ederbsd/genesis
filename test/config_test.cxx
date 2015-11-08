/**
 * @file
 *
 * Tests for an config class.
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

#include <genesis/config.hxx>
#include <genesis/logger.hxx>
#include <genesis/tests.hxx>

using namespace std;

// Tests for class config.
static int config_test( void )
{
  GEN_MSG( "Tests Configuration Read File.\n" );

  // Set for tests.      
  int failed = 0;

  genesis::config cf( "config_test.conf" );

  GEN_MSG( "Here is the configuration read from test.inp: " );
  GEN_MSG( cf );

  int val_int = cf.read<int>( "integer", 0 );
  failed += GEN_TEST_RESULT( "(Config) Value of 'integer' is", 
                             val_int, 7, 0 );

  double val_double = cf.read<double>( "double", 0.0 );
  failed += GEN_TEST_RESULT( "(Config) Value of 'double' is", 
                             val_double, 1.99, 0.0 );

  bool val_bool = cf.read<bool>( "boolean", false );
  failed += GEN_TEST_RESULT( "(Config) Value of 'bool' is", 
                             val_bool, true, 0. );

  std::string val_str = cf.read<std::string>( "string", "nothing" );
  GEN_MSG( "Value of 'string' is " + val_str + "\n" );

  int method_explicit = cf.read<int>( "integer" );
  failed += GEN_TEST_RESULT( "(Config) Read integer with default as", 
                             method_explicit, 7, 0. );

  int method_default = cf.read( "integer", 0 );
  failed += GEN_TEST_RESULT( "(Config) Read integer with default as", 
                             method_default, 7, 0. );

  int val_into = 0;
  bool method_into = cf.read_into( val_into, "integer" );
  failed += GEN_TEST_RESULT( "(Config) Read integer with default as", 
                             method_into, true, 0. );

  method_into = cf.read_into( val_into, "integer", 0 );
  failed += GEN_TEST_RESULT( "(Config) Read integer into variable with default as", 
                             method_into, true, 0. );

  GEN_MSG( "----------------\n" );

  std::string type_str = cf.read<std::string>( "weight", "nothing" );
  GEN_MSG( "Value of weight as a string is " + type_str + "\n" );

  double type_double = cf.read<double>( "weight", 0.0 );
  failed += GEN_TEST_RESULT( "(Config) Value of weight as a double is", 
                             type_double, 2.5, 0. );

  int type_int = cf.read<int>( "weight", 0 );
  failed += GEN_TEST_RESULT( "(Config) Value of weight as a double is", 
                             type_int, 2, 0. );

  int repeat = cf.read<int>( "repeated" );
  failed += GEN_TEST_RESULT( "(Config) Value of 'repeated' is", 
                             repeat, 2, 0. );

  int one_stall = cf.read<int>( "oneStall" );
  failed += GEN_TEST_RESULT( "(Config) Value of oneStall is", 
                             one_stall, 1, 0. );

  int ones_tall = cf.read<int>( "onesTall" );
  failed += GEN_TEST_RESULT( "(Config) Value of onesTall is", 
                             ones_tall, 111, 0. );

  bool space_in_key = cf.read<bool>( "space key", false );
  failed += GEN_TEST_RESULT( "(Config) Value of 'space key' is", 
                             space_in_key, true, 0. );

  std::string multi_pause = cf.read<string>( "multilinePause" );
  GEN_MSG( "Value of 'multilinePause' is " + multi_pause );

  GEN_MSG( "\n----------------" );

  return failed;
}

int main( int argc, char* argv[] ) 
{
  int failed = 0;

  failed += config_test();

  GEN_TEST_PRINT_RESULT( "config", failed );

  return( failed > 0 );

}
