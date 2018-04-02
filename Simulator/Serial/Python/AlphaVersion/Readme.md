Author: CP
Simulator version 3.0a - October 2017

Comments Version 3.0a
1. Checking possible errors when dealing with the new manageFire() and get_burned() logic
2. Major modifications inside the main class in order to take into account the possibility that the fire from one cell would not reach the center of an adjacent cell during one period but the fire could be still alive and we need to loop over fire periods. More tests need to be performed.
3. PeriodLen is #critical#: a fire can burnt the entire forest or just a portion depending on this new parameter (to account for the fire progress from the center of a cell to another).
4. Current version is deterministic... the only "source" of uncertainty that is still in the model consists of the time decay factor: a burning cell is transformed into a burned cell based on a decay factor (with probabilities) instead of a simple maximum amount of periods. Very easy to use prob = 0 if maxFirePeriods parameter is given.
5. Only the original burning cell ROS is used to calculate the fireProgress from the burning cell to an adjacent one. New logic where ROS of the adjacent cell is used after the halfway will be implemented (work in progress) for comparison purposes. Not needed for homogeneous forest tests.
6. New fields were added to the CellsFBP class: simulation is more demanding in terms of RAM for massive instances.
7. Important note: if WS (wind speed) < 2, RAZ has a strange behavior. It does not follows the main wind direction but the opposite (in 180°). Therefore, when WS > 2 and WD (wind direction) = X, the output from the main object (mainstruct.raz) is as expected RAZ = WD, where RAZ indicates the main (head) direction of the fire.

Changelog
1. ROS is calculated for head, flank, and back directions
2. ROS is computed for the (possible less) main 8 axes for each cell, by a simple linear approximation based on the angles between cells' centers.
3. ReadData module: modification of CalculateOne() and CalculateAll() functions, returning main, head, flank, and back objects instead of only main. Needed for getting the RAZ (main angle) and all 4 ROS (forward, flank, and rear).
4. WeatherFBP module: new update(), print(), and set() functions. Critical is the conversion from our angle system (E = 0, N = 90, W = 180, and S = 270) to/from the FBP system (S = 0, W = 90, N = 180, W = 270) when updating the wind speed and direction based on a file or at random.  
5. CellsFBP module: New fields for managing the fire on each axis of the cell (related to an adjacent cell) and new functions for calculating the ROSs, fire progress, "sending messages" (fire arriving to a new cell's center), and "get_burned" steps are included.
...
6. Main class: .... (work in progress)
