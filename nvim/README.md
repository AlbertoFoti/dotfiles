# Neovim configuration

A Tokyo Night themed Neovim setup inspired by ThePrimeagen's workflow, using
modern Neovim 0.11 LSP APIs and `lazy.nvim`.

The printable shortcut reference is available as
[`NEOVIM_KEYMAP_GUIDE.pdf`](NEOVIM_KEYMAP_GUIDE.pdf). Regenerate it after
changing mappings with `python3 generate_keymap_guide.py` (requires Pycairo).

## Prerequisites

- Neovim 0.11.3 or newer
- Git, `curl`, `unzip`, `tar`, and a C/C++ compiler
- `ripgrep` for Telescope live grep
- `fd` for faster file finding (optional)
- `make` for Telescope's native sorter (optional)
- A Nerd Font for icons (optional, but recommended)
- Node.js/npm for the TypeScript, web, and MATLAB language servers
- A Rust toolchain with `rustfmt` for Rust formatting
- MATLAB R2021b or newer for MATLAB language features

Plugins, language servers, and most formatters install automatically on the
first launch. Use `:Lazy` for plugins, `:Mason` for developer tools, and
`:checkhealth` if something does not attach correctly.

For MATLAB, expose the installation directory before starting Neovim:

```bash
export MATLAB_ROOT=/usr/local/MATLAB/R2025b
```

Change that path to match the installed MATLAB release.

## Language support

| Stack | Language servers | Formatter |
| --- | --- | --- |
| React, Vite, JavaScript, TypeScript | `vtsls`, ESLint, Tailwind CSS, Emmet | Prettierd |
| C and C++ | Clangd | clang-format |
| MATLAB | MathWorks MATLAB language server | MATLAB LSP |
| Python | BasedPyright and Ruff | isort and Black |
| Rust | rust-analyzer with Clippy | rustfmt |
| Lua | lua-language-server | StyLua |
| HTML, CSS, JSON, YAML, Bash, Markdown | Dedicated Mason-managed servers | Prettierd/LSP |

Vite does not need a separate language server: its React/TypeScript source is
handled by `vtsls`, ESLint, Tailwind CSS, and Emmet.

## Keymaps

The leader key is `Space`. Press it and pause to open the WhichKey guide.

| Key | Action |
| --- | --- |
| `<leader>pf` | Find project files |
| `<C-p>` | Find Git files |
| `<leader>fg` | Live grep |
| `<leader>fb` | Find open buffers |
| `<leader>e` or `-` | Open Oil file explorer |
| `<leader>ha` | Add current file to Harpoon |
| `<C-e>` | Open the Harpoon menu |
| `<leader>h1` … `<leader>h4` | Jump to a Harpoon file |
| `<leader>gs` | Open Fugitive Git status |
| `<leader>uu` | Toggle Undotree |
| `<leader>tz` | Toggle Zen mode |
| `<leader>cf` | Format the buffer or selection |
| `<leader>uf` | Toggle automatic formatting |
| `gd`, `gr`, `gI`, `gy` | LSP definition, references, implementation, type |
| `<leader>cr` | LSP rename |
| `<leader>ca` | LSP code action |
| `[d`, `]d` | Previous/next diagnostic |
| `<leader>xx` | Workspace diagnostics |

Automatic formatting is enabled by default. `:FormatToggle` toggles it
globally, and `:FormatToggle!` toggles it for the current buffer only.
