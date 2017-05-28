/**
 * @file
 *
 * Definitions for an set_cover.
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
#ifndef GENESIS_SET_COVER_HXX
#define GENESIS_SET_COVER_HXX

#include <genesis/set.hxx>

namespace genesis {
/**
 * Genesis Set Cover Class.
 */
class set_cover
{
public:
    /**
     * Coverage of set.
     *
     * @param members - Name of the member or members.
     * @param subsets - Name of the subsets.
     * @param covering - Name of the covering.
     */
    static int cover( proto_list::set_list_linked *members,
                      proto_list::set_list_linked *subsets,
                      proto_list::set_list_linked *covering );

};

}

#endif // GENESIS_SET_COVER_HXX
