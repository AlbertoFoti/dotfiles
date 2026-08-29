sudo apt update

sudo apt install nala
sudo nala install git g++ cmake nvim
sudo nala install -y \
  curl wget git unzip tar gzip \
  build-essential cmake ninja-build pkg-config \
  ripgrep fd-find \
  nodejs npm \
  python3 python3-pip python3-venv \
  clangd clang-format \
  rustup \
  wl-clipboard \
  fontconfig

# Git Configuration
ssh-keygen -t ed25519 -C "alberto.foti@proton.me"
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
cat ~/.ssh/id_ed25519.pub

git config --global user.name "Alberto Foti"
git config --global user.email "alberto.foti@proton.me"

git config --global init.defaultBranch main
git config --global core.editor "nvim"
git config --global pull.rebase false
git config --global color.ui auto

# Rust
rustup default stable
rustup component add rustfmt clippy

# Fonts
mkdir -p ~/.local/share/fonts/JetBrainsMonoNerdFont

curl -L \
  https://github.com/ryanoasis/nerd-fonts/releases/latest/download/JetBrainsMono.tar.xz \
  -o /tmp/JetBrainsMonoNerdFont.tar.xz

tar -xf /tmp/JetBrainsMonoNerdFont.tar.xz \
  -C ~/.local/share/fonts/JetBrainsMonoNerdFont

fc-cache -fv
