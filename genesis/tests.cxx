/**
 * @file
 *
 * Implementations for an tests.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009-2010 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_TESTS_HXX
#include <genesis/tests.hxx>
#endif
#ifndef GENESIS_APPLICATION_HXX
#include <genesis/application.hxx>
#endif
#ifndef GENESIS_LOGGER_HXX
#include <genesis/logger.hxx>
#endif
#ifndef GENESIS_STRING_UTIL_HXX
#include <genesis/string_util.hxx>
#endif

#include <cstdio>

// Ansi color codes.
#define ANSI_COLOR_CLEAR "\e[0m"
#define ANSI_COLOR_BOLD "\e[1m"
#define ANSI_COLOR_RED "\e[31m"
#define ANSI_COLOR_GREEN "\e[32m"

namespace genesis {

int tests::t_number_ = 0;

double tests::compare_results( double calc, double expect,
                               double tolerance )
{
    if ( calc - expect > tolerance || calc - expect < ( tolerance * -1.0 ) ) {
        return ( calc - expect );
    } else {
        return 0;
    }
}

int tests::result( std::string test, double calc, double expect,
                   double tolerance )
{
    printf( "TEST %s...", test.c_str() );
    tests::t_number_++;

    genesis::application app;

    double diff = compare_results( calc, expect, tolerance );

    if ( diff ) {
        app.set_ansi_color( std::cout, 4 ); // Red.
        GEN_WARN( "[FAILED]" );
        app.set_restore_ansi_color();
        printf( "       Expected %8.8f but calculated %8.8f %0.12f error.\n\n",
                expect, calc, diff );
        return 1;
    } else {
        app.set_ansi_color( std::cout, 2 ); // Green.
        GEN_MSG( "[PASSED]" );
        app.set_restore_ansi_color();
        printf( "       Expected and calculated %8.8f.\n\n", calc );
        return 0;
    }
}

int tests::print_result( std::string module, int failed )
{
    std::string msg = "Class ";
    GEN_MSG( msg + genesis::string_util::to_uppercase( module ) + ":" );
    printf( "Test completed: %d tests, %d errors.\n", count(), failed );
    return ( failed > 0 );
}
}
