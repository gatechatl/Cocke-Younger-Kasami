#include "Path.h"
#include <cstring>
#include <iostream>
//#include "SCFGRule.h"
#define MINNUM -5.0e10;
using namespace std;

Path::Path(){
	I = -1;
	K = -1;
	J = -1;
	y_val = -1;
	z_val = -1;
	prob = MINNUM;

}
Path::Path(bool boo) {
	I = -1;
	K = -1;
	J = -1;
	y_val = -1;
	z_val = -1;
	prob = MINNUM;
}
/*void Path::setRule(SCFGRule r){
	rule = r;
}

SCFGRule Path::getRule(){
	return rule;
}*/

void Path::setIKJ(int i, int k, int j){
	I = i;
	K = k;
	J = j;
}

int Path::getI(){
    return I;
}

int Path::getK(){
	return K;
}

int Path::getJ(){
	return J;
}

void Path::setProb(double p){
	prob = p;
}

double Path::getProb(){
	return prob;
}

char *Path::getZp() {
	return zz;
}
char *Path::getYp() {
	return yy;
}
void Path::getZ(char z1[]) {
	strcpy(z1, zz);
}
void Path::getY(char y1[]) {
	strcpy(y1, yy);
}
int Path::getFlag() {
	return flag;
}
void Path::setYZFlag(int val_y, int val_z, int f) {
    y_val = val_y;
    z_val = val_z;
    flag = f;
}
int Path::getYVal() {
    return y_val;
}
int Path::getZVal() {
    return z_val;
}
void Path::setYZFlag(char y1[], char z1[], int f) {
	//y = y1;
	//z = z1;
	yy = y1;
	zz = z1;
	//strcpy(y, yy);
	//strcpy(z, zz);
	//strncpy(y, y1, sizeof(y1));	
	//strncpy(z, z1, sizeof(z1));
	flag = f;
}
