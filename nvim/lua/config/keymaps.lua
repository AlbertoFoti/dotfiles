local map = vim.keymap.set

map("n", "<Esc>", "<cmd>nohlsearch<CR>", { desc = "Clear search highlight" })
map("n", "Q", "<nop>")

map("n", "J", "mzJ`z", { desc = "Join line without moving cursor" })
map("n", "<C-d>", "<C-d>zz", { desc = "Half-page down and center" })
map("n", "<C-u>", "<C-u>zz", { desc = "Half-page up and center" })
map("n", "n", "nzzzv", { desc = "Next result and center" })
map("n", "N", "Nzzzv", { desc = "Previous result and center" })

map("v", "J", ":m '>+1<CR>gv=gv", { desc = "Move selection down" })
map("v", "K", ":m '<-2<CR>gv=gv", { desc = "Move selection up" })
map("x", "<leader>p", [=["_dP]=], { desc = "Paste without replacing register" })

map({ "n", "v" }, "<leader>y", [=["+y]=], { desc = "Yank to system clipboard" })
map("n", "<leader>Y", [=["+Y]=], { desc = "Yank line to system clipboard" })
map({ "n", "v" }, "<leader>d", [=["_d]=], { desc = "Delete without replacing register" })

map("n", "<C-h>", "<C-w><C-h>", { desc = "Focus left window" })
map("n", "<C-j>", "<C-w><C-j>", { desc = "Focus lower window" })
map("n", "<C-k>", "<C-w><C-k>", { desc = "Focus upper window" })
map("n", "<C-l>", "<C-w><C-l>", { desc = "Focus right window" })

map("n", "<M-j>", "<cmd>cnext<CR>zz", { desc = "Next quickfix item" })
map("n", "<M-k>", "<cmd>cprev<CR>zz", { desc = "Previous quickfix item" })
map("n", "<leader>k", "<cmd>lnext<CR>zz", { desc = "Next location item" })
map("n", "<leader>j", "<cmd>lprev<CR>zz", { desc = "Previous location item" })

map("n", "<leader>s", [[:%s/\<<C-r><C-w>\>/<C-r><C-w>/gI<Left><Left><Left>]], {
  desc = "Replace word under cursor",
})
