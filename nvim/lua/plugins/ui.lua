return {
  {
    "folke/tokyonight.nvim",
    lazy = false,
    priority = 1000,
    opts = {
      style = "moon",
      transparent = true,
      terminal_colors = true,
      dim_inactive = false,
      lualine_bold = true,
      styles = {
        comments = { italic = true },
        keywords = { italic = true },
        functions = { bold = true },
        sidebars = "transparent",
        floats = "transparent",
      },
      on_colors = function(colors)
        colors.bg = "#0b0e17"
        colors.bg_dark = "#080a12"
        colors.bg_highlight = "#252b49"
        colors.bg_popup = "#111525"
        colors.bg_statusline = "#101421"
        colors.bg_visual = "#334a7d"
        colors.black = "#080a12"
        colors.border = "#252b49"
        colors.fg = "#d5ddff"
        colors.fg_dark = "#a6b0d8"
        colors.fg_gutter = "#465176"
        colors.comment = "#7480b5"
        colors.blue = "#7aa7ff"
        colors.blue1 = "#65d1ff"
        colors.cyan = "#7df9ff"
        colors.green = "#b9f27c"
        colors.magenta = "#c6a0ff"
        colors.magenta2 = "#ff4fa3"
        colors.orange = "#ff9d76"
        colors.purple = "#f0a9ff"
        colors.red = "#ff6f91"
        colors.teal = "#54e1c1"
        colors.yellow = "#ffd76d"
        colors.border_highlight = colors.cyan
        colors.error = colors.red
        colors.warning = colors.yellow
        colors.info = colors.cyan
        colors.hint = colors.teal
      end,
      on_highlights = function(highlights, colors)
        highlights.ColorColumn = { bg = "#151a2c" }
        highlights.CursorLine = { bg = "#181e33" }
        highlights.CursorLineNr = { fg = colors.magenta, bold = true }
        highlights.FloatBorder = { fg = colors.blue1, bg = colors.none }
        highlights.LineNr = { fg = colors.fg_gutter }
        highlights.MatchParen = { fg = colors.cyan, bold = true, underline = true }
        highlights.NormalFloat = { fg = colors.fg, bg = colors.none }
        highlights.Pmenu = { fg = colors.fg, bg = colors.none }
        highlights.PmenuSel = { fg = colors.bg_dark, bg = colors.blue, bold = true }
        highlights.PmenuThumb = { bg = colors.magenta }
        highlights.Search = { fg = colors.bg_dark, bg = colors.orange, bold = true }
        highlights.IncSearch = { fg = colors.bg_dark, bg = colors.magenta2, bold = true }
        highlights.TelescopeBorder = { fg = colors.blue1, bg = colors.none }
        highlights.TelescopePromptBorder = { fg = colors.magenta, bg = colors.none }
        highlights.TelescopePromptPrefix = { fg = colors.magenta }
        highlights.TelescopeSelection = { fg = colors.fg, bg = colors.bg_highlight, bold = true }
        highlights.TelescopeSelectionCaret = { fg = colors.magenta, bg = colors.bg_highlight }
        highlights.TelescopeMatching = { fg = colors.cyan, bold = true }
        highlights.Visual = { bg = colors.bg_visual }
        highlights.WhichKeyBorder = { fg = colors.blue1, bg = colors.none }
        highlights.WinSeparator = { fg = colors.bg_highlight }
      end,
    },
    config = function(_, opts)
      require("tokyonight").setup(opts)
      vim.cmd.colorscheme("tokyonight-moon")
    end,
  },

  {
    "nvim-lualine/lualine.nvim",
    event = "VeryLazy",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    opts = function()
      local theme = require("lualine.themes.tokyonight-moon")

      for _, mode in pairs(theme) do
        if mode.c then
          mode.c.bg = "NONE"
        end
      end

      return {
        options = {
          theme = theme,
          globalstatus = true,
          component_separators = "",
          section_separators = { left = "", right = "" },
          refresh = { statusline = 500 },
        },
        sections = {
          lualine_a = { { "mode", icon = "" } },
          lualine_b = { { "branch", icon = "" }, "diff" },
          lualine_c = {
            {
              "filename",
              path = 1,
              symbols = { modified = " ●", readonly = " ", unnamed = " [No Name]" },
            },
          },
          lualine_x = {
            {
              "diagnostics",
              symbols = { error = "󰅚 ", warn = "󰀪 ", info = "󰋽 ", hint = "󰌶 " },
            },
          },
          lualine_y = { "filetype", "progress" },
          lualine_z = { "location" },
        },
        extensions = { "fugitive", "lazy", "mason", "oil", "trouble" },
      }
    end,
  },

  {
    "folke/which-key.nvim",
    event = "VeryLazy",
    opts = {
      preset = "modern",
      delay = 300,
      win = {
        border = "rounded",
        padding = { 1, 2 },
      },
      spec = {
        { "<leader>c", group = "[C]ode" },
        { "<leader>f", group = "[F]ind" },
        { "<leader>g", group = "[G]it" },
        { "<leader>h", group = "[H]arpoon" },
        { "<leader>t", group = "[T]oggle" },
        { "<leader>u", group = "[U]I/undo" },
        { "<leader>w", group = "[W]orkspace" },
        { "<leader>x", group = "Diagnostics" },
      },
    },
  },

  {
    "lewis6991/gitsigns.nvim",
    event = { "BufReadPre", "BufNewFile" },
    opts = function()
      return {
        current_line_blame = false,
        on_attach = function(bufnr)
          local gitsigns = require("gitsigns")
          local function map(mode, lhs, rhs, desc)
            vim.keymap.set(mode, lhs, rhs, { buffer = bufnr, desc = desc })
          end

          map("n", "]h", function()
            if vim.wo.diff then
              vim.cmd.normal({ "]c", bang = true })
            else
              gitsigns.nav_hunk("next")
            end
          end, "Next git hunk")
          map("n", "[h", function()
            if vim.wo.diff then
              vim.cmd.normal({ "[c", bang = true })
            else
              gitsigns.nav_hunk("prev")
            end
          end, "Previous git hunk")
          map("n", "<leader>gp", gitsigns.preview_hunk, "Preview hunk")
          map("n", "<leader>gr", gitsigns.reset_hunk, "Reset hunk")
          map("n", "<leader>gb", gitsigns.toggle_current_line_blame, "Toggle line blame")
        end,
      }
    end,
  },

  {
    "folke/trouble.nvim",
    cmd = { "Trouble" },
    dependencies = { "nvim-tree/nvim-web-devicons" },
    opts = {},
    keys = {
      { "<leader>xx", "<cmd>Trouble diagnostics toggle<CR>", desc = "Workspace diagnostics" },
      { "<leader>xX", "<cmd>Trouble diagnostics toggle filter.buf=0<CR>", desc = "Buffer diagnostics" },
      { "<leader>cs", "<cmd>Trouble symbols toggle focus=false<CR>", desc = "Document symbols" },
      { "<leader>xq", "<cmd>Trouble qflist toggle<CR>", desc = "Quickfix list" },
    },
  },

  {
    "j-hui/fidget.nvim",
    event = "LspAttach",
    opts = {
      notification = {
        window = { winblend = 8 },
      },
    },
  },
}
