/**
 * @file
 *
 * Definitions for an plotting.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_PLOTTING_HPP
#define GENESIS_PLOTTING_HPP

#include <fstream>
#include <vector>

namespace genesis {
  /**
   * Genesis Interactive Plotting Class.
   */
  class plotting {
  public:
    /**
     * Constructor.
     */
    plotting() {};

    /**
     * Destructor.
     */
    ~plotting() {};

    /**
     * Convex Hull plotting raw points. 
     *
     * @param f - File Ostream.
     * @param x_range - Range of numbers X.
     * @param y_range - Range of numbers Y.
     * @param N - Numbers points generated.
     * @param raw_points - Raw data points. 
     */
    void raw_points( std::ostream& f, std::pair<int,int> x_range,
     std::pair<int,int> y_range, size_t N, 
     std::vector< std::pair<int,int> > raw_points );

    /**
     * Convex Hull plotting partitioned points.
     *
     * @param f - File Ostream.
     * @param lower_part_points - Sorted set of lower.
     * @param upper_part_points - Sorted set of upper.
     * @param left - Partitioned set Left.
     * @param right - Partitioned set Right.
     */
    void partitioned_points( std::ostream& f, 
     std::vector< std::pair<int,int> > lower_part_points,
     std::vector< std::pair<int,int> > upper_part_points, 
     std::pair<int,int> left, std::pair<int,int> right );

    /**
     * Convex Hull plotting hull points.
     *
     * @param f - File Ostream.
     * @param text - Name of graph.
     * @param upper_hull - Store hull upper.
     * @param lower_hull - Store hull lower.
     * @param lower_part_points - Sorted set of lower.
     * @param upper_part_points - Sorted set of upper.
     * @param right - Partitioned set Right.
     */
    void hull( std::ostream& f, std::string text, 
     std::vector< std::pair<int,int> > upper_hull, 
     std::vector< std::pair<int,int> > lower_hull,
     std::vector< std::pair<int,int> > lower_part_points, 
     std::vector< std::pair<int,int> > upper_part_points,
     std::pair<int,int> right );

  };
}

#endif // GENESIS_PLOTTING_HPP
