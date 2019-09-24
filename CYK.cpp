//============================================================================
// Name        : CYK.cpp
// Author      : Timothy Shaw, Ying Zheng
// Version     : 
// Copyright   :
// Description : Liming Cai's Lab
//============================================================================

#include "CYK.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#define MINNUM -5.0e10;
#define ARRSIZE 50;
using namespace std;


CYK::CYK(string SCFGFileName,string seq):
	rfp(SCFGFileName),
	rules(rfp.getRules()),
	NTs(rfp.getNTs())		
{
	sequence = seq;

	M = NTs.size();
	window_size = seq.length();
	L = window_size;
	t = 0;
	pairnum = 0;
	score = 0;
	pairscore = 0;

	for (int i = 0; i < NTs.size(); i++) {
	    strcpy(NTTs[i], NTs[i].c_str());
	}

  	NTLoc = (int *) calloc( M, sizeof( int));
	// initialize the rules based on terminal
	for (int i = 0; i < rules.size(); i++) {
	    char getStringHead[50];
	    rules[i].getHead(getStringHead);
	    rules[i].setH_Val(getNT_Index(getStringHead));
	    char getStringY[50];
	    rules[i].getY(getStringY);
	    char getStringZ[50];
	    rules[i].getZ(getStringZ);
	    rules[i].setY_Val(getNT_Index(getStringY));
	    rules[i].setZ_Val(getNT_Index(getStringZ));
	    
	}	

	for (int i = rules.size() - 1; i >= 0; i--) {
	  NTLoc[rules[i].getH_Val()] = i;
	}
	for (int i = 0; i < M; i++) {
	  //cout << NTLoc[i] << endl;
	}
	//exit(1);
	newRuleList = new SCFGRule[rules.size()];

	parse_rules(rules);


	int arraySize = M*window_size*window_size;

	ptt = new Path[arraySize];
	nonZeroInit(ptt);

	InitDoublesMatrix( &mm, arraySize, "mm");

	int count = 0;

	pair.resize(L);
	
	// initialize
	//pairing = (int *) calloc( window_size, sizeof( int));

	pairsequence.resize(L);

	//
}

/* ******************************************** */
void CYK::nonZeroInit( double m1[]) {
  // Set Q[i, i-1] = 1.

	int count = 0;
        for(int i = 0; i < M; i++) {
	    for (int j = 0; j < window_size; j++) {
		for (int k = 0; k < window_size; k++) {
		    //cout << pf_index(i, j, k) << endl;
                    m1[ pf_index(i, j, k)] = 0;
		    count++;
		}
	    }
        }	
}
/* ******************************************** */
void CYK::nonZeroInit( Path p1[]) {
  // Set Q[i, i-1] = 1.

	int count = 0;
        for(int i = 0; i < M; i++) {
	    for (int j = 0; j < window_size; j++) {
		for (int k = 0; k < window_size; k++) {
		    //cout << pf_index(i, j, k) << endl;
                    Path p;
		    //cout << p.getI() << endl;
		    p1[ pf_index(i, j, k)] = p;
		    count++;
		}
	    }
        }	
}
/* ********************************************* */

void CYK::freeMem() {
    free(mm);
    free(ptt);
    //free(pairing);
}
//void InitLDoublesMatrix( DBL_TYPE **Q, int size, char name[]) {
void CYK::InitDoublesMatrix( double **Q, int size, char name[]) {
	
  // Allocate cleared memory for a DBL_TYPEs matrix.
	
  
  *Q = (double *) calloc( size, sizeof( double));
  if( *Q == NULL) {
    printf("Unable to allocate memory for %s!\n", name);
    exit(1);
  }
	
}

//void InitLDoublesMatrix( DBL_TYPE **Q, int size, char name[]) {
void CYK::InitPathMatrix( Path **p, int size, char name[]) {
	
  // Allocate cleared memory for a DBL_TYPEs matrix.
	
  *p = (Path *) calloc( size, sizeof( Path));
  
  if( *p == NULL) {
    printf("Unable to allocate memory for %s!\n", name);
    exit(1);
  }
	
}
/* ******************************************** */
int CYK::pf_index( int i, int j, int N) {
     return i  + j * M + N * M * window_size;
} 

