//
// Created by Admin on 2022-10-31.
//

#include "HttpResponseParser.hpp"

/**
 * Split raw request into 3 parts.
 * head, headers, body.
 *
 * Then call helper methods to parse each.
 */
void HttpResponseParser::parseResponse()
{
    parseHead();
    parseHeaders();
    parseBody();
//    cout << *this << endl;
}

void HttpResponseParser::parseHead()
{
    string head = getNext(LINE);
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

void HttpResponseParser::parseHeaders()
{
    string h = getNext(BOUNDRY);

    int n = h.length();

    // declaring character array
    char headers[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(headers, h.c_str());

    int cursor = 0;

    while (cursor < n)
    {
        string key = getNext(headers + cursor, n, ":", &cursor);
        string value = getNext(headers + cursor, n, LINE, &cursor);

        if (key == "" || value == "")
            break;

        trim(key, ' ');
        trim(value, ' ');
        appendHeader(key, value);
    }
};

void HttpResponseParser::parseBody()
{
    // Becuase we only care about multipart/form-data we will check
    // for it. If we dont see it, im gonna write the body to a
    // string
    if (headersMap.count(CT) > 0 && headersMap.find(CT)->second == CT_MULTI_PART_FORM_DATA)
    {
        parseMultiPart();
        return;
    }

     std::vector<char> bodyBuilder;
    while (*(res) > 0)
    {
        bodyBuilder.push_back(*res);
        res++;
    }
     this->body = bodyBuilder;
};

HttpResponseParser::Method HttpResponseParser::stringToMethod(string method)
{
    for (auto &c : method)
        c = toupper(c);

    if (method == "POST")
        return Method::POST;

    if (method == "DELETE")
        return Method::DELETE;

    return Method::GET;
}

string HttpResponseParser::getNext(string pattern)
{
    size_t patternLength = pattern.size();

    string result;
    char *character;

    // Read socket into string.
    while (!isMatch(result, pattern) && *(character = res) != EOF)
    {
        result += *character;
        res++;
    }

    // Remove pattern from string
    result.resize(result.size() - pattern.size());

    return result;
}

string HttpResponseParser::getNext(char *str, int size, string pattern, int *cursor)
{
    string result;
    if (size < pattern.size() || *cursor >= size)
    {
        return "";
    }

    for (int i = 0; i < size; i++)
    {
        if (*cursor >= size)
        {
            return result;
        }

        result += *str;
        (*cursor)++;
        *(str++);

        if (isMatch(result, pattern))
        {
            result.resize(result.size() - pattern.size());
            return result;
        }
    }

    return result;
}

bool HttpResponseParser::isMatch(string str, string pattern)
{
    if (pattern.size() > str.size() || pattern == "")
        return false;

    for (int i = 0; i < pattern.size(); i++)
    {
        if (str[str.size() - 1 - i] != pattern[pattern.size() - 1 - i])
            return false;
    }

    return true;
}

void HttpResponseParser::trim(string &str, char pattern)
{
    int left = 0;
    int right = str.size() - 1;

    while (str[left] == pattern)
        left++;

    while (str[right] == pattern)
        right--;

    string temp = "";

    while (left <= right)
        temp += str[left++];

    str = temp;
}

void HttpResponseParser::trim(string &str)
{
    int left = 0;
    int right = str.size() - 1;

    while (str[left] == ' ' || str[left] == '\r' || str[left] == '\n')
        left++;

    while (str[right] == ' ' || str[right] == '\r' || str[right] == '\n')
        right--;

    string temp = "";

    while (left <= right)
        temp += str[left++];

    str = temp;
}

bool HttpResponseParser::hasPattern(string str, string pattern)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == pattern[i])
        {
            int j = 0;
            while (j < pattern.size() && str[i + j] != pattern[j])
            {
                if (j == pattern.size() - 1)
                {
                    return true;
                }
                j++;
            }
        }
    }
    return false;
}

/**
 * Returns true if key is an edge case.
 */
bool HttpResponseParser::headerEdgeCases(string key, string value)
{
    // cout << "EDGE CASES: " << key << " --54545|-- " << value << endl;
    // cout << "IS EDGE CASE " << (key == CT) << " --54545|-- " << hasPattern(value, CT_MULTI_PART_FORM_DATA) << endl;

    // Check to see if it form "Content-Type:multipart/form-data"
    if (key == CT && hasPattern(value, CT_MULTI_PART_FORM_DATA))
    {
        return true;
    }
    return false;
};

/**
 * Appends key, value to headerMap
 */
void HttpResponseParser::appendHeader(string key, string value)
{
    // Its lie to call this headerEdgeCases, becuase we
    // are only checking for multipart/form-data
    // &()
    // But i called it headerEdgeCases because its more VERBOSE!
    // :()::<>::{}::~~
    if (headerEdgeCases(key, value))
    {
        int n = value.length();

        // declaring character array
        char v[n + 1];

        // copying the contents of the string to char array
        strcpy(v, value.c_str());
        int cursor = 0;

        // Seperate value into two values.
        value = getNext(v, n, "; ", &cursor);

        // Remove boundry=
        getNext(v + cursor, n, "=", &cursor);

        // Get rest of string to add to boundry
        this->boundry = getNext(v + cursor, n, "", &cursor);

        // cout << "BOUNDRY: " << this->boundry << endl;
    }
    this->headersMap.insert(pair<string, string>(key, value));
};

