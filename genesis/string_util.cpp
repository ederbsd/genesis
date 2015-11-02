/**
 * @file
 *
 * Implementation for an string_util.
 *
 * GENESIS - Library of general purpose classes
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

#include <genesis/string_util.hpp>

#include <algorithm>
#include <cctype>

namespace genesis {

  std::string string_util::to_uppercase( const std::string& s )
  {
    std::string up;

    std::transform( s.begin(), s.end(),
                    std::inserter( up, up.end() ),
                    ::toupper );
    return up;
  }

  std::string string_util::left_trim( const std::string& s, char c )
  {
    std::string::size_type i( 0 );

    while( i < s.length() && s[i] == c ) {
      ++i;
    }

    return i == 0 ? s : s.substr( i );
  }

  std::string string_util::right_trim( const std::string& s, char c )
  {
    std::string::size_type i( s.length() - 1 );

    while( i != std::string::npos && s[i] == c ) {
      --i;
    }

    return s.substr( 0, i + 1 );
  }

  void string_util::trim( std::string& s )
  {
    // Remove leading and trailing whitespace.
    static const char whitespace[] = " \n\t\v\r\f";
    s.erase( 0, s.find_first_not_of( whitespace ) );
    s.erase( s.find_last_not_of( whitespace ) + 1U );
  }

  std::pair<std::string,std::string> string_util::split( const std::string& s, char c )
  {
    std::string::size_type pos(  s.find( c ) );
    return make_pair( trim( s.substr( 0, pos ) ),
                      trim( pos == std::string::npos ?
                            std::string("") : s.substr( pos + 1 ) ) );
  }

  std::vector<std::string> string_util::split_all( const std::string& s, char c )
  {
    std::vector<std::string> vec_st;
    std::string splited = s;

    // This check is done to avoid the first element of 
    // splited be empty.
    if( splited.substr( 0, 1 ) == "/" ) {
      splited = splited.substr( 1 );
    }

    while( splited != "" ) {
      std::string single_st = split( splited, c ).first;
      splited = split( splited, c ).second;
      vec_st.push_back( single_st );
    }

    return vec_st;
  }

}
