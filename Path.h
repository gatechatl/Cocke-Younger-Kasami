#include "SCFGRule.h"

	class Path{
		   private:
	               //SCFGRule rule;
		       int I,K,J, flag, y_val, z_val;
		       double prob;
		       char z[], y[];
			char * yy;
			char * zz;
		   public:
			   Path();
			   Path(bool boo);
			   //void setRule(SCFGRule r);
			   //SCFGRule getRule();
			   void setIKJ(int i, int k, int j);
			   int getI();
			   int getK();
			   int getJ();
			   void getZ(char z1[]);
			   void getY(char y1[]);
			   int getFlag();
			   void setYZFlag(char y1[], char z1[], int f);
			   void setYZFlag(int val_y, int val_z, int f);
			   void setProb(double p);
			   double getProb();
			   char *getZp();
			   char *getYp();
			   int getYVal();
			   int getZVal();
		   };
