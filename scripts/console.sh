#!/bin/bash

cd "$(dirname "$0")/.." || exit

mkdir -p build
mkdir -p databases

g++ -D LOGGING -I include src/console_akinator.c src/tree.c src/stack.c src/log.c -o build/console_akinator_game.out

./build/console_akinator_game.out
