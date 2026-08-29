local opt = vim.opt

opt.number = true
opt.relativenumber = true
opt.cursorline = true
opt.signcolumn = "yes"
opt.colorcolumn = "100"

opt.tabstop = 2
opt.softtabstop = 2
opt.shiftwidth = 2
opt.expandtab = true
opt.smartindent = true

opt.wrap = false
opt.scrolloff = 8
opt.sidescrolloff = 8
opt.splitbelow = true
opt.splitright = true

opt.ignorecase = true
opt.smartcase = true
opt.incsearch = true
opt.hlsearch = false

opt.termguicolors = true
opt.pumblend = 8
opt.winblend = 8
opt.completeopt = { "menu", "menuone", "noselect" }
opt.pumheight = 10
opt.laststatus = 3
opt.showmode = false

opt.swapfile = false
opt.backup = false
opt.undofile = true
opt.undolevels = 10000

opt.updatetime = 250
opt.timeoutlen = 300
opt.confirm = true
opt.mouse = "a"

opt.list = true
opt.listchars = {
  tab = "» ",
  trail = "·",
  nbsp = "␣",
}

opt.foldlevel = 99
opt.foldlevelstart = 99
opt.foldenable = true

vim.schedule(function()
  vim.opt.clipboard = "unnamedplus"
end)
