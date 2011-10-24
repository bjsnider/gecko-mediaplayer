## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

gecko_mediaplayerdocdir = ${prefix}/share/doc/gecko-mediaplayer
gecko_mediaplayerdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	DOCS/tech/javascript.txt

gecko_mediaplayeretcdir = ${sysconfdir}/gconf/schemas
gecko_mediaplayeretc_DATA = gecko-mediaplayer.schemas

EXTRA_DIST = $(gecko_mediaplayerdoc_DATA) $(gecko_mediaplayeretc_DATA) gecko-mediaplayer.spec.in

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
	rm -rf $(distdir)/src/nsIScriptableGeckoMediaPlayer.h

install-data-hook:
	if [ -e ${sysconfdir}/gconf/schemas/gecko-mediaplayer.schemas ]; then GCONF_CONFIG_SOURCE=`gconftool-2 --get-default-source` gconftool-2 --makefile-install-rule ${sysconfdir}/gconf/schemas/gecko-mediaplayer.schemas > /dev/null;	fi

