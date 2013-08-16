#!/bin/bash

CATALOG_TYPE='FOF'
WEB_TYPE='Vweb'
OUTPUT="C_HaloVoid_$CATALOG_TYPE-$WEB_TYPE.dat"

echo 

HALOS_PATH="$HOME/Dropbox/Proyects/ThesisProyect/data/BOLSHOI/C_GH_$CATALOG_TYPE.dat"
VOIDS_PATH="$HOME/Dropbox/Proyects/ThesisProyect/data/BOLSHOI/$WEB_TYPE/256/voids_s1/voids_0.00/void_index.dat"

make Halo_Distance
time ./Halo_Distance.out $HALOS_PATH $VOIDS_PATH $OUTPUT