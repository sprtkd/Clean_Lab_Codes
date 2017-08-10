#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
       do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
       
       

static void
display_pthread_attr(pthread_attr_t *attr)
{
   int s, i;
   size_t v;
   void *stkaddr;
   struct sched_param sp;
   printf("Thread attributes:\n");

   s = pthread_attr_getdetachstate(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getdetachstate");
   printf("Detach state        = %s\n",
           (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
           (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
           "???");

   s = pthread_attr_getscope(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getscope");
   printf("Scope               = %s\n",
           (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
           (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
           "???");

   s = pthread_attr_getinheritsched(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getinheritsched");
   printf("Inherit scheduler   = %s\n",
           (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
           (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
           "???");

   s = pthread_attr_getschedpolicy(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getschedpolicy");
   printf("Scheduling policy   = %s\n",
           (i == SCHED_OTHER) ? "SCHED_OTHER" :
           (i == SCHED_FIFO)  ? "SCHED_FIFO" :
           (i == SCHED_RR)    ? "SCHED_RR" :
           "???");

   s = pthread_attr_getschedparam(attr, &sp);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getschedparam");
   printf("Scheduling priority = %d\n", sp.sched_priority);

   s = pthread_attr_getguardsize(attr, &v);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getguardsize");
   printf("Guard size          = %d bytes\n", v);

   s = pthread_attr_getstack(attr, &stkaddr, &v);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getstack");
   printf("Stack address       = %p\n", stkaddr);
   printf("Stack size          = 0x%zx bytes\n", v);
}

void *threadService(void *arg)
{
    pthread_attr_t gattr;
    
    pthread_getattr_np(pthread_self(), &gattr);
    display_pthread_attr(&gattr);
    return NULL;
}

void main()
{
    pthread_t tid;
    
    pthread_create(&tid, NULL, &threadService, NULL);
    pthread_join(tid, NULL);//joining
    
}

