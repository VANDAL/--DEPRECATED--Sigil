#include <stdio.h>
#include <pthread.h>
#include "libgomp.h"
#include <pub_tool_redir.h>
#include "callgrind.h"

typedef int gomp_mutex_t;

// Use CALLGRIND_SIGIL_PTHREAD to do a Sigil callback and pass in upto 5
// arguments. Argument 1 will be which pthread call it represents. value of 0,
// 1,2,3 should mean create,join,mutex_lock,mutex_unlock. More special cases
// can be added as the implementation becomes more complex. Argument 2 will be
// to represent whether its about to start or it has just finished the
// intercepted function. 0,1 represents the corresponding case. Argument 3 
// represents the mutex address if Argument 1 is lock or unlock.

//Static Pthread Calls

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZucreateZa)(pthread_t *thread, const pthread_attr_t *attr, void *(*start) (void *), void *arg) {
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  //printf("Entered pthread_create!\n");
  CALL_FN_W_WWWW(ret, fn, thread, attr, start, arg);
  //printf("Leaving pthread_create!\n");
  CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZujoinZa)(pthread_t thread, void** value_pointer) {
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(1,0,thread,0);
  //printf("Entered pthread_join!\n");
  CALL_FN_W_WW(ret, fn, thread, value_pointer);
  //printf("Leaving pthread_join!\n");
  CALLGRIND_SIGIL_PTHREAD(1,1,thread,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZumutexZulockZa)(pthread_mutex_t *mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  //printf("Entered pthread_mutex_lock %lu!\n",mutex);
  CALL_FN_W_W(ret, fn, mutex);
  //printf("Leaving pthread_mutex_lock %lu!\n",mutex);
  CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZumutexZuunlockZa)(pthread_mutex_t *mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(3,0,mutex,0);
  //printf("Entered pthread_mutex_unlock %lu!\n",mutex);
  CALL_FN_W_W(ret, fn, mutex);
  //printf("Leaving pthread_mutex_unlock %lu!\n",mutex);
  CALLGRIND_SIGIL_PTHREAD(3,1,mutex,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZubarrierZuwaitZa)(pthread_barrier_t* bar){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("Entered pthread_mutex_barrier_wait %p!\n",bar);
  CALL_FN_W_W(ret, fn, bar);
  //printf("Leaving pthread_mutex_barrier_wait %lu!\n",bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZucondZuwaitZa)(pthread_cond_t* cond, pthread_mutex_t* mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(5,0,mutex,cond);
  //printf("Entered pthread_mutex_cond_wait %lu %lu!\n",mutex,cond);
  CALL_FN_W_WW(ret, fn, cond, mutex);
  //printf("Leaving pthread_mutex_cond_wait %lu %lu!\n",mutex,cond);
  CALLGRIND_SIGIL_PTHREAD(5,1,mutex,cond);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZucondZusignalZa)(pthread_cond_t* cond){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(6,0,0,cond);
  //printf("Entered pthread_mutex_cond_signal %lu!\n",cond);
  CALL_FN_W_W(ret, fn, cond);
  //printf("Leaving pthread_mutex_cond_signal %lu!\n",cond);
  CALLGRIND_SIGIL_PTHREAD(6,1,0,cond);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZuspinZulockZa)(pthread_spinlock_t* lock){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(7,0,lock,0);
  //printf("Entered pthread_mutex_lock %lu!\n",mutex);
  CALL_FN_W_W(ret, fn, lock);
  //printf("Leaving pthread_mutex_lock %lu!\n",mutex);
  CALLGRIND_SIGIL_PTHREAD(7,1,lock,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZuspinZuunlockZa)(pthread_spinlock_t* lock){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(8,0,lock,0);
  //printf("Entered pthread_lock_unlock %lu!\n",lock);
  CALL_FN_W_W(ret, fn, lock);
  //printf("Leaving pthread_lock_unlock %lu!\n",lock);
  CALLGRIND_SIGIL_PTHREAD(8,1,lock,0);
  return ret;
}

// Function wrapping for dynamically loaded pthread library

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZucreateZa)(pthread_t *thread, const pthread_attr_t *attr, void *(*start) (void *), void *arg) {
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("Entered pthread_create!\n");
  CALL_FN_W_WWWW(ret, fn, thread, attr, start, arg);
  //printf("Leaving pthread_create!\n");
  CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZujoinZa)(pthread_t thread, void** value_pointer) {
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(1,0,thread,0);
  printf("Entered pthread_join!\n");
  CALL_FN_W_WW(ret, fn, thread, value_pointer);
  //printf("Leaving pthread_join!\n");
  CALLGRIND_SIGIL_PTHREAD(1,1,thread,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZumutexZulockZa)(pthread_mutex_t *mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  //printf("Entered pthread_mutex_lock %lu!\n",mutex);
  CALL_FN_W_W(ret, fn, mutex);
  //printf("Leaving pthread_mutex_lock %lu!\n",mutex);
  CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZumutexZuunlockZa)(pthread_mutex_t *mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(3,0,mutex,0);
  //printf("Entered pthread_mutex_unlock %lu!\n",mutex);
  CALL_FN_W_W(ret, fn, mutex);
  //printf("Leaving pthread_mutex_unlock %lu!\n",mutex);
  CALLGRIND_SIGIL_PTHREAD(3,1,mutex,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZubarrierZuwaitZa)(pthread_barrier_t* bar){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("Entered pthread_mutex_barrier_wait %p!\n",bar);
  CALL_FN_W_W(ret, fn, bar);
  //printf("Leaving pthread_mutex_barrier_wait %lu!\n",bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZucondZuwaitZa)(pthread_cond_t* cond, pthread_mutex_t* mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(5,0,mutex,cond);
  //printf("Entered pthread_mutex_cond_wait %lu %lu!\n",mutex,cond);
  CALL_FN_W_WW(ret, fn, cond, mutex);
  //printf("Leaving pthread_mutex_cond_wait %lu %lu!\n",mutex,cond);
  CALLGRIND_SIGIL_PTHREAD(5,1,mutex,cond);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZucondZusignalZa)(pthread_cond_t* cond){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(6,0,0,cond);
  //printf("Entered pthread_mutex_cond_signal %lu!\n",cond);
  CALL_FN_W_W(ret, fn, cond);
  //printf("Leaving pthread_mutex_cond_signal %lu!\n",cond);
  CALLGRIND_SIGIL_PTHREAD(6,1,0,cond);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZuspinZulockZa)(pthread_spinlock_t* lock){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(7,0,lock,0);
  //printf("Entered pthread_mutex_lock %lu!\n",mutex);
  CALL_FN_W_W(ret, fn, lock);
  //printf("Leaving pthread_mutex_lock %lu!\n",mutex);
  CALLGRIND_SIGIL_PTHREAD(7,1,lock,0);
  return ret;
}

int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZuspinZuunlockZa)(pthread_spinlock_t* lock){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(8,0,lock,0);
  //printf("Entered pthread_lock_unlock %lu!\n",lock);
  CALL_FN_W_W(ret, fn, lock);
  //printf("Leaving pthread_lock_unlock %lu!\n",lock);
  CALLGRIND_SIGIL_PTHREAD(8,1,lock,0);
  return ret;
}

// Function wrapping for dynamically loaded OpenMP calls 

// GOMP_parallel
// Loop kick-off calls are detected, but pthread creates are used to
// initiate threads. OMP Barriers are used to "end" loops.
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZuparallel)(void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  printf("OpenMP Parallel Call Detected!\n");
  CALL_FN_v_WWWW(func, fn, data, num_threads, flags);
}

// GOMP_parallel_start
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZuparallelZustart)(void (*fn) (void *), void *data, unsigned num_threads) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  printf("OpenMP Parallel Region Start Detected!\n");
  CALL_FN_v_WWW(func, fn, data, num_threads);
}