ostream &operator<<(ostream &os, const HttpResponseParser &res)
{

    os << "HEAD: \n"
       << res.method << " " << res.url << " " << res.version << endl;

    os << "\nHEADERS: \n";
    for (auto const &x : res.headersMap)
    {
        os << x.first // string (key)
           << ':'
           << x.second
           << endl; // string's value
    }

    os << "Boundry: " << res.boundry << endl;

    os << "\nBODY: \n";
    if (res.headersMap.count(CT) > 0 && res.headersMap.find(CT)->second == CT_MULTI_PART_FORM_DATA)
    {
        // Print body map

        for (auto const &x : res.bodyMap)
        {
            os << x.first // string (key)
               << ':'
               << x.second
               << endl; // string's value
        }
        return os;
    }

    // For some reason these had to be constants. Can anyone tell me
    // why?
    std::vector<char>::const_iterator it = res.body.begin();
    std::vector<char>::const_iterator end = res.body.end();

    int pos = 0;
    while ((it + pos) < end)
    {
        os << (char)*(it + pos++);
    }

    return os;
}

void HttpResponseParser::parseMultiPart()
{
    // JUST TO MAKE SURE MY THREAD IS ARRIVING
    // cout << "PARSING MULTI PART --|-- PARSING MULTI PART" << endl;

    // This what i got to do.
    // I need to read the socket line by line
    // if i see an image is present, im going to  to read it directly
    // to a new file

    // Removes first boundry
    string line = getNext("--" + this->boundry + LINE);

    while (line == "")
    {
        string metaData = getNext(BOUNDRY);
        std::map<string, string> metaDataMap;
        parseMultiPartMetaData(metaData, metaDataMap);

        if (metaDataMap.count("filename") > 0)
        {
            this->bodyMap.insert(std::pair<string, string>{"filename", metaDataMap.find("filename")->second});
            // stream socket dirrectly into file
            // Lets save this for another time.
            break;
        }

        // cout << "META DATA PARSED: " << endl;

        // for (auto const &x : metaDataMap)
        // {
        //     std::cout << x.first // string (key)
        //               << ':'
        //               << x.second // string's value
        //               << std::endl;
        // }

        string data = getNext(LINE);
        // cout << "DATA: " << data << endl;
        this->bodyMap.insert(std::pair<string, string>{metaDataMap.find("name")->second, data});
        line = getNext("--" + this->boundry + LINE);
    }
}

void HttpResponseParser::parseMultiPartMetaData(string str, std::map<string, string> &map)
{
    // cout << "PARSING META DATA --|-- PARSING META DATA" << endl;
    int n = str.size();
    // declaring character array
    char v[n + 1];

    // copying the contents of the string to char array
    strcpy(v, str.c_str());
    int cursor = 0;

    // Split content disposition and content type
    string cd = getNext(v + cursor, n, LINE, &cursor);
    string ct = getNext(v + cursor, n, BOUNDRY, &cursor);

    // // Remove white space
    trim(cd);
    trim(ct);

    // cout << "CONTENT DISP: " << cd << endl;
    // cout << "CONTENT TYPE: " << ct << endl;

    // Parse Content Disposition
    int nCD = cd.length();
    // declaring character array
    char vCD[nCD + 1];
    // copying the contents of the string to char array
    strcpy(vCD, cd.c_str());
    int cursorCD = 0;

    // Move cursor to first key value pair
    getNext(vCD + cursorCD, nCD, "; ", &cursorCD);

    // parse line
    while (cursorCD < nCD)
    {
        // Get key value
        string key = getNext(vCD + cursorCD, nCD, "=", &cursorCD);
        string value = getNext(vCD + cursorCD, nCD, "; ", &cursorCD);

        // Remove quotes
        trim(value, '\"');

        // cout << "KEY: " << key << " VALUE: " << value << endl;
        map.insert(std::pair<string, string>(key, value));
    }

    if (ct != "")
    {
        // cout << "CONTENT TYPE: " << ct << endl;
        // Parse Content Disposition
        int nCT = ct.length();
        // declaring character array
        char vCT[nCT + 1];
        // copying the contents of the string to char array
        strcpy(vCT, ct.c_str());
        int cursorCT = 0;
        // cout << "BEOFRE REMOVING CONTENT_TYPE: " << (vCT + cursorCT) << endl;

        getNext(vCT + cursorCT, nCT, ": ", &cursorCT);

        // cout << "AFTER REMOVING CONTENT_TYPE: " << (vCT + cursorCT) << endl;
        // parse line
        string value = getNext(vCT + cursorCT, nCT, "", &cursorCT);
        // cout << "CONTENT TYPE VALUE: " << value << endl;
        map.insert(std::pair<string, string>("Content-Type", value));
    }
};