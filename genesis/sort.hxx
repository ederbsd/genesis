/**
 * @file
 *
 * Definitions for an sort.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#pragma once
#ifndef GENESIS_SORT_HXX
#define GENESIS_SORT_HXX

namespace genesis {
/**
 * Genesis Sort Class.
 */
class sort
{
public:
    /**
     * ct
     *
     * @param data - ...
     * @param size - ...
     * @param k - ...
     */
    static int ct( int *data, int size, int k );

    /**
     * issort
     *
     * @param data - ...
     * @param size - ...
     * @param esize - ...
     * @param compare - ...
     */
    static int issort( void *data, int size, int esize,
                       int ( *compare )( const void *key1,
                                         const void *key2 ) );
};

}

#endif // GENESIS_SORT_HXX
