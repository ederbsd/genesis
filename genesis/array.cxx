/**
 * @file
 *
 * Implementations for an array.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_ARRAY_HXX
#include <genesis/array.hxx>
#endif
 
namespace genesis {

namespace array {

void vector::rotate_vector( types::vector &v, double angle, int axis )
{
    GEN_ASSERT( angle >= 0. );
    GEN_ASSERT( axis >= 0 );

    const double sin_ang = std::sin( angle );
    const double cos_ang = std::cos( angle );
    const int a = ( axis + 1 ) % 3;
    const int b = ( axis + 2 ) % 3;

    double temp = v[a] * cos_ang - v[b] * sin_ang;
    v[b] = v[b] * cos_ang + v[a] * sin_ang;
    v[a] = temp;
}

void matrix::polar3_to_cartesian( types::vector &v, double lon, double lat )
{
    GEN_ASSERT( lon >= 0. );
    GEN_ASSERT( lat >= 0. );

    const double cos_lat = std::cos( lat );

    v[0] = std::cos( lon ) * cos_lat;
    v[1] = std::sin( lon ) * cos_lat;
    v[2] = std::sin( lat );
}

void matrix::invert_orthonormal_matrix( types::matrix &m )
{
    double temp = 0.;

    swapd( m[1], m[3], temp );
    swapd( m[2], m[6], temp );
    swapd( m[5], m[7], temp );
}

void matrix::pre_spin_matrix( types::matrix &m1, types::matrix &m2,
                              double angle )
{
    GEN_ASSERT( angle >= 0. );

    const double sinAng = std::sin( angle );
    const double cosAng = std::cos( angle );
    double temp = 0.;

    int i = 0;
    for ( ; i < 9; i += 3 ) {
        temp  = m1[i] * cosAng - m2[i] * sinAng;
        m2[i] = m2[i] * cosAng + m1[i] * sinAng;
        m1[i] = temp;
    }
}

void matrix::spin_matrix( types::matrix &m1, types::matrix &m2,
                          double angle )
{
    GEN_ASSERT( angle >= 0. );

    const double sin_ang = std::sin( angle );
    const double cos_ang = std::cos( angle );
    double tval = 0.;

    int i = 0;
    for ( ; i < 3; i++ ) {
        tval  = m1[i] * cos_ang - m2[i] * sin_ang;
        m2[i] = m2[i] * cos_ang + m1[i] * sin_ang;
        m1[i] = tval;
    }
}

}
}
