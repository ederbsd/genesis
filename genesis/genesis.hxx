/**
 * @file
 *
 * Definitions for an genesis.
 *
 * GENESIS - Library of general purpose classes.
 *
 * Copyright (c) 2009-2015 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#pragma once
#ifndef GENESIS_GENESIS_HXX
#define GENESIS_GENESIS_HXX

/// Name package project.
#define PACKAGE "genesis"

/// Version package project.
#define VERSION "1.0"

/// Bug email report.
#define PACKAGE_BUGREPORT "ederbsd@gmail.com"

#include <cstdio>

namespace genesis {
/**
 * Class Genesis Library.
 */
class library
{
public:
    /**
     * Destructor.
     */
    virtual ~library();

    /**
     * Shows details of the compilation.
     */
    static void check_build_details();

    /**
     * Get library version string.
     *
     * @return Library version string.
     */
    static const char *version();

    /**
     * Get information the package.
     *
     * @return Package string.
     */
    static const char *package();

    /**
     * Check computer architecture is Big Endian.
     *
     * @return True if Big Endian, false otherwise.
     */
    static bool is_big_endian();

private:
    /**
     * Private Constructor.
     */
    library();
};

/**
 * Genesis Types Class.
 */
class types : public library
{
public:
    /**
     * Destructor.
     */
    ~types() {};

    /// Type Vector.
    typedef double vector[3];

    /// Type Matrix.
    typedef double matrix[9];
};

/**
 * Namespace Used only for the module Dynamic Library.
 */
namespace dynamic_library {

#define GEN_IN    ///< In.
#define GEN_OUT   ///< Out. 
#define GEN_INOUT ///< In or Out.

/// LD library some errors.
#define GEN_E_NOERR 0         ///< OK. Success!
#define GEN_E_NOINTERFACE -1  ///< Requested interface isn't supported.

/// Some data types.
typedef signed long GEN_LIBRARY_HRESULT;

/**
 * Returns a factory object for the objects defined in
 * the library.
 */
class factory;
typedef factory *( * get_class_object_func ) ();

/**
 * Enumerates the available classes in a NULL-terminated
 * array.
 */
class clsid;
typedef clsid *( * get_available_classes_func ) ();

}

/**
 * This namespace works as if anything inside it were declared
 * staticaly in each source file.
 */
namespace {
}

}

#endif // GENESIS_GENESIS_HXX
