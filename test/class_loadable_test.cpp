/**
 * @file
 *
 * Tests for an loadable class.
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

#include "class_lib_loadable.hpp"

#include <genesis/genesis.hpp>
#include <genesis/factory.hpp>
#include <genesis/logger.hpp>
#include <genesis/loadable.hpp>

// Name lib test.
static const std::string libload_ = "libload.so";

int main( int argc, char* argv[] )
{
  genesis::dynamic_library::loadable* loader;
  genesis::dynamic_library::factory* factory;
  genesis::dynamic_library::GEN_LIBRARY_HRESULT res;

  loader = new genesis::dynamic_library::loadable();
  loader->add_ref();

  // Open lib test.
  res = loader->get_class_object( libload_, &factory );

  GEN_ASSERT( res == GEN_E_NOERR );

  lib_simple* simple;
  res = factory->create_instance( 
   genesis::dynamic_library::clsid( "lib_simple" ),
   ( void** )& simple );

  GEN_ASSERT( res == GEN_E_NOERR );

  // Print magic number.
  GEN_MSG( simple->get_magic_number() );

  simple->release();
  loader->release();

  return 0;
}
