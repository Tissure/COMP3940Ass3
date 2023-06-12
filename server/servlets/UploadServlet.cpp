//
// Created by Admin on 2022-10-31.
//

#include "UploadServlet.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <filesystem>

using namespace std;

void UploadServlet::doGet(HttpServletRequest &req, HttpServletResponse &res)
{
    cout << "in doget" << endl;
    auto *writer = res.getWriter();
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

void UploadServlet::doPost(HttpServletRequest &req, HttpServletResponse &res)
{
//    TODO

    cout << "in doPost" << endl;

//    string caption = req.getParameter("caption");
//    string date = req.getParameter("date");
//    string fileName = req.getParameter("fileName");
//
//    cout << ("date: " + date);
//    cout << ("caption: " + caption);
//    cout << ("fileName: " + fileName);

    // write the image to the file
//    auto imageBytes = req.getParameter(fileName);
//    ofstream fos;
//    fos.open(("./images/" + fileName));
//    fos << imageBytes;
//
//    // get the file names in the image file as a json if invoked by CLI or html list if browser
//    string listing = NULL;
//    if (req.getHeader("User-Agent") == " CLI") {
//        res.setContentType("text/json");
//        listing = getSortedListingJSON("./images/");
//    } else {
//        res.setContentType("text/html");
//        listing = getSortedListingHTML("./images/");
//    }
//
//    // write the file names to the client
//    auto *writer = res.getWriter();
//    writer->append(listing);
    res.setStatus(200);
//    res.sendRedirect("/upload");
}

list<string> UploadServlet::getSortedFiles(string directoryPath) {
    ifstream directory;
    directory.open(directoryPath);
    list<string>chld;
    for (auto const& dir_entry : std::filesystem::directory_iterator{ directoryPath }){
        chld.push_back(dir_entry.path().filename().string());
    }
    //list<string> sortedChld = Arrays.asList(chld).stream().sorted((a, b) -> a.toLowerCase().compareTo(b.toLowerCase())).collect(Collectors.toList());
    return chld;
}

string UploadServlet::getSortedListingJSON(string directoryPath) {
    list<string> sortedChld = getSortedFiles(directoryPath);
    string jsonString = "{";
    list<string>::iterator it;
    for (it = sortedChld.begin(); it != sortedChld.end(); ++it){
        jsonString += *it ;
        if (it != sortedChld.end()) {
            jsonString += ",";
        }
    }
    return jsonString;
}

string UploadServlet::getSortedListingHTML(string directoryPath) {
    list<string> sortedChld = getSortedFiles(directoryPath);
    stringstream htmlBuilder;

    htmlBuilder << ("<!DOCTYPE html>\r\n");
    htmlBuilder << ("<html>\r\n");
    htmlBuilder << ("<head>\r\n");
    htmlBuilder << ("<title>File listing</title>\r\n");
    htmlBuilder << ("</head>\r\n");
    htmlBuilder << ("<body>\r\n");

    htmlBuilder << ("<ul>\r\n");
    for (string s : sortedChld) {
        htmlBuilder << ("<li>") << (s) << ("</li>") << ("\r\n");
    }

    htmlBuilder << ("</ul>\r\n");
    htmlBuilder << ("</body>\r\n");
    htmlBuilder << ("</html>\r\n");

    return htmlBuilder.str();
}


