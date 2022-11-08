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

    if (this->method != 0) {
        parseBody();
    }

//    char * character;
//    int count = 0;
//    while(count++ < 10000) {
//        *(character = this->socket->getNext()) > 0;
//        cout << *character;
//    }

    cout << *this << endl;
}

void HttpServletRequest::parseHead()
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

void HttpServletRequest::parseHeaders()
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

void HttpServletRequest::parseBody()
{
    // Becuase we only care about multipart/form-data we will check
    // for it. If we dont see it, im gonna write the body to a
    // string
    if (headersMap.count(CT) > 0 && headersMap.find(CT)->second == CT_MULTI_PART_FORM_DATA)
    {
        parseMultiPart();
        return;
    }

    // std::vector<char> body;
    // this->socket->dump(body);
    // this->body = body;
};

HttpServletRequest::Method HttpServletRequest::stringToMethod(string method)
{
    trim(method);
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
//    cout << "READ FROM SOCKET" << endl;
    while (!isMatch(result, pattern) && !isMatch(result, "--\r\n") && *(character = socket->getNext()) != EOF)
    {
        result += *character;
//        cout << "APPENDING: " << (int) *character << endl;
//        if (result.size() > 2) {
////            cout << "LAST ONE-TWO: " << (int) result[result.size() - 1] << " " << (int) result[result.size() - 2] << endl;
////            cout << "APPENDING: " << result << endl;
//        }

    }

//    cout << "RESULT: " << result << endl;

    // Remove pattern from string
    result.resize(result.size() - pattern.size());
//    cout << "RESULT + SUBTRACTION: " << result << endl;

    return result;
}

string HttpServletRequest::getNext(char *str, int size, string pattern, int *cursor)
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

bool HttpServletRequest::isMatch(string str, string pattern)
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

void HttpServletRequest::trim(string &str, char pattern)
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

void HttpServletRequest::trim(string &str)
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

bool HttpServletRequest::hasPattern(string str, string pattern)
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
bool HttpServletRequest::headerEdgeCases(string key, string value)
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
void HttpServletRequest::appendHeader(string key, string value)
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

ostream &operator<<(ostream &os, const HttpServletRequest &req)
{

    os << "\nHEAD: \n"
       << req.method << " " << req.url << " " << req.version << endl;

    os << "\nHEADERS: \n";
    for (auto const &x : req.headersMap)
    {
        os << x.first // string (key)
           << ':'
           << x.second
           << endl; // string's value
    }

    os << "Boundry: " << req.boundry << endl;

    os << "\nBODY: \n";
    if (req.headersMap.count(CT) > 0 && req.headersMap.find(CT)->second == CT_MULTI_PART_FORM_DATA)
    {
        // Print body map

        for (auto const &x : req.bodyMap)
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
//    std::vector<char>::const_iterator it = req.body.begin();
//    std::vector<char>::const_iterator end = req.body.end();
//
//    int pos = 0;
//    while ((it + pos) < end)
//    {
//        os << (char)*(it + pos++);
//    }
//
    return os;
}

void HttpServletRequest::parseMultiPart()
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

        std::cout << "BEFORE METADATA --|-- BEFORE METADATA" << std::endl;
        string metaData = getNext(BOUNDRY);
        std::cout << "METADATA --|-- = " << metaData << std::endl;
        std::map<string, string> metaDataMap;
        parseMultiPartMetaData(metaData, metaDataMap);

        cout << "META DATA PARSED: " << endl;

        for (auto const &x : metaDataMap)
        {
            std::cout << x.first // string (key)
                      << ':'
                      << x.second // string's value
                      << std::endl;
        }

        if (metaDataMap.count("filename") > 0)
        {
//            if (metaDataMap.find("Content-Type")->second == "image/png") {
//                streamPNGToFile(metaDataMap.find("filename")->second);
//                break;
//            }
            streamIntoFile(metaDataMap.find("filename")->second);
            break;
        }



        string data = getNext(LINE);
//         cout << "DATA: " << data << endl;
        this->bodyMap.insert(std::pair<string, string>{metaDataMap.find("name")->second, data});
        line = getNext("--" + this->boundry + LINE);
        trim(line);
//        cout << "NEXT LINE --|-- NEXT LINE" << endl << ("" == line) << endl;
    }
}



void HttpServletRequest::parseMultiPartMetaData(string str, std::map<string, string> &map)
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
}

void HttpServletRequest::streamIntoFile(string fileName) {

    cout << "PARSING FILE --|-- PARSING FILE" << endl;
    // Logic to into file.
    ofstream file;
    file.open(fileName);

    // Create 2 char array;
    char* buffer = new char[4];
    buffer[0] = *socket->getNext();
    buffer[1] = *socket->getNext();
    buffer[2] = *socket->getNext();
    buffer[3] = *socket->getNext();


    while(!(buffer[0] == '\r' && buffer[1] == '\n' && buffer[2] == '-' && buffer[3] == '-')) {
        file << buffer[0];
        cout << hex << (int)buffer[0] << " " << (int)buffer[1] << " " << (int)buffer[2] << " " << (int)buffer[3] << endl;



        buffer[0] = buffer[1];
        buffer[1] = buffer[2];
        buffer[2] = buffer[3];
        buffer[3] = *socket->getNext();
    }
//    getNext(boundry);

//    cout << (buffer[0] == '\r') << " ";
//    cout << (buffer[1] == '\n') << " ";


    delete buffer;
};

void HttpServletRequest::streamPNGToFile(string fileName) {
    cout << "PARSING PNG --|-- PARSING PNG" << endl;
    cout << "WE DONT KNOW HOW TO PARSE PNGS --|-- WE DONT KNOW HOW TO PARSE PNGS" << endl;
};

