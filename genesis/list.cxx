/**
 * @file
 *
 * Implementation for an list.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/list.hxx>
#include <genesis/logger.hxx>

#include <cstring>

namespace genesis {

  void list::init( proto_list::linked* list, 
                   void( *destroy ) ( void* data ) ) 
  {
    // Initialize the list.
    list->size = 0;
    list->destroy = destroy;
    list->head = 0;
    list->tail = 0;

    GEN_ASSERT( list->size == 0 );
    GEN_ASSERT( list->head == 0 );
    GEN_ASSERT( list->tail == 0 );

    return;
  }

  void list::destroy( proto_list::linked* list )
  {
    void* data;

    // Remove each element.
    while( GEN_LIST_SIZE( list ) > 0 ) {

      if( rem_next( list, 0, ( void** )&data ) == 0 
           && list->destroy != 0 ) {

        // Call a user-defined function to free,
        // dynamically allocated data.
        list->destroy( data );
      }
    }

    // No operation are allowed now, but clear
    // the structure as a precaution!
    std::memset( list, 0, sizeof( proto_list::linked ) );
    return;
  }

  int list::ins_next( proto_list::linked* list, 
                      proto_list::elements* element, 
                      const void* data ) 
  {
    proto_list::elements* new_element = new proto_list::elements;

    if( new_element == 0 ) {
      return -1;
    }
    
    // Insert the element into the list.
    new_element->data = ( void* )data;

    if( element == 0 ) {
     
      // Handle insertion at the head of the list. 
      if( GEN_LIST_SIZE( list ) == 0 ) {
        list->tail = new_element;
      }

      new_element->next = list->head;
      list->head = new_element;

    } else {

      // Handle insertion somewhere other than at the head.      
      if( element->next == 0 ) {
        list->tail = new_element;
      }

      new_element->next = element->next;
      element->next = new_element;
    }

    // Adjust the size of the list to account 
    // for the inserted element.
    list->size++;
    return 0;
  }

  int list::rem_next( proto_list::linked* list, 
                      proto_list::elements* element, 
                      void** data ) 
  {
    proto_list::elements* old_element = new proto_list::elements;

    // Do not allow removal from an empty list.
    if( GEN_LIST_SIZE( list ) == 0 ) {
      return -1;
    }

    // Remove the element from the list.
    if( element == 0 ) {

      //  Handle removal from the head of the list.
      *data = list->head->data;
      old_element = list->head;
      list->head = list->head->next;

      if( GEN_LIST_SIZE( list ) == 1 ) {
        list->tail = 0;
      }
    } else {

      // Handle removal from somewhere other than the head.
      if( element->next == 0 ) {
        return -1;
      }

      *data = element->next->data;
      old_element = element->next;
      element->next = element->next->next;

      if( element->next == 0 ) {
        list->tail = element;
      }
  }

  // Free the storage allocated by the abstract data type.
  delete old_element;

  list->size--;

  return 0;
  }

}
