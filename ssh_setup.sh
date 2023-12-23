# > SSH Keys
ssh-keygen -t ed25519 -C "albertofots@gmail.com"
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

git config --global user.email "albertofots@gmail.com"
git config --global user.name "albertofots"

cat ~/.ssh/id_ed25519.pub
# Log in to bitwarden
echo "[SYS] Now login to Bitwarden and access github to add the key above"