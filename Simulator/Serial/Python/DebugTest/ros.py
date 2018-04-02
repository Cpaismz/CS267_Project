"""
Use the ROS from FBP on four axes to get the ROS on eight axes.
David L. Woodruff; Sept 2017
"""

ros_distr(thetafire, forward, flank, back, ROSAngleDir):
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
    def allocate(angle, base, ros1, ros2):
        # allocate the ros between 1 and 2 based on the angle
        d = (offset - base) / 90.
        return (1-d) * ros1 + d * ros2
    
    for angle in ROSAngleDir:
        offset = angle - thetafire
        if offset >= 0 and offset <= 90:
            ROSAngleDir[angle] = allocate(angle, 0., forward, flank)
        elif offset > 90 and offset < 180:
            ROSAngleDir[angle] = allocate(angle, 90., flank, rear)
        elif offset >= 180 and offset <= 270:
            ROSAngleDir[angle] = allocate(angle, 180., rear, flank)
        elif offset > 270 and offset < 360:
            ROSAngleDir[angle] = allocate(angle, 270., flank, forward)
    return ROSAngleDir
#=====================================================================
    """
    begin notes for dlw
    headstruct = fire_struc()
    backstruct = fire_struc()
    flankstruct = fire_struc()
    e.g., headstruct.ros m/min
    raz is the spread direction azimuth; use main.raz
    Cells.Adjacents is set
    Cells.Coord[0], Coord[1]
    end notes for dlw
    """
    #in cells constructor?
    self.FireProgress = {}  # dynamic; meters from the center on the axis
    self.AngleDict = {} # static; indexed by neighbors contains angle
    self.ROSAngleDir = {} # dynamic; indexed by active angles; contains currenROS
    self.DistToCenter = {} # static; distance in meters
    self.angle_to_nb = {} # static map
    for nb in self.Adjacents:
        adj = nb.coord[0] - self.coord[0]
        opp = nb.coord[1] - self.coord[1]
        if adj != 0:
            angle = math.arctan(opp / adj))
        else:
            if opp > 0:
                angle = 90.
            else:
                angle = 270.
        self.AngleDict[nb] = angle
        self.ROSAngleDir[angle] = None
        self.angle_to_nb[angle] = nb
        self.FireProgress[nb] = 0.0
        self.DistToCenter[nb] = math.sqrt(adj*ajd + opp*opp)

    #======================
    
    #=======================
    ...
    # in send_msg_FBP? after fbp call (assumes I am on fire)
    #   but this needs to be called for all cells on the burning list;
    #   so it probably needs a new name (not send_msg_FBP, but burning() or something like that)
    
    # Here is approximately the call to fbp (note additions to
    #    ReadData.CalcualteOne return list)
    mainstruct, headstruct, flankstruct, backstruct = ReadData.\
        CalculateOne(....)

    
    # assume the ROSAngleDir has already been pruned based on availability (in get_burnt or its successor)
    # ???does main.raz go with the fire (i.e., is it OK or off by 180?)
    # assumes PeriodLen is in seconds
    #
    # NOTE as of Sept 2017 this is written by DLW to use only the source cell ROS
    #   (it would be some work to have it use the neighbors' when the fire crosses
    #    the boundary between cells...)
    #
    self.ROSAngleDir = ros_distr(mainstruct.raz,
                                 headstruct.ros,
                                 flankstruct.ros,
                                 backstruct.ros,
                                 self.ROSAngleDir)
    for angle in self.ROSAngleDir:
        nb = angle_to_nb[angle]
        self.FireProgress[nb] += self.ROSAngleDir[angle] * PeriodLen
        if self.FireProgress[nb] >= self.DistToCenter[nb]:
            msg_list.append(nb)
            self.ROSAngleDir.pop(nb)  # done with that path

    # now send messages
    for nb in msg_list:
        send_msg(nb) or nb.get_burnt(...)
        # A cell that gets a message should see if it should start burning and, if
        # so, it should add itself to the burning list...

    # if Period * PeriodLen > MaxFireLen take myself off the burning list
    # if self.ROSAngleDir is empty take myself off the burning list

#===================
    # Heres some new get_burnt (changing names slightly) (or send_msg) logic. Let's assume
    # it is nb.get_burned
    def get_burned(self, ....)

        # call calculate_one and if the ros is zero, quit; otherwise burn
        mainstruct, headstruct, flankstruct, backstruct = ReadData.\
            CalculateOne(....)
        if headstruct.ros == 0:
            return # no fire "starts" here at this cell's center
        # Add this cell to the burning list, so "send_msg" will be called
        # every time step and also call "send_msg" righ now. I am
        # puttling "send_msg" in quotes (dlw sept 2017) because
        # it really should have its name changed.


		
		
""""random" notes:
    0. Let's not do any speedups until we have everything working,
        -e.g., the weather really changes only every hour, so
         there is really no need to call fbp every time step
         but let's just do it anyway to keep things simple.
    1. Using the neighbors' fbp call once the fire crosses the boundary is would not be too hard to do if we just assume it crossed the
boundary when the fire is half way; but let's not do that too soon
either.
    2. I am not sure where to put the burning cells list; there is
sort of some heavy parallel processing thinking that could be done 
but for now, let's do the simplest thing (whatever that is...). 
Probably it is really going to be just the same mechanism as the 
original message list or the cell just tells itself to call the