
SET DDIR=%C:\Users\dlm\Dropbox\1_Woodruff_FireSimulator\Instances\9CellsHomDLW\%
SET TDIR=%C:\Users\dlm\Dropbox\1_Woodruff_FireSimulator\Jan2018dlw\AlphaVersion\%

python %TDIR%SimJan2018.py --input-instance-folder=%DDIR% --ignitions --nsims=1 --output-grid  --weather-file --weather=constant  --sim-years=1 --ROS-Start-Threshold=1e-3 --Mean-Burnout-Periods=0 --output-folder=outdir --ROS-CV=0 --PeriodLen=60 --verbose --plot --combine --seed=11345