void CYK::parse_rules(vector<SCFGRule> cfgrules){

	for (int i = 0; i < rules.size(); i++) {
	    newRuleList[i] = cfgrules[i];
	    char head[50];
	    newRuleList[i].getHead(head);
	    //cout << head << "\t" << newRuleList[i].getH_Val() << "\t" << newRuleList[i].getY_Val() << "\t" << newRuleList[i].getZ_Val() << "\t" << newRuleList[i].getProb() << endl;
	}
	//exit (1);
}

vector<SCFGRule>& CYK::getListAt(int Index){
	list<vector<SCFGRule> >::iterator it;
	it = rulelist.begin();
	for(int i = 0; i < Index; i++){
		it++;
	}
	return *it;
}

void CYK::copyArray(string seq){
	sequence = seq;

	
	for(int v = 0; v < M; v++){
		for(int i = 1; i < window_size; i++){
			for(int j = i; j < window_size; j++){
				//newarray[v][i-1][j-1] = mm[pf_index(v, i, j)];//m[v][i][j];
				mm[pf_index(v, i -1, j - 1)] = mm[pf_index(v, i, j)];
				//Path p = ptt[pf_index(v, i, j)];//pt[v][i][j];				
				//p.setIKJ(p.getI() - 1, p.getJ() - 1, p.getK() - 1);
				//path[v][i - 1][j - 1] = ptt[pf_index(v, i, j)];//p;//ptt[pf_index(v, i, j)];//pt[v][i][j];				
				
				/*ptt[pf_index(v, i - 1, j - 1)] = ptt[pf_index(v, i, j)];
				Path p = ptt[pf_index(v, i - 1, j - 1)];
				if (p.getI() != -1) {
					p.setIKJ(p.getI() - 1, p.getK() - 1, p.getJ() - 1);
					//cout << p.getI() << "\t" << p.getJ() << "\t" << p.getK() << endl;

				} 
				ptt[pf_index(v, i - 1, j - 1)] = p;*/
			}
		}
	}

	for(int v = 0; v < M; v++) {
		int j = L-1;
		for(int i = 0; i < L; i++) {
			mm[pf_index(v, i, j)] = MINNUM;
			//m[v][i][j] = MINNUM;
		}
	}

	for(int v = 0; v < M; v++) { 
		int i = L-1;
		for(int j = 0; j < L; j++) {
			mm[pf_index(v, i, j)] = MINNUM;
			//m[v][i][j] = MINNUM;
		}
	}

	for(int v = 0; v < M; v++){
		int i = L-1;


    		string xi = sequence.substr(i, 1);
    		string nt = NTs[v];
		double prob = mm[pf_index(v, i, i)] = getbase_prob(nt, xi);
		//cout << mm[pf_index(v, i, i)] << endl;    		
		SCFGRule rule = getbase_rule(nt, xi);

		Path p;
		char returnY[50];
		char returnZ[50];
		rule.getY(returnY);
		rule.getZ(returnZ);		        	
		if (prob > -5.0e10) {
 	            p.setYZFlag(rule.getY_Val(), rule.getZ_Val(), rule.getFlag());
		    //cout << p.getYVal() << "\t" << p.getZVal() << endl;
		}
		//cout << rule.getY_Val() << "\t" << rule.getZ_Val() << endl;
		//p.setYZFlag(returnY, returnZ, rule.getFlag());
    		p.setIKJ(i,i,i);
		p.setProb(mm[pf_index(v, i, i)]);
		ptt[pf_index(v, i, i)] = p;

		//cout << v << endl;
	}

	for(int i = L-2; i >= 0; i--){
	    int j = L-1;
		for(int v = 0; v < M; v++){
		  int startp = NTLoc[v];
		  int endp = rules.size() - 1;
		if (v + 1 == M) {
		  endp = NTLoc[v + 1] - 1;
		}
		int mid = (int)((float)(i + j - 1) / (float) 2);
    		for(int k = i; k <= mid; k++) {
		    bool exit = false;
		    //for (int r = 0; r < rules.size(); r++) {
		    for (int r = startp; r <= endp; r++) {
		      if (newRuleList[r].getH_Val() == v) {
					//char head[50];
					//newRuleList[r].getHead(head);
					
    				   //int flag = newRuleList[r].getFlag();
    				   if(newRuleList[r].getFlag() == 2){
    					   double prob = newRuleList[r].getProb();
					   //cout << head << "\t" << v << "\t" << prob << "\t" << mm[pf_index(newRuleList[r].getY_Val(),i ,k)] << "\t" << mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] << "\t" << newRuleList[r].getZ_Val() << ":" << k + 1 << ":" << j << endl;
					   double q = mm[pf_index(newRuleList[r].getY_Val(),i ,k)] + mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] + prob;
					   if(q > mm[pf_index(v, i, j)]) {
    						   mm[pf_index(v, i, j)] = q;
						   //cout << q << endl;
    						   Path p;
						   //char returnY[50];
					           //char returnZ[50];
						   //newRuleList[r].getY(returnY);
						   //newRuleList[r].getZ(returnZ);
						   //cout << returnY << "\t" << returnZ << endl;
					           p.setYZFlag(newRuleList[r].getY_Val(), newRuleList[r].getZ_Val(), newRuleList[r].getFlag());
						   //cout << p.getYVal() << "\t" << p.getZVal() << endl;
    						   p.setIKJ(i, k, j);
    						   p.setProb(q);
    						   ptt[pf_index(v, i, j)] = p;
						   if ((newRuleList[r].getH_Val() == 4 || newRuleList[r].getH_Val() == 5) && newRuleList[r].getY_Val() >= 14)
							exit = true;
						   
    					   } // q > mm
    				    } // if Flag
				 } // if newRuleList
    		    } // r	
		    if (exit)
		        k = mid - 1;	    
    		} // k

    		for(int k = j - 1; k > mid; k--) {
		    bool exit = false;
		    //for (int r = 0; r < rules.size(); r++) {
		        for (int r = startp; r <= endp; r++) {
				if (newRuleList[r].getH_Val() == v) {
					//char head[50];
					//newRuleList[r].getHead(head);
					
    				   //int flag = newRuleList[r].getFlag();
    				   if (newRuleList[r].getFlag() == 2){
    					   double prob = newRuleList[r].getProb();
					   //cout << head << "\t" << v << "\t" << prob << "\t" << mm[pf_index(newRuleList[r].getY_Val(),i ,k)] << "\t" << mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] << "\t" << newRuleList[r].getZ_Val() << ":" << k + 1 << ":" << j << endl;
					   double q = mm[pf_index(newRuleList[r].getY_Val(),i ,k)] + mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] + prob;
					   if(q > mm[pf_index(v, i, j)]) {
    						   mm[pf_index(v, i, j)] = q;
						   //cout << q << endl;
    						   Path p;

						   //cout << returnY << "\t" << returnZ << endl;
					           p.setYZFlag(newRuleList[r].getY_Val(), newRuleList[r].getZ_Val(), newRuleList[r].getFlag());
						   //cout << p.getYVal() << "\t" << p.getZVal() << endl;
    						   p.setIKJ(i, k, j);
    						   p.setProb(q);
    						   ptt[pf_index(v, i, j)] = p;
						   if (newRuleList[r].getH_Val() == 4 || newRuleList[r].getH_Val() == 5 || newRuleList[r].getH_Val() == 18)
							exit = true;
						   if (newRuleList[r].getZ_Val() >= 14 && newRuleList[r].getH_Val() <= 17)
							exit = true;
    					   } // q > mm
    				    } // if Flag
			} // if newRuleList
    		    } // r	
		    if (exit)
		        k = mid;	    
    		} // k
		} // v
	} //i
	//cout << "finish DP" << endl;
}


