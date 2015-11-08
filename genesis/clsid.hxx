/**
 * @file
 *
 * Definitions for an factory.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_CLSID_HPP
#define GENESIS_CLSID_HPP

#include <genesis/genesis.hxx>

#include <string>

namespace genesis {
  namespace dynamic_library {
    class clsid {
    public:
      /**
       * Constructor.
       */
      clsid();

      /**
       * Constructor.
       *
       * @param clsid - ID Object.
       */
      clsid( GEN_IN const clsid& clsid ) ;

      /**
       * Constructor.
       *
       * @param str_clsid - ID Object string.
       */
      clsid( GEN_IN std::string str_clsid ) ;

      /**
       * Destructor.
       */
      virtual ~clsid() ;
	
      clsid& operator=( GEN_IN clsid& clsid );
      clsid& operator=( GEN_IN std::string str_clsid );

      bool operator==( GEN_IN genesis::dynamic_library::clsid clsid );

      bool operator==( GEN_IN std::string str_clsid );
      bool operator==( GEN_IN char* str_clsid );
      bool operator<( GEN_IN const clsid& clsid ) const;
      bool operator>( GEN_IN const clsid& clsid ) const;

      /**
       * Ostream operator print result.
       *
       * @param s - Output stream to print.
       * @param clsid - Point to print.
       * @return Output stream.
       */
      friend std::ostream& operator <<( std::ostream& s,
       const dynamic_library::clsid& clsid );

      /// Long int quadword[4];
      std::string id_;
    };

  }
}

#endif // GENESIS_CLSID_HPP
