//
// Created by Admin on 2022-10-31.
//
#pragma once
#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"

#ifndef C_WRAPPERS_HTTPSERVLET_HPP
#define C_WRAPPERS_HTTPSERVLET_HPP

class HttpServlet
{
public:
    virtual void doGet(HttpServletRequest &, HttpServletResponse &) = 0;
    virtual void doPost(HttpServletRequest &, HttpServletResponse &) = 0;
};

#endif // C_WRAPPERS_HTTPSERVLET_HPP
