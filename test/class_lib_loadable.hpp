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

#ifndef GENESIS_CLASS_LIB_LOADABLE_HPP
#define GENESIS_CLASS_LIB_LOADABLE_HPP

#include <genesis/factory.hpp>
#include <genesis/logger.hpp>

extern "C" {
  genesis::dynamic_library::factory* get_class_object();
}

class lib_factory : public genesis::dynamic_library::factory {
public:
  static const char* const ID;

  genesis::dynamic_library::GEN_LIBRARY_HRESULT 
   query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
    GEN_OUT void** ppv );

  genesis::dynamic_library::GEN_LIBRARY_HRESULT 
   create_instance( GEN_IN genesis::dynamic_library::clsid clsid, 
    GEN_OUT void** ppv );
};

class lib_simple : public genesis::dynamic_library::unknown {
public:
  static const char* const ID;

  genesis::dynamic_library::GEN_LIBRARY_HRESULT 
   query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
    GEN_OUT void** ppv );

  virtual int get_magic_number() const = 0;
};

class simple : public lib_simple {
public:
  // Simple interface.
  int get_magic_number() const;
};

#endif // GENESIS_CLASS_LIB_LOADABLE_HPP
