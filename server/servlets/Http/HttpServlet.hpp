//
// Created by Admin on 2022-10-31.
//

#ifndef C_WRAPPERS_HTTPSERVLET_HPP
#define C_WRAPPERS_HTTPSERVLET_HPP


class HttpServlet {
public:
    virtual void doGet() = 0;
    virtual void doPost() = 0;
};


#endif //C_WRAPPERS_HTTPSERVLET_HPP
