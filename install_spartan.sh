#!/bin/bash

# Config created by Alberto Foti
# Copyright (C) 2023 XXmorpheusX

config_directory="$HOME/.config"
fonts_directory="/usr/share/fonts"
scripts_directory="/usr/local/bin"
gtk_theme_directory="/usr/share/themes"

green='\033[0;32m'
no_color='\033[0m'
date=$(date +%s)

sudo pacman --noconfirm --needed -Sy dialog

system_update(){
    echo -e "${green}[*] Doing a system update, cause stuff may break if it's not the latest version...${no_color}"
    sudo pacman -Sy --noconfirm archlinux-keyring
    sudo pacman --noconfirm -Syu
    sudo pacman -S --noconfirm --needed base-devel wget git curl
}

install_aur_helper(){ 
    if ! command -v "$aurhelper" &> /dev/null
    then
        echo -e "${green}[*] It seems that you don't have $aurhelper installed, I'll install that for you before continuing.${no_color}"
        git clone https://aur.archlinux.org/"$aurhelper".git $HOME/.srcs/"$aurhelper"
        (cd $HOME/.srcs/"$aurhelper"/ && makepkg -si)
    else
        echo -e "${green}[*] It seems that you already have $aurhelper installed, skipping.${no_color}"
        "$aurhelper" yay -Syu --noconfirm
    fi
}

