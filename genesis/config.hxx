/**
 * @file
 *
 * Definitions for an config.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_CONFIG_HPP
#define GENESIS_CONFIG_HPP

#include <genesis/lexical_cast.hxx>
#include <genesis/logger.hxx>
#include <genesis/string_util.hxx>

#include <map>

namespace genesis {
  /**
   * Genesis Configuration File Reader Class.
   */
  class config : public lexical_cast {
  public:
    /**
     * Constructor.
     *
     * @param filename - File Name.
     * @param delimiter - Delimiter default('=').
     * @param comment - Type comentary default('#').
     * @param sentry - End config.
     */
    config( std::string filename, std::string delimiter = "=",
     std::string comment = "#", std::string sentry = "end" );

    /**
     * Constructor.
     */
    config();

    /**
     * Destructor.
     */
    virtual ~config();

    /**
     * Search for key read value or optional default value.
     *
     * @param key - Search key.
     */	
    template<class T> 
    T read( const std::string& key ) const;

    /**
     * Search for key read value or optional default value.
     *
     * @param key - Search key.
     * @param value - Search value.
     */
    template<class T> T 
    read( const std::string& key, const T& value ) const;

    /**
     * Search for key read value or optional default value.
     *
     * @param var - Search variable.
     * @param key - Search key.
     */
    template<class T> 
    bool read_into( T& var, const std::string& key ) const;

    /**
     * Search for key read value or optional default value.
     *
     * @param var - Search variable.
     * @param key - Search key.
     * @param value - Search value.
     */
    template<class T>
    bool read_into( T& var, const std::string& key, const T& value ) const;
	
    /**
     * Added key and value to a config file.
     *
     * @param key - Add key name.
     * @param value - Add value.
     */
    template<class T> 
    void add( std::string key, const T& value );

    /**
     * Remove key and its value.
     */
    void remove( const std::string& key );
	
    /** 
     * Check whether key exists in configuration.
     *
     * @param key - Key name.
     * @return Contents key.
     */
    bool key_exists( const std::string& key ) const;

  private:	
    /** 
     * Delimiter. Check or change configuration syntax.
     *
     * @return Delimiter.
     */
    std::string get_delimiter() const { 
      return my_delimiter_; 
    }

    /**
     * Comment. Check or change configuration syntax.
     *
     * @return Comment.
     */ 
    std::string get_comment() const { 
      return my_comment_; 
    }

    /**
     * Sentry. Check or change configuration syntax.
     *
     * @return Sentry.
     */
    std::string get_sentry() const { 
      return my_sentry_; 
    }

    /**
     * Set delimiter. Check or change configuration syntax.
     *
     * @return Old delimiter.
     */
    std::string set_delimiter( const std::string& s ) {
      std::string old = my_delimiter_;  
      my_delimiter_ = s;
      return old; 
    }

    /**
     * Set comment. Check or change configuration syntax.
     *
     * @return Old comment.
     */
    std::string set_comment( const std::string& s ) {
      std::string old = my_comment_;  
      my_comment_ = s;  
      return old; 
    }

    /**
     * Ostream operator. Write configuration.
     *
     * @param os - Output stream to read.
     * @param cf - Configuration.
     * @return Output stream.
     */
    friend std::ostream& operator <<( std::ostream& os, const config& cf );

    /**
     * Istream operator. Read configuration.
     *
     * @param is - Read stream.
     * @param cf - Configuration.
     * @return Istream.
     */
    friend std::istream& operator >>( std::istream& is, config& cf );
	
  protected:
    /**
     * Template T as string.
     *
     * @param t - Template T.
     */
    template<class T> 
    static std::string T_as_string( const T& t );

    /**
     * String as T.
     *
     * @param s - String name.
     */
    template<class T> 
    static T string_as_T( const std::string& s );

    std::string my_delimiter_; /// Separator between key and value.
    std::string my_comment_;   /// Separator between value and comments.
    std::string my_sentry_;    /// Optional string to signal end of file.

    /// Extracted keys and values.
    std::map<std::string,std::string> my_contents_;

    /// Map.
    typedef std::map< std::string, std::string >::iterator mapi_;

    /// Mapc.
    typedef std::map< std::string, std::string >::const_iterator mapci_;
  };

/**
 * Convert from a T to a std::string.
 * 
 * @param t - As string.
 * @return Ost string.
 */
template<class T>
std::string config::T_as_string( const T& t )
{
  std::ostringstream ost;
  ost << t;
  return ost.str();
}

/**
 * Convert from a std::string to a T.
 *
 * @param s - String.
 * @return As string.
 */
template<class T>
T config::string_as_T( const std::string& s )
{
  T t;
  std::istringstream ist( s );
  ist >> t;
  return t;
}

/**
 * Convert string to bool.
 *
 * @param s - String.
 * @return True.
 */
template<>
 inline bool config::string_as_T<bool>( const std::string& s )
{
  genesis::lexical_cast::to_bool<bool>( s );
  return true;
}

/**
 * Read the value corresponding to key.
 *
 * @param key - String key.
 * @return As string.
 */
template<class T>
T config::read( const std::string& key ) const
{
  mapci_ p = my_contents_.find( key );

  if( p == my_contents_.end() ) {
    throw exp_key_not_found( key.c_str() );
  }

  return string_as_T<T>( p->second );
}

/**
 * Read the value corresponding to key or given 
 * default value.
 *
 * @param key - String key.
 * @param value - As string.
 * @return As string.
 */
template<class T>
T config::read( const std::string& key, const T& value ) const
{
  mapci_ p = my_contents_.find( key );

  if( p == my_contents_.end() ) {
    return value;
  }

  return string_as_T<T>( p->second );
}

template<class T>
bool config::read_into( T& var, const std::string& key ) const
{
  // Get the value corresponding to key and store in var
  // Return true if key is found
  // Otherwise leave var untouched
  mapci_ p = my_contents_.find( key );
  bool found = ( p != my_contents_.end() );

  if( found ) { 
    var = string_as_T<T>( p->second );
  }

  return found;
}

template<class T>
bool config::read_into( T& var, const std::string& key, const T& value ) const
{
  // Get the value corresponding to key and store in var
  // Return true if key is found
  // Otherwise set var to given default
  mapci_ p = my_contents_.find( key );
  bool found = ( p != my_contents_.end() );

  if( found ) {
    var = string_as_T<T>( p->second );
  } else {
    var = value;
  }

  return found;
}

template<class T>
void config::add( std::string key, const T& value )
{
  // Add a key with given value
  std::string v = T_as_string( value );

  genesis::string_util::trim( key );
  genesis::string_util::trim( v );

  my_contents_[key] = v;
  return;
}

}

#endif // GENESIS_CONFIG_FILE_HPP
