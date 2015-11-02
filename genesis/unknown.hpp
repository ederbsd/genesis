/**
 * @file
 *
 * Definitions for an unknown.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_UNKNOWN_HPP
#define GENESIS_UNKNOWN_HPP

#include <genesis/genesis.hpp>
#include <genesis/clsid.hpp>

namespace genesis {
  namespace dynamic_library {
    class unknown {
    public:
      /// ID Object.
      static const char* const ID;

      /**
       * Constructor.
       */
      unknown();

      /**
       * Destructor.
       */
      ~unknown();

      /**
       * Add reference.
       */
      virtual void add_ref();

      /**
       * Release
       */
      virtual void release();

      /**
       * Query interface.
       */
      virtual GEN_LIBRARY_HRESULT 
       query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
        GEN_OUT void** ppv ) = 0;

    private:
      /// Reference.
      int ref_;
    };

  }
}

#endif // GENESIS_UNKNOWN_HPP
