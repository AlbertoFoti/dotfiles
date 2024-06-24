vim.cmd("let g:netrw_liststyle = 3")

local opt = vim.opt

-- tabs & indentation
opt.cmdheight = 2
opt.tabstop = 2
opt.shiftwidth = 2
opt.expandtab = true
opt.autoindent = true

opt.wrap = false

-- search settings
opt.ignorecase = true
opt.smartcase = true

opt.cursorline = true

-- turn on termguicolors
opt.termguicolors = true
opt.background = "dark"
opt.signcolumn = "yes"

-- backspace
opt.backspace = "indent,eol,start"

-- clipboard
opt.clipboard:append("unnamedplus")

-- split windows
opt.splitright = true
opt.splitbelow = true

-- lines
opt.number = true
opt.relativenumber = true

-- others
opt.completeopt = { "menuone", "noselect" }
opt.conceallevel = 0
opt.fileencoding = "utf-8"
opt.hlsearch = true
opt.mouse = "a"
opt.pumheight = 10
opt.showmode = false
opt.scrolloff = 12
opt.sidescrolloff = 8
opt.guifont = "monospace:h17"
opt.swapfile = false
opt.writebackup = false
opt.wrap = false
