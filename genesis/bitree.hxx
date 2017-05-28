/**
 * @file
 *
 * Definitions for an bitree.
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
#ifndef GENESIS_BITREE_HXX
#define GENESIS_BITREE_HXX

#include <genesis/proto_types.hxx>

namespace genesis {
/**
 * Genesis Bitree Class.
 */
class bitree
{
public:
    /**
     * Constructor.
     */
    bitree();

    /**
     * Destructor.
     */
    virtual ~bitree();

    /**
     * Initialize bitree.
     *
     * @param tree - Object tree.
     * @param destroy - Destroy object.
     * @param data - The data.
     */
    void init( proto_bitree::tree *tree,
               void( *destroy ) ( void *data ) );

    /**
     * Destroy tree.
     *
     * @param tree - Object tree destroy.
     */
    void destroy( proto_bitree::tree *tree );

    /**
     * Nodes in left.
     *
     * @param tree - Object tree.
     * @param node - Object node.
     * @param data - Object data.
     * @return Return integer nodes.
     */
    int ins_left( proto_bitree::tree *tree, proto_bitree::node_avl *node,
                  const void *data );

    /**
     * Nodes in right.
     *
     * @param tree - Object tree.
     * @param node - Object node.
     * @param data - Object data.
     * @return Return integer nodes.
     */
    int ins_right( proto_bitree::tree *tree,
                   proto_bitree::node_avl *node, const void *data );

    /**
     * Remove nodes left.
     *
     * @param tree - Object tree.
     * @param node - Object node.
     */
    void rem_left( proto_bitree::tree *tree, proto_bitree::node_avl *node );

    /**
     * Remove nodes right.
     *
     * @param tree - Object tree.
     * @param node - Object node.
     */
    void rem_right( proto_bitree::tree *tree, proto_bitree::node_avl *node );

    /**
     * Merge between nodes.
     *
     * @param left  - Object tree.
     * @param right - Object tree.
     * @param data  - The data objects.
     */
    int merge( proto_bitree::tree *merge, proto_bitree::tree *left,
               proto_bitree::tree *right, const void *data );
};

/*
class transfer : public bitree {
public:
  virtual ~transfer() {};

  int send_comp( int s, const unsigned char* data, int size, int flags ) {
    return 0;
  }

  int recv_comp( int s, unsigned char** data, int* size, int flags ) {
    return 0;
  }
};*/

#define GEN_BITREE_SIZE( tree ) (( tree )->size )
#define GEN_BITREE_ROOT( tree ) (( tree )->root )
#define GEN_BITREE_NODE_IS_EOB( node ) (( node ) == 0 )
#define GEN_BITREE_NODE_IS_LEAF( node ) (( node )->left == 0 && ( node )->right == 0 )
#define GEN_BITREE_NODE_DATA( node ) (( node )->data )
#define GEN_BITREE_NODE_LEFT( node ) (( node )->left )
#define GEN_BITREE_NODE_RIGHT( node ) (( node )->right )

}

#endif // GENESIS_BITREE_HXX
