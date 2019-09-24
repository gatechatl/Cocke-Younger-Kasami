#ifndef __RuleProcessor__H
#define __RuleProcessor__H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "SCFGRule.h"
#include "math.h"
using namespace std;

class RuleProcessor{
public:
	   RuleProcessor(string infileName);
	   int numRule();
	   int numNT();
	   vector<SCFGRule>& getRules();
	   vector<string>& getNTs();
private:
	   string fileName;
	   vector<string> NTs;
	   vector<SCFGRule> rules;
};


#endif
