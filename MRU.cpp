//File: MRU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of MRU (Most Recently Used) page replacement algorithm
// This version uses a stack to track recency of frames

#include "MRU.h"
#include "pagerTools.h"

// Main MRU function
int mru(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose) {
  int totalPageFaults = 0;
  stack<int> frameStack;  
  int pg;                 
  bool hit;               
  int processPageFaults;  
  int vic;                
  
  for (int i = 0; i < frameCount; i++) {
    frameStack.push(i);
  }
  
  for (map<string, queue<int>>::iterator processIterator = pages.begin(); processIterator != pages.end(); ++processIterator) {
    string pId = processIterator->first;
    processPageFaults = 0;
    
    if (verbose) cout << "Pid: " << pId << endl;
    
    while (!pages[pId].empty()) {
      pg = pages[pId].front();
      pages[pId].pop();
      
      if (verbose) cout << "Accessing page: " << pg << endl;
      
      hit = tryMRUHitFrame(frames, frameStack, pg, frameCount);
      
      if (!hit) {
	totalPageFaults++;
	processPageFaults++;
	
	if (verbose) cout << "Page Fault" << endl;
	
	vic = findMostRecentlyUsed(frames, frameStack, frameCount);
	frameStack.pop();

	swapFrame(frames, pg, pId, vic);
	
	if (verbose) cout << "Page: " << pg << " is now in frame: " << vic << endl;
	
	frameStack.push(vic);
      }
    }
    
    if (verbose) cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
  }
  
  return totalPageFaults;
}

int findMostRecentlyUsed(Frame frames[], stack<int> frameStack, int frameCount) {
  for (int i = 0; i < frameCount; i++) {
    if (frames[i].getPageNum() == -1) {
      return i;
    }
  }
  return frameStack.top();
}

bool tryMRUHitFrame(Frame frames[], stack<int> frameStack, int page, int frameCount) {
  for (int i = 0; i < frameCount; i++) {
    if (frames[i].getPageNum() == page) {
      stack<int> tempStack;
      while (!frameStack.empty()) {
	int idx = frameStack.top();
	frameStack.pop();
	if (idx != i) tempStack.push(idx);
      }
      tempStack.push(i);
      frameStack = tempStack;
      return true;
    }
  }
  return false;
}
