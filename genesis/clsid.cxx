/**
 * @file
 *
 * Implementation for an clsid.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_CLSID_HXX
#include <genesis/clsid.hxx>
#endif

namespace genesis {
namespace dynamic_library {

std::ostream &operator <<( std::ostream &s,
                           const dynamic_library::clsid &clsid )
{
    //s << clsid.id_;
    return s;
}

clsid::clsid()
{
}

clsid::clsid( GEN_IN const clsid &clsid )
{
    id_ = clsid.id_;
}

clsid::clsid( GEN_IN std::string str_clsid )
{
    operator=( str_clsid );
}

clsid::~clsid()
{
}

clsid &clsid::operator=( GEN_IN clsid &clsid )
{
    id_ = clsid.id_;
    return *this;
}

clsid &clsid::operator=( GEN_IN std::string str_clsid )
{
    id_ = str_clsid;
    return *this;
}

bool clsid::operator==( GEN_IN genesis::dynamic_library::clsid clsid )
{
    return ( id_ == clsid.id_ );
}

bool clsid::operator==( GEN_IN std::string str_clsid )
{
    return ( id_ == str_clsid );
}

bool clsid::operator==( GEN_IN char *str_clsid )
{
    return ( id_ == str_clsid );
}

bool clsid::operator<( GEN_IN const clsid &clsid ) const
{
    return ( id_ < clsid.id_ );
}

bool clsid::operator>( GEN_IN const clsid &clsid ) const
{
    return ( id_ > clsid.id_ );
}

}
}
