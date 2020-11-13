#!/bin/bash

INPUT="/home/sci/ssane/data/KarmanVortexStreet_Unsteady/kvs2d.vtk"
OUTPUT="/home/sci/ssane/data/KarmanVortexStreet_Unsteady/SplitVTK/"
DIMX=640
DIMY=80
DIMZ=1501

./SplitVTK $INPUT $OUTPUT $DIMX $DIMY $DIMZ
