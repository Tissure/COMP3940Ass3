#include "sockets/Socket.h"
#include "sockets/ServerSocket.h"
#include "threads/Router.hpp"
#include <stddef.h>
#include <iostream>

using namespace std;
int main() {
  ServerSocket *ss = new ServerSocket(8888);
	if (ss != NULL) {
        while(1){
            cout<<"waiting" << endl;
            Socket * cs = ss->Accept();
            Router *thread = new Router(cs);
            thread->start();
        }

//        Router thread{cs};
//        thread.start();
//		char *req = cs->getRequest();
//		char *res = new char(50);
//		cs->sendResponse(res);
	}
    return 0;
}
