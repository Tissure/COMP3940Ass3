cmake_minimum_required(VERSION 3.13)
project(Http)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(servlets/Http)

add_executable(server servlets/HttpServletResponse.hpp
        servlets/HttpServletResponse.cpp
        servlets/HttpServletRequest.hpp
        servlets/HttpServletRequest.cpp

        servlets/UploadServlet.cpp
        servlets/UploadServlet.hpp


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

        main.cpp
        )