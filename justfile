default:
	#!/usr/bin/bash
	if [[ ! -d "./src/builddir" ]]; then
		echo "./src/builddir does not exist."	
		meson setup src/builddir src
	fi
	meson compile -C src/builddir

test:
	#!/usr/bin/bash
	if [[ ! -d "./unit-tests/builddir" ]]; then
		echo "./unit-tests/builddir does not exist."
		meson setup unit-tests/builddir unit-tests
	fi
	meson test -C unit-tests/builddir

install: default
	meson install -C src/builddir

clean:
	rm -rf src/builddir
	rm -rf unit-tests/builddir
