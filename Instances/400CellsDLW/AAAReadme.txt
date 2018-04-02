DLW, Feb 2018

cryptic notes from DLW to DLW

starting from 400CellsHom

copied a lot of files from something like East/Ignition1, but
then edited them.

in Data.dat fuel type c1 --> c2
in Weather.dat: changed the wind speed from w to 0.w (i.e., very low)

----------
Feb 6
forest and cell data seems to be hard-wired (e.g., cell size)

=====
Feb 10
removed slope from the data

======
aside: the program creates a series of png files
in the plots subdir of the output dir. On unix make
a movie using
ffmpeg -i forest%04d.png firemovie.gif
(there is some commented out code for windows someplace)
