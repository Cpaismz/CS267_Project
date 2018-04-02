######################################################################################################################################
#
#                FireSimulator FBP serial and parallel version 1.0b - March 2017 
#                Author: Cristobal Pais modified by David L. Woodruff
#                example: mpiexec -n X python Path\Simulator1Beta.py  where X is the number of parallel processes
#
######################################################################################################################################
# modified Feb 2018 by DLW. Keeping FBP in the name because we may want to
# incorporate the crown rate in the probabilities.

# Importations
from __future__ import division
import sys
#import os
import math
from random import uniform

"""
We take these input parameters:

\begin{itemize}
\item SPOTANGLE: The angle over which spotting occurs, centered on the wind direction.
\item SPOT0PROB: The probability of ``spotting'' at distance zero. I.e., the probability that any brands will become airborne.
\item SPOT10TIME: The time (in seconds) at which there is still a ten percent chance of
  spotting.
\end{itemize}

For ease of locution, temporarily let $\beta \equiv$~SPOT0PROB and let
$\tilde{d} \equiv (w)$~(SPOT10TIME), which lets us define
$$
\alpha \equiv \frac{ln(.1)}{\tilde{d}} + \frac{ln(beta)}{\tilde{d}} 
$$

For any burning cell, the probability of spotting to a cell
outside the cone centered at the wind direction with
width SPOTANGLE degrees is zero. For other cells it is given
by
$$
\beta e^{\alpha d}
$$
where $d$ is the distance from the center of the burning cell
to the center of the other cell.
"""

