/**
 * @file
 * 
 * Definitions for an lexical_cast.
 * 
 * GENESIS - Library of general purpose classes
 * 
 * Copyright (c) 2009 Ederson de Moura
 * 
 * @author Ederson de Moura
 * 
 * $Id: Exp$
 */

#ifndef GENESIS_LEXICAL_CAST_HPP
#define GENESIS_LEXICAL_CAST_HPP

#include <genesis/logger.hpp>

#include <sstream>

namespace genesis {
  /**
   * Genesis Lexical Cast Class.
   */
  class lexical_cast {
  public:
    /**
     * Constructor.
     */
    lexical_cast();

    /**
     * Destructor.
     */
    virtual ~lexical_cast();
 
    /**
     * Convert string to double.
     *
     * @param s - String to be converted.
     * @return Converted double value.
     */ 
    template<class T>
    inline static T to_double( std::string const& s )
    {
      GEN_ABORT_TRUE_OR_ERROR( s.empty() == 0, "Invalid! Param empty." );

      std::istringstream ss( s );

      double d = 0.;
      ss >> d;

      if( !( ss && ( ss >> std::ws ).eof() ) ) {
        GEN_ERROR( "Error in converting to double!" );
        return 0.;
      }

      return d;
    }

    /**
     * Convert string to int.
     *
     * @param s - String to be converted.
     * @return Converted int value.
     */
    template<class T>
    inline static T to_int( std::string const& s )
    {
      GEN_ABORT_TRUE_OR_ERROR( s.empty() == 0, "Invalid! Param empty." );

      std::istringstream ss( s );

      register int d = 0;
      ss >> d;

      if( !( ss && ( ss >> std::ws ).eof() ) ) {
        GEN_ERROR( "Error in converting to int!" );
        return 0;
      }

      return d;
    }

    /**
     * Convert string to size_t.
     *
     * @param s - String to be converted.
     * @return Converted size_t value.
     */
    template<class T>
    inline static T to_size_t( std::string const& s )
    {
      GEN_ABORT_TRUE_OR_ERROR( s.empty() == 0, "Invalid! Param empty." );

      std::istringstream ss( s );

      register size_t d = 0;
      ss >> d;

      if( !( ss && ( ss >> std::ws ).eof() ) ) {
        GEN_ERROR( "Error in converting to size_t!" );
        return 0;
      }

      return d;
    }

    /**
     * Convert string to bool.
     *
     * @param s - String to be converted.
     * @return Converted bool value.
     */
    template<class T>
    static T to_bool( std::string const& s )
    {
      GEN_ABORT_TRUE_OR_ERROR( s.empty() == 0, "Invalid! Param empty." );

      // Interpret: "false", "F", "no", "n", "0" as false.
      // Interpret: "true", "T", "yes", "y", "1", "-1", or 
      // anything else as true.
      bool b = true;
      std::string sup = s;

      for( std::string::iterator p = sup.begin(); p != sup.end(); ++p ) {
        *p = toupper( *p ); // Make std::string all caps.
      }

      if( sup == std::string( "FALSE" ) || sup == std::string( "F" ) ||
          sup == std::string( "NO" ) || sup == std::string( "N" ) ||
          sup == std::string( "0" ) || sup == std::string( "NONE" ) ) {
        b = false;
      }
 
      return b;
    }

  };
}

#endif // GENESIS_LEXICAL_CAST_HPP
