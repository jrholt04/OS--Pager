//File: MFU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of MFU (Most Frequently Used) page replacement algorithm
// Replaces the frame that has been accessed the most frequently

#include "MFU.h"
#include "pagerTools.h"

// Main MFU function
int mfu(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose) {
  int totalPageFaults = 0; // total page faults across all pages
  int pg;                   // current page being accessed
  bool hit;                 // flag for page hit
  int processPageFaults;    // page faults for current process
  int victim;                  // frame index to replace
 
  for (map<string, queue<int>>::iterator processIterator = pages.begin(); processIterator != pages.end(); ++processIterator) {
    string pId = processIterator->first;
    processPageFaults = 0;
    
    if (verbose) cout << "Pid: " << pId << endl;
    
    while (!pages[pId].empty()) {
      pg = pages[pId].front();
      pages[pId].pop();
      
      if (verbose) cout << "Accessing page: " << pg << endl;
      
      hit = tryHitFrame(frames, pg, frameNumbers);
      
      if (!hit) {
	totalPageFaults++;
	processPageFaults++;
	
	if (verbose) cout << "Page Fault" << endl;
	
	victim = findMostFreqUsed(frames, frameNumbers); // frame with highest frequency
	
	swapFrame(frames, pg, pId, victim);
	
	if (verbose) cout << "Page: " << pg << " is now in frame: " << victim << endl;
      }
    }
    if (verbose) cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
  }
  return totalPageFaults;
}

// Helper function to find the frame with the highest frequency
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
