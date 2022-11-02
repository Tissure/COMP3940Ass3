//
// Created by Admin on 2022-10-31.
//

#include <string>
#include "HttpRequestBuilder.hpp"

using namespace std;

string HttpRequestBuilder::buildMultipartRequest(string filePath, string caption, string date) {
    // build the body before hand so we can get the content length
    string bodyBuilder = buildBody(filePath, caption, date);

    string bodyLength = to_string(bodyBuilder.length());

    string reqBuilder =
            "POST / " + HttpRequestBuilder::VERSION + "\r\n"
            + "User-Agent: " + "CLI" + "\r\n"
            + "Accept: " + "*/*" + "\r\n"
            + "Host: " + HttpRequestBuilder::HOST + "\r\n"
            + "Accept-Encoding: gzip, deflate, br" + "\r\n"
            + "Connection: " + "keep-alive" + "\r\n"
            + "Content-Type: " + "multipart/form-data; boundary=" + HttpRequestBuilder::BOUNDARY + "\r\n"
            + "Content-Length: " + bodyLength + "\r\n"
            + "\r\n"
            + bodyBuilder;
    // request line

    return reqBuilder;
}

string HttpRequestBuilder::buildBody(string filePath, string caption, string date) {
    string body = "--" + HttpRequestBuilder::BOUNDARY + "\r\n";

    // parse the file
    body += buildContentType(filePath);

    // parse the caption
    body = body + "Content-Disposition: form-data; name=\"caption\"" + "\r\n"
            + "\r\n" + caption + "\r\n"
            + "--" + HttpRequestBuilder::BOUNDARY + "\r\n";

    // parse the date
    body = body + "Content-Disposition: form-data; name=\"date\"" + "\r\n"
            + "\r\n" + date + "\r\n"
            + "--" + HttpRequestBuilder::BOUNDARY + "--\r\n";

    return body;
}

string HttpRequestBuilder::buildContentType(string filePath) {
    int index = filePath.find_last_of('.');
    string fileType = filePath.substr(index + 1, filePath.length());
    string contentType = "?";
    if (equal(fileType.begin(), fileType.end(), "png")) {
        contentType = "image/png";
    } else if (equal(fileType.begin(), fileType.end(), "jpg") || equal(fileType.begin(), fileType.end(), "jpeg")) {
        contentType = "image/jpeg";
    } else if (equal(fileType.begin(), fileType.end(), "txt")) {
        contentType = "file/text";
    }

    return "Content-Type: " + contentType + fileType + "\r\n\r\n";
}