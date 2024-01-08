
sudo pacman -S flatpak

flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

sudo usermod -aG flatpak $USER

flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

flatpak install --user flathub APPLICATION_NAME

### Update all packages

flatpak update


### Applications

flatpak install --user flathub com.visualstudio.code
flatpak install --user flathub md.obsidian.Obsidian
flatpak install --user flathub com.bitwarden.desktop
flatpak install --user flathub org.telegram.desktop
flatpak install --user flathub com.obsproject.Studio
