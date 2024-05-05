#!/bin/fish

# Possible themes:
# > diana
#
#
set theme "diana"

# -------------------------------------------------------------------

## Color palette
source ~/dotfiles/theming/themes/$theme/palette.sh
# Echo the color variables
echo "Primary background color: $PRIMARY_BG"
echo "Color 1: $COLOR1"
echo "Color 2: $COLOR2"
echo "Color 3: $COLOR3"
echo "Primary foreground color: $PRIMARY_FG"

## Hyprland
rm ~/dotfiles/config/hypr/conf/hypr_colors.conf 
ln -s ~/dotfiles/theming/themes/$theme/hypr_colors.conf ~/dotfiles/config/hypr/conf/hypr_colors.conf 

## Kitty
rm ~/dotfiles/config/kitty/kitty_colors.conf 
ln -s ~/dotfiles/theming/themes/$theme/kitty_colors.conf ~/dotfiles/config/kitty/kitty_colors.conf 

## Starship
rm ~/dotfiles/config/starship.toml 
ln -s ~/dotfiles/theming/themes/$theme/starship.toml ~/dotfiles/config/starship.toml 