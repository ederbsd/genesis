/**
 * @file
 *
 * Implementation for an logger.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_LOGGER_HXX
#include <genesis/logger.hxx>
#endif

#if !defined( CLEANTLOG )

#if defined( FTLOG )
#include <fstream>
#else
#ifndef GENESIS_NULLSTREAM_HXX
#include <genesis/nullstream.hxx>
#endif
#endif

#include <iostream>

namespace genesis {

logger::logger()
{
}

logger::~logger()
{
}

bool logger::is_activated()
{
    return logger::is_activated_;
}

void logger::activate( bool const activate )
{
    is_activated_ = activate;
}

::std::ostream *&logger::ostream_ptr()
{
    return outstream_;
}

// Activate logger by default.
bool logger::is_activated_ = true;

#if defined( GEN_TLOG )
// Set auto pointer to the null stream
// reason: ::std::cout can not be created in runtime, so
// the auto pointer has nothing to do with its resources.
::std::auto_ptr< ::std::ostream > logger::outstream_helper_ptr_
    = ::std::auto_ptr< ::std::ostream > ( new null_stream );
::std::ostream *logger::outstream_ = &::std::cout;

#elif defined( GEN_ETLOG )
// Look to the GEN_TLOG comments.
::std::auto_ptr< ::std::ostream > logger::outstream_helper_ptr_
    = ::std::auto_ptr< ::std::ostream > ( new null_stream );
::std::ostream *logger::outstream_ = &::std::cerr;

#elif defined( GEN_FTLOG )

#include <cctype>

#define XSTR( s ) STR( s )
#define STR( s ) #s

#define MAX( x,y ) ( ( x ) < ( y ) ? ( y ) : ( x ) )

namespace detail {
/**
 * Function paste rhs C string to the lhs C string.
 * lhs should be long enough for that operation.
 * Additionally coping is stared from the point which
 * points lhs.
 */
template< typename Char_type>
size_t const str_cat( Char_type *&lhs, Char_type const *rhs )
{
    size_t len = 0;

    while ( *rhs != '\0' ) {
        *lhs = *rhs;
        ++rhs;
        ++lhs;
        ++len;
    }
    return len;
}

/**
 * Function calculates length of C string
 * It can be used with wide characters.
 */
template<typename Char_type>
size_t const str_len( Char_type const *str )
{
    size_t len = 0;

    while ( *str != '\0' ) {
        ++str;
        ++len;
    }
    return len;
}

/**
 * Function copy rhs C string in to the lhs.
 * It do not check size of target C string
 * It starts to copy from the beginning of the C string,
 * but it begins put characters at the point where lhs points,
 * so there can be a problem when lhs points on the end of lhs
 * C string.
 */
template<typename Char_type>
size_t const str_cpy( Char_type *&lhs, Char_type const *rhs )
{
    size_t len = 0;

    while ( *rhs != '\0' ) {
        *lhs = *rhs;
        ++rhs;
        ++lhs;
        ++len;
    }
    *lhs = '\0';
    return len + 1;
}

/**
 * Function converts existing file name to the file name
 * which has no non-printable signs and
 * at the end is added extension.
 * The space sign in file name is converted to the underscore.
 * Lengths of C strings has to be proper.
 */
template<typename Char_type>
size_t const createfilename( Char_type *result,
                             Char_type const *filename,
                             Char_type const *ext,
                             Char_type const *helper )
{
    size_t len = 0;

    if ( str_len ( filename ) > 1 ) {
        while ( *filename != '\0' ) {
            // Check if characters have grapnical
            // reprasentation.
            if ( 0 != ::std::isgraph ( *filename ) ) {
                *result = *filename;
                ++result;
                ++len;
            } else {
                // Convert space to underscore.
                if ( *filename == ' ' ) {
                    *result = '_';
                    ++result;
                    ++len;
                }
            }
            ++filename;
        }

        // Add extension.
        str_cat( result, ext );
        *result = '\0';
    } else {
        result = &result[0];
        len = str_cpy ( result, helper );
    }
    return len;
}

template<typename T>
T const max( T const x, T const y )
{
    return ( x < y ? y : x );
}

} // namespace detail

typedef char char_type;

// Convert definition of the TLOGFILE
// to the C string.
char_type const tlogfilename[] = XSTR( FTLOG );

// Extension C string.
char_type const ext[] = ".log";

char_type const helper_name[] = "_logger.log";

// Container for final file name.
char_type filename[ ( MAX( sizeof( tlogfilename ),
                           sizeof( helper_name ) ) +
                      sizeof( ext ) ) / sizeof( char_type ) ];
// Create file name.
size_t const len = detail::createfilename( filename, tlogfilename,
                                           ext, helper_name );
#undef MAX
#undef STR
#undef XSTR

// New file is opened and its destruction is managed by auto_ptr.
::std::auto_ptr< ::std::ostream > logger::outstream_helper_ptr_
    = ::std::auto_ptr< ::std::ostream > ( new ::std::ofstream ( filename ) );

// Set pointer output stream.
::std::ostream *logger::outstream_ = outstream_helper_ptr_.get();

// Here is a place for user defined output stream and flag.

// ...

#else
::std::auto_ptr< ::std::ostream > logger::outstream_helper_ptr_
    = ::std::auto_ptr< ::std::ostream >( new null_stream );
::std::ostream *logger::outstream_ = outstream_helper_ptr_.get();

#endif

::std::auto_ptr<logger> detail::logger_out_ptr_( new logger() );

logger &logger_parent()
{
    return *detail::logger_out_ptr_;
}
}

#endif
