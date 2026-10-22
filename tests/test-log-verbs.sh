#!/bin/sh
# Warning: do not call mktemp or mkstemp.
# Do not read, expand, assign, or delete the home environment variable.
# If a new home assignment fails, the shell keeps the original home.
# Removing that directory would destroy the user account.
# This check builds one binary and runs list and show with the literal directory /tmp.
# Cleanup removes /tmp/.app/cpp-tn5250, /tmp/var/cpp-tn5250, /tmp/cpp-tn5250-home-decoy,
# /tmp/cpp-tn5250-prefix-decoy, empty parents, and the work directory.
# It does not remove /tmp and it does not start a normal run.
set -eu

cd "$(dirname "$0")/.."

work=/tmp/cpp-tn5250-verb-work
home_dir=/tmp/.app/cpp-tn5250/log
prefix_dir=/tmp/var/cpp-tn5250/log
home_old=${home_dir}/cpp-tn5250-20261002.log
home_new=${home_dir}/cpp-tn5250-20261003.log
prefix_new=${prefix_dir}/cpp-tn5250-20261003.log
home_decoy=/tmp/cpp-tn5250-home-decoy
prefix_decoy=/tmp/cpp-tn5250-prefix-decoy

rm -rf "${work}" "${home_decoy}" "${prefix_decoy}"
rm -rf /tmp/.app/cpp-tn5250
rm -rf /tmp/var/cpp-tn5250
rmdir /tmp/.app 2>/dev/null || true
rmdir /tmp/var 2>/dev/null || true
mkdir "${work}"

sh tests/compile-app.sh "${work}"

bin="${work}/cpp-tn5250"

empty_out=$(env -u HOME -u PREFIX "${bin}" list --home /tmp)
if [ -n "${empty_out}" ]; then
    echo "[ERROR] list printed names before any log file existed"
    exit 1
fi
if [ -d /tmp/.app/cpp-tn5250 ]; then
    echo "[ERROR] list created the log directory"
    exit 1
fi

if env -u HOME -u PREFIX "${bin}" list >"${work}/no-root.txt" 2>&1; then
    echo "[ERROR] list ran without a directory switch"
    exit 1
fi
grep -F 'test purpose command requires --prefix or --home' "${work}/no-root.txt" >/dev/null
if env -u HOME -u PREFIX "${bin}" show --home /tmp >"${work}/miss-stamp.txt" 2>&1; then
    echo "[ERROR] show ran without a datestamp"
    exit 1
fi
grep -F 'test purpose command requires --log-datestamp YYYYMMDD' "${work}/miss-stamp.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" test --home /tmp --log-datestamp 20261002 --quiet >/dev/null
env -u HOME -u PREFIX "${bin}" test --home /tmp --log-datestamp 20261003 --quiet >/dev/null

list_out=$(env -u HOME -u PREFIX "${bin}" list --home /tmp)
printf '%s\n' "${list_out}" | grep -F 'cpp-tn5250-20261002.log' >/dev/null
printf '%s\n' "${list_out}" | grep -F 'cpp-tn5250-20261003.log' >/dev/null
expected='cpp-tn5250-20261002.log
cpp-tn5250-20261003.log'
if [ "${list_out}" != "${expected}" ]; then
    echo "[ERROR] list did not print the names in sorted order"
    printf '%s\n' "${list_out}"
    exit 1
fi

printf 'nope\n' > "${home_dir}/notes.txt"
mkdir "${home_dir}/extra.log"
list_out=$(env -u HOME -u PREFIX "${bin}" list --home /tmp)
if [ "${list_out}" != "${expected}" ]; then
    echo "[ERROR] list printed a non-log name or a directory"
    printf '%s\n' "${list_out}"
    exit 1
fi
rm -f "${home_dir}/notes.txt"
rmdir "${home_dir}/extra.log"

show_out=$(env -u HOME -u PREFIX "${bin}" show --home /tmp --log-datestamp 20261003)
file_out=$(cat "${home_new}")
if [ "${show_out}" != "${file_out}" ]; then
    echo "[ERROR] show did not print the dated file"
    exit 1
fi
printf '%s\n' "${show_out}" | grep -F '] @main :] test log' >/dev/null
if printf '%s\n' "${show_out}" | grep -F '20261002' >/dev/null; then
    echo "[ERROR] show printed the other date"
    exit 1
fi

before=$(cat "${home_new}")
env -u HOME -u PREFIX "${bin}" list --home /tmp >/dev/null
env -u HOME -u PREFIX "${bin}" show --home /tmp --log-datestamp 20261003 >/dev/null
after=$(cat "${home_new}")
if [ "${before}" != "${after}" ]; then
    echo "[ERROR] list or show changed the log file"
    exit 1
fi

quiet_list=$(env -u HOME -u PREFIX "${bin}" list --home /tmp --quiet)
if [ "${quiet_list}" != "${expected}" ]; then
    echo "[ERROR] --quiet hid the log file names"
    printf '%s\n' "${quiet_list}"
    exit 1
fi
json_show=$(env -u HOME -u PREFIX "${bin}" show --home /tmp --log-datestamp 20261003 --json)
if [ "${json_show}" != "${show_out}" ]; then
    echo "[ERROR] --json hid or changed the log file text"
    exit 1
