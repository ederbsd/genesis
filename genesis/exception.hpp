/**
 * @file
 *
 * Implementations for an exception.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_EXCEPTION_HPP
#define GENESIS_EXCEPTION_HPP

#include <exception>
#include <stdexcept>

namespace genesis {
  /** 
   * Genesis Class exception augments the standard exception class by
   * allowing a const char* parameter in the constructor.
   */
  class exception : public std::exception {
  public:
    /**
     *Constructor.
     */
    explicit exception( const char* msg )
     : std::exception(), msg_( msg ) {};

    /**
     * Get message exception.
     */ 
    virtual const char* what() const throw() { return msg_; };

  private:
    const char* msg_; ///< Get message ptr.
  };

/**
 * Macro CAUGHT Exception.
 */
#define GEN_CAUGHT_EXCEPTION( caught, message ) \
  class caught : public genesis::exception { \
  public: \
    explicit caught( const char* msg = message ) \
     : exception( msg ) {}; \
  };

  /**
   * Class Exception File not found.
   */
  class exp_file_not_found : public genesis::exception {
  public:
    /**
     * Constructor.
     */ 
    explicit exp_file_not_found( const char* msg = "File not found!" )
     : genesis::exception( msg ) {};
  };

  /**
   * Class Exception key not found.
   */
  class exp_key_not_found : public genesis::exception {
  public:
    /**
     * Constructor.
     */ 
    explicit exp_key_not_found( const char* msg = "Key not found!" )
     : genesis::exception( msg ) {};
  };

  /**
   * Class Exception Abort.
   */ 
  class exp_abort : public genesis::exception, public std::runtime_error {
  public:
    /**
     * Constructor.
     */ 
    explicit exp_abort( const char* msg = "" )
     : genesis::exception( msg ), std::runtime_error( "Runtime abort..." ) {};
  };

  /**
   * Class Exception Bad Alloc Memory.
   */
  class exp_memory : public genesis::exception, std::bad_alloc {
  public:
    /**
     * Constructor.
     */
    explicit exp_memory( const char* msg = "" )
     : genesis::exception( msg ), 
       std::bad_alloc() {};
  }; 

}

#endif // GENESIS_EXCEPTION_HPP
