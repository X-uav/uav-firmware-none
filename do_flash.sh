#!/bin/bash

#make clean && make OptLIB=3 OptSRC=0 all tshow
make OptLIB=3 OptSRC=0 all tshow

read
cur_dir=`pwd`

#Configure which device used
chip="stm32f103c8"

#Download which file
obj="$cur_dir/main.bin"
#obj="$cur_dir/remote.hex"

#Use J-link to download
./jlink.sh $chip $obj

#Done
echo "Done."



