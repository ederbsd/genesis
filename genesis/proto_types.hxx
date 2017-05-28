/**
 * @file
 *
 * Definitions for an proto_types.
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
#ifndef GENESIS_PROTO_TYPES_HXX
#define GENESIS_PROTO_TYPES_HXX

#include <cstdlib>

namespace genesis {
/**
 * Definitions for list.
 */
namespace proto_list {
/**
 * Definitions of the structure elements to the
 * list enchained.
 */
typedef struct elements_ {
    void *data;
    struct elements_ *next;
} elements;

/**
 * Definitions of structure for linked lists.
 */
typedef struct linked_ {
    int size;
    int ( *match ) ( const void *key1, const void *key2 );
    void ( *destroy ) ( void *data );
    elements *head;
    elements *tail;
} linked;

/// Surname to set.
typedef linked set_list_linked;

/**
 * Defines for the subsets identified by a key.
 */
typedef struct set_cover_key_ {
    void *key;
    set_list_linked set;
} cover_key;

}

/**
 * Definitions for bitree.
 */
namespace proto_bitree {
/**
 * Define a structure for binary tree nodes.
 */
typedef struct node_ {
    void *data;
    struct node_ *left;
    struct node_ *right;
} node_avl;

/**
 * Define a structure for binary trees.
 */
typedef struct tree_ {
    int size;
    int ( *compare )( const void *key1, const void *key2 );
    void ( *destroy )( void *data );
    node_avl *root;
} tree;

}

/**
 * Definitions for datetime.
 */
namespace proto_datetime {
/**
 * This is the Human readable (easy printf) date format used
 * by Genesis. It's always in UTC. For local time, please use
 * zonedate.
 */
typedef struct date_ {
    int years;      ///< Years. All values are valid.
    int months;     ///< Months. Valid values : 1 (January) - 12 (December).
    int days;       ///< Days. Valid values 1 - 28,29,30,31 Depends on month.
    int hours;      ///< Hours. Valid values 0 - 23.
    int minutes;    ///< Minutes. Valid values 0 - 59.
    double seconds; ///< Seconds. Valid values 0 - 59.99999...
} date;

/**
 * This is the Human readable (easy printf) date with timezone format
 * used by Genesis.
 */
typedef struct zonedate_ {
    int years;      ///< Years. All values are valid.
    int months;     ///< Months. Valid values : 1 (January) - 12 (December).
    int days;       ///< Days. Valid values 1 - 28,29,30,31 Depends on month.
    int hours;      ///< Hours. Valid values 0 - 23.
    int minutes;    ///< Minutes. Valid values 0 - 59.
    double seconds; ///< Seconds. Valid values 0 - 59.99999...
    long gmtoff;    ///< Timezone offset. Seconds east of UTC. Valid 0..86400.
} zonedate;

/**
 * Human readable Angle in degrees, minutes and seconds.
 */
typedef struct dms_ {
    unsigned short neg;     ///< Non zero if negative.
    unsigned short degrees; ///< Degrees. Valid 0 - 360.
    unsigned short minutes; ///< Minutes. Valid 0 - 59.
    double seconds;         ///< Seconds. Valid 0 - 59.9999...
} dms;

/**
 * Hours, minutes and seconds. Human readable Angle in hours,
 * minutes and seconds.
 */
typedef struct hms_ {
    unsigned short hours;   ///< Hours. Valid 0 - 23.
    unsigned short minutes; ///< Minutes. Valid 0 - 59.
    double seconds;         ///< Seconds. Valid 0 - 59.9999...
} hms;

}

/**
 * Definitions for Geometry.
 */
