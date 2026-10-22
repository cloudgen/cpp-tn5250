cmake_minimum_required(VERSION 3.12)
project(tn5250 LANGUAGES CXX VERSION 0.19.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckIncludeFileCXX)
include(GNUInstallDirs)

find_package(OpenSSL)

if (NOT WIN32)
    # For now, assume Windows users don't want curses build
    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses REQUIRED)
endif()

option(CURSES_OLD_KEYS "Use curses built-in key handling" YES)

check_include_file_cxx("fcntl.h" HAVE_FCNTL_H)
check_include_file_cxx("pwd.h" HAVE_PWD_H)
check_include_file_cxx("syslog.h" HAVE_SYSLOG_H)
check_include_file_cxx("sys/time.h" HAVE_SYS_TIME_H)
check_include_file_cxx("sys/types.h" HAVE_SYS_TYPES_H)
check_include_file_cxx("sys/wait.h" HAVE_SYS_WAIT_H)
check_include_file_cxx("termcap.h" HAVE_TERMCAP_H)
check_include_file_cxx("unistd.h" HAVE_UNISTD_H)

configure_file(config-cmake.h.in config.h @ONLY)

add_subdirectory(doc)
add_subdirectory(lib5250)
add_subdirectory(termcaps)

if (WIN32)
    add_subdirectory(win32)
else()
    add_subdirectory(curses)
    add_subdirectory(lp5250d)
endif()