int CYK::getNT_Index(char nt[]){
	int result = 0;
	for(int i = 0; i < M; i++){
		//cout << ":" << NTTs[i] << ":" << endl;
		if (strcmp(nt,NTTs[i]) == 0){
			//result = i;
			//cout << "found" << endl;
			return i;
			break;
		}
	}
	return result;
}

double CYK::getbase_prob(string nt,string xi){
	double result = MINNUM;
	for(int i = 0; i < rules.size(); i++){
		SCFGRule rule = rules[i];
		char getString[50];
		rule.getHead(getString);
		string r_head = getString;
		rule.getY(getString);
		string r_y = getString;
		double r_prob = rule.getProb();
		int r_flag = rule.getFlag();
		if (r_flag==1 && strcmp(nt.c_str(), r_head.c_str()) == 0 && strcmp(xi.c_str(), r_y.c_str()) == 0){
			//if (!(strcmp(nt.c_str(), "baseU") == 0 || strcmp(nt.c_str(), "baseA") == 0 || strcmp(nt.c_str(), "base") == 0)) {
			    //cout << "@#$%%$^$%^#%^#$%#%#%#$%#$% BLAST ME" << "\t" << nt << r_prob << endl;
			//}
			return r_prob;
			break;
		}
	}
    return result;
}

