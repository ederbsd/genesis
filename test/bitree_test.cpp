/**
 * @file
 *
 * Tests for an bitree class.
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

#include <genesis/bitree.hpp>
#include <genesis/logger.hpp>

#include <cstdio>

//using namespace genesis;

static void print_preorder( const genesis::proto_bitree::node_avl* node )
{
  // Display the binary tree rooted at the specified node in preorder.
  if( !GEN_BITREE_NODE_IS_EOB( node ) ) {
    fprintf( stdout, "Node=%03d\n", *( int * )GEN_BITREE_NODE_DATA( node ) );

    if( !GEN_BITREE_NODE_IS_EOB( GEN_BITREE_NODE_LEFT( node ) ) ) {
      print_preorder( GEN_BITREE_NODE_LEFT( node ) );
    }

    if( !GEN_BITREE_NODE_IS_EOB( GEN_BITREE_NODE_RIGHT( node ) ) ) {
      print_preorder( GEN_BITREE_NODE_RIGHT( node ) );
    }
  }
  return;
}

static void print_inorder( const genesis::proto_bitree::node_avl* node ) 
{
  // Display the binary tree rooted at the specified node in inorder.
  if( !GEN_BITREE_NODE_IS_EOB( node ) ) {

    if( !GEN_BITREE_NODE_IS_EOB( GEN_BITREE_NODE_LEFT( node ) ) ) {
      print_inorder(GEN_BITREE_NODE_LEFT( node ) );
    }

    fprintf( stdout, "Node=%03d\n", *( int * )GEN_BITREE_NODE_DATA( node ) );

    if( !GEN_BITREE_NODE_IS_EOB( GEN_BITREE_NODE_RIGHT( node ) ) ) {
      print_inorder( GEN_BITREE_NODE_RIGHT( node ) );
    }
  }
  return;
}

static void print_postorder( const genesis::proto_bitree::node_avl* node )
{
  // Display the binary tree rooted at the specified node in postorder.
  if( !GEN_BITREE_NODE_IS_EOB( node ) ) {

    if( !GEN_BITREE_NODE_IS_EOB( GEN_BITREE_NODE_LEFT( node ) ) ) {
      print_postorder( GEN_BITREE_NODE_LEFT( node ) );
    }

    if( !GEN_BITREE_NODE_IS_EOB( GEN_BITREE_NODE_RIGHT( node ) ) ) {
      print_postorder(GEN_BITREE_NODE_RIGHT(node));
    }

    fprintf( stdout, "Node=%03d\n", *( int * )GEN_BITREE_NODE_DATA( node ) );
  }
  return;
}

static int insert_int( genesis::proto_bitree::tree* tree, int i ) 
{
  genesis::bitree bitree_;

  genesis::proto_bitree::node_avl* node = 0;
  genesis::proto_bitree::node_avl* prev = 0;

  int* data = 0;
  int direction = 0;

  // Insert i assuming a binary tree organized as a binary search tree.
  node = tree->root;
  direction = 0;

  while( !GEN_BITREE_NODE_IS_EOB( node ) ) {
    prev = node;

    if( i == *( int * )GEN_BITREE_NODE_DATA( node ) ) {
      return -1;

    } else if( i < *( int * )GEN_BITREE_NODE_DATA( node ) ) {

      node = GEN_BITREE_NODE_LEFT( node );
      direction = 1;

    } else {

      node = GEN_BITREE_NODE_RIGHT( node );
      direction = 2;
    }
  }

  data = new int;

  if( data == 0 ) {
    return -1;
  }

  *data = i;

  if( direction == 0 ) {
    return bitree_.ins_left( tree, 0, data );
  }

  if( direction == 1 ) {
    return bitree_.ins_left( tree, prev, data );
  }

  if( direction == 2 ) {
    return bitree_.ins_right( tree, prev, data );
  }

  return -1;
}


static genesis::proto_bitree::node_avl* search_int( 
 genesis::proto_bitree::tree* tree, int i ) 
{
  genesis::proto_bitree::node_avl* node;

  // Look up i assuming a binary tree organized as a binary search tree.
  node = GEN_BITREE_ROOT( tree );

  while( !GEN_BITREE_NODE_IS_EOB( node ) ) {

    if( i == *( int * )GEN_BITREE_NODE_DATA( node ) ) {
      return node;
    } else if( i < *( int * )GEN_BITREE_NODE_DATA( node ) ) {
      node = GEN_BITREE_NODE_LEFT( node );
    } else {
      node = GEN_BITREE_NODE_RIGHT( node );
    }
  }

  return 0;
}

int main( int argc, char* argv[] ) 
{
  genesis::bitree bitree_;

  genesis::proto_bitree::tree tree;
  genesis::proto_bitree::node_avl* node;

  register int i = 0;

  // Initialize the binary tree.
  bitree_.init( &tree, std::free );

  // Perform some binary tree operations.
  GEN_MSG( "Inserting some nodes" );

  if( insert_int( &tree, 20 ) != 0 ) {
   return 1;
  }

  if( insert_int( &tree, 10 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 30 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 15 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 25 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 70 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 80 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 23 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 26 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 5 ) != 0 ) {
    return 1;
  }

  fprintf( stdout, "Tree size is %d\n", GEN_BITREE_SIZE( &tree ) );

  GEN_MSG( "( Preorder traversal )" );

  print_preorder( GEN_BITREE_ROOT( &tree ) );

  i = 30;

  if(( node = search_int( &tree, i )) == 0 ) {
    GEN_WARN( "Could not find..." );
    fprintf( stdout, " %03d\n", i );
  } else {
    fprintf( stdout, "Found %03d...Removing the left tree below it\n", i );
    bitree_.rem_left( &tree, node );
    fprintf( stdout, "Tree size is %d\n", GEN_BITREE_SIZE( &tree ) );
    fprintf( stdout, "(Preorder traversal)\n" );
    print_preorder( GEN_BITREE_ROOT( &tree ) );
  }

  i = 99;

  if(( node = search_int( &tree, i )) == NULL ) {
    fprintf( stdout, "Could not find %03d\n", i );
  } else {
    fprintf( stdout, "Found %03d...Removing the right tree below it\n", i );
    bitree_.rem_right( &tree, node );
    fprintf( stdout, "Tree size is %d\n", GEN_BITREE_SIZE( &tree ) );
    fprintf( stdout, "(Preorder traversal)\n" );
    print_preorder( GEN_BITREE_ROOT( &tree ) );
  }

  i = 20;

  if(( node = search_int( &tree, i ) ) == NULL ) {
    fprintf( stdout, "Could not find %03d\n", i );
  } else {
    fprintf( stdout, "Found %03d...Removing the right tree below it\n", i );
    bitree_.rem_right( &tree, node );
    fprintf( stdout, "Tree size is %d\n", GEN_BITREE_SIZE( &tree ) );
    fprintf( stdout, "(Preorder traversal)\n");
    print_preorder( GEN_BITREE_ROOT( &tree ) );
  }

  i = GEN_BITREE_NODE_IS_LEAF( GEN_BITREE_ROOT( &tree ) );
  fprintf( stdout, "Testing bitree_is_leaf...Value=%d (0=OK)\n", i );

  i = GEN_BITREE_NODE_IS_LEAF( GEN_BITREE_NODE_LEFT(( \
	GEN_BITREE_ROOT( &tree ) )) );
  fprintf( stdout, "Testing bitree_is_leaf...Value=%d (0=OK)\n", i );

  i = GEN_BITREE_NODE_IS_LEAF( GEN_BITREE_NODE_LEFT( \
	GEN_BITREE_NODE_LEFT(( GEN_BITREE_ROOT( &tree ) )) ));
  fprintf( stdout, "Testing bitree_is_leaf...Value=%d (1=OK)\n", i );

  i = GEN_BITREE_NODE_IS_LEAF( GEN_BITREE_NODE_RIGHT( \
	GEN_BITREE_NODE_LEFT(( GEN_BITREE_ROOT( &tree ) )) ));
  fprintf( stdout, "Testing bitree_is_leaf...Value=%d (1=OK)\n", i );

  fprintf( stdout, "Inserting some nodes\n" );

  if( insert_int( &tree, 55 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 44 ) != 0 ) {
    return 1;
  }

  if( insert_int( &tree, 77 ) != 0 ) {
   return 1;
  }

  if( insert_int( &tree, 11 ) != 0 ) {
    return 1;
  }

  fprintf( stdout, "Tree size is %d\n",  GEN_BITREE_SIZE( &tree ) );

  GEN_MSG( "(Preorder traversal)" );
  print_preorder( GEN_BITREE_ROOT( &tree ) );

  GEN_MSG( "(Inorder traversal)" );
  print_inorder( GEN_BITREE_ROOT( &tree ) );

  GEN_MSG( "(Postorder traversal)" );
  print_postorder( GEN_BITREE_ROOT( &tree ) );

  // Destroy the binary tree.
  GEN_MSG( "Destroying the tree" );
  bitree_.destroy( &tree );

  return 0;
}
