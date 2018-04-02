#!\bin\bash
# Run something (anything) using the simulator just to verity that it runs
# ASSUMES the FBP ".so" file is in this directory
# IMPORTANT: the Dogrib data will use too much memory on most computers

BASEDIR="/home/woodruff/Documents/Research/FireSimulator"
DDIR="$BASEDIR/Instances/400CellsDLW/nowindnoslope"
TORUN="$BASEDIR/Jan2018dlw/AlphaVersion/SimJan2018.py"

python $TORUN --input-instance-folder=$DDIR --FBP-tester-cell=210
