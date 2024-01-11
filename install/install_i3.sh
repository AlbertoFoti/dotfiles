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

aurhelper="paru"

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

create_default_directories(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    mkdir -p "$HOME"/.config
    mkdir -p "$HOME"/.scripts
    mkdir -p "$HOME"/.themes
    mkdir -p "$HOME"/.icons

    mkdir -p "$HOME"/Pictures/wallpapers
    mkdir -p "$HOME"/Pictures/screenshots
    mkdir -p ~/Apps
    mkdir -p ~/vault/data
    mkdir -p ~/dev
}

install_pkgs(){
    echo -e "${green}[*] Installing packages with pacman for $wm configuration.${no_color}"

    # File manager 
    sudo pacman -S --noconfirm --needed ranger nemo

    # System Monitor
    sudo pacman -S --noconfirm --needed rsync btop neofetch
    sudo pacman -S --noconfirm --needed duf dust ncdu baobab tldr psensor acpi vnstat
    sudo pacman -S --noconfirm --needed light inxi hwinfo
    "$aurhelper" -S --noconfirm --needed mission-center pacgraph

    # Terminal and shell
    sudo pacman -S --noconfirm --needed kitty
    sudo pacman -S --noconfirm --needed zsh zsh-syntax-highlighting   
    sudo pacman -S --noconfirm --needed fish
    curl -sS https://starship.rs/install.sh | sh

    # Web Browser
    #"$aurhelper" -S --noconfirm --needed google-chrome

    # Audio
    sudo pacman -S --noconfirm --needed pipewire wireplumber pipewire-pulse alsa-utils helvum pavucontrol playerctl
    sudo pacman -S --noconfirm --needed mpc mpd ncmpcpp

    # PDF and image visualizer, screenshot, unzip
    sudo pacman -S --noconfirm --needed unzip zathura zathura-pdf-mupdf
    sudo pacman -S --noconfirm --needed feh slop 
    "$aurhelper" -S --noconfirm --needed gimp

    #Security
    sudo pacman -S --noconfirm --needed ufw

    # Appearance
    sudo pacman -S --noconfirm --needed lxappearance
    sudo pacman -S --noconfirm --needed qt5ct qt6ct
    sudo pacman -S --noconfirm --needed gtk-engine-murrine
    sudo pacman -S --noconfirm --needed adobe-source-code-pro-fonts

    # Others
    sudo pacman -s --noconfirm --needed gnome-calculator
    sudo pacman -S --noconfirm --needed tldr bat fd rg ripgrep
    #sudo pacman -S --noconfirm --needed python-pywal
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

        sudo chmod +x ./config/waybar/custom/spotify/controls.sh
        sudo chmod +x ./config/waybar/custom/spotify/metadata.sh
        sudo chmod +x ./config/waybar/custom/spotify/monitor.sh
        sudo chmod +x ./config/waybar/custom/spotify/play-pause.sh
        sudo chmod +x ./config/waybar/custom/spotify/quit.sh
        sudo chmod +x ./config/wlogout/launch.sh
        sudo chmod +x ./config/wlogout/actions
        sudo chmod +x ./config/wlogout/layout
    elif [[ $wm == "wayland-sway" ]]
    then
        
    else
	    echo -e ">>> [ERROR] NO WM CONFIG PROVIDED"
    fi

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

copy_configs(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    #cp -r ./config/* "$config_directory"

    rm -rf ~/.config/gtk-2.0
    ln -s ~/dotfiles/config/gtk-2.0 ~/.config/gtk-2.0
    rm -rf ~/.config/gtk-3.0
    ln -s ~/dotfiles/config/gtk-3.0 ~/.config/gtk-3.0
    rm -rf ~/.config/gtk-4.0
    ln -s ~/dotfiles/config/gtk-4.0 ~/.config/gtk-4.0

    rm -rf ~/.config/kitty
    ln -s ~/dotfiles/config/kitty ~/.config/kitty
    rm -rf ~/.config/fish
    ln -s ~/dotfiles/config/fish ~/.config/fish
    rm ~/.config/starship.toml
    ln -s ~/dotfiles/config/starship.toml ~/.config/starship.toml 

    #rm -rf ~/.config/nemo
    #ln -s ~/dotfiles/config/nemo ~/.config/nemo
    rm -rf ~/.config/ranger
    ln -s ~/dotfiles/config/ranger ~/.config/ranger
    rm -rf ~/.config/neofetch
    ln -s ~/dotfiles/config/neofetch ~/.config/neofetch
    rm -rf ~/.config/btop
    ln -s ~/dotfiles/config/btop ~/.config/btop
    rm -rf ~/.config/cava
    ln -s ~/dotfiles/config/cava ~/.config/cava

    rm -rf ~/.config/wlogout
    ln -s ~/dotfiles/config/wlogout ~/.config/wlogout

    if [[ $wm == "xorg-i3" ]]
    then
	echo -e "xorg-i3 configs"
    	rm -rf ~/.config/i3/
        ln -s ~/dotfiles/config/i3 ~/.config/i3
        rm -rf ~/.config/picom
        ln -s ~/dotfiles/config/picom ~/.config/picom
        rm -rf ~/.config/polybar
        ln -s ~/dotfiles/config/polybar ~/.config/polybar
        rm -rf ~/.config/rofi
        ln -s ~/dotfiles/config/rofi ~/.config/rofi
    elif [[ $wm == "wayland-hyprland" ]]
    then
	    echo -e "wayland-hyprland configs"
        rm -rf ~/.config/hypr
        ln -s ~/dotfiles/config/hypr ~/.config/hypr
        rm -rf ~/.config/waybar
        ln -s ~/dotfiles/config/waybar ~/.config/waybar
        rm -rf ~/.config/wofi
        ln -s ~/dotfiles/config/wofi ~/.config/wofi
    elif [[ $wm == "" ]]
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
    rm -rf "$HOME"/Pictures/wallpapers
    cp -r ./wallpapers "$HOME"/Pictures/wallpapers
    echo -e "${green}[*] Copying zsh configs.${no_color}"
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    sudo cp "$HOME"/dotfiles/keyitdev.zsh-theme "$HOME"/.oh-my-zsh/custom/themes
    cp "$HOME"/dotfiles/.zshrc "$HOME"
    git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

    echo -e "${green}[*] Installing emoji fonts with $aurhelper.${no_color}"
    "$aurhelper" -S --noconfirm --needed noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra
    sudo cp -f ./local.conf /etc/fonts
    fc-cache -fv

    # system Services
    sudo systemctl enable paccache.timer
    sudo systemctl enable ufw.service
}

install_additional_pkgs(){
    echo -e "${green}[*] Installing additional packages with $aurhelper.${no_color}"

    sudo pacman -S --noconfirm --needed bitwarden steam
    "$aurhelper" -S --noconfirm --needed mpv
    sudo pacman -S --noconfirm --needed gvfs gvfs-gphoto2 android-file-transfer

    # Flatpak
    sudo pacman -S flatpak
    flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
    sudo usermod -aG flatpak $USER
    flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

    #Flatpack applications
    flatpak install --user flathub org.gnome.FileRoller
    flatpak install --user flathub com.visualstudio.code                  #"$aurhelper" -S --noconfirm --needed visual-studio-code-bin
    #flatpak install --user flathub com.jetbrains.IntelliJ-IDEA-Community  #sudo pacman -S --noconfirm --needed intellij-idea-community-edition
    flatpak install --user flathub org.mozilla.Thunderbird 
    flatpak install --user flathub org.mozilla.firefox
    flatpak install --user flathub md.obsidian.Obsidian                   #sudo pacman -S --noconfirm --needed obsidian
    flatpak install --user flathub org.telegram.desktop                   #sudo pacman -S --noconfirm --needed telegram-desktop
    flatpak install --user flathub org.libreoffice.LibreOffice            #sudo pacman -S --noconfirm --needed libreoffice-fresh
    flatpak install --user flathub com.interversehq.qView                 #sudo pacman -S --noconfirm --needed qview
    flatpak install --user flathub org.kde.kdenlive                       #sudo pacman -S --noconfirm --needed kdenlive
    flatpak install --user flathub com.obsproject.Studio
    flatpak install --user flathub org.audacityteam.Audacity              #sudo pacman -S --noconfirm --needed audacity
    flatpak install --user flathub com.spotify.Client

    # Others
    #sudo pacman -S --noconfirm --needed virtualbox
    #"$aurhelper" -S --noconfirm --needed docker-desktop
}

install_vsc(){
    echo -e "${green}[*] Installing vsc extensions.${no_color}"
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
    sudo cp -r ./Tokyo-Night-GTK-Theme/themes/*  ~/.themes/
    sudo cp -r ./Tokyo-Night-GTK-Theme/icons/*  ~/.icons/
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



cmd=(dialog --clear --title "WM Configuration" --menu "Select the target Window Manager" 10 50 16)
options=(1 "xorg-i3" 2 "wayland-hyprland")
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)
case $choices in
    1) wm="xorg-i3";;
    2) wm="wayland-hyprland";;
    3) wm="wayland-sway";;
esac


cmd=(dialog --clear --separate-output --checklist "Select (with space) what script should do.\\nChecked options are required for proper installation, do not uncheck them if you do not know what you are doing." 26 86 16)
options=(1 "System update" on
         2 "Install aur helper" on
         3 "Create default directories" on
         4 "Install basic packages" on
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
        3) create_default_directories;;
        4) install_pkgs;;
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
