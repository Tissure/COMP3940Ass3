//
// Created by Admin on 2022-10-31.
//

#ifndef C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
#define C_WRAPPERS_HTTPSERVLETRESQUEST_HPP

#include <istream>

using namespace std;

class HttpServletRequest {
public:
    HttpServletRequest(istream&);
};


#endif //C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
