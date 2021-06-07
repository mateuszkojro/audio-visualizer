cmake_minimum_required(VERSION 3.19)
project(tinyfiledialogs C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(more_dialogs)

add_executable(tinyfiledialogs
        more_dialogs/tinyfd_moredialogs.c
        more_dialogs/tinyfd_moredialogs.h
        hello.c
#        hello_wchar_t.c
        tinyfiledialogs.c
        tinyfiledialogs.h)
