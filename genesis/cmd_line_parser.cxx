/**
 * @file
 *
 * Implementations for an cmd_line_parser.
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

#include <genesis/cmd_line_parser.hxx>
#include <genesis/application.hxx>
#include <genesis/logger.hxx>

#include <cstring>

static const char* CMD_TRUE_FLAG = "true";

static const int CMD_COMMAND_FLAG = 5;
static const int CMD_COMMAND_OPT = 2;
static const int CMD_COMMON_FLAG = 4;
static const int CMD_COMMON_OPT = 1;
//static const int CMD_FILE_FLAG = 6;
//static const int CMD_FILE_OPT = 3;

static const int CMD_DEFAULT_MAXOPTS = 10;
static const int CMD_DEFAULT_MAXUSAGE = 3;

namespace genesis {

  // Start static variables.
  bool cmd_line_parser::set_ = false;
  bool cmd_line_parser::once_ = false;

  cmd_line_parser::cmd_line_parser()
  {
    init();
  }

  cmd_line_parser::~cmd_line_parser()
  {
    if( storage.mem_allocated ) {
      free();
    }
  }

  void cmd_line_parser::init()
  {
    init( CMD_DEFAULT_MAXOPTS, CMD_DEFAULT_MAXOPTS );
  }

  void cmd_line_parser::init( int maxopt, int maxcharopt )
  {
    // Load argts.
    argts.appname = 0;
    argts.argc = 0;
    argts.argv = 0;
    argts.max_legal_args = 0;
    argts.new_argc = 0 ;
    argts.new_argv = 0;

    // Load string storage.
    str_storage.max_options = maxopt;
    str_storage.option_counter = 0;

    // Load char's storage.
    chars_storage.optchar_counter = 0;
    chars_storage.max_char_options = maxcharopt;    

    // Load values storage.
    values_storage.g_value_counter = 0;
    values_storage.values = 0;	

    // Load help storage.
    help_storage.max_usage_lines = CMD_DEFAULT_MAXUSAGE;
    help_storage.usage_lines = 0;

    // Load storage.
    storage.command_set = false;
    storage.mem_allocated = false;
    storage.posix_style = true;
    storage.verbose = false;

    // Load stream's.
    stream.comment = '#' ;
    stream.delimiter = ':' ;
    stream.endofline = '\n';
    stream.equalsign = '=';
    stream.file_comment_char = '#';
    stream.file_delimiter_char = ':';
    stream.nullterminate = '\0';
    stream.opt_prefix_char = '-';
    stream.whitespace = ' ' ;

    // Was variables static. 
    set_ = false;
    once_ = true;

    auto_usage_ = false;
    has_options_ = false;
    
    std::strcpy( stream.long_opt_prefix , "--" );

    GEN_CAUGHT_EXCEPTION( exp_memory, "Memory bad allocation!" );

    if( alloc() == false ) {
      throw exp_memory();
    }

  }

  bool cmd_line_parser::alloc()
  {
    int i = 0;
    int size = 0 ;

    GEN_CAUGHT_EXCEPTION( exp_memory, "Memory bad allocation!" );

    try {

      if( storage.mem_allocated ) {
        return true;
      }

      size = ( str_storage.max_options+1 ) * sizeof( const char* );

      // Allocate memory.
      str_storage.options = new const char*[ size ];
      str_storage.optiontype = new int[ str_storage.max_options+1 ]; 
      str_storage.optionindex = new int[ str_storage.max_options+1 ];

      if( str_storage.options == 0 || str_storage.optiontype == 0 
           || str_storage.optionindex == 0 ) {
        return false;
      } else {
        storage.mem_allocated  = true;
      }
      
      for( i = 0 ; i < str_storage.max_options ; i++ ) {
        str_storage.options[i] = 0;
        str_storage.optiontype[i] = 0 ;
        str_storage.optionindex[i] = -1 ;
      }

      // Allocate memory.
      chars_storage.optionchars = new char[ chars_storage.max_char_options+1 ];
      chars_storage.optchartype = new int[ chars_storage.max_char_options+1 ];
      chars_storage.optcharindex = new int[ chars_storage.max_char_options+1 ];

      if( chars_storage.optionchars == 0 || 
           chars_storage.optchartype == 0 || 
           chars_storage.optcharindex == 0 ) {
        storage.mem_allocated = false;
        return false;
      }

      for( i = 0 ; i < chars_storage.max_char_options ; i++ ) {
        chars_storage.optionchars[i] = '0';
        chars_storage.optchartype[i] = 0 ;
        chars_storage.optcharindex[i] = -1 ;
      }

      size = ( help_storage.max_usage_lines+1 ) * sizeof( const char* );
      help_storage.usage = new const char*[ ( char )size ];

      if( help_storage.usage == 0  ) {
        storage.mem_allocated = false;
        return false;
      }

      for( i = 0 ; i < help_storage.max_usage_lines ; i++ ) {
        help_storage.usage[i] = 0;
      }

    }
    catch( exp_memory& exp ) {
      GEN_ERROR( exp.what() );
    }

    return true;
  }

  void cmd_line_parser::free()
  {
    delete str_storage.options;
    delete str_storage.optiontype;
    delete str_storage.optionindex;
    delete chars_storage.optionchars;
    delete chars_storage.optchartype;
    delete chars_storage.optcharindex;
    delete help_storage.usage;

    if( values_storage.values != 0 ) {
      delete values_storage.values;
      if( argts.new_argv != 0 ) {
        delete argts.new_argv;
      }
    }
  }

  bool cmd_line_parser::command_set()
  {
    return( storage.command_set );
  }

  bool cmd_line_parser::posix()
  {
    return storage.posix_style;
  }

  void cmd_line_parser::set_verbose()
  {
    storage.verbose = true;
  }

  void cmd_line_parser::print_verbose()
  {
    if( storage.verbose ) {
      GEN_ERROR( "Unknown command argument option!" );
    }
    application::exit();
  }

  void cmd_line_parser::print_verbose( const char* msg1, const char* msg2 )
  {
    if( storage.verbose ) {
      GEN_ERROR( std::string( msg1 ) + std::string( msg2 ) );
    }
    application::exit();
  }

  void cmd_line_parser::print_verbose( char* msg )
  {
    if( storage.verbose ) {
      GEN_ERROR( "Unknown command argument option: " + std::string( msg ) );
    }
    application::exit();
  }

  void cmd_line_parser::print_verbose( char msg )
  {
    if( storage.verbose ) {
    }
  }

  bool cmd_line_parser::has_options()
  {
    return has_options_;
  }

  void cmd_line_parser::auto_usage_print( bool flag )
  {
    auto_usage_ = flag;
  }

  void cmd_line_parser::use_command_args( int argc, char* argv[] )
  {
    argts.argc = argc;
    argts.argv = argv;
    storage.command_set = true;
    argts.appname = argts.argv[0];

    if( argts.argc > 1 ) {
      has_options_ = true;
    }
  }

  // Set methods for options.

  void cmd_line_parser::set_option( char* opt )
  {
    add_option( opt, CMD_COMMON_OPT );
    values_storage.g_value_counter++;
  }

  void cmd_line_parser::set_option( const char* opt_string, char opt_char )
  {
    add_option( opt_string, CMD_COMMON_OPT );
    add_option( opt_char, CMD_COMMON_OPT );
    values_storage.g_value_counter++;
  }

  void cmd_line_parser::set_flag( const std::string opt_string )
  {
    add_option( opt_string.c_str(), CMD_COMMON_FLAG );
    values_storage.g_value_counter++;
  }

  void cmd_line_parser::set_flag( const char opt_char )
  {
    add_option( opt_char, CMD_COMMON_FLAG );
    values_storage.g_value_counter++;
  }

  void cmd_line_parser::set_flag( const std::string opt_string, char opt_char )
  {
    add_option( opt_string.c_str(), CMD_COMMON_FLAG );
    add_option( opt_char, CMD_COMMON_FLAG );
    values_storage.g_value_counter++;
  }

  void cmd_line_parser::add_option( const char* opt, int type )
  {
    str_storage.options[ str_storage.option_counter ] = opt;
    str_storage.optiontype[ str_storage.option_counter ] = type;
    str_storage.optionindex[ str_storage.option_counter ] = 
     values_storage.g_value_counter;
    str_storage.option_counter++;
  } 

  void cmd_line_parser::add_option( char opt, int type )
  {
    if( !posix() ) {
      print_verbose( opt );
      print_verbose();
      return;
    }

    chars_storage.optionchars[ chars_storage.optchar_counter ] = opt ;
    chars_storage.optchartype[ chars_storage.optchar_counter ] = type ;
    chars_storage.optcharindex[ chars_storage.optchar_counter ] = 
     values_storage.g_value_counter; 
    chars_storage.optchar_counter++;
  }

  void cmd_line_parser::process_options()
  {
    if( !value_store_ok() ) {
      return;
    }
  }

  void cmd_line_parser::process_command_args( int max_args )
  {
    argts.max_legal_args = max_args;
    process_command_args();
  }
 
  void cmd_line_parser::process_command_args( int argc, char* argv[], 
   int max_args )
  {
    argts.max_legal_args = max_args;
    process_command_args( argc, argv );
  }

  void cmd_line_parser::process_command_args( int argc, char* argv[] )
  {
    use_command_args( argc, argv );
    process_command_args();
  }

  void cmd_line_parser::process_command_args()
  {
    if( !( value_store_ok() && command_set() )) {
      return;
    }
	   
    if( argts.max_legal_args == 0 ) {
      argts.max_legal_args = argts.argc;
      argts.new_argv = new int[ argts.max_legal_args + 1 ];
    }

    // Ignore first argv.
    int i = 0;

    for( i = 1 ; i < argts.argc ; i++ ) {

      // Long GNU option.
      if( argts.argv[i][0] == stream.long_opt_prefix[0] && 
           argts.argv[i][1] == stream.long_opt_prefix[1] ) {
        int match_at = parse_gnu( argts.argv[i] + 2 ); // Skip.

        // Found match.
        if( match_at >= 0 && i < argts.argc-1 ) {
          set_value( str_storage.options[match_at], argts.argv[++i] );
        }

        // POSIX char.
      } else if( argts.argv[i][0] == stream.opt_prefix_char ) {

        if( posix() ) { 
          char ch =  parse_posix( argts.argv[i] + 1 ); // Skip.

          // Matching char.
          if( ch != '0' && i < argts.argc-1 ) {
            set_value( ch ,  argts.argv[++i] );
          }

	} else { // Treat it as GNU option with a -.
          int match_at = parse_gnu( argts.argv[i] + 1 ); // Skip '-'.

          // Found match.
          if( match_at >= 0 && i < argts.argc-1 ) {
            set_value( str_storage.options[match_at], argts.argv[++i] );
          }
        }

      } else {
 
        // Not option but an argument keep index.
        if( argts.new_argc < argts.max_legal_args ) {
          argts.new_argv[ argts.new_argc ] = i ;
          argts.new_argc++;
        } else { 
          // Ignore extra arguments.
	  print_verbose( argts.argv[i] );
	  print_verbose();
	  print_auto_usage();
        }

	print_verbose( argts.argv[i] );
	print_auto_usage();
      }
    }

  }

  char cmd_line_parser::parse_posix( char* arg )
  {
    size_t i = 0;

    for( i = 0 ; i < std::strlen( arg ) ; i++ ) { 
      char ch = arg[i];

      // Keep matching flags till an option.
      if( match_char( ch ) ) {

        // If last char argv[++i] is the value.
        if( i == std::strlen( arg )-1 ) { 
          return ch;
	} else {
	  i++; // Skip any '=' and ' '.

          while( arg[i] == stream.whitespace || arg[i] == stream.equalsign ) {
	    i++;
          }

          set_value( ch, arg+i );
          return '0';
	}
      }
    }
    //print_verbose( arg );
    return '0';
  }

  int cmd_line_parser::parse_gnu( char *arg )
  {
    int split_at = 0;

    // If has a '=' sign get value.
    unsigned int i = 0;

    for( i = 0 ; i < std::strlen( arg ) ; i++ ) {
      if( arg[i] == stream.equalsign ) {
        split_at = i ; // Store index.
	i = std::strlen( arg ); // Get out of loop.
      }
    }

    // It is an option value pair.
    if( split_at > 0 ) {
      char* tmp = new char[ split_at+1 ];

      for( int i = 0 ; i < split_at ; i++ ) {
        tmp[i] = arg[i];
      }

      tmp[split_at] = '\0';

      if( match_opt( tmp ) >= 0 ) {
        set_value( str_storage.options[match_opt( tmp )] , arg+split_at+1 );
        delete tmp;
      } else {
	print_verbose( "Unknown command argument option: ", arg );
        delete tmp;
	return -1;
      }

    } else { 
      // Regular options with no '=' sign.
      return match_opt( arg );
    }

    return -1;
  }

  int cmd_line_parser::match_opt( char* opt )
  {
    int i = 0;

    for( ; i < str_storage.option_counter ; i++ ) {
      if( std::strcmp( str_storage.options[i], opt ) == 0 ) {
        // Found option return index.
        if( str_storage.optiontype[i] ==  CMD_COMMON_OPT ||
	     str_storage.optiontype[i] ==  CMD_COMMAND_OPT ) {
          return i;
	} else if( str_storage.optiontype[i] == CMD_COMMON_FLAG
                    || str_storage.optiontype[i] == CMD_COMMAND_FLAG ) {
          // Found flag, set it.
          set_flag_on( opt );
          return -1;
        }
      }
    }
    
    print_verbose( opt  ) ;
    return -1;	
  }

  bool cmd_line_parser::match_char( char c )
  {
    int i = 0;

    for( i = 0 ; i < chars_storage.optchar_counter ; i++ ) {
      // Found match.
      if( chars_storage.optionchars[i] == c ) {

        if( chars_storage.optchartype[i] == CMD_COMMON_OPT 
            || chars_storage.optchartype[i] == CMD_COMMAND_OPT ) {
	  // An option store and stop scanning.
          return true;	
	} else if( chars_storage.optchartype[i] == CMD_COMMON_FLAG 
                   || chars_storage.optchartype[i] == CMD_COMMAND_FLAG ) {
          // A flag store and keep scanning.
          set_flag_on( c );
	  return false;
	}
      }
    }

    print_verbose( c ) ;
    return false;
  }

  bool cmd_line_parser::value_store_ok( )
  {
    int size = 0;

    if( !set_ ) {
      if( values_storage.g_value_counter > 0 ) {
        size = values_storage.g_value_counter* sizeof( char* );
        values_storage.values = new char*[ ( char )size ];

        int i = 0;
	for( i = 0 ; i < values_storage.g_value_counter ; i++ ) {
	  values_storage.values[i] = 0;
        }
	set_ = true;
      }
    }

    return set_;
  }

  // Public get methods.

  char* cmd_line_parser::get_value( const std::string option )
  {
    if( !value_store_ok() ) {
      return 0;
    }

    int i = 0;

    for( ; i < str_storage.option_counter ; i++ ) {
      if( std::strcmp( str_storage.options[i], option.c_str() ) == 0 ) {
        return values_storage.values[ str_storage.optionindex[i] ];
      }
    }

    return 0;
  }

  bool cmd_line_parser::get_flag( const std::string option )
  {
    if( !value_store_ok() ) {
      return false;
    }

    int i = 0;

    for( ; i < str_storage.option_counter ; i++ ) {
      if( std::strcmp( str_storage.options[i], option.c_str() ) == 0 ) {
        return find_flag( values_storage.values[ str_storage.optionindex[i] ] );
      }
    }

    return false;
  }

  char* cmd_line_parser::get_value( char option )
  {
    if( !value_store_ok() ) {
      return 0;
    }

    int i = 0;

    for( ; i < chars_storage.optchar_counter ; i++ ){
      if( chars_storage.optionchars[i] == option ) {
        return values_storage.values[ chars_storage.optcharindex[i] ];
      }
    }

    return 0;
  }

  bool cmd_line_parser::get_flag( char option )
  {
    if( !value_store_ok() ) {
      return false;
    }

    int i = 0;

    for( i = 0 ; i < chars_storage.optchar_counter ; i++ ) {
      if( chars_storage.optionchars[i] == option ) {
        return find_flag( 
          values_storage.values[ chars_storage.optcharindex[i] ] );
      }
    }

    return false;
  }

  bool cmd_line_parser::find_flag( char* val )
  {
    if( val == 0 ) {
      return false;
    }

    if( std::strcmp( CMD_TRUE_FLAG, val ) == 0 ) {
      return true;
    }

    return false;
  }

  bool cmd_line_parser::set_value( const char* option , char* value )
  {
    if( !value_store_ok() ) {
      return false;
    }

    int i = 0;

    for( i = 0; i < str_storage.option_counter ; i++ ) {
      if( std::strcmp( str_storage.options[i], option ) == 0 ) {

        values_storage.values[ str_storage.optionindex[i] ] = 
         new char[ std::strlen( value )+1 ];

        std::strcpy( values_storage.values[ str_storage.optionindex[i] ], 
         value );

	return true;
      }
    }

    return false;
  }

  bool cmd_line_parser::set_flag_on( const char* option )
  {
    if( !value_store_ok() ) {
      return false;
    }
 
    int i = 0;

    for( i = 0; i < str_storage.option_counter ; i++ ) {
      if( std::strcmp( str_storage.options[i], option ) == 0 ) {

        values_storage.values[ str_storage.optionindex[i] ] = 
         new char[ std::strlen( CMD_TRUE_FLAG )+1  ];

        std::strcpy( 
         values_storage.values[ str_storage.optionindex[i] ], CMD_TRUE_FLAG );

	return true;
      }
    }

    return false;
  }

  bool cmd_line_parser::set_value( char option, char* value )
  {
    if( !value_store_ok() ) {
      return false;
    }

    int i = 0;

    for( i = 0; i < chars_storage.optchar_counter ; i++ ) {
      if( chars_storage.optionchars[i] == option ) {

        values_storage.values[ chars_storage.optcharindex[i] ] = 
         new char[ std::strlen( value )+1 ];

        std::strcpy( 
         values_storage.values[ chars_storage.optcharindex[i] ], value );

	return true;
      }
    }

    return false;
  }

  bool cmd_line_parser::set_flag_on( char opt_char )
  {
    if( !value_store_ok() ) {
      return false;
    }

    int i = 0;

    for( i = 0; i < chars_storage.optchar_counter ; i++ ) {
      if( chars_storage.optionchars[i] == opt_char ) {

        values_storage.values[ chars_storage.optcharindex[i] ] = 
         new char[ std::strlen( CMD_TRUE_FLAG )+1 ];

	std::strcpy( 
         values_storage.values[ chars_storage.optcharindex[i] ], 
         CMD_TRUE_FLAG );

        return true;
      }
    }

    return false;
  }

  int cmd_line_parser::get_argc()
  {
    return argts.new_argc;
  }

  char* cmd_line_parser::get_argv( int index )
  {
    if( index < argts.new_argc ){
      return( argts.argv[ argts.new_argv[ index ] ] );
    }

    return 0;
  }

  // Usage and Help methods.

  void cmd_line_parser::print_auto_usage()
  {
    if( auto_usage_ ) {
      print_usage();
    }
  }

  void cmd_line_parser::print_usage()
  {
    int i = 0;

    if( once_ ) {
      once_ = false ;
      //GEN_MSG( "" );
      for( i = 0 ; i < help_storage.usage_lines ; i++ ) {
        GEN_MSG( help_storage.usage[i] );
      }
      //GEN_MSG( "" );
    }
  }

  void cmd_line_parser::add_usage( const std::string desc )
  {
    GEN_MSG( desc );
  }

} 
