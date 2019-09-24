#ifndef __CYK__H
#define __CYK__H
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include "SCFGRule.h"
#include "RuleProcessor.h"
#include "Path.h"
#include<stdlib.h>
#include<ctype.h>
using namespace std;
struct Test {
    int a;
    int b;
    int c;
};
class CYK{

public:
	CYK(string SCFGFileName,string seq);
	void parse_rules(vector<SCFGRule> cfgrules);
	void copyArray(string seq);
	double getbase_prob(string nt,string xi);
    SCFGRule getbase_rule(string nt,string xi);
    int getNT_Index(char nt[]);
    void CYK_DP();
    double getScore();
    double getPairScore();
    void resetT();
    void printPath(string nt,int n1,int n2);
    vector<char>& printseq_Pair();
    vector<SCFGRule>& getListAt(int Index);
    int pf_index( int i, int j, int N);
    void InitDoublesMatrix( double **Q, int size, char name[]);
    void InitPathMatrix( Path **p, int size, char name[]);
    void freeMem();    
    void nonZeroInit( double m1[]);
    void Perform_DP(double m1[]);
    void nonZeroInit( Path p1[]);
    string printseq_Pair2();
private:


	   RuleProcessor rfp ;
	   string sequence;
	   //double[][][] mm;
	   //double mm[][];
	   vector<vector<vector<double> > > m;
	   double *mm;
	   //double[][][] *m;
	   //double **m;
	   vector<vector<vector<Path> > > pt;
	   Path* ptt;
	   vector<int> pair;
	   char pairing[500];
	   vector<char> pairsequence;
           vector<SCFGRule>& rules;
           vector<string>& NTs;
	   char NTTs[100][20];
	   SCFGRule *newRuleList;
	   list<vector<SCFGRule> > rulelist;
	   int pairnum;
	   double score;
	   int window_size;
       double pairscore;
       int t;
       int L;
       int M;
	int *NTLoc;
};
#endif
