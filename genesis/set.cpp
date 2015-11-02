/**
 * @file
 *
 * Implementation for an set.
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

#include <genesis/set.hpp>

#include <cstdlib>
#include <cstring>

namespace genesis {

  void set::init( proto_list::set_list_linked* set, int( *match ) 
   ( const void* key1, const void *key2 ), void( *destroy )( void*data ) ) 
  {
    list::init( set, destroy );
    set->match = match;

    return;
  }

  void set::destroy( proto_list::set_list_linked* set )
  {
    list::destroy( set ); 
  }

  int set::insert( proto_list::set_list_linked* set, const void* data ) 
  {
    if( is_member( set, data ) ) {
      return 1;
    }

    return list::ins_next( set, GEN_LIST_TAIL( set ), data );
  }

  int set::remove( proto_list::set_list_linked* set, void** data ) 
  {
    proto_list::elements* ptr_member_ = 0;
    proto_list::elements* ptr_prev_ = 0;

    for( ptr_member_ = GEN_LIST_HEAD( set ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ ) ) {

      if( set->match( *data, GEN_LIST_DATA( ptr_member_ ) )) {
        break;
      }

      ptr_prev_ = ptr_member_;
    }

    if( ptr_member_ == 0 ) {
      return -1;
    }

    return list::rem_next( set, ptr_prev_, data );
  }

  int set::s_union( proto_list::set_list_linked* setu, 
   const proto_list::set_list_linked* set1, 
   const proto_list::set_list_linked* set2 ) 
  {
    proto_list::elements* ptr_member_;

    void* data;

    init( setu, set1->match, 0 );

    for( ptr_member_ = GEN_LIST_HEAD( set1 ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ ) ) {
      data = GEN_LIST_DATA( ptr_member_ );

      if( list::ins_next( setu, GEN_LIST_TAIL( setu ), data ) != 0 ) {
        list::destroy( setu );
        return -1;
      }
    }

    for( ptr_member_ = GEN_LIST_HEAD( set2 ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ ) ) {

      if( is_member( set1, GEN_LIST_DATA( ptr_member_ ) )) {
        continue;
      } else {
        data = GEN_LIST_DATA( ptr_member_ );

        if( list::ins_next( setu, GEN_LIST_TAIL( setu ), data ) != 0 ) {
          list::destroy( setu );
          return -1;
        }
      }
    }

    return 0;
  }

  int set::intersection( proto_list::set_list_linked* seti, 
   const proto_list::set_list_linked* set1, 
   const proto_list::set_list_linked* set2 ) 
  {
    proto_list::elements* ptr_member_ = 0;

    void* data;

    init( seti, set1->match, 0 );

    for( ptr_member_ = GEN_LIST_HEAD( set1 ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ ) ) {

      if( is_member( set2, GEN_LIST_DATA( ptr_member_ ) )) {
        data = GEN_LIST_DATA( ptr_member_ );

        if( list::ins_next( seti, GEN_LIST_TAIL( seti ), data ) != 0 ) {
          list::destroy( seti );
          return -1;
        }
      }
    }

    return 0;
  }

  int set::difference( proto_list::set_list_linked* setd, 
   const proto_list::set_list_linked* set1, 
   const proto_list::set_list_linked* set2 ) 
  {
    proto_list::elements* ptr_member_;

    void* data;

    init( setd, set1->match, 0 );

    for( ptr_member_ = GEN_LIST_HEAD( set1 ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ ) ) {

      if( !is_member( set2, GEN_LIST_DATA( ptr_member_ ) )) {
        data = GEN_LIST_DATA( ptr_member_ );

        if( list::ins_next( setd, GEN_LIST_TAIL( setd ), data ) != 0 ) {
          list::destroy( setd );
          return -1;
        }
      }
    }

    return 0;
  }

  int set::is_member( const proto_list::set_list_linked* set, 
   const void* data )
  {
    proto_list::elements* ptr_member_;

    for( ptr_member_ = GEN_LIST_HEAD( set ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ )) {

      if( set->match( data, GEN_LIST_DATA( ptr_member_ ) )) {
        return 1;
      }

    }

    return 0;
  }

  int set::is_subset( const proto_list::set_list_linked* set1, 
   const proto_list::set_list_linked* set2 ) 
  {
    proto_list::elements* ptr_member_;

    if( GEN_SET_SIZE( set1 ) > GEN_SET_SIZE( set2 ) ) {
      return 0;
    }

    for( ptr_member_ = GEN_LIST_HEAD( set1 ); ptr_member_ != 0; 
          ptr_member_ = GEN_LIST_NEXT( ptr_member_ )) {

      if( !is_member( set2, GEN_LIST_DATA( ptr_member_ ) )) {
        return 0;
      }
    }

    return 1;
  }

  int set::is_equal( const proto_list::set_list_linked* set1, 
   const proto_list::set_list_linked* set2 ) 
  {
    if( GEN_SET_SIZE( set1 ) != GEN_SET_SIZE( set2 ) ) {
      return 0;
    }

    return is_subset( set1, set2 );
  }

}
