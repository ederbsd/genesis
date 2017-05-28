/**
 * @file
 *
 * Definitions for an system.
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
#ifndef GENESIS_SYSTEM_HXX
#define GENESIS_SYSTEM_HXX

#include <string>

namespace genesis {
/**
 * Genesis System Class.
 */
class system
{
public:
    /**
     * List files in a directory.
     *
     * @param path - Where is the directory to be listed?
     */
    static char **list_files( const std::string path );

    /**
     * Copy file.
     */
    static bool copy_file( const std::string &from, const std::string &to );

    /**
     * Exec system command.
     *
     * @param cmd - Command execute.
     */
    static int exec_cmd( const std::string cmd );

    /**
     * Remove file and directorie.
     *
     * @param path - Dir or file to be removed.
     */
    static int remove( const std::string path );

    /**
     * Rename file and directorie.
     *
     * @param from - Atual dir or file.
     * @param to - New dir or file renamed.
     */
    static int rename( const std::string from, const std::string to );

};
}

#endif // GENESIS_SYSTEM_HXX
