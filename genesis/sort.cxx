/**
 * @file
 *
 * Implementation for an sort.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_SORT_HXX
#include <genesis/sort.hxx>
#endif
#ifndef GENESIS_LOGGER_HXX
#include <genesis/logger.hxx>
#endif

#include <cstdlib>
#include <cstring>

namespace genesis {

int sort::ct( int *data, int size, int k )
{
    int *counts = 0;
    int *temp = 0;

    int i = 0;
    int j = 0;

    // Allocate storage for the counts.
    counts = new int[ k ];

    // Allocate storage for the sorted elements.
    temp = new int[ size ];

    // Initialize the counts.
    for ( i = 0; i < k; i++ ) {
        counts[i] = 0;
    }

    // Count the occurrences of each element.
    for ( j = 0; j < size; j++ ) {
        counts[data[j]] = counts[data[j]] + 1;
    }

    // Adjust each count to reflect the counts before it.
    for ( i = 1; i < k; i++ ) {
        counts[i] = counts[i] + counts[i - 1];
    }

    // Use the counts to position each element where it belongs.
    for ( j = size - 1; j >= 0; j-- ) {
        temp[counts[data[j]] - 1] = data[j];
        counts[data[j]] = counts[data[j]] - 1;
    }

    // Prepare to pass back the sorted data.
    std::memcpy( data, temp, size * sizeof( int ) );

    // Free the storage allocated for sorting.
    delete counts;
    delete temp;

    return 0;
}

int sort::issort( void *data, int size, int esize,
                  int( *compare ) ( const void *key1,
                                    const void *key2 ) )
{
    char *a = ( char * )data;
    void *key;

    int i = 0;
    int j = 0;

    // Allocate storage for the key element.
    key = new char[ esize ];

    // Repeatedly insert a key element among the sorted elements.
    for ( j = 1; j < size; j++ ) {

        std::memcpy( key, &a[j * esize], esize );
        i = j - 1;

        // Determine the position at which to insert the key element.
        while ( i >= 0 && compare( &a[i * esize], key ) > 0 ) {
            std::memcpy( &a[ (i + 1) * esize ], &a[ i * esize ], esize );
            i--;
        }

        std::memcpy( &a[ (i + 1) * esize ], key, esize );
    }

    // Free the storage allocated for sorting.
    std::free( key );

    return 0;
}

}
