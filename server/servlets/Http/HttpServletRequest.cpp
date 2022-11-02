//
// Created by Admin on 2022-10-31.
//

#include "HttpServletRequest.hpp"

/**
 * Split raw request into 3 parts.
 * head, headers, body.
 *
 * Then call helper methods to parse each.
 */
void HttpServletRequest::parseRequest() {
    int pos = 0;

    // Find and set end of the head
    while (*(raw + pos) == '\r' && *(raw + (pos + 1))  == '\n')
        pos++;

    this->head(pos);
    pos++;

    // Find and set end of headers
    while (
            *(raw + pos) == '\r' &&
            *(raw + (pos + 1)) == '\n' &&
            *(raw + (pos + 2)) == '\r' &&
            *(raw + (pos + 3)) == '\n'
            )
        pos++;

    this->head(pos);
    pos++;


    parseHead();
    parseHeaders();
    parseBody();
}

void HttpServletRequest::parseHead() {
    std::cout << head << std::endl;
};

void HttpServletRequest::parseHeaders() {
    std::cout << headers << std::endl;

};

void HttpServletRequest::parseBody() {
    std::cout << body << std::endl;
};
