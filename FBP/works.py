# mimic FBP-LINE-newest.c
# Author: David L. Woodruff, January 2017
# CAUTION: Beware of DOS versus UNIX file formats for the input data.
# (Check the first string read by the panda for a strange leading char.)


import pandas as pd
from argparse import ArgumentParser
import pprint as pp # pretty print for debugging
import ctypes

"""
to create a shared library on gnu/linux
$ gcc -c -Wall -Werror -fpic foo.c
take a look at the messages, then maybe:
$ gcc -c -Wall -fpic foo.c
this makes the library:
$ gcc -shared -o libfoo.so foo.o
"""
    
soname = "FBPfunc5.so"
try:
    lib = ctypes.cdll.LoadLibrary(soname)
except:
    raise RuntimeError("Could not load the library="+soname)

################

month = [ 0,31,59,90,120,151,181,212,243,273,304,334]

class fire_struc(ctypes.Structure):
    _fields_ = [('ros', ctypes.c_float),
                ('dist', ctypes.c_float),
                ('rost', ctypes.c_float),
                ('cfb', ctypes.c_float),
                ('fc', ctypes.c_float),
                ('cfc', ctypes.c_float),
                ('time', ctypes.c_float),
                ('rss', ctypes.c_float),
                ('isi', ctypes.c_float), 
                ('fd', ctypes.c_char),
                ('fi', ctypes.c_double)]


class main_outs(ctypes.Structure):
    _fields_ = [('hffmc', ctypes.c_float),
        ('sfc', ctypes.c_float),
        ('csi', ctypes.c_float),
        ('rso', ctypes.c_float),
        ('fmc', ctypes.c_float),
        ('sfi', ctypes.c_float),
        ('rss', ctypes.c_float),
        ('isi', ctypes.c_float),
        ('be', ctypes.c_float),
        ('sf', ctypes.c_float),
        ('raz', ctypes.c_float),
        ('wsv', ctypes.c_float),
        ('ff', ctypes.c_float), 
        ('jd_min', ctypes.c_int), 
        ('jd', ctypes.c_int), 
        ('covertype', ctypes.c_char)] 


class snd_outs(ctypes.Structure):
    _fields_ = [('lb', ctypes.c_float),
        ('area', ctypes.c_float),
        ('perm', ctypes.c_float),
        ('pgr', ctypes.c_float),
        ('lbt', ctypes.c_float)]
        
#################

class fuel_coeffs(ctypes.Structure):
    #_fields_ = [('fueltype', ctypes.c_wchar_p), 
    _fields_ = [('fueltype', ctypes.c_char*4), 
                ('q', ctypes.c_float),
                ('bui0', ctypes.c_float),
                ('cbh', ctypes.c_float),
                ('cfl', ctypes.c_float),
                ('a', ctypes.c_double),
                ('b', ctypes.c_double),
                ('c', ctypes.c_double)]

listlen = 18
ListOfCoefs = listlen * fuel_coeffs   
coef_ptr = ListOfCoefs()

lib.setup_const(coef_ptr)
print ("start debug info")
print("coef_ptr[0].fueltype="+str(coef_ptr[0].fueltype))
print("coef_ptr[0].a="+str(coef_ptr[0].a))
print("coef_ptr[17].fueltype="+str(coef_ptr[17].fueltype))
print("coef_ptr[17].a="+str(coef_ptr[17].a))
print ("end debug info")

################

parser = ArgumentParser()
parser.add_argument("--input-file-name",
                    help="The name of the csv file that contains the data",
                    dest="input_file_name",
                    type=str,
                    default=None)

args = parser.parse_args()

# Caution: the c code modifies input as they are assigned
#          to the struct; e.g. waz. I will modify them later.
# Note: I don't like the name "data" but that is what the
#       c code uses...
# Note: we do a lot of messing around because the fields
# in the input file read by the c program are not in the same
# order as in the struct, but I theorize
# that *the struct order matters.* (Jan 2017; struggles...)

class inputs(ctypes.Structure):
    _fields_ = [('fueltype', ctypes.c_char*4),
                ('ffmc', ctypes.c_float),
                ('ws', ctypes.c_float),
                ('gfl', ctypes.c_float),
                ('bui', ctypes.c_float),
                ('lat', ctypes.c_float),
                ('lon', ctypes.c_float),
                ('time', ctypes.c_int),
                ('pattern', ctypes.c_int),
                ('mon', ctypes.c_int),
                ('jd', ctypes.c_int),
                ('jd_min', ctypes.c_int),
                ('waz', ctypes.c_int),
                ('ps', ctypes.c_int),
                ('saz', ctypes.c_int),
                ('pc', ctypes.c_int),
                ('pdf', ctypes.c_int),
                ('cur', ctypes.c_int),
                ('elev', ctypes.c_int),
                ('hour', ctypes.c_int),
                ('hourly', ctypes.c_int)]

