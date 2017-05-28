/**
 * @file
 *
 * Implementation for an plotting.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_PLOTTING_HXX
#include <genesis/plotting.hxx>
#endif

namespace genesis {

void plotting::raw_points( std::ostream &f, std::pair<int, int> x_range,
                           std::pair<int, int> y_range, size_t N,
                           std::vector< std::pair<int, int> > raw_points )
{
    f << "set xrange ["
      << x_range.first
      << ":"
      << x_range.second
      << "]\n";
    f << "set yrange ["
      << y_range.first
      << ":"
      << y_range.second
      << "]\n";
    f << "unset mouse\n";
    f << "set title 'The set of raw points in the set' font 'Arial,12'\n";
    f << "set style line 1 pointtype 7 linecolor rgb 'red'\n";
    f << "set style line 2 pointtype 7 linecolor rgb 'green'\n";
    f << "set style line 3 pointtype 7 linecolor rgb 'black'\n";
    f << "plot '-' ls 1 with points notitle\n";

    size_t i = 0;

    for ( i = 0 ; i < N ; i++ ) {
        f << raw_points[ i ].first << " " << raw_points[ i ].second << "\n";
    }

    f << "e\n";
    f << "pause -1 'Hit OK to move to the next state!'\n";
}

void plotting::partitioned_points( std::ostream &f,
                                   std::vector< std::pair<int, int> > lower_part_points,
                                   std::vector< std::pair<int, int> > upper_part_points,
                                   std::pair<int, int> left, std::pair<int, int> right )
{
    f << "set title 'The points partitioned into an upper and lower hull' font 'Arial,12'\n";
    f << "plot '-' ls 1 with points notitle, "
      << "'-' ls 2 with points notitle, "
      << "'-' ls 3 with linespoints notitle\n";

    size_t i = 0;

    for ( i = 0 ; i < lower_part_points.size() ; i++ ) {
        f << lower_part_points[ i ].first
          << " "
          << lower_part_points[ i ].second
          << "\n";
    }
    f << "e\n";

    for ( i = 0 ; i < upper_part_points.size() ; i++ ) {
        f << upper_part_points[ i ].first
          << " "
          << upper_part_points[ i ].second
          << "\n";
    }
    f << "e\n";

    f << left.first << " " << left.second << "\n";
    f << right.first << " " << right.second << "\n";
    f << "e\n";
    f << "pause -1 'Hit OK to move to the next state!'\n";
}

void plotting::hull( std::ostream &f, std::string text,
                     std::vector< std::pair<int, int> > upper_hull,
                     std::vector< std::pair<int, int> > lower_hull,
                     std::vector< std::pair<int, int> > lower_part_points,
                     std::vector< std::pair<int, int> > upper_part_points,
                     std::pair<int, int> right )
{
    f << "set title 'The hull in state: "
      << text
      << "' font 'Arial,12'\n";
    f << "plot '-' ls 1 with points notitle, ";

    if ( lower_hull.size() ) {
        f << "'-' ls 3 with linespoints notitle, ";
    }

    if ( upper_hull.size() ) {
        f << "'-' ls 3 with linespoints notitle, ";
    }

    size_t i = 0;

    f << "'-' ls 2 with points notitle\n";
    for ( i = 0 ; i < lower_part_points.size() ; i++ ) {
        f << lower_part_points[ i ].first
          << " "
          << lower_part_points[ i ].second
          << "\n";
    }
    f << right.first << " " << right.second << "\n";
    f << "e\n";

    if ( lower_hull.size() ) {
        for ( i = 0 ; i < lower_hull.size() ; i++ ) {
            f << lower_hull[ i ].first
              << " "
              << lower_hull[ i ].second
              << "\n";
        }
        f << "e\n";
    }

    if ( upper_hull.size() ) {
        for ( std::vector< std::pair<int, int> >::reverse_iterator ii =
                    upper_hull.rbegin(); ii != upper_hull.rend(); ii++ ) {
            f << ii->first
              << " "
              << ii->second
              << "\n";
        }
        f << "e\n";
    }

    for ( i = 0 ; i < upper_part_points.size() ; i++ ) {
        f << upper_part_points[ i ].first
          << " "
          << upper_part_points[ i ].second
          << "\n";
    }
    f << "e\n";
    f << "pause -1 'Hit OK to move to the next state!'\n";

}
}

