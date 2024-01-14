TZSH="/usr/share/zsh"
ZSH="/usr/share/oh-my-zsh"
export ZSH="$HOME/.oh-my-zsh"
ZSH_THEME="keyitdev"
plugins=(git z zsh-autosuggestions)
QT_QPA_PLATFORMTHEME="qt5ct"
export QT_QPA_PLATFORMTHEME="qt5ct"

ZSH_CACHE_DIR="$HOME/.cache/oh-my-zsh"
if [[ ! -d "$ZSH_CACHE_DIR" ]]; then
  mkdir "$ZSH_CACHE_DIR"
fi

source "$ZSH"/oh-my-zsh.sh
source "$TZSH"/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh

# git
alias g="git"
alias gad="git add --all"
alias gcm="git commit -m"
alias gcms="git commit -S -m"
alias gph="git push"
alias gpl="git pull"
alias gcl="git clone"
alias gin="git init"

alias gst="git status"
alias glg="git log -n 5"
alias glgr="git reflog"
alias gdf="git diff"

alias gbr="git branch"
alias gsw="git switch"
alias gch="git checkout"
alias gra="git remote add origin git@github.com:"
alias grs="git remote set-url origin git@github.com:"

# other
alias nv="nvim"
alias la="ls -alF"
alias h="history|grep"
alias c="clear" # I know about ctrl l etc.
alias logout="killall -KILL -u $USER"
alias files="nemo"
alias files.="nemo ."
alias help="cat ~/.zshrc | less"

# cd
alias ..="cd .."
alias ....="cd ../.."
alias ......="cd ../../.."
alias ........="cd ../../../.."

alias colemak='sudo bash ~/Apps/BigBagKbdTrixXKB/setkb.sh 4ca us us; rm -f ~/.config/i3/config; ln -s ~/dotfiles/config/i3/config_colemak ~/.config/i3/config; i3-msg restart'
alias it='sudo bash ~/Apps/BigBagKbdTrixXKB/setkb.sh 4n it; rm -f ~/.config/i3/config; ln -s ~/dotfiles/configs/i3/config_qwerty ~/.config/i3/config; i3-msg restart'
alias ir='cowsay -f dragon "you are an idiot! you are using a colemak layout!" | lolcat'
alias dotfiles='cd ~/dotfiles; ls'
alias vault='cd ~/vault; ls'

cursor_mode() {
    # See https://ttssh2.osdn.jp/manual/4/en/usage/tips/vim.html for cursor shapes
    cursor_block='\e[2 q'
    cursor_beam='\e[6 q'

    function zle-keymap-select {
        if [[ ${KEYMAP} == vicmd ]] ||
            [[ $1 = 'block' ]]; then
            echo -ne $cursor_block
        elif [[ ${KEYMAP} == main ]] ||
            [[ ${KEYMAP} == viins ]] ||
            [[ ${KEYMAP} = '' ]] ||
            [[ $1 = 'beam' ]]; then
            echo -ne $cursor_beam
        fi
    }

    zle-line-init() {
        echo -ne $cursor_beam
    }

    zle -N zle-keymap-select
    zle -N zle-line-init
}

cursor_mode
