#!/bin/bash
# Run something (anything) using the simulator just to verity that it runs
# ASSUMES the FBP ".so" file is in this directory
# IMPORTANT: the Dogrib data will use too much memory on most computers

DDIR="C:/Users/Lenovo/Documents/GitHub/FireSimulator/Instances/9CellsHom"

#python SimJan2018.py --help


python SimJan2018.py --input-instance-folder=$DDIR --output-folder=simoutput --ignitions --nsims=1 --output-grid --plot --combine --ROS-Threshold=0.1 --seed=7734 --verbose
##--spotting-parameter-data-file-name=SpotSample.json
