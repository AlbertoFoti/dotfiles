#!/usr/bin/env python3
"""Generate the Tokyo Night Neovim keymap guide as a vector PDF."""

from pathlib import Path

import cairo


PAGE_WIDTH = 595.28
PAGE_HEIGHT = 841.89
MARGIN = 34
GUTTER = 14
CONTENT_TOP = 116
CONTENT_BOTTOM = 802
CARD_GAP = 10
CARD_PADDING = 10
KEY_WIDTH = 91

OUTPUT = Path(__file__).with_name("NEOVIM_KEYMAP_GUIDE.pdf")

COLORS = {
    "background": "#1a1b26",
    "surface": "#24283b",
    "surface_alt": "#1f2335",
    "border": "#3b4261",
    "foreground": "#c0caf5",
    "muted": "#7982a9",
    "blue": "#7aa2f7",
    "cyan": "#7dcfff",
    "green": "#9ece6a",
    "orange": "#ff9e64",
    "purple": "#bb9af7",
    "red": "#f7768e",
}


PAGES = [
    {
        "eyebrow": "01 / NAVIGATION + FILES",
        "title": "Neovim keyboard field guide",
        "subtitle": "Move quickly, find anything, and keep important files close.",
        "accent": "blue",
        "columns": [
            [
                (
                    "Core movement",
                    "blue",
                    [
                        ("h  j  k  l", "Left, down, up, right"),
                        ("w / b / e", "Next, previous, end of word"),
                        ("0 / $", "Start / end of line"),
                        ("gg / G", "Top / bottom of file"),
                        ("{ / }", "Previous / next paragraph"),
                        ("%", "Matching bracket or block"),
                        ("f{c} / t{c}", "Find / move until character"),
                        ("Ctrl-d / Ctrl-u", "Half-page down / up, centered"),
                        ("n / N", "Next / previous search, centered"),
                        ("* / #", "Search word forward / backward"),
                        ("m{a-z} / '{m}", "Set / jump to a mark"),
                        ("Ctrl-o / Ctrl-i", "Older / newer jump location"),
                    ],
                ),
                (
                    "Windows + buffers",
                    "cyan",
                    [
                        ("Ctrl-h/j/k/l", "Focus the adjacent window"),
                        (":split / :vsplit", "Create horizontal / vertical split"),
                        ("Ctrl-w =", "Equalize split sizes"),
                        ("Space fb", "Pick an open buffer"),
                        ("Ctrl-^", "Return to previous buffer"),
                        (":bd", "Close current buffer"),
                        (":w / :q / :wq", "Save / quit / save and quit"),
                    ],
                ),
                (
                    "Harpoon",
                    "purple",
                    [
                        ("Space ha", "Add the current file"),
                        ("Ctrl-e", "Open the Harpoon menu"),
                        ("Space h1...h4", "Jump to marked file 1–4"),
                        ("Space hp / hn", "Previous / next marked file"),
                    ],
                ),
            ],
            [
                (
                    "Telescope + search",
                    "cyan",
                    [
                        ("Space pf", "Find project files, including hidden"),
                        ("Ctrl-p", "Find Git files and untracked files"),
                        ("Space fg", "Live grep through the project"),
                        ("Space fw", "Find the word under the cursor"),
                        ("Space fb", "Find open buffers"),
                        ("Space fr", "Open a recent file"),
                        ("Space fh", "Search Neovim help tags"),
                        ("Space fk", "Search all active keymaps"),
                        ("Space /", "Fuzzy-search current buffer"),
                    ],
                ),
                (
                    "Oil file explorer",
                    "green",
                    [
                        ("Space e / -", "Open explorer / parent directory"),
                        ("Enter", "Open selected file or directory"),
                        ("- / _", "Parent directory / working directory"),
                        ("Ctrl-s", "Open selection in vertical split"),
                        ("Ctrl-h", "Open selection in horizontal split"),
                        ("Ctrl-t", "Open selection in a new tab"),
                        ("Ctrl-p", "Preview selected file"),
                        ("g.", "Toggle hidden files"),
                        ("gs", "Change sorting"),
                        ("g?", "Show Oil's complete keymap"),
                        ("i / a / o / dd", "Edit entries like ordinary text"),
                        (":w", "Apply creates, renames, and deletes"),
                    ],
                ),
                (
                    "Discoverability",
                    "orange",
                    [
                        ("Space + pause", "Show available WhichKey groups"),
                        (":map {key}", "Inspect a mapping"),
                        (":help {topic}", "Open built-in documentation"),
                    ],
                ),
            ],
        ],
    },
    {
        "eyebrow": "02 / CODE WORKFLOW",
        "title": "Understand, edit, format, ship",
        "subtitle": "LSP intelligence and Primeagen-style tools for daily development.",
        "accent": "purple",
        "columns": [
            [
                (
                    "LSP navigation + actions",
                    "purple",
                    [
                        ("gd / gD", "Definition / declaration"),
                        ("gr", "References in Telescope"),
                        ("gI", "Implementations in Telescope"),
                        ("gy", "Type definitions in Telescope"),
                        ("K", "Hover documentation"),
                        ("Ctrl-s (insert)", "Function signature help"),
                        ("Space cr", "Rename symbol"),
                        ("Space ca", "Available code actions"),
                        ("Space cd", "Diagnostics for current line"),
                        ("Space ws", "Search workspace symbols"),
                        ("Space th", "Toggle LSP inlay hints"),
                        (":LspInfo", "Inspect attached language servers"),
                    ],
                ),
                (
                    "Completion + snippets",
                    "cyan",
                    [
                        ("Ctrl-n / Ctrl-p", "Next / previous completion"),
                        ("Ctrl-Space", "Open completion menu"),
                        ("Ctrl-y", "Accept selected completion"),
                        ("Enter", "Accept only an explicit selection"),
                        ("Tab / Shift-Tab", "Completion or snippet jump"),
                        ("Ctrl-b / Ctrl-f", "Scroll documentation"),
                        ("Ctrl-e", "Close completion menu"),
                    ],
                ),
                (
                    "Formatting",
                    "green",
                    [
                        ("Space cf", "Format buffer or visual selection"),
                        ("Space uf", "Toggle format-on-save globally"),
                        (":FormatToggle!", "Toggle for current buffer only"),
                        (":ConformInfo", "Inspect formatter availability"),
                    ],
                ),
            ],
            [
                (
                    "Diagnostics",
                    "red",
                    [
                        ("[d / ]d", "Previous / next diagnostic"),
                        ("Space xx", "Workspace diagnostics"),
                        ("Space xX", "Current-buffer diagnostics"),
                        ("Space xq", "Quickfix list in Trouble"),
                        ("Space cs", "Document symbols in Trouble"),
                        ("Alt-j / Alt-k", "Next / previous quickfix item"),
                    ],
                ),
                (
                    "Git workflow",
                    "orange",
                    [
                        ("Space gs", "Open Fugitive status"),
                        ("]h / [h", "Next / previous changed hunk"),
                        ("Space gp", "Preview changed hunk"),
                        ("Space gr", "Reset changed hunk"),
                        ("Space gb", "Toggle line blame"),
                        ("g? (Fugitive)", "Show status-buffer operations"),
                        (":Git commit", "Commit in a Neovim buffer"),
                        (":Git blame", "Open interactive blame view"),
                        (":Gdiffsplit", "Compare worktree with index"),
                    ],
                ),
                (
                    "Editing + registers",
                    "blue",
                    [
                        ("J / K (visual)", "Move selected lines down / up"),
                        ("J (normal)", "Join lines without cursor drift"),
                        ("Space p (visual)", "Paste without replacing register"),
                        ("Space y / Y", "Yank to system clipboard"),
                        ("Space d", "Delete without replacing register"),
                        ("u / Ctrl-r", "Undo / redo"),
                        (".", "Repeat last change"),
                        ("ciw / diw", "Change / delete inner word"),
                        ("Space s", "Replace word throughout buffer"),
                    ],
                ),
                (
                    "Utility tools",
                    "green",
                    [
                        ("Space uu", "Toggle Undotree"),
                        ("Space tz", "Toggle distraction-free Zen mode"),
                        (":Lazy / :Mason", "Manage plugins / developer tools"),
                        (":checkhealth", "Run Neovim diagnostics"),
                    ],
                ),
            ],
        ],
    },
]


