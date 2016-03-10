AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(GNETHOGS_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gnethogs

gnethogs_SOURCES =  \
	main.cpp \
	MainWindow.h \
	TreeData.h \
	MainWindow.cpp \
	gresources.c

gnethogs_LDFLAGS = -lnethogs 
gnethogs_CXXFLAGS = --std=c++11 

gnethogs_LDADD = $(GNETHOGS_LIBS) $(PTHREAD_LIBS)

ui_dir = ../ui/
ui_gresource = ../ui/app.gresources.xml
ui_deps = \
	$(ui_dir)/appmenu.ui \
	$(ui_dir)/headerbar.ui \
	$(ui_dir)/window.glade \
	$(ui_dir)/aboutdialog.glade

gresources.c: $(ui_gresource) $(ui_deps)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --generate-source --sourcedir=$(ui_dir) $(ui_gresource) --target=$@
