#!/bin/sh
EXPLORATIONS=web-game-accessibility-explorations.master
echo
echo "Checking out submodule..."
git submodule init || exit 42
git submodule update --remote || exit 42
cd $EXPLORATIONS || exit 42
git checkout master || exit 42
git reset --hard || exit 42
cd - || exit 42
echo
echo "Building all explorations..."
cd $EXPLORATIONS || exit 42
git pull || exit 42
./install-and-build-all.sh || exit 42
cd - || exit 42
echo
echo "Coyping in needed things..."
cp -v $EXPLORATIONS/04-menu-general/page-sdl.* . || exit 42
