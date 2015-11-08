/**
 * @file
 *
 * Implementation for an convex_hull.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/convex_hull.hxx>
#include <genesis/logger.hxx>

#include <algorithm>
#include <ctime>

namespace genesis {

  std::ostream& operator <<( std::ostream& s, const std::pair<int,int>& point )
  {
    s << "("
      << point.first
      << ","
      << point.second
      << ")";
    return s;
  }

  convex_hull::convex_hull( size_t n, int xmin, int xmax, int ymin, int ymax )
   : N_( n ), x_range_( xmin, xmax ), y_range_( ymin, ymax )
  {
    GEN_ASSERT( n > 0 );
    GEN_ASSERT( xmin >= 0 );
    GEN_ASSERT( xmax >= 0 );
    GEN_ASSERT( ymin >= 0 );
    GEN_ASSERT( ymax >= 0 );

    // Set variables.
    this->build_plot_ = false;
    this->check_points_ = false;

    size_t i = 0;

    std::srand( static_cast<unsigned int>( std::time( 0 ) ) );

    for( ; i < N_ ; i++ ) {
      int x = ( std::rand() % ( x_range_.second - x_range_.first + 1 ) ) + 
              x_range_.first;
      int y = ( std::rand() % ( y_range_.second - y_range_.first + 1 ) ) + 
              y_range_.first;
      raw_points_.push_back( std::make_pair( x, y ) );
    }
  }

  void convex_hull::partition_points()
  {
    // Step one in partitioning the points is to sort the raw data.
    std::sort( raw_points_.begin(), raw_points_.end() );

    // The the far left and far right points, remove them from the
    // sorted sequence and store them in special members.
    left_ = raw_points_.front();
    raw_points_.erase( raw_points_.begin() );
    right_ = raw_points_.back();
    raw_points_.pop_back();

    // Now put the remaining points in one of the two output 
    // sequences.
    size_t i = 0;

    for( ; i < raw_points_.size() ; i++ ) {
      int dir = direction( left_, right_, raw_points_[ i ] );

      if( dir < 0 ) {
        upper_partition_points_.push_back( raw_points_[ i ] );
      } else {
        lower_partition_points_.push_back( raw_points_[ i ] );
      }
    }
  }

  void convex_hull::build_hull( std::ostream& f, bool plot )
  {
    if( plot ) {
      build_plot_ = true;
    }

    build_half_hull( f, lower_partition_points_, lower_hull_, 1 );
    build_half_hull( f, upper_partition_points_, upper_hull_, -1 );

    if( plot ) {
      // Plotting...
      plotting::hull( f, "Complete", upper_hull_, lower_hull_, 
                      lower_partition_points_, upper_partition_points_, 
                      right_ );
    }
  }

  void convex_hull::build_half_hull( std::ostream& f, 
   std::vector< std::pair<int,int> > input,
   std::vector< std::pair<int,int> > &output, int factor )
  {
    input.push_back( right_ );
    output.push_back( left_ );

    // The construction loop runs until the input is exhausted.
    while( input.size() != 0 ) {

      // Convexity is restored.
      output.push_back( input.front() );
      
      if( build_plot_ ) {
        // Plotting...
        plotting::hull( f, "Adding a new point", upper_hull_, lower_hull_, 
                        lower_partition_points_, upper_partition_points_, 
                        right_ );
      }

      input.erase( input.begin() );
      while( output.size() >= 3 ) {
        size_t end = output.size() - 1;

        if( factor * direction( output[ end - 2 ], 
                                output[ end ], 
                                output[ end - 1 ] ) <= 0 ) {
          output.erase( output.begin() + end - 1 );

          if( build_plot_ ) {
            // Plotting...
            plotting::hull( f, "BackTracking", upper_hull_, lower_hull_, 
                            lower_partition_points_, upper_partition_points_, 
                            right_ );
          }

        } else {
          break;
        }

      }
    }

  }

  int convex_hull::direction( std::pair<int,int> p0, std::pair<int,int> p1,
   std::pair<int,int> p2 )
  {
    return ( ( p0.first - p1.first ) * ( p2.second - p1.second ) ) -
           ( ( p2.first - p1.first ) * ( p0.second - p1.second ) );
  }

  void convex_hull::print_raw_points( std::ostream& f, std::ostream& m,
   bool plot )
  {
    this->check_points_ = true;

    size_t i = 0;

    m << "Creating raw points:\n";
    for( ; i < N_ ; i++ ) {
      m << raw_points_[ i ] << " ";
    }
    m << "\n";

    if( plot ) {
      // Plotting...
      plotting::raw_points( f, x_range_, y_range_, N_, raw_points_ );
    }

    // Called partition points.
    partition_points();
  }

  void convex_hull::print_partitioned_points( std::ostream& f, std::ostream& m,
   bool plot )
  {
    if( !check_points_ ) {
      GEN_WARN( "Not defined Raw Points!" );
    }

    m << "Partitioned set:\n"
      << "Left : " << left_ << "\n"
      << "Right : " << right_ << "\n"
      << "Lower partition: ";

    size_t i = 0;

    for( i = 0 ; i < lower_partition_points_.size() ; i++ ) {
      m << lower_partition_points_[ i ];
    }
    m << "\n";

    m << "Upper partition: ";
    for( i = 0 ; i < upper_partition_points_.size() ; i++ ) {
     m << upper_partition_points_[ i ];
    }
    m << "\n";

    if( plot ) {
      // Plotting
      plotting::partitioned_points( f, lower_partition_points_,  
                                    upper_partition_points_, 
                                    left_, right_ );
    }
  }

  void convex_hull::print_hull( std::ostream& f, std::ostream& m, bool plot )
  {
    if( !check_points_ ) {
      GEN_WARN( "Not defined Raw Points Hull!" );
    }

    if( plot ) {
      build_hull( f, true );
    } else {
      build_hull( f, false );
    }

    size_t i = 0;

    m << "Lower hull: ";
    for( i = 0 ; i < lower_hull_.size() ; i++ ) {
     m << lower_hull_[ i ];
    }
    m << "\n";

    m << "Upper hull: ";
    for( i = 0 ; i < upper_hull_.size() ; i++ ) {
      m << upper_hull_[ i ];
    }
    m << "\n";

    m << "Convex hull: ";
    for( i = 0 ; i < lower_hull_.size() ; i++ ) {
      m << lower_hull_[ i ] << " ";
    }

    for( std::vector< std::pair<int,int> >::reverse_iterator ii = 
          upper_hull_.rbegin() + 1 ; ii != upper_hull_.rend(); ii ++ ) {
      m << *ii << " ";
    }
    m << "\n";
  }
}
