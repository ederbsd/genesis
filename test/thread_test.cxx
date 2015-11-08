/**
 * @file
 *
 * Tests for an exception thread.
 *
 * GENESIS - Library of general purpose classes
 *
 * Copyright (c) 2009 Ederson de Moura
 *
 * @author Ederson de Moura
 *
 * @mainteiner: ederbsd@gmail.com
 *
 * $Id: Exp$
 */

#include <genesis/thread.hxx>

using namespace genesis;

class c_increment_thread : public genesis::c_thread {
public:
  /// Constructor.
  c_increment_thread() {
    counter = 0;
  };

  /// Destructor.
  ~c_increment_thread() {};

  /// Counter.
  int counter;

  virtual proto_th::GEN_BOOL on_task( proto_th::GEN_VOID th_data_obj ) {
    proto_th::thread_id_t id;
    get_id( &id );
    if( th_data_obj ) {
      int* pInt = ( int* )th_data_obj;
      printf( "\tthread(%ld, counter+%d=%d, counter incremented\n", 
              id, *pInt,( counter += *pInt ) );
    }
    return GEN_SET_TRUE;
  }

  virtual proto_th::GEN_BOOL on_task() {
    proto_th::thread_id_t id;
    get_id( &id );
    m_mutex.lock();  
    printf( "\tthread(%ld, counter++= %d, counter incremented)\n",
            id, ( ++counter ) );
    m_mutex.unlock();
    return GEN_SET_TRUE;
  }

  int get_value() {
    int counterValue = 0;
    m_mutex.lock();
    counterValue = counter;
    m_mutex.unlock();
    return counter;
  }

  void reset() {
    m_mutex.lock();
    counter = 0;
    m_mutex.unlock();
  }
};

class c_task_incrementer: public genesis::task {
public:
  /// Constructor.
  c_task_incrementer() { 
    counter = 0; 
  };

  /// Destructor.
  ~c_task_incrementer() {};

  void set_incr( int iValue )  {
    m_mutex.lock();
    incr = iValue;
    m_mutex.unlock();
  }

  int get_increment_value() {
    int incr_value = 0;

    m_mutex.lock();
    incr_value = incr;
    m_mutex.unlock();

    return incr_value;
  }

  int get_value() {
    int counterValue = 0;
    m_mutex.lock();
    counterValue = counter;
    m_mutex.unlock();
    return counter;
  }

  proto_th::GEN_BOOL c_task() {
    proto_th::thread_id_t id;
    thread( &id );

    m_mutex.lock();
    printf( "\tthread( %ld, counter+%d=%d, counter incremented )\n",
            id, incr, ( counter += incr ) );
    m_mutex.unlock();
    return GEN_SET_TRUE;
  }

private:
  int counter; ///< Counter
  int incr;    ///< Incrementer.
};

class my_task: public genesis::task {
public:
  /// Constructor.
  my_task() {};
  
  /// Destructor.
  ~my_task() {};
  proto_th::GEN_BOOL c_task() {
    GEN_MSG( "\tPerformed a ctask task\n" );
    return GEN_SET_TRUE;
  }

};

