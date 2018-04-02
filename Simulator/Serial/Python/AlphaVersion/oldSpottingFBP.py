######################################################################################################################################
#
#                FireSimulator FBP serial and parallel version 1.0b - March 2017 
#                Author: Cristobal Pais
#                example: mpiexec -n X python Path\Simulator1Beta.py  where X is the number of parallel processes
#
######################################################################################################################################

# Importations
from __future__ import division
import sys
#import os
import math
from random import uniform

# Angles and distances arrays
def AnglesDistSpot(Cells_Obj):
    Angles = [[] for c in range(0,len(Cells_Obj))]
    Distances = [[] for c in range(0,len(Cells_Obj))]

    #Angles and distances
    for c1 in range(0,len(Cells_Obj)):
        for c2 in range(0,len(Cells_Obj)):
            if c1 <= len(Cells_Obj):
                #break
                if c1 == c2:
                    Angles[c1].append(None)
                    Distances[c1].append(None)
                else:
                    a = Cells_Obj[c1].Coord[0] - Cells_Obj[c2].Coord[0]
                    b = Cells_Obj[c1].Coord[1] - Cells_Obj[c2].Coord[1]
                    
                    if a == 0:
                        if b>=0:
                            Angles[c1].append(270)
                            Distances[c1].append(abs(b))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                        else:
                            Angles[c1].append(90)
                            Distances[c1].append(abs(b))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                    if b == 0:
                        if a >= 0:
                            Angles[c1].append(180)
                            Distances[c1].append(abs(a))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                        else:                    
                            Angles[c1].append(0)
                            Distances[c1].append(abs(a))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                            
                    if a!=0 and b!=0:
                        #print "a,b,degree",a,b,math.degrees(math.atan(b/a))
                        
                        if a>0 and b >0:
                            Angles[c1].append(math.degrees(math.atan(b/a))+180.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a>0 and b <0:
                            Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+180.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a<0 and b >0:
                            Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+360.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a<0 and b <0:
                            Angles[c1].append(math.degrees(math.atan(b/a)))
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
    
    return Angles,Distances

def AnglesDistSpot_12JULIO(Coord):
    Angles = [[] for c in range(0,len(Coord))]
    Distances = [[] for c in range(0,len(Coord))]

    #Angles and distances
    for c1 in range(0,len(Coord)):
        for c2 in range(0,len(Coord)):
            if c1 <= len(Coord):
                #break
                if c1 == c2:
                    Angles[c1].append(None)
                    Distances[c1].append(None)
                else:
                    a = Coord[c1][0] - Coord[c2][0]
                    b = Coord[c1][1] - Coord[c2][1]
                    
                    if a == 0:
                        if b>=0:
                            Angles[c1].append(270)
                            Distances[c1].append(abs(b))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                        else:
                            Angles[c1].append(90)
                            Distances[c1].append(abs(b))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                    if b == 0:
                        if a >= 0:
                            Angles[c1].append(180)
                            Distances[c1].append(abs(a))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                        else:                    
                            Angles[c1].append(0)
                            Distances[c1].append(abs(a))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                            
                    if a!=0 and b!=0:
                        #print "a,b,degree",a,b,math.degrees(math.atan(b/a))
                        
                        if a>0 and b >0:
                            Angles[c1].append(math.degrees(math.atan(b/a))+180.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a>0 and b <0:
                            Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+180.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a<0 and b >0:
                            Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+360.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a<0 and b <0:
                            Angles[c1].append(math.degrees(math.atan(b/a)))
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
    
    return Angles,Distances

def AnglesDistSpot_03Aug_Ind(Coord,c1):
    Angles = {}
    Angles[c1] = []
    
    Distances = {}
    Distances[c1] = []
    
    #Angles and distances
    for c2 in range(0,len(Coord)):
        if c1 == c2:
            Angles[c1].append(None)
            Distances[c1].append(None)
        else:
            a = Coord[c1][0] - Coord[c2][0]
            b = Coord[c1][1] - Coord[c2][1]
                    
            if a == 0:
                if b>=0:
                    Angles[c1].append(270)
                    Distances[c1].append(abs(b))
                    #print "a,b:",a,b
                    #print Angles,"\n",Distances,"\n"
                else:
                    Angles[c1].append(90)
                    Distances[c1].append(abs(b))
                    #print "a,b:",a,b
                    #print Angles,"\n",Distances,"\n"
            if b == 0:
                if a >= 0:
                    Angles[c1].append(180)
                    Distances[c1].append(abs(a))
                    #print "a,b:",a,b
                    #print Angles,"\n",Distances,"\n"
                else:                    
                    Angles[c1].append(0)
                    Distances[c1].append(abs(a))
                    #print "a,b:",a,b
                    #print Angles,"\n",Distances,"\n"
                            
            if a!=0 and b!=0:
                #print "a,b,degree",a,b,math.degrees(math.atan(b/a))
                        
                if a>0 and b >0:
                    Angles[c1].append(math.degrees(math.atan(b/a))+180.0)
                    Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                if a>0 and b <0:
                    Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+180.0)
                    Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                if a<0 and b >0:
                    Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+360.0)
                    Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                if a<0 and b <0:
                    Angles[c1].append(math.degrees(math.atan(b/a)))
                    Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
    
    return Angles,Distances

        
    
