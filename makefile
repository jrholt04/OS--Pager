##makefile for Paging
##N Neagle, J Holt, and A Seng

pager: pager.o FIFO.o LRU.o MRU.o random.o frame.o pagerTools.o
	g++ pager.o FIFO.o LRU.o MRU.o random.o frame.o pagerTools.o -o pager

pager.o: pager.cpp frame.o FIFO.o LRU.o MRU.o random.o pagerTools.o
	g++ pager.cpp

FIFO.o: FIFO.cpp FIFO.h frame.o
	FIFO.cpp

LRU.o: LRU.cpp LRU.h frame.o
	g++ LRU.cpp

MRU.o: MRU.cpp MRU.h frame.o
	g++ -c MRU.cpp

random.o: random.cpp random.o frame.o
	g++ -c random.cpp

pagerTools.o: pagerTools.cpp pager.o frame.o
	g++ -c pagerTools.cpp