#include "sockets/Socket.h"
#include "sockets/ServerSocket.h"
#include "threads/Router.hpp"
#include <stddef.h>
#include <iostream>

using namespace std;
int main()
{
  ServerSocket *ss = new ServerSocket(8888);
  if (ss != NULL)
  {
    while (1)
    {
      cout << "waiting" << endl;
      Socket *cs = ss->Accept();
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

/**
 * The tail of moving a socket from router to httpServletRequest and parsing
 * the request. So far i have made progress.
 *
 * im  listening to this if you want to join in.
 * https://youtu.be/i4gebic_Wnc
 *
 *
 * so was able to parse the head. I was tired and i gave up.
 *
 * So first things first, lets move that socket over!!
 *
 * Well this fucking blows, ive spent an hour trying to compile
 * this thing??? Like WHAT!!! :()();
 *
 * I have given in and decided to reach out Kyle.
 * Is he god, nobody knows.
 *
 * I am stupid!! i did not define a constructor. Learning moment!
 * When compiler screams this is undefined and its your own
 * class, you might not have defined : (__)
 *
 * But anyways, it is time to parse the socket.
 *
 * I need two functions getNext(string pattern) and isMatch(string str, string pattern)
 *
 * Head is parsed!!! blap blap ma ma
 *
 * Next is the headers. Dude thos getNext anf isMatch functions make my life so easy!!
 *
 *
 */