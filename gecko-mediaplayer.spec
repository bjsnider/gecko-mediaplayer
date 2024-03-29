%define ver 1.0.4
%define use_gconf 0

Name: gecko-mediaplayer
Summary: Multimedia browser plugin for Gecko based browsers
Version: %{ver}
Release: 1%{?dist}
License: GPLv2+
Group: Internet/Multimedia
Packager: Kevin DeKorte <kdekorte@gmail.com>
Source0: http://dekorte.homeip.net/download/gecko-mediaplayer/gecko-mediaplayer-%{ver}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Requires: gnome-mplayer

%if 0%{?fedora} > 8
BuildRequires: gcc-c++, pkgconfig, gettext, xulrunner-devel, dbus-devel, dbus-glib-devel, glib2-devel, GConf2-devel, libX11-devel libcurl-devel 
%else
BuildRequires: gcc-c++, pkgconfig, gettext, firefox-devel, dbus-devel, dbus-glib-devel, glib2-devel, GConf2-devel, libX11-devel
%endif

%description
Gecko Media Player is a browser plugin that uses GNOME MPlayer to play media in a browser. It should work with all browsers on Unix-ish systems(Linux, BSD, Solaris) and use the NS4 API (Mozilla, Firefox, Opera, etc.). Gecko Media Player is in heavy development, but I wanted to get some code drops out there so that people can start using and testing it.

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf %buildroot
make install DESTDIR=%buildroot

%clean
rm -rf $buildroot

%post
update-desktop-database %{_datadir}/applications
%if %{use_gconf}
export GCONF_CONFIG_SOURCE=`gconftool-2 --get-default-source`
if [ -e %{_sysconfdir}/gconf/schemas/gecko-mediaplayer.schemas ]; then
gconftool-2 --makefile-install-rule %{_sysconfdir}/gconf/schemas/gecko-mediaplayer.schemas > /dev/null
fi 
%endif

%files
%defattr(-,root,root,-)
%{_docdir}/%{name}
%{_libdir}/mozilla
%{_datadir}/locale
%if %{use_gconf}
%config %{_sysconfdir}
%endif
