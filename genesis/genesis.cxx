/**
 * @file
 *
 * Implementation for an genesis.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_GENESIS_HXX
#include <genesis/genesis.hxx>
#endif
#ifndef GENESIS_LOGGER_HXX
#include <genesis/logger.hxx>
#endif
#ifndef GENESIS_STRING_UTIL_HXX
#include <genesis/string_util.hxx>
#endif

namespace genesis {

library::library()
{
}

library::~library()
{
}

void library::check_build_details()
{
    GEN_MSG( "Compilation Details:\n" );
    GEN_MSG( "      Build Date: " __DATE__ " " __TIME__ );
    GEN_MSG( "      Build Version: " __VERSION__ );
#ifdef __OPTIMIZE__
#define __OPT__ 1
    GEN_MSG( "      Build Optimized: Yes" );
#else
#define __OPT__ 0
    GEN_MSG( "      Build Optimized: No" );
#endif
#ifdef __STDC__
    GEN_MSG( "      ISO Standard: Yes" );
#else
    GEN_MSG( "      ISO Standard: No" );
#endif
}

const char *library::version()
{
    static std::string v( string_util::to_uppercase( PACKAGE ) +
                          ", Version " VERSION + "\n" +
                          "Copyright 2009 "
                          "Ederson de Moura" );

    return v.c_str();
}

const char *library::package()
{
    static std::string p( string_util::to_uppercase( PACKAGE ) );
    return p.c_str();
}

bool library::is_big_endian()
{
    unsigned int a = 1;
    unsigned char *b = ( unsigned char * )& a;
    return ( *b ? false : true );
}

}
