#!/bin/bash

CATALOG_TYPE='FOF'
WEB_TYPE='Tweb'
OUTPUT="C_HaloVoid_$CATALOG_TYPE-$WEB_TYPE.dat"
PROC=$2

HALOS_PATH="./halos_catalog_fof.dat"
VOIDS_PATH="$HOME/Projects/CosmicData/BOLSHOI/$WEB_TYPE/256/voidsFAG/voids_01/void_index.dat"

#Running code in serial
if [ $1 -eq 1 ]; then
    make CFLAGS='-g -I. -c -DPRINT' Halo_Distance
    time ./Halo_Distance.out $HALOS_PATH $VOIDS_PATH $OUTPUT
#Running code in parallel
elif [ $1 -eq 2 ]; then
    make Halo_Distance
    #Dividing the file for each processor
    NUMLIN=$(wc -l $HALOS_PATH | awk '{print $1}')
    split -l $(($NUMLIN/($PROC))) $HALOS_PATH
    #Creating string to run
    COMMAND="("
    for f in $(ls x??); do
	OUTPUT_T="$OUTPUT.$f"
	COMMAND+="echo ./Halo_Distance.out ./$f $VOIDS_PATH $OUTPUT_T;"
    done
    COMMAND+=") | parallel"
    #echo $COMMAND > log.log
    time eval $COMMAND
    #Removing trash and creating final file
    cat `ls $OUTPUT.x*` > $OUTPUT
    rm $OUTPUT.x* x*
fi


# ELVIS
# BOX=$1
# SCHEME='Tweb'
# RES=64
# OUTPUT="./distances$BOX.dat"
# 
# echo 
# 
# HALOS_PATH="../Elvis_Web/data/$SCHEME$RES/voids/halos$BOX.dat"
# VOIDS_PATH="../Elvis_Web/data/$SCHEME$RES/voids/voids$BOX/void_index.dat"
# 
# make Halo_Distance
# time ./Halo_Distance.out $HALOS_PATH $VOIDS_PATH $OUTPUT