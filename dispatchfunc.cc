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
void dispatchfunc(int n, int s, FROB frobarray[10000], DISPATCHQUEUE dispatcharray[], int *sqentry, SCHEDULINGQUEUE schedulearray[], int *dqentry, REGFILE regfilearray[10000], TEMPDISPATCH tempd[], int *clockcyc)
{
	int tempsize = 0;
	int temppoint = 0;
	
	// Add to instructions in ID stage to temp struct
	for(int i=0;i<(2*n);i++)
	{
		if(dispatcharray[i].STAGE == ID && tempsize<(2*n) && dispatcharray[i].TAG >= 0)
		{
			tempd[tempsize].TAG = dispatcharray[i].TAG;
			tempd[tempsize].STAGE = dispatcharray[i].STAGE;
			tempsize++;
		}
	}
	// Sort the temp struct in ascending order
	int TAG_temp;
	int STAGE_temp;
	for(int i=0; i<tempsize-1; i++)
	{
		for(int j=0; j<tempsize-i-1; j++)
		{
			if(tempd[j].TAG > tempd[j+1].TAG)
			{
				TAG_temp=tempd[j].TAG;
				STAGE_temp=tempd[j].STAGE;
				
				tempd[j].TAG=tempd[j+1].TAG;
				tempd[j].STAGE=tempd[j+1].STAGE;
				
				tempd[j+1].TAG=TAG_temp;
				tempd[j+1].STAGE=STAGE_temp;
			}
		}			
	}
	// Sending to scheduling queue and updating ROB (ID -> IS)
	while((*sqentry)<s && temppoint<n)
	{
		for(int j=0; j<s; j++)
		{
			if(schedulearray[j].TAG<0 && tempd[temppoint].TAG >= 0)
			{
				// send to scheduling queue from temp struct
				schedulearray[j].TAG = tempd[temppoint].TAG;
				// remove corresponding entry from dispatch queue
				for(int i=0; i<(2*n); i++)
				{
					if(tempd[temppoint].TAG == dispatcharray[i].TAG)
					{
						dispatcharray[i].TAG=-1;
						dispatcharray[i].STAGE=0;
					}
				}
				// update FROB  
				frobarray[tempd[temppoint].TAG].STAGE = IS;
				frobarray[tempd[temppoint].TAG].CYCLEIS = *clockcyc;
				// register renaming
					// renaming source
				if(regfilearray[frobarray[tempd[temppoint].TAG].SRC1].VALID == 1 || frobarray[tempd[temppoint].TAG].SRC1 == -1)
				{
					schedulearray[j].READYSRC1 = 1;
					schedulearray[j].TAGSRC1 = -1;
				}
				else
				{
					schedulearray[j].READYSRC1 = 0;
					schedulearray[j].TAGSRC1 = regfilearray[frobarray[tempd[temppoint].TAG].SRC1].TAG;	
				}
				if(regfilearray[frobarray[tempd[temppoint].TAG].SRC2].VALID == 1 || frobarray[tempd[temppoint].TAG].SRC2 == -1)
				{
					schedulearray[j].READYSRC2 = 1;
					schedulearray[j].TAGSRC2 = -1;
				}
				else
				{
					schedulearray[j].READYSRC2 = 0;
					schedulearray[j].TAGSRC2 = regfilearray[frobarray[tempd[temppoint].TAG].SRC2].TAG;	
				}
				// renaming destination
				if(frobarray[tempd[temppoint].TAG].DEST >=0)
				{
					regfilearray[frobarray[tempd[temppoint].TAG].DEST].TAG = frobarray[tempd[temppoint].TAG].TAG;
					regfilearray[frobarray[tempd[temppoint].TAG].DEST].VALID = 0;
				}

				(*sqentry)++;
				(*dqentry)--;
				goto x;
			}
		}
		x:
		temppoint++;
	}
	// clearing temp d
	for(int i=0; i<(2*n); i++)
	{
		tempd[i].TAG = -1;
		tempd[i].STAGE = 0;
	}
	// change from IF to ID
	for(int i=0; i<(2*n); i++)
	{
		if(dispatcharray[i].STAGE == IF)
		{
			dispatcharray[i].STAGE = ID;
			frobarray[dispatcharray[i].TAG].STAGE = ID;
			frobarray[dispatcharray[i].TAG].CYCLEID = *clockcyc;
		}
	}
}