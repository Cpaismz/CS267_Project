# DLW Jan 2017: to try out ctypes

"""
to create a shared library on gnu/linux
$ gcc -c -Wall -Werror -fpic foo.c
take a look at the messages, then maybe:
$ gcc -c -Wall -fpic foo.c
this makes the library:
$ gcc -shared -o libfoo.so foo.o
"""


import ctypes
import unicodedata as ucd
class inputs(ctypes.Structure):
    #_fields_ = [('fueltype', ctypes.c_wchar_p), 
    #_fields_ = [('fueltype', ctypes.c_char_p*4), 
    _fields_ = [('fueltype', ctypes.c_char*4), 
                ('mon', ctypes.c_int)]
ft = 'heck'
ft = str.encode(ft)  
bar = inputs(fueltype = ft, mon = 1)

print ("bar.mon="+str(bar.mon))
lib = ctypes.cdll.LoadLibrary('libfoo.so')
lib.MeShow(bar)
print("here we go.")
lib.ShowMe(ctypes.byref(bar))
