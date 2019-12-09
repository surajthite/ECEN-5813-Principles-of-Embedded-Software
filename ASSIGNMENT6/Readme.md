# Readme For project 6 Team Members :
1)Suraj Thite (suraj.thite@colorado.edu)
2)Atharv Desai (atharv.desai@colorado.edu)

This is a readme file for the sixth project assignment in the Principles of Embedded Software Course for FALL '19. 
The below enumerated files are contained in the repository 
1) PES_Project6 
  i) Project Settings 
  ii) Build Targets 
  iii) Binaries 
  iv) Includes 
  v) CMSIS 
  vi) Board 
  vii) Drivers 
  viii) Freertos
  viii) Source
             a) main.c & main.h 
             b) logger.c & logger.h 
             c) RGBled.c & RGBled.h 
             d) adc_dac.c & adc_dac.h 
             e) wave.c & wave.h 
             f) circularbuff.c & circularbuff.h 
             g) timestamp.c  & timestamp.h
             h) dma.c & dma.h
             i) task1.c & btasks.h
ix) Start up 
x) Utilities 
xi) Debug 
xii) PESProject6 PE Debug.launch

2) Readme File (Readme Markdown File)

3) Sine wave on OScillloscope Screen shot

# INSTALLATION & EXECUTION NOTES 

The code is tested on the environment below:

* MCUXpresso IDE which is an easy to use Eclipse-based development environment for NXP® MCUs based on Arm® Cortex®-M cores.
* During this project, this IDE was used to code,execute circular buffer functions and interface them with adc and dac pins i.e PTE 20 and PTE 30 of FRDM board on FRDM-KL25z and observe output on the oscilloscope.
* Also, we were able to check and verify the workability of the DMA by comparing the ADC and DSP buffer values in the project.
* Using DSO-X-2022A, the PTE30 pin data in the form of sine waveform was observed on the DSO for 5sec peak to peak and amplitude of 2V. 
* The FreeRtos Functions such as VtaskDelay and many others were read from the reference manual on the FreeRtos Website.
* The hardware used in this project was FRDM-KL25Z board which has been designed by NXP and built on ARM® Cortex™-M0+ processor.
* The editor used to build the code is gedit version 2.3.8.1 on Linux Mint Machine.
* To execute the executable file simply type ./(filename) in linux gcc environment while click on debug (bug icon) and then resume button to execute the file on MCUXpresso.
* Kindly use notepad++ for viewing .out files ,particularly for first output since they have been misaligned due to character "Space or Tab" encoding.
* Set #define to 1 (ECHO) or 0 (APPLICATION)  respectively.
* Set modes to Test, Debug or Status mode by setting the vale for variable 'a'  in logger.c file accordingly.  

# DIFFICULTIES & OBSERVATIONS:

* While capturing the Sine wave output on Oscilloscope, we faced issues in capturing the time difference between two peaks using for loop. Therefore, we learned to use the vtaskdelay function and pass appropriate macro value as an argument to that function to get .
* While designing the circular buffer functions, we were not able to reallocate a new buffer while retaining the old data and adding new data further.
* While implementing the tasks in FreeRtos, we studied the working of scheduler while giving priorities to the functions such as DaC, ADC etc and learnt about the operating system concepts such as mutex and semaphores.
* While implementing logger earlier, the en um values were being passed as arguments in integer format only. But on accessing them in other .c files using extern keyword, the issue was resolved. Also, integrated the timestamp with the logger and segregated the count value between hours, minutes and seconds to get the timestamp in appropriate format.
* The semaphores and mutex needs to be released in time in order to avoid hard faults. 
* Log statements to be removed in application mode ,in order to minimise the task time. Same can be enabled in Debug mode. 


# Extra Credits Implemented 
* Created FreeRTOS Queues in order to store values received in ADC and DMA transfer to DSP buffer 
* Implemented Semaphore and Mutex Free RTOS APIs.
