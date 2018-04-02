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
#from random import randint,uniform
#from math import exp,pow
#from itertools import repeat
#from mpi4py import MPI
#import time
import imread
#from subprocess import call

#Visual importations
from matplotlib.pylab import *
import matplotlib as mpl
import matplotlib.cm as cm
import matplotlib.patches as patches
import itertools
import numpy as np
from matplotlib.colors import LinearSegmentedColormap

# Plot class: All methods neede for plotting the forest status	
class Plot:
	def PlotForestOnly(self,Colors,Coords,counter,period,Year,showtrue,r,col,Folder):
		#Max and min status values
		min_val = 0
		max_val = 2

		#RGB DE BARRA QUE QUIERO
		#C=[0,160,0, 226,158,52, 255,23,31]
		#cm = mpl.colors.ListedColormap(C/255)

		#Colorbar dictionary
		cdict1 = {'red':   ((0.0, 0.0, 0.0),(0.0, 0.0, 0.1),(1.0, 1.0, 1.0)),
				 'green':  ((0.0, 0.0, 0.6),(1.0, 0.0, 0.0),(1.0, 0.0, 0.0)),
				 'blue':   ((0.0, 0.0, 0.0),(1.0, 0.1, 0.0),(1.0, 0.0, 0.0))
				}
				
		green_red = LinearSegmentedColormap('GreenRed', cdict1)
		plt.register_cmap(cmap=green_red)

		my_cmap = cm.get_cmap(green_red) # or any other one
		norm = matplotlib.colors.Normalize(min_val, max_val) # the color maps work for [0, 1]

		#Colours' definitions (status)
		# Available: Green 
		x_i = 0
		color_i = my_cmap(norm(x_i)) # returns an rgba value
	
		# Burnt: Orange
		x_i2 = 1
		color_i2 = my_cmap(norm(x_i2)) # returns an rgba value
		# Burning: Red and different levels depending on the period (decay factor)
		x_i3 = 2
		color_i3 = my_cmap(norm(x_i3)) # returns an rgba value
		x_i32 = 1.8
		color_i32 = my_cmap(norm(x_i32)) # returns an rgba value
		x_i33 = 1.6
		color_i33 = my_cmap(norm(x_i33)) # returns an rgba value
		x_i34 = 1.4
		color_i34 = my_cmap(norm(x_i34)) # returns an rgba value
		x_i35 = 1.2
		color_i35 = my_cmap(norm(x_i35)) # returns an rgba value
		# Harvested: green/orange
		x_i4 = 0.6
		color_i4 = my_cmap(norm(x_i4)) # returns an rgba value
		
		cmmapable = cm.ScalarMappable(norm, my_cmap)
		cmmapable.set_array(range(min_val, max_val))

		#Scatter data
		#print "Rows:",r
		#print "Cols:",col
		c = col
		#r = 3 
		#c = 3
		x = np.linspace(0, c, c+1)
		y = np.linspace(0, r, r+1)
		pts = itertools.product(x, y)

		#Initializing figures
		figure()
		ax = gca()

		#Markers
		#ax.scatter(*zip(*pts), marker='o', s=30, color='red', zorder=2)

		#Rectangle
		#fillcolor='g'
		fillcolor=color_i
		edgecolor="None"#'k'
		lwidth=1.0
		
		rectangle = []
		
		for c in range(0,len(Colors)):
				rectangle.append(plt.Rectangle((Coords[c][0], Coords[c][1]), 1, 1, fc=Colors[c],ec=edgecolor,linewidth=lwidth))
		for i in range(0,len(Colors)):
			ax.add_patch(rectangle[i])

		#ax.add_patch(rect)
		#ax.add_patch(rect2)

		#Grid
		#plt.grid()

		#Title
		#plt.title('Fire simulation Year '+str(Year) +' period '+str(period))
		plt.title(".",color="white")
		plt.axis('scaled')

		#Arrows
		#plt.quiver(x, y , size, angle, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=3)
		#QP = plt.quiver(2.0,1 ,5, 0, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=0)
		
		XCoord = None
		YCoord = None
		
		#Path and name o the file
		PathFile = os.path.join(Folder, "ForestInitial.png")
		#plt.axis('off')
		
		#Save the file
		#plt.savefig('C:/Users/Cris/Desktop/forest1.png', dpi=90, bbox_inches='tight')
		#gca().set_axis_off()
		#subplots_adjust(top = 1, bottom = 0, right = 1, left = 0, 
		#			hspace = 0, wspace = 0)
		#margins(0,0)
		#gca().xaxis.set_major_locator(NullLocator())
		#gca().yaxis.set_major_locator(NullLocator())
		plt.savefig(PathFile,dpi=200, bbox_inches='tight')#,pad_inches=0)
		plt.close("all")
		
		if showtrue == True:
			show()						
			
	def forest_plotV3(self,Cells_Obj,msg_list,counter,period,Year,showtrue,r,col,Folder,Sim):
		#Max and min status values
		min_val = 0
		max_val = 2

		#RGB DE BARRA QUE QUIERO
		#C=[0,160,0, 226,158,52, 255,23,31]
		#cm = mpl.colors.ListedColormap(C/255)

		#Colorbar dictionary
		cdict1 = {'red':   ((0.0, 0.0, 0.0),(0.0, 0.0, 0.1),(1.0, 1.0, 1.0)),
				 'green':  ((0.0, 0.0, 0.6),(1.0, 0.0, 0.0),(1.0, 0.0, 0.0)),
				 'blue':   ((0.0, 0.0, 0.0),(1.0, 0.1, 0.0),(1.0, 0.0, 0.0))
				}
				
		green_red = LinearSegmentedColormap('GreenRed', cdict1)
		plt.register_cmap(cmap=green_red)

		my_cmap = cm.get_cmap(green_red) # or any other one
		norm = matplotlib.colors.Normalize(min_val, max_val) # the color maps work for [0, 1]

		#Colours' definitions (status)
		# Available: Green 
		x_i = 0
		color_i = my_cmap(norm(x_i)) # returns an rgba value
	
		# Burnt: Orange
		x_i2 = 1
		color_i2 = my_cmap(norm(x_i2)) # returns an rgba value
		# Burning: Red and different levels depending on the period (decay factor)
		x_i3 = 2
		color_i3 = my_cmap(norm(x_i3)) # returns an rgba value
		x_i32 = 1.8
		color_i32 = my_cmap(norm(x_i32)) # returns an rgba value
		x_i33 = 1.6
		color_i33 = my_cmap(norm(x_i33)) # returns an rgba value
		x_i34 = 1.4
		color_i34 = my_cmap(norm(x_i34)) # returns an rgba value
		x_i35 = 1.2
		color_i35 = my_cmap(norm(x_i35)) # returns an rgba value
		# Harvested: green/orange
		x_i4 = 0.6
		color_i4 = my_cmap(norm(x_i4)) # returns an rgba value
		
		#Determining cells' colors
		for c in Cells_Obj.keys():
			# if cell is burning, depending on the number of periods, red tends to be orange
			if Cells_Obj[c].Status == 1:
				#First burning period
				if Cells_Obj[c].Firestarts == period:	
					Cells_Obj[c].Color = color_i3
				#Second burning period
				if Cells_Obj[c].Firestarts == (period-1):	
					Cells_Obj[c].Color = color_i32
				#Third burning period
				if Cells_Obj[c].Firestarts == (period-2):	
					Cells_Obj[c].Color = color_i33
				#Fourth burning period
				if Cells_Obj[c].Firestarts == (period-3):	
					Cells_Obj[c].Color = color_i34
				#Fifth burning period
				if Cells_Obj[c].Firestarts == (period-4):	
					Cells_Obj[c].Color = color_i35
				#More burning periods
				if Cells_Obj[c].Firestarts < (period-4):	
					Cells_Obj[c].Color = color_i2
					
			# if cell is burnt (but not burning), orange (cuidado con el numero, esta puesto estado harvested)
			elif Cells_Obj[c].Status == 2:
				Cells_Obj[c].Color = color_i2
			
			# if cell is harvested, different green
			elif Cells_Obj[c].Status == 3:
				Cells_Obj[c].Color = color_i4
			
		cmmapable = cm.ScalarMappable(norm, my_cmap)
		cmmapable.set_array(range(min_val, max_val))

		#Scatter data
		#print "Rows:",r
		#print "Cols:",col
		c = col
		#r = 3 
		#c = 3
		x = np.linspace(0, c, c+1)
		y = np.linspace(0, r, r+1)
		pts = itertools.product(x, y)

		#Initializing figures
		figure()
		ax = gca()

		#Markers
		#ax.scatter(*zip(*pts), marker='o', s=30, color='red', zorder=2)

		#Rectangle
		#fillcolor='g'
		fillcolor=color_i
		edgecolor="None"#'k'
		lwidth=1.0
		
		rectangle = []
		rectangle.append(plt.Rectangle((0, r-1), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		rectangle.append(plt.Rectangle((0, 0), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		rectangle.append(plt.Rectangle((c-1, r-1), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		rectangle.append(plt.Rectangle((c-1, 0), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		
		
		for c in Cells_Obj.keys():
			if Cells_Obj[c].Status != "Available":
				rectangle.append(plt.Rectangle((Cells_Obj[c].Coord[0], Cells_Obj[c].Coord[1]), 1, 1, fc=Cells_Obj[c].Color,ec=edgecolor,linewidth=lwidth))
		
		
		for i in range(0,len(rectangle)):
			ax.add_patch(rectangle[i])
		
			
		#ax.add_patch(rect)
		#ax.add_patch(rect2)

		#Grid
		#plt.grid()

		#Title
		plt.title('Fire simulation Year '+str(Year) +' period '+str(period))
		plt.axis('scaled')

		#Arrows
		#plt.quiver(x, y , size, angle, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=3)
		#QP = plt.quiver(2.0,1 ,5, 0, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=0)
		
		XCoord = None
		YCoord = None
		#print Cells_Obj
		for cell in Cells_Obj.keys():
			#print "Messages of cell",cell,":",msg_list[cell]
			for adj in msg_list[cell]:
					XCoord = Cells_Obj[adj-1].Coord[0] - Cells_Obj[cell].Coord[0]
					YCoord = Cells_Obj[adj-1].Coord[1] - Cells_Obj[cell].Coord[1]
		
					#print "Cell adj:",adj," XCoord:",XCoord," YCoord:",YCoord
				
					if XCoord > 0:
						u = XCoord
					elif XCoord == 0:
						u = XCoord
					elif XCoord < 0:
						u = XCoord
						
					if YCoord > 0:
						v = YCoord
					elif YCoord == 0:
						v = YCoord
					elif YCoord < 0:
						v = YCoord
		
					# Plot
					plt.quiver(Cells_Obj[cell].Coord[0]+0.5+0.4*u,Cells_Obj[cell].Coord[1]+0.5+0.4*v ,u,v, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=3)
		
		#Legend
		#k = plt.quiverkey(QP,0.65, 0.92, 5, r'$Fire\_message\_direction \hspace{0.5} \theta$', labelpos='W',
			#			   fontproperties={'weight': 'bold'},zorder=4)
		
		#Put a colorbar
		#colorbar(cmmapable)

		
		Folder = os.path.join(Folder, "Plots"+str(Sim))
		if not os.path.exists(Folder):
			os.makedirs(Folder)
		fstr = str(counter).zfill(4)
		PathFile = os.path.join(Folder,"forest"+fstr+".png")
		#Path and name o the file
                """
		if counter<10:
			PathFile = Folder+"forest000"+str(counter)+".png"
		if counter>=10 and counter<100:
			PathFile = Folder+"forest00"+str(counter)+".png"
		if counter>=100 and counter<1000:
			PathFile = Folder+"forest0"+str(counter)+".png"
		if counter>=1000 and counter<10000:
			PathFile = Folder+"forest"+str(counter)+".png"
		"""
		#Save the file
		#plt.savefig('C:/Users/Cris/Desktop/forest1.png', dpi=90, bbox_inches='tight')
		plt.savefig(PathFile, dpi=200, figsize=(200, 200), bbox_inches='tight', transparent=True)
		plt.close("all")
		
		if showtrue == True:
			show()		
	
	def forest_plotV3_FreeMem(self,Cells_Obj,msg_list,counter,period,Year,showtrue,r,col,Folder,Coords,BurntCells,Sim):
		#Max and min status values
		min_val = 0
		max_val = 2

		#RGB DE BARRA QUE QUIERO
		#C=[0,160,0, 226,158,52, 255,23,31]
		#cm = mpl.colors.ListedColormap(C/255)

		#Colorbar dictionary
		cdict1 = {'red':   ((0.0, 0.0, 0.0),(0.0, 0.0, 0.1),(1.0, 1.0, 1.0)),
				 'green':  ((0.0, 0.0, 0.6),(1.0, 0.0, 0.0),(1.0, 0.0, 0.0)),
				 'blue':   ((0.0, 0.0, 0.0),(1.0, 0.1, 0.0),(1.0, 0.0, 0.0))
				}
				
		green_red = LinearSegmentedColormap('GreenRed', cdict1)
		plt.register_cmap(cmap=green_red)

		my_cmap = cm.get_cmap(green_red) # or any other one
		norm = matplotlib.colors.Normalize(min_val, max_val) # the color maps work for [0, 1]

		#Colours' definitions (status)
		# Available: Green 
		x_i = 0
		color_i = my_cmap(norm(x_i)) # returns an rgba value
	
		# Burnt: Orange
		x_i2 = 1
		color_i2 = my_cmap(norm(x_i2)) # returns an rgba value
		# Burning: Red and different levels depending on the period (decay factor)
		x_i3 = 2
		color_i3 = my_cmap(norm(x_i3)) # returns an rgba value
		x_i32 = 1.8
		color_i32 = my_cmap(norm(x_i32)) # returns an rgba value
		x_i33 = 1.6
		color_i33 = my_cmap(norm(x_i33)) # returns an rgba value
		x_i34 = 1.4
		color_i34 = my_cmap(norm(x_i34)) # returns an rgba value
		x_i35 = 1.2
		color_i35 = my_cmap(norm(x_i35)) # returns an rgba value
		# Harvested: green/orange
		x_i4 = 0.6
		color_i4 = my_cmap(norm(x_i4)) # returns an rgba value
		
		#Determining cells' colors
		for c in Cells_Obj.keys():
			# if cell is burning, depending on the number of periods, red tends to be orange
			if Cells_Obj[c].Status == 1:
				#First burning period
				if Cells_Obj[c].Firestarts == period:	
					Cells_Obj[c].Color = color_i3
				#Second burning period
				if Cells_Obj[c].Firestarts == (period-1):	
					Cells_Obj[c].Color = color_i32
				#Third burning period
				if Cells_Obj[c].Firestarts == (period-2):	
					Cells_Obj[c].Color = color_i33
				#Fourth burning period
				if Cells_Obj[c].Firestarts == (period-3):	
					Cells_Obj[c].Color = color_i34
				#Fifth burning period
				if Cells_Obj[c].Firestarts == (period-4):	
					Cells_Obj[c].Color = color_i35
				#More burning periods
				if Cells_Obj[c].Firestarts < (period-4):	
					Cells_Obj[c].Color = color_i2
					
			# if cell is burnt (but not burning), orange (cuidado con el numero, esta puesto estado harvested)
			elif Cells_Obj[c].Status == 2:
				Cells_Obj[c].Color = color_i2
			
			# if cell is harvested, different green
			elif Cells_Obj[c].Status == 3:
				Cells_Obj[c].Color = color_i4
		
		cmmapable = cm.ScalarMappable(norm, my_cmap)
		cmmapable.set_array(range(min_val, max_val))

		#Scatter data
		#print "Rows:",r
		#print "Cols:",col
		c = col
		#r = 3 
		#c = 3
		x = np.linspace(0, c, c+1)
		y = np.linspace(0, r, r+1)
		pts = itertools.product(x, y)

		#Initializing figures
		figure()
		ax = gca()

		#Markers
		#ax.scatter(*zip(*pts), marker='o', s=30, color='red', zorder=2)

		#Rectangle
		#fillcolor='g'
		fillcolor=color_i
		edgecolor="None"#'k'
		lwidth=1.0
		
		rectangle = []
		rectangle.append(plt.Rectangle((0, r-1), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		rectangle.append(plt.Rectangle((0, 0), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		rectangle.append(plt.Rectangle((c-1, r-1), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		rectangle.append(plt.Rectangle((c-1, 0), 1, 1, fc=(1.0,1.0,1.0,0.0),ec=edgecolor,linewidth=lwidth))
		
		
		for c in Cells_Obj.keys():
			if Cells_Obj[c].Status != "Available":
				rectangle.append(plt.Rectangle((Cells_Obj[c].Coord[0], Cells_Obj[c].Coord[1]), 1, 1, fc=Cells_Obj[c].Color,ec=edgecolor,linewidth=lwidth))
		
		for c in BurntCells:
			if (c-1) not in Cells_Obj.keys():
				rectangle.append(plt.Rectangle((Coords[c-1][0], Coords[c-1][1]), 1, 1, fc=color_i2,ec=edgecolor,linewidth=lwidth))
		
		for i in range(0,len(rectangle)):
			ax.add_patch(rectangle[i])
		
			
		#ax.add_patch(rect)
		#ax.add_patch(rect2)

		#Grid
		#plt.grid()

		#Title
		plt.title('Fire simulation Year '+str(Year) +' period '+str(period))
		plt.axis('scaled')

		#Arrows
		#plt.quiver(x, y , size, angle, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=3)
		#QP = plt.quiver(2.0,1 ,5, 0, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=0)
		
		XCoord = None
		YCoord = None
		#print Cells_Obj
		for cell in Cells_Obj.keys():
			#print "Messages of cell",cell,":",msg_list[cell]
			for adj in msg_list[cell]:
					XCoord = Cells_Obj[adj-1].Coord[0] - Cells_Obj[cell].Coord[0]
					YCoord = Cells_Obj[adj-1].Coord[1] - Cells_Obj[cell].Coord[1]
		
					#print "Cell adj:",adj," XCoord:",XCoord," YCoord:",YCoord
				
					if XCoord > 0:
						u = XCoord
					elif XCoord == 0:
						u = XCoord
					elif XCoord < 0:
						u = XCoord
						
					if YCoord > 0:
						v = YCoord
					elif YCoord == 0:
						v = YCoord
					elif YCoord < 0:
						v = YCoord
		
					# Plot
					plt.quiver(Cells_Obj[cell].Coord[0]+0.5+0.4*u,Cells_Obj[cell].Coord[1]+0.5+0.4*v ,u,v, color='r', units='x',linewidths=(2,), edgecolors=('k'), headaxislength=5,zorder=3)
		
		#Legend
		#k = plt.quiverkey(QP,0.65, 0.92, 5, r'$Fire\_message\_direction \hspace{0.5} \theta$', labelpos='W',
			#			   fontproperties={'weight': 'bold'},zorder=4)
		
		#Put a colorbar
		#colorbar(cmmapable)
		
		Folder = os.path.join(Folder, "Plots"+str(Sim))
		if not os.path.exists(Folder):
			os.makedirs(Folder)
		fstr = str(counter).zfill(4)
		PathFile = os.path.join(Folder,"forest"+fstr+".png")
                """
		#Path and name o the file
		if counter<10:
			PathFile = Folder+"forest000"+str(counter)+".png"
		if counter>=10 and counter<100:
			PathFile = Folder+"forest00"+str(counter)+".png"
		if counter>=100 and counter<1000:
			PathFile = Folder+"forest0"+str(counter)+".png"
		if counter>=1000 and counter<10000:
			PathFile = Folder+"forest"+str(counter)+".png"
		"""
		#Save the file
		#plt.savefig('C:/Users/Cris/Desktop/forest1.png', dpi=90, bbox_inches='tight')
		plt.savefig(PathFile, dpi=200, figsize=(200, 200), bbox_inches='tight', transparent=True)
		plt.close("all")
		
		if showtrue == True:
			show()		
	
	def Mix(self,Folder,filen,Sim):
		img = imread(os.path.join(Folder, "ForestInitial.png"))
		fstr = str(filen).zfill(4)
		#Path and name o the file
	        PathFile = os.path.join(Folder, "Plots", "Plots"+str(Sim), "forest"+fstr+".png")
                """
		if filen<10:
		if filen>=10 and filen<100:
			PathFile = Folder+"\\Plots\\Plots"+str(Sim)+"\\forest00"+str(filen)+".png"
		if filen>=100 and filen<1000:
			PathFile =  Folder+"\\Plots\\Plots"+str(Sim)+"\\forest0"+str(filen)+".png"
		if filen>=1000 and filen<10000:
			PathFile =  Folder+"\\Plots\\Plots"+str(Sim)+"\\forest"+str(filen)+".png"
		"""		
		img2 = imread(PathFile)
		
		gca().set_axis_off()
		subplots_adjust(top = 1, bottom = 0, right = 1, left = 0, 
					hspace = 0, wspace = 0)
		margins(0,0)
		gca().xaxis.set_major_locator(NullLocator())
		gca().yaxis.set_major_locator(NullLocator())
		
		plt.imshow(img,zorder=0)
		plt.imshow(img2,zorder=1)
		plt.savefig(PathFile, dpi=200, bbox_inches='tight', pad_inches=0)
		plt.close("all")
	
