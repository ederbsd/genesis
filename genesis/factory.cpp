/**
 * @file
 *
 * Implementations for an factory.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <genesis/factory.hpp>

namespace genesis {
  namespace dynamic_library {

    const char* const factory::ID = "genesis::dynamic_library::factory";

    GEN_LIBRARY_HRESULT factory::query_interface( 
     GEN_IN genesis::dynamic_library::clsid clsid,
     GEN_OUT void** ppv )
    {
      GEN_LIBRARY_HRESULT ret;

      if( clsid == factory::ID ) {
        *ppv = ( void* )this;
        add_ref();
        ret = GEN_E_NOERR;
      } else {
        ret = unknown::query_interface( clsid, ppv );
      }

      return ret;
    }

 }
}
