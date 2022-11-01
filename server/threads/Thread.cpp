#include "Thread.h"
#include "Router.hpp"
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

void* startMethodInThread(void *arg){
    cout << "cum"<< endl;
	if (arg == NULL) {
        cout <<"no args" << endl;
        return 0;
    }
	Router *thread = (Router*)arg;
	thread->run();
	return NULL;
}

Thread::Thread(Thread *childThread) {
	this->state = malloc(sizeof(pthread_t));
	this->childThread = childThread;
}

void Thread::start() {
        pthread_t tid;
	pthread_create(&tid, NULL, startMethodInThread, (void *) this);
	memcpy(this->state, (const void *)&tid, sizeof(pthread_t));
}

Thread::~Thread() {
	free(this->state);
}