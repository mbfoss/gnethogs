### AUTOTOOLS #######################################################
# Runs autoconf, autoheader, aclocal, automake, autopoint, libtoolize
echo "Regenerating autotools files"
autoreconf --install --force --symlink || exit 1

### INTLTOOL ########################################################
# Run after autopoint or glib-gettextize
echo "Setting up intltool"
intltoolize --copy --force --automake || exit 1

echo "Now run ./configure, make, and make install."

