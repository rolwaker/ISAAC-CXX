#!/bin/bash
set -e

cmake .
make

./isaac32-old >old.txt
./isaac32-new >new.txt

diff old.txt new.txt
