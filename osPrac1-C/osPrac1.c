/*
*   Author: Devin Bess
*   
*   Refer to README-osPrac1 for more info
*   
*   Operating System Practice Objectives
*   ------------------------------------
*   Processes and job scheduling
*   Object-oriented programming
*   Switch and cases
*   Parameterizing functions
*   Sorting, queueing and scheduling algorithms
*   Calculating CPU Time for processes
*   Calculating Turnaround Time / Average Turnaround Time for processes
*   Calculating Arrival Time for processes 
*   Calculating and parameterizing Priority Levels for processes
*   First In First Out Algorithm
*   Shortest Job First Algorithm
*   Shortest Remaining Time First Algorithm
*   Preemptive Multilevel Priority Scheduling Algorithm
*   Multilevel Feedback Scheduling Algorithm
*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#define frand() (((double)rand()+1.)/((double)RAND_MAX+1.))

//A PROCESS WILL CONTAIN:
//a total cpu time -> double totalCPUTime
//an arrival time -> double arrivalTime
//a priority level -> int priorityLevel
//a waiting time -> double remainTime
//a turnaround time -> double turnaroundTime
//a flag -> int flag
//corresponding mean and std. deviation values, d and v -> double g, h
//a number of processes in total -> int n
//a time interval value -> int k


/* Process object for scheduling */
typedef struct process{
	double cpuTime;
	double arrivalTime; 
	int priorityLevel; 
	double remainingTime, turnaroundTime; 
	int flag; //flag
    double g1; //d1
    double h1; //v1
    double g2; //d2
    double h2; //v2
    int n; //n
    int k; //k
}process;

/* Sorting algorithm for scheduling processes */
void sort(process temp[], int n) 
{
	process t;
	int i,j;
	for(i=1;i<n;i++)
		for(j=0;j<n-i;j++){
			if(temp[j].arrivalTime > temp[j+1].arrivalTime){
				t = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = t;
			}
		}
}   

/*Initializing process parameters for scheduling processes */
int initialize(process P[])
{
	int i,n,k;
    double d1 = 0.0;
    double d2 = 0.0;
    double v1 = 0.0;
    double v2 = 0.0;

	printf("\n Enter total no. of processes, n : ");
	scanf("%d", &n);
    printf("\n Enter time interval value, k : ");
    scanf("%d", &k);

    d1 = k/n;
    v1 = d1/4.0;
    d2 = (25*k)/n;
    v2 = d2/4.0;

	for(i = 0; i < n; i++){
        P[i].arrivalTime = rand()%(k+1);
        P[i].priorityLevel = rand()%10+1;
        P[i].cpuTime = d1 + v1 * cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand()));
        P[i].g1 = d1;
        P[i].h1 = v1;
        P[i].g2 = d2;
        P[i].h2 = v2;
        P[i].n = n;
        P[i].k = k;

	}
     
	return n;
}

