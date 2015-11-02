/**
 * @file
 *
 * Definitions for an thread.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#ifndef GENESIS_THREAD_HPP
#define GENESIS_THREAD_HPP

#include <genesis/logger.hpp>
#include <genesis/proto_types.hpp>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <genesis/events.hpp>
#include <genesis/mutex.hpp>

extern "C" {
#include <pthread.h>
}

namespace genesis {

  static const int QUE_SIZE = 100;
  static const int DEFAULT_STACK_SIZE = 0;
  static const int GEN_SET_TRUE = 1;
  static const int GEN_SET_FALSE = 0;

  void gen_sleep( unsigned int mseconds );

  typedef enum {
    TH_BUSY,     ///< Thread is currently handling a task.
    TH_WAITING,  ///< Thread is waiting for something to do.
    TH_DOWN,     ///< Thread is not running.
    TH_SHUTDOWN, ///< Thread is in the process of shut down.
    TH_FAULT     ///< Error has occured and the thread could not be launched.
  } thread_state_t;

  typedef enum {
    TH_TYPE_EVENT_DRIVEN,
    TH_TYPE_INTERVAL_DRIVEN
  } thread_type_t;

  typedef enum {
    TASK_STATUS_NOT_SUBMITTED,
    TASK_STATUS_WAITING_ON_QUEUE,
    TASK_STATUS_BEING_PROCESSED,
    TASK_STATUS_COMPLETED
  } task_status_t;

  class task {
  public:
    /**
     * Constructor.
     */
    task() {
      m_state = TASK_STATUS_NOT_SUBMITTED;
      std::memset( &m_dw_thread, 0, sizeof( proto_th::thread_id_t ) );
    };

    /**
     * Destructor.
     */
    ~task() {};

    /**
     * Set task status.
     *
     * @param state - Status.
     */
    void set_task_status( task_status_t state ) {
      m_mutex.lock();
      m_state = state;
      m_mutex.unlock();
    }

    /**
     * Set ID thread.
     *
     * @param pid - Pid running thread.
     */
    void set_id( proto_th::thread_id_t* pid ) {
      std::memcpy( &m_dw_thread, pid, sizeof( proto_th::thread_id_t ) );
    }

    /**
     * Wait for upto timeout seconds for a task to 
     * complete.
     *
     * @param timeout_secs - Timeout seconds.
     */
    proto_th::GEN_BOOL wait( int timeout_secs ) {
      timeout_secs = timeout_secs * 1000;

      if( status() != TASK_STATUS_COMPLETED && timeout_secs > 0 ) {
        gen_sleep( 100 );
        timeout_secs = timeout_secs - 100;
      }

      if( status() == TASK_STATUS_COMPLETED ) {
        return GEN_SET_TRUE;
      }

      return GEN_SET_FALSE;
    }

    /**
     * Where returns current state of a task.
     */
    task_status_t status() {
      task_status_t state;

      m_mutex.lock();
      state = m_state;
      m_mutex.unlock();

      return state;
    }

    /**
     * Thread.
     *
     * @param p_id - Id thread.
     */
    void thread( proto_th::thread_id_t* p_id ) {
      std::memcpy( p_id, &m_dw_thread, sizeof( proto_th::thread_id_t ) );
    }

    /**
     * Method pure virtual.
     */
    virtual proto_th::GEN_BOOL c_task() = 0;

  private:
    task_status_t m_state;   ///< Task status.
    proto_th::thread_id_t m_dw_thread; /// DW Thread.

  protected:
    mutex m_mutex; ///< Mutex instance.
  };

  /**
   * A Genesis Thread represents a separate thread of control within 
   * the program; it shares data with all the other threads within the 
   * process but executes independently in the way that a separate program 
   * does on a multitasking operating system.
   */
  class c_thread {
  public:
    /**
     * Constructor.
     */
    c_thread();

    /**
     * Destructor.
     */
    ~c_thread();

    mutex m_mutex; ///< Mutex that protects threads internal data.

    /**
     * Called when an event occurs.
     *
     * @param th_data_obj - Thread data object.
     */
    virtual proto_th::GEN_BOOL on_task( proto_th::GEN_VOID th_data_obj );

    /**
     * Called when a time interval has elapsed.
     */
    virtual proto_th::GEN_BOOL on_task();

    /**
     * Thread callback function used by Create Thread.
     *
     * @param th_data_obj - Thread data object.
     */
    friend proto_th::GEN_VOID TH_KERNEL( proto_th::GEN_VOID th_data_obj );

    /**
     * Kernel Process routes thread activity.
     */
    proto_th::GEN_BOOL kernel_process();

    /**
     * Waves up thread to process data.
     *
     * @param pv_task - Data to be processed by thread.
     */
    proto_th::GEN_BOOL event( task* pv_task );

    /**
     * Waves up thread to process data.
     *
     * @param th_data_obj - Thread data object.
     */
    proto_th::GEN_BOOL event( proto_th::GEN_VOID th_data_obj = 0 );

    /**
     * Stop Thread.
     */
    void stop();

    /**
     * Start Thread.
     */
    proto_th::GEN_BOOL start();

    /** 
     * Return thread ID.
     * 
     * @param p_id - Thread ID.
     */
    void get_id( proto_th::thread_id_t* p_id ) {
      std::memcpy( p_id, &m_dwid, sizeof( proto_th::thread_id_t ) ); 
    }

    /**
     * Return the current state of the thread.
     */
    thread_state_t thread_state();

    /**
     * Used to determine if a thread is running.
     *
     * @param dw_timeout - Timeout in milli-seconds.
     */
    proto_th::GEN_BOOL run_thread( proto_th::GEN_DWORD dw_timeout = 0 );

    /**
     * Return state of object.
     */
    proto_th::GEN_DWORD get_error_flags() { 
      return this->m_dw_object_condition; 
    }
 
    /**
     * Specifies the type of threading that is to be performed.
     *
     * @param typ - An event must be physically sent to the 
     *              thread using the event member function.
     * @param idl - An event occurs automatically every
     *              dwIdle milli seconds.
     */
    void set_thread_type( thread_type_t typ = TH_TYPE_EVENT_DRIVEN, 
      proto_th::GEN_DWORD idl = 100 );

    /**
     * Change the threads idl interval.
     *
     * @param idl - Dw IDLE.
     */
    void set_idle( proto_th::GEN_DWORD idl = 100 );

    /**
     * Return the total number of events waiting
     * in the event QUE.
     */
    unsigned int get_events_pending();

    /**
     * Check thread ID is equal.
     *
     * @param p1 - Thread ID 1.
     * @param p2 - Thread ID 2.
     */
    static proto_th::GEN_BOOL 
    thread_ids_equal( proto_th::thread_id_t* p1, proto_th::thread_id_t* p2 ) {
      return( ( *p1 == *p2 ) ? GEN_SET_TRUE:GEN_SET_FALSE );
    }

    /**
     * Return Thread ID.
     */
    static proto_th::thread_id_t thread_id() {
      proto_th::thread_id_t this_threads_id;
      this_threads_id = pthread_self();
      return this_threads_id;
    }

  private:
    events m_event; ///< Event controller.
    proto_th::GEN_BOOL m_brunning; ///< Set to 'true' if thread is running.
    pthread_t m_thread; ///< Thread handle.
    proto_th::thread_id_t m_dwid; ///< Id of this thread.
    proto_th::GEN_VOID* m_lppvque; ///< Task QUE.

    unsigned int m_chque; ///< QUE depth.
    unsigned int m_quepos; ///< Current que possition.

    proto_th::GEN_VOID m_lpvprocessor; ///< Data which is currently being processed.
    thread_state_t m_state; ///< Current state of thread see thread state data structure.
    proto_th::GEN_DWORD m_dwidle; ///< Used for gen_sleep periods.
    thread_type_t m_type; ///< Used TH types.
    proto_th::GEN_DWORD m_stack_size; ///< Thread stack size.

    proto_th::GEN_DWORD m_dw_object_condition;

    /**
     * Place a data object in the thread QUE.
     *
     * @param lpv - Data.
     */
    proto_th::GEN_BOOL push( proto_th::GEN_VOID lpv );

    /**
     * Move an object from the input QUE to the 
     * processor.
     */
    proto_th::GEN_BOOL pop();

    /**
     * Return a value of 'true' if there are no items 
     * on the thread QUE otherwise a value of 'false' 
     * is returned.
     */
    proto_th::GEN_BOOL empty();

  protected:
    
  };

}

#endif // GENESIS_THREAD_HPP
