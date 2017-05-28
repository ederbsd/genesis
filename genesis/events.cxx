/**
 * @file
 *
 * Implementation for an event.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_EVENTS_HXX_
#include <genesis/thread.hxx>
#endif

namespace genesis {

events::events()
    : m_bcreated( genesis::GEN_SET_TRUE )
{
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init( &mattr );
    pthread_mutex_init( &m_lock, &mattr );
    pthread_cond_init( &m_ready, 0 );
}

events::~events()
{
    pthread_cond_destroy( &m_ready );
    pthread_mutex_destroy( &m_lock );
}

void events::set()
{
    pthread_mutex_lock( &m_lock );
    pthread_mutex_unlock( &m_lock );
    pthread_cond_signal( &m_ready );
}

proto_th::GEN_BOOL events::wait()
{
    pthread_mutex_lock( &m_lock );
    pthread_cond_wait( &m_ready, &m_lock );
    return genesis::GEN_SET_TRUE;
}

void events::reset()
{
    pthread_mutex_unlock( &m_lock );
}

}
