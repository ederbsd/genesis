/**
 * @file
 *
 * Definitions for an maths.
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
#ifndef GENESIS_MATHS_HXX
#define GENESIS_MATHS_HXX

#include <genesis/genesis.hxx>

#include <cmath>

namespace genesis {

namespace maths {
/**
 * Genesis Base Class.
 */
class base
{
public:
    /**
     * Compute factor.
     *
     * @param number - Number.
     * @param n - Number.
     * @param j - Number.
     */
    static void compute_factor( int number, int n, int j );

    /**
     * Compute a factorial recursively.
     *
     * @param n - Number compute.
     */
    static int compute_fact( int n );

    /**
     * Compute a factorial in a tail-recursive manner.
     *
     * @param n - Number.
     * @param a - Number.
     */
    static int compute_fact_tail( int n, int a );

};

/**
 * Genesis Interpolation Class.
 */
class interpolation : public base
{
public:
    /**
     * Linearly interpolates a given set of points.
     *
     * @param x - The x-coordinates for the initial points.
     * @param y - The y-coordinates for the initial points.
     * @param n - The y-coordinates for the initial points.
     */
    static void linear( double *x, double *y, int n );

    /**
     * Returns value the approximated ordinate at the given
     * abscissa.
     *
     * @param x - The abscissa of the interpolation point.
     */
    static double linear_get_y( double x );

    /**
     * Interpolates a given set of points using the Lagrange
     * polynomial.
     *
     * @param x - The x-coordinates for the initial points.
     * @param y - The y-coordinates for the initial points.
     * @param n - The number of initial points.
     */
    static void lagrange( double *x, double *y, int n );

    /**
     * Returns value the approximated ordinate at the given
     * abscissa.
     *
     * @param x - The abscissa of the interpolation point.
     */
    static double lagrange_get_y( double x );

    /**
     * The method of least squares or ordinary least squares (OLS),
     * is used to approximately solve overdetermined systems.
     *
     * @param x - The x-coordinates for the initial points.
     * @param y - The y-coordinates for the initial points.
     * @param n - The number of initial points.
     * @param b1 - ...
     * @param b0 - ...
     */
    static void least_square( const double *x, const double *y, int n,
                              double *b1, double *b0 )
    {
        return;
    };

private:
    static double *vector_x_; ///< Interpolation method used by the vector x.
    static double *vector_y_; ///< Interpolation method used by the vector y.
    static int length_; ///< Interpolation method used by the length.

};

/**
 * Genesis RootFinding Class.
 */
class root : public base
{
public:
    /**
     * Calculates the zeros of a function using Newton's method.
     *
     * @param f - The user-defined function.
     * @param g - Default value g...
     * @param x - Default value x...
     * @param n - Default value n...
     * @param delta - The derivative...
     */
    static int newton( double( *f ) ( double x ), double( *g ) ( double x ),
                       double *x, int *n, double delta )
    {
        return 0;
    };
};

}
}

#endif // GENESIS_MATHS_HXX