def color(name, alpha=1.0):
    value = COLORS.get(name, name).lstrip("#")
    return tuple(int(value[index : index + 2], 16) / 255 for index in (0, 2, 4)) + (alpha,)


def set_color(context, name, alpha=1.0):
    context.set_source_rgba(*color(name, alpha))


def rounded_rectangle(context, x, y, width, height, radius):
    context.new_sub_path()
    context.arc(x + width - radius, y + radius, radius, -1.5708, 0)
    context.arc(x + width - radius, y + height - radius, radius, 0, 1.5708)
    context.arc(x + radius, y + height - radius, radius, 1.5708, 3.14159)
    context.arc(x + radius, y + radius, radius, 3.14159, 4.71239)
    context.close_path()


def font(context, size, family="DejaVu Sans", bold=False):
    weight = cairo.FONT_WEIGHT_BOLD if bold else cairo.FONT_WEIGHT_NORMAL
    context.select_font_face(family, cairo.FONT_SLANT_NORMAL, weight)
    context.set_font_size(size)


def draw_text(context, x, y, value, size, tone="foreground", family="DejaVu Sans", bold=False):
    font(context, size, family, bold)
    set_color(context, tone)
    context.move_to(x, y)
    context.show_text(value)


def wrap_text(context, value, width, size=8.4):
    font(context, size)
    words = value.split()
    lines = []
    current = ""
    for word in words:
        candidate = word if not current else f"{current} {word}"
        if context.text_extents(candidate).width <= width:
            current = candidate
        else:
            if current:
                lines.append(current)
            current = word
    if current:
        lines.append(current)
    return lines or [""]


