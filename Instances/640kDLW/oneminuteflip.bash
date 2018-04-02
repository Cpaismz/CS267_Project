#!\bin\bash
# Run something (anything) using the simulator just to verity that it runs
# ASSUMES the FBP ".so" file is in this directory
# IMPORTANT: the Dogrib data will use too much memory on most computers

BASEDIR="/export/home/dlwoodruff/Documents/FireSimulator"
DDIR="$BASEDIR/Instances/640kDLW/"
TORUN="$BASEDIR/Jan2018dlw/AlphaVersion/SimJan2018.py"

mpiexec -n 20 python $TORUN --input-instance-folder=$DDIR --ignitions --nsims=1  --weather-file  --ROS-Start-Threshold=1e-3 --Mean-Burnout-Periods=3 --ROS-CV=0.13 --output-folder=outdir --weather=date-based --seed=1134 --PeriodLen=1 --max-fire-periods=100
###--verbose --output-grid
## --plot --combine

##python SimJan2018.py --input-instance-folder=$DDIR --output-folder=simoutput --ignitions --nsims=1 --output-grid --weather-file --plot --combine --ROS-Start-Threshold=1e-3 --spotting-parameter-data-file-name=SpotSample.json
