/**
 * @file
 *
 * Definitions for an tests.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_TESTS_HPP
#define GENESIS_TESTS_HPP

#include <string>

namespace genesis {
  /**
   * Genesis Tests Class.
   */
  class tests {
  public:
    /**
     * Compare results.
     *
     * @param calc - Method calcule test.
     * @param expect - Value defined.
     * @param tolerance - Value for tolerance.
     */
    static double compare_results( double calc, double expect, 
                                    double tolerance );

    /**
     * Explain result tests.
     *
     * @param test - Name to execute test.
     * @param calc - Method calcule test.
     * @param expect - Value defined.
     * @param tolerance - Value for tolerance.
     */ 
    static int result( std::string test, double calc, double expect, 
                        double tolerance );

    /**
     * Print result for tests.
     *
     * @param module - Name class execute test.
     * @param failed - Tests executed.
     * @return Result tests.
     */
    static int print_result( std::string module, int failed );

  private:
    /**
     * Count tests executed.
     *
     * @return Number of the tests executed.
     */ 
    static inline int count( void ) {
      return t_number_;
    }

  protected:
    /// Holds number of tests.
    static int t_number_;
  };

/**
 * Macro explain result tests.
 */
#define GEN_TEST_RESULT( msg, calc, expect, tolerance ) \
  genesis::tests::result( msg, calc, expect, tolerance );

/**
 * Macro prints result for tests.
 */
#define GEN_TEST_PRINT_RESULT( msg, failed ) \
  genesis::tests::print_result( msg, failed );

}

#endif // GENESIS_TESTS_HPP
