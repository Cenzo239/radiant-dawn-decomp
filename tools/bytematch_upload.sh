#!/bin/sh
# Upload the objdiff progress report to ByteMatch (https://bytematch.dev).
#
#   BYTEMATCH_TOKEN=bm_... sh tools/bytematch_upload.sh [--build]
#
# The token is the project's upload token from the ByteMatch manage page. Keep it out of the
# repository: pass it in the environment or store it in ~/.config/bytematch/radiant-dawn-decomp.token.
# The report is uploaded for the current commit (HEAD), which must be pushed to GitHub so that
# ByteMatch can show the source. --build runs `ninja build/RFEE01/report.json` first; the build
# needs your own extracted disc in orig/RFEE01 and never sends any game file anywhere.
set -eu
cd "$(dirname "$0")/.."
VERSION=RFEE01
REPO=${BYTEMATCH_REPO:-Cenzo239/radiant-dawn-decomp}
REPORT=build/$VERSION/report.json

if [ "${1:-}" = "--build" ]; then
    ninja "$REPORT"
fi
[ -f "$REPORT" ] || { echo "no $REPORT; run with --build or 'ninja $REPORT'" >&2; exit 1; }

TOKEN=${BYTEMATCH_TOKEN:-}
TOKEN_FILE="$HOME/.config/bytematch/radiant-dawn-decomp.token"
if [ -z "$TOKEN" ] && [ -f "$TOKEN_FILE" ]; then
    TOKEN=$(cat "$TOKEN_FILE")
fi
[ -n "$TOKEN" ] || { echo "set BYTEMATCH_TOKEN or write the token to $TOKEN_FILE" >&2; exit 1; }

if [ -n "$(git status --porcelain --untracked-files=no)" ]; then
    echo "warning: uncommitted changes; the report may not match HEAD" >&2
fi
SHA=$(git rev-parse HEAD)
git branch -r --contains "$SHA" | grep -q . || echo "warning: $SHA is not on any pushed branch yet" >&2
MSG=$(git log -1 --format=%s | python3 -c 'import sys,urllib.parse;print(urllib.parse.quote(sys.stdin.read().strip()))')
TS=$(git log -1 --format=%cI)
TSQ=$(printf %s "$TS" | python3 -c 'import sys,urllib.parse;print(urllib.parse.quote(sys.stdin.read()))')

gzip -c "$REPORT" | curl --fail-with-body -sS -X POST \
    -H "Authorization: Bearer $TOKEN" \
    -H "Content-Encoding: gzip" \
    --data-binary @- \
    "https://bytematch.dev/api/v1/projects/$REPO/reports?version=$VERSION&commit=$SHA&commit_message=$MSG&commit_timestamp=$TSQ"
echo
