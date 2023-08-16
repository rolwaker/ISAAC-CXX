#!/bin/bash
set -e

cmake .
make

./isaac64-old >old.txt
./isaac64-new >new.txt

diff old.txt new.txt
