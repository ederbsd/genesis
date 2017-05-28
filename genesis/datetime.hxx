/**
 * @file
 *
 * Definitions for an datetime.
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
#ifndef GENESIS_DATETIME_HXX
#define GENESIS_DATETIME_HXX

#include <genesis/calendar.hxx>
#include <genesis/proto_types.hxx>

#include <cmath>
#include <ctime>

#ifndef WIN32
extern "C" {
#include <sys/time.h>
}
#endif

namespace genesis {
/**
 * Genesis Time and date operations.
 */
class datetime
{
public:
    /**
     * Constructor.
     */
    datetime() {};

    /**
     * Destructor.
     */
    virtual ~datetime() {};

    /**
     * Current DateTime the system.
     *
     * @return Returns the current datetime.
     */
    static int current_datetime();

    /**
     * Calculate the date from the Julian day.
     *
     * @param JD - Julian day.
     * @param date - Pointer to new calendar date.
     */
    static void get_date( double JD, proto_datetime::date *date );

    /**
     * Set date from system tm structure.
     *
     * @param t - System tm structure.
     * @param date - Pointer to new calendar date.
     */
    static void get_date_from_tm( struct tm *t, proto_datetime::date *date );

    /**
     * Set date from system time.
     *
     * @param t - System time.
     * @param date - Pointer to new calendar date.
     */
    static void get_date_from_timet( time_t *t,
                                     proto_datetime::date *date );

    /**
     * Calculate local date from system date.
     *
     * @param date - Pointer to store date.
     */
    static void get_date_from_sys( proto_datetime::date *date );

    /**
     * Calculate Julian day from time_t.
     *
     * @param in_time - The time_t.
     * @return Julian day.
     */
    static inline double get_julian_from_timet( time_t *in_time )
    {
        return ( double )( 2440587.5 +
                           ( double )( *in_time / ( double ) 86400.0 ));
    };

    /**
     * Calculate time_t from julian day.
     *
     * @param JD - The Julian day.
     * @param in_time - Pointer to store time_t.
     */
    static inline void get_timet_from_julian( double JD, time_t *in_time )
    {
        *in_time = ( time_t )round(( JD - ( double )2440587.5 ) *
                                   ( double )86400.0 );
    };

    /**
     * Calculate the local date from the a MPC packed date.
     * See http://cfa-www.harvard.edu/iau/info/PackedDates.html for info.
     *
     * @param date - New calendar date.
     * @param mpc_date - MPC date.
     * @return 0 for valid date.
     */
    static int get_date_from_mpc( proto_datetime::date *date, char *mpc_date );

    /**
     * Convert hours:mins:secs to degrees.
     *
     * @param hms - Hours, minute, seconds.
     * @return Degrees.
     */
    static double hms_to_deg( proto_datetime::hms *hms );

    /**
     * Convert dms to degrees.
     *
     * @param dms - DMS
     * @return Degrees.
     */
    static double dms_to_deg( proto_datetime::dms *dms );

    /**
     * Convert degress to dms.
     *
     * @param degrees - In degrees.
     * @param dms - DMS.
     */
    static void deg_to_dms( double degrees, proto_datetime::dms *dms );

    /**
     * Convert degrees to hh:mm:ss.
     *
     * @param degrees - Hours, minute, seconds.
     * @param hms - HMS.
     * @return Degrees.
     */
    static void deg_to_hms( double degrees, proto_datetime::hms *hms );

    /**
     * msleep.
     */
    static void msleep( int miliseconds );

private:
    /**
     * Convert a long Julian Day to day/month/year.
     *
     * @param jd - Julian Day to convert.
     * @param day - Where to put the day of the month.
     * @param month - Where to put the month of the year.
     * @param year - Where to put the year.
     * @param calendar - ( optional ) T_GREGORIAN or T_JULIAN,
     * former is the default.
     */
    static void day_to_dmy( double jd, int &day, int &month, int &year,
                            calendar::calendar_type_ calendar = calendar::T_GREGORIAN );
};

/**
 * Genesis Dynamical Time.
 */
class dynamical_time : public datetime
{
public:
    /**
     * Constructor.
     */
    dynamical_time() {};

    /**
     * Destructor.
     */
    ~dynamical_time() {};

    /**
     * Calculates the dynamical time (TD) difference in seconds
     * (delta T) from universal time.
     *
     * @param JD - Julian day.
     * @return TD.
     */
    static double get_dynamical_time_diff( double JD );

    /**
     * Calculates the Julian Ephemeris Day (JDE) from the given
     * julian day.
     *
     * @param JD - Julian day.
     * @return Julian Ephemeris day.
     */
    static double get_jde( double JD );

private:
    /**
     * Stephenson and Houlden for years prior to 948 A.D.
     *
     * @param JD - Julian day.
     */
    static double get_dynamical_diff_sh1( double JD );

    /**
     * Stephenson and Houlden for years between 948 A.D. and 1600 A.D.
     *
     * @param JD - Julian day.
     */
    static double get_dynamical_diff_sh2( double JD );

    /**
     * Table 9.a pg 72 for years 1600..1992. Uses interpolation
     * formula 3.3 on pg 25.
     *
     * @param JD - Julian day.
     */
    static double get_dynamical_diff_table( double JD );

    /**
     * Get the dynamical time diff in the near past / future 1992 .. 2010.
     * Uses interpolation formula 3.3 on pg 25.
     *
     * @param JD - Julian day.
     */
    static double get_dynamical_diff_near( double JD );

    /**
     * Uses equation 9.1 pg 73 to calc JDE for othe JD values.
     *
     * @param JD - Julian day.
     */
    static double get_dynamical_diff_other( double JD );

};

}

#endif // GENESIS_DATETIME_HXX
