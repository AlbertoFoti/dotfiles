echo "(0/3)[CHECK SYSTEM FAILURES]"
systemctl --failed

echo "(1/3)[UPDATING SYSTEM]"
sudo pacman -Sy --noconfirm archlinux-keyring
sudo pacman --noconfirm -Syu
paru --noconfirm -Syyu

echo "(2/3)[UPDATING FLATPAK]"
flatpak update
flatpak uninstall --unused

echo "(3/4)[CLEARING CACHE]"
paccache -r