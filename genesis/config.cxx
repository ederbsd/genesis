/**
 * @file
 *
 * Implementations for an config.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <genesis/config.hxx>

#include <fstream>

namespace genesis {

  config::config( std::string filename, std::string delimiter,
   std::string comment, std::string sentry ) : my_delimiter_( delimiter ),
   my_comment_( comment ), my_sentry_( sentry )
  {
    // Construct a config, getting keys and values from given file.
    std::ifstream in( filename.c_str() );
    if( !in ) {
      throw exp_file_not_found( filename.c_str() );
    }

    in >> ( *this );
  }

  config::config()
   : my_delimiter_( std::string( 1, '=' ) ), 
     my_comment_( std::string( 1, '#' ) )
  {
  }

  config::~config()
  {
  }

  void config::remove( const std::string& key )
  {
    my_contents_.erase( my_contents_.find( key ) );
  }

  bool config::key_exists( const std::string& key ) const
  {
    // Indicate whether key is found.
    mapci_ p = my_contents_.find( key );
    return( p != my_contents_.end() );
  }

  std::ostream& operator<<( std::ostream& os, const config& cf )
  {
    // Save a config to os.
    for( config::mapci_ p = cf.my_contents_.begin(); 
          p != cf.my_contents_.end(); ++p ) {
      os << p->first << " " << cf.my_delimiter_ << " ";
      os << p->second << std::endl;
    }
    return os;
  }

  std::istream& operator>>( std::istream& is, config& cf )
  {
    // Load a config from is. Read in keys and values, 
    // keeping internal whitespace.
    typedef std::string::size_type pos;

    const std::string& delim = cf.my_delimiter_; // Separator.
    const std::string& comm = cf.my_comment_; // Comment.
    const std::string& sentry = cf.my_sentry_; // End of file sentry.

    const pos skip = delim.length(); // Length of separator.

    // Might need to read ahead to see where value ends.
    std::string nextline = "";

    while( is || nextline.length() > 0 ) {
      // Read an entire line at a time.
      std::string line;

      if( nextline.length() > 0 ) {
        line = nextline; // We read ahead, use it now.
	nextline = "";
      } else {
        std::getline( is, line );
      }
		
      // Ignore comments.
      line = line.substr( 0, line.find( comm ) );

      // Check for end of file sentry.
      if( sentry != "" && line.find( sentry ) != std::string::npos ) {
        return is;
      }

      // Parse the line if it contains a delimiter.
      pos delimPos = line.find( delim );

      if( delimPos < std::string::npos ) {
        // Extract the key
	std::string key = line.substr( 0, delimPos );
	line.replace( 0, delimPos+skip, "" );

        // See if value continues on the next line.
	// Stop at blank line, next line with a key, end of stream,
	// or end of file sentry.
	bool terminate = false;

        while( !terminate && is ) {
          std::getline( is, nextline );
	  terminate = true;

	  std::string nlcopy = nextline;
          genesis::string_util::trim( nlcopy );

          if( nlcopy == "" ) { 
            continue;
          }

          nextline = nextline.substr( 0, nextline.find( comm ) );

          if( nextline.find( delim ) != std::string::npos ) {
            continue;
          }

          if( sentry != "" && nextline.find( sentry ) != std::string::npos ) {
            continue;
          }

          nlcopy = nextline;
          genesis::string_util::trim( nlcopy );

          if( nlcopy != "" ) {
            line += "\n";
          }

          line += nextline;
          terminate = false;
	}
			
	// Store key and value.
	genesis::string_util::trim( key );
	genesis::string_util::trim( line );
	cf.my_contents_[key] = line; // Overwrites if key is repeated.

	}
      }

    return is;
  }
}
