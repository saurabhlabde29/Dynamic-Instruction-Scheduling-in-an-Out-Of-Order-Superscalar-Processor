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

int executefunc(int n, int s, SCHEDULINGQUEUE schedulearray[], FUNCUNITS funcarray[], REGFILE regfilearray[], FROB frobarray[10000], int *clockcyc, int completed)
{
	for(int i=0; i<10000; i++)
	{
		if(funcarray[i].COUNTINST == funcarray[i].CYCLE && funcarray[i].TAG != -1 && funcarray[i].CYCLE>0)
		{
			frobarray[funcarray[i].TAG].FINISH = 1;
			if(funcarray[i].TAG == regfilearray[frobarray[funcarray[i].TAG].DEST].TAG)
			{
				regfilearray[frobarray[funcarray[i].TAG].DEST].VALID = 1;
			}
			for(int j=0;j<s;j++)
			{
				if(schedulearray[j].TAGSRC1 == funcarray[i].TAG)
				{
					schedulearray[j].READYSRC1 = 1;
				}
				if(schedulearray[j].TAGSRC2 == funcarray[i].TAG)
				{
					schedulearray[j].READYSRC2 = 1;
				}
			}
			
			// update FROB
			frobarray[funcarray[i].TAG].STAGE = WB;
			frobarray[funcarray[i].TAG].CYCLEWB = *clockcyc;
			
			completed++;
			funcarray[i].TAG = -1;
			funcarray[i].CYCLE = 0;
			funcarray[i].COUNTINST = 0;
		}
		funcarray[i].COUNTINST++;
	}
	return completed;
}