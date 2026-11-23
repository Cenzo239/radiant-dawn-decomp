#!/bin/sh
# Installs the fe10 game-data guard as pre-commit and pre-push hook of this clone.
#
# The checker and allow list are copied into <git-common-dir>/fe10-guard/, so the hooks work
# on every branch and in every worktree, also on branches that do not have tools/guard yet.
# Re-run after changing tools/guard/ to update the installed copy. An existing foreign hook is
# kept as <hook>.local and still runs first.
set -eu
cd "$(dirname "$0")/../.."
common=$(cd "$(git rev-parse --git-common-dir)" && pwd)
hooks=$(git rev-parse --git-path hooks)
case "$hooks" in /*) ;; *) hooks="$PWD/$hooks" ;; esac
dest="$common/fe10-guard"
mkdir -p "$dest" "$hooks"
cp tools/guard/check_game_data.py tools/guard/allow.txt "$dest/"

for hook in pre-commit pre-push; do
    f="$hooks/$hook"
    if [ -f "$f" ] && ! grep -q "fe10-guard" "$f"; then
        mv "$f" "$f.local"
        echo "kept existing $hook hook as $hook.local"
    fi
    cat > "$f" <<HOOK
#!/bin/sh
# fe10-guard: refuses game data (installed by tools/guard/install.sh)
hookdir=\$(cd "\$(dirname "\$0")" && pwd)
if [ -x "\$hookdir/$hook.local" ]; then
    if [ "$hook" = pre-push ]; then
        input=\$(cat)
        printf '%s\n' "\$input" | "\$hookdir/$hook.local" "\$@" || exit \$?
        printf '%s\n' "\$input" | exec python3 "\$(git rev-parse --git-common-dir)/fe10-guard/check_game_data.py" $hook "\$@"
    fi
    "\$hookdir/$hook.local" "\$@" || exit \$?
fi
exec python3 "\$(git rev-parse --git-common-dir)/fe10-guard/check_game_data.py" $hook "\$@"
HOOK
    chmod +x "$f"
done
echo "hooks installed in $hooks"
python3 "$dest/check_game_data.py" --index
