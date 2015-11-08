/**
 * @file
 *
 * Definitions for an bit.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_BIT_HPP
#define GENESIS_BIT_HPP

namespace genesis {
  /**
   * Genesis Bit Class.
   */
  class bit {
  public:
    /**
     * Destructor.
     */
    ~bit() {};

    /**
     * Take the state of the bit at position pos in the buffer bits. 
     * The far left position in buffer is 0. The status returned 
     * is 1 or 0.
     *
     * @param bits - Name of the bit to get.
     * @param pos - Position of bit.
     */ 
    static int get( const unsigned char* bits, int pos );

    /**
     * Sets the state of the bit at position pos in the bit buffer 
     * to the value specified by state. The position will more left 
     * the buffer is 0. The state must be 1 or 0.
     *
     * @param bits - Name of the bit.
     * @param pos - Position of bit.
     * @param state - State of bit, default is 0.
     */
    static void set( unsigned char* bits, int pos, int state ); 

    /**
     * Compute the bitwise XOR of the two buffers bits1 and bits2, 
     * each containing bits size, and returns the result in bitsx. 
     * The bitwise XOR of two binary operands returns 0 in each 
     * position where the bits are different.
     *
     * @param bits1 - Name of the bit 1.
     * @param bits2 - Name of the bit 2.
     * @param bitsx - Name of the bit XOR.
     * @param size - Buffer size, (32,64).
     */
    static void b_xor( const unsigned char* bits1, const unsigned char* bits2,
                       unsigned char* bitsx, int size );

    /**
     * Rotates the bits of the buffer containing bits size to count 
     * the bits on the left. After the operation, the bit count found 
     * more to the left become the count bit more right in the buffer 
     * and all other bits change of position as appropriate.
     *
     * @param bits - Name of the bits.
     * @param size - Buffer size.
     * @param count - Number count, default 1.
     */
    static void rot_left( unsigned char* bits, int size, int count );
 
  private:
    /**
     * Private Constructor.
     */
     bit() {};
  };

}

#endif // GENESIS_BIT_HPP
