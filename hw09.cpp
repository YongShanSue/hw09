
//////HW08.cpp		 
//////Author:	YUNG-SHAN SU 
//////Date: 4/25


///////////////////////Tutorial
//////If you want to use this code, you should change two parts:	
//////		Change the variable "size"  in line 24
//////		Change the data name  in line 35

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include"MAT.h"
#include<math.h>
#include<sys/time.h>


int main(int argc,char **argv){
	double duration;                    //Variable time duration
    struct timeval start;               //Variable start time
    struct timeval stop;                //Variable stop timei
    int size =21;
    char rega,regb;
    VEC XDATA(size);
    VEC YDATA(size);
    int x_first=475;
    int x_end=775;
    VEC XDATA_truth(x_end-x_first+1 );
    VEC YDATA_truth(x_end-x_first+1 );
    VEC YDATA_interpolation(x_end-x_first+1 );
    ////////////Load the supported points/////////
    FILE *fPtr;
	fPtr=fopen("f21.dat","r");
	fscanf(fPtr,"%c\t%c\n",&rega,&regb);
	for(int i=0;i< size ;i++)
		fscanf(fPtr,"%lf\t%lf\n",&XDATA[i],&YDATA[i]);
	fclose(fPtr);
	////////////Load the ground truth/////////
	FILE *fPtr1;
	fPtr1=fopen("f301.dat","r");
	fscanf(fPtr1,"%c\t%c\n",&rega,&regb);
	for(int i=0;i<x_end-x_first+1;i++)
    	fscanf(fPtr1 , "%lf\t%lf\n" , &XDATA_truth[i],&YDATA_truth[i]); 
	fclose(fPtr1);
    
	//////////////Lagrange Interpolation
	printf("x\ty\n");
	int a=0;
	for (int i = x_first ; i<=x_end ;i++){
		YDATA_interpolation[a]=Lagrange((double)i,XDATA,YDATA);
		printf("%d\t%lf\n",i,YDATA_interpolation[a]);
		a++;
	}
	/////////////Find the max error
	VEC difference_Y(YDATA_truth-YDATA_interpolation);
	VEC error(absolute(difference_Y));
	double maxerror=0;
	for(int i=0;i<x_end-x_first+1;i++){
		if(maxerror<error[i]&&XDATA_truth[i]>=550&&XDATA_truth[i]<=700)
			maxerror=error[i];
	}
	printf("Max Error:\t%lf\n",maxerror);


	
	return 0;
}	
