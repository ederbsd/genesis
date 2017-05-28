/**
 * @file
 *
 * Definitions for an string_util.
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
#ifndef GENESIS_STRING_UTIL_HXX
#define GENESIS_STRING_UTIL_HXX

#include <string>
#include <sstream>
#include <vector>

namespace genesis {
/**
 * Genesis String Util Class.
 */
class string_util
{
public:
    /**
     * Constructor.
     */
    string_util() {};

    /**
     * Destructor.
     */
    ~string_util() {};

    /**
     * Converts a string to upper case.
     *
     * @param s The string to convert
     * @return The uppercase string
     */
    static std::string to_uppercase( const std::string &s );

    /**
     * Removes a specified character from the left side of a string.
     *
     * @param s The string to trim
     * @param c Character to trim
     * @return Trimmed string
     */
    std::string left_trim( const std::string &s, char c = ' ' );

    /**
     * Removes a specified character from the right side of a string.
     *
     * @param s The string to trim
     * @param c Character to trim
     * @return Trimmed string
     */
    std::string right_trim( const std::string &s, char c = ' ' );

    /**
     * Removes a specified character from the left and right sides of a string.
     *
     * @param s - The string to trim.
     * @param c - Character to trim.
     * @return Trimmed string
     */
    inline
    std::string trim( const std::string &s, char c = ' ' )
    {
        return right_trim( left_trim( s, c ), c );
    }

    /**
     * Removes a specified character.
     *
     * @param s - The string to trim.
     */
    static void trim( std::string &s );

    /**
     * Splits the string in two parts.
     *
     * The first before the char.
     * The second after the char.
     *
     * @param s - The string to be splitted.
     * @param c - The char to use as the splitpoint.
     * @return A pair containing the part before the char and the part
     * after the char.
     */
    std::pair<std::string, std::string> split( const std::string &s, char c );

    /**
     * Split the string in a vector of strings using a char as separator.
     * If the first position of s is c, the position is discarded.
     *
     * @param s - The string to be splitted.
     * @param c - The char to use as the splitpoint.
     * @return A vector containing all parts of splitted string.
     */
    std::vector<std::string> split_all( const std::string &s, char c );

    /**
     * Convert from string.
     *
     * @param s - String to be converted.
     * @return Converted value
     */
    template<class T>
    inline static T from_string( const std::string &s )
    {
        std::istringstream ss( s );
        T t;
        ss >> t;
        return t;
    }

    /**
     * Convert from string.
     *
     * @param t - Converted value.
     * @param s String to be converted
     */
    template<class T>
    inline static void from_string( T &t, const std::string &s )
    {
        t = from_string<T>( s );
    }

    /**
     * Convert to string.
     *
     * @param t - What to convert.
     * @return Converted string
     */
    template<class T>
    inline static std::string to_string( const T &t )
    {
        std::ostringstream ss;
        ss << t;
        return ss.str();
    }

    /**
     * Convert to string.
     *
     * @param t - What to convert.
     * @param s - Converted string.
     */
    template<class T>
    inline static void to_string( const T &t, const std::string &s )
    {
        t = to_string<T>( s );
    }

};
}

#endif // GENESIS_STRING_UTIL_HXX
