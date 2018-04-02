#!/bin/bash
# inspired by the bat file for 400CellHom and quickstart.bash

BASEDIR="/home/david/Documents/Research/FireSimulator"
DDIR="$BASEDIR/Instances/400CellsDLW/nowindnoslope"
TORUN="$BASEDIR/Jan2018dlw/AlphaVersion/SimJan2018.py"

python $TORUN --input-instance-folder=$DDIR --ignitions --nsims=1 --output-grid  --weather-file --weather=constant  --sim-years=1 --ROS-Start-Threshold=1e-3 --Mean-Burnout-Periods=0 --output-folder=outdir --ROS-CV=0 --PeriodLen=60 --verbose

##--weather-file is needed as of feb even with constant weather... dlw
###  --plot --combine
###  --save-memory