# Spotting probabilities functions (sending message functions)    
def SpottingProbs(Cells_Obj,AvailSet,WSD,WSC,WTolerance,Angles,Distances,SpotTolerance,verbose):
    SpotProb = [[] for c in range(0,len(Cells_Obj))]
    WSMax = SpotTolerance
    
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
        print "Wind Windows:","[",WA,",",WB,"]"
        
        
    Indicator = 0
    Indicators = [[] for i in range(0,len(Cells_Obj))]
    for c1 in range(0,len(Cells_Obj)):
        for c2 in range(0,len(Cells_Obj)):
            Indicator = 0
                
            if Angles[c1][c2] == None or Distances[c1][c2] <2.0:
                SpotProb[c1].append(0)
                Indicators[c1].append(None)
            
            else:
                if Angles[c1][c2] != None and WTolerance >=180:
                    Indicator = 1
                    Indicators[c1].append(1)
                    SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                else:            
                    if WA>=0 and WB>=0 and WA<360 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB and  Angles[c1][c2] >= WA:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)
                            
                    if WA>=0 and WB>=0 and WA<360 and WB>=360 and WTolerance<180:
                        if Angles[c1][c2] <= WB-360 and  Angles[c1][c2] >= WA:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)                            
                    
                    if WA<0 and WB>=0 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB or Angles[c1][c2] >= WA+360:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)
                    
    #print "Probabilities:",SpotProb    
    
    return SpotProb

# Spotting probabilities functions (sending message functions)    
def SpottingProbs_12JULIO(Cells_Obj,AvailSet,WSD,WSC,WTolerance,Angles,Distances,SpotTolerance,verbose):
    SpotProb = [[] for c in range(0,len(Angles))]
    WSMax = SpotTolerance
    
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
        print "Wind Windows:","[",WA,",",WB,"]"
        
        
    Indicator = 0
    Indicators = [[] for i in range(0,len(Angles))]
    for c1 in range(0,len(Angles)):
        for c2 in range(0,len(Angles)):
            Indicator = 0
                
            if Angles[c1][c2] == None or Distances[c1][c2] <2.0:
                SpotProb[c1].append(0)
                Indicators[c1].append(None)
            
            else:
                if Angles[c1][c2] != None and WTolerance >=180:
                    Indicator = 1
                    Indicators[c1].append(1)
                    SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                else:            
                    if WA>=0 and WB>=0 and WA<360 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB and  Angles[c1][c2] >= WA:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)
                            
                    if WA>=0 and WB>=0 and WA<360 and WB>=360 and WTolerance<180:
                        if Angles[c1][c2] <= WB-360 and  Angles[c1][c2] >= WA:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)                            
                    
                    if WA<0 and WB>=0 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB or Angles[c1][c2] >= WA+360:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)
                    
    #print "Probabilities:",SpotProb    
    
    return SpotProb

