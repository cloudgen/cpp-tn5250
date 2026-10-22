#!/bin/sh
# Warning: do not call mktemp or mkstemp.
# Do not read, expand, assign, or delete the home environment variable.
# This check builds one binary with g++ and does not run ./build.sh.
# It opens the window on the current display and leaves after one second.
set -eu

cd "$(dirname "$0")/.."

work=/tmp/cpp-tn5250-window-work
rm -rf "${work}"
mkdir "${work}"

sh tests/compile-app.sh "${work}"
bin="${work}/cpp-tn5250"

if [ -z "${DISPLAY:-}" ]; then
    echo "[ERROR] DISPLAY is unset. The window check needs a graphical session."
    exit 1
fi

env -u HOME -u PREFIX "${bin}" --verbose --shutdown=1 >"${work}/window.txt" 2>"${work}/window.err"
grep -F 'gnome window ready' "${work}/window.txt" >/dev/null
if grep -F 'WebKit' "${work}/window.txt" "${work}/window.err" >/dev/null; then
    echo "[ERROR] the window run mentioned WebKit"
    exit 1
fi

echo "PASS gnome window"
rm -rf "${work}"
