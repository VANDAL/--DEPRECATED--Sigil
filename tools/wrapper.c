#include <stdio.h>
#include <pthread.h>
#include "pub_tool_redir.h"
//#include "valgrind.h"
#include "callgrind.h"

//Use CALLGRIND_SIGIL_PTHREAD to do a Sigil callback and pass in upto 5 arguments. Argument 1 will be which pthread call it represents. value of 0,1,2,3 should mean create,join,mutex_lock,mutex_unlock. More special cases can be added as the implementation becomes more complex. Argument 2 will be to represent whether its about to start or it has just finished the intercepted function. 0,1 represents the corresponding case. Argument 3 represents the mutex address if Argument 1 is lock or unlock.

/* int I_WRAP_SONAME_FNNAME_ZZ(VG_Z_LIBPTHREAD_SONAME,pthreadZucreateZAZa)(pthread_t *thread, const pthread_attr_t *attr, void *(*start) (void *), void *arg) { */
/*   int ret; */
/*   OrigFn fn; */
/*   VALGRIND_GET_ORIG_FN(fn); */
/*   CALLGRIND_SIGIL_PTHREAD(0,0,0,0); */
/*   //printf("Entered pthread_create!\n"); */
/*   CALL_FN_W_WWWW(ret, fn, thread, attr, start, arg); */
/*   //printf("Leaving pthread_create!\n"); */
/*   CALLGRIND_SIGIL_PTHREAD(0,1,0,0); */
/*   return ret; */
/* } */

/* int I_WRAP_SONAME_FNNAME_ZZ(VG_Z_LIBPTHREAD_SONAME,pthreadZujoin)(pthread_t thread, void** value_pointer) { */
/*   int ret; */
/*   OrigFn fn; */
/*   VALGRIND_GET_ORIG_FN(fn); */
/*   CALLGRIND_SIGIL_PTHREAD(1,0,0,0); */
/*   //printf("Entered pthread_join!\n"); */
/*   CALL_FN_W_WW(ret, fn, thread, value_pointer); */
/*   //printf("Leaving pthread_join!\n"); */
/*   CALLGRIND_SIGIL_PTHREAD(1,1,0,0); */
/*   return ret; */
/* } */

/* /\* int I_WRAP_SONAME_FNNAME_ZZ(VG_Z_LIBPTHREAD_SONAME,pthreadZumutexZuinit)(pthread_mutex_t *mutex,pthread_mutexattr_t* attr){ *\/ */
/* /\*   int ret; *\/ */
/* /\*   OrigFn fn; *\/ */
/* /\*   VALGRIND_GET_ORIG_FN(fn); *\/ */
/* /\*   printf("Entered pthread_mutex_init!\n"); *\/ */
/* /\*   CALL_FN_W_WW(ret, fn, mutex,attr); *\/ */
/* /\*   printf("Leaving pthread_mutex_init!\n"); *\/ */
/* /\*   return ret; *\/ */
/* /\* } *\/ */

/* int I_WRAP_SONAME_FNNAME_ZZ(VG_Z_LIBPTHREAD_SONAME,pthreadZumutexZulock)(pthread_mutex_t *mutex){ */
/*   int ret; */
/*   OrigFn fn; */
/*   VALGRIND_GET_ORIG_FN(fn); */
/*   CALLGRIND_SIGIL_PTHREAD(2,0,mutex,0); */
/*   printf("Entered pthread_mutex_lock %lu!\n",mutex); */
/*   CALL_FN_W_W(ret, fn, mutex); */
/*   printf("Leaving pthread_mutex_lock %lu!\n",mutex); */
/*   CALLGRIND_SIGIL_PTHREAD(2,1,mutex,0); */
/*   return ret; */
/* } */

/* int I_WRAP_SONAME_FNNAME_ZZ(VG_Z_LIBPTHREAD_SONAME,pthreadZumutexZuunlock)(pthread_mutex_t *mutex){ */
/*   int ret; */
/*   OrigFn fn; */
/*   VALGRIND_GET_ORIG_FN(fn); */
/*   CALLGRIND_SIGIL_PTHREAD(3,0,mutex,0); */
/*   printf("Entered pthread_mutex_unlock %lu!\n",mutex); */
/*   CALL_FN_W_W(ret, fn, mutex); */
/*   printf("Leaving pthread_mutex_unlock %lu!\n",mutex); */
/*   CALLGRIND_SIGIL_PTHREAD(3,1,mutex,0); */
/*   return ret; */
/* } */

//WRAPPER FOR STATIC LIBRARIES

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

//YET TO BE IMPLEMENTED IN MAIN.c

int I_WRAP_SONAME_FNNAME_ZZ(NONE,pthreadZubarrierZuwaitZa)(pthread_barrier_t* bar){
  int ret;
  OrigFn fn;
  VALGRIND_GET_ORIG_FN(fn);
  CALLGRIND_SIGIL_PTHREAD(4,0,bar,0);
  //printf("Entered pthread_mutex_barrier_wait %lu!\n",bar);
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

//OUR pthread.h DOES NOT SUPPORT sem_wait and sem_post. Will need a workaround for this
/* int I_WRAP_SONAME_FNNAME_ZZ(NONE,semZuwaitZa)(sem_t* sem){ */
/*   int ret; */
/*   OrigFn fn; */
/*   VALGRIND_GET_ORIG_FN(fn); */
/*   CALLGRIND_SIGIL_PTHREAD(9,0,0,sem); */
/*   //printf("Entered pthread_mutex_cond_wait %lu %lu!\n",mutex,cond); */
/*   CALL_FN_W_W(ret, fn, sem); */
/*   //printf("Leaving pthread_mutex_cond_wait %lu %lu!\n",mutex,cond); */
/*   CALLGRIND_SIGIL_PTHREAD(9,1,0,sem); */
/*   return ret; */
/* } */

/* int I_WRAP_SONAME_FNNAME_ZZ(NONE,semZupostZa)(sem_t* sem){ */
/*   int ret; */
/*   OrigFn fn; */
/*   VALGRIND_GET_ORIG_FN(fn); */
/*   CALLGRIND_SIGIL_PTHREAD(10,0,0,sem); */
/*   //printf("Entered pthread_mutex_cond_wait %lu %lu!\n",mutex,cond); */
/*   CALL_FN_W_W(ret, fn, sem); */
/*   //printf("Leaving pthread_mutex_cond_wait %lu %lu!\n",mutex,cond); */
/*   CALLGRIND_SIGIL_PTHREAD(10,1,0,sem); */
/*   return ret; */
/* } */