// First  Algorithm
void FIFO(process P[], int n){
	process temp[10000];
	double sumRT = 0.0, sumTT = 0.0;
    double dtemp1 = 0.0;
    double dtemp2 = 0.0;
    double dtemp3 = 0.0;
	double x = 0.0;
	float ATT = 0.0;
	int i, j;

    FILE *fptr;
    FILE *fPtr;

    //EDIT HERE
    /* Change filename to one of the following for the corresponding N and K vaues
    *   (n,k) = (100, 1000) -> FIFO_A.csv & FIFO_1.csv
    *   (n,k) = (500, 10000) -> FIFO_B.csv * FIFO_2.csv
    *   (n,k) = (500, 5000) -> FIFO_C.csv & FIFO_3.csv
    *   (n,k) = (1000, 10000) -> FIFO_D.csv & FIFO_4.csv
    */
    fptr = fopen("FIFO_A.csv", "w");
    fPtr = fopen("FIFO_1.csv", "w");

    

	for(i = 0; i < n; i++){

		temp[i] = P[i];

    }

    fprintf(fPtr,"\nProcess Scheduling Algorithm Simulation Report\n");
    fprintf(fPtr, "FIFO Algorithm Results (N = %d | K = %d)\n", temp[0].n, temp[0].k);
    fprintf(fPtr, "Process,CPU Time T,Arrival Time A\n");
    printf("\n\n\tProcess\tCPU Time, T\tArrival Time, A");

	sort(temp, n);
        
	for(i = 0; i < n; i++){

        printf("%d\t%f\t\t%f", i, temp[i].cpuTime, temp[i].arrivalTime);
        fprintf(fPtr, "%d,%f,%f\n", i, temp[i].cpuTime, temp[i].arrivalTime);
    }

	sumRT = temp[0].remainingTime = 0;
	sumTT = temp[0].turnaroundTime = temp[0].cpuTime - temp[0].arrivalTime;
        
    printf("\n\tProcess\td/ATT1\t\td/ATT2\n");
    printf("\t-----------------------------------\n");

    fprintf(fPtr, "\nProcess,d/ATT1,d/ATT2\n");

    fprintf(fptr,"d/ATT1,d1,d/ATT2,d2\n");
	for(i = 1;i < n; i++){

		temp[i].remainingTime = (temp[i - 1].cpuTime + temp[i - 1].arrivalTime + temp[i - 1].remainingTime) - temp[i].arrivalTime;;
		temp[i].turnaroundTime = (temp[i].remainingTime + temp[i].cpuTime);
		sumRT += temp[i].remainingTime;
		sumTT += temp[i].turnaroundTime;
        dtemp1 = temp[i].turnaroundTime/n;
        dtemp2 = temp[i].g1 / dtemp1;
        dtemp3 = temp[i].g2 / dtemp1;
        printf("\t%d\t%f\t%f\n", i, dtemp2, dtemp3);
        fprintf(fPtr, "%d,%f,%f\n", i, dtemp2, dtemp3);
        fprintf(fptr, "%f,%f,%f,%f", dtemp2, temp[i].g1, dtemp3, temp[i].g2);
        fprintf(fptr, "\n");
        dtemp1 = 0.0;
        dtemp2 = 0.0;
        dtemp3 = 0.0;

	}

	ATT = (float)sumTT/n;

	printf("\n\n\tProcess\tCPU Time, T\tArrival Time, A\tRemaining Time, R\tTurnaround Time, TT\tPriority Level");
    fprintf(fPtr, "\nProcess,CPU Time T,Arrival Time A,Remaining Time R,Turnaround Time TT,Priority Level L\n");

	for(i = 0; i < n; i++){

		printf("\n %d\t%f\t\t%f\t%f\t\t%f\t\t%d", i, temp[i].cpuTime, temp[i].arrivalTime, temp[i].remainingTime, temp[i].turnaroundTime, temp[i].priorityLevel);
        fprintf(fPtr, "%d,%f,%f,%f,%f,%d\n", i, temp[i].cpuTime, temp[i].arrivalTime, temp[i].remainingTime, temp[i].turnaroundTime, temp[i].priorityLevel);
        
    }       

	printf("\n\n Average turn-around, ATT = %0.2f.", ATT);
    fprintf(fPtr, "\n\nAverage turn-around:, ATT = %0.2f.", ATT);

    fclose(fptr);
    fclose(fPtr);
        
}