namespace proto_geo {
/**
 * Rectangular Coordinates of a body. These coordinates can be
 * either geocentric or heliocentric.
 *
 * A heliocentric position is an objects position relative to the
 * centre of the Sun.
 * A geocentric position is an objects position relative to the centre
 * of the Earth.
 *
 * Position is in units of AU for planets and in units of km
 * for the Moon.
 */
typedef struct point_rect_coord_ {
    double x; ///< Rectangular X coordinate.
    double y; ///< Rectangular Y coordinate.
    double z; ///< Rectangular Z coordinate.
} point_rect_coord;

/**
 * Define a structure for points in spherical coordinates.
 */
typedef struct point_spher_coord_ {
    double rho;
    double theta;
    double phi;
} point_spher_coord;

/**
 * Ecliptical (or celestial) Longitude and Latitude.
 * The Ecliptical (or celestial) Latitude and Longitude of
 * and object.
 *
 * Angles are expressed in degrees. East is positive, West negative.
 */
typedef struct point_lon_lat_posn_ {
    double lon; ///< Longitude. Object longitude.
    double lat; ///< latitude. Object latitude.
} point_lon_lat_posn;

/**
 * Equatorial Coordinates. The Right Ascension and Declination
 * of an object.
 *
 * Angles are expressed in degrees.
 */
typedef struct point_equ_posn_ {
    double ra;  ///< RA. Object right ascension in degrees.
    double dec; ///< DEC. Object declination.
} point_equ_posn;

/**
 * Human readable Equatorial Coordinates.
 */
typedef struct point_nh_equ_posn_  {
    proto_datetime::hms ra; ///< RA. Object right ascension.
    proto_datetime::dms dec; ///< DEC. Object declination.
} point_nh_equ_posn;

/**
 * Horizontal Coordinates. The Azimuth and Altitude of
 * an object.
 *
 * Angles are expressed in degrees.
 */
typedef struct point_hrz_posn_ {
    /**
     * AZ. Object azimuth. 0 deg = south, 90 deg = West,
     * 180 deg = Nord, 270 deg = East.
     */
    double az;

    /**
     * ALT. Object altitude. 0 deg = horizon, 90 deg = zenit,
     * -90 deg = nadir.
     */
    double alt;
} point_hrz_posn;

/**
 * Galactic coordinates. The Galactic Latitude and
 * Longitude of and object.
 *
 * Angles are expressed in degrees.
 */
typedef struct point_gal_posn_ {
    double lon; ///< Galactic longitude (degrees).
    double lat; ///< Galactic latitude (degrees).
} point_gal_posn;

/**
 * Human readable Ecliptical (or celestial) Longitude and Latitude.
 */
typedef struct point_nh_lonlat_posn_ {
    proto_datetime::dms lon; ///< Longitude. Object longitude.
    proto_datetime::dms lat; ///< Latitude. Object longitude.
} point_nh_lonlat_posn;

/**
 * Azimuth and Altitude. Human readable Horizontal
 * Coordinates.
 */
typedef struct point_nh_hrz_posn_ {
    proto_datetime::dms az;  ///< AZ. Object azimuth.
    proto_datetime::dms alt; ///< ALT. Object altitude.
} point_nh_hrz_posn;
}

/**
 * Definitions for Command line parser.
 */
namespace proto_cmd {
/**
 * Command Line variables.
 */
typedef struct argts_ {
    int argc;             ///< Command Line arg count.
    char **argv;          ///< Commnad Line args.
    char *appname;        ///< The application name from argv[0].
    int *new_argv;        ///< Arguments sans options (index to argv).
    int new_argc;         ///< Argument count sans the options.
    int max_legal_args;   ///< Ignore extra arguments.
} argts;

/**
 * Option "string" storage and indexing.
 */
typedef struct str_storage_ {
    int max_options;      ///< Maximum number of options.
    const char **options; ///< Option storage.
    int *optiontype;      ///< Type common, command, file.
    int *optionindex;     ///< Index into value storage.
    int option_counter;   ///< Counter for added options.
} str_storage;

/**
 * Option "chars" storage and indexing.
 */
typedef struct chars_storage_ {
    int max_char_options; ///< Maximum number options.
    char *optionchars;    ///< Option storage.
    int *optchartype;     ///< Type common, command, file.
    int *optcharindex;    ///< Index into value storage.
    int optchar_counter;  ///< Counter for added options.
} chars_storage;

/**
 * Values Storage.
 */
typedef struct values_storage_ {
    char **values;       ///< Common value storage.
    int g_value_counter; ///< Globally updated value index LAME.
} values_storage;

/**
 * Help and usage variables.
 */
typedef struct help_storage_ {
    const char **usage;  ///< Usage.
    int max_usage_lines; ///< Max usage lines reseverd.
    int usage_lines;     ///< Number of usage lines.
} help_storage;

/**
 * Storage variables.
 */
typedef struct storage_ {
    bool command_set;   ///< If argc/argv were provided.
    bool mem_allocated; ///< If memory allocated in init().
    bool posix_style;   ///< Enables to turn off POSIX style options.
    bool verbose;       ///< Silent|verbose.
    bool print_usage_;  ///< Print usage verbose.
    bool print_help_;   ///< help verbose.
} storage;

/**
 * Stream variables.
 */
typedef struct stream_ {
    char opt_prefix_char;     ///< '-' in "-w".
    char file_delimiter_char; ///< ':' in width : 100.
    char file_comment_char;   ///<  '#' in "#this is a comment".
    char equalsign;           ///< Equal.
    char comment;             ///< Comment.
    char delimiter;           ///< Delimiter.
    char endofline;           ///< End of line.
    char whitespace;          ///< White spaces.
    char nullterminate;       ///< Null Terminate.
    char long_opt_prefix[2]; ///< '--' in "--width".
} stream;

}

/**
 * Definitions for Thread class.
 */
namespace proto_th {
typedef unsigned char GEN_BOOL;
typedef long GEN_DWORD;
typedef void *GEN_VOID;
typedef GEN_DWORD thread_id_t;
}

}
#endif // GENESIS_PROTO_TYPES_HXX
