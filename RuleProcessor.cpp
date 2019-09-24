//============================================================================
// Name        : RuleProcessor.cpp
// Author      : Timothy Shaw, Ying Zheng
// Version     :
// Copyright   :
// Description : Read the SCFG rules file
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "RuleProcessor.h"
using namespace std;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;



RuleProcessor::RuleProcessor(string infileName){
	fileName = infileName;
}

int RuleProcessor::numRule(){
	int numR = 0;
	fstream inStream;
	string s;

	inStream.open(fileName.c_str(),ios::in);
	if(inStream.fail()){
		cout<< "File Open Error!" << fileName <<endl;
		exit(1);
	}

    do{
    	getline(inStream,s);
	//cout << "Special: " << s << endl;
    	numR++;
    }while(!inStream.eof());
    inStream.close();

    return numR - 1;
}

int RuleProcessor::numNT(){
    int numNT = 0;
    fstream inStream;
    string s;

    inStream.open(fileName.c_str(),ios::in);
    if(inStream.fail()){
    	cout<< "File Open Error!"<<endl;
    	exit(1);
    }

    int count = 0;
    do{
    	getline(inStream,s);
    	int end = s.length()-1;
	size_t found = s.find_first_of(":");
	if (found != string::npos) {
		numNT++;
	}
    	//if(s.at(end)==';')
	//if (s.find(";", 0) != 0) 
   	//	numNT++;
	count++;
    }while(!inStream.eof());
    inStream.close();
    //cout << "Count " << count << endl;
    //cout << "numNT " << numNT << endl;
    return numNT;
}

vector<SCFGRule>& RuleProcessor::getRules(){
	rules.resize(numRule());
	NTs.resize(numNT());
	fstream inStream;
    string s;

    string head="",y,z;
    int flag;
    double prob;
    int first,second;

    int count = 0;
    int nt_count = 0;

    inStream.open(fileName.c_str(),ios::in);
    if(inStream.fail()){
    	cout<<"File Open Error!"<<endl;
    	exit(1);
    }
    //cout << "Opening File: " << fileName << endl;
    while(!inStream.eof()) {
	//head = "";
	//y = "";	//cout << head << "\t" << y << "\t" << z << "\t" << temp << endl;
	//z = "";
	prob = -99999;
    	getline(inStream,s);

    	int divider_pos = 0;//s.find_first_of(":");
	//cout << "Before " << divider_pos << endl;
    	bool has_head = false;
	size_t found1 = s.find_first_of(":");
	if (found1 != string::npos) {
	    has_head = true;    
	}//divider_pos >= 0;
	//cout << s << endl;
    	if (has_head){
    		first = s.find_first_of("<");
		//cout << "first " << first << endl;
    		second = s.find_first_of(">");
		//cout << "second " << second << endl;
    		head = s.substr(first+1, second - first - 1);
		//cout << "head " << head << endl;
    		NTs[nt_count] = head;

    		nt_count++;
    	}
	//cout << "After " << divider_pos << endl;
    	if(has_head){
    		divider_pos = s.find_first_of(":");
    	}
    	else{
    		divider_pos = s.find_first_of("|");
    	}

    	string right = s.substr(divider_pos+1);
    	bool is_base = false;
        size_t found = right.find_first_of("<");
	if (found == string::npos) {
	    is_base = true;
	}

    	if(is_base){
    		flag = 1;
    		first = right.find_first_of(" ");

    		y = right.substr(first+1, 1);
    		z = "";
    	}else{
    		flag = 2;
    		first = right.find_first_of("<");
    		second = right.find_first_of(">");
    		y = right.substr(first+1, second - first - 1);

    		right = right.substr(second+1);
    		first = right.find_first_of("<");
    		second = right.find_first_of(">");
    		z = right.substr(first+1, second - first - 1);
    	}

    	first = right.find_first_of("{");
	//cout << right << endl;
    	second = right.find_first_of("}");
    	string temp = right.substr(first+1,second - first - 1);


    	prob = log(atof(temp.c_str()));

	//cout << prob << endl;
	
        SCFGRule rule;

	char getStringH[50];
	strcpy(getStringH, head.c_str());
        rule.setHead(getStringH);
	char getStringY[50];
	strcpy(getStringY, y.c_str());
	rule.setY(getStringY);
	char getStringZ[50];
	strcpy(getStringZ, z.c_str());
        rule.setZ(getStringZ);
        rule.setProb(prob);
        rule.setFlag(flag);

	if (numRule() > count) {
            rules[count] = rule;
	    //cout << head << "\t" << y << "\t" << z << "\t" << flag << "\t" << prob << endl;
	}
	
	
	//cout << head << endl;
	//cout << y << endl;
	//cout << z << endl;
        count++;
	//cout << count << endl;

    } ;
    inStream.close();

    return rules;
}

vector<string>& RuleProcessor::getNTs(){
    return NTs;
}
