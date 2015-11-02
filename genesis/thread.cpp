/**
 * @file
 *
 * Implementation for an thread.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * $Id: Exp$
 */

#include <genesis/thread.hpp>

#define NO_ERRORS 0
#define MUTEX_CREATION 0x01
#define EVENT_CREATION 0x02
#define THREAD_CREATION 0x04
#define UNKNOWN 0x08
#define ILLEGAL_USE_OF_EVENT 0x10
#define MEMORY_FAULT 0x20

namespace genesis {

  extern "C" {
   int usleep( useconds_t useconds );
#ifdef GEN_NANO_SECOND_SLEEP
   int nanosleep( const struct timespec* rqtp, struct timespec* rmtp );
#endif
  }

  void gen_sleep( unsigned int milli ) {
#ifdef GEN_NANO_SECOND_SLEEP
    struct timespec interval, remainder;
    milli = milli * 1000000;
    interval.tv_sec = 0;
    interval.tv_nsec = milli;
    nanosleep( &interval, &remainder );
#else
    usleep( milli * 1000 );
#endif	
  }

  proto_th::GEN_VOID TH_KERNEL( proto_th::GEN_VOID th_data_obj )
  {
    c_thread* p_thread = ( c_thread* )th_data_obj;
    thread_type_t last_type;

    // Init.
    p_thread->m_mutex.lock();
    p_thread->m_state = TH_WAITING;
    p_thread->m_brunning = GEN_SET_TRUE;
    p_thread->m_mutex.unlock();

    while( GEN_SET_TRUE ) {
      last_type = p_thread->m_type;

      if( last_type == TH_TYPE_EVENT_DRIVEN ) {
        if( !p_thread->m_event.wait()  ) {
	  break;
         }
      }

      if( !p_thread->kernel_process() ) {
        break;
      }

      if( last_type == TH_TYPE_EVENT_DRIVEN ) {
        p_thread->m_event.reset();
      }

      if( p_thread->m_type == TH_TYPE_INTERVAL_DRIVEN ) {
        gen_sleep( p_thread->m_dwidle );
      }

    }

    p_thread->m_mutex.lock();
    p_thread->m_state = TH_DOWN;
    p_thread->m_brunning = GEN_SET_FALSE;
    p_thread->m_mutex.unlock();

    return ( proto_th::GEN_VOID )0;
  }

  proto_th::GEN_BOOL c_thread::on_task( proto_th::GEN_VOID th_data_obj )
  {
    task* p_task = ( task* )th_data_obj;
    p_task->set_task_status( TASK_STATUS_BEING_PROCESSED );

    proto_th::GEN_BOOL bReturn = p_task->c_task();
    p_task->set_task_status( TASK_STATUS_COMPLETED );
    return bReturn;
  } 

  proto_th::GEN_BOOL c_thread::on_task()
  {
    GEN_MSG( "\nThread is alive!\n" );
    return GEN_SET_TRUE;
  }

  proto_th::GEN_BOOL c_thread::event( task* pv_task )
  {
    proto_th::thread_id_t id;
    m_mutex.lock();

    if( m_type != TH_TYPE_EVENT_DRIVEN ) {
      m_mutex.unlock();
      m_dw_object_condition |= ILLEGAL_USE_OF_EVENT;
      m_state = TH_FAULT;
      return GEN_SET_FALSE;
    }

    m_mutex.unlock();
    get_id( &id );
    pv_task->set_id( &id );

    if( !push( ( proto_th::GEN_VOID )pv_task ) ) {
      return GEN_SET_FALSE;
    }

    pv_task->set_task_status( TASK_STATUS_WAITING_ON_QUEUE );
    m_event.set();

    return GEN_SET_TRUE;
  }

  proto_th::GEN_BOOL c_thread::event( proto_th::GEN_VOID th_data_obj )
  {
    m_mutex.lock();

    if( m_type != TH_TYPE_EVENT_DRIVEN ) {
      m_mutex.unlock();
      m_dw_object_condition |= ILLEGAL_USE_OF_EVENT;
      m_state = TH_FAULT;
      return GEN_SET_FALSE;
    }

    m_mutex.unlock();

    if( !push( th_data_obj ) ) {
      return GEN_SET_FALSE;
    }

    m_event.set();
    return GEN_SET_TRUE;
  }