// GOMP_parallel_end
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZuparallelZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  printf("OpenMP Parallel Region End Detected!\n");
  CALL_FN_v_v(func);
}

// gomp_mutex_lock
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZumutexZulock)(gomp_mutex_t *mutex) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  printf("OpenMP Mutex Lock Detected!\n");
  CALL_FN_v_W(func, mutex);
  CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
}

//gomp_mutex_unlock
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZumutexZuunlock)(gomp_mutex_t *mutex) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  printf("OpenMP Mutex Unlock Detected!\n");
  CALL_FN_v_W(func, mutex);
  CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
}

//gomp_barrier_wait
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZubarrierZuwait)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Barrier Detected %p\n",bar);
  CALL_FN_v_W(func, bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

// With nested loops, GOMP_atomic is called.
// Inside, gomp_mutex_lock is called from $LIBGOMP_LIB/config/linux/mutex.h.
// However, gomp_mutex_lock is not found in the libgomp shared object file.
// Thus, we wrap the atomic start function we can see, which has no parameters.
// This function passes a statically initilialized gomp_mutex_t object.
// We do the same here in the function wrapping for the addresses in our traces.
//
static gomp_mutex_t atomic_lock;

//GOMP_atomic_start
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZuatomicZustart)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,&atomic_lock,0);
  printf("OpenMP Atomic Start Detected: %p!\n",&atomic_lock);
  CALL_FN_v_v(func);
  CALLGRIND_SIGIL_PTHREAD(2,1,&atomic_lock,0);
}

