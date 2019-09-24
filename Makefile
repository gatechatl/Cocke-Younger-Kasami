# Title: MakeFile for FastaOpener 
# Description: MakeFile for FastaOpener 
# Copyright (c) 2009 
# Organization: UGA RNA-Informatics GROUP 
#
# @author: Tim Shaw gatech(a)uga.edu
# @Created: 2/15/2009
# @Updated: 2/15/2009
# Example: "make run"
 
CFILES = CYKTest.cpp CYK.cpp  RuleProcessor.cpp SCFGRule.cpp Path.cpp 
HFILES = CYK.h RuleProcessor.h SCFGRule.h Path.h 
OFILES = CYKTest.o CYK.o RuleProcessor.o SCFGRule.o Path.o
DEBUGFLAGS = -DDEBUG
#VIENNA_LIB = libRNA.a
#VIENNA_PATH = /home/tim/ViennaRNA-1.8.3/lib

cyk: $(CFILES) $(HFILES)
	
	g++ -O3 -c $(CFILES) -I/home/tim/ViennaRNA-1.8.3/H/
	g++ -O3 -o cyk $(OFILES) -L/home/tim/ViennaRNA-1.8.3/lib/ -lRNA -lm
	

debug: $(CFILES) $(HFILES)
	g++ -lstdc++ -o cyk $(DEBUGFLAGS) $(CFILES)

clean:
	rm -rf cyk

run: cyk
	./cyk 

runs: cyk
	./cyk 

tar: clean
	#cd ..; rm Pairs.tgz; tar cvzf Pairs.tgz Pairs/
