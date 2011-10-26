#!/bin/sh
echo Generating Unix makefiles
cmake -G "Unix Makefiles" ..
echo done
echo Type make to build PSOlib library
