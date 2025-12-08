## makefile for Paging
## N Neagle, J Holt, and A Seng

pager: pager.o FIFO.o LRU.o MRU.o LFU.o MFU.o random.o frame.o pagerTools.o
	g++ pager.o FIFO.o LRU.o MRU.o LFU.o MFU.o random.o frame.o pagerTools.o -o pager

pager.o: pager.cpp frame.h FIFO.h LRU.h MRU.h LFU.h MFU.h random.h pagerTools.h
	g++ -c pager.cpp

frame.o: frame.cpp frame.h
	g++ -c frame.cpp

FIFO.o: FIFO.cpp FIFO.h frame.o
	g++ -c FIFO.cpp

LRU.o: LRU.cpp LRU.h frame.o
	g++ -c LRU.cpp

MRU.o: MRU.cpp MRU.h frame.o
	g++ -c MRU.cpp

LFU.o: LFU.cpp LFU.h frame.o
	g++ -c LFU.cpp

MFU.o: MFU.cpp MFU.h frame.o
	g++ -c MFU.cpp

random.o: random.cpp random.h frame.o
	g++ -c random.cpp

pagerTools.o: pagerTools.cpp pagerTools.h frame.o
	g++ -c pagerTools.cpp


