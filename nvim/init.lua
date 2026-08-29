if vim.fn.has("nvim-0.11.3") == 0 then
  error("This configuration requires Neovim 0.11.3 or newer")
end

-- This configuration does not use Neovim remote plugins for these runtimes.
vim.g.loaded_node_provider = 0
vim.g.loaded_perl_provider = 0
vim.g.loaded_ruby_provider = 0

vim.g.mapleader = " "
vim.g.maplocalleader = " "

require("config.options")
require("config.keymaps")
require("config.autocmds")
require("config.lazy")
