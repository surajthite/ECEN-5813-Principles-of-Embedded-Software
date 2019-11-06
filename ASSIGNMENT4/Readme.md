# Readme For Project 4 Team Members :
1)Suraj Thite (suraj.thite@colorado.edu)
2)Atharv Desai (atharv.desai@colorado.edu)

This is a readme file for the fourth project assignment in the Principles of Embedded Software Course for FALL '19. 
The below enumerated files are contained in the repository 
1) PES_PROJECT4 
i) Project Settings 
ii) Build Targets 
iii) Binaries 
iv) Includes 
v) CMSIS 
vi) Board 
vii) Drivers 
viii) Source a) main.c & main.h 
             b) logger.c & logger.h 
             c) RGBled.c & RGBled.h 
             d) i2c.c & i2c.h 
             e) unittest.c & unittest.h 
             f) statemachine.c & statemachine.h 
ix) Startup 
x) Utilities 
xi) Debug 
xii) PESProject4 PE Debug.launch

2) Readme File (Readme Markdown File)

3) I2C Transactions Screenshot

# INSTALLATION & EXECUTION NOTES 

The code is tested on the enviornment below:

* MCUXpresso IDE which is an easy to use Eclipse-based development environment for NXP® MCUs based on Arm® Cortex®-M cores.
* During this project, this IDE was used to code,execute state machines and interface TMP102 with FRDM board using I2C protocol on FRDM-KL25z and print their output on the IDE’s serial terminal.
* Also, we were able to check and verify the workability of the state machines using the unittest cases in the project.
* Using Debug Port Logic Analyser, the SCL and SDA pin data in the form of  waveform was used to capture I2C transactions 
* The hardware used in this project was FRDM-KL25Z board which has been designed by NXP and built on ARM® Cortex™-M0+ processor.
* The editor used to build the code is gedit version 2.3.8.1 on Linux Mint Machine.
* To execute the executable file simply type ./(filename) in linux gcc environment while click on debug (bug icon) and then resume button to execute the file on MCUXpresso.
* Kindly use notepad++ for viewing .out files ,particularly for first output since they have been misaligned due to character "Space or Tab" encoding.
* Set #define (MODE) to 1 or 0 for test cases or state machine modes  respectively.
* Set modes to Test, Debug or Status mode by setting the vale for variable 'a'  in logger.c file accordingly.  

# DIFFICULTIES & OBSERVATIONS:

* While capturing the I2C transactions output on Logic Analyser, faced issues in capturing the SCL, SDA waveforms in timing mode.
* While designing the disconnected state, we were not able to swap between Connected and Disconnected state using software control. Many times, reset button needed to be pressed to check whether the current state has changed from connected to disconnected state and viceversa.
* In state-oriented state machine, we were able to define all states like Alert, read temperature in a single function . However, in table driven, we had to create standalone functions for each and every state to make sure about optimal working of the table driven machine.
* While implementing logger earlier, the enum values were being passed as arguments in integer format only. But on accessing them in other .c files using extern keyword, the issue was resolved.