SCFGRule CYK::getbase_rule(string nt,string xi) {
	SCFGRule result;

	for(int i = 0; i < rules.size(); i++){
		//SCFGRule rule = rules[i];
		char getStringH[50];
		rules[i].getHead(getStringH);
		string r_head = getStringH;
		char getStringY[50];
		rules[i].getY(getStringY);
		string r_y = getStringY;
		
		
		int r_flag = rules[i].getFlag();
		if (r_flag==1 && strcmp(nt.c_str(), r_head.c_str()) == 0 && strcmp(xi.c_str(), r_y.c_str()) == 0) {
			//cout << r_head << "\t" << r_y << endl;
			//result = rules[i];
			//rules[i].setY_Val(getNT_Index(r_y.c_str()));
			//rules[i].setZ_Val(getNT_Index(
			return rules[i];
			break;
		}
	}
	return result;
}


void CYK::Perform_DP(double m1[]) {

}

void CYK::CYK_DP(){

    //cout << "Team work" << endl;

    /*for (int i = 0; i < rules.size(); i++) {
	//newRuleList[i] = cfgrules[i];
	    char head[50];
	    newRuleList[i].getHead(head);
	    //cout << "booyah: " << head << "\t" << newRuleList[i].getH_Val() << "\t" << newRuleList[i].getY_Val() << "\t" << newRuleList[i].getZ_Val() << "\t" << newRuleList[i].getProb() << endl;
    }*/
   //cout << "M: " << M << "\t" << L << endl;
   for(int v = 0; v< M; v++) {
    	for(int i = 0; i <= L - 1; i++){
    		for(int j = 0; j < window_size; j++){
    			mm[pf_index(v, i, j)] = MINNUM;
    		}
    		string xi = sequence.substr(i, 1);
    		string nt = NTs[v];
		double prob = mm[pf_index(v, i, i)] = getbase_prob(nt, xi);
		//cout << mm[pf_index(v, i, i)] << endl;    		
		SCFGRule rule = getbase_rule(nt, xi);

		Path p;
		char returnY[50];
		char returnZ[50];
		rule.getY(returnY);
		rule.getZ(returnZ);		        	
		if (prob > -5.0e10) {
 	            p.setYZFlag(rule.getY_Val(), rule.getZ_Val(), rule.getFlag());
		    //cout << p.getYVal() << "\t" << p.getZVal() << endl;
		}
		//cout << rule.getY_Val() << "\t" << rule.getZ_Val() << endl;
		//p.setYZFlag(returnY, returnZ, rule.getFlag());
    		p.setIKJ(i,i,i);
		p.setProb(mm[pf_index(v, i, i)]);
		ptt[pf_index(v, i, i)] = p;
		
		//if (v == 18 && i == 79) {
		//	cout << "BLAH BLAH BLAH BLAH" << endl;
		//	cout << "SCORE:\t" << mm[pf_index(v, i, i)] << endl;;
		//}
		//cout << v << "\t" << i << endl;
    	}
    }
    for(int i = L-2; i >= 0; i--){
        //cout << i << "\t" << count << endl;
    	for(int j = i+1; j <= L-1; j++){
	    for(int v = 0; v < M; v++) {
		int mid = (int)((float)(i + j - 1) / (float) 2);
    		for(int k = i; k <= mid; k++) {
		    bool exit = false;
		    for (int r = 0; r < rules.size(); r++) {
				if (newRuleList[r].getH_Val() == v) {
					char head[50];
					newRuleList[r].getHead(head);
					
    				   int flag = newRuleList[r].getFlag();
    				   if(flag == 2){
    					   double prob = newRuleList[r].getProb();
					   //cout << head << "\t" << v << "\t" << prob << "\t" << mm[pf_index(newRuleList[r].getY_Val(),i ,k)] << "\t" << mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] << "\t" << newRuleList[r].getZ_Val() << ":" << k + 1 << ":" << j << endl;
					   double q = mm[pf_index(newRuleList[r].getY_Val(),i ,k)] + mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] + prob;
					   if(q > mm[pf_index(v, i, j)]) {
    						   mm[pf_index(v, i, j)] = q;
						   //cout << q << endl;
    						   Path p;
						   //char returnY[50];
					           //char returnZ[50];
						   //newRuleList[r].getY(returnY);
						   //newRuleList[r].getZ(returnZ);
						   //cout << returnY << "\t" << returnZ << endl;
					           p.setYZFlag(newRuleList[r].getY_Val(), newRuleList[r].getZ_Val(), newRuleList[r].getFlag());
						   //cout << p.getYVal() << "\t" << p.getZVal() << endl;
    						   p.setIKJ(i, k, j);
    						   p.setProb(q);
    						   ptt[pf_index(v, i, j)] = p;
						   if ((newRuleList[r].getH_Val() == 4 || newRuleList[r].getH_Val() == 5) && newRuleList[r].getY_Val() >= 14)
							exit = true;
						   
    					   } // q > mm
    				    } // if Flag
			} // if newRuleList
    		    } // r	
		    if (exit)
		        k = mid - 1;	    
    		} // k

    		for(int k = j - 1; k > mid; k--) {
		    bool exit = false;
		    for (int r = 0; r < rules.size(); r++) {
				if (newRuleList[r].getH_Val() == v) {
					char head[50];
					newRuleList[r].getHead(head);
					
    				   int flag = newRuleList[r].getFlag();
    				   if(flag == 2){
    					   double prob = newRuleList[r].getProb();
					   //cout << head << "\t" << v << "\t" << prob << "\t" << mm[pf_index(newRuleList[r].getY_Val(),i ,k)] << "\t" << mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] << "\t" << newRuleList[r].getZ_Val() << ":" << k + 1 << ":" << j << endl;
					   double q = mm[pf_index(newRuleList[r].getY_Val(),i ,k)] + mm[pf_index(newRuleList[r].getZ_Val(), k+1, j)] + prob;
					   if(q > mm[pf_index(v, i, j)]) {
    						   mm[pf_index(v, i, j)] = q;
						   //cout << q << endl;
    						   Path p;

						   //cout << returnY << "\t" << returnZ << endl;
					           p.setYZFlag(newRuleList[r].getY_Val(), newRuleList[r].getZ_Val(), newRuleList[r].getFlag());
						   //cout << p.getYVal() << "\t" << p.getZVal() << endl;
    						   p.setIKJ(i, k, j);
    						   p.setProb(q);
    						   ptt[pf_index(v, i, j)] = p;
						   if (newRuleList[r].getH_Val() == 4 || newRuleList[r].getH_Val() == 5 || newRuleList[r].getH_Val() == 18)
							exit = true;
						   if (newRuleList[r].getZ_Val() >= 14 && newRuleList[r].getH_Val() <= 17)
							exit = true;
    					   } // q > mm
    				    } // if Flag
			} // if newRuleList
    		    } // r	
		    if (exit)
		        k = mid;	    
    		} // k

    	    } // v
	    
    	} // j
	
	//it++;	
    } // i
    //printPath("R", 0, L - 1);
    //exit(1);
}

