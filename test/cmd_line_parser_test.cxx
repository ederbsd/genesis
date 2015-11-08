/**
 * @file
 *
 * Tests for cmd_line_parser class.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/cmd_line_parser.hxx>

#include <iostream>
using namespace std;

void example( int argc, char* argv[] );

int main( int argc, char* argv[] )
{
  example( argc, argv ); 
  return 0 ;
}

void example( int argc, char* argv[] )
{
  using namespace genesis;

  //cmd_line_parser* opt = new cmd_line_parser();

  cmd_line_parser opt;

  opt.add_usage( "" );
  opt.add_usage( "Usage: " );
  opt.add_usage( "" );
  opt.add_usage( " -h  --help  		Prints this help " );
  opt.add_usage( " -s  --size 42 	        Image Size " );
  opt.add_usage( " -z  --zip  		Compress Image " );
  opt.add_usage( " -c   			convert Image " );
  opt.add_usage( "     --name image.jpg	Image Name " );
  opt.add_usage( "" );

  opt.set_flag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */ 
  opt.set_option(  "size", 's' ); /* an option (takes an argument), supporting long and short form */
  opt.set_flag( 'c' );            /* a flag (takes no argument), supporting only short form */

  opt.process_command_args( argc, argv );

  if( !opt.has_options() ) {
    opt.print_usage();
    return;
  }

  if( opt.get_flag( "help" ) || opt.get_flag( 'h' ) ) {
    opt.print_usage();
  }

  if( opt.get_value( 's' ) != NULL  || opt.get_value( "size" ) != NULL ) {
    cout << "Hello" << std::endl;
    cout << "size = " << opt.get_value( 's' ) << endl;
    string val = opt.get_value( 's' );
    cout << val << endl;
    //double *val = ( double* )opt.getValue( 's' );
  }

  if( opt.get_value( "title" ) != NULL )
    cout << "title = " << opt.get_value( "title" ) << endl ;
  if( opt.get_flag( 'c' ) )
    cout << "c = flag set " << endl ;
  if( opt.get_flag( 'z' ) || opt.get_flag( "zip" ) )
    cout << "zip = flag set " << endl ;

  cout << endl ;

  for( int i = 0 ; i < opt.get_argc(); i++ ) {
    cout << "arg = " << opt.get_argv( i ) << endl ;
  }

}
