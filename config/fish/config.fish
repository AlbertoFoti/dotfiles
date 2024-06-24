if status is-interactive
    # Commands to run in interactive sessions can go here
end

set -U fish_greeting ""

alias t="zellij --layout ~/.config/zellij/layout_file.kdl"
alias mat="cd ~/MATLAB/R2024a/bin/ && ./matlab"
alias nv="nvim ."

alias vault="cd ~/Vault"
alias ml="cd ~/Vault/my_life"
alias work="cd ~/Vault/my_life/Personal/A\ -\ Career/work"
alias data="cd ~/Data/"

alias gs="git status"
alias gp="git push"

starship init fish | source
