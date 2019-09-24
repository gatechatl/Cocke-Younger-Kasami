//============================================================================
// Name        : CYKTest.cpp
// Author      : Timothy Shaw, Ying Zheng
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "time.h"
#include "SCFGRule.h"
#include "RuleProcessor.h"
#include "CYK.h"
     #include  "utils.h"
     #include  "fold_vars.h"
     #include  "fold.h"
     #include  "part_func.h"
     #include  "inverse.h"
     #include  "RNAstruct.h"
     #include  "treedist.h"
     #include  "stringdist.h"
     #include  "profiledist.h"


using namespace std;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;


int main() {
     time_t seconds = time(NULL);
     string scfgFile = "scfg2";
     //string seqFile = "miRNA_sequence.txt";
     //string seqFile = "cyk_20000_human.txt";
     //string seqFile = "Human_Chicken_miRNA.txt";
     //string seqFile = "has-mir-complement.txt";
     //string seqFile = "revcom_8494_output.txt";
     //string seqFile = "revcom-hsa-mir.txt";
     string seqFile = "8494_output.txt";
     int num = 0;
     fstream inStream;
     string s;

     inStream.open(seqFile.c_str(),ios::in);
     if(!inStream){
    	 cout<< "File Open Error!"<<endl;
    	 exit(1);
     }
     int window_size = 80;
     double cyk_avg = -126.79;
     //double cyk_avg = -110.74;
     double cyk_stdev = 7.49;
     //double cyk_stdev = 6.74;
     double mfe_avg = -14.75;
     //double mfe_avg = -12.21;
     double mfe_stdev = 6.94;
     //double mfe_stdev = 6.15;
     cout << "initialization" << endl;
     do{
    	 getline(inStream,s);
    	 num++;
    	 int len = s.length();
	 bool valid = true;
	 if (num%2 == 0 && len < window_size) {
	     valid = false;
	     cout << s << "\t" << "0" << "\t" << "0" << "\t" << "Not long enough" << endl;
	 }
    	 if(num%2==0 && valid){
             
	     	 string newstr  = s.substr(0, window_size);
		 
		 CYK cyk(scfgFile, newstr);
		 cyk.CYK_DP();

		
		//cyk.printPath("R", 0 ,newstr.length()-1);

		//string result = cyk.printseq_Pair2();
		
		float e1;
		char *seq1 = (char*) malloc(sizeof(char)*(window_size + 1));
		strcpy(seq1, newstr.c_str());		
		initialize_fold(strlen(seq1));		
		temperature = 37.;		
		char *struct1 = (char* ) malloc(sizeof(char)*(strlen(seq1) + 1));
		e1 = fold(seq1, struct1);
		double zMFE = (mfe_avg - e1) / mfe_stdev;
		double cykScore = cyk.getScore();
		double zCYK = (cykScore - cyk_avg) / cyk_stdev;
		double combinedScore = zMFE + zCYK * 2;
		//cout << result << endl;
		//cout << newstr << "\t" << e1 << "\t" << zMFE << "\t" << cykScore << "\t" << zCYK << "\t" << struct1 << endl;
	        // cout << cyk.getScore() << endl;
		cyk.resetT();
		free_arrays();
		//exit(1);
		//cout << "hello world" << endl;
    		string best_seq = seq1;
		string best_Structure = struct1;
		double best_zMFE = zMFE;
		double best_zCYK = zCYK;
		double best_cykScore = cykScore;
		float best_e1 = e1;
		double best_combinedScore = combinedScore;
		for (int i = 1; i < len - window_size; i++){
    			 newstr = s.substr(i, window_size);

			 //cout << newstr << endl;
    			 //char file[50];
			 //strcpy(file, scfgFile.c_str());
			 //char str[50];
			 //strcpy(str, newstr.c_str());
			 //CYK cyk(file, str);
			 
			 //cout << "Initializaiton" << endl;
    			 cyk.copyArray(newstr);
			 strcpy(seq1, newstr.c_str());
			 initialize_fold(strlen(seq1));
		 	 e1 = fold(seq1, struct1);
			 
    			 //cyk.printPath("R", 0 ,newstr.length()-1);
			 //result = cyk.printseq_Pair2();
			 //cout << result << endl;

			zMFE = (mfe_avg - e1) / mfe_stdev;
			cykScore = cyk.getScore();
			zCYK = (cykScore - cyk_avg) / cyk_stdev;
			combinedScore = zMFE + zCYK * 2;
			if (combinedScore > best_combinedScore) {
			    best_zMFE = zMFE;
			    best_zCYK = zCYK;
			    best_cykScore = cykScore;
			    best_e1 = e1;
			    best_Structure = struct1;
			    best_seq = seq1;
			    best_combinedScore = combinedScore;
			}
			//cout << newstr << "\t" << e1 << "\t" << cyk.getScore() << "\t" << struct1 << endl;
			 
    			 //<< "\t" << cyk.getPairScore() << "\t" << cyk.printseq_Pair()
    			cyk.resetT();
			free_arrays();
			 
    	       }
		free(seq1);
		cyk.freeMem();
		cout << best_seq << "\t" << best_e1 << "\t" << best_zMFE << "\t" << best_cykScore << "\t" << best_zCYK << "\t" << struct1 << endl;
    		 //cout<< "the sequence length is: " + s.length();
    	 }
     }while(!inStream.eof());
     inStream.close();
     cout<< "Run time: " << (time(NULL)-seconds);

     return 0;
}
