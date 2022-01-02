//for reference - taken from StackOverflow.-vasant

#include<iostream>
#include<pthread.h>
#include<conio.h>

class Semaphore {
private:
  bool            signaled;   // <- changed
  pthread_mutex_t m;
  pthread_cond_t  c;

  void Lock() { pthread_mutex_lock(&m); }          // <- helper inlines added
  void Unlock() { pthread_mutex_unlock(&m); }
public:

  /* -- CONSTRUCTOR/DESTRUCTOR */

  Semaphore(bool);

  //~Semaphore();

  /* -- SEMAPHORE OPERATIONS */

  void P();   // changed to void: you don't return anything
  void V();
};


// consider using C++ constructor initializer syntax.

Semaphore::Semaphore(bool s){        // don't use leading underscores on identifiers
    signaled = s;
    c = PTHREAD_COND_INITIALIZER;    // Not sure you can use the initializers this way!
    m = PTHREAD_MUTEX_INITIALIZER;   // they are for static objects.

    // pthread_mutex_init(&m); // look, this is shorter!
}

void Semaphore::P(){
    Lock();              // added
    while (!signaled){   // this must be a loop, not if!
        pthread_cond_wait(&c, &m);
    }
    signaled = false;
    Unlock();
}

void Semaphore::V(){
    bool previously_signaled;
    Lock();
    previusly_signaled = signaled; 
    signaled = true;
    Unlock();  // always release the mutex before signaling
    if (!previously_signaled)
      pthread_cond_signal(&c); // this may be an expensive kernel op, so don't hold mutex
}

int main()
{

	return 0;
}