//GOMP_atomic_end
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZuatomicZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(3,0,&atomic_lock,0);
  printf("OpenMP Atomic End Detected %p!\n",&atomic_lock);
  CALL_FN_v_v(func);
  CALLGRIND_SIGIL_PTHREAD(3,1,&atomic_lock,0);
}

static gomp_mutex_t default_lock;

//GOMP_critical_start
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZucriticalZustart)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,&default_lock,0);
  printf("OpenMP Critical Start Detected: %p!\n",&default_lock);
  CALL_FN_v_v(func);
  CALLGRIND_SIGIL_PTHREAD(2,1,&default_lock,0);
}

//GOMP_critical_end
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZucriticalZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(3,0,&default_lock,0);
  printf("OpenMP Critical End Detected: %p!\n",&default_lock);
  CALL_FN_v_v(func);
  CALLGRIND_SIGIL_PTHREAD(3,1,&default_lock,0);
}


gomp_mutex_t *plock;

//GOMP_critical_name_start
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZucriticalZunameZustart)(void **pptr) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,plock,0);
  printf("OpenMP Critical Name Start Detected: %p!\n",plock);
  CALL_FN_v_W(func,plock);
  CALLGRIND_SIGIL_PTHREAD(2,1,plock,0);
}

//GOMP_critical_name_end
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,GOMPZucriticalZunameZuend)(void **pptr) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(3,0,plock,0);
  printf("OpenMP Critical Name End Detected: %p!\n",plock);
  CALL_FN_v_W(func,plock);
  CALLGRIND_SIGIL_PTHREAD(3,1,plock,0);
}

//omp_set_lock
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,ompZusetZulock)(omp_lock_t *lock) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,lock,0);
  printf("OpenMP Set Lock Detected: %p!\n",lock);
  CALL_FN_v_W(func,lock);
  CALLGRIND_SIGIL_PTHREAD(2,1,lock,0);
}

//omp_unset_lock
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,ompZuunsetZulock)(omp_lock_t *lock) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(3,0,lock,0);
  printf("OpenMP Unset Lock Detected %p!\n",lock);
  CALL_FN_v_W(func,lock);
  CALLGRIND_SIGIL_PTHREAD(3,1,lock,0);
}

//Testing Thread Team Start
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZuteamZustart)(void (*fn) (void *), void *data, unsigned nthreads, unsigned flags, struct gomp_team *team) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Team Start Detected!\n");
  CALL_FN_v_5W(func,fn,data,nthreads,flags,team);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//Testing Thread Team End
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZuteamZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Team End Detected!\n");
  CALL_FN_v_v(func);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//Testing Thread Start
void * I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZuthreadZustart)(void *xdata) {
  void *ret;
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Thread Start Detected!\n");
  CALL_FN_W_W(ret,func,xdata);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
  return ret; 
}

//Testing Free Thread: gomp_free_thread
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZufreeZuthread)(void *arg __attribute__((unused))) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Free Thread Detected!\n");
  CALL_FN_v_W(func, arg );
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//gomp_team_barrier_wait - NOT FOUND
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZuteamZubarrierZuwait)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Team Barrier Wait Detected!\n");
  CALL_FN_v_W(func,bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

//gomp_barrier_destroy
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZubarrierZudestroy)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Barrier Destroy Detected!\n");
  CALL_FN_v_W(func,bar);
  //CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

//gomp_team_barrier_wait_final
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZuteamZubarrierZuwaitZufinal)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Team Barrier Wait Final Detected!\n");
  CALL_FN_v_W(func,bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

//gomp_barrier_wait_end
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,gompZubarrierZuwaitZuend)(gomp_barrier_t *bar, gomp_barrier_state_t state) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Barrier Wait End Detected!\n");
  CALL_FN_v_WW(func,bar,state);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//free_team
void I_WRAP_SONAME_FNNAME_ZZ(libgompZdsoZd1,freeZuteam)(struct gomp_team *team) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Free Team Detected!\n");
  CALL_FN_v_W(func,team);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

// Static wrapping of OpenMP functions
//

//GOMP_parallel
// Loop kick-off calls are detected, but pthread creates are used to
// initiate threads. OMP Barriers are used to "end" loops.

void I_WRAP_SONAME_FNNAME_ZZ(NONE,GOMPZuparallel)(void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Parallel Call Detected!\n");
  CALL_FN_v_WWWW(func, fn, data, num_threads, flags);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//GOMP_parallel_start
void I_WRAP_SONAME_FNNAME_ZZ(NONE,GOMPZuparallelZustart)(void (*fn) (void *), void *data, unsigned num_threads) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Parallel Region Start Detected!\n");
  CALL_FN_v_WWW(func, fn, data, num_threads);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//GOMP_parallel_end
void I_WRAP_SONAME_FNNAME_ZZ(NONE,GOMPZuparallelZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Parallel Region End Detected!\n");
  CALL_FN_v_v(func);
  //printf("Leaving pthread_create!\n");
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//gomp_mutex_lock
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZumutexZulock)(gomp_mutex_t *mutex) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  printf("OpenMP Mutex Lock Detected!\n");
  CALL_FN_v_W(func, mutex);
  //CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
}

