/**
 * @file
 *
 * Definitions for an mutex.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_MUTEX_HPP
#define GENESIS_MUTEX_HPP

#include <genesis/proto_types.hxx>
#include <genesis/thread.hxx>

namespace genesis {
  /**
   * Genesis Mutex provides access serialization between thread. 
   * The purpose of a Mutex is to protect an object, data structure 
   * or section of code so that only one thread can access it at a time.
   */
  class mutex {
  public:
    /**
     * Constructor.
     */
    mutex();

    /**
     * Destructor.
     */
    ~mutex();

    proto_th::GEN_BOOL m_bcreated;

    void lock();
    void unlock();

  private:
    pthread_mutex_t m_mutex;
    proto_th::thread_id_t m_owner;
  };

}

#endif // GENESIS_MUTEX_HPP