//Shortest Job First Algorithm
void SJF(process P[], int n){
	process temp[10000];
	process t;
	double sumRT = 0.0, sumTT = 0.0;
    double dtemp1 = 0.0, dtemp2 = 0.0, dtemp3 = 0.0;
	float ATT = 0.0;
	int i, j;
    double x = 0.0;

    FILE *fptr;
    FILE *fPtr;

    //EDIT HERE
    /* Change filename to one of the following for the corresponding N and K vaues
    *   (n,k) = (100, 1000) -> SJF_A.csv & SJF_1.csv
    *   (n,k) = (500, 10000) -> SJF_B.csv * SJF_2.csv
    *   (n,k) = (500, 5000) -> SJF_C.csv & SJF_3.csv
    *   (n,k) = (1000, 10000) -> SJF_D.csv & SJF_4.csv
    */
    fptr = fopen("SJF_A.csv", "w");
    fPtr = fopen("SJF_1.csv", "w");

	for(i = 0; i < n;i++){

		temp[i] = P[i];

    }

    fprintf(fPtr,"\nProcess Scheduling Algorithm Simulation Report\n");
    fprintf(fPtr, "SJF Algorithm Results (N = %d | K = %d)\n", temp[0].n, temp[0].k);
    fprintf(fPtr, "Process,CPU Time T,Arrival Time A\n");
    printf("\n\n\tProcess\tCPU Time, T\tArrival Time, A");

    sort(temp, n);

	for(i = 2; i < n; i++){
		for(j = 1; j < n - i + 1; j++){
			if(temp[j].cpuTime > temp[j + 1].cpuTime){
				t = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = t;
			}
		}
    }

	printf("\n\tProcess\td/ATT1\t\td/ATT2\n");
    printf("\t-----------------------------------\n");

    fprintf(fPtr, "\nProcess,d/ATT1,d/ATT2\n");

    fprintf(fptr,"d/ATT1,d1,d/ATT2,d2\n");
	
    for(i = 0; i < n; i++){

		printf("\n%d\t%f\t%f", i, temp[i].cpuTime, temp[i].arrivalTime);
        fprintf(fPtr, "%d,%f,%f\n", i, temp[i].cpuTime, temp[i].arrivalTime);

    }

	sumRT = temp[0].remainingTime = 0.0;
	sumTT = temp[0].turnaroundTime = temp[0].cpuTime - temp[0].arrivalTime;

	for(i = 1; i < n; i++){

		temp[i].remainingTime = (temp[i - 1].cpuTime + temp[i - 1].arrivalTime + temp[i - 1].remainingTime) - temp[i].arrivalTime;;
		temp[i].turnaroundTime = (temp[i].remainingTime + temp[i].cpuTime);
		sumRT += temp[i].remainingTime;
		sumTT += temp[i].turnaroundTime;
        dtemp1 = temp[i].turnaroundTime/n;
        dtemp2 = temp[i].g1 / dtemp1;
        dtemp3 = temp[i].g2 / dtemp1;
        printf("\t%d\t%f\t%f\n", i, dtemp2, dtemp3);
        fprintf(fPtr, "%d,%f,%f\n", i, dtemp2, dtemp3);
        fprintf(fptr, "%f,%f,%f,%f", dtemp2, temp[i].g1, dtemp3, temp[i].g2);
        fprintf(fptr, "\n");
        dtemp1 = 0.0;
        dtemp2 = 0.0;
        dtemp3 = 0.0;

	}
		
	ATT = (float)sumTT/n;

	printf("\n\n Process\tCPU Time, T\tArrival Time, A\tRemaining Time, R\tTurnaround Time, TT");
    fprintf(fPtr, "\nProcess,CPU Time T,Arrival Time A,Remaining Time R,Turnaround Time TT,Priority Level L\n");

	for(i = 0; i < n; i++){

		printf("\n %d\t%f\t%f\t%f\t%f", i, temp[i].cpuTime, temp[i].arrivalTime, temp[i].remainingTime, temp[i].turnaroundTime);
        fprintf(fPtr, "%d,%f,%f,%f,%f,%d\n", i, temp[i].cpuTime, temp[i].arrivalTime, temp[i].remainingTime, temp[i].turnaroundTime, temp[i].priorityLevel);

    }

	printf("\n\n Average turn-around, ATT = %0.2f.", ATT);
    fprintf(fPtr, "\n\nAverage turn-around:, ATT = %0.2f.", ATT);

    fclose(fptr);
    fclose(fPtr);

}

