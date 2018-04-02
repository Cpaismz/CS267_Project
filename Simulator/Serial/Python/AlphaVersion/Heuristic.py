#Template para clase Heuristics
import math 
import pandas as pd

# Reads the csv file "ForestDetails.csv" with prices and volume associated to each cell per period, based on growth model
def ReadForest(Folder,Year):
	aux = 1
	filename = Folder + "ForestDetails.csv"
	file = open(filename, "r") 
		
	Utility = {}
	Volume = {} 
		
	# Read file and return the Utility and Volume per cells, for the selected Year
	for line in file: 
		if aux >1:
			aux +=1
			line = line.replace("\n","")
			line = line.split(",")
			
			if int(line[6]) == Year:
				Utility[int(line[0])] = float(line[4])
				Volume[int(line[0])] = float(line[6])
						
		if aux == 1:
			aux +=1

### Heuristics Template ###
# Selects the heuristic and returns the Harvested Cells for the current period
def Heuristics(type,AvailSet,BurntSet,Period,Folder,DemandArray):
	# Global variables/parameters
	HarvestedCells = set()
	TotalDemand = 0
	TotalUtility = 0
	
	
	
	# Calling nth heuristic
	if type == n:
		#############
		#  Heuristic Logic   #
		#############
		
	

	return HarvestedCells,TotalDemand,TotalUtility