/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/common/mutex.h                                                   *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, rAthena                                                  *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/

#ifndef _rA_MUTEX_H_
#define _rA_MUTEX_H_


typedef struct ramutex *ramutex; // Mutex
typedef struct racond *racond; // Condition Var

/**
 * Creates a Mutex
 *
 * @return not NULL
 */
ramutex ramutex_create();

/**
 * Destroys a Mutex
 *
 * @param m - the mutex to destroy
 */
void ramutex_destroy(ramutex m);

/**
 * Gets a lock
 *
 * @param m - the mutex to lock
 */
void ramutex_lock(ramutex m);

/**
 * Trys to get the Lock
 *
 * @param m - the mutex try to lock
 *
 * @return boolean (true = got the lock)
 */
bool ramutex_trylock(ramutex m);

/**
 * Unlocks a mutex
 *
 * @param m - the mutex to unlock
 */
void ramutex_unlock(ramutex m);


/**
 * Creates a Condition variable
 *
 * @return not NULL
 */
racond racond_create();

/**
 * Destroy a Condition variable
 *
 * @param c - the condition varaible to destroy
 */
void racond_destroy(racond c);

/**
 * Waits Until state is signalled
 *
 * @param c - the condition var to wait for signalled state
 * @param m - the mutex used for syncronization
 * @param timeout_ticks - timeout in ticks ( -1 = INFINITE )
 */
void racond_wait(racond c,  ramutex m,  sysint timeout_ticks);

/**
 * Sets the given condition var to signalled state
 *
 * @param c - condition var to set in signalled state.
 *
 * @note:
 *  Only one waiter gets notified.
 */
void racond_signal(racond c);

/**
 * Sets notifys all waiting threads thats signalled.
 * @param c - condition var to set in signalled state
 *
 * @note:
 *  All Waiters getting notified.
 */
void racond_broadcast(racond c);


#endif
