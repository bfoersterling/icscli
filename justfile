default:
	#!/usr/bin/bash
	if [[ ! -d "./src/builddir" ]]; then
		echo "./src/builddir does not exist."	
		meson setup src/builddir src
	fi
	meson compile -C src/builddir

test:
	#!/usr/bin/bash
	if [[ ! -d "./unit_tests/builddir" ]]; then
		echo "./unit_tests/builddir does not exist."
		meson setup unit_tests/builddir unit_tests
	fi
	meson test -C unit_tests/builddir

install: default
	meson install -C src/builddir

clean:
	rm -rf src/builddir
	rm -rf unit_tests/builddir