void CYK::printPath(string nt,int n1, int n2) {
	if(n1 != n2){
		char newNT[50];
		strcpy(newNT, nt.c_str());
		int nt_index = getNT_Index(newNT);
		string y,z;
		int i,k,j, flag;

        flag = ptt[pf_index(nt_index, n1, n2)].getFlag();	
        i = ptt[pf_index(nt_index, n1, n2)].getI();
        k = ptt[pf_index(nt_index, n1, n2)].getK();
        j = ptt[pf_index(nt_index, n1, n2)].getJ();


	int y_val = ptt[pf_index(nt_index, n1, n2)].getYVal();
	int z_val = ptt[pf_index(nt_index, n1, n2)].getZVal();

	z = NTs[z_val];
	y = NTs[y_val];
	
	//cout << nt_index << "\t" << n1 << "\t" << n2 << endl;	
	//cout << y << "\t" << i << "\t" << k << endl;
	//cout << z << "\t" << k + 1 << "\t" << j << endl;
	//getNT_Index(char nt[])
        /*if((y.find("baseA")!=string::npos && z.find("S-and-baseU")!=string::npos) || (y.find("baseC")!=string::npos&&z.find("S-and-baseG")!=string::npos)
           || (y.find("baseU")!=string::npos&&z.find("S-and-baseA")!=string::npos) || (y.find("baseG")!=string::npos&&z.find("S-and-baseC")!=string::npos)
           || (y.find("baseU")!=string::npos&&z.find("S-and-baseG")!=string::npos) || (y.find("baseG")!=string::npos&&z.find("S-and-baseU")!=string::npos)){*/
	if (getNT_Index("baseA") == y_val && getNT_Index("S-and-baseU") == z_val || y_val == getNT_Index("baseC") && z_val == getNT_Index("S-and-baseG") || y_val == getNT_Index("baseG") && z_val == getNT_Index("S-and-baseC") || y_val == getNT_Index("baseU") && z_val == getNT_Index("S-and-baseA") || y_val == getNT_Index("baseU") && z_val == getNT_Index("S-and-baseG") || y_val == getNT_Index("baseG") && z_val == getNT_Index("S-and-baseU")) {
        	//cout << "Found pairing" << endl;
		pair[t] = i;
        	pair[t+1] = j;
        	t = t+2;
        	pairnum++;
        }
        printPath(y, i, k);
            if(flag == 2){
        	printPath(z, k+1, j);
            }
	}
}

