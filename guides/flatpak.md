
sudo pacman -S flatpak

flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

sudo usermod -aG flatpak $USER

flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

flatpak install --user flathub APPLICATION_NAME

### Update all packages

flatpak update


### Applications

### Testing
//flatpak install --user flathub org.onlyoffice.desktopeditors [broken] 
//flatpak install --user flathub com.bitwarden.desktop [broken]
//flatpak install --user flathub org.gnome.baobab [theming]
//flatpak install --user flathub org.gnome.Calculator [theming]
//flatpak install flathub org.gnome.Calendar [theming]

### Theming

paru -S flatseal

or

sudo flatpak override --env=GTK_THEME=<theme_name>
sudo flatpak override --filesystem=$HOME/.themes