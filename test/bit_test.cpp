/**
 * @file
 *
 * Tests for an bit class.
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

#include <genesis/bit.hpp>
#include <genesis/logger.hpp>

#include <cstdio>

int main( int argc, char* argv[] ) 
{
  unsigned char bits1[8];
  unsigned char bits2[8];
  unsigned char bits3[8];

  register int i = 0;

  // Perform some bit operations using 64-bit buffers.
  for( i = 0; i < 8; i++ ) {
    bits1[i] = 0x00;
    bits2[i] = 0x00;
    bits3[i] = 0x00;
  }

  GEN_MSG( "Bits Initially..." );

  fprintf( stdout, "bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], 
           bits1[6], bits1[7] );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  genesis::bit::set( bits1, 15, 1 );
  genesis::bit::set( bits1, 16, 1 );
  genesis::bit::set( bits1, 32, 1 );
  genesis::bit::set( bits1, 63, 1 );
  genesis::bit::set( bits2,  0, 1 );
  genesis::bit::set( bits2, 15, 1 );

  GEN_MSG( "After setting bits 15, 16, 32, 63 "
             "of bits1 and bits 00, 15 of bits2" );

  fprintf( stdout, "bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], 
           bits1[6], bits1[7] );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  fprintf( stdout, "Bit 63 of bits1 is %d\n", genesis::bit::get( bits1, 63 ) );
  fprintf( stdout, "Bit 62 of bits1 is %d\n", genesis::bit::get( bits1, 62 ) );
  fprintf( stdout, "Bit 00 of bits2 is %d\n", genesis::bit::get( bits2,  0 ) );
  fprintf( stdout, "Bit 01 of bits2 is %d\n", genesis::bit::get( bits2,  1 ) );

  genesis::bit::b_xor( bits1, bits2, bits3, 32 );

  GEN_MSG( "bits3 is bits1 XOR bits2 (32 bits)" );

  fprintf( stdout, "bits3: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits3[0], bits3[1], bits3[2], bits3[3], bits3[4], bits3[5], 
           bits3[6], bits3[7] );

  genesis::bit::b_xor( bits1, bits2, bits3, 64 );

  GEN_MSG( "bits3 is bits1 XOR bits2 (64 bits)" );

  fprintf( stdout, "bits3: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits3[0], bits3[1], bits3[2], bits3[3], bits3[4], bits3[5], 
           bits3[6], bits3[7] );

  genesis::bit::rot_left( bits1, 64, 1 );

  GEN_MSG( "After rotating bits1 left x 1 (64 bits)" );

  fprintf( stdout, "bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], 
           bits1[6], bits1[7] );

  genesis::bit::rot_left( bits2, 64, 1 );

  GEN_MSG( "After rotating bits2 left x 1 (64 bits)" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  genesis::bit::rot_left(bits2, 16, 7);

  GEN_MSG( "After rotating bits2 left x 7 (16 bits)" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  genesis::bit::rot_left( bits2, 8, 2 );

  GEN_MSG( "After rotating bits2 left x 2 (8 bits)" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  for( i = 0; i < 8; i++ ) {
    bits2[i] = 0x00;
  }

  genesis::bit::set( bits2,  0, 1 );
  genesis::bit::set( bits2,  3, 1 );
  genesis::bit::set( bits2,  8, 1 );
  genesis::bit::set( bits2, 27, 1 );

  GEN_MSG( "After clearing and setting bits 0, 3, 8, 27 of bits2" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  genesis::bit::rot_left( bits2, 11, 6 );
  
  GEN_MSG( "After rotating bits2 left x 6 (11 bits)" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  for( i = 0; i < 8; i++) {
    bits2[i] = 0x00;
  }

  genesis::bit::set( bits2,  0, 1 );
  genesis::bit::set( bits2,  3, 1 );
  genesis::bit::set( bits2,  8, 1 );
  genesis::bit::set( bits2, 27, 1 );

  GEN_MSG( "After clearing and setting bits 0, 3, 8, 27 of bits2" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  genesis::bit::rot_left( bits2, 28, 4 );

  GEN_MSG( "After rotating bits2 left x 4 (28 bits)" );

  fprintf( stdout, "bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
           bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], 
           bits2[6], bits2[7] );

  return 0;
}
