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
void HttpServletRequest::parseRequest()
{
    parseHead();

    cout << this->getMethod() << " " << this->url << " " << this->version << endl;
}

void HttpServletRequest::parseHead()
{

    string head = getNext("\n\r");

    cout << "Head: " << head << endl;
    int type = 0;
    string value;
    for (int i = 0; i < head.size(); i++)
    {
        value += head[i];
        cout << "Value: " << value << endl;
        if (head[i] == ' ')
        {
            switch (type)
            {
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

void HttpServletRequest::parseHeaders(){

    // while (*(raw + pos) != '\n' || *(raw + pos + 3) != '\r')
    //     pos++;

    // pos = pos + 3;
    // this->headers = pos;

    // std::cout << "HEADERS: " << endl;
    // for (int i = this->head; i < this->headers; i++)
    //     cout << *(raw + i);
};

void HttpServletRequest::parseBody(){
    // std::cout << body << std::endl;
};

HttpServletRequest::Method HttpServletRequest::stringToMethod(string method)
{
    for (auto &c : method)
        c = toupper(c);

    if (method == "POST")
        return Method::POST;

    if (method == "DELETE")
        return Method::DELETE;

    return Method::GET;
}

string HttpServletRequest::getNext(string pattern)
{

    // Set up table.
    size_t patternLength = pattern.size();

    string result;
    char *character;

    // Read socket into string.
    while (*(character = socket->getNext()) != EOF && !isMatch(result, pattern))
    {
        result += *character;
    }

    return result;
}

bool HttpServletRequest::isMatch(string str, string pattern)
{
    if (pattern.size() > str.size())
        return false;

    for (int i = 0; i < pattern.size(); i++)
    {
        if (str[str.size() - 1 - i] != pattern[pattern.size() - 1 - i])
            return false;
    }

    return true;
}