vector<char>& CYK::printseq_Pair(){
	char c[L];
	strncpy(c,sequence.c_str(),L);
	for(int i = 0; i< L; i++){
		pairsequence[i] = c[i];
	}
    for(int c = 0; c < pairnum*2; c++){
    	pairsequence[pair[c]] = '(';
    	pairsequence[pair[c+1]] = ')';
    }

    for(int i =0; i < L; i++){
    	if(pairsequence[i]!='(' && pairsequence[i]!=')')
    	     pairsequence[i] = '.';
    }

    return pairsequence;
}

void CYK::resetT(){
	t = 0;
	pairnum = 0;
	score = 0;
}


string CYK::printseq_Pair2(){
    char c[L];
    char result[L];
    strncpy(c,sequence.c_str(),L);
    for(int i = 0; i< L; i++){
		pairing[i] = c[i];
    }
    for(int c = 0; c < pairnum*2; c= c + 2){
    	pairing[pair[c]] = '(';
    	pairing[pair[c+1]] = ')';
    }

    for(int i =0; i < L; i++){
    	if(pairing[i]!='(' && pairing[i]!=')')
    	     pairing[i] = '.';
    }
    for (int i = 0; i < L; i++) {
        result[i] = pairing[i];
	//cout << result[i];
    }
    //cout << endl;
    //cout << result << "hello" << endl;
    string s = result;
    return s;
}

double CYK::getScore(){

	//cout << endl;
	score = ptt[pf_index(0, 0, L-1)].getProb();
	//score = pt[0][0][L-1].getProb();
	return score;
}

double CYK::getPairScore(){
	int x =0, y = 0;
	for(int i = 0; i< L; i++){
		if(pairsequence[i]=='(')
			x = i;
		if(pairsequence[i]==')'){
			y = i;
			break;
		}
	}
	int d = y - x;
	if(d > 0)
		pairscore = (double)(pairnum*2/L);
	else
		pairscore = MINNUM;

	return pairscore;
}



