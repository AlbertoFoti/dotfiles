#!/bin/bash

# Config created by Alberto Foti
# Copyright (C) 2024 XXmorpheusX

config_directory="$HOME/.config"
fonts_directory="$HOME/.fonts"
scripts_directory="$HOME/.scripts"
themes_directory="$HOME/.themes"
icons_directory="$HOME/.icons"

green='\033[0;32m'
no_color='\033[0m'
date=$(date +%s)

aurhelper="paru"

sudo pacman -S --noconfirm --needed dialog

system_update(){
    echo -e "${green}[*](0)[SYSTEM UPDATE]${no_color}"
    sudo pacman --noconfirm -Sy archlinux-keyring
    sudo pacman --noconfirm -Syu
    sudo pacman -S --noconfirm --needed base-devel wget git curl
}

install_aur_helper(){
    echo -e "${green}[*](1)[AUR HELPER INSTALL]${no_color}"
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
    echo -e "${green}[*] Copying configs.${no_color}"
    mkdir -p $config_directory
    mkdir -p $scripts_directory
    mkdir -p $themes_directory
    mkdir -p $icons_directory
    mkdir -p $fonts_directory

    mkdir -p "$HOME"/Pictures/wallpapers
    mkdir -p "$HOME"/Pictures/screenshots
    mkdir -p "$HOME"/Desktop
    mkdir -p "$HOME"/Downloads
    mkdir -p ~/Apps
    mkdir -p ~/vault/media
    mkdir -p ~/vault/backups
    mkdir -p ~/dev
}

