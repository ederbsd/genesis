/**
 * @file
 *
 * Implementation for an mutex.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_THREAD_HXX
#include <genesis/thread.hxx>
#endif

namespace genesis {

mutex::mutex()
    : m_bcreated( GEN_SET_TRUE )
{
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init( &mattr );
    pthread_mutex_init( &m_mutex, &mattr );
}

mutex::~mutex()
{
    pthread_mutex_lock( &m_mutex );
    pthread_mutex_unlock( &m_mutex );
    pthread_mutex_destroy( &m_mutex );
}

void mutex::lock()
{
    proto_th::thread_id_t id = c_thread::thread_id();

    if ( c_thread::thread_ids_equal( &m_owner, &id ) ) {
        // The mutex is already locked by this thread.
        return;
    }

    pthread_mutex_lock( &m_mutex );
    m_owner = c_thread::thread_id();
}

void mutex::unlock()
{
    proto_th::thread_id_t id = c_thread::thread_id();

    if ( !c_thread::thread_ids_equal( &id, &m_owner ) ) {
        // On the thread that has locked the mutex can
        // release the mutex.
        return;
    }

    std::memset( &m_owner, 0, sizeof( proto_th::thread_id_t ) );
    pthread_mutex_unlock( &m_mutex );
}

}
