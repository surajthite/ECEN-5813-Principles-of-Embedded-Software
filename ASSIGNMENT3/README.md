# Readme for Project 3
# ECEN 5813 Project Skeleton - Fall 2019

Team Members : 
1)	Atharv Desai (atharv.desai@colorado.edu)
2)	Suraj Thite (suraj.thite@colorado.edu) 
This is a readme file for the third project assignment in the Principles of Embedded Software Course for FALL '19.
The below enumerated files are contained in the repository
1.	PES_PROJECT3 
i)	Project Settings 
ii)	Build Targets 
iii)	Binaries 
iv)	Includes 
v)	CMSIS 
vi)	Board 
vii)	Drivers 
viii)	Source 
a)	main.c & main.h
b)	logger.c & logger.h
c)	RGBled.c & RGBled.h
d)	memory.c & memory.h
e)	unittest.c & unittest.h
ix)	Startup 
x)	Utilities 
xi)	Debug 
xii)	PESProject3 PE Debug.launch
2.	UML Activity Diagram
3.	UML Sequence Diagram
4.	Readme File (Readme Markdown File)
5.	WBS for project 3
6. Custom make file for linux gcc enviornment



# INSTALLATION & EXECUTION NOTES
#INSTALLATION & EXECUTION NOTES
The code is tested on the enviornment below:
1.	MCUXpresso IDE which is an easy to use Eclipse-based development environment for NXP® MCUs based on Arm® Cortex®-M cores. Fb_debug and fb_run modules were compiled and executed on this IDE.
2.	MCUXpresso IDE which is an easy to use Eclipse-based development environment for NXP® MCUs based on Arm® Cortex®-M cores. Fb_debug and fb_run modules were compiled and executed on this IDE.
3.	During this project, this IDE was used to code and execute memory tests on FRDM-KL25z and print their output on the IDE’s serial terminal. 
4.	Also, we were able to check and verify the memory blocks allocation in heap using the memory map options in the IDE. 
5.	TO execute the project on both, the development system and linux/windows ,we developed a MakeFile for the code of the whole project and built on MCUXpresso IDE with all build options and flags mandatory to execute and build the project on development system as well as linux.
6.	The hardware used in this project was FRDM-KL25Z board which has been designed by NXP and built on ARM® Cortex™-M0+ processor.
7.	The editor used to build the code is gedit version 2.3.8.1 on Linux Mint Machine.
8.	To execute the executable file simply type ./(filename) in linux gcc environment while click on debug (bug icon) and then resume button to execute the file on MCUXpresso.
9.	To compile and create executable file in linux environment , type gcc (filename).c -o (filename) -Wall - Werror -lm
10.	Kindly use notepad++ for viewing .out files ,particularly for first output since they have been misaligned due to character "Space or Tab" encoding.
11.	Using Drawio online tool, we made UML sequence diagram and UML activity diagram for demonstrating the flow of memory test cases.
12. Kindly use the make file in the linux build make folder in the repository to build the project in linux enviornment.

# CHALLENGES
1. The pattern verify function needs to generate pattern out of allocated memory block. Hence it could not enter the pattern generate function at the memory block.Hence new function without memory bounds checking has been incorporated.
2.The printf function could not be aligned in the memroy tests since each function in the System.h and other related files pulled from github could be modified.
3. The memory tests suite has been incorporated just after the execution of assigned  functional tests.
4.The switching of the LEDS couldn't retain their state, hence incorporated a delay of 1 seconds to check the response of the functional tests. 

