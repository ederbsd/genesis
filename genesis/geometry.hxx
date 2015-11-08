/**
 * @file
 *
 * Definitions for an geometry.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_GEOMETRY_HPP
#define GENESIS_GEOMETRY_HPP

#include <genesis/datetime.hxx>
#include <genesis/list.hxx>
#include <genesis/logger.hxx>

namespace genesis {

/// Define an approximation for Pi.
#ifndef GEN_GEOMETRY_PI
#define GEN_GEOMETRY_PI 3.1415926535897932384626433832795
#define GEN_GEOMETRY_PI_2 1.5707963267948966192313216916398
#define GEN_GEOMETRY_PI_4 0.78539816339744830961566084581988
#endif

  /**
   * Genesis Geometry Class.
   */ 
  class geometry {
  public:
    /**
     * 
     */
    static int lint( proto_geo::point_rect_coord p1, 
                     proto_geo::point_rect_coord p2, 
                     proto_geo::point_rect_coord p3, 
                     proto_geo::point_rect_coord p4 );

    /**
     *
     */ 
    static void arclen( proto_geo::point_spher_coord p1, 
                        proto_geo::point_spher_coord p2, 
                        double* length, std::string unit );

    /**
     * Approximates the distance between two points on Earth.
     *
     * @param lat1 - The latitude of the position in degrees within 
     *               the range [-90, 90].
     * @param lon1 - The longitude of the position in degrees within 
     *               the range [-180, 180].
     * @param lat2 - The latitude of the position in degrees within 
     *               the range [-90, 90].
     * @param lon2 - The longitude of the position in degrees within 
     *               the range [-180, 180]
     * @param d - Returns the distance, default 0.
     * @param unit -
     */
    static int geodist( double lat1, double lon1, double lat2, 
                         double lon2, double *d, std::string unit );

    /**
     * Computes the volume of an ellipsoidal cap.
     *
     * @param x - The coordinate which determines the ellipsoidal cap.
     * @param a - The x semi-axis (width).
     * @param b - The y semi-axis (depth).
     * @param c - The z semi-axis (height).
     */
    inline static double ellipsoidal_cap( double x, double a, 
                                           double b, double c ) {
      GEN_ASSERT( x >= -c && x <= c );
      return GEN_GEOMETRY_PI * a * b * ( 2.0 * c / 3.0 - x + x * x * x / 
                                       ( 3.0 * c * c ) );
    };

    /**
     * Puts a large angle in the correct range 0 - 360 degrees.
     *
     * @param angle - Angle.
     */ 
    static double range_degrees( double angle );

    /**
     * Human readable equatorial position to double equatorial position.
     *
     * @param hpos - Equatorial coordinates. 
     * @param pos - Equatorial coordinates.
     */
    static void hequ_to_equ( proto_geo::point_nh_equ_posn* hpos, 
                             proto_geo::point_equ_posn* pos );

    /**
     * Human readable longitude and latitude position to double 
     * long/lat position.
     *
     * @param hpos - Hpos. 
     * @param pos - Pos.
     */
    static void hlnlat_to_lnlat( proto_geo::point_nh_lonlat_posn* hpos, 
                                 proto_geo::point_lon_lat_posn* pos );
  };

/// Define macros for comparisons.
#define GEN_GEOMETRY_MIN( x, y ) (( ( x ) < ( y ) ) ? ( x ) : ( y ) )
#define GEN_GEOMETRY_MAX( x, y ) (( ( x ) > ( y ) ) ? ( x ) : ( y ) )

/// Define macros for converting between degrees and radians.
#define GEN_GEOMETRY_DEGTORAD( deg ) (( ( deg ) * 2.0 * GEN_GEOMETRY_PI ) / 360.0 )
#define GEN_GEOMETRY_RADTODEG( rad ) (( ( rad ) * 360.0 ) / ( 2.0 * GEN_GEOMETRY_PI ) )

/// Define the radius of the Earth in nautical miles.
#define GEN_GEOMETRY_EARTH_RADIUS 3440.065

}

#endif // GENESIS_GEOMETRY_HPP
