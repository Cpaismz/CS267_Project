"""David L. Woodruff, March 2018: quick little program to deal with a
grid file. Ouputs Forest.asc and Data.dat (will not overwrite).
Optionally reduces the size. Will throw away rows or columns of no
data (e.g. -9999). The logic on skipping is not general: it is mainly
set up to skip the first column and last row.
*** IF IT KEEPS fewer cells, it keeps the lower left corner!!! ***
"""

import sys
import math
import os
import pandas

from pylab import *

if len(sys.argv) < 2:
    print ("***Incorrect invocation- use:"\
           + "python gridprocessor.py gridfilein [rows cols]")
    sys.exit(1)

infilename = sys.argv[1]
if len(sys.argv) > 2:
    rowsout = int(sys.argv[2])  # one-based
    colsout = int(sys.argv[3])  # one-based
else:
    rowsout = -1
    colsout = -1
    
    
gridfileoutname = "Forest.asc"
FBPdataoutname = "Data.dat"
if os.path.exists(gridfileoutname):
    raise RuntimeError("File exists:"+ gridfileoutname)

if os.path.exists(FBPdataoutname):
    raise RuntimeError("File exists:"+ FBPdataoutname)

lookupfile = "fbp_lookup_table.csv"
if not os.path.exists(lookupfile):
    raise RuntimeError("File not present:"+lookupfile)
fbplookuptableDF = pandas.read_csv(lookupfile, sep=",", index_col="grid_value")

#------------------------------------
# Deal with header:
def header_field(row, name, filelines):
    """
    process a header fields:
    args:
        row: zero based row number
        name: field name
        filelines: lines of the file
    returns:
        the field as a string
    """
    line = filelines[row].replace("\n","")
    parts = line.split()
    if parts[0] != name:
        print ("line=",line, "name=",name)
        raise RuntimeError("Expected given name on given line of "+filename)
    return parts[1]

#-------`
FPBFieldsInFileOrder = ['fueltype',
                    'mon', 
                    'jd', 
                    'm', 
                        'jd_min',
                    'lat', 
                    'lon', 
                    'elev', 
                    'ffmc', 
                    'ws', 
                    'waz', 
                    'bui', 
                    'ps', 
                    'saz', 
                    'pc', 
                    'pdf', 
                    'gfl', 
                    'cur', 
                    'time']

# default values
# pdf and pc are assumed elsewhere to default to zero
FPBBaseDict = {'fueltype': 'c1', 
               'mon': 7,
        'jd': 7,
        'm': 0,
        'jd_min': 334,
        'lat': 55,
        'lon': 110,
        'elev': 0,
        'ffmc': 90,
        'ws': 0,
        'waz': 0,
        'bui': 130,
        'ps': 0,
        'saz': 0,
        'pc': 0,
        'pdf': 0,
        'gfl': 0,
        'cur': 0,
        'time': 21
        }

WorkingFBPDict = FPBBaseDict.copy()

#---------
def do_FBP_row(f, OrdList, ValDict, cellint):
    """
    Write the FBP row for a cell.
    args:
        f: open file handle
        OrdList: list of fields in file order
        ValDict: dictionary of values to write
        cellint: integer with the fuel code for the cell
    """
    if cellint >= 100 and cellint <= 105:
        if cellint == 102:
            ft = "WA"
        else:
            ft = "NF"
    else:
        ft = fbplookuptableDF[" fuel_type"][cellint]
        partsspace = ft.split()
        ft = partsspace[0].split("/")[0].replace("-", "")
        if len(partsspace) > 1:
            if partsspace[2] == "PC)":
                pcval = int(partsspace[1][1:3])
                WorkingFBPDict['pc'] = pcval
            elif partsspace[2] == "PDF)":
                pdfval = int(partsspace[1][1:3])
                WorkingFBPDict['pdf'] = pdfval
    WorkingFBPDict['fueltype'] = ft
    f.write(ValDict[OrdList[0]])
    for i in range(1,len(OrdList)):
        f.write(","+str(ValDict[OrdList[i]]))
    f.write("\n")
    WorkingFBPDict['pc'] = WorkingFBPDict['pdf'] = 0
    
#===== main ====================

with open(infilename) as fin:
    linesin = fin.readlines()
    
colsin = int(header_field(0, "ncols", linesin)) # we are going trust this
rowsin = int(header_field(1, "nrows", linesin)) # we are going trust this
xllcorner = header_field(2, "xllcorner", linesin)
yllcorner = header_field(3, "yllcorner", linesin)
cellsize = int(header_field(4, "cellsize", linesin))
NODATA = int(header_field(5, "NODATA_value", linesin))

assert(colsin >= colsout)
assert(rowsin >= rowsout)

firstcol = 0 # zero-based
parts = linesin[6].split()
if int(parts[0]) == NODATA:
    print("Skipping first column")
    firstcol = 1
    colsin -= 1 # effective cols in

lastrow = len(linesin) - 1 # zero-based, but remember 6 lines of header
rowsin -= 1 # assume the worst...
parts = linesin[lastrow].split()
for i in range(len(parts)):
    if int(parts[i]) != NODATA:
        print("Keeping last row due to",parts[i])
        rowsin += 1 # keep them all
        break

if colsout == -1:
    colsout = colsin
if rowsout == -1:
    rowsout = rowsin

with open(gridfileoutname, "w") as fout:
    fout.write("ncols         "+str(colsout)+"\n")
    fout.write("nrows         "+str(rowsout)+"\n")
    fout.write("xllcorner     "+str(xllcorner)+"\n")
    fout.write("yllcorner     "+str(yllcorner)+"\n")
    fout.write("cellsize      "+str(cellsize)+"\n")
    fout.write("NODATA_value  "+str(NODATA)+"\n")

    with open(FBPdataoutname, "w") as f:
        firstrow = 6 + rowsin - rowsout # deleted row taken care of previously
        for i in range(6, rowsout+6):
            parts = linesin[i].strip().split()
            for j in range(firstcol, colsout+firstcol): 
                cellint = int(parts[j])
                if cellint == NODATA:
                    print ("Unexpected NODATA row="+str(i)+" col="+str(j),\
                           "replacing with",lastgood) # crash if no lastgood
                    cellint = int(lastgood)
                else:
                    lastgood = parts[j] # last good will be this time's
                fout.write(lastgood+" ")
                do_FBP_row(f, FPBFieldsInFileOrder, WorkingFBPDict, cellint)
            fout.write("\n")
