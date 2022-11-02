//
// Created by Admin on 2022-10-31.
//

#include <iostream>
#include <limits>

#include "FileUploadMenu.hpp"
#include "HttpRequestBuilder.hpp"


using namespace std;

void clean_cin() {
    cin.clear(); //clearing out bad bits
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clearing garbage in buffer
}

map <string, string> FileUploadMenu::getDataFromUser(){
    map<string, string>data;

    cout << endl << "Welcome to the File Upload CLI!!!" << endl;

    cout << endl << "Please enter a caption" << endl;
    string caption;
    getline(cin, caption);
    data.insert(pair<string, string>("caption", caption));

    cout << endl << "Please enter a date yyyymmdd" << endl;
    string date;
    getline(cin, date);
    data.insert(pair<string, string>("date", date));

    cout << endl << "Please enter a file path" << endl;
    string file_path;
    getline(cin, file_path);
    data.insert(pair<string, string>("file_path", file_path));

    return data;
}

void FileUploadMenu::buildRequest(map <std::string, std::string> dataFromUser) {
    string filePath = dataFromUser.at("file_path");
    string caption = dataFromUser.at("caption");
    string date = dataFromUser.at("date");
    this->setRequestString(HttpRequestBuilder::buildMultipartRequest(filePath, caption, date));
}