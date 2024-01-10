
sudo pacman -S flatpak

flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

sudo usermod -aG flatpak $USER

flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

flatpak install --user flathub APPLICATION_NAME

### Update all packages

flatpak update


### Applications
flatpak install --user flathub com.visualstudio.code
flatpak install --user flathub org.mozilla.Thunderbird
flatpak install --user flathub org.mozilla.firefox
flatpak install --user flathub md.obsidian.Obsidian
flatpak install --user flathub org.telegram.desktop
flatpak install --user flathub org.kde.kdenlive
flatpak install --user flathub com.obsproject.Studio
flatpak install --userflathub org.libreoffice.LibreOffice
flatpak install --user flathub com.interversehq.qView 
flatpak install --user flathub org.audacityteam.Audacity  
flatpak install --user flathub com.spotify.Client
flatpak install --user flathub org.gnome.FileRoller

### Testing
flatpak install --user flathub com.discordapp.Discord
flatpak install --user flathub com.valvesoftware.Steam
flatpak install --user flathub com.jetbrains.IntelliJ-IDEA-Community

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