/**
 * @file
 *
 * Definitions for an application.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_APPLICATION_HPP
#define GENESIS_APPLICATION_HPP

#include <genesis/cmd_line_parser.hpp>
#include <genesis/lexical_cast.hpp>

#include <string>

namespace genesis {
  /**
   * Genesis Application Class.
   *
   * The Application class manages the create application's 
   * control flow and main settings.
   */
  class application : public cmd_line_parser, public lexical_cast {
  public:
    /// Successfull execution.
    static const int exit_success = EXIT_SUCCESS;

    /// Unsuccessfull execution.
    static const int exit_failure = EXIT_FAILURE;

    /// Unsuccessfull execution due to an exception.
    static const int exit_exception = 0;

    /** 
     * Unsuccessfull execution due to lack of information
     * to complete processing. 200 is exist_failure
     * fixing value in 210.
     */
    static const int exit_not_enough_info = 210;

    /**
     * Color ANSI types.
     */
    enum color {
      BLUE,
      CYAN,
      GREEN,
      MAGENTA,
      RED,
      WHITE,
      YELLOW
    };

    /**
     * Constructor.
     */
    application() {};

    /**
     * Destructor.
     */
    virtual ~application();

    /**
     * Instance for class cmd_line_parser. Used
     * to module tools application.
     */
    cmd_line_parser cmd;

    /**
     * Run the application.
     *
     * @param argc Command-line argument count.
     * @param argv Command-line arguments.
     */
    virtual int run( int argc, char* argv[] );

    /**
     * Terminate application.
     */
    static void exit();

    /**
     * Abort application.
     */
    static void abort();

    /**
     * Cursor Wait Progress.
     */
    void set_progress( long int wait = 30000 );

    /**
     * Set Ansi color text.
     *
     * @param p - Stream Text.
     * @param cod_color - Number color (default 0).
     */
    void set_ansi_color( std::ostream& p, int cod_color = 0 );

    /**
     * Set Restore Normal Color.
     */
    void set_restore_ansi_color();

    /**
     * Get the application name.
     *
     * @return Application name.
     */
    std::string name() const {
      return name_;
    }

  private:
    std::string name_; ///< Application name.

  protected:
    /**
     * The main function for the application.
     *
     * @param argc Number of arguments in command line
     * @param argv List of arguments in command line
     * @return 0 on sucess, not 0 on error.
     */
    virtual int main( int argc, char* argv[] );

    /// Is debug mode enabled?
    static bool is_debug_enabled_;
  };

}

#endif // GENESIS_APPLICATION_HPP
