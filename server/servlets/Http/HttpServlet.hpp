//
// Created by Admin on 2022-10-31.
//
#pragma once
#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"


class HttpServlet {
public:
    virtual void doGet(HttpServletRequest, HttpServletResponse) = 0;
    virtual void doPost(HttpServletRequest, HttpServletResponse) = 0;
};
