cmake_minimum_required(VERSION 3.13)
project(Http)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(server/servlets)

add_executable(server server/servlets/HttpServletResponse.hpp
        server/servlets/HttpServletResponse.cpp
        server/servlets/HttpServletRequest.hpp
        server/servlets/HttpServletRequest.cpp

        server/servlets/UploadServlet.cpp
        server/servlets/UploadServlet.hpp


        server/sockets/ServerSocket.h
        server/sockets/ServerSocket.cpp
        server/sockets/Socket.h
        server/sockets/Socket.cpp

        server/threads/Router.hpp
        server/threads/Router.cpp
        server/threads/SimpleThread.h
        server/threads/SimpleThread.cpp
        server/threads/Thread.h
        server/threads/Thread.cpp

        server/main.cpp
        )

include_directories(client)

add_executable(client client/FileUploadMenu.hpp
        client/FileUploadMenu.cpp
        client/HttpRequestBuilder.hpp
        client/HttpRequestBuilder.cpp

        client/HttpResponseBuilder.hpp
        client/HttpResponseBuilder.cpp

        client/socketclient.cpp
        )