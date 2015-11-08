/**
 * @file
 *
 * Definitions for an factory.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_FACTORY_HPP
#define GENESIS_FACTORY_HPP

#include <genesis/unknown.hxx>

namespace genesis {

  namespace dynamic_library {

    class factory : public unknown {
    public:
      /// ID Object.
      static const char* const ID;

      /**
       * Constructor.
       */
      factory() {};

      /**
       * Destructor.
       */
      ~factory() {};

      /**
       * Efect query interface.
       */
      GEN_LIBRARY_HRESULT
       query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
        GEN_OUT void** ppv );

      /**
       * Create instance.
       */
      virtual GEN_LIBRARY_HRESULT
       create_instance( GEN_IN genesis::dynamic_library::clsid clsid, 
        GEN_OUT void** ppv ) = 0;
    };
 
  }
}

#endif // GENESIS_FACTORY_HPP