  proto_th::GEN_BOOL c_thread::kernel_process()
  {
    m_mutex.lock();
    m_state = TH_BUSY;

    if( !m_brunning ) {
      m_state = TH_SHUTDOWN;
      m_mutex.unlock();
      return GEN_SET_FALSE;
    }

    m_mutex.unlock();

    if( !empty() ) {
      while( !empty() ) {
        pop();
	if( !on_task( m_lpvprocessor ) ) {
          m_mutex.lock();
          m_lpvprocessor = 0;
          m_state = TH_SHUTDOWN;
          m_mutex.unlock();
          return GEN_SET_FALSE;
	}
      }
      m_mutex.lock();
      m_lpvprocessor = 0;
      m_state = TH_WAITING;
    } else {
      if( !on_task() ) {
        m_mutex.lock();
	m_state = TH_SHUTDOWN;
	m_mutex.unlock();
	return GEN_SET_FALSE;
      } 
      m_mutex.lock();
      m_state = TH_WAITING;
    }

    m_mutex.unlock();
    return GEN_SET_TRUE;
  }

  unsigned int c_thread::get_events_pending()
  {
    unsigned int ch_events_waiting = 0;

    m_mutex.lock();
    ch_events_waiting = m_quepos;
    m_mutex.unlock();

    return ch_events_waiting;
  }

  c_thread::c_thread()
   : m_brunning( GEN_SET_FALSE ),
     m_dwid( 0L ), 
     m_lppvque( 0 ),
     m_chque( QUE_SIZE ),
     m_quepos( 0 ),
     m_lpvprocessor( 0 ),
     m_state( TH_DOWN ),
     m_dwidle( 100 ),
     m_type( TH_TYPE_EVENT_DRIVEN ),
     m_stack_size( DEFAULT_STACK_SIZE )
  {
    m_dw_object_condition = NO_ERRORS;
    m_lppvque = new proto_th::GEN_VOID[ QUE_SIZE ];

    if( !m_lppvque ) {
      m_dw_object_condition |= MEMORY_FAULT;
      m_state = TH_FAULT;
      return;
    }

    if( !m_mutex.m_bcreated ) {
      GEN_ERROR( "Mutex creation failed!" );
      m_dw_object_condition |= MUTEX_CREATION;
      m_state = TH_FAULT;
      return;
    }

    if( !m_event.m_bcreated ) {
      GEN_ERROR( "Event creation failed!" );
      m_dw_object_condition |= EVENT_CREATION;
      m_state = TH_FAULT;
      return;
    }

    start();
  }

  proto_th::GEN_BOOL c_thread::empty()
  {
    m_mutex.lock();

    if( m_quepos <= 0 ) {
      m_mutex.unlock();
      return GEN_SET_TRUE;
    }

    m_mutex.unlock();
    return GEN_SET_FALSE;
  }

  proto_th::GEN_BOOL c_thread::push( proto_th::GEN_VOID lpv )
  {
    if( !lpv ) {
      return GEN_SET_TRUE;
    }

    m_mutex.lock();

    if( m_quepos + 1 >= m_chque ) {
      m_mutex.unlock();
      return GEN_SET_FALSE;
    }

    m_lppvque[m_quepos++] = lpv;
    m_mutex.unlock();
    return GEN_SET_TRUE;
  }

  proto_th::GEN_BOOL c_thread::pop()
  {
    m_mutex.lock();

    if(m_quepos - 1 <= 0) {
      m_quepos = 0;
      m_mutex.unlock();
      return GEN_SET_FALSE;
    }

    m_quepos--;
    m_lpvprocessor = m_lppvque[m_quepos];
    m_mutex.unlock();
    return GEN_SET_TRUE;
  }

