/**
 * @file
 *
 * Implementation for an datetime.
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

#include <genesis/datetime.hpp>

#include <genesis/geometry.hpp>

#include <cstring>
#include <cstdlib>

static const int DYNAMICAL_TIME_TERMS = 192;

namespace genesis {

  /// Dynamical time in seconds for every second year from 1620 to 1992.
  const static double delta_t[DYNAMICAL_TIME_TERMS] =
  {   
    124.0, 115.0, 106.0, 98.0, 91.0,
    85.0, 79.0, 74.0, 70.0, 65.0,
    62.0, 58.0, 55.0, 53.0, 50.0,
    48.0, 46.0, 44.0, 42.0, 40.0,
    37.0, 35.0, 33.0, 31.0, 28.0,
    26.0, 24.0, 22.0, 20.0, 18.0,
    16.0, 14.0, 13.0, 12.0, 11.0,
    10.0, 9.0, 9.0, 9.0, 9.0,
    9.0, 9.0, 9.0, 9.0, 10.0,
    10.0, 10.0, 10.0, 10.0, 11.0,
    11.0, 11.0, 11.0, 11.0, 11.0,
    11.0, 12.0, 12.0, 12.0, 12.0,
    12.0, 12.0, 13.0, 13.0, 13.0,
    13.0, 14.0, 14.0, 14.0, 15.0,
    15.0, 15.0, 15.0, 16.0, 16.0,
    16.0, 16.0, 16.0, 17.0, 17.0,
    17.0, 17.0, 17.0, 17.0, 17.0,
    17.0, 16.0, 16.0, 15.0, 14.0,
    13.7, 13.1, 12.7, 12.5, 12.5,
    12.5, 12.5, 12.5, 12.5, 12.3,
    12.0, 11.4, 10.6, 9.6, 8.6,
    7.5, 6.6, 6.0, 5.7, 5.6,
    5.7, 5.9, 6.2, 6.5, 6.8,
    7.1, 7.3, 7.5, 7.7, 7.8,
    7.9, 7.5, 6.4, 5.4, 2.9,
    1.6, -1.0, -2.7, -3.6, -4.7,
    -5.4, -5.2, -5.5, -5.6, -5.8,
    -5.9, -6.2, -6.4, -6.1, -4.7,
    -2.7, 0.0, 2.6, 5.4, 7.7,
    10.5, 13.4, 16.0, 18.2, 20.2,
    21.2, 22.4, 23.5, 23.9, 24.3,
    24.0, 23.9, 23.9, 23.7, 24.0,
    24.3, 25.3, 26.2, 27.3, 28.2,
    29.1, 30.0, 30.7, 31.4, 32.2,
    33.1, 34.0, 35.0, 36.5, 38.3,
    40.2, 42.2, 44.5, 46.5, 48.5,
    50.5, 52.2, 53.8, 54.9, 55.8,
    56.9, 58.3
  };

  int datetime::current_datetime()
  {
    time_t current = time( 0 );
    std::cout << ctime( &current ) << std::endl; 
    return 0;
  }

  void datetime::get_date( double JD, proto_datetime::date* date )
  {
     register int A = 0, a = 0, B = 0, 
                  C = 0, D = 0, E = 0;

     double F = 0.0;
     double Z = 0.0;

     JD += 0.5;
     Z = ( int )JD;
     F = JD - Z;

     if( Z < 2299161 ) {
       A = ( int )Z;
     } else {
       a = ( int )(( Z - 1867216.25 ) / 36524.25 );
       A = ( int )( Z + 1 + a - ( int )( a / 4 ));
     }

     B = A + 1524;
     C = ( int )(( B - 122.1 ) / 365.25 );
     D = ( int )( 365.25 * C );
     E = ( int )(( B - D ) / 30.6001 );

     // Get the hms.
     date->hours = ( int )( F * 24 );
     F -= ( double )date->hours / 24;
     date->minutes = ( int )( F * 1440 );
     F -= ( double )date->minutes / 1440;
     date->seconds = F * 86400;

     // Get the day.
     date->days = B - D - ( int )( 30.6001 * E );

     // Get the month.
     if( E < 14 ) {
       date->months = E - 1;
     } else {
       date->months = E - 13;
     }

     // Get the year.
     if( date->months > 2 ) {
       date->years = C - 4716;
     } else {
       date->years = C - 4715;
     }
  }

  void datetime::get_date_from_tm( struct tm* t, proto_datetime::date* date )
  {
    // Fill in date struct.
    date->seconds = t->tm_sec;
    date->minutes = t->tm_min;
    date->hours = t->tm_hour;
    date->days = t->tm_mday;
    date->months = t->tm_mon + 1;
    date->years = t->tm_year + 1900;
  }

  void datetime::get_date_from_timet( time_t* t, proto_datetime::date* date )
  {
    struct tm gmt;

    // Convert to UTC time representation.
    gmtime_r( t, &gmt );
    get_date_from_tm( &gmt, date );
  }

  void datetime::get_date_from_sys( proto_datetime::date* date )
  {
    struct tm * gmt;

#ifndef __WIN32__
    struct timeval tv;
    struct timezone tz;
#else
    time_t now;
#endif

#ifndef __WIN32__
    // Get current time with microseconds precission.
    gettimeofday( &tv, &tz );

    // Convert to UTC time representation.
    gmt = gmtime( &tv.tv_sec );
#else
    now = time( 0 );
    gmt = gmtime( &now );
#endif

    // Fill in date struct.
#ifndef __WIN32__
    date->seconds = gmt->tm_sec + (( double )tv.tv_usec / 1000000 );
#else
    date->seconds = gmt->tm_sec;
#endif
    date->minutes = gmt->tm_min;
    date->hours = gmt->tm_hour;
    date->days = gmt->tm_mday;
    date->months = gmt->tm_mon + 1;
    date->years = gmt->tm_year + 1900;
  }

  int datetime::get_date_from_mpc( proto_datetime::date* date, char* mpc_date )
  {
    char year[3];
    char month[2];
    char day[2];

    // Is mpc_date correct length.
    if( std::strlen( mpc_date ) != 5 ) {
      return -1;
    }

        /* get the century */
        switch (*mpc_date) {
                case 'I':
                        date->years = 1800;
                break;
                case 'J':
                        date->years = 1900;
                break;
                case 'K':
                        date->years = 2000;
                break;
                default:
                        return -1;
        }

        /* get the year */
        year[0] = *(mpc_date + 1);
        year[1] = *(mpc_date + 2);
        year[2] = 0;
        date->years += std::strtol( year, 0, 10 );

        /* month */
        month[0] = *(mpc_date + 3);
        month[1] = 0;
        date->months = strtol (month, 0, 16);

        /* day */
        day[0] = *(mpc_date + 4);
        day[1] = 0;
        date->days = strtol (day, 0, 31);

        /* reset hours,min,secs to 0 */
        date->hours = 0;
        date->minutes = 0;
        date->seconds = 0;
        return 0;
  }

  double datetime::hms_to_deg( proto_datetime::hms* hms )
  {
    double degrees = 0.0;

    degrees = ( ( double )hms->hours / 24 ) * 360;
    degrees += ( ( double )hms->minutes / 60 ) * 15;
    degrees += ( ( double )hms->seconds / 60 ) * 0.25;

    return degrees;
  }

  double datetime::dms_to_deg( proto_datetime::dms* dms )
  {
    double degrees = 0.0;

    degrees =  std::fabs( ( double )dms->degrees );
    degrees += std::fabs( ( double )dms->minutes / 60 );
    degrees += std::fabs( ( double )dms->seconds / 3600 );

    // Is negative?
    if( dms->neg ) {
      degrees *= -1.0;
    }

    return degrees;
  }

  void datetime::deg_to_dms( double degrees, proto_datetime::dms* dms )
  {
    double dtemp;

    if (degrees >= 0)
                dms->neg = 0;
        else
                dms->neg = 1;

        degrees = fabs(degrees);
        dms->degrees = (int)degrees;
        dtemp = degrees - dms->degrees;

    /* divide remainder by 60 to get minutes */
    dms->minutes = dtemp = dtemp * 60;
    dtemp -= dms->minutes;

    /* divide remainder by 60 to get seconds */
    dms->seconds = dtemp * 60;

    /* catch any overflows */
    if (dms->seconds > 59) {
        dms->seconds = 0;
        dms->minutes ++;
    }
    if (dms->minutes > 59) {
        dms->minutes = 0;
        dms->degrees ++;
    }

  }

  void datetime::deg_to_hms( double degrees, proto_datetime::hms* hms )
  {
    double dtemp;

    degrees = geometry::range_degrees( degrees );

        /* divide degrees by 15 to get the hours */
    hms->hours = dtemp = degrees / 15.0;
    dtemp -= hms->hours;

    /* divide remainder by 60 to get minutes */
    hms->minutes = dtemp = dtemp * 60.0;
    dtemp -= hms->minutes;

    /* divide remainder by 60 to get seconds */
    hms->seconds = dtemp * 60.0;

    /* catch any overflows */
    if (hms->seconds > 59) {
        hms->seconds = 0;
        hms->minutes ++;
    }
    if (hms->minutes > 59) {
        hms->minutes = 0;
        hms->hours ++;
    }

  }

  void datetime::msleep( int miliseconds )
  {    
    clock_t end_wait = 0;
    end_wait = clock() + miliseconds * CLOCKS_PER_SEC / 1000;
    while( clock() < end_wait ) {}
  }

  double dynamical_time::get_dynamical_diff_sh1( double JD )
  {
    double TD = 0.0;
    double E = 0.0;
    
    // Number of centuries from 948.
    E = ( JD - 2067314.5 ) / 36525.0;
    TD = 1830.0 - 405.0 * E + 46.5 * E * E;

    return TD;
  }

  double dynamical_time::get_dynamical_diff_sh2( double JD )
  {
    double TD = 0.0;
    double t = 0.0;
    
    // Number of centuries from 1850.
    t = ( JD - 2396758.5 ) / 36525.0;
    TD = 22.5 * t * t;

    return TD;
  }

  double dynamical_time::get_dynamical_diff_table( double JD )
  {
    double TD = 0;

    double a = 0.0, b = 0.0,
           c = 0.0, n = 0.0;

    register int i = 0;
    
    // Get no days since 1620 and divide by 2 years.
    i = ( int )(( JD - 2312752.5 ) / 730.5 );
    
    // Get the base interpolation factor in the table.
    if( i > ( DYNAMICAL_TIME_TERMS - 2 ) )
        i = DYNAMICAL_TIME_TERMS - 2;
	
	// Calc a,b,c,n.
	a = delta_t[i+1] - delta_t[i];
	b = delta_t[i+2] - delta_t[i+1];
	c = a - b;
	n = (( JD - ( 2312752.5 + ( 730.5 * i ))) / 730.5 );
	
	TD = delta_t[i+1] + n / 2 * (a + b + n * c);

    return TD;
  }

  double dynamical_time::get_dynamical_diff_near( double JD )
  {
    double TD = 0;
    /* TD for 1990, 2000, 2010 */
    double delta_T[3] = {56.86, 63.83, 70.0};
    double a,b,c,n;
         
    /* calculate TD by interpolating value */
    a = delta_T[1] - delta_T[0];
    b = delta_T[2] - delta_T[1];
    c = b - a;
    
    /* get number of days since 2000 and divide by 10 years */
	n = (JD - 2451544.5) / 3652.5; 
	TD = delta_T[1] + (n / 2) * (a + b + n * c);
	     
    return TD;
  }

  double dynamical_time::get_dynamical_diff_other( double JD )
  {
    double TD;
    double a;
    
    a = (JD - 2382148);
    a *= a;

    TD = -15 + a / 41048480;
       
    return TD;
  }

  double dynamical_time::get_dynamical_time_diff( double JD )
  {
    double TD;

    /* check when JD is, and use corresponding formula */
    /* check for date < 948 A.D. */
    if ( JD < 2067314.5 )
        /* Stephenson and Houlden */
	    TD = get_dynamical_diff_sh1 (JD);
    else if ( JD >= 2067314.5 && JD < 2305447.5 )
	    /* check for date 948..1600 A.D. Stephenson and Houlden */
    	TD = get_dynamical_diff_sh2 (JD);
	else if ( JD >= 2312752.5 && JD < 2448622.5 )
		/* check for value in table 1620..1992  interpolation of table */
		TD = get_dynamical_diff_table (JD);
	else if ( JD >= 2448622.5 && JD <= 2455197.5 )
		/* check for near future 1992..2010 interpolation */
		TD = get_dynamical_diff_near (JD);       
	else
	    /* other time period outside */
	    TD = get_dynamical_diff_other (JD);   	    
		    
	return TD;
  }

  double dynamical_time::get_jde( double JD )
  {
    double JDE = 0.0;
    double secs_in_day = 24 * 60 * 60;
    
    JDE = JD +  get_dynamical_time_diff (JD) / secs_in_day;
    
    return JDE;
  }

}

