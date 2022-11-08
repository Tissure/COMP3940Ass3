//
// Created by Admin on 2022-10-31.
//

#include <iostream>
#include <limits>
#include <iterator>

#include "FileUploadMenu.hpp"
#include "HttpRequestBuilder.hpp"
#include "HttpResponseParser.hpp"


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

void FileUploadMenu::handleResponse(char *res) {
//    string fileName = null;
    cout << "File names returned from the server: "<< endl;
//    for (int i = 0; i < 1024; ++i) {
//        cout << res[i];
//    }
    HttpResponseParser parser{res};
    parser.parse();
    vector<char> body = parser.getBody();
    copy(body.begin(), body.end(), std::ostream_iterator<char>(cout));
//    try {
//        // move until we reach the body of the response
//        while (in.readLine() != "\r\n\r\n" && !in.readLine().isEmpty());
//        // read the body of the response
//        while ((fileName = in.readLine()) != null) {
//            System.out.println(fileName);
//        }
//    } catch (IOException e) {
//        e.printStackTrace();
//    }
}

