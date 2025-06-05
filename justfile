default:
	cd src && meson setup builddir
	cd src/builddir && meson compile

install:
	cd src/builddir && meson install