//Shortest Remaining Time Algorithm
void SRT(process P[], int n){
	int i, tcurr, j; 
    int x, pos, ttemp;
    double dtemp1 = 0.0, dtemp2 = 0.0, dtemp3 = 0.0, t_total = 0.0;
	double sumRT = 0.0,sumTT = 0.0;
	float ATT = 0.0;
    double total;
    double arrivalTimeTemp[10000];
    double cpuTimeTemp[10000];
    double remainingTimeTemp[10000];
    double y[10000];
    double turnaroundTimeTemp[10000];
    double tatTemp;
    int count = 0, time, smallest;
    double avg = 0,tt = 0, end;
	process temp[10000], t;

    FILE *fptr;
    FILE *fPtr;

    //EDIT HERE
    /* Change filename to one of the following for the corresponding N and K vaues
    *   (n,k) = (100, 1000) -> SRT_A.csv & SRT_1.csv
    *   (n,k) = (500, 10000) -> SRT_B.csv * SRT_2.csv
    *   (n,k) = (500, 5000) -> SRT_C.csv & SRT_3.csv
    *   (n,k) = (1000, 10000) -> SRT_D.csv & SRT_4.csv
    */

    fptr = fopen("SRT_D.csv", "w");
    fPtr = fopen("SRT_4.csv", "w");

	for(i = 0; i < n; i++){

		temp[i] = P[i];
		t_total += P[i].cpuTime;

	}

    fprintf(fPtr,"\nProcess Scheduling Algorithm Simulation Report\n");
    fprintf(fPtr, "SRT Algorithm Results (N = %d | K = %d)\n", temp[0].n, temp[0].k);

    sort(temp, n);

    for(int i = 0; i < n; i++)
    {
        arrivalTimeTemp[i] = temp[i].arrivalTime;
        cpuTimeTemp[i] = temp[i].cpuTime;
        y[i] = cpuTimeTemp[i];
        remainingTimeTemp[i] = temp[i].remainingTime;

    }

    for(i = 0; i < n; i++){

        pos = i;

        for(j = i + 1; j < n; j++){

            if(cpuTimeTemp[j]<cpuTimeTemp[pos]){

                pos = j;
            }
        }

        ttemp = cpuTimeTemp[i];
        cpuTimeTemp[i] = cpuTimeTemp[pos];
        cpuTimeTemp[pos] = ttemp;
        ttemp = y[i];
        y[i] = y[pos];
        y[pos]= ttemp;
    }

    remainingTimeTemp[0] = 0;

    for(i = 1; i < n; i++){

        remainingTimeTemp[i] = 0;

        for(j = 0; j < i; j++){

            remainingTimeTemp[i] += cpuTimeTemp[j];

        }
 
    }

    total = 0.0;

    printf("\n\t\tProcess\td/ATT1\t\td/ATT2\n");
    printf("\t\t-----------------------------------\n");

    fprintf(fPtr, "\nProcess,d/ATT1,d/ATT2\n");
    
    //fprintf(fptr,"d/ATT1,d1,d/ATT2,d2\n");

    for(int i = 0; i < n; i++){

        turnaroundTimeTemp[i] = cpuTimeTemp[i] + remainingTimeTemp[i];
        tatTemp += turnaroundTimeTemp[i];
        dtemp1 = tatTemp/n;
        dtemp2 = temp[i].g1 / dtemp1;
        dtemp3 = temp[i].g2 / dtemp1;
        printf("\t\t%d\t%f\t%f\n", i, dtemp2, dtemp3);
        fprintf(fPtr, "%d,%f,%f\n", i, dtemp2, dtemp3);
        fprintf(fptr, "%f,%f,%f,%f", temp[i].g1, dtemp2, temp[i].g2, dtemp3);
        fprintf(fptr, "\n");
        dtemp1 = 0.0;
        dtemp2 = 0.0;
        dtemp3 = 0.0;
    }
	
	//printf(" %d", tcurr);
    ATT = (float)sumTT/n;

    printf("\n\n Process\tCPU Time, T\tArrival Time, A\tRemaining Time, R\tTurnaround Time, TT");
    fprintf(fPtr, "\nProcess,CPU Time T,Arrival Time A,Remaining Time R,Turnaround Time TT,Priority Level L\n");

	for(i = 0; i < n; i++){

		printf("\n %d\t\t%f\t%f\t%f\t\t%f", i, temp[i].cpuTime, temp[i].arrivalTime, temp[i].remainingTime, temp[i].turnaroundTime);
        fprintf(fPtr, "%d,%f,%f,%f,%f,%d\n", i, temp[i].cpuTime, temp[i].arrivalTime, temp[i].remainingTime, temp[i].turnaroundTime, temp[i].priorityLevel);

    }

	printf("\n\n Average turn-around = %0.2f.", ATT);


    fclose(fptr);
    fclose(fPtr);
}

