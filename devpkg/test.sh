set -e

# Sets up a new install on a computer.
./devpkg -S

# Installs a piece of software from a URL.
./devpkg -I http://archive.apache.org/dist/apr/apr-1.5.2.tar.gz

# Lists all the software that's been installed.
./devpkg -L

# Fetches some source code for manual building.
./devpkg -F

# Builds fetches source code and installs it, even if already installed.
./devpkg -B


