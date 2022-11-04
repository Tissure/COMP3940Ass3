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
    parseHeaders();
}

void HttpServletRequest::parseHead()
{

    string head = getNext("\n\r");

    // cout << "Head : " << head << endl;

    int type = 0;
    string value;
    for (int i = 0; i < head.size(); i++)
    {
        value += head[i];
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

void HttpServletRequest::parseHeaders()
{
    string h = getNext("\n\r\n\r");

    int n = h.length();

    // declaring character array
    char headers[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(headers, h.c_str());

    int cursor = 0;
    string key = getNext(headers + cursor, n, ":", &cursor);

    // skip over :
    cursor++

        string value = getNext(headers + cursor, n, "\n\r", &cursor);

    cout << "Key: " << key << " Value: " << value << endl;
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
    size_t patternLength = pattern.size();

    string result;
    char *character;

    // Read socket into string.
    while (*(character = socket->getNext()) != EOF && !isMatch(result, pattern))
    {
        result += *character;
        // cout << result << endl;
    }

    return result;
}

string HttpServletRequest::getNext(char *str, int size, string pattern, int *cursor)
{
    string result;
    if (size < pattern.size())
    {
        return str;
    }

    for (int i = 0; i < size; i++)
    {
        result += *str;
        if (isMatch(result, pattern))
        {
            return result;
        }
        *(str++);
        (*cursor)++;
    }
    result += result;
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
