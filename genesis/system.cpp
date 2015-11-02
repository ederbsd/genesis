/**
 * @file
 *
 * Implementation for an system.
 *
 * GENESIS - - Library of general purpose classes
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

#include <genesis/system.hpp>
#include <genesis/logger.hpp>

#include <cstdlib>
#include <cstring>
#include <fstream>

extern "C" {
#include <dirent.h>
}

namespace genesis {

  char** system::list_files( const std::string path )
  {
    GEN_ABORT_TRUE_OR_ERROR( path.empty() == 0, "Invalid! Path empty." );

    DIR* dir_ = opendir( path.c_str() );

    struct dirent* dp; // Returned from read dir.
    size_t filecount = 0; // Number of entries in directory.
    register int i = 0;

    char **files = 0;

    if( dir_ == 0 ) {
      return 0;
    }

    // Count number of files and subdirectories.
    while(( dp = readdir( dir_ ) ) != 0 ) {
      filecount++;
    }

    // Allocate space for the result.
    files = new char*[ ( char )filecount ];

    if( files == 0 ) {
      return 0;
    }

    // Collect all filenames.
    rewinddir( dir_ );
    while(( dp = readdir( dir_ ) ) != 0 ) {
      files[i] = strdup( dp->d_name );
        
      if( files[i] == 0 ) {
        // Memory allocation failure; free what's been allocated
        // so far and return 0.
        GEN_ASSERT( i > 0 );
        while( i > 0 ) {
          std::free( files[--i] );
        }
        std::free( files );
        return 0;
      }
      printf( "%d: %s\n", i, dp->d_name );
      i++;
    }
 
    ( void )closedir( dir_ );
    return files;
  }

  bool system::copy_file( const std::string& from, const std::string& to )
  {
    GEN_ABORT_TRUE_OR_ERROR( from.empty() == 0, "Invalid! From empty." );
    GEN_ABORT_TRUE_OR_ERROR( to.empty() == 0, "Invalid! To empty." );

    std::ifstream in( from.c_str(), std::ios::binary );
    std::ofstream out( to.c_str(), std::ios::binary );
    out << in.rdbuf();

    return true;
  }

  int system::exec_cmd( const std::string cmd )
  {
    GEN_ABORT_TRUE_OR_ERROR( cmd.empty() == 0, "Invalid! Cmd empty." );

    register int exec = std::system( cmd.c_str() );

    GEN_TRUE_OR_ERROR( exec == 0, "Invalid command!" );

    return exec;
  }

  int system::remove( const std::string path )
  {
    GEN_ABORT_TRUE_OR_ERROR( path.empty() == 0, "Invalid! Path empty." );

    register int rm = std::remove( path.c_str() );

    GEN_TRUE_OR_ERROR( rm == 0, "Erro removing!" );

    return rm;
  }

  int system::rename( const std::string from, const std::string to )
  {
    GEN_ABORT_TRUE_OR_ERROR( from.empty() == 0, "Invalid! From empty." );
    GEN_ABORT_TRUE_OR_ERROR( to.empty() == 0, "Invalid! To empty." );

    register int rne = std::rename( from.c_str(), to.c_str() );

    GEN_TRUE_OR_ERROR( rne == 0, "Erro rename!" );

    return rne;
  }
}
