import ReadDataPrometheus
from argparse import ArgumentParser
import ctypes
import CellsFBP
import ReadData
import WeatherFBP
import pprint as pp 
import math

########################### INITIALIZATION ################################
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


# Test Angles and data structure
FireProgress = {}  # dynamic; meters from the center on the axis
AngleDict = {} # static; indexed by neighbors contains angle
ROSAngleDir = {} # dynamic; indexed by active angles; contains currenROS
DistToCenter = {} # static; distance in meters
angle_to_nb = {} # static map


# Read 9 Cells (testing purposes)
parser = ArgumentParser()
parser.add_argument("--folder",
					help="The path to the folder contains all the files for the simulation",
                    dest="input_folder",
                    type=str,
                    default=None)		

# Read Folder
args = parser.parse_args()
Folder = args.input_folder

if Folder != None:
	ForestFile = Folder+"Forest.asc"
	FBPlookup = Folder+"fbp_lookup_table.csv"
	
FBPDict,ColorsDict =  ReadDataPrometheus.Dictionary(FBPlookup)
CellsGrid3,CellsGrid4,Rows,Cols,AdjCells,CoordCells = ReadDataPrometheus.ForestGrid(ForestFile,FBPDict)
			
print("Adjacents Cell 1:", AdjCells[1-1])
print("CoordCells:", CoordCells)
print("CellsGrid3:", CellsGrid3)

# Dataframe 
filename = Folder+"Data.dat"

# Read DataFrame
DF = ReadData.inputData(filename)



########################### INITIALIZATION ################################

########################### ISOLATED CELL TEST ################################

# Computing angles (CP style from spotting function) for cell 1 (0 in arrays)
# Case by case to avoid mistakes like 45 instead of 225 due to atan() output
CCell = 4

print("")
print("Values for cell", CCell+1)
for nb in AdjCells[CCell].values():
	if nb != None: 
		a = -CoordCells[nb[0]-1][0] + CoordCells[CCell][0]
		b = -CoordCells[nb[0]-1][1] + CoordCells[CCell][1]
		
		if a == 0:
			if b>=0:
				angle = 270
			else:
				angle = 90
								
		if b == 0:
			if a >= 0:
				angle = 180
			else:					
				angle = 0
								
		if a!=0 and b!=0:
			if a>0 and b >0:
				angle = math.degrees(math.atan(b/a))+180.0
			if a>0 and b <0:
				angle = math.degrees(-abs(math.atan(b/a)))+180.0
			if a<0 and b >0:
				angle = math.degrees(-abs(math.atan(b/a)))+360.0
			if a<0 and b <0:
				angle = math.degrees(math.atan(b/a))
					
		AngleDict[nb[0]] = angle
		ROSAngleDir[angle] = None
		angle_to_nb[angle] = nb[0]
		FireProgress[nb[0]] = 0.0
		DistToCenter[nb[0]] = math.sqrt(a*a + b*b)

print("AdjCells:", AdjCells[CCell])
print("AngleDict:", AngleDict)
print("ROSAngleDir:", ROSAngleDir)
print("angle_to_nb:", angle_to_nb)
print("FireProgress:", FireProgress)
print("DistToCenter:", DistToCenter)

########################### ISOLATED CELL TEST ################################

################### CELLS CLASS TEST #############################
########################### INITIALIZATION ################################
# Initializing data for creating a new cell (object)
AreaCells = 100
VolCells = 100
AgeCells = 1 
TerrainCells = 0 
PerimeterCells = 0 
FTypes2 = {"m1":0, "m2":1,"m3":2,"m4":3,"c1":4,"c2":5,"c3":6,"c4":7,"c5":8,"c6":9,"c7":10,"d1":11,"s1":12,"s2":13,"s3":14,"o1a":15,"o1b":16,"d2":17}


FTypeCells = []
StatusCells = []
Colors = []
RealCells = []
cellcounter=1
			
