#ifndef headers_h
#define headers_h

void dispatchfunc(int n, int s, FROB frobarray[10000], DISPATCHQUEUE dispatcharray[], int *sqentry, SCHEDULINGQUEUE schedulearray[], int *dqentry, REGFILE regfilearray[10000], TEMPDISPATCH tempd[], int *clockcyc)

int executefunc(int n, int s, SCHEDULINGQUEUE schedulearray[], FUNCUNITS funcarray[], REGFILE regfilearray[], FROB frobarray[10000], int *clockcyc, int completed)

void fetchfunc(FILE *f, int n, int s, int *itag,FROB frobarray[10000],int *bottompointer,DISPATCHQUEUE dispatcharray[10000], int *dqentry, int *clockcyc)

void issuefunc(int n, int s, SCHEDULINGQUEUE schedulearray[], TEMPISSUE tempi[], FROB frobarray[10000], FUNCUNITS funcarray[], int *sqentry, int *clockcyc)


#endif