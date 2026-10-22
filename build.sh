#!/bin/bash
# =========================================================================
# build.sh - Build Script for cpp-tn5250
# Sources project.sh as Single Source of Truth + safe fallbacks.
# Compiles lib5250 and the GNOME terminal into one binary.
# clean removes only target/ and builddir/. It leaves the upstream autotools tree.
# =========================================================================

set -e

# ====================== Source project.sh (Single Source of Truth) ======================
if [ -f "./project.sh" ]; then
    echo "[INFO] Sourcing project.sh as Single Source of Truth..."
    source ./project.sh
else
    echo "[WARN] project.sh not found — using safe generic fallbacks"
    export PRJ="${PRJ:-$(basename "$(pwd)")}"
    export SRC="${SRC:-src}"
    export SRC_C="${SRC_C:-$SRC/main/cpp}"
    export BUILD="${BUILD:-target}"
    export BUILD_DEBUG="${BUILD_DEBUG:-$BUILD/exe/debug}"
fi

# Ensure required variables have sensible defaults
PROJECT_NAME="${PRJ:-app}"
SRC_DIR="${SRC_C:-src/main/cpp}"
BUILD_DIR="${BUILD_DEBUG:-target/exe/debug}"
OBJ_DIR="${BUILD_DIR}/obj"
BINARY="${BUILD_DIR}/${PROJECT_NAME}"

LIB_SOURCES="
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

APP_SOURCES="
src/main/cpp/main.cpp
src/main/cpp/logger.cpp
src/main/cpp/gtkterm.cpp
src/main/cpp/gnome_app.cpp
"

install_deps() {
    echo "[INFO] Installing required development packages..."
    sudo apt update -qq
    sudo apt install -y -qq \
        build-essential \
        pkg-config \
        libglib2.0-dev \
        libgtk-3-dev \
        libssl-dev

    echo "[INFO] All dependencies installed successfully."
}

# Place the already-built binary. Does not compile, does not call sudo, does not run apt.
place_built_binary() {
    local dest_dir="$1"

    if [ ! -x "${BINARY}" ]; then
        echo "[ERROR] Build the program first. Missing ${BINARY}"
        exit 1
    fi
    mkdir -p "${dest_dir}"
    install -m 0755 "${BINARY}" "${dest_dir}/${PROJECT_NAME}"
    echo "[INFO] Installed ${dest_dir}/${PROJECT_NAME}"
}

install_local() {
    # Operator place only. Tests must not call this and must not expand HOME.
    if [ -z "${HOME}" ]; then
        echo "[ERROR] HOME is empty. Local installation needs a home directory."
        exit 1
    fi
    place_built_binary "${HOME}/.local/bin"
}

install_global() {
    local prefix="${PREFIX:-/usr/local}"
    local global_bin="${prefix%/}/bin"
    if [ ! -d "${global_bin}" ] || [ ! -w "${global_bin}" ]; then
        echo "[ERROR] ${global_bin} is not writable. Re-run as the user who can write that directory. This command does not call sudo."
        exit 1
    fi
    place_built_binary "${global_bin}"
}

# ====================== clean ======================
clean() {
    echo "[INFO] Cleaning build artifacts..."
    rm -rf target builddir
    echo "[INFO] Clean completed."
}

# ====================== build ======================
# =========================================================================
# CIAO PROTECTION BLOCK - build() function (Sacred)
# =========================================================================
#
# This function is the Single Point of Truth for compilation and linking.
# Future AI or developers MUST NOT:
#   - Rewrite or heavily refactor the compilation logic
#   - Remove or simplify the PKG_FLAGS
#   - Change the compile + link approach without strong justification
#   - Bypass this function for building the application
#   - Delete upstream autotools products from clean()
#
# Reason: This logic was battle-tested and finally produced a successful build.
# Changing it violates CIAO Principle 7 (Reusable Function Protection) and
# Principle 18 (Protect Against AI & Human Modification).
#
# Last updated: 2026-10-22
# The product compiles lib5250 with the GNOME terminal. Objects stay under
# target/exe/debug/obj so upstream lib5250/*.o files are left in place.
# =========================================================================
build() {
    echo "[INFO] Starting simple GCC/C++ build for ${PROJECT_NAME}..."

    mkdir -p "${OBJ_DIR}"

    echo "[DEBUG] PKG_CONFIG_PATH = ${PKG_CONFIG_PATH}"
    echo "[DEBUG] Packages requested from pkg-config: gtk+-3.0"

    PKG_FLAGS=$(pkg-config --cflags --libs \
        gtk+-3.0 2>&1)

    echo "[DEBUG] pkg-config output:"
    echo "${PKG_FLAGS}"

    local pkg_cflags
    local pkg_libs
    pkg_cflags=$(pkg-config --cflags gtk+-3.0)
    pkg_libs=$(pkg-config --libs gtk+-3.0)

    local objects=""
    local source
    for source in ${LIB_SOURCES}; do
        local object="${OBJ_DIR}/$(basename "${source}" .cpp).o"
        echo "[INFO] Compiling ${source}"
        g++ -std=c++17 -g -O2 -I. -Ilib5250 -DSYSCONFDIR=\"/usr/local/etc\" \
            ${pkg_cflags} -c "${source}" -o "${object}"
        objects="${objects} ${object}"
    done
    for source in ${APP_SOURCES}; do
        local object="${OBJ_DIR}/$(basename "${source}" .cpp).o"
        echo "[INFO] Compiling ${source}"
        g++ -std=c++17 -Wall -Wextra -Werror -g -O2 -I. -Ilib5250 -Isrc/main/cpp \
            -DSYSCONFDIR=\"/usr/local/etc\" \
            ${pkg_cflags} -c "${source}" -o "${object}"
        objects="${objects} ${object}"
    done

    echo "[INFO] Linking final binary..."
    g++ ${objects} -o "${BINARY}" ${pkg_libs} -lssl -lcrypto -pthread

    echo "[INFO] Build successful!"
    echo "[INFO] Binary ready → ${BINARY}"
    echo "[INFO] Run with: ${BINARY}"
}

# ====================== Main logic ======================
case "$1" in
    install|deps)
        install_deps
        ;;
    install-local)
        install_local
        ;;
    install-global)
        install_global
        ;;
    clean)
        clean
        ;;
    build|""|simple)
        build
        ;;
    *)
        echo "Usage: $0 {install|install-local|install-global|clean|build}"
        echo "   install         → install system dependencies"
        echo "   install-local   → copy the built binary to \$HOME/.local/bin"
        echo "   install-global  → copy the built binary to \${PREFIX:-/usr/local}/bin"
        echo "   clean           → remove target/ and builddir/"
        echo "   build           → compile the application"
        exit 1
        ;;
esac
