/**
 * @file
 *
 * Implementations for an calendar.
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

#include <genesis/calendar.hxx>

#include <cstring>

namespace genesis {

  // Variable used for calendar Hebrew.
  static const int is_hebrew_leap_year[19] = { 0, 0, 1, 0, 0, 1,
                                               0, 1, 0, 0, 1, 0, 
                                               0, 1, 0, 0, 1, 0, 1 };

  int calendar::get_calendar_year( long jd, calendar_type_ calendar ) 
  {
    int year = -1;
    
    switch( calendar ) {

      case T_GREGORIAN:

      case T_JULIAN:
        year = ( jd - E_JULIAN_GREGORIAN ) / 365L;
        break;

      case T_HEBREW:
        year = ( jd - E_HEBREW ) / 365L;
        break;

      case T_ISLAMIC:
        year = ( jd - E_ISLAMIC ) / 354L;
        break;

      case T_REVOLUTIONARY:
        year = ( jd - E_REVOLUTIONARY ) / 365L;
        break;

      case T_PERSIAN:
        year = ( jd - JALALI_ZERO ) / 365L;

        if( year < LOWER_PERSIAN_YEAR ) {
          year = LOWER_PERSIAN_YEAR;
        }

        if( year > UPPER_PERSIAN_YEAR ) {
          year = UPPER_PERSIAN_YEAR;
        }

        break;

      default: // Undefined calendar.
        break;
    }

    return year;
  }

  void calendar::get_jul_greg_year_data( int year, long& daysInYear, 
                                          month_days_& md, bool julian )
  {
    static const month_days_ months = { 31, 28, 31, 30, 31, 30, 
                                        31, 31, 30, 31, 30, 31, 0 };

    if( year >= 0L ) {
      daysInYear = year * 365L + year / 4L;

      if( !julian ) { 
        daysInYear += -year / 100L + year / 400L;
      }

    } else {
      daysInYear = ( year * 365L ) + ( year - 3L ) / 4L;

      if( !julian ) {
        daysInYear += -( year - 99L ) / 100L + ( year - 399L ) / 400L;
      }
    }

    if( julian ) {
      daysInYear -= 2L;
    }

    std::memcpy( &md, months, sizeof( month_days_ ) );

    if( !( year % 4 ) ) {
      if( ( year % 100L ) || !( year % 400L ) || julian ) {
        md[1] = 29;
        daysInYear--;
      }
    }

    daysInYear += E_JULIAN_GREGORIAN + 1;
  }

  int calendar::get_calendar_data( int year, year_end_days_& days, 
                                    month_days_& md, calendar_type_ calendar )
  {
    int rval = 0;

    std::memset( &md, 0, sizeof( month_days_ ) );
 
    switch( calendar ) {

      case T_GREGORIAN:

      case T_JULIAN:
        get_jul_greg_year_data( year, days[0], md, ( T_JULIAN == calendar ) );
        break;

      case T_ISLAMIC:
        get_islamic_year_data( year, days[0], md );
        break;

      case T_HEBREW:
        get_hebrew_year_data( year, days, md );
        break;

      case T_REVOLUTIONARY:
        get_revolutionary_year_data( year, days, md );
        break;

      case T_PERSIAN:
        if( year >= LOWER_PERSIAN_YEAR && year <= UPPER_PERSIAN_YEAR ) {
          get_jalali_year_data( year, days, md );
        } else {
          rval = -1;
        }
        break;

      default:
        rval = -1;
        break;
    }

    if( 0 == rval ) {
      // days[1] = JD of "New Years Eve" + 1;  that is, New Years Day of the
      // following year. If you have days[0] <= JD < days[1], JD is in the
      // current year.
      days[1] = days[0];

      int i = 0;
      for( ; i < 13; i++ ) {
        days[1] += md[i];
      }
    }

    return( rval );
  }
 
  void calendar::get_islamic_year_data( int year, long& days_in_year, 
                                         month_days_& md )
  {
    static const long THIRTY_ISLAMIC_YEARS = 10631L;

    static const int is_islamic_leap_year[30] = { 0, 0, 1, 0, 0, 
                                                  1, 0, 1, 0, 0,
                                                  1, 0, 0, 1, 0, 
                                                  0, 1, 0, 1, 0,
                                                  0, 1, 0, 0, 1, 
                                                  0, 1, 0, 0, 1 };

    long year_within_cycle = mod( year, 30L );
    long thirty_year_cycles = ( year - year_within_cycle ) / 30L;
    long rval = E_ISLAMIC + thirty_year_cycles * 
                THIRTY_ISLAMIC_YEARS + year_within_cycle * 354L;

    md[12] = 0;
    md[11] = 29 + is_islamic_leap_year[year_within_cycle];

    while( year_within_cycle-- ) {
      rval += long( is_islamic_leap_year[year_within_cycle] );
    }
   
    days_in_year = rval;
 
    // The Islamic calendar alternates between 30-day and 29-day
    // months for the first eleven months; the twelfth is 30
    // days in a leap year, 29 otherwise (see above).
    int i = 0;
    for( ;i < 11; i++ ) {
      md[i] = 30 - ( i % 2 );
    }
  }

  int calendar::lunations_to_tishri1( int year ) 
  {
    long year_within_cycle = mod( year - 1, 19L );
    long full_nineteen_year_cycles = ( year - 1 - year_within_cycle ) / 19L;
    long rval = full_nineteen_year_cycles * 235L + year_within_cycle * 12L;

    int y = 0;
    for( ;y < year_within_cycle; y++ ) {
      rval += is_hebrew_leap_year[y];
    }

    return rval;
  }
 
  void calendar::lunations_to_days_and_halakim( long lunations, 
                                                 long& days, long& halakim )
  {
    long lunation_within_glumph = mod( lunations, 25920L );

    long curr_glumph = ( lunations - lunation_within_glumph ) / 25920L;

    days += curr_glumph * 765433L + lunation_within_glumph * 29L;
    halakim += lunation_within_glumph * 13753L;

    // Now make sure excess halakim carry over correctly
    days += halakim / HALAKIM_IN_DAY;
    halakim %= HALAKIM_IN_DAY;
  }

  void calendar::find_tishri1( long year, long& days, long& halakim )
  {
    //  Set days and halakim to the 'epoch': 1 Tishri 1 = 2 5604
    days = 2L;
    halakim = 5604L;
    lunations_to_days_and_halakim( lunations_to_tishri1( year ), 
                                    days, halakim );
  }

  void calendar::get_hebrew_year_data( long year, year_end_days_& days_in_year,
                                        month_days_& md )
  {
    int i = 0;

    for( ;i < 2; i++ ) {
      long day = 0;
      long halakim = 0;

      find_tishri1( year + i, day, halakim );

      // Check dehiyyah (c):
      if( 3 == mod( day, 7L ) && 
           halakim >= 9L * 1080L + 204L && 
            !is_hebrew_leap_year[ mod( year - 1 + i, 19L ) ] ) {
        day += 2;
      } else if( mod( day, 7L ) == 2 && // Check dehiyyah (d):
                  halakim >= 15L * 1080L + 589L &&
                   is_hebrew_leap_year[ mod( year - 2 + i, 19L ) ] ) {
          day++;
      } else {
          if( halakim > 18L * 1080L ) {
            day++;
          }

          if( mod( day, 7L ) == 1 || 
              mod( day, 7L ) == 4 ||
              mod( day, 7L ) == 6L ) {
            day++;
         }
      }
      days_in_year[i] = day + E_HEBREW;
    }

    int year_length = int( days_in_year[1] - days_in_year[0] );

    if( 0 != md[0] ) {
      for( int i = 0; i < 6; i++ ) { // Normal lengths.
        md[i] = md[i + 7] = ( char )( 30 - ( i & 1 ) );
      }

      if( is_hebrew_leap_year[ mod( year - 1, 19L) ] ) {
        md[5] = 30; // Adar I is bumped up a day in leap years.
        md[6] = 29;
      } 
    } else {

      md[6] = 0; // Exist at all; set it to zero days.

      if( year_length == 353 || year_length == 383 ) { // Deficient year.
        md[2] = 29;
      }

      if( year_length == 355 || year_length == 385 ) { // Complete year.
        md[1] = 30;
      }
    }

  }

  int calendar::jd_of_french_rev_year( long year )
  {
    long rval = E_REVOLUTIONARY + year * 365L;

    if( year >= 20 ) {
      year--;
    }

    rval += long( year / 4 - year / 100 + year / 400 );
    //rval += long( year / 4 - year / 128 );

    if( year <= 0L ) {
      rval--;
    }

    return rval;
  }

  void calendar::get_revolutionary_year_data(  long year, 
                                               year_end_days_& days_in_year,
                                               month_days_& md )
  {
    days_in_year[0] = jd_of_french_rev_year( year );
    days_in_year[1] = jd_of_french_rev_year( year + 1 );

    // There are twelve months of 30 days each,  followed by
    // five (leap years,  six) days;  call 'em an extra
    // thirteenth "month", containing all remaining days:
    int i = 0;

    for( ; i < 12; i++ ) {
      md[i] = 30;
    }

    md[12] = ( days_in_year[1] - days_in_year[0] - 360L );
  }

  long int calendar::jalali_jd0( long int jalali_year )
  {
    static const int breaks[12] = { -708, -221, -3, 6, 394, 720,
                                     786, 1145, 1635, 1701, 1866, 2328 };

    static const int deltas[12] = { 1108, 1047, 984, 1249, 952, 
                                    891, 930, 866, 869, 844, 848, 852 };
    long rval = -1L;

    if( jalali_year >= LOWER_PERSIAN_YEAR ) {
      int i = 0;
      for( ; i < 12; i++ ) {
        if( jalali_year < breaks[i] ) {
          rval = JALALI_ZERO + jalali_year * 365L + 
                 ( deltas[i] + jalali_year * 303L ) / 1250L;
          if( i < 3 ) {
            rval--;
          }
        break;
        }
      }
    }
    return rval;
  }

  void calendar::get_jalali_year_data( long int year, 
                                        year_end_days_& days_in_year, 
                                        month_days_& md )
  {
    if( year < LOWER_PERSIAN_YEAR || year > UPPER_PERSIAN_YEAR ) {
      return;
    }

    days_in_year[0] = jalali_jd0( year) + 1L;
    days_in_year[1] = jalali_jd0( year + 1L ) + 1L;

    // The first six months have 31 days.
    // The next five have 30 days.
    // The last month has 29 days in ordinary years, 
    // 30 in leap years.
    int i = 0;

    for( ;i < 6; i++ ) {
      md[i] = 31;
    }

    i = 6;
    for( ;i < 11; i++ ) {
      md[i] = 30;
    }

    md[11] = ( days_in_year[1] - days_in_year[0] - 336L );
  }

}
