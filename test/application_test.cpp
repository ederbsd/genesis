/**
 * @file
 *
 * Tests for an application class.
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

#include <genesis/application.hpp>
#include <genesis/string_util.hpp>

class application_test : public genesis::application {
  public:  
    /// Constructor.
    application_test();

    /// Destructor.
    ~application_test();

  private:
    // Override.
    int main( int argc, char* argv[] );

    /// Print usage message to console.
    void usage() const;

    /// Print version message to console.
    void version() const;
};

application_test::application_test() 
  : genesis::application()
{
}

application_test::~application_test()
{
}

void application_test::usage() const
{
}

void application_test::version() const
{
  std::cout << "\n" << name() << "Version " << VERSION << ". "
            << "Part of the " << genesis::string_util::to_uppercase( PACKAGE )
            << " package.\n\n"
            << "Copyright (C) 2009 "
            << "Ederson de Moura.\n"
            << std::endl;
}

int application_test::main( int argc, char* argv[] )
{
  version();
  return 0;
}

int main( int argc, char* argv[] ) 
{
  return application_test().run( argc, argv );
}
