######################################################################################################################################
#
#				FireSimulator serial and parallel version 1.0b - January 2016 
#				Author: Cristobal Pais
#				example: mpiexec -n X python Path\Simulator1Beta.py  where X is the number of parallel processes
#
######################################################################################################################################

# Importations
import sys
import os
from random import randint,uniform
from math import exp,pow
from itertools import repeat
from mpi4py import MPI
import time
from subprocess import call

#Visual importations
from matplotlib.pylab import *
import matplotlib.cm as cm
import matplotlib.patches as patches
import itertools
import numpy as np
from matplotlib.colors import LinearSegmentedColormap


# Forest Class: defining the main parameters of the instance including ID (int), Location (String), Coordinates (Lat & Long, double list), NCells (int), Area (double), Vol (double), Age (double), Perimeter (double) types of trees (dictionary)
class Forest:
	#Basic parameters
	#CellsDistance = {1: [distancias], 2: [distancias]} , podria hacerse con numpy estilo matriz clasica y se soluciona el problema de tratarlo como listas anidadas
	
	def __init__(self,ID,Location,Coord,NCells,Area,Vol,Age,Perimeter,FTypes):
		#Constructor
		self.ID = ID
		self.Location = Location
		self.Coord = Coord
		self.NCells = NCells
		self.Area = Area
		self.Vol = Vol
		self.Age = Age
		self.FTypes = FTypes
		
		self.CellsDistance = {}
		self.AvailCells = []
		self.AvailCells.append(list(range(1,self.NCells+1)))
		self.BurntCells = list()
		
	def set_AvailCells(period,AvailCells_set):
		#AvailCells list takes the value from the actual AvailCells set (global set)
		self.AvailCells[period] = AvailCells.insert((period) ,list(AvailCells_set))
		return AvailCells
		
	def set_BurntCells(period,BurntCells_set):
		#BurntCells list takes the value from the actual BurntCells set (global set)
		self.BurntCells[period] = BurntCells.insert((period) ,list(BurntCells_set))
		return BurntCells
		
	def print_info(self):
		print "Forest Information" + "\n" +" ID = " + str(self.ID) + "\n" + " Location = "+ str(self.Location)+ "\n"+ " Coordinates = " +str(self.Coord)+ "\n" +" NCells = " +str(self.NCells)+"\n"+" Area = "+str(self.Area)+"\n"+" Vol = "+str(self.Vol)+"\n" + " Age = "+ str(self.Age)+"\n"+ " FTypes = "+ str(self.FTypes)
		