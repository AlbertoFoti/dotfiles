
paru -S android-studio

paru -S flutter

paru -Sy android-sdk android-sdk-build-tools android-sdk-cmdline-tools-latest android-platform android-sdk-platform-tools

sudo cp -R /opt/android-sdk ~

cd ~
sudo chown -R yourusername:yourgroupname android-sdk

export ANDROID_HOME=$HOME/android-sdk
export PATH=$PATH:$ANDROID_HOME/platform-tools
export JAVA_HOME=/usr/lib/jvm/java-17-openjdk