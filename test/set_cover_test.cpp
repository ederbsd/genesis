/**
 * @file
 *
 * Tests for an set_cover class.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/set_cover.hpp>
#include <genesis/logger.hpp>

// Define the number of members in the skills and player sets.
static const int SKILLS_COUNT = 12;
static const int PLAYER_COUNT = 8;

static void print_skills( const genesis::proto_list::set_list_linked* skills ) 
{
  genesis::proto_list::elements* ptr_member;

  char* data = 0;

  int size = 0;
  int i = 0;

  // Display the set of skills.
  fprintf( stdout, "Set size is %d\n", size = GEN_SET_SIZE( skills ) );

  i = 0;
  ptr_member = GEN_LIST_HEAD( skills );

  while( i < size ) {
    data = ( char* )GEN_LIST_DATA( ptr_member );

    fprintf( stdout, "Skills[%03d]=%c\n", i, *data );
    ptr_member = GEN_LIST_NEXT( ptr_member );
    i++;
  }

  return;
}

static void print_players( const genesis::proto_list::set_list_linked* players ) 
{
  genesis::proto_list::elements* ptr_member = 
   new genesis::proto_list::elements;

  // Display the skills for each player in the set of players.
  for( ptr_member = GEN_LIST_HEAD( players ); ptr_member != 0; 
       ptr_member = GEN_LIST_NEXT( ptr_member ) ) {

     fprintf( stdout, "Player %c\n", *( char* )(( 
              genesis::proto_list::cover_key* )
              GEN_LIST_DATA( ptr_member ))->key );

     print_skills( &(( genesis::proto_list::cover_key* )
                   GEN_LIST_DATA( ptr_member ))->set );
  }

  return;
}

int match_key( const void* key1, const void* key2 ) 
{
  // Determine whether two keyed sets match.
  if( *( char* ) (( const genesis::proto_list::cover_key* ) key1 )->key == 
      *( char* ) (( const genesis::proto_list::cover_key* ) key2)->key ) {
    return 1;
  } else {
    return 0;
  }

}

int match_skill( const void* skill1, const void* skill2 ) 
{
  // Determine whether two skills match.
  if( *( const char* ) skill1 == *( const char* )skill2 ) {
    return 1;
  } else {
    return 0;
  }
}

int main( int argc, char* argv[] ) 
{
  genesis::proto_list::set_list_linked skills;
  genesis::proto_list::set_list_linked players;
  genesis::proto_list::set_list_linked covering;

  char skills_array[ SKILLS_COUNT ];
  char subids_array[ PLAYER_COUNT ];

  genesis::proto_list::cover_key player_array[ PLAYER_COUNT ];

  register int retval = 0;
  register int i = 0;

  // Create the set of skills.
  GEN_MSG( "Creating the set of skills" );

  genesis::set::init( &skills, match_skill, NULL );

  skills_array[0] = 'a';
  skills_array[1] = 'b';
  skills_array[2] = 'c';
  skills_array[3] = 'd';
  skills_array[4] = 'e';
  skills_array[5] = 'f';
  skills_array[6] = 'g';
  skills_array[7] = 'h';
  skills_array[8] = 'i';
  skills_array[9] = 'j';
  skills_array[10] = 'k';
  skills_array[11] = 'l';

  for( i = 0; i < SKILLS_COUNT; i++ ) {
   if( genesis::set::insert( &skills, &skills_array[i] ) != 0 ) {
     return 1;
   }
  }

  print_skills( &skills );

  // Create some player sets with certain skills.
  GEN_MSG( "Creating the player subsets" );

  genesis::set::init( &players, match_key, NULL );

  subids_array[0] = '1';
  subids_array[1] = '2';
  subids_array[2] = '3';
  subids_array[3] = '4';
  subids_array[4] = '5';
  subids_array[5] = '6';
  subids_array[6] = '7';
  subids_array[7] = '8';

  for( i = 0; i < PLAYER_COUNT; i++ ) {

    player_array[i].key = &subids_array[i];
    genesis::set::init( &player_array[i].set, match_skill, NULL );

    switch( i ) {

    case 0:
      if( genesis::set::insert( &player_array[i].set, &skills_array[0] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[1]) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[2]) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[3] ) != 0 ) {
        return 1;
      }

    break;

    case 1:

      if( genesis::set::insert( &player_array[i].set, &skills_array[4] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[5] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[6] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[7] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[8] ) != 0 ) {
        return 1;
      }

    break;

    case 2:

      if( genesis::set::insert( &player_array[i].set, &skills_array[9] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[10] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[11] ) != 0 ) {
        return 1;
      }

    break;

    case 3:

      if( genesis::set::insert( &player_array[i].set, &skills_array[0] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[4] ) != 0 ) {
        return 1;
      }

    break;

    case 4:

      if( genesis::set::insert( &player_array[i].set, &skills_array[1] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[5] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[6] ) != 0 ) {
        return 1;
      }

    break;

      case 5:

      if( genesis::set::insert( &player_array[i].set, &skills_array[2] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[3] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[6] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[7] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[10] ) != 0 ) {
        return 1;
      }

      if( genesis::set::insert( &player_array[i].set, &skills_array[11] ) != 0 ) {
        return 1;
      }

    break;

    default:

      if( genesis::set::insert( &player_array[i].set, &skills_array[11] ) != 0 ) {
        return 1;
      }
    }

    if( genesis::set::insert( &players, &player_array[i]) != 0 ) {
      return 1;
    }

  }

  print_players( &players );

  // Compute the set covering.
  GEN_MSG( "Generating the cover" );

  if(( retval = genesis::set_cover::cover( &skills, &players, &covering )) != 0 ) {
    return 1;
  }

  if( retval == 1 ) {
    GEN_WARN( "The set could not be covered" );
  } else {
    print_players( &covering );
  }

  // Destroy the sets.
  GEN_MSG( "Destroying the sets" );

  for( i = 0; i < PLAYER_COUNT; i++ ) {
    genesis::set::destroy( &player_array[i].set );
  }

  genesis::set::destroy( &skills );

  return 0;
}
