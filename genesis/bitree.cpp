/**
 * @file
 *
 * Implementations for an bitree.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009-2015 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/bitree.hpp>
#include <genesis/logger.hpp>

#include <cstring>

namespace genesis {

  bitree::bitree() 
  {
    // Empty contructor.
  }

  bitree::~bitree() 
  {
    // Empty destructor.
  }
  
  void bitree::init( proto_bitree::tree* tree, void( *destroy )( void* data ) ) 
  {
    // Initialize the binary tree.
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = 0;

    GEN_ASSERT( tree->size == 0 );
    GEN_ASSERT( tree->root == 0 );

    return;
  }

  void bitree::destroy( proto_bitree::tree* tree ) 
  {
    // Remove all the nodes from the tree. 
    rem_left( tree, 0 );

    // No operations are allowed now, but clear the structure as a precaution.
    delete tree;
    //free( std::memset( tree, 0, sizeof( tree ) ));
    return;
  }

  int bitree::ins_left( proto_bitree::tree* tree, 
   proto_bitree::node_avl* node, const void* data ) 
  {
    proto_bitree::node_avl *new_node, **position;

    // Determine where to insert the node.
    if( node == 0 ) {
      // Allow insertion at the root only in an empty tree.
      if( GEN_BITREE_SIZE( tree ) > 0 ) {
        return -1;
      }

      position = &tree->root;
    } else {
      // Normally allow insertion only at the end of a branch.
      if( GEN_BITREE_NODE_LEFT( node ) != 0 ) {
        return -1;
      }

      position = &node->left;
    }

    // Allocate storage for the node.
    new_node = new proto_bitree::node_avl;

    // Insert the node into the tree.
    new_node->data = ( void * )data;
    new_node->left = 0;
    new_node->right = 0;
    *position = new_node;

    // Adjust the size of the tree to account for the inserted node.
    tree->size++;

    return 0;
  }

  int bitree::ins_right( proto_bitree::tree* tree, 
   proto_bitree::node_avl* node, const void* data )
  {
    proto_bitree::node_avl* new_node, **position;

    // Determine where to insert the node.
    if( node == 0 ) {
      // Allow insertion at the root only in an empty tree.
      if( GEN_BITREE_SIZE( tree ) > 0 ) {
        return -1;
      }

      position = &tree->root;
    } else {
      // Normally allow insertion only at the end of a branch
      if( GEN_BITREE_NODE_RIGHT( node ) != 0 ) {
        return -1;
      }

      position = &node->right;
    }

    // Allocate storage for the node.
    new_node = new proto_bitree::node_avl;

    // Insert the node into the tree.
    new_node->data = ( void * )data;
    new_node->left = 0;
    new_node->right = 0;
    *position = new_node;

    //  Adjust the size of the tree to account for the inserted node.
    tree->size++;
    return 0;
  }

  void bitree::rem_left( proto_bitree::tree* tree, 
   proto_bitree::node_avl* node ) 
  {
    proto_bitree::node_avl** position;

    // Do not allow removal from an empty tree.
    if( GEN_BITREE_SIZE( tree ) == 0 ) {
      return;
    }

    // Determine where to remove nodes.
    if( node == 0 ) {
      position = &tree->root;
    } else {
      position = &node->left;
    }

    // Remove the nodes.
    if( *position != 0 ) {
      rem_left( tree, *position );
      rem_right( tree, *position );

      if( tree->destroy != 0 ) {
        // Call a user-defined function to free dynamically allocated data.
        tree->destroy( ( *position )->data );
      }

      delete *position;
      *position = 0;

      // Adjust the size of the tree to account for the removed node.
      tree->size--;
    }

    return;
  }

  void bitree::rem_right( proto_bitree::tree* tree, 
   proto_bitree::node_avl* node )
  {
    proto_bitree::node_avl** position = 0;

    // Do not allow removal from an empty tree.
    if( GEN_BITREE_SIZE( tree ) == 0 ) {
      return;
    }

    // Determine where to remove nodes.
    if( node == 0 ) {
      position = &tree->root;
    } else {
      position = &node->right;
    }

    // Remove the nodes.
    if( *position != 0 ) {
      rem_left( tree, *position );
      rem_right( tree, *position );

      if( tree->destroy != 0 ) {
        // Call a user defined method to free dynamically allocated data.
        tree->destroy(( *position )->data );
      }

      delete *position;
      *position = 0;

      // Adjust the size of the tree to account for the removed node.
      tree->size--;
    }

    return;
  }

  int bitree::merge( proto_bitree::tree* merge, proto_bitree::tree* left, 
   proto_bitree::tree* right, const void* data ) 
  {
    // Initialize the merged tree.
    init( merge, left->destroy );

    // Insert the data for the root node of the merged tree.
    if( ins_left( merge, 0, data ) != 0 ) {
      destroy( merge );
      return -1;
    }

    // Merge the two binary trees into a single binary tree.
    GEN_BITREE_ROOT( merge )->left = GEN_BITREE_ROOT( left );
    GEN_BITREE_ROOT( merge )->right = GEN_BITREE_ROOT( right );

    // Adjust the size of the new binary tree. 
    merge->size = merge->size + 
                  GEN_BITREE_SIZE( left ) + GEN_BITREE_SIZE( right );

    // Do not let the original trees access the merged nodes.
    left->root = 0;
    left->size = 0;
    right->root = 0;
    right->size = 0;

    return 0;
  }

}
