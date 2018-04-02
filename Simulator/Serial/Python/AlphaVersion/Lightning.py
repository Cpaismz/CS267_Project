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
from random import randint,uniform
from math import exp,pow
#from itertools import repeat
#from mpi4py import MPI
#import time
#from subprocess import call

#Visual importations
#from matplotlib.pylab import *
#import matplotlib.cm as cm
#import matplotlib.patches as patches
#import itertools
#import numpy as np
#from matplotlib.colors import LinearSegmentedColormap

# Lightning Class: Fire ignition class, determines the week when fire starts, based on a poisson strike	
class Lightning:	
	PoissonRate = None
	
	def Lambda_Simple_Test(self,period):
		#Returns true if a fire starts in a particular week of the fire season
		Selected_Week = randint(1, 12)
		return Selected_Week
	
	def Lambda_NH(self,period,verbose):
		#Returns the probability of having a fire in a week of the fire season
		Fire_Rate = 0.5
		AlfaFact = 0.1
		Poisson_Mean = (Fire_Rate/2.0)*(2.0+AlfaFact*(pow(period,2)-pow((period-1),2)-2.0))
		ProbsNoFire = round(exp(-Poisson_Mean),2)
		if verbose == True:
			print "Probs of not fire (week "+str(period)+"): "+str(ProbsNoFire)
		
		if round(uniform(0,1),2) > ProbsNoFire:
			return True
		else:
			return False
			
	def Lambda_H(self,period,verbose):
		#Returns the probability of having a fire in a week of the fire season
		Poisson_Mean = 0.5
		ProbsNoFire = round(exp(-Poisson_Mean),2)
		if verbose == True:
			print "Probs of not fire (week "+str(period)+"): "+str(ProbsNoFire)
			
		if round(uniform(0,1),2) > ProbsNoFire:
			return True
		else:
			return False