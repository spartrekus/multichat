#include "mythread.h"

using namespace std;

//Need to actually "allocate" static member
pthread_mutex_t MyThread::mutex;

MyThread::MyThread() {
}

void * MyThread::printThread(void *args) {
  while(1) {
  	cout << "Inside function: ";
        if(args) cout << (char *) args;
        cout << endl;
        sleep(1);
  }
  return NULL;
}

int MyThread::Create(void *Callback, void *args) {
  int tret=0;
 
  //Supercreepy typecast
  tret = pthread_create(&this->tid, NULL, (void *(*)(void *))Callback, args);

  if(tret) { 
    cerr << "Error while creating threads." << endl;
    return tret;
  }
  else {
    cout << "Thread succesfuly created." << endl;

    //Wait until threads return to end main process
    //Fix - This should be called after all threads are created
    //pthread_join(this->tid, NULL);

    return 0;
  }
}

int MyThread::Join() {
  pthread_join(this->tid, NULL);
  return 0;
}

int MyThread::InitMutex() {
  
  if(pthread_mutex_init(&MyThread::mutex, NULL) < 0) {
    cerr << "Error while initializing mutex" << endl;
    return -1;
  }
  else {
    cout << "Mutex initialized." << endl;
    return 0;
  }
}

/*
    LockMutex():
		Blocks until mutex becomes available
*/
int MyThread::LockMutex(const char *identifier) {
  cout << identifier << " is trying to acquire the lock..." << endl;
  if(pthread_mutex_lock(&MyThread::mutex) == 0) {
    cout << identifier << " acquired the lock!" << endl;
    return 0;
  }
  else {
   cerr << "Error while " << identifier << " was trying to acquire the lock" << endl;
   return -1;
  }
}

int MyThread::UnlockMutex(const char *identifier) {
  cout << identifier << " is trying to release the lock..." << endl;
  if(pthread_mutex_unlock(&MyThread::mutex) == 0) {
    cout << identifier << " released the lock!" << endl;
    return 0;
  }
  else {
   cerr << "Error while " << identifier << " was trying to release the lock" << endl;
   return -1;
  }
}