install_pkgs(){
    echo -e "${green}[*] Installing packages with pacman for $wm configuration.${no_color}"

    # File manager 
    sudo pacman -S --noconfirm --needed ranger
    sudo pacman -S --noconfirm --needed nemo
    #sudo pacman -S --noconfirm --needed thunar
    #others: dolphin, krusader, nautilus 

    # System Monitor
    sudo pacman -S --noconfirm --needed btop 
    sudo pacman -S --noconfirm --needed neofetch 
    sudo pacman -S --noconfirm --needed duf dust ncdu tldr psensor acpi vnstat
    sudo pacman -S --noconfirm --needed light
    sudo pacman -S --noconfirm --needed inxi
    "$aurhelper" -S --noconfirm --needed mission-center
    "$aurhelper" -S --noconfirm --needed pacgraph

    # Terminal and shell
    sudo pacman -S --noconfirm --needed kitty
    #sudo pacman -S --noconfirm --needed alacritty
    sudo pacman -S --noconfirm --needed zsh zsh-syntax-highlighting   
    sudo pacman -S --noconfirm --needed fish
    curl -sS https://starship.rs/install.sh | sh

    # Web Browser
    "$aurhelper" -S --noconfirm --needed google-chrome

    # Audio
    sudo pacman -S --noconfirm --needed pipewire wireplumber pipewire-pulse alsa-utils helvum pavucontrol playerctl
    sudo pacman -S --noconfirm --needed mpc mpd ncmpcpp

    # PDF and image visualizer, screenshot, unzip
    sudo pacman -S --noconfirm --needed unzip zathura zathura-pdf-mupdf
    sudo pacman -S --noconfirm --needed feh slop 
    "$aurhelper" -S --noconfirm --needed gimp
    "$aurhelper" -S --noconfirm --needed 7-zip

    # Appearance
    sudo pacman -S --noconfirm --needed lxappearance

    # Others
    sudo pacman -S --noconfirm --needed tldr
    sudo pacman -S --noconfirm --needed python-pywal
    sudo pacman -S --noconfirm --needed yad
    "$aurhelper" -S --noconfirm --needed ntp

    # Dependencies
    sudo pacman -S --noconfirm --needed python-pip npm nodejs python-pynvim pacman-contrib
    "$aurhelper" -S --noconfirm --needed adwaita-qt6-git qt5-plugins
    "$aurhelper" -S --noconfirm --needed ntfs-3g

    # Meme packages
    sudo pacman -S --noconfirm --needed cowsay lolcat cmatrix sl


    if [[ $wm == "xorg-i3" ]]
    then
	echo -e "xorg-i3 configuration" 
        echo -e "xorg-i3 configuration"

        # i3 install
        sudo pacman -S --noconfirm --needed i3-wm
        sudo pacman -S --noconfirm --needed i3lock

        # System Bar
    	sudo pacman -S --noconfirm --needed polybar 
        # Search Menu
        sudo pacman -S --noconfirm --needed rofi 
        # Screenshot
        sudo pacman -S --noconfirm --needed scrot xclip xorg-xrandr
        # Others
        sudo pacman -S --noconfirm --needed picom
    	sudo pacman -S --noconfirm --needed papirus-icon-theme
        sudo pacman -S --noconfirm --needed xorg-xev
        sudo pacman -S --noconfirm --needed dunst
        "$aurhelper" -S --noconfirm --needed i3lock-color i3-resurrect ffcast
    
        sudo chmod +x ./config/polybar/launch.sh
        sudo chmod +x ./config/polybar/uptime.sh
        sudo chmod +x ./config/i3/lock
        sudo chmod +x ./config/i3/rofi-powermenu
    elif [[ $wm == "wayland-hyprland" ]]
    then
        echo -e "wayland-hyprland configuration"

        # hyprland install
        sudo pacman -S --noconfirm --needed hyprland xdg-desktop-portal-hyprland
        sudo pacman -S --noconfirm --needed qt6-wayland qt5-wayland

        # System Bar
    	"$aurhelper" -S --noconfirm --needed waybar-hyprland-cava-git
        # Search Menu
        sudo pacman -S --noconfirm --needed wofi 
        # Screenshots
        sudo pacman -S --noconfirm --needed grim slurp
        # Wallpaper
        sudo pacman -S --noconfirm --needed hyprpaper
        # Others
        sudo pacman -S --noconfirm --needed polkit-kde-agent
        sudo pacman -S --noconfirm --needed gettext jq libnotify
        sudo pacman -S --noconfirm --needed wev
        sudo pacman -S --noconfirm --needed swayidle
        "$aurhelper" -S --noconfirm --needed swaync swaylock-effects-git
        "$aurhelper" -S --noconfirm --needed waybar-module-pacman-updates-git
        "$aurhelper" -S --noconfirm --needed waybar-updates
        "$aurhelper" -S --noconfirm --needed cava
        "$aurhelper" -S --noconfirm --needed wlogout

        #sudo pacman -S --noconfirm --needed firefox
        #git clone https://github.com/PROxZIMA/Sweet-Pop.git && cd Sweet-Pop
        #sudo mkdir -p /usr/bin/defaults/pref/
        #./programs/install.sh

        sudo chmod +x ./config/waybar/custom/spotify/controls.sh
        sudo chmod +x ./config/waybar/custom/spotify/metadata.sh
        sudo chmod +x ./config/waybar/custom/spotify/monitor.sh
        sudo chmod +x ./config/waybar/custom/spotify/play-pause.sh
        sudo chmod +x ./config/waybar/custom/spotify/quit.sh
        sudo chmod +x ./config/wlogout/launch.sh
        sudo chmod +x ./config/wlogout/actions
        sudo chmod +x ./config/wlogout/layout
    else
	    echo -e ">>> [ERROR] NO WM CONFIG PROVIDED"
    fi
}

create_default_directories(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    mkdir -p "$HOME"/.config
    sudo mkdir -p  /usr/local/bin
    sudo mkdir -p  /usr/share/themes

    rm -rf "$HOME"/Pictures/wallpapers
    mkdir -p "$HOME"/Pictures/wallpapers

    mkdir -p ~/Apps
    mkdir -p ~/vault/data
    mkdir -p ~/dev
}

