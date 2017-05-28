/**
 * @file
 *
 * Implementations for an set_cover.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_SET_COVER_HXX
#include <genesis/set_cover.hxx>
#endif

namespace genesis {

int set_cover::cover( proto_list::set_list_linked *members,
                      proto_list::set_list_linked *subsets,
                      proto_list::set_list_linked *covering )
{
    members = new proto_list::set_list_linked;
    subsets = new proto_list::set_list_linked;

    proto_list::set_list_linked intersection;
    proto_list::cover_key *ptr_subset;

    proto_list::elements *ptr_member = 0;
    proto_list::elements *ptr_max_member = 0;

    void *data;
    int max_size = 0;

    // Initialize the covering.
    set::init( covering, subsets->match, 0 );

    // Continue while there are noncovered members and candidate subsets.
    while ( GEN_SET_SIZE( members ) > 0 && GEN_SET_SIZE( subsets ) > 0 ) {

        // Find the subset that covers the most members.
        max_size = 0;

        for ( ptr_member = GEN_LIST_HEAD( subsets ); ptr_member != 0;
                ptr_member = GEN_LIST_NEXT( ptr_member ) ) {

            if ( set::intersection( &intersection, &(( proto_list::cover_key * )
                                                     GEN_LIST_DATA( ptr_member ))->set, members ) != 0 ) {
                return -1;
            }

            if ( GEN_SET_SIZE( &intersection ) > max_size ) {
                ptr_max_member = ptr_member;
                max_size = GEN_SET_SIZE( &intersection );
            }

            set::destroy( &intersection );
        }

        // A covering is not possible if there was no intersection.
        if ( max_size == 0 ) {
            return 1;
        }

        // Insert the selected subset into the covering.
        ptr_subset = ( proto_list::cover_key * )GEN_LIST_DATA( ptr_max_member );

        if ( set::insert( covering, ptr_subset ) != 0 ) {
            return -1;
        }

        // Remove each covered member from the set of noncovered members.
        for ( ptr_member = GEN_LIST_HEAD( &(( proto_list::cover_key * )
                                            GEN_LIST_DATA( ptr_max_member ))->set); ptr_member != 0;
                ptr_member = GEN_LIST_NEXT( ptr_member ) ) {

            data = GEN_LIST_DATA( ptr_member );

            if ( set::remove( members, ( void ** )&data ) == 0 &&
                    members->destroy != 0 ) {
                members->destroy( data );
            }

        }

        // Remove the subset from the set of candidate subsets.
        if ( set::remove( subsets, ( void ** )&ptr_subset ) != 0 ) {
            return -1;
        }
    }

    // No covering is possible if there are still noncovered members.
    if ( GEN_SET_SIZE( members ) > 0 ) {
        return -1;
    }

    return 0;

}

}
