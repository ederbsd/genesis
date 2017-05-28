/**
 * @file
 *
 * Definitions for an cmd_line_parser.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#pragma once
#ifndef GENESIS_CMD_LINE_PARSER_HXX
#define GENESIS_CMD_LINE_PARSER_HXX

#include <genesis/proto_types.hxx>

#include <string>

namespace genesis {
/**
 * Genesis Command Line Parser Class.
 */
class cmd_line_parser
{
public:
    /**
     * Constructor.
     */
    cmd_line_parser();

    /**
     * Destructor.
     */
    virtual ~cmd_line_parser();

    /**
     * Provide the input for the options like argv[] for commandline
     * and the option file name  to use.
     *
     * @param argc - Command line argument count.
     * @param argv - Command line argument count.
     */
    void use_command_args( int argc, char *argv[] );

    /**
     * Prints warning verbose if you set anything wrong
     */
    void set_verbose();

    /**
     * Set option.
     *
     * @param opt_string - Full name of the option.
     */
    void set_option( char *opt_string );

    /**
     * Set option.
     *
     * @param opt_string - Full name of the option.
     * @param opt_char - Short name of the option.
     */
    void set_option( const char *opt_string, char opt_char );

    /**
     * Set flag.
     *
     * @param opt_string - Full name of the flag.
     */
    void set_flag( const std::string opt_string );

    /**
     * Set flag.
     *
     * @param opt_char - Short name of the flag.
     */
    void set_flag( char opt_char );

    /**
     * Set flag.
     *
     * @param opt_string - Full name of the flag.
     * @param opt_char - Short name of the flag.
     */
    void set_flag( const std::string opt_string, char opt_char );

    /**
     * Process the options, registerd using method
     * use_command_args().
     */
    void process_options();

    /**
     * Process command args.
     *
     * @param max_args - Number max args.
     */
    void process_command_args( int max_args );

    /**
     * Process the specified options.
     *
     * @param argc - Process argc.
     * @param argv - Process argv.
     * @param max_args - Number max args.
     */
    void process_command_args( int argc, char *argv[], int max_args );

    /**
     * Process the specified options.
     *
     * @param argc - Process argc.
     * @param argv - Process argv.
     */
    void process_command_args( int argc, char *argv[] );

    /**
     * Process command args.
     */
    void process_command_args();

    /**
     * Get the value of the options.
     *
     * @param option - Full name of the option.
     * @return Return 0 if no value is set.
     */
    char *get_value( const std::string option );

    /**
     * Get flag.
     *
     * @param option - Name of the get flag.
     * @return Return true.
     */
    bool get_flag( const std::string option );

    /**
     * Get the value of the option.
     *
     * @param option - Short name of the option.
     * @return Return 0 if no value is set.
     */
    char *get_value( char option );

    /**
     * Get flag.
     *
     * @param option - Short name get flag.
     * @return Return true.
     */
    bool get_flag( char option );

    /**
     * Print Usage.
     */
    void print_usage();

    /**
     * Print auto usage.
     */
    void print_auto_usage();

    /**
     * Add mode usage.
     *
     * @param desc - Description mode usage.
     */
    void add_usage( const std::string desc );

    /**
     * Print Help.
     */
    void print_help();

    /**
     * Print auto usage.
     *
     * @param flag - Name of the flag.
     */
    void auto_usage_print( bool flag );

    /**
     * Get the argument count and arguments sans the
     * options.
     *
     * @return Return 0 if no value is set.
     */
    int get_argc();

    /**
     * Get the argument count and arguments the
     * options.
     *
     * @param index - Number of the argument.
     * @return Return 0 if no value is set.
     */
    char *get_argv( int index );

    /**
     * Check all options.
     *
     * @return Return true values is ok.
     */
    bool has_options();

private:
    /**
     * Init method.
     */
    void init();

    /**
     * Init method.
     *
     * @param maxopt - Number of options.
     * @param maxcharopt - Number of characters.
     */
    void init( int maxopt, int maxcharopt );

    /**
     * Alloc memory.
     *
     * @return true If success allocating memory.
     */
    bool alloc();

    /**
     * Free memory.
     */
    void free();

    /**
     * Storage values.
     *
     * @return Return set_ if ok.
     */
    bool value_store_ok();

    /**
     * Set value.
     *
     * @param option - Full name of the option.
     * @param value - Name of the value.
     * @return Return true if ok.
     */
    bool set_value( const char *option, char *value );

    /**
     * Set flag on.
     *
     * @param option - Found flag.
     * @return Return true if ok.
     */
    bool set_flag_on( const char *option );

    /**
     * Set value.
     *
     * @param option - Name of the option.
     * @param value - Name of the value.
     * @return Return true if ok.
     */
    bool set_value( char option, char *value );

    /**
     * Set flag on.
     *
     * @param opt_char - Found flag.
     * @return Return true if ok.
     */
    bool set_flag_on( char opt_char );

    /**
     * Add options.
     *
     * @param option - Full name of the option.
     * @param type - Number type option.
     */
    void add_option( const char *option, int type );

    /**
     * Add options.
     *
     * @param opt - Full name of the option.
     * @param type - Number type option.
     */
    void add_option( char opt, int type );

    /**
     * Find flag.
     *
     * @param val - Find value.
     * @return Return true if ok.
     */
    bool find_flag( char *val );

    /**
     * Command set.
     *
     * @return Return storage.command_set.
     */
    bool command_set();

    /**
     * Standard posix.
     *
     * @return Return storage.posix_style.
     */
    bool posix();

    /**
     * Parse argument posix.
     *
     * @param arg - Argument example '-x, -w'.
     */
    char parse_posix( char *arg );

    /**
     * Parse argument GNU.
     *
     * @param arg - Argument example '--xxx=10'.
     */
    int parse_gnu( char *arg );

    /**
     * Match Option.
     *
     * @param opt - Found option.
     * @return Return 'i' if found option.
     */
    int match_opt( char *opt );

    /**
     * Match Character.
     *
     * @param c - Found character.
     * @return Return true if found character.
     */
    bool match_char( char c );

    /**
     * Print verbose messages in console.
     *
     * @param msg1 - Message 1.
     * @param msg2 - Message 2.
     */
    void print_verbose( const char *msg1, const char *msg2 );

    /**
     * Print verbose message in console.
     *
     * @param msg - Message.
     */
    void print_verbose( char *msg );

    /**
     * Print verbose message in console.
     *
     * @param msg - Message.
     */
    void print_verbose( char msg );

    /**
     * Print default verbose message in console.
     */
    void print_verbose();

protected:
    /// Command line.
    proto_cmd::argts argts;

    /// Option "chars" storage and indexing.
    proto_cmd::chars_storage chars_storage;

    /// Help and usage variables.
    proto_cmd::help_storage help_storage;

    /// Storage variables.
    proto_cmd::storage storage;

    /// Stream variables.
    proto_cmd::stream stream;

    /// Option "string" storage and indexing.
    proto_cmd::str_storage str_storage;

    /// Values Storage.
    proto_cmd::values_storage values_storage;

    static bool set_; ///< Was static member
    static bool once_; ///< Was static member

    bool has_options_; ///< Has options.
    bool auto_usage_;  ///< Automatic usage.

};
}

#endif // GENESIS_CMD_LINE_PARSER_HXX
