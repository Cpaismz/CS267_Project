######################################################################################################################################
#
#				FireSimulator serial and parallel version 1.0b - January 2016 
#				Author: Cristobal Pais
#				example: mpiexec -n X python Path\Simulator1Beta.py  where X is the number of parallel processes
#
######################################################################################################################################

# Importations
#import sys
#import os
#from random import randint,uniform
from math import exp,pow
#from itertools import repeat
#import time
from mpi4py import MPI
#from subprocess import call

#Visual importations
#from matplotlib.pylab import *
#import matplotlib.cm as cm
#import matplotlib.patches as patches
#import itertools
#import numpy as np
#from matplotlib.colors import LinearSegmentedColormap

# Parallel Class: All methods and functions needed to run the simulator in parallel	
class Parallel:
	def processes_per_worker(self,size,works,verbose):
	#Important method: based on the size of the MPI environment (number of processes) and number of jobs, assigns them
	#in a balanced way. It returns a list with the number of works to be processed in each worker
	#Number of processes per worker
		Total_Processes_list = [0 for i in range(0,size)]
		if works%size==0:
			if verbose == True:
				print ""
				print "Equal number of jobs per worker"
			jobs = works/size
			if verbose == True:
				print "Jobs per worker: ",jobs
				
			for i in range(0,size):
				Total_Processes_list[i] = jobs

		else:
			jobs = works/size
			if verbose == True:
				print ""
				print "Not equal number of jobs per worker"
							
			for i in range(0,size):
				Total_Processes_list[i] = jobs
					
			Difference = works - (jobs*size)
							
			# 0 if I want master to be the first in the line, 1 for first worker
			for i in range(0,size):			
				if Difference==0:
					break
				else:
					Total_Processes_list[i]+=1
					Difference-=1
						
			if verbose == True:
				print "Jobs per worker: ",Total_Processes_list
		return Total_Processes_list	