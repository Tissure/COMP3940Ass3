//
// Created by Admin on 2022-10-31.
//
#pragma once
#ifndef C_WRAPPERS_HTTPSERVLETRESPONSE_HPP
#define C_WRAPPERS_HTTPSERVLETRESPONSE_HPP

#include <ostream>

using namespace std;


class HttpServletResponse {
public:
    HttpServletResponse(){};
    char * getResponse();
};


#endif //C_WRAPPERS_HTTPSERVLETRESPONSE_HPP
