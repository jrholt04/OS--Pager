//File: MRU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of MRU (Most Recently Used) page replacement algorithm
// This version uses a stack to track recency of frames

#include "MRU.h"
#include "pagerTools.h"

// Main MRU function
int mru(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose) {
  int totalPageFaults = 0; // Total number of page faults across all pages
  stack<int> frameStack;    // Stack to track recency of frames (top = most recently used)
  int pg;                   // Current page being accessed
  bool hit;                 // Flag to indicate if page is already in a frame
  int processPageFaults;    // Page faults for the current process
  int vic;                  // Frame index to replace (least recently used)
  
  for (int i = 0; i < frameNumbers; i++) {
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
      
      hit = tryMRUHitFrame(frames, frameStack, pg, frameNumbers);
      
      if (!hit) {
	totalPageFaults++;
	processPageFaults++;
	
	if (verbose) cout << "Page Fault" << endl;
	
	vic = findLeastRecentlyUsed(frames, frameStack, frameNumbers); // frame to replace (least recently used)
	frameStack.pop();

	swapFrame(frames, pg, pId, vic);
	
	if (verbose) cout << "Page: " << pg << " is now in frame: " << vic << endl;
	
	frameStack.push(vic); // move newly used frame to top
      }
    }
    
    if (verbose) cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
  }
  
  return totalPageFaults;
}

int findLeastRecentlyUsed(Frame frames[], stack<int> frameStack, int frameCount) {
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
      tempStack.push(i); // push recently used frame to top?
      frameStack = tempStack;
      return true;
    }
  }
  return false;
}