FieldsInFileOrder = [('fueltype', ctypes.c_char*4), 
                ('mon', ctypes.c_int),
                ('jd', ctypes.c_int),
                ('m', ctypes.c_int),
                ('jd_min', ctypes.c_int),
                ('lat', ctypes.c_float),
                ('lon', ctypes.c_float),
                ('elev', ctypes.c_int),
                ('ffmc', ctypes.c_float),
                ('ws', ctypes.c_float),
                ('waz', ctypes.c_int),
                ('bui', ctypes.c_float),
                ('ps', ctypes.c_int),
                ('saz', ctypes.c_int),
                ('pc', ctypes.c_int),
                ('pdf', ctypes.c_int),
                ('gfl', ctypes.c_float),
                ('cur', ctypes.c_int),
                ('time', ctypes.c_int)]
    
# ColNames are hardwired in the c code;
# the names match the struct element names.
# note that the c program doesn't read anything
# after 'time'
LastOne = 'time'
ColNames = []
for i in FieldsInFileOrder:
     na, ty = i
     ColNames.append(na)
     print ("col na=",na)
     if na == LastOne:
         print ("hit break")
         break
     
filename = args.input_file_name
if filename is None:
    raise RuntimeError("The --input-file-name option is required.")
try:
    df = pd.read_csv(filename, index_col=False, header=None, names=ColNames, encoding='utf-8')
except:
    raise RuntimeError("Could not read csv file="+filename)

print ("** start debug output")
for linenum in df.index.values:
    print (str(linenum))
    print ("df['fueltype'][linenum]="+df['fueltype'][linenum])
    print ("len(df['fueltype'][linenum])="+str(len(df['fueltype'][linenum])))
print ("**start pprint of all input data")
pp.pprint(df)
print ("**end pprint")
print ("** end debug output")

### delete this comment: can you assign directly to the struct or do you need to modify the df before calling the struct constructor????

def CopyRowtoData(index, row):
    # Copy to the data struct (bad name) with modifictions.
    # Use LastOne to truncate the copy.
    global FieldsInFileOrder
    print ("debug row['waz']="+str(row['waz']))
    kwargs = {}
    for i in FieldsInFileOrder:
        na, ty = i
        val = row[na]
        if str(val) == "nan":
            val = 0
        if ty == ctypes.c_float: 
            val = float(val)
        elif ty == ctypes.c_int: 
            val = int(val)
        elif ty == ctypes.c_double: 
            val = double(val)
        else:
            print ("ty=",str(ty))
            print ("len(val)=",len(val))
            val = val.strip()
            print ("stripped len(val)=",len(val))
            if len(val) == 2:
                val = val + ' '
            print ("type(val)=",type(val))
            for i in val:
                print ("str(i)="+str(i))
            val = str.encode(val)
            print ("after encode len(val)=",len(val))
            for i in val:
                print ("str(i)="+str(i))
            print(str(val))
        kwargs[na] = val
    print ("end loop.")
    data = inputs(**kwargs)
    # modifications; comments are from the c code
    #  data.waz+=180;if(data.waz>=360)data.waz-=360;
    print ("debug data.waz="+str(data.waz))
    data.waz += 180
    if data.waz >= 360:
        data.waz -= 360
    print ("debug2 waz="+str(data.waz))
    # if(m!=0) data.jd=month[m-1]+d;
    # else data.jd=0;
    if data.m != 0:
        data.jd = month[data.m-1] + data.jd
    else:
        data.ja = 0
    # m=(int)(var[3]); d=(int)(var[4]);   /* this is minimum foliar moisture date*/
    # if(m>0) data.jd_min=month[m-1]+d;   /* only use it if it is EXPLICITLY specified*/
    if data.mon > 0:
        data.jd_min = month[data.m-1] + data.jd_min
    #   data.pattern=1;   /* point source ignition...so acceleration is included */
    data.pattern = 1
    return data

# Main loop
for index, row in df.iterrows():
    datastruct = CopyRowtoData(index, row)
    # to be on the safe side, make new output receivers each time through
    mainstruct = main_outs()
    mainstruct.covertype = b'z'  # debug
    mainstruct.hffmc = 6.2  # debug
    mainstruct.isi = 99.99
    sndstruct = snd_outs()
    sndstruct.lb = 21.2 # debug
    headstruct = fire_struc()
    backstruct = fire_struc()
    flankstruct = fire_struc()
    # byref seems like the opposite of what it is...
    dataptr = ctypes.byref(datastruct)
    mainptr = ctypes.byref(mainstruct)
    sndptr = ctypes.byref(sndstruct)
    headptr = ctypes.byref(headstruct)
    flankptr = ctypes.byref(flankstruct)
    backptr = ctypes.byref(backstruct)
    print ("looking at mainstruct.hffmc=",mainstruct.hffmc)
    print ("dlw debug: about to do the call")
    lib.calculate(dataptr,
                  coef_ptr,
                  mainptr,
                  sndptr,
                  headptr,
                  flankptr,
                  backptr);
    print ("mainstruct.rso=",str(mainstruct.rso))

"""
PyomoFest Ausin (Jan 2017) questions:

- Have you considered writing parts in scithon, etc? 

- Why not use Python's parallelization?

- Michael B: Wanted to help in development, but source code
is "sophisticated." Any guidance concerning where to start
helping develop?

- Suggestion: Mark issues as "easy to implement."

- Suggestion: create "summer of code" type projects and post them.

- Suggestion: slicing over ordered index

- DLW: says use Var not variables in network names
  DLW: get Gabes net expression of tree thing

"""
