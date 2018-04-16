#!\bin\bash
# Run something (anything) using the simulator just to verity that it runs
# ASSUMES the FBP ".so" file is in this directory
# IMPORTANT: the Dogrib data will use too much memory on most computers

#BASEDIR="/export/home/dlwoodruff/Documents/FireSimulator"
BASEDIR="/home/david/Documents/Research/FireSimulator"
DDIR="$BASEDIR/Instances/400CellsDLW/test1inputs"
TORUN="$BASEDIR/Jan2018dlw/AlphaVersion/SimJan2018.py"

python $TORUN --input-instance-folder=$DDIR --ignitions --nsims=10 --output-grid --weather-file --ROS-Start-Threshold=1e-3 --Mean-Burnout-Periods=2 --ROS-CV=0.13 --output-folder=outdir --weather=date-based --seed=1134

# mpiexec -n 50 

##  --plot --combine

##python SimJan2018.py --input-instance-folder=$DDIR --output-folder=simoutput --ignitions --nsims=1 --output-grid --weather-file --plot --combine --ROS-Start-Threshold=1e-3 --spotting-parameter-data-file-name=SpotSample.json