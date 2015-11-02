/**
 * @file
 *
 * Definitions for an convex_hull.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_CONVEX_HULL_HPP
#define GENESIS_CONVEX_HULL_HPP

#include <genesis/plotting.hpp>

namespace genesis {
  /**
   * Genesis Convex Hull, class using Graham scan algorithm to 
   * calculate the convex hull of a batch of points.
   */
  class convex_hull : public plotting {
  public:
    /**
     * Constructor.
     *
     * I generate the N random points asked for by the caller.
     * Their values are randomly assigned in the x/y ranges specified 
     * as arguments.
     *
     * @param n - Numbers points generated.
     * @param xmin - Min range of numbers X.
     * @param xmax - Max range of numbers X.
     * @param ymin - Min range of numbers Y.
     * @param ymax - Max range of numbers Y.
     */
    explicit convex_hull( size_t n, int xmin, int xmax, int ymin, int ymax );

    /**
     * Print Raw Points.
     *
     * @param f - File Ostream.
     * @param m - Message cout.
     * @param plot - Generate the graph, (default no).
     */
    void print_raw_points( std::ostream& f, std::ostream& m, bool plot = false );

    /**
     * Print Partitioned Points.
     *
     * @param f - File Ostream.
     * @param m - Message cout.
     * @param plot - Generate the graph, (default no).
     */
    void print_partitioned_points( std::ostream& f, std::ostream& m, bool plot = false );

    /**
     * Print Convex Hull.
     *
     * @param f - File Ostream.
     * @param m - Message cout.
     * @param plot - Generate the graph, (default no).
     */
    void print_hull( std::ostream& f, std::ostream& m, bool plot = false );

  private:
    /**
     * Building the hull consists of two procedures: building the lower and
     * then the upper hull. The two procedures are nearly identical - the main
     * difference between the two is the test for convexity.
     *
     * When building the upper hull, our rull is that the middle point must
     * always be "above" the line formed by its two closest neighbors. When
     * building the lower hull, the rule is that point must be "below" its
     * two closest neighbors. We pass this information to the building
     * routine as the last parameter, which is either -1 or 1.
     *
     * @param f - File Ostream.
     * @param plot - Generate the graph, (default no).
     */
    void build_hull( std::ostream& f, bool plot = false );

    /**
     * The initial array of points is stored in vectgor raw_points. I first
     * sort it, which gives me the far left and far right points of the hull.
     * These are special values, and they are stored off separately in the left
     * and right members.
     *
     * I then go through the list of raw_points, and one by one determine
     * whether each point is above or below the line formed by the right and
     * left points.
     *
     * If it is above, the point is moved into the upper_partition_points
     * sequence. If it is below, the point is moved into the
     * lower_partition_points sequence. So the output of this routine is the
     * left and right points, and the sorted points that are in the upper
     * and lower partitions.
     */
    void partition_points();

    /**
     * This is the method that builds either the upper or the lower half 
     * convex hull. It takes as its input a copy of the input array, 
     * which will be the sorted list of points in one of the two halfs. 
     * It produces as output a list of the points in the corresponding 
     * convex hull.
     *
     * The factor should be 1 for the lower hull, and -1 for the upper hull.
     *
     * @param f - File Ostream.
     * @param input - Input points.
     * @param output - Ouput points.
     * @param factor - Factor hull.
     */
    void build_half_hull( std::ostream& f,
     std::vector< std::pair<int,int> > input,
     std::vector< std::pair<int,int> > &output, int factor );

  protected:
    /**
     * In running application we frequently want to look at three consecutive
     * points, p0, p1, and p2, and determine whether p2 has taken a turn
     * to the left or a turn to the right.
     *
     * We can do this by by translating the points so that p1 is at the origin,
     * then taking the cross product of p0 and p2. The result will be positive,
     * negative, or 0, meaning respectively that p2 has turned right, left, or
     * is on a straight line.
     *
     * @param p0 - Point 0.
     * @param p1 - Point 1.
     * @param p2 - Point 2.
     */
    static int direction( std::pair<int,int> p0, std::pair<int,int> p1,
     std::pair<int,int> p2 );

    /**
     * Ostream operator print result.
     *
     * @param s - Output stream to print.
     * @param point - Point to print.
     * @return Output stream.
     */
    friend std::ostream& operator <<( std::ostream& s, 
     const std::pair<int,int>& point );

    /// Used in method build_hull.
    bool build_plot_;

    /// Check create point.
    bool check_points_;

    ///< Numbers generated.
    const size_t N_;

    ///< Range of numbers X.
    const std::pair<int,int> x_range_;

    ///< Range of numbers Y.
    const std::pair<int,int> y_range_; 

    /// The raw data points generated by the constructor.
    std::vector< std::pair<int,int> > raw_points_;

    /// Partitioned set Left.
    std::pair<int,int> left_;

    /// Partitioned set Rigth.
    std::pair<int,int> right_;

    /// Partitioned sorted set of upper.
    std::vector< std::pair<int,int> > upper_partition_points_;

    /// Partitioned sorted set of lower
    std::vector< std::pair<int,int> > lower_partition_points_;

    /**
     * The lower hull and upper hull are stored in these
     * sorted sequences.
     */
    std::vector< std::pair<int,int> > lower_hull_;

    /**
     * There is a bit of duplication between the two because
     * both sets include the leftmost and rightmost point.
     */
    std::vector< std::pair<int,int> > upper_hull_;

  };

}

#endif // GENESIS_CONVEX_HULL_HPP
