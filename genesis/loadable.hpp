/**
 * @file
 *
 * Definitions for an loadable.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_LOADABLE_HPP
#define GENESIS_LOADABLE_HPP

#include <genesis/genesis.hpp>
#include <genesis/unknown.hpp>

#include <map>

namespace genesis {
  namespace dynamic_library {
    /**
     * An interface for an object to provide an easy way to load
     * dynamic libraries and discover and instantiate objects the
     * interface is provided in addition to a default implementation
     * to allow alternative loading methods such as pulling the
     * libraries off the internet transparently (probably a security risk)
     * or perhaps compiling source code on the fly.
     */
    class loader : public unknown {
    public:
      /// ID Object.
      static const char* const ID;

      /**
       * Constructor.
       */
      loader() {};

      /**
       * Destructor.
       */
      ~loader() {};

      /**
       * Query interface.
       *
       * @param clsid - Object.
       * @param ppv - Factor.
       */
      GEN_LIBRARY_HRESULT 
       query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
        GEN_OUT void** ppv );

      /** 
       * Get the factory object defined by this library.
       * 
       * @param soname - Name library.
       * @param cf - Factor name.
       */
      virtual GEN_LIBRARY_HRESULT 
       get_class_object( GEN_IN std::string soname, GEN_OUT factory** cf ) = 0;
    };

    class loadable : public loader {
    public:
      /// ID Object.
      static const char* const ID;

      /**
       * Constructor.
       */
      loadable();

      /**
       * Destructor.
       */
      virtual ~loadable();

      /** 
       * Create unknown interface.
       */
      GEN_LIBRARY_HRESULT 
       query_interface( GEN_IN genesis::dynamic_library::clsid clsid, 
        GEN_OUT void** ppv );

      /**
       * Get the factory object defined by this library.
       */
      GEN_LIBRARY_HRESULT 
       get_class_object( GEN_IN std::string soname, GEN_OUT factory** cf );

      /**
       * A conveniance function to create some instances directly.
       */
      GEN_LIBRARY_HRESULT
       create_instance( GEN_IN std::string soname, 
        GEN_IN genesis::dynamic_library::clsid clsid, 
        GEN_OUT void** ppv );
  
    private:
      /// Keeps track of open dlls.
      std::map< std::string,void* > dlls;
    };

  }
}

#endif // GENESIS_LOADABLE_HPP
