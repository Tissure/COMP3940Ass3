//
// Created by Admin on 2022-10-31.
//

#pragma once
#ifndef C_WRAPPERS_FILEUPLOADMENU_HPP
#define C_WRAPPERS_FILEUPLOADMENU_HPP

#include <string>
#include <map>

using namespace std;

class FileUploadMenu {
private:
    string requestString;

public:
    map <string, string> getDataFromUser();

    void buildRequest(map <string, string> dataFromUser);

    void handleResponse(char * res);

    string getRequestString() { return this->requestString; }

    void setRequestString(string requestString) { this->requestString = requestString; }
};


#endif //C_WRAPPERS_FILEUPLOADMENU_HPP
