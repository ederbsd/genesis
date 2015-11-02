/**
 * @file
 *
 * Tests for an datetime class.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <genesis/datetime.hpp>
#include <genesis/logger.hpp>

#include <iostream>
#include <cstdio>

// Test methods dynamical time.
/*
static int dynamical_time_test( void )
{
}
*/

int main( int argc, char* argv[] ) 
{
  genesis::datetime::current_datetime();

  return 0;
}
