/*
*   AUTHOR: Devin Bess
*
*   Operating System Practice Objectives
*   ------------------------------------
*   Subroutine instantiation and calls
*   Memory allocation and deallocation
*   Arrays and pointers 
*   Creating, opening, and writing data to files
*   Analzying and visualizing statistical data collected from processing simulation 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define frand() (((double)rand()+1.)/((double)RAND_MAX+1.))


/* Initialize subroutines for obtaining standard deviation of sequences */
double getSD1(double seq1[]);
double getSD2(double seq2[]);
double getSD3(double seq3[]);
int main () {
    /* Using parameters provided in provided scenarios */
    //initializing m and M parameters
   int m_1 = 1, M_1 = 8;
   int m_2 = 1, M_2 = 2000; 
   int m_3 = 1, M_3 = 8100;
   //initializing n parameters
   int n_1 = 20, n_2 = 200000;
   int n_3 = 2000000;
   //initializing mu and sigma parameters
   double mu_1 = 5, mu_2 = pow(2,10), mu_3 = pow(2, 12);  
   double sigma_1 = 1, sigma_2 = pow(2, 8), sigma_3 = (1.3 *(pow(2, 10)));

   size_t t;

   /* Intializes random number generator */
   srand((unsigned) t);


   //Creating file pointer to write data to csv file
   //Includes 2 file pointers for better testing data accuracy during development

   //FILE *fptr;

   //FILE *fptr2;

   //Opening file 
   //fptr = fopen("/Users/xxx", "w+");

   //fptr2 = fopen("/Users/xxx.csv", "w+");



    printf("--------------------------------------------------\n");
    printf("Scenario\t");
    printf("Mu\t");
    printf("Sigma\t");
    printf("m\t");
    printf("M\t");
    printf("n\n");
    printf("--------------------------------------------------\n");
    printf("Scenario #1  |  5    |   1    |   1  |   8   | 20\n");
    printf("--------------------------------------------------\n");
    printf("Scenario #2  | 2^10  |   2^8  |   1  | 2,000 | 200,000\n");
    printf("--------------------------------------------------\n");
    printf("Scenario #3  | 2^12  |1.3*2^10|   1  | 8,100 | 2,000,000\n");
    printf("--------------------------------------------------\n");

    


   //Scenario 1 for u, v, t, v/t, uvt sequences
   double uvt1[n_1];
   double vt1[n_1];
   double t1[n_1];
   double v1[n_1];
   double u1[n_1];
   double utemp1, usum1, umean1, vtemp1, vsum1, vmean1, ttemp1, tsum1, tmean1, vttemp1, vtsum1, vtmean1, uvttemp1, uvtsum1, uvtmean1;
   for(int a = 0; a < n_1; a++)
   {    
       //Derive a uniformly distributed random integer in range [m,M) for u sequence 
       u1[a]= rand() % (M_1-m_1) + m_1;
       utemp1 = u1[a];
       usum1 += u1[a];
       
       //Derive a normally distributed random number with mean mu and standard deviation sigma for v sequence 
       v1[a] = mu_1 + sigma_1 * cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand()));
       vtemp1 = v1[a];
       vsum1 += v1[a];

       //Derive a normally distributed random number with mean mu and standard deviation sigma truncated in the range [m,M)  
       ttemp1 = m_1 - 1;
       while(ttemp1 < m_1 || ttemp1 >= M_1)
       {
            ttemp1 = round(mu_1 + sigma_1 * cos(2 * 3.141592 * frand()) * sqrt(-2 * log(frand())));
       }
       t1[a] = ttemp1;
       tsum1 += t1[a];

       //Formula for sequence 4: v / t - dubbed v/t sequence 
       vttemp1 = v1[a] / t1[a];
       vt1[a] = vttemp1;
       vtsum1 += vt1[a];
       
       //Formula for sequence 5: 4u - 5v + 2t - dubbed uvt sequence 
       uvttemp1 = (4 * u1[a]) - (5 * v1[a]) + (2 * t1[a]);
       uvt1[a] = uvttemp1;
       uvtsum1 += uvt1[a];

   }

   umean1 = usum1 / n_1;
   vmean1 = vsum1 / n_1;
   tmean1 = tsum1 / n_1;
   vtmean1 = vtsum1 / n_1;
   uvtmean1 = uvtsum1 / n_1;

   printf("Standard deviation of Scenario #1 for u sequence: ");
   printf("%.4f\n\n", getSD1(u1));
   printf("Standard deviation of Scenario #1 for v sequence: ");
   printf("%.4f\n\n", getSD1(v1));
   printf("Standard deviation of Scenario #1 for t sequence: ");
   printf("%.4f\n\n", getSD1(t1));
   printf("Standard deviation of Scenario #1 for v/t sequence: ");
   printf("%.4f\n\n", getSD1(vt1));
   printf("Standard deviation of Scenario #1 for uvt sequence: ");
   printf("%.4f\n\n", getSD1(uvt1));


   printf("Sample mean of Scenario #1 for u sequence: ");
   printf("%f\n\n", umean1);
   printf("Sample mean of Scenario #1 for v sequence: ");
   printf("%f\n\n", vmean1);
   printf("Sample mean of Scenario #1 for t sequence: ");
   printf("%f\n\n", tmean1);
   printf("Sample mean of Scenario #1 for v/t sequence: ");
   printf("%f\n\n", vtmean1);
   printf("Sample mean of Scenario #1 for uvt sequence: ");
   printf("%f\n\n", uvtmean1);

   //Using memory details for calculating necessary data targets
   //memset(u1, 0, sizeof(u1));
   //memset(v1, 0, sizeof(v1));
   //memset(t1, 0, sizeof(t1));
   //memset(vt1, 0, sizeof(vt1));
   //memset(uvt1, 0, sizeof(uvt1));

   //Scenario 2 for u, v, t, v/t, uvt sequences
   double uvt2[n_2];
   double vt2[n_2];
   double t2[n_2];
   double v2[n_2];
   double u2[n_2];
   double utemp2, usum2, umean2, vtemp2, vsum2, vmean2, ttemp2, tsum2, tmean2, vttemp2, vtsum2, vtmean2, uvttemp2, uvtsum2, uvtmean2;
   for(int b = 0; b < n_2; b++)
   {    
       //Derive a uniformly distributed random integer in range [m,M) for u sequence 
       u2[b]= rand() % (M_2-m_2) + m_2;
       utemp2 = u2[b];
       usum2 += u2[b];
       
       //Derive a normally distributed random number with mean mu and standard deviation sigma for v sequence 
       v2[b] = mu_2 + sigma_2 * cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand()));
       vtemp2 = v2[b];
       vsum2 += v2[b];

       // Derive a normally distributed random number with mean mu and standard deviation sigma truncated in the range [m,M) 
       ttemp2 = m_2 - 1;
       while(ttemp2 < m_2 || ttemp2 >= M_2)
       {
            ttemp2 = round(mu_2 + sigma_2 * cos(2 * 3.141592 * frand()) * sqrt(-2 * log(frand())));
       }
       t2[b] = ttemp2;
       tsum2 += t2[b];

       //Formula for sequence 4: v / t - dubbed v/t sequence 
       vttemp2 = v2[b] / t2[b];
       vt2[b] = vttemp2;
       vtsum2 += vt2[b];
       
       //Formula for sequence 5: 4u - 5v + 2t - dubbed uvt sequence 
       uvttemp2 = (4 * u2[b]) - (5 * v2[b]) + (2 * t2[b]);
       uvt2[b] = uvttemp2;
       uvtsum2 += uvt2[b];

   }
   


   umean2 = usum2 / n_2;
   vmean2 = vsum2 / n_2;
   tmean2 = tsum2 / n_2;
   vtmean2 = vtsum2 / n_2;
   uvtmean2 = uvtsum2 / n_2;

   printf("Standard deviation of Scenario #2 for u sequence: ");
   printf("%.4f\n\n", getSD2(u2));
   printf("Standard deviation of Scenario #2 for v sequence: ");
   printf("%.4f\n\n", getSD2(v2));
   printf("Standard deviation of Scenario #2 for t sequence: ");
   printf("%.4f\n\n", getSD2(t2));
   printf("Standard deviation of Scenario #2 for v/t sequence: ");
   printf("%.4f\n\n", getSD2(vt2));
   printf("Standard deviation of Scenario #2 for uvt sequence: ");
   printf("%.4f\n\n", getSD2(uvt2));


   printf("Sample mean of Scenario #2 for u sequence: ");
   printf("%f\n\n", umean2);
   printf("Sample mean of Scenario #2 for v sequence: ");
   printf("%f\n\n", vmean2);
   printf("Sample mean of Scenario #2 for t sequence: ");
   printf("%f\n\n", tmean2);
   printf("Sample mean of Scenario #2 for v/t sequence: ");
   printf("%f\n\n", vtmean2);
   printf("Sample mean of Scenario #2 for uvt sequence: ");
   printf("%f\n\n", uvtmean2);

   //Using memory details for calculating necessary data targets
   //memset(u2, 0, sizeof(u2));
   //memset(v2, 0, sizeof(v2));
   //memset(t2, 0, sizeof(t2));
   //memset(vt2, 0, sizeof(vt2));
   //memset(uvt2, 0, sizeof(uvt2));

   
   
   //Scenario 3 for u, v, t, v/t, uvt sequences
   double* uvt3;
   double* vt3;
   double* t3;
   double* v3;
   double* u3;
   
   double utemp3, usum3, umean3, vtemp3, vsum3, vmean3, ttemp3, tsum3, tmean3, vttemp3, vtsum3, vtmean3, uvttemp3, uvtsum3, uvtmean3;

   u3 = (double*)malloc(n_3*sizeof(double));

   for(int c = 0; c < n_3; c++)
   {   

       u3[c]= rand() % (M_3-m_3) + m_3;
       utemp3 = u3[c];
       usum3 += u3[c];
       //fprintf(fptr2, "%f\n", u3[c]);
   }
  

   v3 = (double*)malloc(n_3*sizeof(double));
   for(int d = 0; d < n_3; d++)
   {
       v3[d] = mu_3 + sigma_3 * cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand()));
       vtemp3 = v3[d];
       vsum3 += v3[d];
       //fprintf(fptr2, "%f\n", v3[d]);
   }
   
   t3 = (double*)malloc(n_3*sizeof(double));
   for(int e = 0; e < n_3; e++)
   {
       ttemp3 = m_3 - 1;
       while(ttemp3 < m_3 || ttemp3 >= M_3)
       {
            ttemp3 = round(mu_3 + sigma_3 * cos(2 * 3.141592 * frand()) * sqrt(-2 * log(frand())));
       }
       t3[e] = ttemp3;
       tsum3 += t3[e];
       //fprintf(fptr2, "%f\n", t3[e]);
   }
   

   vt3 = (double*)malloc(n_3*sizeof(double));
   for(int f = 0; f < n_3; f++)
   {
       vttemp3 = v3[f] / t3[f];
       vt3[f] = vttemp3;
       vtsum3 += vt3[f];
       //fprintf(fptr2, "%f\n", vt3[f]);
   } 

   uvt3 = (double*)malloc(n_3*sizeof(double));
   for(int i = 0; i < n_3; i++)
   {
       uvttemp3 = (4 * u3[i]) - (5 * v3[i]) + (2 * t3[i]);
       uvt3[i] = uvttemp3;
       uvtsum3 += uvt3[i];
       //fprintf(fptr2, "%f\n", uvt3[i]);
   }

   /*
   for(int t = 0; t < n_3; t++)
   {
     fprintf(fptr2, "%f, %f, %f, %f, %f\n", u3[t], v3[t], t3[t], vt3[t], uvt3[t]);

   }
   */


   umean3 = usum3 / n_3;
   vmean3 = vsum3 / n_3;
   tmean3 = tsum3 / n_3;
   vtmean3 = vtsum3 / n_3;
   uvtmean3 = uvtsum3 / n_3;

   printf("Standard deviation of Scenario #3 for u sequence: ");
   printf("%.4f\n\n", getSD3(u3));
   printf("Standard deviation of Scenario #3 for v sequence: ");
   printf("%.4f\n\n", getSD3(v3));
   printf("Standard deviation of Scenario #3 for t sequence: ");
   printf("%.4f\n\n", getSD3(t3));
   printf("Standard deviation of Scenario #3 for v/t sequence: ");
   printf("%.4f\n\n", getSD3(vt3));
   printf("Standard deviation of Scenario #3 for uvt sequence: ");
   printf("%.4f\n\n", getSD3(uvt3));


   printf("Sample mean of Scenario #3 for u sequence: ");
   printf("%f\n\n", umean3);
   printf("Sample mean of Scenario #3 for v sequence: ");
   printf("%f\n\n", vmean3);
   printf("Sample mean of Scenario #3 for t sequence: ");
   printf("%f\n\n", tmean3);
   printf("Sample mean of Scenario #3 for v/t sequence: ");
   printf("%f\n\n", vtmean3);
   printf("Sample mean of Scenario #3 for uvt sequence: ");
   printf("%f\n\n", uvtmean3);

   free(u3);
   free(v3);
   free(t3);
   free(vt3);
   free(uvt3);

   //Using memory details for calculating necessary data targets
   //memset(u3, 0, sizeof(u3));
   //memset(v3, 0, sizeof(v3));
   //memset(t3, 0, sizeof(t3));
   //memset(vt3, 0, sizeof(vt3));
   //memset(uvt3, 0, sizeof(uvt3));
   

  //Closing csv files
  //fclose(fptr);
  //fclose(fptr2);

   return(0);

}

