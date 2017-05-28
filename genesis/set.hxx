/**
 * @file
 *
 * Definitions for an set.
 *
 * GENESIS
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#pragma once
#ifndef GENESIS_SET_HXX
#define GENESIS_SET_HXX

#include <genesis/list.hxx>

namespace genesis {
/**
 * Genesis Set Class.
 */
class set
{
public:
    /**
     * Initializes the set specified. This method must be called
     * before a set can be used with any other operation.
     *
     * @param set - Set to be initialized.
     * @param match - To determine if two members agree.
     * @param destroy - Provides means to free dynamically allocated data.
     */
    static void init( proto_list::set_list_linked *set,
                      int( *match ) ( const void *key1, const void *key2 ),
                      void( *destroy )( void *data ) );

    /**
     * Destroy the specified range as set.
     *
     * @param set - Remove set.
     */
    static void destroy( proto_list::set_list_linked *set );

    /**
     * Inserts a member in the set specified as set. The new member
     * contains a pointer to date, so the memory that is "data" as a
     * reference must remain valid as long as the member remains
     * in the set.
     *
     * @param set - Name set.
     * @param data - Definition of data.
     */
    static int insert( proto_list::set_list_linked *set, const void *data );

    /**
     *  Removes the member who match "data" in the set as "set".
     *
     * @param set - Name set.
     * @param data - Definition of data.
     */
    static int remove( proto_list::set_list_linked *set, void **data );

    /**
     * Build a set that is the union of set1 and set2.
     *
     * @param setu - Contains the union.
     * @param set1 - Name of the first set.
     * @param set2 - Name of the second set.
     */
    static int s_union( proto_list::set_list_linked *setu,
                        const proto_list::set_list_linked *set1,
                        const proto_list::set_list_linked *set2 );

    /**
     * Build a set that is the intersection of set1 and set2.
     *
     * @param seti - Contains the intersection.
     * @param set1 - Name of the first set.
     * @param set2 - Name of the second set.
     */
    static int intersection( proto_list::set_list_linked *seti,
                             const proto_list::set_list_linked *set1,
                             const proto_list::set_list_linked *set2 );

    /**
     * Build a set that is the difference of set1 and set2.
     *
     * @param setd - Contains the difference.
     * @param set1 - Name of the first set.
     * @param set2 - Name of the second set.
     */
    static int difference( proto_list::set_list_linked *setd,
                           const proto_list::set_list_linked *set1,
                           const proto_list::set_list_linked *set2 );

    /**
     * Determines whether the data specified by "data" coincides
     * with a member of the set specified as set.
     *
     * @param set - Name of the set.
     * @param data - Name of the data.
     */
    static int is_member( const proto_list::set_list_linked *set,
                          const void *data );

    /**
     * Determines whether the specified set of set1 is a
     * subset of the set specified as set2.
     *
     * @param set1 - Name of the first set.
     * @param set2 - Name of the second set.
     */
    static int is_subset( const proto_list::set_list_linked *set1,
                          const proto_list::set_list_linked *set2 );

    /**
     * Determines whether the specified set of set1 is equal
     * to all specified as set2.
     *
     * @param set1 - Name of the first set.
     * @param set2 - Name of the second set.
     */
    static int is_equal( const proto_list::set_list_linked *set1,
                         const proto_list::set_list_linked *set2 );
};

/// Set size.
#define GEN_SET_SIZE( set ) ( ( set )->size )

}

#endif // GENESIS_SET_HXX
