#!/bin/bash -le

# Install gcc 
# Note: This section will need to be re-run between every SteamOS upgrade
sudo steamos-readonly disable
sudo pacman --sync --noconfirm base-devel glibc linux-api-headers
sudo steamos-readonly enable

# Install and setup homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
(echo; echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"') >> /home/deck/.bash_profile
eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"

# Install our development dependencies
brew install cmake git git-lfs llvm ninja

# Intall our development tools
flatpak install flathub com.raggesilver.BlackBox
flatpak install flathub com.visualstudio.code
