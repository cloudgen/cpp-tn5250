#!/bin/sh
# Compile one cpp-tn5250 binary with g++. Do not call ./build.sh.
# Do not read, expand, assign, or delete HOME.
# Argument: work directory. The binary is <work>/cpp-tn5250.
set -eu

if [ "$#" -ne 1 ]; then
    echo "[ERROR] usage: tests/compile-app.sh <work-directory>"
    exit 1
fi

work=$1
cd "$(dirname "$0")/.."
mkdir -p "${work}"

cflags=$(pkg-config --cflags gtk+-3.0)
libs=$(pkg-config --libs gtk+-3.0)

lib_sources="
lib5250/buffer.cpp
lib5250/conf.cpp
lib5250/dbuffer.cpp
lib5250/debug.cpp
lib5250/display.cpp
lib5250/field.cpp
lib5250/macro.cpp
lib5250/menu.cpp
lib5250/printsession.cpp
lib5250/record.cpp
lib5250/scrollbar.cpp
lib5250/scs.cpp
lib5250/session.cpp
lib5250/sslstream.cpp
lib5250/stream.cpp
lib5250/telnetstr.cpp
lib5250/terminal.cpp
lib5250/utility.cpp
lib5250/version.cpp
lib5250/window.cpp
lib5250/wtd.cpp
"

app_sources="
src/main/cpp/main.cpp
src/main/cpp/logger.cpp
src/main/cpp/gtkterm.cpp
src/main/cpp/gnome_app.cpp
"

objects=""
for source in ${lib_sources}; do
    object="${work}/$(basename "${source}" .cpp).o"
    g++ -std=c++17 -g -O2 -I. -Ilib5250 -DSYSCONFDIR=\"/usr/local/etc\" \
        ${cflags} -c "${source}" -o "${object}"
    objects="${objects} ${object}"
done
for source in ${app_sources}; do
    object="${work}/$(basename "${source}" .cpp).o"
    g++ -std=c++17 -Wall -Wextra -Werror -g -O2 -I. -Ilib5250 -Isrc/main/cpp \
        -DSYSCONFDIR=\"/usr/local/etc\" \
        ${cflags} -c "${source}" -o "${object}"
    objects="${objects} ${object}"
done

g++ ${objects} -o "${work}/cpp-tn5250" ${libs} -lssl -lcrypto -pthread