//Preemptive Multilevel Priority Scheduling Algorithm (W/ RR)
void MLP(process P[], int n){
	int i, t_total = 0, tcurr, k = 0, pflag = 0, t;
    double Q = 0, q = 0;
	double sumRT = 0.0, sumTT = 0.0;
	float ATT = 0.0;
    double dtemp1 = 0.0, dtemp2 = 0.0, dtemp3 = 0.0;
	process temp1[10000], temp2[10000];	

    FILE *fptr;
    FILE *fPtr;

    //EDIT HERE
    /* Change filename to one of the following for the corresponding N and K vaues
    *   (n,k) = (100, 1000) -> MLP_A.csv & MLP_1.csv
    *   (n,k) = (500, 10000) -> MLP_B.csv * MLP_2.csv
    *   (n,k) = (500, 5000) -> MLP_C.csv & MLP_3.csv
    *   (n,k) = (1000, 10000) -> MLP_D.csv & MLP_4.csv
    */

    fptr = fopen("MLP_D.csv", "w");
    fPtr = fopen("MLP_4.csv", "w");

	for(i = 0; i < n; i++){

		temp1[i] = P[i];
		t_total += P[i].cpuTime;
	}

    fprintf(fPtr,"\nProcess Scheduling Algorithm Simulation Report\n");
    fprintf(fPtr, "MLP Algorithm Results (N = %d | K = %d)\n", temp1[0].n, temp1[0].k);

	sort(temp1, n);

    for(i = 0; i < n; i++){

		temp2[i] = temp1[i];
    }

    q = (temp1[0].k / temp1[0].n) + ((temp1[0].k / temp1[0].n)/4.0);
    
    printf("\nQuantum, q = %f", q);
    fprintf(fPtr, "\nQuantum, %f", q);

	printf("\n Enter quantum time, q (= d + v) : ");
	scanf("%lf", &Q);
    
    printf("\n\t\tProcess\td/ATT1\t\td/ATT2\n");
    printf("\t\t-----------------------------------\n");

    fprintf(fPtr, "\nProcess,d/ATT1,d/ATT2\n");

    //fprintf(fptr,"d/ATT1,d1,d/ATT2,d2\n"); possible fix

	for(k = 0;; k++){

		if(k > n - 1){

			k = 0;
        }

		if(temp1[k].cpuTime > 0){

		//printf("  %d", tcurr); possible fix
		t = 0;

        }

		while((t < Q) && (temp1[k].cpuTime > 0)){
			t++;
			tcurr++;
			temp1[k].cpuTime--;
		}

		if((temp1[k].cpuTime <= 0) && (temp1[k].flag != 1)){
			temp1[k].remainingTime = tcurr - temp2[k].cpuTime - temp1[k].arrivalTime;
			temp1[k].turnaroundTime = tcurr - temp1[k].arrivalTime;
			pflag++;
			temp1[k].flag = 1;
			sumRT += temp1[k].remainingTime;
			sumTT += temp1[k].turnaroundTime;
            dtemp1 = temp1[k].turnaroundTime/n;
            dtemp2 = temp1[k].g1 / dtemp1;
            dtemp3 = temp1[k].g2 / dtemp1;
            printf("\t\t%d\t%f\t%f\n", k, dtemp2, dtemp3);
            fprintf(fPtr, "%d,%f,%f\n", k, dtemp2, dtemp3);
            fprintf(fptr, "%f,%f,%f,%f", temp1[k].g1, dtemp2, temp1[k].g2, dtemp3);
            fprintf(fptr, "\n");
            dtemp1 = 0.0;
            dtemp2 = 0.0;
            dtemp3 = 0.0;
		}

		if(pflag == n){

			break;
        }
    }

	//printf(" %d", tcurr); possible fix
	ATT = (float)sumTT/n;

    printf("\n\n Process\tCPU Time, T\tArrival Time, A\tRemaining Time, R\tTurnaround Time, TT");
    fprintf(fPtr, "\nProcess,CPU Time T,Arrival Time A,Remaining Time R,Turnaround Time TT,Priority Level L\n");

	for(i = 0; i < n; i++){

		printf("\n %d\t\t%f\t%f\t%f\t\t%f", i, temp1[i].cpuTime, temp1[i].arrivalTime, temp1[i].remainingTime, temp1[i].turnaroundTime);
        fprintf(fPtr, "%d,%f,%f,%f,%f,%d\n", i, temp1[i].cpuTime, temp1[i].arrivalTime, temp1[i].remainingTime, temp1[i].turnaroundTime, temp1[i].priorityLevel);

        }
		
	printf("\n\n Average turn-around, ATT = %0.2f.", ATT);
    fprintf(fPtr, "\n\nAverage turn-around:, ATT = %0.2f.", ATT);


    fclose(fptr);
    fclose(fPtr);
}

