/**
 * @file
 *
 * Calculate the convex hull of a batch of points.
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
#include <genesis/convex_hull.hpp>
#include <genesis/logger.hpp>
#include <genesis/string_util.hpp>
#include <genesis/system.hpp>

class genesis_convex_hull : public genesis::application {
  public:
    /// Constructor.
    genesis_convex_hull() {};

  private:
    // Override.
    int main( int argc, char* argv[] );

    /// Print usage message to console.
    void usage();

    /// Print version message to console.
    void version() const;

  protected:
    /**
     * Computing the Convex Hull of a batch of points.
     *
     * @param n - The latitude of the position.
     * @param xmin - The longitude of the position.
     * @param xmax - The latitude of the position.
     * @param ymin - The longitude of the position.
     * @param ymax - X.
     * @param f - Filename.
     * @param exec - Execute GnuPlot.
     */ 
    void compute_convex_hull( size_t n, int xmin, int xmax, 
     int ymin, int ymax, std::string f, bool exec = false );
};

void genesis_convex_hull::usage() 
{
  add_usage( "Description:" );
  add_usage( "   This application calculate the Convex Hull of a batch of " );
  add_usage( "   points, using Graham Algorithm.\n" );
  add_usage( "Usage: " );
  add_usage( "   [<OPTIONS>] [<NUMBER>] [<XMIN>] [<XMAX>] [<YMIN>] "
             "[<YMAX>]\n" );
  add_usage( "Options:" );
  add_usage( "      --version | -v       Display version information." );
  add_usage( "      --help | -h          Prints this usage message." );
  add_usage( "      --log | -l           Write log message to the screen." );
  add_usage( "      --number | -n        Numbers points generated." );
  add_usage( "      --xmin | -x          Min range of numbers X." );
  add_usage( "      --xmax | -a          Max range of numbers X." );
  add_usage( "      --ymin | -y          Min range of numbers Y." );
  add_usage( "      --ymax | -i          Max range of numbers Y." );
  add_usage( "      --plot | -p          File name plotting." );
  add_usage( "      --gnuplot | -g       Execute GnuPlot (If defined true)" );
  print_usage();
}

void genesis_convex_hull::version() const
{
  std::cout << genesis::string_util::to_uppercase( name() )
            << ":\n\n"
            << "      Version " << VERSION << "." << " Part of the "
            << genesis::string_util::to_uppercase( PACKAGE )
            << " package.\n"
            << std::endl;

  genesis::library::check_build_details();

  std::cout << "\nCopyright (C) 2009 "
            << "Ederson de Moura " << "<" << PACKAGE_BUGREPORT
            << ">."
            << std::endl;
}

void genesis_convex_hull::compute_convex_hull( size_t n, int xmin, int xmax, 
 int ymin, int ymax, std::string f, bool exec )
{
  GEN_MSG( "\nComputing the Convex Hull of a batch of points.\n" );

  bool plot = false;
  std::ofstream gnuplot;

  if( !f.empty() ) {
    plot = true;
    gnuplot.open( f.c_str() );
  }

  genesis::convex_hull cx( n, xmin, xmax, ymin, ymax );

  cx.print_raw_points( gnuplot, std::cout, plot );
  cx.print_partitioned_points( gnuplot, std::cout, plot );
  cx.print_hull( gnuplot, std::cout, plot );

  if( exec ) {
    set_progress( 3000 );
    genesis::system::exec_cmd( "gnuplot-nox " + f );
  }

}

int genesis_convex_hull::main( int argc, char* argv[] )
{
  set_verbose();

  set_flag( "version", 'v' );
  set_flag( "help", 'h' );
  set_flag( "log", 'l' );

  set_option( "number", 'n' );
  set_option( "xmin", 'x' );
  set_option( "xmax", 'a' );
  set_option( "ymin", 'y' );
  set_option( "ymax", 'i' );
  set_option( "plot", 'p' );
  set_option( "gnuplot", 'g' );

  bool ok = false;

  process_command_args( argc, argv );

  if( !has_options() ) {
    usage();
    return ok;
  }

  if( get_flag( "version" ) || get_flag( 'v' ) ) {
    version();
    return ok;
  }

  if( get_flag( "help" ) || get_flag( 'h' ) ) {
    usage();
    return ok;
  }

  if( get_flag( "log" ) || get_flag( 'l' ) ) {
    GEN_LOG( "Log Enabled" );
    return ok;
  }

  std::string number;
  if( get_value( "number" ) != 0 || get_value( 'n' ) != 0 ) {
    number = get_value( 'n' );
  }

  std::string xmin;
  if( get_value( "xmin" ) != 0 || get_value( 'x' ) != 0 ) {
    xmin = get_value( 'x' );
  }

  std::string xmax;
  if( get_value( "xmax" ) != 0 || get_value( 'a' ) != 0 ) {
    xmax = get_value( 'a' );
  }

  std::string ymin;
  if( get_value( "ymin" ) != 0 || get_value( 'y' ) != 0 ) {
    ymin = get_value( 'y' );
  }

  std::string ymax;
  if( get_value( "ymax" ) != 0 || get_value( 'i' ) != 0 ) {
    ymax = get_value( 'i' );
  }

  std::string plot;
  if( get_value( "plot" ) != 0 || get_value( 'p' ) != 0 ) {
    plot = get_value( 'p' );
  }

  bool exec = false;
  std::string gnuplot;
  if( get_value( "gnuplot" ) != 0  || get_value( 'g' ) != 0 ) {
    gnuplot = get_value( 'g' );
    exec = true;
  }

  compute_convex_hull( to_size_t<size_t>( number ), 
                       to_int<int>( xmin ), to_int<int>( xmax ), 
                       to_int<int>( ymin ), to_int<int>( ymax ), plot, exec );
  return 0;
}

int main( int argc, char* argv[] )
{
  return genesis_convex_hull().run( argc, argv );
}
