//
// Created by Admin on 2022-10-31.
//
#pragma once

#include <list>
#include "HttpServlet.hpp"

#ifndef C_WRAPPERS_UPLOADSERVLET_HPP
#define C_WRAPPERS_UPLOADSERVLET_HPP

class UploadServlet : public HttpServlet
{
public:
    void doGet(HttpServletRequest &req, HttpServletResponse &res) override;
    void doPost(HttpServletRequest &req, HttpServletResponse &res) override;
    list<string> getSortedFiles(string directoryPath);
    string getSortedListingJSON(string directoryPath);
    string getSortedListingHTML(string directoryPath);
};

#endif // C_WRAPPERS_UPLOADSERVLET_HPP
