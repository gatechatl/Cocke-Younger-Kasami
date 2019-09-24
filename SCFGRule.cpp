//============================================================================
// Name        : SCFGRule.cpp
// Author      : Timothy Shaw, Ying Zheng
// Version     :
// Copyright   :
// Description : SCFG rules in CNF
//============================================================================


#include <string>
#include <cstring>
#include "SCFGRule.h"
#define MINNUM -5.0e10;
using namespace std;

SCFGRule::SCFGRule(){
	strcpy(head, "");
	strcpy(y, "");
	strcpy(z, "");
	prob = MINNUM;
	z_val = 0;
	y_val = 0;
	h_val = 0;
}

/*void SCFGRule::setHead(string inHead){
	head = inHead;
}*/

void SCFGRule::setHead(char inHead[]){
	strcpy(head, inHead);
	//head = inHead;
}

/*string SCFGRule::getHead(){
	return head;
}*/
void SCFGRule::getHead(char h1[]){
	strcpy(h1, head);
}
/*void SCFGRule::setY(string inY){
	y = inY;
}*/
void SCFGRule::setY(char inY[]){
	strcpy(y, inY);
}

/*string SCFGRule::getY(){
	return y;
}*/
void SCFGRule::setY_Val(int val) {
        y_val = val;
}
int SCFGRule::getY_Val() {
	return y_val;
}
void SCFGRule::setZ_Val(int val) {
        z_val = val;
}
int SCFGRule::getZ_Val() {
	return z_val;
}
int SCFGRule::getH_Val() {
	return h_val;
}
void SCFGRule::setH_Val(int val) {
	h_val = val;
}
void SCFGRule::getY(char y1[]){
	strcpy(y1, y);
}

/*void SCFGRule::setZ(string inZ){
	z = inZ;
}*/
void SCFGRule::setZ(char inZ[]){
	strcpy(z, inZ);
}

/*string SCFGRule::getZ(){
	return z;
}*/
void SCFGRule::getZ(char z1[]){
	strcpy(z1, z);
}

void SCFGRule::setProb(double inProb){
	prob = inProb;
}

double SCFGRule::getProb(){
	return prob;
}

void SCFGRule::setFlag(int inFlag){
	flag = inFlag;
}

int SCFGRule::getFlag(){
	return flag;
}


