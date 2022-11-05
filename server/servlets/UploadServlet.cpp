//
// Created by Admin on 2022-10-31.
//
#include <list>
#include <sstream>
#include "UploadServlet.hpp"


void UploadServlet::doGet(HttpServletRequest request, HttpServletResponse response) {
    //TODO
    auto writer = response.getOutputStream();

    response.setContentType("text/html");

    writer << ("<!DOCTYPE html>\r\n");
    writer << ("<html>\r\n");
    writer << ("    <head>\r\n");
    writer << ("        <title>File Upload Form</title>\r\n");
    writer << ("    </head>\r\n");
    writer << ("    <body>\r\n");
    writer << ("<h1>Upload file</h1>\r\n");
    writer << ("<form method=\"POST\" action=\"/\" enctype=\"multipart/form-data\">\r\n");
    writer << ("<input type=\"file\" name=\"fileName\"/><br/><br/>\r\n");
    writer << ("Caption: <input type=\"text\" name=\"caption\"<br/><br/>\r\n");
    writer << ("<br />\r\n");
    writer << ("Date: <input type=\"date\" name=\"date\"<br/><br/>\r\n");
    writer << ("<br />\r\n");
    writer << ("<input type=\"submit\" value=\"Submit\"/>\r\n");
    writer << ("</form>\r\n");
    writer << ("</body>\r\n");
    writer << ("</html>\r\n");

    response.setStatus("200");
    writer.close();

}

void UploadServlet::doPost(HttpServletRequest request, HttpServletResponse response) {
    //TODO

    string caption = request.getParameter("caption");
    string date = request.getParameter("date");
    string fileName = request.getParameter("fileName");

    cout << ("date: " + date);
    cout << ("caption: " + caption);
    cout << ("fileName: " + fileName);

    // write the image to the file
    byte[] imageBytes = request.getImageBytes(fileName);
    ofstream fos;
    fos.open(("./images/" + fileName));
    fos << imageBytes;

    // get the file names in the image file as a json if invoked by CLI or html list if browser
    string listing = null;
    if (request.getHeader("User-Agent") == " CLI") {
        response.setContentType("text/json");
        listing = getSortedListingJSON("./images/");
    } else {
        response.setContentType("text/html");
        listing = getSortedListingHTML("./images/");
    }

    // write the file names to the client
    auto writer = response.getWriter();
    writer.write(listing);
    writer.close();
    response.setStatus("200");
    response.sendRedirect("/upload");
}

string UploadServlet::getSortedListingJSON(string directoryPath) {
    list<string> sortedChld = getSortedFiles(directoryPath);
    string jsonString = "{";
    for (int i = 0; i < sortedChld.size(); i++) {
        jsonString += i + ": " + sortedChld.get(i);
        if (i != sortedChld.size() - 1) {
            jsonString += ",";
        }
    }
    jsonString += "}";
    return jsonString;
}

string UploadServlet::getSortedListingHTML(string directoryPath) {
    List<String> sortedChld = getSortedFiles(directoryPath);
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

    return htmlBuilder.toString();
}

list<string> UploadServlet::getSortedFiles(string directoryPath) {
    ifstream directory;
    directory.open(directoryPath);
    string[] chld = directory.list();
    list<string> sortedChld = Arrays.asList(chld).stream().sorted((a, b) -> a.toLowerCase().compareTo(b.toLowerCase())).collect(Collectors.toList());
    return sortedChld;
}

}