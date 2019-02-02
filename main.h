#ifndef main_h
#define main_h
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;

enum pipestage
{
	IF,
	ID,
	IS,
	EX,
	WB,
};

struct DISPATCHQUEUE
{
	int TAG;
	int STAGE;
};

struct SCHEDULINGQUEUE
{
	int TAG;
	int READYSRC1;
	int READYSRC2;
	int TAGSRC1;
	int TAGSRC2;
};

struct FUNCUNITS
{
	int TAG;
	int CYCLE;
	int COUNTINST;
};

struct REGFILE
{
	int TAG;
	int VALID;
};

struct FROB
{
	int STAGE;
	int TAG;
	int TYPE;
	int DEST;
	int SRC1;
	int SRC2;
	int FINISH;
	int CYCLEIF;
	int CYCLEID;
	int CYCLEIS;
	int CYCLEEX;
	int CYCLEWB;
};
 
struct TEMPDISPATCH
{
	int TAG;
	int STAGE;
};

struct TEMPISSUE
{
	int TAG;
	int READYSRC1;
	int READYSRC2;
	int TAGSRC1;
	int TAGSRC2;
};

int S;
int N;
int BLOCKSIZE;
int L1SIZE;
int L1ASSOC;
int L2SIZE;
int L2ASSOC;
string tracefile;

#endif