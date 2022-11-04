//
// Created by Admin on 2022-10-31.
//

#include "HttpServletRequest.hpp"

/**
 * Split raw request into 3 parts.
 * head, headers, body.
 *
 * Then call helper methods to parse each.
 */
void HttpServletRequest::parseRequest() {
    parseHead();
    parseHeaders();
    cout << *this << endl;
}

void HttpServletRequest::parseHead() {
    string head = getNext(HEAD_BOUNDRY);

    int type = 0;
    string value;
    for (int i = 0; i < head.size(); i++) {
        value += head[i];
        if (head[i] == ' ') {
            switch (type) {
                case 0:
                    this->method = this->stringToMethod(value);
                    break;
                case 1:
                    this->url = value;
                    break;
                default:
                    break;
            }
            value = "";
            type++;
        }
    }

    this->version = value;
};

void HttpServletRequest::parseHeaders() {
    string h = getNext(HEADER_BOUNDRY);

    int n = h.length();

    // declaring character array
    char headers[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(headers, h.c_str());

    int cursor = 0;

    while (cursor < n) {
        string key = getNext(headers + cursor, n, ":", &cursor);

        // skip over :
        cursor++;
        string value = getNext(headers + cursor, n, HEAD_BOUNDRY, &cursor);

        if (key == "" || value == "")
            break;

        appendHeader(key, value);
    }
};

void HttpServletRequest::parseBody() {
    // std::cout << body << std::endl;
};

HttpServletRequest::Method HttpServletRequest::stringToMethod(string method) {
    for (auto &c: method)
        c = toupper(c);

    if (method == "POST")
        return Method::POST;

    if (method == "DELETE")
        return Method::DELETE;

    return Method::GET;
}

string HttpServletRequest::getNext(string pattern) {
    size_t patternLength = pattern.size();

    string result;
    char *character;

    // Read socket into string.
    while (*(character = socket->getNext()) != EOF && !isMatch(result + *character, pattern)) {
        result += *character;
    }

    return result;
}

string HttpServletRequest::getNext(char *str, int size, string pattern, int *cursor) {
    string result;
    if (size < pattern.size() || *cursor >= size) {
        return "";
    }

    for (int i = 0; i < size; i++) {
        if (*cursor >= size) {
            return "";
        }

        result += *str;


        (*cursor)++;

        if (isMatch(result, pattern)) {
//            if(result[0] == pattern[0]){
//                //remove pattern from start of string
////                result = result[pattern.size()];
//                result = result.substr(pattern.size(), result.size());
//            } else {
                // Remove pattern from string
                result.resize(result.size() - pattern.size());
                return result;
//            }
        }

        *(str++);
    }
    result += result;
}

bool HttpServletRequest::isMatch(string str, string pattern) {
    if (pattern.size() > str.size())
        return false;

    for (int i = 0; i < pattern.size(); i++) {
        if (str[str.size() - 1 - i] != pattern[pattern.size() - 1 - i])
            return false;
    }

    return true;
}

/**
 * Returns true if key is an edge case.
 */
bool HttpServletRequest::headerEdgeCases(string key, string value) {
    cout << "EDGE CASES: " << key << "--54545|--" << value << endl;
    // Check to see if it form "Content-Type:multipart/form-data"
    if (key == CT && value == CT_MULTI_PART_FORM_DATA) {
        return true;
    }
    return false;
};

/**
 * Appends key, value to headerMap
 */
void HttpServletRequest::appendHeader(string key, string value) {
    cout << "Append Header" << endl;
    // Its lie to call this headerEdgeCases, becuase we
    // are only checking for multipart/form-data
    // &()
    // But i called it headerEdgeCases because its more VERBOSE!
    // :()::<>::{}::~~
    if (headerEdgeCases(key, value)) {
        cout << "IN EDGE CASE HANDLER" << endl;

        int n = value.length();

        // declaring character array
        char valueArray[n + 1];

        // copying the contents of the
        // string to char array
        strcpy(valueArray, value.c_str());

        // cout << "EDGE CASE: " << endl;
        int cursor = 0;
        int size = value.size();

        string tempVal = getNext(valueArray, size, " ", &cursor);

        cout << "KEY: " << key << " VALUE: " << value << endl;

        string tempBoundry = getNext(valueArray, size, HEAD_BOUNDRY, &cursor);

        cout << "BOUNDRY: " << tempBoundry << endl;
    }
    this->headersMap.insert(pair<string, string>(key, value));
};

ostream &operator<<(ostream &os, const HttpServletRequest &request) {

    os << request.method << " " << request.url << " " << request.version << endl;

    for (auto const &x: request.headersMap) {
        os << x.first // string (key)
           << ':'
           << x.second
           << endl; // string's value
    }
    return os;
}