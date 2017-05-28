/**
 * @file
 *
 * Definitions for an calendar.
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
#ifndef GENESIS_CALENDAR_HXX
#define GENESIS_CALENDAR_HXX

namespace genesis {
/**
 * Calendars class contains calendar calculations.
 */
class calendar
{
public:
    /**
     * Constructor.
     */
    calendar() {};

    /**
     * Destructor.
     */
    ~calendar() {};

    /// Month days.
    typedef int month_days_[13];

    /// Years end Days.
    typedef long year_end_days_[2];

    /**
     * List type calendars
     */
    enum calendar_type_ {
        T_GREGORIAN = 0,
        T_JULIAN = 1,
        T_HEBREW = 2,
        T_ISLAMIC = 3,
        T_REVOLUTIONARY = 4,
        T_PERSIAN = 5
    };

    /**
     * Get calendar year.
     */
    static int get_calendar_year( long jd, calendar_type_ calendar );

    /**
     * Get Julian ...
     */
    static void get_jul_greg_year_data( int year, long &days,
                                        month_days_& md, bool julian );

    /**
     * Calendar Data.
     */
    static int get_calendar_data( int year, year_end_days_& days,
                                  month_days_& md, calendar_type_ calendar );

private:
    /**
     * Calendar epoch.
     */
    enum calendar_epoch_ {
        E_JULIAN_GREGORIAN = 1721060L,
        E_ISLAMIC = 1948086L,
        E_HEBREW = 347996L,
        E_REVOLUTIONARY = 2375475L
    };

    /**
     * Types.
     */
    enum {
        HALAKIM_IN_DAY = ( 24L * 1080L ),
        JALALI_ZERO = 1947954L,
        LOWER_PERSIAN_YEAR = -1096,
        UPPER_PERSIAN_YEAR = 2327
    };

    /// XXX:
    static int mod( int x, int y )
    {
        return 0;
    }

    /**
     * Islamic calendar.
     */
    static void get_islamic_year_data( int year, long &days_in_year,
                                       month_days_& md );

    /**
     * Hebrew calendar.
     */
    static int lunations_to_tishri1( int year );

    static void lunations_to_days_and_halakim( long lunations,
                                               long &days, long &halakim );

    static void find_tishri1( long year, long &days, long &halakim );

    static void get_hebrew_year_data( long year, year_end_days_& days_in_year,
                                      month_days_& md );

    /**
     * French Revolutionary calendar.
     */
    static int jd_of_french_rev_year( long year );

    static void get_revolutionary_year_data( long year,
                                             year_end_days_& days_in_year,
                                             month_days_& md );

    /**
     * Persian (Jalaali) calendar.
     */
    static long int jalali_jd0( long int jalali_year );

    static void get_jalali_year_data( long int year,
                                      year_end_days_& days_in_year,
                                      month_days_& md );
};

}

#endif // GENESIS_CALENDAR_HXX