copy_configs(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    cp -r ./config/* "$config_directory"

    if [[ $wm == "xorg-i3" ]]
    then
	echo -e "xorg-i3 configs"
    	rm ~/.config/i3/config
    	ln -s ~/.config/i3/config_colemak ~/.config/i3/config
    elif [[ $wm == "wayland-hyprland" ]]
    then
	    echo -e "wayland-hyprland configs"
    else
	    echo -e ">>> [ERROR] NO WM CONFIG PROVIDED"
    fi

    echo -e "${green}[*] Copying scripts to $scripts_directory.${no_color}"
    sudo cp -r ./scripts/* "$scripts_directory"

    mkdir -p ~/.scripts
    sudo chmod +x ./.scripts/lock
    sudo chmod +x ./scripts/wofi-power
    sudo chmod +x ./scripts/clean
    cp -r ./.scripts/* ~/.scripts

    echo -e "${green}[*] Copying fonts to $fonts_directory.${no_color}"
    sudo cp -r ./fonts/* "$fonts_directory"
    fc-cache -fv

    echo -e "${green}[*] Copying wallpapers to "$HOME"/Pictures/wallpapers.${no_color}"
    cp -r ./wallpapers/* "$HOME"/Pictures/wallpapers
    echo -e "${green}[*] Copying zsh configs.${no_color}"
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    sudo cp "$HOME"/dotfiles/keyitdev.zsh-theme "$HOME"/.oh-my-zsh/custom/themes
    cp "$HOME"/dotfiles/.zshrc "$HOME"
    git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

    echo -e "${green}[*] Installing emoji fonts with $aurhelper.${no_color}"
    "$aurhelper" -S --noconfirm --needed noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra
    sudo cp -f ./local.conf /etc/fonts
    fc-cache -fv
}

install_additional_pkgs(){
    echo -e "${green}[*] Installing additional packages with $aurhelper.${no_color}"

    sudo pacman -S --noconfirm --needed telegram-desktop bitwarden obsidian intellij-idea-community-edition
    sudo pacman -S --noconfirm --needed audacity kdenlive
    sudo pacman -S --noconfirm --needed libreoffice-fresh
    sudo pacman -S --noconfirm --needed steam
    #sudo pacman -S --noconfirm --needed vlc
    "$aurhelper" -S --noconfirm --needed mpv

    # Others
    #sudo pacman -S --noconfirm --needed virtualbox
    #"$aurhelper" -S --noconfirm --needed docker-desktop

    if [[ $wm == "xorg-i3" ]]
    then
	    echo -e "xorg-i3 configs"
    	cd ~/Apps && git clone https://github.com/DreymaR/BigBagKbdTrixXKB.git
        cd ~/Apps/BigBagKbdTrixXKB/ && ./install-dreymar-xmod.sh && cd ~/
        sudo chmod +x ~/Apps/BigBagKbdTrixXKB/setkb.sh
    elif [[ $wm == "wayland-hyprland" ]]
    then
	    echo -e "wayland-hyprland configs"
        "$aurhelper" -S --noconfirm --needed spotify-wayland
    else
	    echo -e ">>> [ERROR] NO WM CONFIG PROVIDED"
    fi
}

install_vsc(){
    echo -e "${green}[*] Installing vsc extensions.${no_color}"
    "$aurhelper" -S --noconfirm --needed visual-studio-code-bin
    #code --install-extension zhuangtongfa.Material-theme
    #echo -e "${green}[*] Copying vsc configs.${no_color}"
    #cp ./vsc/settings.json "$HOME"/.config/Code\ -\ OSS/User
}

install_neovim_config(){
    sudo pacman -S --noconfirm --needed neovim
    echo -e "${green}[*] Copying neovim config.${no_color}"

    #rm -rf ./nvim
    #rm -rf ./config/nvim
    #rm -rf ~/.config/nvim
    #git clone https://github.com/nvim-lua/kickstart.nvim.git nvim
    #rm -rf nvim/.git
    #cp -r nvim config/nvim
    #mv nvim ~/.config/nvim

    mkdir -p ~/.npm-global
    npm config set prefix '~/.npm-global'
    rm ~/.profile
    cp ./.profile ~/.profile
    source ~/.profile
    bash <(curl -s https://raw.githubusercontent.com/lunarvim/lunarvim/master/utils/installer/install.sh)
}

install_gtk_theme(){
    echo -e "${green}[*] Installing gtk theme.${no_color}"
    git clone --depth 1 https://github.com/Fausto-Korpsvart/Tokyo-Night-GTK-Theme
    echo -e "${green}[*] Copying gtk theme to /usr/share/themes.${no_color}"
    sudo cp -r ./Tokyo-Night-GTK-Theme/themes/*  /usr/share/themes/
    sudo cp -r ./Tokyo-Night-GTK-Theme/icons/*  /usr/share/icons/
    mkdir -p "$HOME"/.config/gtk-4.0
    sudo cp -r ./Tokyo-Night-GTK-Theme/themes/Tokyonight-Dark-BL-LB/gtk-4.0/* "$HOME"/.config/gtk-4.0
}   

install_sddm(){
    echo -e "${green}[*] Installing sddm theme.${no_color}"
    "$aurhelper" -S --noconfirm --needed qt5-graphicaleffects qt5-quickcontrols2 qt5-svg sddm
    sudo systemctl enable sddm.service
    sudo git clone https://github.com/Keyitdev/sddm-astronaut-theme.git /usr/share/sddm/themes/sddm-astronaut-theme
    sudo cp /usr/share/sddm/themes/sddm-astronaut-theme/Fonts/* /usr/share/fonts/
    echo "[Theme]
    Current=sddm-astronaut-theme" | sudo tee /etc/sddm.conf
}

finishing(){
    echo -e "${green}[*] Chmoding light.${no_color}"
    sudo chmod +s /usr/bin/light
    #echo -e "${green}[*] Setting Zsh as default shell.${no_color}"
    #chsh -s /bin/zsh
    #sudo chsh -s /bin/zsh
    echo -e "${green}[*] Setting Fish as default shell.${no_color}"
    chsh -s /bin/fish
    sudo chsh -s /bin/fish
    echo -e "${green}[*] Updating nvim extensions.${no_color}"
}

cmd=(dialog --clear --title "Aur helper" --menu "Firstly, select the aur helper you want to install (or have already installed)." 10 50 16)
options=(1 "yay" 2 "paru")
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

case $choices in
    1) aurhelper="yay";;
    2) aurhelper="paru";;
esac

cmd=(dialog --clear --title "WM Configuration" --menu "Select the target Window Manager" 10 50 16)
options=(1 "xorg-i3" 2 "wayland-hyprland")
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

case $choices in
    1) wm="xorg-i3";;
    2) wm="wayland-hyprland";;
esac


cmd=(dialog --clear --separate-output --checklist "Select (with space) what script should do.\\nChecked options are required for proper installation, do not uncheck them if you do not know what you are doing." 26 86 16)
options=(1 "System update" on
         2 "Install aur helper" on
         3 "Install basic packages" on
         4 "Create default directories" on
         5 "Create backup of existing configs (to prevent overwritting)" off
         6 "Copy configs, scripts and fonts (..., gtk theme, wallpaper, zsh configs)" on
         7 "Install additional packages" off
         8 "Install vsc theme" on
	     9 "Install neovim config" off
         10 "Install gtk theme" on
         11 "Install sddm theme" on
         12 "Make Light executable, set zsh as default shell, update nvim extensions." on)
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

clear

for choice in $choices
do
    case $choice in
        1) system_update;;
        2) install_aur_helper;;
        3) install_pkgs;;
        4) create_default_directories;;
        5) create_backup;;
        6) copy_configs;;
        7) install_additional_pkgs;;
        8) install_vsc;;
	    9) install_neovim_config;;
        10) install_gtk_theme;;
        11) install_sddm;;
        12) finishing;;
    esac
done
