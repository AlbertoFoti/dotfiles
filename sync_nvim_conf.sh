#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
NVIM_SOURCE="${SCRIPT_DIR}/nvim"
NVIM_TARGET="${HOME}/.config/nvim"

if [[ ! -d "${NVIM_SOURCE}" ]]; then
  printf 'Error: Neovim configuration directory not found: %s\n' "${NVIM_SOURCE}" >&2
  exit 1
fi

mkdir -p -- "${HOME}/.config"
rm -rf -- "${NVIM_TARGET}"
ln -s -- "${NVIM_SOURCE}" "${NVIM_TARGET}"

printf 'Neovim configuration linked: %s -> %s\n' "${NVIM_TARGET}" "${NVIM_SOURCE}"
