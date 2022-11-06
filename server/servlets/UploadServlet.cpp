//
// Created by Admin on 2022-10-31.
//

#include "UploadServlet.hpp"

#include <iostream>

using namespace std;

void UploadServlet::doGet(HttpServletRequest &req, HttpServletResponse &res)
{
    string *writer = res.getWriter();
    res.setContentType("text/html");

    writer->append("<!DOCTYPE html>\r\n");
    writer->append("<html>\r\n");
    writer->append("    <head>\r\n");
    writer->append("        <title>File Upload Form</title>\r\n");
    writer->append("    </head>\r\n");
    writer->append("    <body>\r\n");
    writer->append("<h1>Upload file</h1>\r\n");
    writer->append("<form method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n");
    writer->append("<input type=\"file\" name=\"fileName\"/><br/><br/>\r\n");
    writer->append("Caption: <input type=\"text\" name=\"caption\"<br/><br/>\r\n");
    writer->append("<br />\r\n");
    writer->append("Date: <input type=\"date\" name=\"date\"<br/><br/>\r\n");
    writer->append("<br />\r\n");
    writer->append("<input type=\"submit\" value=\"Submit\"/>\r\n");
    writer->append("</form>\r\n");
    writer->append("</body>\r\n");
    writer->append("</html>\r\n");

    res.setStatus(200);
    res.setContentLength(writer->size());
}

void UploadServlet::doPost(HttpServletRequest &, HttpServletResponse &)
{
}