/**
 * @file
 *
 * Implementations for an loadable.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009-2015 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_LOADABLE_HXX
#include <genesis/loadable.hxx>
#endif
#ifndef GENESIS_EXCEPTION_HXX
#include <genesis/exception.hxx>
#endif
#ifndef GENESIS_FACTORY_HXX
#include <genesis/factory.hxx>
#endif
#ifndef GENESIS_GENESIS_HXX
#include <genesis/genesis.hxx>
#endif
#ifndef GENESIS_LOGGER_HXX
#include <genesis/logger.hxx>
#endif

#include <cstdio>

extern "C" {
#include <dlfcn.h>
}

namespace genesis {
namespace dynamic_library {

const char *const loader::ID = "genesis::dynamic_library::loader";

GEN_LIBRARY_HRESULT
loader::query_interface( GEN_IN genesis::dynamic_library::clsid clsid,
                         GEN_OUT void **ppv )
{
    GEN_LIBRARY_HRESULT ret = unknown::query_interface( clsid, ppv );

    if ( ret == GEN_E_NOERR ) {
        return ret;
    } else if ( clsid == loader::ID ) {
        *ppv = ( void * )this;
        add_ref();
        ret = GEN_E_NOERR;
    }

    return ret;
}

const char *const loadable::ID = "genesis::dynamic_library::loadable";

loadable::loadable()
{
}

loadable::~loadable()
{
    std::map< std::string, void * >::iterator i;
    for ( i = dlls.begin(); i != dlls.end(); i++ ) {
        dlclose( i->second );
    }
}

GEN_LIBRARY_HRESULT
loadable::query_interface( GEN_IN genesis::dynamic_library::clsid clsid,
                           GEN_OUT void **ppv )
{
    GEN_LIBRARY_HRESULT ret  = loadable::query_interface( clsid, ppv );

    if ( ret == GEN_E_NOERR ) {
        return ret;
    } else if ( clsid == loadable::ID ) {
        *ppv = ( void * )this;
        add_ref();
        ret = GEN_E_NOERR;
    }

    return ret;
}

GEN_LIBRARY_HRESULT
loadable::get_class_object( GEN_IN std::string soname, GEN_OUT factory **cf )
{
    void *handle;
    const char *errmsg = 0;

    get_class_object_func p_get_class_object;

    *cf = 0;

    std::map< std::string, void * >::iterator i = dlls.find( soname );

    if ( i == dlls.end() ) {

        // Load library.
        handle = dlopen( soname.c_str(), RTLD_NOW );

        if ( handle == 0 ) {
            GEN_ERROR( "Couldn't open dll (check LD_LIBRARY_PATH):" );
            fprintf( stderr, "Failed to load library '%s': %s\n",
                     soname.c_str(), dlerror() );
            // Abort now...
            throw genesis::exp_abort();

        } else {
            dlls[soname] = handle;
        }

        // Clear errors.
        dlerror();

    } else {
        handle = dlls[soname];
    }

    p_get_class_object = ( get_class_object_func) dlsym( handle, "get_class_object" );

    if ( ( errmsg = dlerror() ) != 0 ) {
        GEN_ERROR( "Couldn't find dll entry point (C linkage?):" );
        fprintf( stderr, "Didn't find get_class_object(): %s\n", errmsg );

        // Abort now...
        throw genesis::exp_abort();
    }

    *cf = p_get_class_object();
    return GEN_E_NOERR;
}

GEN_LIBRARY_HRESULT
loadable::create_instance( GEN_IN std::string soname,
                           GEN_IN genesis::dynamic_library::clsid clsid,
                           GEN_OUT void **ppv )
{
    GEN_LIBRARY_HRESULT hresult;
    factory *factory;

    hresult = get_class_object( soname, &factory );

    if ( hresult == GEN_E_NOERR ) {
        hresult = factory->create_instance( clsid, ppv );
        factory->release();
    }

    return hresult;
}

}
}
