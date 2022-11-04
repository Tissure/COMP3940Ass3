//
// Created by Admin on 2022-10-31.
//
#pragma once
#include "HttpServlet.hpp"

#ifndef C_WRAPPERS_UPLOADSERVLET_HPP
#define C_WRAPPERS_UPLOADSERVLET_HPP

class UploadServlet : public HttpServlet
{
public:
    void doGet(HttpServletRequest, HttpServletResponse) override;
    void doPost(HttpServletRequest, HttpServletResponse) override;
};

#endif // C_WRAPPERS_UPLOADSERVLET_HPP
