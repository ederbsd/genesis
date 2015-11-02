/**
 * @file
 *
 * Calcule distance lat lon.
 *
 * Copyright (c) 2009-2015 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/application.hpp>
#include <genesis/genesis.hpp>
#include <genesis/geometry.hpp>
#include <genesis/logger.hpp>
#include <genesis/string_util.hpp>

#include <genesis/config.hpp>

class genesis_geodist : public genesis::application {
  public:
    /// Constructor.
    genesis_geodist() { 
      this->enable_color_ = false;
    };

  private:
    // Override.
    int main( int argc, char* argv[] );

    /// Print usage message to console.
    void usage();

    /// Print version message to console.
    void version() const;

  protected:
    /**
     * Computing distances between points on Earth.
     *
     * @param lat1 - The latitude of the position.
     * @param lon1 - The longitude of the position.
     * @param lat2 - The latitude of the position.
     * @param lon2 - The longitude of the position.
     * @param unit - The unit you desire for results.
     */ 
    void compute_geodist( double lat1, double lon1, double lat2, double lon2, std::string unit );

    /**
     * Read values the config file.
     */
    void read_conf();

    double lat1_conf_; ///< Conf file. The latitude of the position.
    double lon1_conf_; ///< Conf file. The longitude of the position.
    double lat2_conf_; ///< Conf file. The latitude of the position.
    double lon2_conf_; ///< Conf file. The longitude of the position.
    std::string unit_conf_; ///< Conf file. The unit you desire for results .
 
    bool enable_color_; ///< Enable color ansi in console.
};

void genesis_geodist::usage() 
{
  if( enable_color_ ) {
    set_ansi_color( std::cout, 6 );
  }

  add_usage( "Description:" );
  add_usage( "   This application computing distances between points on Earth.\n" );
  add_usage( "Usage: " );
  add_usage( "   [<OPTIONS>] [<LAT1>] [<LON1>] [<LAT2>] [<LON2>]\n" );
  add_usage( "Options:" );
  add_usage( "      --version | -v       Display version information." );
  add_usage( "      --help | -h          Prints this usage message." );
  add_usage( "      --log | -l           Write log message to the screen." );
  add_usage( "      --color | -p         Enable output color in console." );
  add_usage( "      --lat1 | -a          The latitude of the position in "
             "degrees within\n"
             "                           the range [-90, 90]." );
  add_usage( "      --lon1 | -b          The longitude of the position in "
             "degrees within\n"
             "                           the range [-180, 180]." );
  add_usage( "      --lat2 | -c          The latitude of the position in "
             "degrees within\n"
             "                           the range [-90, 90]." );
  add_usage( "      --lon2 | -d          The longitude of the position in "
             "degrees within\n"
             "                           the range [-180, 180]." );
  add_usage( "      --unit | -u          The unit you desire for results. Where:\n" 
             "                           'M' is miles\n"
             "                           'K' is kilometers\n"
             "                           'N' is nautical miles.");
  add_usage( "      --conf | -f          Read options from conf file name." );
  set_restore_ansi_color();
  print_usage();
}

void genesis_geodist::version() const
{
  std::cout << genesis::string_util::to_uppercase( name() )
            << ":\n\n"
            << "      Version " << VERSION << "." << " Part of the " 
            << genesis::string_util::to_uppercase( PACKAGE ) 
            << " package.\n"
            << std::endl;

  genesis::library::check_build_details();

  std::cout << "\nCopyright (C) 2009-2015 "
            << "Ederson de Moura " << "<" << PACKAGE_BUGREPORT
            << ">."
            << std::endl;
}

void genesis_geodist::compute_geodist( double lat1, double lon1, double lat2, 
 double lon2, std::string unit )
{
  GEN_MSG( "\nComputing distances between points on Earth.\n" );

  double distance = 0.0;

  GEN_TRUE_OR_ERROR( genesis::geometry::geodist( lat1, lon1, lat2,
                      lon2, &distance, unit ) == 0, "Error Geometry Geodist!" );

  fprintf( stdout, "City1: (%+07.2lf,%+07.2lf)\n", lat1, lon1 );
  fprintf( stdout, "City2: (%+07.2lf,%+07.2lf)\n", lat2, lon2 );
  fprintf( stdout, "distance = %f\n\n", distance );
}

void genesis_geodist::read_conf()
{
  genesis::config cf( "genesis_geodist.conf" );

  lat1_conf_ = cf.read<double>( "lat1", 0.0 );
  lon1_conf_ = cf.read<double>( "lon1", 0.0 );

  lat2_conf_ = cf.read<double>( "lat2", 0.0 );
  lon2_conf_ = cf.read<double>( "lon2", 0.0 );

  unit_conf_ = cf.read<std::string>( "unit" );
}

int genesis_geodist::main( int argc, char* argv[] )
{
  set_verbose();

  set_flag( "version", 'v' );
  set_flag( "help", 'h' );
  set_flag( "log", 'l' );
  set_flag( "conf", 'f' );
  set_flag( "color", 'p' );
 
  set_option( "lat1", 'a' );
  set_option( "lon1", 'b' );
  set_option( "lat2", 'c' );
  set_option( "lon2", 'd' );
  set_option( "unit", 'u' );

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

  if( get_flag( "conf" ) != 0  || get_flag( 'f' ) != 0 ) {
    read_conf();
    compute_geodist( lat1_conf_, lon1_conf_, lat2_conf_, lon2_conf_, unit_conf_ );
    return ok;
  }

  if( get_flag( "color" ) != 0 || get_flag( 'p' ) != 0 ) {
    enable_color_ = true;
  }

  std::string lat1;
  if( get_value( "lat1" ) != 0 || get_value( 'a' ) != 0 ) {
    lat1 = get_value( 'a' );
  }

  std::string lon1;
  if( get_value( "lon1" ) != 0 || get_value( 'b' ) != 0 ) {
    lon1 = get_value( 'b' );
  }

  std::string lat2;
  if( get_value( "lat2" ) != 0 || get_value( 'c' ) != 0 ) {
    lat2 = get_value( 'c' );
  }

  std::string lon2;
  if( get_value( "lon2" ) != 0 || get_value( 'd' ) != 0 ) {
    lon2 = get_value( 'd' );
  }

  std::string unit;
  if( get_value( "unit" ) != 0 || get_value( 'u' ) != 0 ) {
    unit = get_value( 'u' );
  }

  compute_geodist( to_double<double>( lat1 ), to_double<double>( lon1 ),
                   to_double<double>( lat2 ), to_double<double>( lon2 ), unit );

  return exit_success;
}

int main( int argc, char* argv[] )
{
  return genesis_geodist().run( argc, argv );
}
