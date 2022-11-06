//
// Created by Admin on 2022-10-31.
//
#pragma once
#include "Http/HttpServlet.hpp"


class UploadServlet : public HttpServlet {
public:
    void doGet(HttpServletRequest&, HttpServletResponse&) override;
    void doPost(HttpServletRequest, HttpServletResponse) override;
};