//gomp_mutex_unlock
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZumutexZuunlock)(gomp_mutex_t *mutex) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  printf("OpenMP Mutex Unlock Detected!\n");
  CALL_FN_v_W(func, mutex);
  CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
}

//OpenMP's pthread mutex lock call - mutex lock with return value
int I_WRAP_SONAME_FNNAME_ZZ(libpthreadZdsoZd0,pthreadZumutexZulock)(pthread_mutex_t *mutex){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0);
  printf("Detected OpenMP/pthread_mutex_lock!\n");
  CALL_FN_W_W(ret, fn, mutex);
  CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0);
  return ret;
}

//gomp_barrier_wait
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZubarrierZuwait)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Barrier Detected %p\n",bar);
  CALL_FN_v_W(func, bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

// With nested loops, GOMP_atomic is called.
// Inside, gomp_mutex_lock is called from $LIBGOMP_LIB/config/linux/mutex.h.
// However, gomp_mutex_lock is not found in the libgomp shared object file.
// Thus, we wrap the atomic start function we can see, which has no parameters.
// This function passes a statically initilialized gomp_mutex_t object.
// We do the same here in the function wrapping for the addresses in our traces.
//

//GOMP_atomic_start
void I_WRAP_SONAME_FNNAME_ZZ(NONE,GOMPZuatomicZustart)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(2,0,&atomic_lock,0);
  printf("OpenMP Atomic Start Detected: %p!\n",&atomic_lock);
  CALL_FN_v_v(func);
  CALLGRIND_SIGIL_PTHREAD(2,1,&atomic_lock,0);
}

//GOMP_atomic_end
void I_WRAP_SONAME_FNNAME_ZZ(NONE,GOMPZuatomicZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(3,0,&atomic_lock,0);
  printf("OpenMP Atomic End Detected %p!\n",&atomic_lock);
  CALL_FN_v_v(func);
  CALLGRIND_SIGIL_PTHREAD(3,1,&atomic_lock,0);
}

//Testing Thread Team Start
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZuteamZustart)(void (*fn) (void *), void *data, unsigned nthreads, unsigned flags, struct gomp_team *team) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Team Start Detected!\n");
  CALL_FN_v_5W(func,fn,data,nthreads,flags,team);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//Testing Thread Team End
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZuteamZuend)() {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Team End Detected!\n");
  CALL_FN_v_v(func);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//Testing Thread Start
void * I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZuthreadZustart)(void *xdata) {
  void *ret;
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Thread Start Detected!\n");
  CALL_FN_W_W(ret,func,xdata);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
  return ret; 
}

//Testing Free Thread: gomp_free_thread
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZufreeZuthread)(void *arg __attribute__((unused))) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Free Thread Detected!\n");
  CALL_FN_v_W(func, arg );
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//gomp_team_barrier_wait - NOT FOUND
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZuteamZubarrierZuwait)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Team Barrier Wait Detected!\n");
  CALL_FN_v_W(func,bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

//gomp_barrier_destroy
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZubarrierZudestroy)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Barrier Destroy Detected!\n");
  CALL_FN_v_W(func,bar);
  //CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

//gomp_team_barrier_wait_final
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZuteamZubarrierZuwaitZufinal)(gomp_barrier_t *bar) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  printf("OpenMP Team Barrier Wait Final Detected!\n");
  CALL_FN_v_W(func,bar);
  CALLGRIND_SIGIL_PTHREAD(4,1,bar,0);
}

//gomp_barrier_wait_end
void I_WRAP_SONAME_FNNAME_ZZ(NONE,gompZubarrierZuwaitZuend)(gomp_barrier_t *bar, gomp_barrier_state_t state) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Barrier Wait End Detected!\n");
  CALL_FN_v_WW(func,bar,state);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}

//free_team
void I_WRAP_SONAME_FNNAME_ZZ(NONE,freeZuteam)(struct gomp_team *team) {
  OrigFn func;
  VALGRIND_GET_ORIG_FN(func);
  //CALLGRIND_SIGIL_PTHREAD(0,0,*thread,0);
  printf("OpenMP Free Team Detected!\n");
  CALL_FN_v_W(func,team);
  //CALLGRIND_SIGIL_PTHREAD(0,1,*thread,0);
}
