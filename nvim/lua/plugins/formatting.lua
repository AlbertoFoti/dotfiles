return {
  {
    "stevearc/conform.nvim",
    event = { "BufWritePre", "BufNewFile" },
    cmd = "ConformInfo",
    keys = {
      {
        "<leader>cf",
        function()
          require("conform").format({ async = true, lsp_format = "fallback" })
        end,
        mode = { "n", "x" },
        desc = "Format buffer or selection",
      },
      { "<leader>uf", "<cmd>FormatToggle<CR>", desc = "Toggle auto-format" },
    },
    init = function()
      vim.api.nvim_create_user_command("FormatToggle", function(args)
        if args.bang then
          vim.b.disable_autoformat = not vim.b.disable_autoformat
          vim.notify("Buffer auto-format " .. (vim.b.disable_autoformat and "disabled" or "enabled"))
        else
          vim.g.disable_autoformat = not vim.g.disable_autoformat
          vim.notify("Global auto-format " .. (vim.g.disable_autoformat and "disabled" or "enabled"))
        end
      end, { bang = true, desc = "Toggle auto-format (use ! for current buffer)" })
    end,
    opts = {
      notify_on_error = false,
      default_format_opts = {
        lsp_format = "fallback",
      },
      formatters_by_ft = {
        lua = { "stylua" },
        javascript = { "prettierd", "prettier", stop_after_first = true },
        javascriptreact = { "prettierd", "prettier", stop_after_first = true },
        typescript = { "prettierd", "prettier", stop_after_first = true },
        typescriptreact = { "prettierd", "prettier", stop_after_first = true },
        html = { "prettierd", "prettier", stop_after_first = true },
        css = { "prettierd", "prettier", stop_after_first = true },
        scss = { "prettierd", "prettier", stop_after_first = true },
        json = { "prettierd", "prettier", stop_after_first = true },
        jsonc = { "prettierd", "prettier", stop_after_first = true },
        yaml = { "prettierd", "prettier", stop_after_first = true },
        markdown = { "prettierd", "prettier", stop_after_first = true },
        c = { "clang_format" },
        cpp = { "clang_format" },
        python = { "isort", "black" },
        rust = { "rustfmt", lsp_format = "fallback" },
        matlab = { lsp_format = "fallback" },
      },
      format_on_save = function(bufnr)
        if vim.g.disable_autoformat or vim.b[bufnr].disable_autoformat then
          return
        end
        return { timeout_ms = 1000, lsp_format = "fallback" }
      end,
    },
  },

  {
    "WhoIsSethDaniel/mason-tool-installer.nvim",
    dependencies = { "mason-org/mason.nvim" },
    opts = {
      ensure_installed = {
        "black",
        "clang-format",
        "isort",
        "prettierd",
        "stylua",
      },
      run_on_start = true,
      start_delay = 3000,
      debounce_hours = 24,
    },
  },

  {
    "windwp/nvim-autopairs",
    event = "InsertEnter",
    opts = { check_ts = true },
  },
}
