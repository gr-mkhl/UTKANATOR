#!/bin/bash

cd "$(dirname "$0")/.." || exit

mkdir -p build
mkdir -p databases

g++ -D LOGGING -I include src/graphic_akinator.c src/graphic_tools.c src/tree.c src/log.c src/stack.c -o build/akinator_graphic_game.out -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lasound

./build/akinator_graphic_game.out
