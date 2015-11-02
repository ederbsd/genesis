/**
 * @file
 *
 * Tests for an exception class.
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

#include <genesis/exception.hpp>
#include <genesis/logger.hpp>

#include <iostream>

static bool exception_test( void )
{
  GEN_MSG( "Testing exceptions.\n" );

  try {
    throw genesis::exp_file_not_found();
  }
  catch( genesis::exp_file_not_found &e ) {
    std::cerr << "Caught: " << e.what() << std::endl;
  }

  return true;
}

static bool exception_macro_test( void )
{
  GEN_MSG( "\nTesting macro exceptions.\n" );

  GEN_CAUGHT_EXCEPTION( exp_file_not_found, "XXX. File not found!" );

  try {
    throw exp_file_not_found();
  }
  catch( exp_file_not_found &e ) {
    std::cerr << "Macro Caught: " << e.what() << std::endl;
  }

  return true;
}

int main( int argc, char* argv[] ) 
{
  GEN_TRUE_OR_ERROR( exception_test() != false,
                      "Error function: exception_test()" );

  GEN_TRUE_OR_ERROR( exception_macro_test() != false,
                      "Error function: exception_test()" );


  //throw genesis::exp_abort();

  try {
    throw genesis::exp_abort();
  }
  catch( genesis::exp_abort& e ) {
    std::cerr << "Caught: " << e.runtime_error::what() << std::endl;
    std::cerr << "Caught 2: " << e.genesis::exception::what() << std::endl;
  }

  return 0;
}
