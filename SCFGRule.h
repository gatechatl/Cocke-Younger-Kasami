#ifndef __SCFGRule__H
#define __SCFGRule__H
#include <string>
using namespace std;

class SCFGRule{
public :
	   SCFGRule();
	   //void setHead(string inHead);
	   void setHead(char inHead[]);
	   //string getHead();
	   void getHead(char h1[]);
	   //void setY(string inY);
	   void setY(char inY[]);
	   //string getY();
	   void getY(char y1[]);
	   //void setZ(string inZ);
	   void setZ(char inZ[]);
	   //string getZ();
	   void getZ(char z1[]);
	   void setProb(double inProb);
	   double getProb();
	   void setFlag(int inFlag);
	   int getFlag();
	   void setY_Val(int val);
	   int getY_Val();
	   void setZ_Val(int val);
	   int getZ_Val();
	   int getH_Val();
	   void setH_Val(int val);
private :
	   char head[50];
	   char y[50];
	   char z[50];
	   double prob;
	   int flag;
	   int y_val;
	   int z_val;
	   int h_val;
};
#endif