int main( int argc, char* argv[] )
{
  int increment = 10;

  c_increment_thread* p_thread_inc;

  GEN_MSG( "\n****** T H R E A D  T E S T *********\n\n" );
  GEN_MSG( "--INSTANTIATING CINCREMENTTHREAD DERIVED FROM CTHREAD\n" );

  p_thread_inc = new c_increment_thread;

  if( p_thread_inc ) {
    if( p_thread_inc->run_thread( 500 ) ) {
      GEN_MSG( "\nSENDING EVENT + 10\n" );
      p_thread_inc->event( ( proto_th::GEN_VOID )&increment );
      gen_sleep( 500 );
      GEN_MSG( "\nSENDING EVENT ++\n" );
      p_thread_inc->event();
      gen_sleep( 500 );
    } else {
      GEN_ERROR( "\nTHREAD DID NOT START\n" );
    }

    GEN_MSG( "\n--CHANGING THREAD MODEL TO INTERVAL BASED\n" );
    p_thread_inc->set_thread_type( TH_TYPE_INTERVAL_DRIVEN, 100 );
    gen_sleep( 500 );
    GEN_MSG( "\n--CHANGING THREAD MODEL BACK TO EVENT DRIVEN\n" );
    p_thread_inc->set_thread_type( TH_TYPE_EVENT_DRIVEN );
    gen_sleep( 500 );
    GEN_MSG( "\n--SENDING + 10\n" );
    p_thread_inc->event((proto_th::GEN_VOID)&increment);
    gen_sleep( 500 );
    GEN_MSG( "\n--DESTROYING OBJECT...\n" );
    //delete p_thread_inc;
    gen_sleep( 500 );
  } else {
    GEN_ERROR( "FAILED TO ALLOCATE THREAD\n" );
  }

   GEN_MSG( "\n--INSTANTIATING AN ARRAY OF TEN CINCREMENTTHREADS DERIVED FROM CTHREAD\n" );
   p_thread_inc = new c_increment_thread[10];

   if( p_thread_inc ) {
     if( p_thread_inc[9].run_thread( 2000 ) ) {
       int i = 0;
       for( i = 0; i < 10; i++ ) {
         p_thread_inc[i].event();
       }
       gen_sleep(500);
       GEN_MSG( "\n\n--DESTROYING OBJECT ARRAY\n" );
       delete[] p_thread_inc;
     } else {
       GEN_ERROR( "\nTHREADS DID NOT START\n" );
     }
  } else {
    GEN_ERROR( "FAILED TO ALLOCATE THREADS\n" );
  }

  GEN_MSG( "\n--INSTANTIATING A CINCRMENTTHREAD BY DECLARATION\n" );
  {
    c_increment_thread th;

    if( th.run_thread( 2000 ) ) {
      GEN_MSG( "\nSENDING EVENT\n" );
      th.event();
      gen_sleep( 500 );
    } else {
      GEN_MSG( "FAILED TO START THREAD\n" );
    }
    GEN_MSG( "\nLEAVING SCOPE\n" );
  }

  GEN_MSG( "\n--INSTANTIATING A CINCREMENTTHREAD BY DECLARATION\n" );
  {
    c_increment_thread my_th; 
    int two = 2;
    while( my_th.get_value() < 20 ) {
      my_th.event();
      gen_sleep( 100 );
    }

    my_th.reset();
    
    while( my_th.get_value() < 40 ) {
      my_th.event( &two );
      //gen_sleep( 100 );
    }
  }

  /*
  GEN_MSG( "\n--INSTANTIATING THE ORIGIONAL CTHREAD CLASS BY DECLARATION\n" );
  {
    my_task my_task;
    c_thread thread;
    thread.event( &my_task );

    while( my_task.status() != TASK_STATUS_COMPLETED ) {
      gen_sleep( 500 );
    }

    thread.event( &my_task );
    my_task.wait( 1 );
  }*/
  
  GEN_MSG( "\n--INSTANTIATING THE ORIGIONAL CTHREAD CLASS BY DECLARATION\n" );
  {
    my_task* p_my_task = new my_task;
    c_thread thread;
    thread.event( p_my_task );

    if( p_my_task->wait( 1 ) )  {
      GEN_MSG( "\tFreeing p_my_task\n" );
    }
  }

  /*
  GEN_MSG( "\n--INSTANTIATING a CTHREAD AND USING A CTASK OBJECT\n" );
  {
    c_task_incrementer incr;
    c_thread thr;
    incr.set_incr( 2 );

    while( incr.get_value() < 40 ) {
      thr.event( &incr );
      gen_sleep( 100 );
    }
  }*/

  GEN_MSG( "\nDone.\n" );
  return 0;
}