def card_height(context, rows, width):
    action_width = width - (2 * CARD_PADDING) - KEY_WIDTH - 8
    height = CARD_PADDING + 20
    for _, action in rows:
        height += max(15, len(wrap_text(context, action, action_width)) * 10.5 + 4)
    return height + CARD_PADDING - 2


def draw_card(context, x, y, width, title, accent, rows):
    height = card_height(context, rows, width)
    rounded_rectangle(context, x, y, width, height, 8)
    set_color(context, "surface")
    context.fill_preserve()
    set_color(context, "border", 0.8)
    context.set_line_width(0.7)
    context.stroke()

    rounded_rectangle(context, x + CARD_PADDING, y + 9, 4, 15, 2)
    set_color(context, accent)
    context.fill()
    draw_text(context, x + CARD_PADDING + 11, y + 21, title, 11.3, bold=True)

    cursor_y = y + 34
    action_width = width - (2 * CARD_PADDING) - KEY_WIDTH - 8
    for index, (key, action) in enumerate(rows):
        lines = wrap_text(context, action, action_width)
        row_height = max(15, len(lines) * 10.5 + 4)

        rounded_rectangle(context, x + CARD_PADDING, cursor_y, KEY_WIDTH, row_height - 3, 4)
        set_color(context, "surface_alt")
        context.fill()
        draw_text(
            context,
            x + CARD_PADDING + 6,
            cursor_y + 10.5,
            key,
            7.3,
            accent,
            family="DejaVu Sans Mono",
            bold=True,
        )

        for line_index, line in enumerate(lines):
            draw_text(
                context,
                x + CARD_PADDING + KEY_WIDTH + 8,
                cursor_y + 10 + (line_index * 10.5),
                line,
                8.3,
            )

        cursor_y += row_height
        if index < len(rows) - 1:
            set_color(context, "border", 0.35)
            context.set_line_width(0.45)
            context.move_to(x + CARD_PADDING + KEY_WIDTH + 8, cursor_y - 2)
            context.line_to(x + width - CARD_PADDING, cursor_y - 2)
            context.stroke()

    return height


def draw_page(context, page, page_number):
    set_color(context, "background")
    context.paint()

    set_color(context, page["accent"])
    context.rectangle(0, 0, 7, PAGE_HEIGHT)
    context.fill()

    draw_text(context, MARGIN, 32, page["eyebrow"], 8.2, page["accent"], bold=True)
    draw_text(context, MARGIN, 63, page["title"], 23, bold=True)
    draw_text(context, MARGIN, 83, page["subtitle"], 9.3, "muted")

    badge_width = 104
    rounded_rectangle(context, PAGE_WIDTH - MARGIN - badge_width, 42, badge_width, 27, 13.5)
    set_color(context, "surface")
    context.fill_preserve()
    set_color(context, page["accent"], 0.8)
    context.set_line_width(0.7)
    context.stroke()
    draw_text(
        context,
        PAGE_WIDTH - MARGIN - badge_width + 13,
        59.5,
        "LEADER  =  SPACE",
        7.2,
        page["accent"],
        family="DejaVu Sans Mono",
        bold=True,
    )

    column_width = (PAGE_WIDTH - (2 * MARGIN) - GUTTER) / 2
    for column_index, sections in enumerate(page["columns"]):
        x = MARGIN + column_index * (column_width + GUTTER)
        y = CONTENT_TOP
        for title, accent, rows in sections:
            height = draw_card(context, x, y, column_width, title, accent, rows)
            y += height + CARD_GAP
        if y > CONTENT_BOTTOM:
            raise RuntimeError(f"Page {page_number}, column {column_index + 1} overflows by {y - CONTENT_BOTTOM:.1f}pt")

    set_color(context, "border", 0.55)
    context.set_line_width(0.6)
    context.move_to(MARGIN, 816)
    context.line_to(PAGE_WIDTH - MARGIN, 816)
    context.stroke()
    draw_text(context, MARGIN, 831, "SPACE + PAUSE opens WhichKey  •  g? opens contextual tool help", 7.2, "muted")
    draw_text(context, PAGE_WIDTH - MARGIN - 31, 831, f"{page_number} / {len(PAGES)}", 7.2, page["accent"], bold=True)


def main():
    surface = cairo.PDFSurface(str(OUTPUT), PAGE_WIDTH, PAGE_HEIGHT)
    if hasattr(surface, "set_metadata"):
        surface.set_metadata(cairo.PDF_METADATA_TITLE, "Neovim Keyboard Field Guide")
        surface.set_metadata(cairo.PDF_METADATA_AUTHOR, "dotfiles")
        surface.set_metadata(cairo.PDF_METADATA_SUBJECT, "Neovim keymaps and tool usage")

    context = cairo.Context(surface)
    for page_number, page in enumerate(PAGES, start=1):
        draw_page(context, page, page_number)
        context.show_page()
    surface.finish()
    print(f"Generated {OUTPUT}")


if __name__ == "__main__":
    main()
