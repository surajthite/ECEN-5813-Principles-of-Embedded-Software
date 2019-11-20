# Readme For project 5 Team Members :
1)Suraj Thite (suraj.thite@colorado.edu)
2)Atharv Desai (atharv.desai@colorado.edu)

This is a readme file for the fifth project assignment in the Principles of Embedded Software Course for FALL '19. 
The below enumerated files are contained in the repository 
1) PES_Project5 
  i) Project Settings 
  ii) Build Targets 
  iii) Binaries 
  iv) Includes 
  v) CMSIS 
  vi) Board 
  vii) Drivers 
  viii) Source
             a) main.c & main.h 
             b) logger.c & logger.h 
             c) RGBled.c & RGBled.h 
             d) char_count_update.c & char_count_update.h 
             e) unittest.c & unittest.h 
             f) circularbuff.c & circularbuff.h 
             g) timestamp.c  & timestamp.h
             h) uart_interrupt.c & uart_interrupt.h
ix) Startup 
x) Utilities 
xi) Debug 
xii) PESProject5 PE Debug.launch

2) Readme File (Readme Markdown File)

3) UART Transactions Screenshot

# INSTALLATION & EXECUTION NOTES 

The code is tested on the enviornment below:

* MCUXpresso IDE which is an easy to use Eclipse-based development environment for NXP® MCUs based on Arm® Cortex®-M cores.
* During this project, this IDE was used to code,execute circular buffer functions and interface them with polling and interrupt based UART of FRDM board on FRDM-KL25z and print their output on the IDE’s serial terminal.
* Also, we were able to check and verify the workability of the UART and Buffer using the unittest cases in the project.
* Using Debug Port Logic Analyser, the PTA1 and PTA2 pin data in the form of  waveform was used to capture UART transactions 
* The hardware used in this project was FRDM-KL25Z board which has been designed by NXP and built on ARM® Cortex™-M0+ processor.
* The editor used to build the code is gedit version 2.3.8.1 on Linux Mint Machine.
* To execute the executable file simply type ./(filename) in linux gcc environment while click on debug (bug icon) and then resume button to execute the file on MCUXpresso.
* Kindly use notepad++ for viewing .out files ,particularly for first output since they have been misaligned due to character "Space or Tab" encoding.
* Set #define to 1 (ECHO) or 0 (APPLICATION)  respectively.
* Set #define to 1 (TESTMODE ) or 0 (ECHO OR APPLICATION MODE)  respectively.
* Set modes to Test, Debug or Status mode by setting the vale for variable 'a'  in logger.c file accordingly.  

# DIFFICULTIES & OBSERVATIONS:

* While capturing the UART transactions output on Logic Analyser, faced issues in capturing the UART TX and RX waveforms in timing mode. Also, we learned to interpret the data on those   lines in binary format.
* While designing the circular buffer functions, we were not able to reallocate a new buffer while retaining the old data and adding new data further.
* While implementing the UART communication with specific baud rate, performed calculations such as calculating reload value for 10Hz frequency and setting systick timer frequency for the same.
* While implementing logger earlier, the enum values were being passed as arguments in integer format only. But on accessing them in other .c files using extern keyword, the issue was resolved. Also, integrated the timestamp with the logger and segregated the count value between hours, minutes and seconds to get the timestamp in appropriate format.
