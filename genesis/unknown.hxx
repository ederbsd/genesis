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

#pragma once
#ifndef GENESIS_UNKNOWN_HXX
#define GENESIS_UNKNOWN_HXX

#include <genesis/clsid.hxx>

namespace genesis {
namespace dynamic_library {
class unknown
{
public:
    /// ID Object.
    static const char *const ID;

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
                     GEN_OUT void **ppv ) = 0;

private:
    /// Reference.
    int ref_;
};

}
}

#endif // GENESIS_UNKNOWN_HXX
