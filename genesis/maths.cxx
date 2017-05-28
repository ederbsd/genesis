/**
 * @file
 *
 * Implementations for an maths.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009-2010 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_MATHS_HXX
#include <genesis/maths.hxx>
#endif
#ifndef GENESIS_LOGGER_HXX
#include <genesis/logger.hxx>
#endif

#include <cstdio>

namespace genesis {

// Initialize variables.
double *maths::interpolation::vector_x_;
double *maths::interpolation::vector_y_;
int maths::interpolation::length_;

namespace maths {

void base::compute_factor( int number, int n, int j )
{
    GEN_ASSERT( number >= 0 );
    GEN_ASSERT( n >= 0 );
    GEN_ASSERT( j >= 0 );

    int i = 0;

    // 1 is neither prime nor composite.
    if ( n == 1 ) {
        GEN_MSG( "Invalid 1 is a unit." );
        return;
    }

    i = j;

    // Determine the prime factors of n.
    while ( i <= ( int )( std::sqrt(( double )n ) )) {

        if ( n % i == 0 ) {
            // We have found a prime factor of n.
            // Print it and factor n / i.
            fprintf( stdout, "%d\n", i );
            compute_factor( number, ( int )( n / i ), i );
            return;
        } else {
            i++;
        }
    }

    // If this point is reached, n is prime.
    if ( n == number ) {
        printf( "%d is prime\n", number );
    } else {
        printf( "%d\n", n );
    }

    return;
}

int base::compute_fact( int n )
{
    GEN_ASSERT( n >= 0 );

    // Compute a factorial recursively.
    if ( n < 0 ) {
        return 0;
    } else if ( n == 0 ) {
        return 1;
    } else if ( n == 1 ) {
        return 1;
    } else {
        return n * compute_fact( n - 1 );
    }
}

int base::compute_fact_tail( int n, int a )
{
    GEN_ASSERT( n >= 0 );

    // Compute a factorial in a tail-recursive manner.
    if ( n < 0 ) {
        return 0;
    } else if ( n == 0 ) {
        return 1;
    } else if ( n == 1 ) {
        return a;
    } else {
        return compute_fact_tail( n - 1, n * a );
    }
}

void interpolation::linear( double *x, double *y, int n )
{
    interpolation::vector_x_ = new double[n];
    interpolation::vector_y_ = new double[n];

    int i = 0;

    for ( ; i < n; ++i ) {
        interpolation::vector_x_[i] = x[i];
        interpolation::vector_y_[i] = y[i];
    }
}

double interpolation::linear_get_y( double x )
{
    GEN_ASSERT( x >= 0. );

    int i = 0;

    while ( x > interpolation::vector_x_[++i] );

    double f = ( x - interpolation::vector_x_[i - 1] ) /
               ( interpolation::vector_x_[i] -
                 interpolation::vector_x_[i - 1] );

    return interpolation::vector_y_[i - 1] + f *
           ( interpolation::vector_y_[i] -
             interpolation::vector_y_[i - 1] );
}

void interpolation::lagrange( double *x, double *y, int n )
{
    interpolation::vector_x_ = x;
    interpolation::vector_y_ = y;
    interpolation::length_ = n;
}

double interpolation::lagrange_get_y( double x )
{
    GEN_ASSERT( x >= 0. );

    double y = 0.;

    int i = 0;
    int j = 0;

    for ( ; i < interpolation::length_; ++i ) {
        double aux = vector_y_[i];
        for ( ; j < interpolation::length_; ++j ) {
            if ( i != j ) {
                aux *= ( x - interpolation::vector_x_[j] ) /
                       ( interpolation::vector_x_[i] - interpolation::vector_x_[j] );
            }
            y += aux;
        }
    }

    return y;
}

}
}
