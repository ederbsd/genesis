/**
 * @file
 *
 * Definitions for an events.
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
#ifndef GENESIS_EVENTS_HXX
#define GENESIS_EVENTS_HXX

#include <genesis/proto_types.hxx>

namespace genesis {
/**
 * A Genesis event thread objects.
 */
class events
{
public:
    /**
     * Constructor.
     */
    events();

    /**
     * Destructor.
     */
    ~events();

    /**
     * Set an event to signaled.
     */
    void set();

    /**
     * Wait for events. Wait for an event object to
     * be set to signaled.
     */
    proto_th::GEN_BOOL wait();

    /**
     * Reset an event flag to unsignaled.
     */
    void reset();

    proto_th::GEN_BOOL m_bcreated; ///< Check event created.

private:
    pthread_cond_t m_ready;
    pthread_mutex_t m_lock;

};

}

#endif // GENESIS_EVENTS_HXX
