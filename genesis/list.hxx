/**
 * @file
 *
 * Definitions for an list.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$                                                                        
 */

#ifndef GENESIS_LIST_HPP
#define GENESIS_LIST_HPP

#include <genesis/proto_types.hxx>

namespace genesis {
  /**
   * Genesis List Class.
   */
  class list {
  public:
    /**
     * Start the list enchained. This method must be called 
     * before enchained to a list that can be used in any operation.
     *
     * @param list - Name of the list.
     * @param destroy - Free memory or name of the data.
     */
    static void init( proto_list::linked* list, 
                      void( *destroy ) ( void* data ) );

    /**
     * Destroy the specified list with enchained.
     *
     * @param list - Name of the list.
     */
    static void destroy( proto_list::linked* list );

    /**	
     * Inserts an element after "elements" list enchained.
     *
     * @param list - Name of the list.
     * @param element - Name of the elements.
     * @param data - Name of the data.
     */
    static int ins_next( proto_list::linked* list, 
                         proto_list::elements* element, 
                         const void* data );

    /**
     * Remove an element after element list enchained
     *
     * @param list - Name of the list.
     * @param element - Name of the elements.
     * @param data - Name of the data.
     */
    static int rem_next( proto_list::linked* list, 
                         proto_list::elements* element, 
                         void** data );
  };

/** 
 * Contains the number of elements in the list.
 *
 * @return Number of elements in the list.
 */
#define GEN_LIST_SIZE( list ) (( list )->size )

/**
 * Elements in the head of the list.
 *
 * @return Elements in the "head" of the list.
 */
#define GEN_LIST_HEAD( list ) (( list )->head )

/** 
 * Elements of the list in tail.
 *
 * @return elements in the "tail" of the list.
 */
#define GEN_LIST_TAIL( list ) (( list )->tail )

/** 
 * Determines whether the specified element as "elements"
 * of the list is the head.
 *
 * @return 1 if the element is the "head" of the list, or 0.
 */
#define GEN_LIST_IS_HEAD( list, element ) (( element ) == ( list )->head ? 1 : 0 )

/**
 * Determines whether the specified element as the "elements" 
 * in the tail of a list.
 *
 * @return 1 if the element is the "tail" of the list, or 0.
 */
#define GEN_LIST_IS_TAIL( element ) (( element )->next == 0 ? 1 : 0 )

/**
 * Evaluates the data stored in the element of a list of 
 * specified "elements" enchained.
 *
 * @return The data that are stored in the element.
 */
#define GEN_LIST_DATA( element ) (( element )->data )

/**
 * Evaluate the element of a list enchained, following the 
 * element specified by "elements".
 *
 * @return Element that follows the specified element.
 */
#define GEN_LIST_NEXT( element ) (( element )->next )

}

#endif // GENESIS_LIST_HPP
