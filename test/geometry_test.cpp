/**
 * @file
 *
 * Implementation for an geometry class.
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

#include <genesis/geometry.hpp>
#include <genesis/tests.hpp>

// Test method geodist.
static int geodist_test( void )
{
  double lat1 = 0.0;
  double lon1 = 0.0;
  double lat2 = 0.0;
  double lon2 = 0.0;

  double distance = 0.0;

  // For tests.
  int failed = 0;

  // Test computing distances between points on Earth.
  GEN_MSG( "Computing distances between points on Earth.\n" );

  // SFO (San Francisco)
  lat1 = 37.62;
  lon1 = 122.38;

  // LAX (Los Angeles)
  lat2 = 33.94;
  lon2 = 118.41;

  GEN_TRUE_OR_ERROR( genesis::geometry::geodist( lat1, lon1, lat2, 
                      lon2, &distance, "" ) == 0, "Error Geometry Geodist!" );

  fprintf( stdout, "SFO: (%+07.2lf,%+07.2lf)\n", lat1, lon1 );
  fprintf( stdout, "LAX: (%+07.2lf,%+07.2lf)\n", lat2, lon2 );
  fprintf( stdout, "distance = %f\n\n", distance );

  failed += genesis::tests::result( "(Geometry Geodist) Calculing distance "
                                    "SFO -> LAX: ", distance, 293.554, 0.001 );

  // CDG (Paris)
  lat1 = 49.01;
  lon1 = -2.55;

  // PER (Perth)
  lat2 = -31.94;
  lon2 = -115.97;

  GEN_TRUE_OR_ERROR( genesis::geometry::geodist( lat1, lon1, lat2,
                      lon2, &distance, "" ) == 0, "Error Geometry Geodist!" );

  fprintf( stdout, "CDG: (%+07.2lf,%+07.2lf)\n", lat1, lon1 );
  fprintf( stdout, "PER: (%+07.2lf,%+07.2lf)\n", lat2, lon2 );
  fprintf( stdout, "distance = %f\n\n", distance );

  failed += genesis::tests::result( "(Geometry Geodist) Calculing distance " 
                                    "CDG -> PER: ", distance, 7706.63, 0.01 );

  // NYK (NewYork)
  lat1 = 40.47;
  lon1 = 73.58;

  // LDN (London)
  lat2 = 51.32;
  lon2 = 0.5;

  GEN_TRUE_OR_ERROR( genesis::geometry::geodist( lat1, lon1, lat2,
                      lon2, &distance, "" ) == 0, "Error Geometry Geodist!" );

  fprintf( stdout, "NYK: (%+07.2lf,%+07.2lf)\n", lat1, lon1 );
  fprintf( stdout, "LDN: (%+07.2lf,%+07.2lf)\n", lat2, lon2 );
  fprintf( stdout, "distance = %f\n\n", distance );

  failed += genesis::tests::result( "(Geometry Geodist) Calculing distance "
                                    "NYK -> LDN: ", distance, 2991.84, 0.01 );

  // RJO (Rio de Janeiro)
  lat1 = -22.0;
  lon1 = 43.0;

  // SPO (Sao Paulo)
  lat2 = -23.0;
  lon2 = 46.0;

  GEN_TRUE_OR_ERROR( genesis::geometry::geodist( lat1, lon1, lat2,
                      lon2, &distance, "" ) == 0, "Error Geometry Geodist!" );

  fprintf( stdout, "RJO: (%+07.2lf,%+07.2lf)\n", lat1, lon1 );
  fprintf( stdout, "SPO: (%+07.2lf,%+07.2lf)\n", lat2, lon2 );
  fprintf( stdout, "distance = %f\n\n", distance );

  failed += genesis::tests::result( "(Geometry Geodist) Calculing distance " 
                                    "RJO -> SPO: ", distance, 176.905, 0.001 );

  // SPO (Sao Paulo)
  lat1 = -23.0;
  lon1 = 46.0;

  // RJO (Rio de Janeiro)
  lat2 = -22.0;
  lon2 = 43.0;

  GEN_TRUE_OR_ERROR( genesis::geometry::geodist( lat1, lon1, lat2,
                      lon2, &distance, "" ) == 0, "Error Geometry Geodist!" );

  fprintf( stdout, "SPO: (%+07.2lf,%+07.2lf)\n", lat1, lon1 );
  fprintf( stdout, "RJO: (%+07.2lf,%+07.2lf)\n", lat2, lon2 );
  fprintf( stdout, "distance = %f\n\n", distance );

  failed += genesis::tests::result( "(Geometry Geodist) Calculing distance "
                                    "SPO -> RJO: ", distance, 176.905, 0.001 );

  GEN_MSG( "End: Geometry Geodist.\n" );

  return failed;
}

// Test method ellipsoidal cap.
static int ellipsoidal_cap_test( void )
{
  GEN_MSG( "Compute ellipsoidal cap.\n" );

  // The x semi-axis.
  double a = 10.5;

  // The y semi-axis.
  double b = 5.2;
 
  // The z semi-axis.
  double c = 3;

  // The x value.
  double x = 0.0;
 
  // For tests.
  int failed = 0;

  // Display the lengths of the semi-axes.
  printf( "a = %.1lf\nb = %.1lf\nc = %.1lf\n\n", a, b, c );
 
  // Display the volume for different values of x.
  for( x = c; x >= -c; x -= 0.5 ) {
    printf( "x = %4.1lf    V = %.1lf \n", x, 
             genesis::geometry::ellipsoidal_cap( x, a, b, c ) );
  }
  
  GEN_MSG( "" );

  failed += genesis::tests::result( "(Geometry Ellipsoidal Cap) Value X: ",
                                    x, -3.5, -0.0 );

  GEN_MSG( "End: Ellipsoidal Cap.\n" );

  return failed;
}

int main( int argc, char *argv[] ) 
{
  int failed = 0;

  failed += geodist_test();
  failed += ellipsoidal_cap_test();

  genesis::tests::print_result( "geometry", failed );

  return( failed > 0 );
}
