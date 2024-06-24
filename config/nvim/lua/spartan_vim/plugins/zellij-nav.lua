return {
	"https://git.sr.ht/~swaits/zellij-nav.nvim",
	lazy = true,
	event = "VeryLazy",
	keys = {
		{ "<C-Left>", "<cmd>ZellijNavigateLeft<cr>", { silent = true, desc = "navigate left" } },
		{ "<C-Down>", "<cmd>ZellijNavigateDown<cr>", { silent = true, desc = "navigate down" } },
		{ "<C-Up>", "<cmd>ZellijNavigateUp<cr>", { silent = true, desc = "navigate up" } },
		{ "<C-Right>", "<cmd>ZellijNavigateRight<cr>", { silent = true, desc = "navigate right" } },
	},
	opts = {},
}