install_display_manager(){
    echo -e "${green}[*] Installing display manager.${no_color}"

     if [[ $dm == "sddm" ]]
    then
        echo -e "${green}[*] sddm display manager.${no_color}"
        sudo pacman -S --noconfirm --needed sddm
        "$aurhelper" -S --noconfirm --needed qt5-graphicaleffects qt5-quickcontrols2 qt5-svg sddm
        sudo systemctl enable sddm.service
        sudo git clone https://github.com/Keyitdev/sddm-astronaut-theme.git /usr/share/sddm/themes/sddm-astronaut-theme
        sudo cp /usr/share/sddm/themes/sddm-astronaut-theme/Fonts/* $fonts_directory
        echo "[Theme]
        Current=sddm-astronaut-theme" | sudo tee /etc/sddm.conf
    elif [[ $dm == "lightdm" ]]
    then
        echo -e "${green}[*] lightdm display manager.${no_color}"
        ### TODO
    else
	    echo -e ">>> [ERROR] NO WM CONFIG PROVIDED"
    fi
}

install_window_manager(){
    echo -e "${green}[*] Installing window manager.${no_color}"

    # hyprland install
    sudo pacman -S --noconfirm --needed hyprland xdg-desktop-portal-hyprland
    sudo pacman -S --noconfirm --needed qt6-wayland qt5-wayland

    # System Bar
    sudo pacman -S --noconfirm --needed waybar
    # Search Menu
    sudo pacman -S --noconfirm --needed wofi 
    # Screenshots
    sudo pacman -S --noconfirm --needed grim slurp
    # Wallpaper
    sudo pacman -S --noconfirm --needed hyprpaper
    # Others
    #sudo pacman -S --noconfirm --needed polkit-kde-agent
    sudo pacman -S --noconfirm --needed gettext jq libnotify
    sudo pacman -S --noconfirm --needed wev
    #sudo pacman -S --noconfirm --needed swayidle
    #"$aurhelper" -S --noconfirm --needed swaync swaylock-effects-git
    "$aurhelper" -S --noconfirm --needed waybar-module-pacman-updates-git
    "$aurhelper" -S --noconfirm --needed waybar-updates
    #"$aurhelper" -S --noconfirm --needed cava
    "$aurhelper" -S --noconfirm --needed wlogout

    sudo chmod +x ./config/waybar/custom/spotify/controls.sh
    sudo chmod +x ./config/waybar/custom/spotify/metadata.sh
    sudo chmod +x ./config/waybar/custom/spotify/monitor.sh
    sudo chmod +x ./config/waybar/custom/spotify/play-pause.sh
    sudo chmod +x ./config/waybar/custom/spotify/quit.sh
    sudo chmod +x ./config/wlogout/launch.sh
    sudo chmod +x ./config/wlogout/actions
    sudo chmod +x ./config/wlogout/layout
}

install_pkgs(){
    echo -e "${green}[*] Installing packages with pacman for $wm configuration.${no_color}"

    # File manager 
    sudo pacman -S --noconfirm --needed ranger nemo

    # System Monitor
    sudo pacman -S --noconfirm --needed rsync btop neofetch
    sudo pacman -S --noconfirm --needed ncdu baobab psensor acpi vnstat
    #sudo pacman -S --noconfirm --needed duf dust light
    sudo pacman -S --noconfirm --needed hwinfo
    "$aurhelper" -S --noconfirm --needed mission-center pacgraph

    # Terminal and shell
    sudo pacman -S --noconfirm --needed kitty zsh zsh-syntax-highlighting fish
    curl -sS https://starship.rs/install.sh | sh

    # Audio
    sudo pacman -S --noconfirm --needed pipewire wireplumber pipewire-pulse alsa-utils helvum pavucontrol playerctl
    #sudo pacman -S --noconfirm --needed mpc mpd ncmpcpp

    # PDF and image visualizer, screenshot, unzip
    sudo pacman -S --noconfirm --needed zathura zathura-pdf-mupdf
    sudo pacman -S --noconfirm --needed feh slop 

    #Security
    sudo pacman -S --noconfirm --needed ufw

    # Appearance
    sudo pacman -S --noconfirm --needed lxappearance
    sudo pacman -S --noconfirm --needed qt5ct qt6ct
    sudo pacman -S --noconfirm --needed gtk-engine-murrine
    sudo pacman -S --noconfirm --needed adobe-source-code-pro-fonts
    sudo pacman -S --noconfirm --needed papirus-icon-theme
    sudo pacman -S --noconfirm --needed kiconthemes5
    sudo pacman -S --noconfirm --needed otf-font-awesome

    # Others
    sudo pacman -S --noconfirm --needed tldr bat fd ripgrep yad
    "$aurhelper" -S --noconfirm --needed ntp

    # Dependencies
    sudo pacman -S --noconfirm --needed python-pip npm nodejs python-pynvim pacman-contrib
    "$aurhelper" -S --noconfirm --needed adwaita-qt6-git qt5-plugins

    # Meme packages
    sudo pacman -S --noconfirm --needed cowsay lolcat cmatrix sl
}

copy_configs(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    #cp -r ./config/* "$config_directory"

    cd ~/Apps && git clone https://github.com/DreymaR/BigBagKbdTrixXKB.git && cd ~/dotfiles
    cd ~/Apps/BigBagKbdTrixXKB/ && ./install-dreymar-xmod.sh && cd ~/dotfiles
    #sudo chmod +x ~/Apps/BigBagKbdTrixXKB/setkb.sh

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

    rm -rf ~/.config/nemo
    ln -s ~/dotfiles/config/nemo ~/.config/nemo
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


    echo -e "wayland-hyprland configs"
    rm -rf ~/.config/hypr
    ln -s ~/dotfiles/config/hypr ~/.config/hypr
    rm -rf ~/.config/waybar
    ln -s ~/dotfiles/config/waybar ~/.config/waybar
    rm -rf ~/.config/wofi
    ln -s ~/dotfiles/config/wofi ~/.config/wofi

    echo -e "${green}[*] Copying scripts to $scripts_directory.${no_color}"
    mkdir -p ~/.scripts
    sudo cp -r ./.scripts/* "$scripts_directory"

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

    echo -e "${green}[*] Setting Fish as default shell.${no_color}"
    chsh -s /bin/fish
    sudo chsh -s /bin/fish

    # system Services
    sudo systemctl enable paccache.timer
    sudo systemctl enable ufw.service
}

install_additional_pkgs(){
    echo -e "${green}[*] Installing additional packages with $aurhelper.${no_color}"

    sudo pacman -S --noconfirm --needed bitwarden steam
    sudo pacman -S --noconfirm --needed gvfs gvfs-gphoto2 android-file-transfer
    sudo pacman -s --noconfirm --needed gnome-calculator
    "$aurhelper" -S --noconfirm --needed mpv

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
    flatpak install --user flathub com.google.Chrome
    flatpak install --user flathub org.mozilla.firefox
    flatpak install --user flathub md.obsidian.Obsidian                   #sudo pacman -S --noconfirm --needed obsidian
    flatpak install --user flathub org.telegram.desktop                   #sudo pacman -S --noconfirm --needed telegram-desktop
    flatpak install --user flathub org.libreoffice.LibreOffice            #sudo pacman -S --noconfirm --needed libreoffice-fresh
    flatpak install --user flathub com.interversehq.qView                 #sudo pacman -S --noconfirm --needed qview
    flatpak install --user flathub org.kde.kdenlive                       #sudo pacman -S --noconfirm --needed kdenlive
    flatpak install --user flathub org.gimp.GIMP
    flatpak install --user flathub com.obsproject.Studio
    flatpak install --user flathub org.audacityteam.Audacity              #sudo pacman -S --noconfirm --needed audacity
    
    flatpak install --user flathub com.spotify.Client
    flatpak install --user flathub com.discordapp.Discord
    flatpak install --user flathub com.valvesoftware.Steam
    flatpak install --user flathub com.jetbrains.IntelliJ-IDEA-Community
    flatpak install --user flathub org.octave.Octave
    flatpak install --user flathub tv.kodi.Kodi

    # Others
    #sudo pacman -S --noconfirm --needed virtualbox
    #"$aurhelper" -S --noconfirm --needed docker-desktop
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


## Login/Display Manager
cmd=(dialog --clear --title "DM Display manager" --menu "Select the target Display Manager" 10 50 16)
options=(1 "sddm" 2 "lightdm (TODO)")
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)
case $choices in
    1) dm="sddm";;
    2) dm="lightdm";;
esac

## WM Configuration
cmd=(dialog --clear --title "WM Configuration" --menu "Select the target Window Manager" 10 50 16)
options=(1 "wayland-hyprland" 2 "wayland-sway (TODO)")
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)
case $choices in
    1) wm="wayland-hyprland";;
    2) wm="wayland-sway";;
esac


cmd=(dialog --clear --separate-output --checklist "Select (with space) what script should do.\\nChecked options are required for proper installation, do not uncheck them if you do not know what you are doing." 26 86 16)
options=(
    1 "System update" on
    2 "Install aur helper" on
    3 "Create default directories" on
    4 "Install display manager" on
    5 "Install window manager" on
    6 "Install basic packages" on
    7 "Copy config" on 
    8 "Install additional packages" on
    9 "Install GTK theme" on
)
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

clear

for choice in $choices
do
    case $choice in
        1) system_update;;
        2) install_aur_helper;;
        3) create_default_directories;;
        4) install_display_manager;;
        5) install window_manager;;
        6) install_pkgs;;
        7) copy_configs;;
        8) install_additional_pkgs;;
        9) install_gtk_theme;;
    esac
done
