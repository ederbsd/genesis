/**
 * @file
 *
 * Definitions for an logger.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_LOGGER_HPP
#define GENESIS_LOGGER_HPP

#include <genesis/genesis.hpp>
#include <genesis/exception.hpp>

#include <iostream>
#include <memory>
#include <ostream>

namespace genesis {
  /** 
   * Genesis Logger Class.
   */
  class logger {
  public:
    /**
     * Constructor.
     */
    logger();

    /**
     * Destructor.
     */ 
    ~logger();
        
    /// Return true if logger is activated.
    static bool is_activated();

    /// Activate and deactivate logger.
    static void activate( bool const activated );

    /// Return reference to pointer to output stream.
    static ::std::ostream *& ostream_ptr();

  private:
    /// True if logger is activated.
    static bool is_activated_;

    /// Auto pointer helps manage resources.
    static ::std::auto_ptr< ::std::ostream > outstream_helper_ptr_;

    /// Pointer to the output stream of the logger
    static ::std::ostream* outstream_;

  private:
    /// In this design logger should be noncopyable.
    logger( logger const& );
    logger & operator=( logger const& );

  };

  // Important funtion which helps solves
  // "static initialisation fiasco" problem.
  extern logger & logger_parent();

  namespace detail {
    extern ::std::auto_ptr<logger> logger_out_ptr_;
  }

} // Namespace genesis.

/** 
 * Macro prints variable name and its value to the 
 * logger stream.
 */
#define GEN_LOG( name ) \
    do { if( genesis::logger_parent().is_activated() ) { \
    *genesis::logger_parent().ostream_ptr() << __FILE__ \
    << " [" << __LINE__ << "] : " << #name \
    << " = " << ( name ) << ::std::endl; } } while( false )

/**
 * Macro print messages.
 */
#define GEN_MSG( str ) \
  do { if( genesis::logger_parent().is_activated() ) { \
  *genesis::logger_parent().ostream_ptr() << str \
  << ::std::endl; } } while( false )

/**
 * Macro print values.
 */
#define GEN_PRINT( str ) \
  do { if( genesis::logger_parent().is_activated() ) { \
  *genesis::logger_parent().ostream_ptr() << str \
  << ::std::endl; } } while( false )

/**
 * Macro prints value of the variable to the logger stream
 * useful for printing constant strings
 */
#define GEN_LOG_MSG( str ) \
  do { if( genesis::logger_parent().is_activated() ) { \
  *genesis::logger_parent().ostream_ptr() << __FILE__ \
  << " [" << __LINE__ << "] : " << str \
  << ::std::endl; } } while( false )

/**
 * Macro used to produce a warning log message containing origin information.
 * This macro supports printf like semantics.
 */
#define GEN_WARN( ... ) \
  do { if( genesis::logger_parent().is_activated() ) { \
  *genesis::logger_parent().ostream_ptr() << __FILE__ \
  << " [" << __LINE__ << "] : " << genesis::library::package() \
  << " Warning> " << __VA_ARGS__  \
  << ::std::endl; } } while( false )

/**
 * Macro used to produce an error log message containing origin information.
 * This macro supports printf like semantics. The log handler must guarantee 
 * that this macro never returns.
 */
#define GEN_ERROR( ... ) \
  do { if( genesis::logger_parent().is_activated() ) { \
  *genesis::logger_parent().ostream_ptr() << __FILE__ \
  << " [" << __LINE__ << "] : " << genesis::library::package() \
  << " Error> " << __VA_ARGS__  \
  << ::std::endl; } } while( false )

/**
 * Check if a condition is valid, only checked when PCS_NDEBUG is 
 * not defined.
 *
 * @param _arg - Condition to check.
 */
#define GEN_ASSERT( _arg ) \
  if( !( _arg ) ) { \
    GEN_ERROR(  "Assertion failed: " #_arg ); \
  }

/**
 * Macro used to produce an error log message containing origin information
 * when condition @a arg fails. This macro supports printf like semantics.
 * The log handler must guarantee that this macro never returns.
 */
#ifndef WIN32
#define GEN_TRUE_OR_ERROR( arg, ... )  \
  if( !( arg ) ) { GEN_ERROR( __VA_ARGS__ ); }
#else
inline void GEN_TRUE_OR_ERROR( bool arg, ... )
{
  if( !arg ) {
    va_list va;
    va_start( va, arg );
    GEN_ERROR( va );
    va_end( va );
  }
}
#endif

/**
 * Macro used to produce an error log message and abort exception.
 * This macro supports printf like semantics.
 * The log handler must guarantee that this macro never returns.
 */
#ifndef WIN32
#define GEN_ABORT_TRUE_OR_ERROR( arg, ... )  \
  if( !( arg ) ) { \
    try { \
      GEN_ERROR( __VA_ARGS__ ); \
      throw genesis::exp_abort(); \
    } \
    catch(  genesis::exp_abort& e ) { \
      std::cerr << "Caught: " << e.runtime_error::what() << std::endl; \
      throw genesis::exp_abort(); \
    } \
  }
#else
inline void GEN_ABORT_TRUE_OR_ERROR( bool arg, ... )
{
  if( !arg ) {
    va_list va;
    va_start( va, arg );
    GEN_ERROR( va );
    va_end( va );
  }
}
#endif

namespace genesis {
    // Example how to create functions which operates on logger stream
    // here are used templates for preparing function which is independent
    // on the type, but this is not required.
    template<typename T1, typename T2, typename T3, typename T4> 
    void put_debug_info ( logger & log, 
        T1 const & t1, T2 const & t2, T3 const & t3, T4 const & t4 )
    {
      if( log.is_activated() ) {
        *( log.ostream_ptr() ) << t1 << " (" << t2 << ") : ";
        *( log.ostream_ptr() ) << t3 << " = " << t4 << ::std::endl;
      } 
    }
    
    template<typename T> 
    void put_log_info( logger & log, T const & t )
    {
      if( log.is_activated() ) {
        *( log.ostream_ptr() ) << t << ::std::endl;
      } 
    }
}

/** 
 * Macro shows how to write macros which using 
 * user-defined functions.
 */
#define GEN_LOG_FN( name ) \
  ::genesis::put_debug_info ( genesis::logger_parent(),\
  __FILE__, __LINE__, #name, ( name ) )

#define GEN_LOG_INFO( name ) \
  ::genesis::put_log_info ( genesis::logger_parent(), ( name ) )

/**
 *  Macros for switching off and on logger.
 */
#define GEN_LOG_ON() \
  do { ::genesis::logger_parent().activate ( true ); } while( false )
#define GEN_LOG_OFF() \
  do { ::genesis::logger_parent().activate ( false ); } while( false )

#if defined( CLEANTLOG )
#undef GEN_LOG
#undef GEN_LOG_ON
#undef GEN_LOG_OFF
#undef GEN_LOG_FN
#undef GEN_LOG_STR
#undef GEN_LOG_INFO
#define GEN_LOG( name ) do{}while( false )
#define GEN_LOG_FN( name ) do{}while( false )
#define GEN_LOG_ON() do{}while( false )
#define GEN_LOG_OFF() do{}while( false )
#define GEN_LOG_STR( str ) do{}while( false )
#define GEN_LOG_INFO( str ) do{}while( false )
#endif

#endif // GENESIS_LOGGER_HPP
