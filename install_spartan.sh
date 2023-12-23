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
    fi
}

install_pkgs(){
    echo -e "${green}[*] Installing packages with pacman.${no_color}"
    sudo pacman -S --noconfirm --needed neofetch picom alacritty btop polybar rofi zsh thunar zathura zathura-pdf-mupdf
    #sudo pacman -S --noconfirm --needed neovim
    #sudo pacman -S --noconfirm alsa-utils
    sudo pacman -S --noconfirm --needed papirus-icon-theme
    sudo pacman -S --noconfirm --needed inxi feh acpi pacman-contrib scrot mpc mpd ncmpcpp slop xclip ranger light

    sudo chmod +x ./config/polybar/launch.sh
    sudo chmod +x ./config/polybar/uptime.sh
    sudo chmod +x ./config/i3/set_background.sh
}

install_aur_pkgs(){
    echo -e "${green}[*] Installing packages with $aurhelper.${no_color}"
    "$aurhelper" -S --noconfirm --needed i3lock-color i3-resurrect ffcast
    "$aurhelper" -S --noconfirm --needed gimp ntfs-3g ntp vnstat
}

create_default_directories(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    mkdir -p "$HOME"/.config
    sudo mkdir -p  /usr/local/bin
    sudo mkdir -p  /usr/share/themes

    rm -rf "$HOME"/Pictures/wallpapers
    mkdir -p "$HOME"/Pictures/wallpapers
}

copy_configs(){
    echo -e "${green}[*] Copying configs to $config_directory.${no_color}"
    cp -r ./config/* "$config_directory"
}

copy_scripts(){
    echo -e "${green}[*] Copying scripts to $scripts_directory.${no_color}"
    sudo cp -r ./scripts/* "$scripts_directory"
}

copy_fonts(){
    echo -e "${green}[*] Copying fonts to $fonts_directory.${no_color}"
    sudo cp -r ./fonts/* "$fonts_directory"
    fc-cache -fv
}

copy_other_configs(){
    echo -e "${green}[*] Copying wallpapers to "$HOME"/Pictures/wallpapers.${no_color}"
    cp -r ./wallpapers/* "$HOME"/Pictures/wallpapers
    echo -e "${green}[*] Copying zsh configs.${no_color}"
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    sudo cp ./keyitdev.zsh-theme "$HOME"/.oh-my-zsh/custom/themes
    cp ./.zshrc "$HOME"
}

install_additional_pkgs(){
    echo -e "${green}[*] Installing additional packages with $aurhelper.${no_color}"
}

install_emoji_fonts(){
    echo -e "${green}[*] Installing emoji fonts with $aurhelper.${no_color}"
    "$aurhelper" -S --noconfirm --needed noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra
    sudo cp -f ./local.conf /etc/fonts
    fc-cache -fv
}

install_vsc(){
    echo -e "${green}[*] Installing vsc extensions.${no_color}"
    #code --install-extension zhuangtongfa.Material-theme
    echo -e "${green}[*] Copying vsc configs.${no_color}"
    cp ./vsc/settings.json "$HOME"/.config/Code\ -\ OSS/User
}

install_gtk_theme(){
    echo -e "${green}[*] Installing gtk theme.${no_color}"
    git clone --depth 1 https://github.com/Fausto-Korpsvart/Rose-Pine-GTK-Theme
    echo -e "${green}[*] Copying gtk theme to /usr/share/themes.${no_color}"
    sudo cp -r ./Rose-Pine-GTK-Theme/themes/RosePine-Main-BL  /usr/share/themes/RosePine-Main
    mkdir -p "$HOME"/.config/gtk-4.0
    sudo cp -r ./Rose-Pine-GTK-Theme/themes/RosePine-Main-BL/gtk-4.0/* "$HOME"/.config/gtk-4.0
}   

install_sddm(){
    echo -e "${green}[*] Installing sddm theme.${no_color}"
    "$aurhelper" -S --noconfirm --needed qt5-graphicaleffects qt5-quickcontrols2 qt5-svg sddm
    sudo systemctl enable sddm.service
    sudo git clone https://github.com/keyitdev/sddm-flower-theme.git /usr/share/sddm/themes/sddm-flower-theme
    sudo cp /usr/share/sddm/themes/sddm-flower-theme/Fonts/* /usr/share/fonts/
    echo "[Theme]
    Current=sddm-flower-theme" | sudo tee /etc/sddm.conf
}

finishing(){
    echo -e "${green}[*] Chmoding light.${no_color}"
    sudo chmod +s /usr/bin/light
    echo -e "${green}[*] Setting Zsh as default shell.${no_color}"
    chsh -s /bin/zsh
    sudo chsh -s /bin/zsh
    echo -e "${green}[*] Updating nvim extensions.${no_color}"
    #nvim +PackerSync
}

cmd=(dialog --clear --title "Aur helper" --menu "Firstly, select the aur helper you want to install (or have already installed)." 10 50 16)
options=(1 "yay" 2 "paru")
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

case $choices in
    1) aurhelper="yay";;
    2) aurhelper="paru";;
esac

cmd=(dialog --clear --separate-output --checklist "Select (with space) what script should do.\\nChecked options are required for proper installation, do not uncheck them if you do not know what you are doing." 26 86 16)
options=(1 "System update" on
         2 "Install aur helper" on
         3 "Install basic packages" on
         4 "Install basic packages (aur)" on
         5 "Create default directories" on
         6 "Create backup of existing configs (to prevent overwritting)" off
         7 "Copy configs" on
         8 "Copy scripts" on
         9 "Copy fonts" on
         10 "Copy other configs (gtk theme, wallpaper, vsc configs, zsh configs)" on
         11 "Install additional packages" off
         12 "Install emoji fonts" off
         13 "Install vsc theme" off
         14 "Install gtk theme" on
         15 "Install sddm theme" on
         16 "Make Light executable, set zsh as default shell, update nvim extensions." on)
choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

clear

for choice in $choices
do
    case $choice in
        1) system_update;;
        2) install_aur_helper;;
        3) install_pkgs;;
        4) install_aur_pkgs;;
        5) create_default_directories;;
        6) create_backup;;
        7) copy_configs;;
        8) copy_scripts;;
        9) copy_fonts;;
        10) copy_other_configs;;
        11) install_additional_pkgs;;
        12) install_emoji_fonts;;
        13) install_vsc;;
        14) install_gtk_theme;;
        15) install_sddm;;
        16) finishing;;
    esac
done