# Full function
def SpottingFBP(Cells_Obj, CoordCells, AvailSet,WSD,WSC,SpotParms,verbose):
    """
    Manage spotting.
    Comments added by DLW Feb 2018 based on reading the code.
    Inputs:
        Cells_Obj: list of the cells objects; not sure what the list is
                   Maybe just burning cells?
        CoordCells: zero-based cell grid? grid Lat long (maybe elev some day) 
                    (A native speaker of
                    English would have named this CellCoords, BTW)
                    9 cell grid: [0,2], [1,2], [2,2], [0,1],...
                    Remember that cell one is NW 
        AvailSet: set of available cells
        WSD: wind direction
        WSC: wind speed
        SpotDict: dictionary with spotting control parameters (e.g., angle)
        verbose: boolean to control output
    Returns:
        MsgList: a list of cells that should received spotting ignition messages
    DLW Feb 2018 notes: this seems to have been written with Cells_Obj as a list
                        in mind, but it is a dictionary. It has integer keys
                        but the keys cannot be trusted to be contiguous.
                        Major re-write Feb 2018
    more notes: maybe we should base this on ROS or crown ROS or something
    """

    #Main arrays for spotting logic
    Angles = {} ##Angles = [[] for c in range(0,len(Cells_Obj))]
    Distances = {} ## = [[] for c in range(0,len(Cells_Obj))]
    SpotProb = {} ## [[] for c in range(0,len(Cells_Obj))]

    if SpotParms["SPOTANGLE"] * SpotParms["SPOT0PROB"] \
       * SpotParms["SPOT10TIME"] * WSC == 0:
        return []
    
    # changed to half on each side Feb 2018
    WTolerance = SpotParms["SPOTANGLE"] / 2.0

    print ("debug AvailSet=", AvailSet)
    
    #Wind thresholds
    WA = WSD-WTolerance
    WB = WSD+WTolerance
    
    if WSD - WTolerance >= 0 and WSD + WTolerance <=360:
        WWindowA =  WSD - WTolerance
        WWindowB =  WSD + WTolerance
        
    if WSD - WTolerance < 0 and WSD + WTolerance <=360:
        WWindowA =  360 + (WSD - WTolerance)
        WWindowB =  WSD + WTolerance
    
    if WSD - WTolerance >= 0 and WSD + WTolerance > 360:
        WWindowA =  WSD - WTolerance
        WWindowB =  WSD + WTolerance - 360
    
    if WSD - WTolerance < 0 and WSD + WTolerance > 360:
        WWindowA =  360 + (WSD - WTolerance)
        WWindowB =  WSD + WTolerance - 360
    
    if verbose == True:
        print "Wind Direction:",WSD
        print "Wind Speed:", WSC
        print "Spotting Wind Windows:","[",WA,",",WB,"]"

    print "debug obj keys"
    for foobar in Cells_Obj.keys():
        print foobar
    print "debug AvailSet",AvailSet
    print "Debug CoordCells=", CoordCells

    #Angles and distances
    # c1 is from Cells_obj (zero-based?) and c2 is from a set (one-based)
    for c1 in Cells_Obj.keys():
        Angles[c1] = {}
        Distances[c1] = {}
        for c2 in AvailSet:
            if c1 == c2:
                Angles[c1][c2] = None
                Distances[c1][c2] = None
            else:
                a = CoordCells[c1][0] - CoordCells[c2-1][0]
                b = CoordCells[c1][1] - CoordCells[c2-1][1]

                if a == 0:
                    if b>=0:
                        Angles[c1][c2] = 270
                        Distances[c1][c2] = abs(b)
                        #print "a,b:",a,b
                        #print Angles,"\n",Distances,"\n"
                    else:
                        Angles[c1][c2] = 90
                        Distances[c1][c2] = abs(b)
                        #print "a,b:",a,b
                        #print Angles,"\n",Distances,"\n"
                if b == 0:
                    if a >= 0:
                        Angles[c1][c2] = 180
                        Distances[c1][c2] = abs(a)
                        #print "a,b:",a,b
                        #print Angles,"\n",Distances,"\n"
                    else:                    
                        Angles[c1][c2] = 0
                        Distances[c1][c2] = abs(a)
                        #print "a,b:",a,b
                        #print Angles,"\n",Distances,"\n"

                if a!=0 and b!=0:
                    #print "a,b,degree",a,b,math.degrees(math.atan(b/a))

                    if a>0 and b >0:
                        Angles[c1][c2] = math.degrees(math.atan(b/a))+180.0
                        Distances[c1][c2] = math.sqrt(math.pow(a,2)+math.pow(b,2))
                    if a>0 and b <0:
                        Angles[c1][c2] = math.degrees(-abs(math.atan(b/a)))+180.0
                        Distances[c1][c2] = math.sqrt(math.pow(a,2)+math.pow(b,2))
                    if a<0 and b >0:
                        Angles[c1][c2] = math.degrees(-abs(math.atan(b/a)))+360.0
                        Distances[c1][c2] = math.sqrt(math.pow(a,2)+math.pow(b,2))
                    if a<0 and b <0:
                        Angles[c1][c2] = math.degrees(math.atan(b/a))
                        Distances[c1][c2] = math.sqrt(math.pow(a,2)+math.pow(b,2))
    
    if verbose == True:
        print "Angles for spotting:",Angles
        print "\nDistances:",Distances
        print ""

    #Probabilities
    cellsize = Cells_Obj[c1].Perimeter / 4. # meters per grid cell
    beta = SpotParms["SPOT0PROB"]
    tilde_d = SpotParms["SPOT10TIME"] * WSC / cellsize   # units are "grid cells
    alpha = math.log(.1)/tilde_d + math.log(beta) /  tilde_d

    for c1 in Cells_Obj.keys():
        SpotProb[c1] = {}
        for c2 in AvailSet:
                
            if Angles[c1][c2] == None:
                SpotProb[c1][c2] = 0
            
            else:
                if Angles[c1][c2] != None and WTolerance >=180:
                    SpotProb[c1][c2] = beta * math.exp(-Distances[c1][c2] * alpha)
                        
                else:            
                    if WA>=0 and WB>=0 and WA<360 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB and  Angles[c1][c2] >= WA:
                            SpotProb[c1][c2] = beta * math.exp(-Distances[c1][c2] * alpha)
                        
                        else:
                            SpotProb[c1][c2] = 0
                            
                    if WA>=0 and WB>=0 and WA<360 and WB>=360 and WTolerance<180:
                        if Angles[c1][c2] <= WB-360 and  Angles[c1][c2] >= WA:
                            SpotProb[c1][c2] = beta * math.exp(-Distances[c1][c2] * alpha)
                        
                        else:
                            SpotProb[c1][c2] = 0
                    
                    if WA<0 and WB>=0 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB or Angles[c1][c2] >= WA+360:
                            SpotProb[c1][c2] = beta * math.exp(-Distances[c1][c2] * alpha)
                        
                        else:
                            SpotProb[c1][c2] = 0
    if verbose == True:                
        print "Probabilities:",SpotProb                

    #Send messages
    # keys are mixed zero- and one-based!?!? (sort of DLW's fault)
    msg_list = []
    for c1 in SpotProb.keys():
        for c2 in SpotProb[c1].keys():
            # left side of and is to save the call to Uniform
            if SpotProb[c1][c2] > 0 and SpotProb[c1][c2] < uniform(0,1):
                if verbose:
                    print "Spotting Message sent from", c1+1, " to", c2
                msg_list.append(c2)
         
    # to allow a push????
    return msg_list