for i in range(0,len(CellsGrid4)):
	if str.lower(CellsGrid4[i]) not in FTypes2.keys():
		FTypeCells.append(0)
		StatusCells.append(4)
		CellsGrid4[i] = "s1"
		RealCells.append(0)
	else:
		FTypeCells.append(2)
		StatusCells.append(0)
		RealCells.append(cellcounter)
		cellcounter+=1
		
	if str(CellsGrid3[i]) not in ColorsDict.keys():
		Colors.append((1.0,1.0,1.0,1.0))
				
	if 	str(CellsGrid3[i]) in ColorsDict.keys():
		Colors.append(ColorsDict[str(CellsGrid3[i])])
		
#Releasing memory
del CellsGrid3
del ColorsDict


# Create cell's object
Cells_Obj = [0 for i in range(0, len(CoordCells))]
print("Number of cells: ", len(Cells_Obj))

for Cell in range(0, len(Cells_Obj)):
	Cells_Obj[Cell] = CellsFBP.Cells(Cell+1,AreaCells,CoordCells[Cell],AgeCells,FTypeCells[Cell],
											coef_ptr[FTypes2[str.lower(CellsGrid4[Cell])]],TerrainCells,
											VolCells,PerimeterCells,StatusCells[Cell],AdjCells[Cell],Colors[Cell],
											RealCells[Cell])

########################### INITIALIZATION ################################
########################### NEW FUNCTIONS/FIELDS TEST ################################
											
# Check object (Cell number ID = Cell + 1)
Cell = 4
print("")
print("Cell object new fields (not populated)")
print("ID:",Cells_Obj[Cell].ID)
print("FireProgress:",Cells_Obj[Cell].FireProgress)
print("AngleDict:",Cells_Obj[Cell].AngleDict)
print("ROSAngleDir:",Cells_Obj[Cell].ROSAngleDir)
print("DistToCenter:",Cells_Obj[Cell].DistToCenter)
print("angle_to_nb:",Cells_Obj[Cell].angle_to_nb)

# Populate them
print("")
print("Initialize fire fields")
print("Adjacents:", Cells_Obj[Cell].Adjacents)
Cells_Obj[Cell].InitializeFireFields(CoordCells)
print("")
print("Cell object new fields")
print("ID:",Cells_Obj[Cell].ID)
print("FireProgress:",Cells_Obj[Cell].FireProgress)
print("AngleDict:",Cells_Obj[Cell].AngleDict)
print("ROSAngleDir:",Cells_Obj[Cell].ROSAngleDir)
print("DistToCenter:",Cells_Obj[Cell].DistToCenter)
print("angle_to_nb:",Cells_Obj[Cell].angle_to_nb)



########################### DF MODIFICATION ################################

print("")
print("")
print("-------------------------------- DF manipulation and ros_dist function inside cell object ------------------------------")
print("DF columns: ", DF.columns)
print("")
print("New DF: Changing WS, WAZ, SAZ - getting new RAZ and ROSs")
# Weather Object
InitialWeather = {"Wind_Speed": 30, "Wind_Direction": 25, "Temperature": 23, "DPoint": 8.4, "Rain": 0, "Radiation": 0, "RHumidity":0}
Weather_Obj = WeatherFBP.Weather(InitialWeather)

# New values
WindSpeed = [10]
WindDirection = [90]
Temperature = [10]
RHumidity = [1]
Precipitation = [0]
period = 0

print("Setting values: weather in DF")
print("WindSpeed:", WindSpeed[period],"[m/s]")
print("WindDirection:", WindDirection[period],"[degrees], East = 0 degrees, counter clockwise")


DF = Weather_Obj.update_Weather_FBPReadFile(period,DF,WindSpeed,
																	WindDirection,Temperature,
																	RHumidity,Precipitation,False)

# Check new FBP objects: main, head, flank, and back
mainstruct, headstruct, flankstruct, backstruct = ReadData.CalculateOne(DF,coef_ptr,Cell+1)
															
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

'''
NEW FUNCTION!!!!
'''
Cells_Obj[Cell].ros_distr(thetafire, forward, flank, back)
print("")
print("Cell object after calling ros_distr function")
print("ID:",Cells_Obj[Cell].ID)
print("ROSAngleDir:",Cells_Obj[Cell].ROSAngleDir)

