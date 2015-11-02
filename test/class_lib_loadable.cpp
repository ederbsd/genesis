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

const char* const lib_simple::ID = "lib_simple";
const char* const lib_factory::ID = "lib_factory";

extern "C" {
  genesis::dynamic_library::factory* get_class_object() {
    genesis::dynamic_library::factory* ret;
    ret = new lib_factory();
    ret->add_ref();
    return ret;
  }
}

genesis::dynamic_library::GEN_LIBRARY_HRESULT 
 lib_factory::query_interface( GEN_IN genesis::dynamic_library::clsid clsid,
  GEN_OUT void** ppv )
{
  genesis::dynamic_library::GEN_LIBRARY_HRESULT ret;

  if( clsid == lib_factory::ID ) {
    *ppv = ( void* )this;
    add_ref();
    ret = GEN_E_NOERR;
  } else {
    ret = factory::query_interface( clsid, ppv );
  }

  return ret;
}

genesis::dynamic_library::GEN_LIBRARY_HRESULT 
 lib_factory::create_instance( GEN_IN genesis::dynamic_library::clsid clsid,
  GEN_OUT void** ppv )
{
  genesis::dynamic_library::GEN_LIBRARY_HRESULT ret;
  genesis::dynamic_library::unknown* obj;

  if( clsid == lib_simple::ID ) {
    obj = new simple();
    obj->add_ref();
    *ppv = obj;
    ret = GEN_E_NOERR;
  } else {
    ret = GEN_E_NOINTERFACE;
  }

  return ret;
}

genesis::dynamic_library::GEN_LIBRARY_HRESULT 
 lib_simple::query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
  GEN_OUT void** ppv )
{
  genesis::dynamic_library::GEN_LIBRARY_HRESULT ret;

  if( clsid == lib_simple::ID ) {
    add_ref();
    *ppv = ( void* )this;
    ret = GEN_E_NOERR;
  } else {
    ret = unknown::query_interface( clsid, ppv );
  }

  return ret;
}

int simple::get_magic_number() const
{
  GEN_MSG( "Returning magic number!" ); 
  return 100;
}
