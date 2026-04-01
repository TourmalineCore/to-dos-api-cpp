#!/usr/bin/env bash
set -euo pipefail

ODB_DEB_URL="https://www.codesynthesis.com/download/odb/2.5.0/ubuntu/ubuntu22.04/x86_64/odb_2.5.0-0~ubuntu22.04_amd64.deb"
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MODELS_DIR="$ROOT_DIR/src/core"
APPLICATION_DIR="$ROOT_DIR/src/application"
ODB_OUT_DIR="$APPLICATION_DIR/odb-gen"

# ── Resolve Conan include paths ───────────────────────────────
echo "[0/3] Resolving Conan include paths..."
ODB_INCLUDE="$(conan cache path libodb/2.5.0)/../s/src"
PGSQL_INCLUDE="$(conan cache path libodb-pgsql/2.5.0)/../s/src"
echo "  libodb    → $ODB_INCLUDE"
echo "  libodb-pg → $PGSQL_INCLUDE"

# ── Install ───────────────────────────────────────────────────
echo "[1/3] Installing ODB..."
tmp=$(mktemp -d)
curl -fsSL -o "$tmp/odb.deb" "$ODB_DEB_URL"
sudo apt-get install -y "$tmp/odb.deb"
rm -rf "$tmp"

# ── Generate ──────────────────────────────────────────────────
echo "[2/3] Generating ODB files..."
mkdir -p "$ODB_OUT_DIR"

find "$MODELS_DIR" -type f \( -name "*.hxx" -o -name "*.h" \) \
    -not -path "$ODB_OUT_DIR/*" -print0 | \
while IFS= read -r -d '' header; do
    echo "  → $(basename "$header")"
    odb --std c++20 -d pgsql --generate-query \
        -o "$ODB_OUT_DIR" \
        -I "$ODB_INCLUDE" \
        -I "$PGSQL_INCLUDE" \
        -I "$ROOT_DIR" \
        "$header"
done

# ── Cleanup ───────────────────────────────────────────────────
echo "[3/3] Removing ODB..."
sudo apt-get remove -y odb

echo "Done. Output: $ODB_OUT_DIR"
