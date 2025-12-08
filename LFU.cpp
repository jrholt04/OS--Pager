//File: LFU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the LFU is a page swapping algorithm that swaps out the least frequenlty used frame
//  this is the implmentation of that algorithm

#include "LFU.h"
#include "pagerTools.h"

int lfu(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose){
  int totalPageFaults = 0;
  int victim;
  
  for (auto it = pages.begin(); it != pages.end(); ++it) {
    string pId = it->first;
    int pg;
    bool hit;
    int processPageFaults = 0;
    
    if(verbose) cout << "Pid: " << pId << endl;
    
    while(!pages[pId].empty()) {
      pg = pages[pId].front();
      pages[pId].pop();
      
      if(verbose) cout << "Accessing page: " << pg << endl;
   
      hit = tryHitFrame(frames, pg, frameCount);

      if(!hit){
	totalPageFaults++;
	processPageFaults++;
	
	if(verbose) cout << "Page Fault" << endl;

	victim = findLeastFreqUsed(frames, frameCount);
    	
	swapFrame(frames, pg, pId, frameCount, victim);
	
	if(verbose) cout << "Page: " << pg << " is now in frame: " << victim << endl;
        
      }
    } 
    if(verbose) cout << "Pid: " << pId <<" page faulted " << processPageFaults << " times" << endl;
  }
  return totalPageFaults;
}

int findLeastFreqUsed(Frame frames[], int frameCount) {
  int lowestFreq = -1;
  int leastFreqUsed = 0;
  
  for (int i = 0; i < frameCount; i++) {
    if (!frames[i].getValid()) {
      return i;
    }
    
    if (lowestFreq = -1) {
      lowestFreq = frames[i].getFreq();
    }
    
    if (frames[i].getFreq() < lowestFreq) {
      lowestFreq = frames[i].getFreq();
      leastFreqUsed = i;
    }
  }
  return leastFreqUsed;
}
    
