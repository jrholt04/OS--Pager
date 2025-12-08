//File: MFU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of MFU (Most Frequently Used) page replacement algorithm
// Replaces the frame that has been accessed the most frequently

#include "MFU.h"
#include "pagerTools.h"

int mfu(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose) {
  int totalPageFaults = 0; 
  int pg;                  
  bool hit;                
  int processPageFaults;   
  int victim;              
 
  for (map<string, queue<int>>::iterator processIterator = pages.begin(); processIterator != pages.end(); ++processIterator) {
    string pId = processIterator->first;
    processPageFaults = 0;
    
    if (verbose) cout << "Pid: " << pId << endl;
    
    while (!pages[pId].empty()) {
      pg = pages[pId].front();
      pages[pId].pop();
      
      if (verbose) cout << "Accessing page: " << pg << endl;
      
      hit = tryHitFrame(frames, pg, frameCount);
      
      if (!hit) {
	totalPageFaults++;
	processPageFaults++;
	
	if (verbose) cout << "Page Fault" << endl;
	
	victim = findMostFreqUsed(frames, frameCount); 
	
	swapFrame(frames, pg, pId, victim);
	
	if (verbose) cout << "Page: " << pg << " is now in frame: " << victim << endl;
      }
    }
    if (verbose) cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
  }
  return totalPageFaults;
}

int findMostFreqUsed(Frame frames[], int frameCount) {
  int highestFreq = -1;
  int mostFreqUsed = 0;
  
  for (int i = 0; i < frameCount; i++) {
    if (!frames[i].getValid()) {
      return i;
    }
    
    if (frames[i].getFreq() > highestFreq) {
      highestFreq = frames[i].getFreq();
      mostFreqUsed = i;
    }
  }
  
  if (highestFreq == -1) {
    mostFreqUsed = 0; // fallback
  }
  
  return mostFreqUsed;
}
