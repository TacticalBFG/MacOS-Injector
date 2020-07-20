# Helicity MacOS Injector - Shell
# Actual injection library used is lib2proc, written by Natov
# https://www.unknowncheats.me/forum/pc-software/214802-lib2proc-definitive-os-macos-injector.html

path=$(cd "$(dirname "$0")"; pwd -P)    # Get absolute path of Helicity's folder
cd $path                                # CD to it so the relative paths work right (injector gives its own application path)
sudo ./lib2proc $1 ./Helicity_MacOS.dylib   # Inject
# Because this is ran as sudo (super-user do); it'll ask for an admin password;

# Source avaliable at https://github.com/TacticalBFG/MacOS-Injector
