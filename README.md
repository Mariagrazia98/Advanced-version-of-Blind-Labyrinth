# ExtraPoints2

Project for the course of "Architetture dei sistemi di elaborazione" at "Politecnico di Torino" 

The joystick replaces the ROTATE and RUN buttons and works in two modes that can be controlled by the SELECT button: 

a)	EXPLORE, in which the robot cannot move, and the joystick is only used to change the robot direction. By acting on the UP/DOWN/LEFT/RIGHT directions, the robot is oriented to NORTH (N) / SOUTH (S) / WEST (W) / EAST (E), respectively. This mode is mainly intended for exploring the cells nearby the robot without any movement. 

b)	MOVE, in which the player can drive the robot in one of the four directions. Along with the movement, the robot is also rotated to align the proximity sensors with the movement direction. The robot advances 1 slot per second (i.e. the movement is performed after having pressed for one second the joystick in one of the four directions). 

 
In both EXPLORE and MOVE modes, the proximity sensors are always active and can possibly detect obstacles along the direction in front of the robot. The sensors have a range of action of 5 slots. That is, they are able detect obstacles within 5 slots away from the robot.  Considering Figure 1, when the robot is in position (1,11) and it looks to WEST, the proximity sensors do not detect the obstacle in (1,5) since it does not fall into the range of 5 slots.  
 
The player can switch between EXPLORE and MOVE by pressing the SELECT. When a new game is started, the MOVE mode is selected by default.  

![immagine](https://user-images.githubusercontent.com/55098208/140758305-737bc344-1179-419b-9430-ec24a55ba846.png)

Figure 1. Example of gameplay: in grey, the path covered by the robot; in blue, the obstacled reported by the sensors; in red, the other obstacles; in green, the exits. 
 
As an example, a gameplay is reported in Figure 1, in which the player uses the EXPLORE mode in (7,7) to check at N/S/W/E detecting the obstacle in (5,7); then it moves to E up to (7,11) and looks at N/S. During the movement the obstacle in (7,13) is detected; then it moves to N up to (4,11) and looks at W/E detecting the obstacle in (4,7); it continues up to (1,11) and looks W/E; changes direction to E in (0,11) and finally reaches (0,12). 
 
In the new controller, the touchscreen display shows the obstacles that have been detected by the robot’s proximity sensor in the current game. Moreover, the robot must be displayed using different colors (chosen by you) when the game is in EXPLORE mode or in MOVE mode (see Figure 2). Please note that obstacles must appear on the touchscreen in both EXPLORE and MOVE mode (if within the range of 5 slots). 
 
The touchscreen is also used to make some actions: 

•	To start a new game, the user must touch the labyrinth area. 

•	A RESTART button can be touched to quit the current game and to show the initial screen. 

•	A CLEAR button can be touched to cancel all obstacles previously detected in the current game; the game continues, and the display will show new obstacles detected (including previous ones if detected again). 

When the player reaches one of the exits, the game ends. To start a new game, the player must press the RESET button or touch RESTART on the screen. The joystick is disabled when the previous game ends and until the new game is started. When the game ends, an end-game message must be displayed on the touchscreen (up to you to design the message). 
Figure 2 shows a possible graphical view of the specifications above.  

![immagine](https://user-images.githubusercontent.com/55098208/140757859-a1bc41cb-2684-42d7-9749-cb7e727244e8.png)

Figure 2. Touchscreen display usage. In the first figure from the left, the robot is exploring the area and obstacles detected by the proximity sensors are displayed; in the second, the robot is moving; in the third, after touching Clear, the game continue and obstacles are “forgot”; in the right figure, after touching Restart, the player is ready to play again.  

