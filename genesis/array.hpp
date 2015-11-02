/**
 * @file
 *
 * Definitions for an array.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_ARRAY_HPP
#define GENESIS_ARRAY_HPP

#include <genesis/logger.hpp>
#include <genesis/string_util.hpp>

#include <cmath>

#include <algorithm>
#include <vector>

namespace genesis {

  namespace array {
    /**
     * Genesis Vector Class.
     */
    class vector {
    public:
      /**
       * Constructor.
       */ 
      vector() {};

      /**
       * Destructor.
       */
      virtual ~vector() {};

      /**
       * Dynamically allocates a 1D block (vector) of data.
       *
       * @param columns - The length of the vector. 
       */ 
      template<class T>
      inline static T* create_vector( long columns )
      {
        T* m = new T[columns];
        GEN_ASSERT( m != 0 );
        return m;
      }

      /**
       * Dynamically allocates a 1D block (vector) of data 
       * using an offset base memory address.
       *
       * @param columns_start - The first addressible index.
       * @param columns_end - The last addressible index.
       */ 
      template<class T>
      inline static T* create_vector( long columns_start, long columns_end )
      {
        T* m = new T[columns_end - columns_start + 1];
        GEN_ASSERT( m != 0 );
        return m - columns_start;
      }

      /**
       * Frees from memory a 1D block of dynamically allocated data.
       *
       * @param create_vector - Is the 1D data structure to delete.
       * @param offset - Is the original offset to the first element 
       *                 in the array, if not zero (default=0).
       */ 
      template<class T>
      inline static void free_vector( T* create_vector, int offset = 0 )
      {
        delete[] ( create_vector + offset );
      }

      /**
       * Binary Search Element.
       *
       * @param vec - Vector data search.
       * @param key - Key search element.
       * @param line - Possition line (default 0).
       */
      template<class T>
      static T binary_search( std::vector<double> vec, double key, 
       int line = 0 )
      {
        std::vector<double>::iterator it(
         std::find( vec.begin(), vec.end(), key ) );

        if( it != vec.end() ) {
          line = it - vec.begin() + 1;
          GEN_MSG( "Location Position Element: " +
                   genesis::string_util::to_string( line ) );
          return line;
        } else {
          GEN_WARN( "Element not found: " + 
                    genesis::string_util::to_string( line ) );
        }

        return 0;
      }

      /**
       * Rotate a vector along the spec'd axis.
       *
       * @param v - Vector to rotate.
       * @param angle - Angle of rotation.
       * @param axis - Axis to rotate along.
       */
      static void rotate_vector( types::vector& v, double angle, int axis );

    };

    /**
     * Genesis Matrix Class.
     */
    class matrix : public vector {
    public:
      /**
       * Constructor.
       */ 
      matrix() {};

      /**
       * Destructor.
       */
      virtual ~matrix() {};

      /**
       * Preload a matrix:
       *
       * 0 1 1
       * 1 0 1
       * 1 1 0
       *
       * @param m - Matrix to initialize.
       */
      static void set_identity_matrix( types::matrix m ) {
        register int i = 0;
        for( ;i < 9; i++ ) {
          m[i] = ( (i & 3) ? 0. : 1. );
        }
      }

      /**
       * Inline swap ( a <--> b )
       *
       * tmp is only there to avoid a local var.
       *
       * @param a - First double.
       * @param b - Second double.
       * @param tmp - Scratch double.
       */
      static void swapd( double& a, double& b, double tmp ) {
        tmp = a;  a = b;  b = tmp; 
      }

      /**
       * Convert polar coordinates to Cartesian.
       *
       * @param v - Vector to put Cartesian Coordinates into.
       * @param lon - Polar longitude.
       * @param lat - Polar latitude.
       */
      static void polar3_to_cartesian( types::vector& v, double lon, double lat );

      /**
       * Inverting an orthonormal matrix is simple:
       *
       * swap a's, b's and c's as shown below:
       *
       * This:
       *    x a b
       *    a x c
       *    b c x
       *
       * @param m - Matrix to invert.
       */
      static void invert_orthonormal_matrix( types::matrix& m );

      /**
       * Partial spin?
       *
       * @param m1 - First matrix.
       * @param m2 - Second matrix.
       * @param angle - Angle.
       */ 
      static void pre_spin_matrix( types::matrix& m1, types::matrix& m2, double angle );

      /**
       * SpinMatrix
       *
       * @param m1 - First matrix.
       * @param m2 - Second matrix.
       * @param angle - Angle.
       */
      static void spin_matrix( types::matrix& m1, types::matrix& m2, double angle );

      /**
       * Dynamically allocates a zero-based 2D block (matrix) of data.
       *
       * @param rows - The 2nd dimension of a matrix.
       * @param columns - The 1st (primary) dimension of a matrix.
       */ 
      template<class T>
      inline static T** create_matrix( long rows, long columns )
      {
        T** m = new T*[rows];

        GEN_ASSERT( m != 0 );
 
        if( m != 0 ) {
          m[0] = new T[rows * columns];
          GEN_ASSERT( m[0] != 0 );

          if( m[0] != 0 ) {
            for( long i = 1; i < rows; i++ ) { 
              m[i] = m[i-1] + columns; 
            }
          }
        }

        return m;
      }

      /**
       * Frees from memory a 2D block of dynamically allocated data.
       *
       * @param create_matrix - Is the 2D data structure to delete.
       */ 
      template<class T>
      inline static void free_matrix( T** create_matrix )
      {
        delete[]( create_matrix[0] );
        delete[]( create_matrix );
      }

      /**
       * Dynamically allocates a zero_based 3D block (cube) of data.
       *
       * @param depth - The 3rd dimension of a cube.
       * @param rows - The 2nd dimension of a cube.
       * @param columns - The 1st (primary) dimension of a cube.
       */
      template<class T>
      inline static T*** create_cube( long depth, long rows, long columns )
      {
        T*** m = create_matrix<T*>( depth, rows );

        GEN_ASSERT( m != 0 );

        if( m != 0 ) {
          m[0][0] = new T[rows * columns * depth];
          GEN_ASSERT( m[0][0] != 0 );
 
          if( m[0][0] != 0 ) {
            for( long j = 1; j < rows; j++ ) {
              m[0][j] = m[0][j-1] + columns;
            }
 
            for( long i = 1; i < depth; i++ ) {
              m[i][0] = m[i-1][0] + rows * columns;
              for( long j = 1; j < rows; j++ ) {
                m[i][j]=m[i][j-1] + columns;
              }
            }
          }
        }

        return m;
      }

      /**
       * Removes any dynamically allocated memory for a 3D structure from 
       * the stack. This method is usually used on data structures created 
       * using (cube<...>), though it can also be used on other 3D types, 
       * so long as the memory is continuously allocated with a pointers to 
       * pointers setup.
       *
       * @param cube - Is the 2D data structure to delete.
       */ 
      template<class T>
      inline static void free_cube( T*** cube )
      {
        delete[]( cube );
      }

    };

  }
}

#endif // GENESIS_ARRAY_HPP
