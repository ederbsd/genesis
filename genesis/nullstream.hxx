/**
 * @file
 *
 * Definitions for an nullstream.
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
#ifndef GENESIS_NULLSTREAM_HXX
#define GENESIS_NULLSTREAM_HXX

#include <streambuf>
#include <ostream>

namespace genesis {
/**
 * Genesis Null stream buffer class.
 */
template<class charT, class traits = ::std::char_traits<charT> >
class null_buffer : public ::std::basic_streambuf<charT, traits>
{
public:
    /**
     * Constructor.
     */
    null_buffer() {};

    /**
     * Destructor.
     */
    virtual ~null_buffer() {};

    /// XXX:
    typedef typename ::std::basic_streambuf<charT, traits>::int_type int_type;

private:

    virtual int_type overflow( int_type c )
    {
        // Just ignore the character.
        return traits::not_eof(c);
    }
};

/**
 * Genesis Generic null output stream class.
 */
template <class charT, class traits = ::std::char_traits<charT> >
class basic_null_stream : private null_buffer<charT, traits>,
    public ::std::basic_ostream<charT, traits>
{
public:
    /**
     * Constructor.
     */
    basic_null_stream() :
        ::std::basic_ostream<charT, traits>( this )
    {
    }

};

/// Helper declaration for narrow and wide streams.
typedef basic_null_stream<char> null_stream;

/// Helper declaration for narrow and wide streams.
typedef basic_null_stream<wchar_t> null_wstream;

}

#endif // GENESIS_NULLSTREAM_HXX
