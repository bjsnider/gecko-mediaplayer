## Process this file with automake to produce Makefile.in

## Created by Anjuta

EXTRA_DIST = nsIScriptableGeckoMediaPlayer.idl

INCLUDES = \
	-fPIC \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GECKO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(DBUS_CFLAGS) \
	$(GCONF_CFLAGS) \
	$(GCONF_DEFINES)

AM_CFLAGS =\
	 -Wall \
	 -g 

DEFINES = -DMOZILLA_STRICT_API -DXP_UNIX

xpt_DATA = \
	gecko-mediaplayer-dvx.xpt \
	gecko-mediaplayer-qt.xpt \
	gecko-mediaplayer-rm.xpt \
	gecko-mediaplayer.xpt \
	gecko-mediaplayer-wmp.xpt
	
xptdir = $(libdir)/mozilla/plugins

gecko-mediaplayer-dvx.xpt: nsIScriptableGeckoMediaPlayer.idl
	$(GECKO_XPIDL) -w -m typelib -I $(GECKO_IDLDIR) -I $(srcdir) -e $@ $<
gecko-mediaplayer-qt.xpt: nsIScriptableGeckoMediaPlayer.idl
	$(GECKO_XPIDL) -w -m typelib -I $(GECKO_IDLDIR) -I $(srcdir) -e $@ $<
gecko-mediaplayer-rm.xpt: nsIScriptableGeckoMediaPlayer.idl
	$(GECKO_XPIDL) -w -m typelib -I $(GECKO_IDLDIR) -I $(srcdir) -e $@ $<
gecko-mediaplayer.xpt: nsIScriptableGeckoMediaPlayer.idl
	$(GECKO_XPIDL) -w -m typelib -I $(GECKO_IDLDIR) -I $(srcdir) -e $@ $<
gecko-mediaplayer-wmp.xpt: nsIScriptableGeckoMediaPlayer.idl
	$(GECKO_XPIDL) -w -m typelib -I $(GECKO_IDLDIR) -I $(srcdir) -e $@ $<

COMMONCODE = \
	plugin.cpp \
	plugin.h \
	plugin_list.h \
	plugin_list.cpp \
	plugin_types.h \
	plugin_setup.h \
	plugin_setup.cpp \
	plugin_dbus.h \
	plugin_dbus.cpp \
	np_entry.cpp \
	npn_gate.cpp \
	npp_gate.cpp \
	pluginbase.h \
	nsScriptablePeer.cpp \
	nsScriptablePeer.h \
	nsIScriptableGeckoMediaPlayer.h \
	npplat.h

install_libexecdir = $(libdir)/mozilla/plugins
install_libexec_PROGRAMS = \
	gecko-mediaplayer.so \
	gecko-mediaplayer-qt.so \
	gecko-mediaplayer-wmp.so \
	gecko-mediaplayer-rm.so \
	gecko-mediaplayer-dvx.so
	
gecko_mediaplayer_so_SOURCES = \
	plugin_types_std.cpp \
	$(COMMONCODE)
		
gecko_mediaplayer_so_CFLAGS = -fPIC 
gecko_mediaplayer_so_LDFLAGS = -shared $(GLIB_LIBS) $(DBUS_LIBS) $(GCONF_LIBS) -fPIC

gecko_mediaplayer_qt_so_SOURCES = \
	plugin_types_qt.cpp \
	$(COMMONCODE)
	
gecko_mediaplayer_qt_so_CFLAGS = -fPIC 
gecko_mediaplayer_qt_so_LDFLAGS = -shared $(GLIB_LIBS) $(DBUS_LIBS) $(GCONF_LIBS) -fPIC

gecko_mediaplayer_wmp_so_SOURCES = \
	plugin_types_wmp.cpp \
	$(COMMONCODE)
	
gecko_mediaplayer_wmp_so_CFLAGS = -fPIC 
gecko_mediaplayer_wmp_so_LDFLAGS = -shared $(GLIB_LIBS) $(DBUS_LIBS) $(GCONF_LIBS) -fPIC

gecko_mediaplayer_dvx_so_SOURCES = \
	plugin_types_dvx.cpp \
	$(COMMONCODE)
	
gecko_mediaplayer_dvx_so_CFLAGS = -fPIC 
gecko_mediaplayer_dvx_so_LDFLAGS = -shared $(GLIB_LIBS) $(DBUS_LIBS) $(GCONF_LIBS) -fPIC

gecko_mediaplayer_rm_so_SOURCES = \
	plugin_types_rm.cpp \
	$(COMMONCODE)
	
gecko_mediaplayer_rm_so_CFLAGS = -fPIC 
gecko_mediaplayer_rm_so_LDFLAGS = -shared $(GLIB_LIBS) $(DBUS_LIBS) $(GCONF_LIBS) -fPIC