# Spotting probabilities functions (sending message functions)    
def SpottingProbs_03AUG(NCells,AvailSet,WSD,WSC,WTolerance,Angles,Distances,SpotTolerance,c1,verbose):
    SpotProb = {}
    SpotProb[c1] = []
    WSMax = SpotTolerance
    
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
        print "Wind Windows:","[",WA,",",WB,"]"
        
        
    Indicator = 0
    Indicators = {}
    Indicators[c1] = []
    
    for c2 in range(0,NCells):
        Indicator = 0
                
        if Angles[c1][c2] == None or Distances[c1][c2] <2.0:
            SpotProb[c1].append(0)
            Indicators[c1].append(None)
            
        else:
            if Angles[c1][c2] != None and WTolerance >=180:
                Indicator = 1
                Indicators[c1].append(1)
                SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
            else:            
                if WA>=0 and WB>=0 and WA<360 and WB<360 and WTolerance<180:
                    if Angles[c1][c2] <= WB and  Angles[c1][c2] >= WA:
                        Indicator = 1
                        Indicators[c1].append(1)
                        SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                    else:
                        SpotProb[c1].append(0)
                        Indicators[c1].append(0)
                            
                if WA>=0 and WB>=0 and WA<360 and WB>=360 and WTolerance<180:
                    if Angles[c1][c2] <= WB-360 and  Angles[c1][c2] >= WA:
                        Indicator = 1
                        Indicators[c1].append(1)
                        SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                    else:
                        SpotProb[c1].append(0)
                        Indicators[c1].append(0)                            
                    
                if WA<0 and WB>=0 and WB<360 and WTolerance<180:
                    if Angles[c1][c2] <= WB or Angles[c1][c2] >= WA+360:
                        Indicator = 1
                        Indicators[c1].append(1)
                        SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                    else:
                        SpotProb[c1].append(0)
                        Indicators[c1].append(0)
                    
    #print "Probabilities:",SpotProb    
    
    return SpotProb
    
        
    
# Spotting Messsage
def SpottingMsg(Cell,SpotProb,AvailSet,verbose):
    MsgList = []
    probspot = 0
    
    for i in range(0,len(SpotProb)):
        if SpotProb[Cell.ID-1][i] != None and SpotProb[Cell.ID-1][i]>0:
            probspot = round(uniform(0, 1),2)
            if verbose == True:
                print "Spotting from",Cell.ID,"to",i+1
                print "Probspot:",probspot, "SpotProb:",SpotProb[Cell.ID-1][i]#, "AvailSet:",AvailSet
            if probspot <= SpotProb[Cell.ID-1][i] and i+1 in AvailSet:
                MsgList.append(i+1)
                if verbose == True:
                    print "Cell",Cell.ID,"sends spotting to cell:",i+1
                
    if verbose == True:
        print "Cell",Cell.ID,"spotting:",MsgList        
    return MsgList

def SpottingMsg_12JULIO(Cell,SpotProb,AvailSet,verbose):
    MsgList = []
    probspot = 0
    
    for i in range(0,len(SpotProb)):
        if SpotProb[Cell.ID-1][i] != None and SpotProb[Cell.ID-1][i]>0:
            probspot = round(uniform(0, 1),2)
            if verbose == True:
                print "Spotting from",Cell.ID,"to",i+1
                print "Probspot:",probspot, "SpotProb:",SpotProb[Cell.ID-1][i]#, "AvailSet:",AvailSet
            if probspot <= SpotProb[Cell.ID-1][i] and i+1 in AvailSet:
                MsgList.append(i+1)
                if verbose == True:
                    print "Cell",Cell.ID,"sends spotting to cell:",i+1
                
    if verbose == True:
        print "Cell",Cell.ID,"spotting:",MsgList        
    return MsgList
    
def SpottingMsg_03AUG(Cell,SpotProb,AvailSet,verbose):
    MsgList = []
    probspot = 0
    
    for i in range(0,len(SpotProb[Cell.ID-1])):
        if SpotProb[Cell.ID-1][i] != None and SpotProb[Cell.ID-1][i]>0:
            probspot = round(uniform(0, 1),2)
            if verbose == True:
                print "Spotting from",Cell.ID,"to",i+1
                print "Probspot:",probspot, "SpotProb:",SpotProb[Cell.ID-1][i]#, "AvailSet:",AvailSet
            if probspot <= SpotProb[Cell.ID-1][i] and i+1 in AvailSet:
                MsgList.append(i+1)
                if verbose == True:
                    print "Cell",Cell.ID,"sends spotting to cell:",i+1
                
    if verbose == True:
        print "Cell",Cell.ID,"spotting:",MsgList        
    return MsgList    
    
