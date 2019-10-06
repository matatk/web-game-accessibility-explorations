#!/bin/sh
echo 'This will carry out the install steps in the main README (except for Emscripten set-up, which needs to be done manually) and then install the dependencies of, and build, all explorations.' | fmt
echo
echo 'Interrupt to abort, or press ENTER to continue...'
read -r _

echo Installing repo native dependencies...
if [ "$(uname -s)" = 'Darwin' ]; then
	brew install cppcheck
else
	sudo apt-get install cppcheck
fi
echo

echo Installing repo Node dependencies...
npm install
echo

echo Installing dependencies of, and building, each exploration...
echo
for makefile in */Makefile; do
	DIR=$(dirname "$makefile")
	cd "$DIR" || continue
	echo "Exploration: $DIR"
	if grep '^install-deps:' Makefile > /dev/null; then
		make install-deps
		echo
	fi
	make
	cd - > /dev/null || exit
	echo
done
