iconsdir = $(datadir)/icons

nobase_dist_icons_DATA = \
	hicolor/16x16/apps/gnethogs.png \
	hicolor/22x22/apps/gnethogs.png \
	hicolor/24x24/apps/gnethogs.png \
	hicolor/32x32/apps/gnethogs.png \
	hicolor/48x48/apps/gnethogs.png

gtk_update_icon_cache = gtk-update-icon-cache -f -t $(datadir)/icons/hicolor

install-data-hook: update-icon-cache
uninstall-hook: update-icon-cache
update-icon-cache:
	@-if test -z "$(DESTDIR)"; then \
		echo "Updating Gtk icon cache."; \
		$(gtk_update_icon_cache); \
	else \
		echo "*** Icon cache not updated.  After (un)install, run this:"; \
		echo "***   $(gtk_update_icon_cache)"; \
	fi