  void c_thread::set_thread_type( thread_type_t typ, proto_th::GEN_DWORD idl )
  { 
    m_mutex.lock();
    m_dwidle = idl;
	
    if( m_type == typ ) {
      m_mutex.unlock();
      return;
    }

    m_type = typ;
    m_mutex.unlock();

    m_event.set();
  }  

  void c_thread::stop()
  {
    m_mutex.lock();
    m_brunning = GEN_SET_FALSE;
    m_mutex.unlock();
    event();

    gen_sleep( m_dwidle );

    while( GEN_SET_TRUE ) {
      m_mutex.lock();
      if( m_state == TH_DOWN ) {
        m_mutex.unlock();
	return;
      }
      m_mutex.unlock();
      gen_sleep( m_dwidle );
    }

    return;
  }

  void c_thread::set_idle( proto_th::GEN_DWORD idl )
  {
    m_mutex.lock();
    m_dwidle = idl;
    m_mutex.unlock();
  }

  proto_th::GEN_BOOL c_thread::start()
  {
    m_mutex.lock();

    if( m_brunning ) {
      m_mutex.unlock();
      return GEN_SET_TRUE;
    }

    m_mutex.unlock();

    if( m_dw_object_condition & THREAD_CREATION ) {
      m_dw_object_condition = m_dw_object_condition ^ THREAD_CREATION;
    }

    pthread_attr_t attr;
    pthread_attr_init( &attr );

    if( m_stack_size != 0 ) {
      pthread_attr_setstacksize(&attr,m_stack_size);
    }

    register int error = pthread_create( &m_thread, 
                                         &attr, 
                                         TH_KERNEL, 
                                         ( proto_th::GEN_VOID )this );

    if( error != 0 ) {
      m_dw_object_condition |= THREAD_CREATION;
      m_state = TH_FAULT;

#if defined( HPUX ) || defined( SUNOS ) || \
 defined( LINUX ) || defined( FREEBSD )
      switch( error ) {
      case EINVAL:
        GEN_ERROR( "attr in an invalid thread attributes object!" );
	break;
      case EAGAIN:
        GEN_ERROR( "The necessary resources to create a thread are " 
                   "not available!" );
	break;
      case EPERM:
        GEN_ERROR( "The caller does not have the privileges to create. "
                   "The thread with the specified attr object." );
	break;
#if defined( HPUX )
      case ENOSYS:
        GEN_ERROR( "Ops... pthread_create not implemented!" );
	if(  __is_threadlib_linked() == 0 ) {
          GEN_ERROR( "Genesis threaded library not being used, improper "
                     "linkage '-lpthread -lc'!" );
	}
        break;
#endif
      default:
        GEN_ERROR( "An unknown error was encountered attempting to "
                   "create the requested thread." );
	break;
#else
      GEN_ERROR( "Could not create thread, pthread_create failed: " );
      GEN_ERROR( error );
#endif
      return GEN_SET_FALSE;
      }

    return GEN_SET_TRUE;
  }

  thread_state_t c_thread::thread_state()
  {
    thread_state_t current_state;
    m_mutex.lock();
    current_state = m_state;
    m_mutex.unlock();
    return current_state;
  }

  c_thread::~c_thread()
  {
    proto_th::GEN_VOID lpv;

    if( m_brunning ) {
      stop();
      pthread_join( m_thread, &lpv );
    }

    delete[] m_lppvque;
  }

  proto_th::GEN_BOOL c_thread::run_thread( proto_th::GEN_DWORD dw_timeout )
  {
    proto_th::GEN_DWORD dw_total = 0;

    while( GEN_SET_TRUE) {
      if( dw_total > dw_timeout && dw_timeout > 0 ) {
        return GEN_SET_FALSE;
      }
      m_mutex.lock();

      if( m_brunning ) {
        m_mutex.unlock();
        return GEN_SET_TRUE;
      }

      dw_total += m_dwidle;
      m_mutex.unlock();
      gen_sleep( m_dwidle );
    }

    return GEN_SET_FALSE;
  }

} // Name
