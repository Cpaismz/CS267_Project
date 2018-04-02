# test driver for HFFMC.c
# Author: David L. Woodruff, January 2017
# CAUTION: Beware of DOS versus UNIX file formats for the input data.
# (Check the first string read by the panda for a strange leading char.)
# This code is written for Python 3.x, but the call is the same for 2.7


import pandas as pd
from argparse import ArgumentParser
import pprint as pp # pretty print for debugging
import ctypes

"""
to create the shared library on gnu/linux
$ gcc -c -Wall -fpic HFFMC.c
this makes the library:
$ gcc -lm -shared -o HFFMC.so HFFMC.o
(For windows consider using mingw)
"""
    
soname = "HFFMC.so"
try:
    lib = ctypes.cdll.LoadLibrary(soname)
except:
    raise RuntimeError("Could not load the library="+soname)

################

#ctypes.c_float, ctypes.c_int, ctypes.c_double

parser = ArgumentParser()
parser.add_argument("--input-file-name",
                    help="The name of the file that contains the test data",
                    dest="input_file_name",
                    type=str,
                    default=None)

parser.add_argument("--output-file-name",
                    help="The name of the file for output (default demo_HFFMC.out)",
                    dest="output_file_name",
                    type=str,
                    default="demo_HFFMC.out")

parser.add_argument("--previous-ffmc",
                    help="The value with which to initialize oldffmc (default=85.0)",
                    dest="oldffmc",
                    type=float,
                    default=85.0)

args = parser.parse_args()

colnames = ["year", "mon", "day", "hour", "temp", "rh", "ws", "rain"]

# Read the data used by the C program for verification.
#   (The delimiter specifies any number of spaces.)
filename = args.input_file_name
if filename is None:
    raise RuntimeError("The --input-file-name option is required.")
try:
    df = pd.read_csv(filename,
                     index_col=False,
                     header=None,
                     names=colnames,
                     delimiter=r"\s+",
                     encoding='utf-8')
except:
    raise RuntimeError("Could not read input file="+filename)

# Main loop
lib.hourly_ffmc.restype = ctypes.c_float  # establish return value's type
with open(args.output_file_name, "w") as fout:
    oldffmc = args.oldffmc
    for index, row in df.iterrows():
        ffmc = lib.hourly_ffmc(ctypes.c_float(row["temp"]),
                               ctypes.c_float(row["rh"]),
                               ctypes.c_float(row["ws"]),
                               ctypes.c_float(row["rain"]),
                               ctypes.c_float(oldffmc))
        oldffmc = ffmc
        # fprintf(out,"%4d %2d %2d %2d %5.1f %3.0f %5.1f %5.1f %5.1f\n",year,mon,day,hour,temp, rh, ws, rain, ffmc)
        fout.write("{:4d} {:2d} {:2d} {:2d} {:5.1f} {:3.0f} {:5.1f} {:5.1f} {:5.1f}\n".format(int(row["year"]),int(row["mon"]),int(row["day"]),int(row["hour"]),row["temp"],row["rh"], row["ws"], row["rain"], ffmc))

