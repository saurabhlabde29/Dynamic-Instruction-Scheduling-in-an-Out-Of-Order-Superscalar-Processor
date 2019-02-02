#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include"main.h"
using namespace std;
void issuefunc(int n, int s, SCHEDULINGQUEUE schedulearray[], TEMPISSUE tempi[], FROB frobarray[10000], FUNCUNITS funcarray[], int *sqentry, int *clockcyc)
{
	int tempsizeissue = 0;
	int temppointissue = 0;
	int tempflag = 0;
	// Add ready entries to temp struct
	for(int i=0;i<s;i++)
	{
		if(schedulearray[i].TAG>=0 && schedulearray[i].READYSRC1==1 && schedulearray[i].READYSRC2==1)
		{
			tempi[tempsizeissue].TAG=schedulearray[i].TAG;
			tempi[tempsizeissue].READYSRC1=schedulearray[i].READYSRC1;
			tempi[tempsizeissue].READYSRC2=schedulearray[i].READYSRC2;
			tempi[tempsizeissue].TAGSRC1=schedulearray[i].TAGSRC1;
			tempi[tempsizeissue].TAGSRC2=schedulearray[i].TAGSRC2;
			tempflag = 1;
			tempsizeissue++;
		}
	}
	// Sort the temp struct in ascending order
	int TAG_temp_i;
	int READYSRC1_temp;
	int READYSRC2_temp;
	int TAGSRC1_temp;
	int TAGSRC2_temp;
	for(int i=0; i<tempsizeissue-1; i++)
	{
		for(int j=0; j<tempsizeissue-i-1; j++)
		{
			if(tempi[j].TAG > tempi[j+1].TAG)
			{
				TAG_temp_i=tempi[j].TAG;
				READYSRC1_temp=tempi[j].READYSRC1;
				READYSRC2_temp=tempi[j].READYSRC2;
				TAGSRC1_temp=tempi[j].TAGSRC1;
				TAGSRC2_temp=tempi[j].TAGSRC2;
				
				tempi[j].TAG=tempi[j+1].TAG;
				tempi[j].READYSRC1=tempi[j+1].READYSRC1;
				tempi[j].READYSRC2=tempi[j+1].READYSRC2;
				tempi[j].TAGSRC1=tempi[j+1].TAGSRC1;
				tempi[j].TAGSRC2=tempi[j+1].TAGSRC2;
				
				tempi[j+1].TAG=TAG_temp_i;
				tempi[j+1].READYSRC1=READYSRC1_temp;
				tempi[j+1].READYSRC2=READYSRC2_temp;
				tempi[j+1].TAGSRC1=TAGSRC1_temp;
				tempi[j+1].TAGSRC2=TAGSRC2_temp;
			}
		}			
	}
	// Sending to functional units
	for(int i=0;i<tempsizeissue;i++)
	{
		for(int j=0;j<10000;j++)
		{
			if(funcarray[j].TAG<0 && (*sqentry)>=0 && tempflag==1 && temppointissue<n)
			{
				funcarray[j].TAG = tempi[i].TAG;
				if(frobarray[tempi[i].TAG].TYPE == 0)
				{
					funcarray[j].CYCLE = 1;
					funcarray[j].COUNTINST = 1;
				}
				else if(frobarray[tempi[i].TAG].TYPE == 1)
				{
					funcarray[j].CYCLE = 2;
					funcarray[j].COUNTINST = 1;
				}
				else if(frobarray[tempi[i].TAG].TYPE == 2)
				{
					funcarray[j].CYCLE = 5;
					funcarray[j].COUNTINST = 1;
				}
				for(int k=0; k<s; k++)
				{
					if(tempi[i].TAG == schedulearray[k].TAG)
					{
						schedulearray[k].TAG = -1;
						schedulearray[k].READYSRC1 = 1;
						schedulearray[k].TAGSRC1 = -1;
						schedulearray[k].READYSRC2 = 1;
						schedulearray[k].TAGSRC2 = -1;
					}
				}
				temppointissue++;
				(*sqentry)--;
				// Update FROB
				frobarray[tempi[i].TAG].STAGE = EX;
				frobarray[tempi[i].TAG].CYCLEEX = *clockcyc;
				goto y;
			}
		}
		y: ;
	}
	//clear issue temp
	for(int i=0; i<s; i++)
	{
		tempi[i].TAG = 11000;
	}
}