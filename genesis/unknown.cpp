/**
 * @file
 *
 * Implementation for an unknown.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/unknown.hpp>

namespace genesis {
  namespace dynamic_library {

    const char* const unknown::ID = "genesis::dynamic_library::unknown";

    unknown::unknown() 
     : ref_( 0 )
    {
      return;
    }

    unknown::~unknown()
    {
    }

    void unknown::add_ref()
    {
      ref_++;
    }

    void unknown::release()
    {
      if( --ref_ == 0 ) {
      }
    }

    GEN_LIBRARY_HRESULT unknown::query_interface( 
     GEN_IN genesis::dynamic_library::clsid clsid, 
     GEN_OUT void** ppv )
    {
      GEN_LIBRARY_HRESULT ret = GEN_E_NOINTERFACE;
      *ppv = 0;

      if( clsid == unknown::ID ) {
        *ppv = (void*)this;
	add_ref();
	ret = GEN_E_NOERR;
      }

      return ret;
    }

  }
} 
