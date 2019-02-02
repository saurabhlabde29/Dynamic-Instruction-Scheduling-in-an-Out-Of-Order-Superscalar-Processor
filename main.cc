#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include"main.h"
#include"headers.h"
using namespace std;

int main(int argc,char *argv[])
{
	S = atoi(argv[1]);
    N = atoi(argv[2]);
	BLOCKSIZE = atoi(argv[3]);
	L1SIZE = atoi(argv[4]);
	L1ASSOC = atoi(argv[5]);
	L2SIZE = atoi(argv[6]);
	L2ASSOC = atoi(argv[7]);
	tracefile = argv[8];
	
	FILE *f = NULL;
	f = fopen(argv[8],"r");
	int y=0; // init for tag pointer
	int *itag = &y; // tag pointer
	int z=0; //init for bottom pointer
	int *bottompointer = &z; // bottom pointer
	int w=0; //init for dq entry
	int *dqentry = &w; // dq entry
	int v=0; //init for sq entry
	int *sqentry = &v; // sq entry
	int r=0; // init for clock cycles
	int *clockcyc = &r; // clock cycles
	int completed = 0;

	DISPATCHQUEUE dispatcharray[2*N];
	SCHEDULINGQUEUE schedulearray[S];
	FUNCUNITS funcarray[10000];
	REGFILE regfilearray[10000];
	FROB frobarray[10000];
	TEMPDISPATCH tempd[2*N];
	TEMPISSUE tempi[S];
	//Struct initializations
	for(int i=0;i<(2*N);i++)
	{
		dispatcharray[i].TAG=-1;
		dispatcharray[i].STAGE=0;
	}
	for(int i=0;i<S;i++)
	{
		schedulearray[i].TAG=-1;
		schedulearray[i].READYSRC1=1;
		schedulearray[i].READYSRC2=1;
		schedulearray[i].TAGSRC1=-1;
		schedulearray[i].TAGSRC2=-1;
	}
	for(int i=0;i<10000;i++)
	{
		//funcunit
		funcarray[i].TAG=-1;
		funcarray[i].CYCLE=0;
		funcarray[i].COUNTINST=0;
		//regfile
		regfilearray[i].TAG=-1;
		regfilearray[i].VALID=1;
		//fakerob
		frobarray[i].STAGE=0;
		frobarray[i].TAG=-1;
		frobarray[i].TYPE=0;
		frobarray[i].DEST=0;
		frobarray[i].SRC1=0;
		frobarray[i].SRC2=0;
		frobarray[i].FINISH=0;
		frobarray[i].CYCLEIF=0;
		frobarray[i].CYCLEID=0;
		frobarray[i].CYCLEIS=0;
		frobarray[i].CYCLEEX=0;
		frobarray[i].CYCLEWB=0;
	}
	for(int i=0;i<(2*N);i++)
	{
		tempd[i].TAG=-1;
		tempd[i].STAGE=0;
	}
	for(int i=0;i<S;i++)
	{
		tempi[i].TAG=11000;
		tempi[i].READYSRC1=1;
		tempi[i].READYSRC2=1;
		tempi[i].TAGSRC1=-1;
		tempi[i].TAGSRC2=-1;
	}
	//Main Loop
	while(completed<10000)
    {	completed=executefunc(N,S,schedulearray,funcarray,regfilearray,frobarray,clockcyc,completed);
		issuefunc(N,S,schedulearray,tempi,frobarray,funcarray,sqentry,clockcyc);
		dispatchfunc(N,S,frobarray,dispatcharray,sqentry,schedulearray,dqentry,regfilearray,tempd,clockcyc);
		fetchfunc(f,N,S,itag,frobarray,bottompointer,dispatcharray,dqentry,clockcyc);
		(*clockcyc)++;
	}
	//Print 
	for(int i=0; i<10000; i++)
    {
    	cout<<frobarray[i].TAG<<" fu{"<<frobarray[i].TYPE<<"} src{"<<frobarray[i].SRC1<<","<<frobarray[i].SRC2<<"} dst{"<<frobarray[i].DEST<<"} IF{"<<frobarray[i].CYCLEIF<<","<<frobarray[i].CYCLEID-frobarray[i].CYCLEIF<<"} ID{"<<frobarray[i].CYCLEID<<","<<frobarray[i].CYCLEIS-frobarray[i].CYCLEID<<"} IS{"<<frobarray[i].CYCLEIS<<","<<frobarray[i].CYCLEEX-frobarray[i].CYCLEIS<<"} EX{"<<frobarray[i].CYCLEEX<<","<<frobarray[i].CYCLEWB-frobarray[i].CYCLEEX<<"} WB{"<<frobarray[i].CYCLEWB<<",1}"<<endl;
    }

    cout.precision(2);
 	cout<<"CONFIGURATION"<<endl;
 	cout<<"superscalar bandwidth (N) = "<<N<<endl;
 	cout<<"dispatch queue size (2*N) = "<<2*N<<endl;
 	cout<<"schedule queue size (S)   = "<<S<<endl;
 	cout<<"RESULTS"<<endl;
 	cout<<"number of instructions = 10000"<<endl;
 	cout<<"number of cycles       = "<<*clockcyc<<endl;
 	cout<<"IPC                    = "<<fixed<<(float(10000.0/(*clockcyc)))<<endl;
	
}