//Multilevel Feedback Scheduling Algorithm (W/RR)
void MLF(process P[], int n)
{   

	int pflag = 0, t, tcurr = 0, k = 0, i;
    double Q = 0, q = 0;
	double sumRT = 0.0, sumTT = 0.0;
	float ATT = 0.0;
    double dtemp1 = 0.0, dtemp2 = 0.0, dtemp3 = 0.0;
	process temp1[10000], temp2[10000];	

    FILE *fptr;
    FILE *fPtr;

    //EDIT HERE
    /* Change filename to one of the following for the corresponding N and K vaues
    *   (n,k) = (100, 1000) -> MLF_A.csv & MLF_1.csv
    *   (n,k) = (500, 10000) -> MLF_B.csv * MLF_2.csv
    *   (n,k) = (500, 5000) -> MLF_C.csv & MLF_3.csv
    *   (n,k) = (1000, 10000) -> MLF_D.csv & MLF_4.csv
    */

    fptr = fopen("MLF_D.csv", "w");
    fPtr = fopen("MLF_4.csv", "w");

	for(i = 0; i < n; i++){

		temp1[i] = P[i];
    
    }

    fprintf(fPtr,"\nProcess Scheduling Algorithm Simulation Report\n");
    fprintf(fPtr, "MLP Algorithm Results (N = %d | K = %d)\n", temp1[0].n, temp1[0].k);

	sort(temp1, n);

	for(i = 0; i < n; i++){

		temp2[i] = temp1[i];

    }

    q = (temp1[0].k / temp1[0].n) - (2*((temp1[0].k / temp1[0].n)/4.0));
    
    printf("\nQuantum, q = %f", q);
    fprintf(fPtr, "\nQuantum, %f", q);

	printf("\n Enter quantum time, q (= d - 2v) : ");
	scanf("%lf", &Q);

    printf("\n\t\tProcess\td/ATT1\t\td/ATT2\n");
    printf("\t\t-----------------------------------\n");

    fprintf(fPtr, "\nProcess,d/ATT1,d/ATT2\n");

    //fprintf(fptr,"d/ATT1,d1,d/ATT2,d2\n"); possible fix

	for(k = 0;; k++){

		if(k > n - 1){

			k = 0;
        }

		if(temp1[k].cpuTime > 0){

		//printf("  %d", tcurr); possible fix
		t = 0;

        }

		while((t < Q) && (temp1[k].cpuTime > 0)){

			t++;
			tcurr++;
			temp1[k].cpuTime--;

		} 

		if((temp1[k].cpuTime <= 0) && (temp1[k].flag != 1)){

			temp1[k].remainingTime = tcurr - temp2[k].cpuTime - temp1[k].arrivalTime;
			temp1[k].turnaroundTime = tcurr - temp1[k].arrivalTime;
			pflag++;
			temp1[k].flag = 1;
			sumRT += temp1[k].remainingTime;
			sumTT += temp1[k].turnaroundTime;
            dtemp1 = temp1[k].turnaroundTime/n;
            dtemp2 = temp1[k].g1 / dtemp1;
            dtemp3 = temp1[k].g2 / dtemp1;
            printf("\t\t%d\t%f\t%f\n", k, dtemp2, dtemp3);
            fprintf(fPtr, "%d,%f,%f\n", k, dtemp2, dtemp3);
            fprintf(fptr, "%f,%f,%f,%f", temp1[k].g1, dtemp2, temp1[k].g2, dtemp3);
            fprintf(fptr, "\n");
            dtemp1 = 0.0;
            dtemp2 = 0.0;
            dtemp3 = 0.0;

		}

		if(pflag == n){

			break;
        }
	}

	//printf("  %d", tcurr); possible fix
	ATT = (float)sumTT/n;

    printf("\n\n Process\tCPU Time, T\tArrival Time, A\tRemaining Time, R\tTurnaround Time, TT");
    fprintf(fPtr, "\nProcess,CPU Time T,Arrival Time A,Remaining Time R,Turnaround Time TT,Priority Level L\n");

	for(i = 0; i < n; i++){

		printf("\n %d\t\t%f\t%f\t%f\t\t%f", i, temp1[i].cpuTime, temp1[i].arrivalTime, temp1[i].remainingTime, temp1[i].turnaroundTime);
        fprintf(fPtr, "%d,%f,%f,%f,%f,%d\n", i, temp1[i].cpuTime, temp1[i].arrivalTime, temp1[i].remainingTime, temp1[i].turnaroundTime, temp1[i].priorityLevel);

    
    }
		
	printf("\n\n Average turn-around, ATT = %0.2f.", ATT);
    fprintf(fPtr, "\n\nAverage turn-around:, ATT = %0.2f.", ATT);

    fclose(fptr);
    fclose(fPtr);
}


int main(){
	
	process P[10000];
	int ch, n;
	do{
		printf("\n\n Scheduling Algorithm Simulation\n");
        printf("---------------------------------");
		printf("\n\t |Option Keys|");
        printf("\n  Select: _____________");
		printf("\n\t0| Initialize parameters");
		printf("\n\t1| FIFO");
		printf("\n\t2| SJF");
		printf("\n\t3| SRT");
		printf("\n\t4| MLP(RR)");
		printf("\n\t5| MLF(RR)");
		printf("\n\t6| Exit\n Select : ");
		scanf("%d", &ch);
		switch(ch){
			case 0:
				n = initialize(P);
				break;
			case 1:
				FIFO(P, n);
				break;
			case 2:
				SJF(P, n);
				break;
			case 3:
				SRT(P, n);
				break;
			case 4:
				MLP(P, n);
				break;
			case 5:
				MLF(P, n);
				break;
			case 6:
                exit(0);	
		}
	}while(ch != 6);
	return 0;
}

