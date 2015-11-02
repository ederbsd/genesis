/**
 * @file
 *
 * Implementations for an application.
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

#include <genesis/application.hpp>
#include <genesis/exception.hpp>
#include <genesis/logger.hpp>

#include <cstdlib>
#include <csignal>

// Ansi color codes.
#define ANSI_COLOR_CLEAR "\e[0m"

#define ANSI_COLOR_BLUE "\e[34m"
#define ANSI_COLOR_CYAN "\e[36m"
#define ANSI_COLOR_GREEN "\e[32m"
#define ANSI_COLOR_MAGENTA "\e[35m"
#define ANSI_COLOR_RED "\e[31m"
#define ANSI_COLOR_WHITE "\e[37m"
#define ANSI_COLOR_YELLOW "\e[33m"

namespace genesis {

  bool application::is_debug_enabled_ = false;

  application::~application()
  {
  }

  void signal_handler( int signum )
  {
    std::string msg;

    try {
      switch( signum ) {
      case SIGABRT:
        msg = "SIGABRT received!";
        throw genesis::exp_abort();
        break;
      case SIGSEGV:
        msg = "SIGSEGV received!";
        throw genesis::exp_abort();
        break;
      case SIGFPE:
        msg = "SIGFPE received!";
        throw genesis::exp_abort();
        break;
      case SIGILL:
        msg = "SIGILL received!";
        throw genesis::exp_abort();
        break;
      case SIGINT:
        msg = "SIGINT received!";
        throw genesis::exp_abort();
        break;
#ifndef WIN32
      case SIGQUIT:
        msg = "SIGQUIT received!";
        throw genesis::exp_abort();
        break;
#endif
      case SIGTERM:
        msg = "SIGTERM received!";
        throw genesis::exp_abort();
        break;
      default:
        msg = "Unknown signal received: ";
        throw genesis::exp_abort();
      }
    }
    catch( genesis::exp_abort& e ) {
      GEN_ERROR( msg );
      std::cerr << "Caught: " << e.runtime_error::what() << std::endl;
      application::exit(); // Exit Now!
    }
  }

  int application::run( int argc, char* argv[] )
  {
    std::signal( SIGABRT, signal_handler );
    std::signal( SIGSEGV, signal_handler );
    std::signal( SIGFPE, signal_handler );
    std::signal( SIGILL, signal_handler );
    std::signal( SIGINT, signal_handler );
#ifndef WIN32
    std::signal( SIGQUIT, signal_handler );
#endif
    std::signal( SIGTERM, signal_handler );

    // Get name app.
    name_ = argv[0];

    return main( argc, argv );
  }

  int application::main( int argc, char* argv[] )
  {
    int status = EXIT_SUCCESS;
    return status;
  }

  void application::exit()
  {
    int status = EXIT_SUCCESS;
    std::exit( status );
  }

  void application::abort()
  {
    std::abort();
  }

  void application::set_progress( long int wait )
  {
    char cursor_run[8] = { '-', '\\', '|', '/', '-', '\\', '|', '/' };

    register int i = 0;

    for( ; i < 80; i++ ) {
      ( void )usleep( wait );
      //datetime::msleep( wait );
      printf( "%c\033[2D", cursor_run[i%8] );
      std::fflush( stdout );
    }
  }

  void application::set_ansi_color( std::ostream& p, int cod_color )
  {
    switch( cod_color ) {
    case BLUE: // 0.
      p << ANSI_COLOR_BLUE;
      break;
    case CYAN: // 1.
      p << ANSI_COLOR_CYAN;
      break;
    case GREEN: // 2.
      p << ANSI_COLOR_GREEN;
      break;
    case MAGENTA: // 3.
      p << ANSI_COLOR_MAGENTA;
      break;
    case RED: // 4.
      p << ANSI_COLOR_RED;
      break;
    case WHITE: // 5.
      p << ANSI_COLOR_WHITE;
      break;
    case YELLOW: // 6.
      p << ANSI_COLOR_YELLOW;
    default:
      GEN_ERROR( "Color not found!" );
      break;
    }
  }

  void application::set_restore_ansi_color( void )
  {
    GEN_MSG( ANSI_COLOR_CLEAR );
  }

}
