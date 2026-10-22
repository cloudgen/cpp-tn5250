#!/bin/sh
# Warning: do not call mktemp or mkstemp.
# Do not read, expand, assign, or delete the home environment variable.
# This check builds one binary with g++ and does not run ./build.sh.
# It uses the literal directory /tmp only.
set -eu

cd "$(dirname "$0")/.."

work=/tmp/cpp-tn5250-terminal-work
rm -rf "${work}"
mkdir "${work}"

sh tests/compile-app.sh "${work}"
bin="${work}/cpp-tn5250"

env -u HOME -u PREFIX "${bin}" key-check >"${work}/key-check.txt"
grep -F 'PASS key-check' "${work}/key-check.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" key-plan >"${work}/key-plan.txt"
grep -F 'Attention' "${work}/key-plan.txt" >/dev/null
grep -F 'Field Exit' "${work}/key-plan.txt" >/dev/null
grep -F 'F24' "${work}/key-plan.txt" >/dev/null
grep -F 'Enter' "${work}/key-plan.txt" >/dev/null
grep -F 'Roll' "${work}/key-plan.txt" >/dev/null
grep -F 'Ctrl+Q' "${work}/key-plan.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" attribute-plan >"${work}/attribute-plan.txt"
grep -F '0 green' "${work}/attribute-plan.txt" >/dev/null
grep -F '7 nondisplay' "${work}/attribute-plan.txt" >/dev/null
grep -F '16 turquoise' "${work}/attribute-plan.txt" >/dev/null
grep -F '31 nondisplay' "${work}/attribute-plan.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" screen-plan >"${work}/screen-plan.txt"
grep -F 'IBM-3179-2 24 80' "${work}/screen-plan.txt" >/dev/null
grep -F 'IBM-3477-FC 27 132' "${work}/screen-plan.txt" >/dev/null

if env -u HOME -u PREFIX "${bin}" session-plan >"${work}/no-host.txt" 2>&1; then
    echo "[ERROR] session-plan ran without a host"
    exit 1
fi
grep -F 'session-plan requires a host' "${work}/no-host.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" --quiet session-plan map=37 ssl:ibmi.example >"${work}/session-plan.txt"
grep -F 'host=ssl:ibmi.example' "${work}/session-plan.txt" >/dev/null
grep -F 'argv=map=37 ssl:ibmi.example' "${work}/session-plan.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" form-plan map=37 +ruler +underscores +ssl_verify_server \
    env.TERM=IBM-3477-FC env.DEVNAME=DSP01 trace=trace-file \
    ssl_ca_file=ca.pem ssl_cert_file=cert.pem ssl_pem_pass=phrase ssl_check_exp=60 \
    env.CODEPAGE=37 ssl:ibmi.example \
    >"${work}/form-plan.txt"
grep -F 'map=37' "${work}/form-plan.txt" >/dev/null
grep -F '+ruler' "${work}/form-plan.txt" >/dev/null
grep -F '+underscores' "${work}/form-plan.txt" >/dev/null
grep -F '+ssl_verify_server' "${work}/form-plan.txt" >/dev/null
grep -F 'env.TERM=IBM-3477-FC' "${work}/form-plan.txt" >/dev/null
grep -F 'env.DEVNAME=DSP01' "${work}/form-plan.txt" >/dev/null
grep -F 'trace=trace-file' "${work}/form-plan.txt" >/dev/null
grep -F 'ssl_ca_file=ca.pem' "${work}/form-plan.txt" >/dev/null
grep -F 'ssl_cert_file=cert.pem' "${work}/form-plan.txt" >/dev/null
grep -F 'ssl_pem_pass=phrase' "${work}/form-plan.txt" >/dev/null
grep -F 'ssl_check_exp=60' "${work}/form-plan.txt" >/dev/null
grep -F 'env.CODEPAGE=37' "${work}/form-plan.txt" >/dev/null
grep -F 'ssl:ibmi.example' "${work}/form-plan.txt" >/dev/null

if env -u HOME -u PREFIX "${bin}" key-plan screen-plan >"${work}/two.txt" 2>&1; then
    echo "[ERROR] two plan commands were accepted"
    exit 1
fi
grep -F 'one plan command' "${work}/two.txt" >/dev/null

env -u HOME -u PREFIX "${bin}" --version >"${work}/version.txt"
grep -F 'cpp-tn5250 1.0.0' "${work}/version.txt" >/dev/null
grep -F 'tn5250 0.19.0' "${work}/version.txt" >/dev/null

help_out=$(env -u HOME -u PREFIX "${bin}" help)
printf '%s\n' "${help_out}" | grep -F -- '--verbose' >/dev/null
printf '%s\n' "${help_out}" | grep -F -- '--log-datestamp' >/dev/null
printf '%s\n' "${help_out}" | grep -F '/var/' >/dev/null
printf '%s\n' "${help_out}" | grep -F '/.app/' >/dev/null
printf '%s\n' "${help_out}" | grep -F 'not a WebKit view' >/dev/null
printf '%s\n' "${help_out}" | grep -F 'ssl_ca_file=' >/dev/null

echo "PASS tn5250 terminal"
rm -rf "${work}"
