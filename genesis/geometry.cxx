/**
 * @file
 *
 * Implementation for an geometry.
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

#include <genesis/geometry.hxx>
#include <genesis/logger.hxx>

#include <cmath>

namespace genesis {

  int geometry::lint( proto_geo::point_rect_coord p1, 
                      proto_geo::point_rect_coord p2, 
                      proto_geo::point_rect_coord p3, 
                      proto_geo::point_rect_coord p4 )
  {
    double z1 = 0.;
    double z2 = 0.;
    double z3 = 0.;
    double z4 = 0.;

    volatile register int s1 asm ("eax");
    volatile register int s2 asm ("eax");
    volatile register int s3 asm ("eax");
    volatile register int s4 asm ("eax");
    s1 = 0; s2 = 0; s3 = 0; s4 = 0;


    // Perform the quick rejection test.
    if(!( GEN_GEOMETRY_MAX( p1.x, p2.x ) >= GEN_GEOMETRY_MIN( p3.x, p4.x ) && 
          GEN_GEOMETRY_MAX( p3.x, p4.x ) >= GEN_GEOMETRY_MIN( p1.x, p2.x ) && 
          GEN_GEOMETRY_MAX( p1.y, p2.y ) >= GEN_GEOMETRY_MIN( p3.y, p4.y ) && 
          GEN_GEOMETRY_MAX( p3.y, p4.y ) >= GEN_GEOMETRY_MIN( p1.y, p2.y ) )) {
      return 0;
    }

    // Determine whether the line segments straddle each other.
    if(( z1 = (( p3.x - p1.x ) * ( p2.y - p1.y )) - (( p3.y - p1.y ) * 
         ( p2.x - p1.x )) ) < 0 ) {
      s1 = -1;
    } else if( z1 > 0 ) {
      s1 = 1;
    } else {
      s1 = 0;
    }

    if(( z2 = (( p4.x - p1.x ) * ( p2.y - p1.y )) - (( p4.y - p1.y ) * 
         ( p2.x - p1.x ) )) < 0 ) {
      s2 = -1;
    } else if( z2 > 0 ) {
      s2 = 1;
    } else {
      s2 = 0;
    }

    if(( z3 = (( p1.x - p3.x) * ( p4.y - p3.y )) - (( p1.y - p3.y ) * 
         ( p4.x - p3.x ) )) < 0 ) {
      s3 = -1;
    } else if( z3 > 0 ) {
      s3 = 1;
    } else {
      s3 = 0;
    }

    if(( z4 = (( p2.x - p3.x ) * ( p4.y - p3.y )) - (( p2.y - p3.y ) * 
         ( p4.x - p3.x) )) < 0 ) {
      s4 = -1;
    } else if( z4 > 0 ) {
      s4 = 1;
    } else {
      s4 = 0;
    }

    if(( s1 * s2 <= 0 ) && ( s3 * s4 <= 0 )) {
      return 1;
    }

    // Return taht the line segments do not intersects.
    return 0;
  }

  void geometry::arclen( proto_geo::point_spher_coord p1,
                         proto_geo::point_spher_coord p2,
                         double* length, std::string unit )
  {    
    proto_geo::point_rect_coord p1_rct;
    proto_geo::point_rect_coord p2_rct;

    double alpha = 0.;
    double dot = 0.;

    // Convert the spherical coordinates to rectilinear coordinates.
    p1_rct.x = p1.rho * std::sin( p1.phi ) * std::cos( p1.theta );
    p1_rct.y = p1.rho * std::sin( p1.phi ) * std::sin( p1.theta );
    p1_rct.z = p1.rho * std::cos( p1.phi );

    p2_rct.x = p2.rho * std::sin( p2.phi ) * std::cos( p2.theta );
    p2_rct.y = p2.rho * std::sin( p2.phi ) * std::sin( p2.theta );
    p2_rct.z = p2.rho * std::cos( p2.phi );

    // Get the angle between the line segments from the origin to each point.
    dot = ( p1_rct.x * p2_rct.x ) + ( p1_rct.y * p2_rct.y ) + 
          ( p1_rct.z * p2_rct.z );

    alpha = std::acos( dot / std::pow( p1.rho, 2.0 ) );

    // Compute the length of the arc along the spherical surface.
    *length = alpha * p1.rho;

    if( unit == "M" ) {
      // Print in miles.
      *length = *length * 60 * 1.1515;
    } else if( unit == "K") {
      // Print in kilometers.
      *length = *length * 1.609344;
    } else if( unit == "N" ) {
      // Print in nautical miles.
      *length = *length * 0.8684;
    }

    return;
  }

  int geometry::geodist( double lat1, double lon1, double lat2, 
                          double lon2, double* d, std::string unit )
  {
    proto_geo::point_spher_coord p1, p2;

    // Validate the coordinates.
    if( lat1 <  -90.0 || lat1 >  90.0 || lat2 <  -90.0 || lat2 >  90.0 ) {
      GEN_WARN( "Latitude must be within the range of [-90, 90] degrees." );
      return -1;
    }

    if( lon1 < -180.0 || lon1 > 180.0 || lon2 < -180.0 || lon2 > 180.0 ) {
      GEN_WARN( "Longitude must be within the range of [-180, 180] degrees." );
      return -1;
    }

    // Convert each latitude and longitude to spherical coordinates in 
    // radians using the earth's radius for rho.
    p1.rho = GEN_GEOMETRY_EARTH_RADIUS;
    p1.theta = -1.0 * GEN_GEOMETRY_DEGTORAD( lon1 );
    p1.phi = ( GEN_GEOMETRY_DEGTORAD( -1.0 * lat1 ) ) + 
               GEN_GEOMETRY_DEGTORAD( 90.0 );

    p2.rho = GEN_GEOMETRY_EARTH_RADIUS;
    p2.theta = -1.0 * GEN_GEOMETRY_DEGTORAD( lon2 );
    p2.phi = (  GEN_GEOMETRY_DEGTORAD( -1.0 * lat2 ) ) + 
                GEN_GEOMETRY_DEGTORAD( 90.0 );

    // Compute the distance between the points.
    arclen( p1, p2, d, unit );

    return 0;
  }

  double geometry::range_degrees( double angle )
  {
    double temp = 0.0;

    if( angle >= 0.0 && angle < 360.0 ) 
       return angle;

        temp = (int)(angle / 360);
        if (angle < 0.0)
                temp --;
    temp *= 360;
        return angle - temp;

  }

  void geometry::hequ_to_equ( proto_geo::point_nh_equ_posn* hpos,
                              proto_geo::point_equ_posn* pos )
  {
    pos->ra = datetime::hms_to_deg( &hpos->ra );
    pos->dec = datetime::dms_to_deg( &hpos->dec );
  }

  void geometry::hlnlat_to_lnlat( proto_geo::point_nh_lonlat_posn* hpos, 
                                  proto_geo::point_lon_lat_posn* pos )
  {
     pos->lon = datetime::dms_to_deg( &hpos->lon );
     pos->lat = datetime::dms_to_deg( &hpos->lat );
  }
}
