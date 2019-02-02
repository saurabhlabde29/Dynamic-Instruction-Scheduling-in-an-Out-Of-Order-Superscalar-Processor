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
void fetchfunc(FILE *f, int n, int s, int *itag,FROB frobarray[10000],int *bottompointer,DISPATCHQUEUE dispatcharray[10000], int *dqentry, int *clockcyc)
{
 	int s_count = 0;
 	int PC = 0;
 	int type = 0;
 	int dest = 0;
 	int src1 = 0;
 	int src2 = 0;
 	int memaddress = 0;
 	int i=0;
	
 	while(!feof(f) && (s_count < n) && (*dqentry < (2*n)))
 	{
 		fscanf(f, "%x %d %d %d %d %x\n",&PC, &type, &dest, &src1, &src2, &memaddress);
  		s_count++;
 		
		// Add to frob
		frobarray[*itag].STAGE=IF;
		frobarray[*itag].TAG=*itag;
		frobarray[*itag].TYPE=type;
		frobarray[*itag].DEST=dest;
		frobarray[*itag].SRC1=src1;
		frobarray[*itag].SRC2=src2;
		frobarray[*itag].CYCLEIF=*clockcyc;
		
		// Add to dispatch
		dispatcharray[*bottompointer].TAG=frobarray[*itag].TAG;
		dispatcharray[*bottompointer].STAGE=frobarray[*itag].STAGE;
		(*itag)++;
		(*bottompointer)++;
		//cout<<*dqentry<<endl;
		(*dqentry)++;
		if((*bottompointer) == 2*n)
		{
			(*bottompointer)=0;
		}
		i++;
 	}
}