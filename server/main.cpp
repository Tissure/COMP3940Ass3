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
  }
  return 0;
}

/**
 * The tail of moving a socket from router to httpServletRequest and parsing
 * the request. So far i have made progress......
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
 * Next is the headers. Dude this getNext and isMatch functions make my life so easy!!
 * I made another getNext method, this one takes in a cursor and moves it along the string
 * you passed in.
 *
 * Im gonna go smoke a J***T see yeah
 *
 * So yo, i got the header, key value parsing working. Im gonna work on the edge cases,
 * I dont care about anything else except content-type.
 *
 * Wish me luck :<>
 * This is what im watching currently
 * https://www.youtube.com/watch?v=Ze0kq-ROeaU <-- @adrien
 *
 * also this
 * https://www.youtube.com/watch?v=gNUAm1I_bu8 <-- @urinatingtree
 *
 * Im too tired and i cant process the info. Im gonna get some chips
 * and pass the fuck out.
 *
 * Hello everyone, im back at it with clayton.
 *
 * Clayton? would you like to say a couple word?:
 *
 * // This is Clayton
 * bitch @clayonHunter
 * // Clayton has finished streaming
 *
 * Kyle just walked in, I felt tingles all over my skin.
 *
 * // Kyle jumping in
 *  Bout to fix Rav's code
 *
 *  Fixed rav's code :)
 *
 * // Rav jumping back
 * F**k you kyle, i was there beside you. And you don't give
 * me any creadit?
 *
 * Anyways, we are know in 3522 lecture and Jeff is talking about
 * assignment 2. I should probably pay attention, that cost nothing.
 *
 * Anyhow I got the headers parsed fully!!! Eat my....jeff said something important
 * and i didn't write it down.
 *
 * Some thing just happened. I have to eat my shoe. I have got my self into
 * a corner. I have to use an else block!!!! I told all to block the
 * alluring gaze of the else.
 *
 * I'm embarassed and will whip myself 10 times.
 *
 * Peace and love .... peace and love V
 *
 * I finished making a function for the Socket class called dump()
 * dump(std::vector<char> &result). The Scoets contents will be dumped
 * into the passed in vector.
 *
 * So i relized something, when every I parsed anything, some white space
 * was left over. So i made a trim() method. Im too tired now, im going to
 * sleep.
 *
 * This is taking way longer than i thought!
 *
 * I keep having to make more and more methods, fuggg This has taken me
 * way too long :().
 *
 * The power just went out at my house. Good thing i just charged my laptop
 * Currenctly its at 98%
 *
 * So i stopped doing the journal because i was really frustrated. Turns out
 * my getNext function wasn't working properl. It kept taking an extra
 * byte out of the socke, and did not truncate the pattern from the result.
 *
 * Any ways everything is done except piping the file to a file. I have left
 * a section of code for that in HttpServletRequest.cpp line 347. All you need to do
 * is pipe all bytes from the socket into the file until, \r\n is seen.
 * Remove \r\n and append the rest of the data.
 *
 * PUG!!
 *
 * Also my internet is out still, so i need to go to my freinds house tonight and
 * push all the code.
 */
