# Config created by Keyitdev https://www.github.com/keyitdev/dotfiles
# Copyright (C) 2022 Keyitdev

local return_code="%(?..%{$fg[red]%}%? ↵%{$reset_color%})"
local user_symbol='%(!.#.$)'
local current_dir="%B%{$fg[blue]%}%~ %{$reset_color%}"
local date="[%D{%H:%M:%S}]"
local vcs_branch='$(git_prompt_info)$(hg_prompt_info)'

# Get Git branch name (if applicable)
local git_branch='$(git rev-parse --abbrev-ref HEAD 2>/dev/null)'

# Check if inside a Git repository
if [[ -n "${git_branch}" ]]; then
    local git_info="%{$fg[yellow]%}(${git_branch})%{$reset_color%} "
else
    local git_info=""
fi

ZSH_THEME_RVM_PROMPT_OPTIONS="i v g"

#PROMPT="${current_dir}${rvm_ruby}${vcs_branch}${venv_prompt} %B${user_symbol}%b "
PROMPT="${current_dir}${git_info}%B${user_symbol}%b "
RPROMPT="%B${return_code}%b"

ZSH_THEME_GIT_PROMPT_PREFIX="%{$fg[green]%}‹"
ZSH_THEME_GIT_PROMPT_SUFFIX="› %{$reset_color%}"
ZSH_THEME_GIT_PROMPT_DIRTY="%{$fg[red]%} |!|%{$fg[green]%}"
ZSH_THEME_GIT_PROMPT_CLEAN="%{$fg[green]%}"