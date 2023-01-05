# systems-practice-C

README - osPrac1

This program simulates five different process/job scheduling scenarios for four different parameter
value pairs (the total number of desired processes, n and a time interval max, k), each ran using 
multiple sorting, priority queueing, and scheduling algorithms. 

In order to initialize the desired parameters, you must type 0 in the console to enter
in the values for n, k, and at times, q.

Select options are as followed:

0 - Initialization 
1 - FIFO Scheduling Algorithm 
2 - SJF Scheduling Algorithm 
3 - SRT Scheduling Algorithm 
4 - MLP Scheduling Algorithm 
5 - MLF Scheduling Algorithm

The MLP and MLF scheduling processes will ask for a quantum time parameter, q (= Q).
The program should write the output of the desired scheduling algorithm to a .csv 
file for allocating the output collected.

Only two files can be written at one time so make sure to personalize the .csv file names of
*fptr and *fPtr after each (n, k) parameter set has been ran in each process/job scheduling 
scenario/algorithm. [See below for more..] 

An example of the expected runtime output filenames and their corresponding parameter values are as followed:
  
    *   (n,k) = (100, 1000) -> FIFO_A.csv & FIFO_1.csv
    *   (n,k) = (500, 10000) -> FIFO_B.csv * FIFO_2.csv
    *   (n,k) = (500, 5000) -> FIFO_C.csv & FIFO_3.csv
    *   (n,k) = (1000, 10000) -> FIFO_D.csv & FIFO_4.csv
    *   (n,k) = (100, 1000) -> SJF_A.csv & SJF_1.csv
    *   (n,k) = (500, 10000) -> SJF_B.csv * SJF_2.csv
    *   (n,k) = (500, 5000) -> SJF_C.csv & SJF_3.csv
    *   (n,k) = (1000, 10000) -> SJF_D.csv & SJF_4.csv
    *   (n,k) = (100, 1000) -> SRT_A.csv & SRT_1.csv
    *   (n,k) = (500, 10000) -> SRT_B.csv * SRT_2.csv
    *   (n,k) = (500, 5000) -> SRT_C.csv & SRT_3.csv
    *   (n,k) = (1000, 10000) -> SRT_D.csv & SRT_4.csv
    *   (n,k) = (100, 1000) -> MLP_A.csv & MLP_1.csv
    *   (n,k) = (500, 10000) -> MLP_B.csv * MLP_2.csv
    *   (n,k) = (500, 5000) -> MLP_C.csv & MLP_3.csv
    *   (n,k) = (1000, 10000) -> MLP_D.csv & MLP_4.csv
    *   (n,k) = (100, 1000) -> MLF_A.csv & MLF_1.csv
    *   (n,k) = (500, 10000) -> MLF_B.csv * MLF_2.csv
    *   (n,k) = (500, 5000) -> MLF_C.csv & MLF_3.csv
    *   (n,k) = (1000, 10000) -> MLF_D.csv & MLF_4.csv
    
These filenames and parameters are hard-coded in the program but you may edit them according to your specific needs.

Everytime a pair of new filenames are entered, the program must be recompiled and ran again.

Even though some values and parameters are randomized, always re-initialize the parameters of the desired process/job scheduling scenario/algorithm.
