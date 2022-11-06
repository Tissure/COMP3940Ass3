cmake_minimum_required(VERSION 3.13)
project(Http)

set(CMAKE_CXX_STANDARD 14)

include_directories(servlets/Http)

add_executable(Server servlets/HttpServletResponse.hpp
        servlets/HttpServletResponse.cpp
        servlets/HttpServletRequest.hpp
        servlets/HttpServletRequest.cpp

        servlets/UploadServlet.cpp
        servlets/UploadServlet.hpp

        main.cpp

        sockets/ServerSocket.h
        sockets/ServerSocket.cpp
        sockets/Socket.h
        sockets/Socket.cpp

        threads/Router.hpp
        threads/Router.cpp
        threads/SimpleThread.h
        threads/SimpleThread.cpp
        threads/Thread.h
        threads/Thread.cpp
        
        )