/**
 * @file
 *
 * Tests for an genesis class.
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

#include <genesis/genesis.hpp>
#include <genesis/logger.hpp>

int main( int argc, char* argv[] ) 
{
  genesis::library::check_build_details();
  GEN_MSG( genesis::library::version() );
  GEN_MSG( genesis::library::package() );

  GEN_MSG( "\nComputer architecture is: " );
  if( genesis::library::is_big_endian() ) {
    GEN_MSG( "Big Endian!" );
  } else {
    GEN_MSG( "Little Endian (or other non-Big Endian)." );
  }

  return 0;
}