/* Subroutines for calculating the standard deviation of a sequence */
double getSD1(double seq1[])
{
    double sum_1 = 0.0, mean_1, SD1 = 0.0;
    int p;
    for (p = 0; p < 20; p++)
    {
        sum_1 += seq1[p];

    }
    mean_1 = sum_1/20;
    for (p = 0; p < 20; p++)
    {
        SD1 += pow(seq1[p] - mean_1, 2);
    }
    return sqrt(SD1/20);
}
double getSD2(double seq2[])
{
    double sum_2 = 0.0, mean_2, SD2 = 0.0;
    int q;
    for (q = 0; q < 200000; q++)
    {
        sum_2 += seq2[q];

    }
    mean_2 = sum_2/200000;
    for (q = 0; q < 200000; q++)
    {
        SD2 += pow(seq2[q] - mean_2, 2);
    }
    return sqrt(SD2/200000);
}
double getSD3(double seq3[])
{
    double sum_3 = 0.0, mean_3, SD3 = 0.0;
    int r;
    for (r = 0; r < 2000000; r++)
    {
        sum_3 += seq3[r];

    }
    mean_3 = sum_3/2000000;
    for (r = 0; r < 2000000; r++)
    {
        SD3 += pow(seq3[r] - mean_3, 2);
    }
    return sqrt(SD3/2000000);
}
