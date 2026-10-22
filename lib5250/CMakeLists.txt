cmake_minimum_required(VERSION 3.12)
project(lib5250 LANGUAGES CXX)

include_directories(${CMAKE_BINARY_DIR})

add_library(5250 STATIC buffer.cpp conf.cpp dbuffer.cpp debug.cpp display.cpp field.cpp macro.cpp menu.cpp printsession.cpp record.cpp scrollbar.cpp scs.cpp session.cpp sslstream.cpp stream.cpp telnetstr.cpp terminal.cpp utility.cpp version.cpp window.cpp wtd.cpp buffer.h codes5250.h conf.h dbuffer.h debug.h display.h field.h macro.h menu.h printsession.h record.h scrollbar.h scs.h session.h stream.h terminal.h utility.h window.h wtd.h transmaps.h scs-private.h tn5250-private.h)

if (${OPENSSL_FOUND})
    target_link_libraries(5250 OpenSSL::Crypto OpenSSL::SSL)
endif()

if (WIN32)
    target_link_libraries(5250 Ws2_32 Winmm)
endif()
