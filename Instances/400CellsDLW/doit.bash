#!/bin/bash
# inspired by the bat file for 400CellHom and quickstart.bash

BASEDIR="/home/david/Documents/Research/FireSimulator"
DDIR="$BASEDIR/Instances/400CellsDLW/test1inputs"
TORUN="$BASEDIR/Jan2018dlw/AlphaVersion/SimJan2018.py"

python $TORUN --input-instance-folder=$DDIR --ignitions --nsims=1 --output-grid  --weather=rows  --sim-years=1 --ROS-Threshold=1e-3 --output-folder=outdir --ROS-CV=0 --Fire-Period-Length=60 --Weather-Period-Length=1440 --plot --combine
##--weather-file is needed as of feb even with constant weather... dlw
### --verbose
