from argparse import ArgumentParser
import ctypes
import CellsFBP
import ReadData
import WeatherFBP
import pprint as pp 
import numpy as np

# Shared library
soname = "FBPfunc5NODEBUG.so"
try:
    lib = ctypes.cdll.LoadLibrary(soname)
except:
    raise RuntimeError("Could not load the library="+soname)
	
# Coefficients
listlen = 18
ListOfCoefs = listlen * CellsFBP.fuel_coeffs   
coef_ptr = ListOfCoefs()
lib.setup_const(coef_ptr)

print("Attributes coef_ptr")
l = dir(coef_ptr)
print(l)

# Read Folder from cmd line
parser = ArgumentParser()
parser.add_argument("--folder",
					help="The path to the folder contains all the files for the simulation",
                    dest="input_folder",
                    type=str,
                    default=None)		

# Read Folder
args = parser.parse_args()
Folder = args.input_folder
filename = Folder+"Data.dat"

# Read DataFrame
DF = ReadData.inputData(filename)

# Printing info
print(DF)
print(DF.columns)

# FBP objects: main, head, flank, and back
mainstruct, headstruct, flankstruct, backstruct = ReadData.CalculateOne(DF,coef_ptr,1)
print("Attributes mainstruct")
l = dir(mainstruct)
print(l)

print("\nAttributes headstruct")
l = dir(headstruct)
print(l)

print("\nAttributes flankstruct")
l = dir(flankstruct)
print(l)

print("\nAttributes backstruct")
l = dir(backstruct)
print(l)


print("\nTEST mainstruct raz", mainstruct.raz)

print("\nTEST headstruct ros", headstruct.ros)
#print("TEST headstruct rost", headstruct.rost)

print("\nTEST flankstruct ros", flankstruct.ros)
#print("TEST flankstruct rost", flankstruct.rost)

print("\nTEST backstruct ros", backstruct.ros)
#print("TEST backstruct rost", backstruct.rost)

thetafire = mainstruct.raz
forward = headstruct.ros
flank = flankstruct.ros
back = backstruct.ros

############################ End First DEBUG ###############################

print("")
print("New DF: Changing WS, WAZ, SAZ - getting new RAZ and ROSs")
# Weather Object
InitialWeather = {"Wind_Speed": 30, "Wind_Direction": 25, "Temperature": 23, "DPoint": 8.4, "Rain": 0, "Radiation": 0, "RHumidity":0}
Weather_Obj = WeatherFBP.Weather(InitialWeather)

# Update weather for checking impact in DF

''' 
Note: Setting the WindSpeed >= 2 gives us the current wind direction as the 
forward direction for the fire when calling the CalculateOne function.
When WindSpeed < 2, the forward direction gives us the opposite angle (+180).
Ex:  WindSpeed = 10, WindDirection = 90  => mainstruct.raz = 90 
       WindSpeed = 1.5, WindDirection = 90  => mainstruct.raz = 270 

We have to be aware of this...

Modifications were performed inside the WeatherFBP class, changing the logic of 
the update_Weather_FBPReadFile function in order to deal with the different angle systems.
In prometheus and inside the FBP, EAST = 270  (EAST = 0 for us), NORTH = 180, (NORTH = 90 for us)
WEST = 90 (WEST = 180 for us), SOUTH = 0 (SOUTH = 270 for us) 

'''
WindSpeed = [2]
WindDirection = [135]
Temperature = [10]
RHumidity = [1]
Precipitation = [0]
period = 0

print("Setting values: weather in DF")
print("WindSpeed:", 20,"[m/s]")
print("WindDirection:", 90,"[degrees], East = 0 degrees, counter clockwise")


DF = Weather_Obj.update_Weather_FBPReadFile(period,DF,WindSpeed,
																	WindDirection,Temperature,
																	RHumidity,Precipitation,False)
# Check new DF
print("New DF: ", DF)
print("Wind Angle:", DF["waz"])	


# Check new FBP objects: main, head, flank, and back
mainstruct, headstruct, flankstruct, backstruct = ReadData.CalculateOne(DF,coef_ptr,1)
															
print("\nTEST mainstruct raz", mainstruct.raz)

print("\nTEST headstruct ros", headstruct.ros)
#print("TEST headstruct rost", headstruct.rost)

print("\nTEST flankstruct ros", flankstruct.ros)
#print("TEST flankstruct rost", flankstruct.rost)

print("\nTEST backstruct ros", backstruct.ros)
#print("TEST backstruct rost", backstruct.rost)

# New values
thetafire = mainstruct.raz
forward = headstruct.ros
flank = flankstruct.ros
back = backstruct.ros

############################ End Second DEBUG ###############################

print("")
print("ROS functions: allocation and distribution")
# ROS functions
def allocate(offset, base, ros1, ros2):
        # allocate the ros between 1 and 2 based on the angle
		d = (offset - base) / 90.
		return (1-d) * ros1 + d * ros2
    

def ros_distr(thetafire, forward, flank, back, ROSAngleDir):
    """
    Distribute the rate of spread (ROS,ros) to the axes given in the AngleList.
    All angles are w.t.r. E-W with East positive and in non-negative degrees.
    Inputs:
        thetafire: direction of "forward"
        forward : forward ROS
        flank: ROS normal to forward (on both sides)
        back: ROS in the opposide direction of forward
        AngleList: List of angles for the axes connecting centers
                   of interest (might have less than 8 angles)
    Effect:
        Populate the ROSAngleDir, whose indexes are the angles,
        with ROS values.
    no return value
    """
	
    for angle in ROSAngleDir:
		#offset = angle - thetafire  # CP: this can be negative with the current angle system e.g. angle = 0, thetafire = 25
		offset = np.abs(angle - thetafire)  # CP: abs value and works with our angle system
		print("Angle:", angle)
		print("Thetafire:", thetafire)
		print("Offset:", offset)
		
		if offset >= 0 and offset <= 90:
			ROSAngleDir[angle] = allocate(offset, 0., forward, flank)
		elif offset > 90 and offset < 180:
			ROSAngleDir[angle] = allocate(offset, 90., flank, back)
		elif offset >= 180 and offset <= 270:
			ROSAngleDir[angle] = allocate(offset, 180., back, flank)
		elif offset > 270 and offset < 360:
			ROSAngleDir[angle] = allocate(offset, 270., flank, forward)
    return ROSAngleDir
	
	
# Test data 
ROSAngleDir = {0: 0, 45: 0, 90: 0, 135: 0, 180: 0, 
					   225: 0, 270: 0, 315: 0}
					   
					   
#ROSAngleDir = ros_distr(thetafire, forward, flank, back, ROSAngleDir)
ROSAngleDir = ros_distr(thetafire, forward, flank, back, ROSAngleDir)
print("ROSAngleDir:",ROSAngleDir)	




################################# END DEBUG 3 ##################################
