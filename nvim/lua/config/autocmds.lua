local group = vim.api.nvim_create_augroup("DotfilesAutocmds", { clear = true })

vim.api.nvim_create_autocmd("TextYankPost", {
  group = group,
  desc = "Highlight yanked text",
  callback = function()
    vim.highlight.on_yank({ timeout = 200 })
  end,
})

vim.api.nvim_create_autocmd("FileType", {
  group = group,
  desc = "Use four-space indentation for non-web languages",
  pattern = { "c", "cpp", "matlab", "python", "rust" },
  callback = function()
    vim.opt_local.tabstop = 4
    vim.opt_local.softtabstop = 4
    vim.opt_local.shiftwidth = 4
  end,
})

vim.api.nvim_create_autocmd("FileType", {
  group = group,
  desc = "Close utility windows with q",
  pattern = { "help", "lspinfo", "man", "qf", "checkhealth" },
  callback = function(event)
    vim.bo[event.buf].buflisted = false
    vim.keymap.set("n", "q", "<cmd>close<CR>", { buffer = event.buf, silent = true })
  end,
})

vim.api.nvim_create_autocmd("VimEnter", {
  group = group,
  once = true,
  callback = function()
    vim.notify("Tokyo Night dotfiles loaded — happy coding!", vim.log.levels.INFO)
  end,
})
