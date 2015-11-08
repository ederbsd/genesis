/**
 * @file
 *
 * Tests for an system class.
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

#include <genesis/system.hxx>
#include <genesis/logger.hxx>

// Test method copy file.
static bool copy_file_test( void )
{
  GEN_MSG( "Coping files.\n" );

  genesis::system::copy_file( "genesis_test.cpp", "A.txt" );

  GEN_MSG( "\nEnd: Coping files.\n" );

  return true;
}

// Test method rename.
static bool rename_test( void )
{
  GEN_MSG( "Rename files.\n" );

  genesis::system::rename( "A.txt", "BACALHO.txt" );

  GEN_MSG( "\nEnd: Rename.\n" );

  return true;
}

// Test method remove.
static bool remove_test( void )
{
  GEN_MSG( "Remove file" );

  genesis::system::remove( "BACALHO.txt" );

  GEN_MSG( "\nEnd: Remove files.\n" );

  return true;
}

// Test method list files.
static bool list_files_test( void )
{
  GEN_MSG( "Listing directory.\n" );

  static char** files = 0;

  GEN_TRUE_OR_ERROR( files = genesis::system::list_files( "." ),
                      "Error: Listing directory." );

  GEN_MSG( "\nEnd: Listing directory.\n" );

  return true;
}

int main( int argc, char* argv[] ) 
{
  GEN_TRUE_OR_ERROR( copy_file_test() != false,
                      "Error function: copy_file_test()" );

  GEN_TRUE_OR_ERROR( rename_test() != false,
                     "Error function: rename_test()" );

  GEN_TRUE_OR_ERROR( remove_test() != false,
                     "Error function: remove_test()" );

  GEN_TRUE_OR_ERROR( list_files_test() != false,
                      "Error function: list_files_test()" );

  genesis::system::exec_cmd( "ls" );

  return 0;
}