# Full function    
def SpottingFBP(Cells_Obj,AvailSet,WSD,WSC,WTolerance,verbose):
    #Main arrays for spotting logic
    Angles = [[] for c in range(0,len(Cells_Obj))]
    Distances = [[] for c in range(0,len(Cells_Obj))]
    SpotProb = [[] for c in range(0,len(Cells_Obj))]
    WSMax = 35
    
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
        print "Wind Windows:","[",WA,",",WB,"]"
    
    #Angles and distances
    for c1 in range(0,len(Cells_Obj)):
        for c2 in range(0,len(Cells_Obj)):
            if c1 <= len(Cells_Obj):
                #break
                if c1 == c2:
                    Angles[c1].append(None)
                    Distances[c1].append(None)
                else:
                    a = Cells_Obj[c1].Coord[0] - Cells_Obj[c2].Coord[0]
                    b = Cells_Obj[c1].Coord[1] - Cells_Obj[c2].Coord[1]
                    
                    if a == 0:
                        if b>=0:
                            Angles[c1].append(270)
                            Distances[c1].append(abs(b))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                        else:
                            Angles[c1].append(90)
                            Distances[c1].append(abs(b))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                    if b == 0:
                        if a >= 0:
                            Angles[c1].append(180)
                            Distances[c1].append(abs(a))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                        else:                    
                            Angles[c1].append(0)
                            Distances[c1].append(abs(a))
                            #print "a,b:",a,b
                            #print Angles,"\n",Distances,"\n"
                            
                    if a!=0 and b!=0:
                        #print "a,b,degree",a,b,math.degrees(math.atan(b/a))
                        
                        if a>0 and b >0:
                            Angles[c1].append(math.degrees(math.atan(b/a))+180.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a>0 and b <0:
                            Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+180.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a<0 and b >0:
                            Angles[c1].append(math.degrees(-abs(math.atan(b/a)))+360.0)
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
                        if a<0 and b <0:
                            Angles[c1].append(math.degrees(math.atan(b/a)))
                            Distances[c1].append(math.sqrt(math.pow(a,2)+math.pow(b,2)))
    
    #Probabilities
    if verbose == True:
        print "Angles:",Angles
        print "\nDistances:",Distances
        print ""
    
    Indicator = 0
    Indicators = [[] for i in range(0,len(Cells_Obj))]
    for c1 in range(0,len(Cells_Obj)):
        for c2 in range(0,len(Cells_Obj)):
            Indicator = 0
                
            if Angles[c1][c2] == None:
                SpotProb[c1].append(0)
                Indicators[c1].append(None)
            
            else:
                if Angles[c1][c2] != None and WTolerance >=180:
                    Indicator = 1
                    Indicators[c1].append(1)
                    SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                else:            
                    if WA>=0 and WB>=0 and WA<360 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB and  Angles[c1][c2] >= WA:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)
                            
                    if WA>=0 and WB>=0 and WA<360 and WB>=360 and WTolerance<180:
                        if Angles[c1][c2] <= WB-360 and  Angles[c1][c2] >= WA:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)                            
                    
                    if WA<0 and WB>=0 and WB<360 and WTolerance<180:
                        if Angles[c1][c2] <= WB or Angles[c1][c2] >= WA+360:
                            Indicator = 1
                            Indicators[c1].append(1)
                            SpotProb[c1].append((WSC/WSMax)*math.exp(-Distances[c1][c2]*0.5)*Indicator)
                        
                        else:
                            SpotProb[c1].append(0)
                            Indicators[c1].append(0)
    if verbose == True:                
        print "Probabilities:",SpotProb                
        print "\nIndicators:",Indicators
    
    #Send messages
    
    