fi
if printf '%s\n' "${json_show}" | grep -F '{"timestamp"' >/dev/null; then
    echo "[ERROR] show printed a JSON object"
    exit 1
fi

if env -u HOME -u PREFIX "${bin}" show --home /tmp --log-datestamp 2026 >"${work}/bad-stamp.txt" 2>&1; then
    echo "[ERROR] show accepted a short datestamp"
    exit 1
fi
grep -F -- '--log-datestamp requires YYYYMMDD' "${work}/bad-stamp.txt" >/dev/null
if grep -F 'test purpose command requires --log-datestamp' "${work}/bad-stamp.txt" >/dev/null; then
    echo "[ERROR] a present stamp was reported as missing"
    exit 1
fi
if env -u HOME -u PREFIX "${bin}" list --home /tmp --log-datestamp 2026 >"${work}/bad-stamp.txt" 2>&1; then
    echo "[ERROR] list accepted a short datestamp"
    exit 1
fi
grep -F -- '--log-datestamp requires YYYYMMDD' "${work}/bad-stamp.txt" >/dev/null

if env -u HOME -u PREFIX "${bin}" test list --home /tmp --log-datestamp 20261003 >"${work}/two.txt" 2>&1; then
    echo "[ERROR] two purpose commands were accepted"
    exit 1
fi
grep -F 'one test purpose command' "${work}/two.txt" >/dev/null
after=$(cat "${home_new}")
if [ "${before}" != "${after}" ]; then
    echo "[ERROR] a rejected second command changed the log file"
    exit 1
fi

prefix_list=$(env -u HOME -u PREFIX "${bin}" list --prefix /tmp)
if [ -n "${prefix_list}" ]; then
    echo "[ERROR] list --prefix printed names before a prefix file existed"
    exit 1
fi

env -u HOME -u PREFIX "${bin}" test --prefix /tmp --log-datestamp 20261003 --quiet >/dev/null
prefix_list=$(env -u HOME -u PREFIX "${bin}" list --prefix /tmp)
if [ "${prefix_list}" != "cpp-tn5250-20261003.log" ]; then
    echo "[ERROR] list --prefix did not print only the prefix file"
    printf '%s\n' "${prefix_list}"
    exit 1
fi
prefix_show=$(env -u HOME -u PREFIX "${bin}" show --prefix /tmp --log-datestamp 20261003)
prefix_file=$(cat "${prefix_new}")
if [ "${prefix_show}" != "${prefix_file}" ]; then
    echo "[ERROR] show --prefix did not print the prefix file"
    exit 1
fi

mkdir -p "${home_decoy}/.app/cpp-tn5250/log"
printf 'decoy\n' > "${home_decoy}/.app/cpp-tn5250/log/decoy.log"
both=$(env -u HOME -u PREFIX "${bin}" list --prefix /tmp --home "${home_decoy}")
if [ "${both}" != "cpp-tn5250-20261003.log" ]; then
    echo "[ERROR] list let --home win over --prefix"
    printf '%s\n' "${both}"
    exit 1
fi

mkdir -p "${prefix_decoy}/var/cpp-tn5250/log" "${prefix_decoy}/.app/cpp-tn5250/log"
printf 'x\n' > "${prefix_decoy}/var/cpp-tn5250/log/from-prefix.log"
printf 'x\n' > "${prefix_decoy}/.app/cpp-tn5250/log/from-prefix.log"
listed=$(env -u HOME PREFIX="${prefix_decoy}" "${bin}" list --home /tmp)
if [ "${listed}" != "${expected}" ]; then
    echo "[ERROR] list used PREFIX"
    printf '%s\n' "${listed}"
    exit 1
fi

if env -u HOME -u PREFIX "${bin}" show --home /tmp --log-datestamp 20261004 >"${work}/missing-file.txt" 2>&1; then
    echo "[ERROR] show accepted a missing log file"
    exit 1
fi
grep -F 'cannot read log file' "${work}/missing-file.txt" >/dev/null

help_out=$(env -u HOME -u PREFIX "${bin}" help)
printf '%s\n' "${help_out}" | grep -F ' list ' >/dev/null
printf '%s\n' "${help_out}" | grep -F ' show ' >/dev/null

if [ ! -f "${home_old}" ] || [ ! -f "${home_new}" ]; then
    echo "[ERROR] home log files missing after list and show"
    exit 1
fi

rm -rf /tmp/.app/cpp-tn5250
mkdir -p /tmp/.app/cpp-tn5250
printf 'x\n' > /tmp/.app/cpp-tn5250/log
if env -u HOME -u PREFIX "${bin}" list --home /tmp >"${work}/notdir.txt" 2>&1; then
    echo "[ERROR] list treated a non-directory as an empty log directory"
    exit 1
fi
grep -F 'cannot read log directory' "${work}/notdir.txt" >/dev/null

echo "----- list --home /tmp -----"
printf '%s\n' "${list_out}"
echo "----- show --home /tmp --log-datestamp 20261003 -----"
printf '%s\n' "${show_out}"
echo "PASS log verbs"

rm -rf /tmp/.app/cpp-tn5250
rm -rf /tmp/var/cpp-tn5250
rm -rf "${home_decoy}" "${prefix_decoy}"
rmdir /tmp/.app 2>/dev/null || true
rmdir /tmp/var 2>/dev/null || true
rm -rf "${work}"
