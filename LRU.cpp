//File: LRU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of LRU (Least Recently Used) page replacement algorithm
// This version uses a queue to track recency of frames, similar to FIFO.

#include "LRU.h"
#include "pagerTools.h"

int lru(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose) {
  int totalPageFaults = 0; 
  queue<int> frameQueue;    
  int pg;                   
  bool hit;                
  int processPageFaults;   
  int vic;                
  
  for (int i = 0; i < frameCount; i++) {
    frameQueue.push(i);
  }
  
  for (map<string, queue<int>>::iterator processIterator = pages.begin(); processIterator != pages.end(); ++processIterator) {
    string pId = processIterator->first;
    processPageFaults = 0;
    
    if (verbose) cout << "Pid: " << pId << endl;
    
    while (!pages[pId].empty()) {
      pg = pages[pId].front();
      pages[pId].pop();
      
      if (verbose) cout << "Accessing page: " << pg << endl;
      
      hit = tryLRUHitFrame(frames, frameQueue, pg, frameCount);
      
      if (!hit) {
	totalPageFaults++;
	processPageFaults++;
	
	if (verbose) cout << "Page Fault" << endl;
	
	vic = frameQueue.front();
	frameQueue.pop();

	swapFrame(frames, pg, pId, vic);
	
	if (verbose) cout << "Page: " << pg << " is now in frame: " << vic << endl;
	
	frameQueue.push(vic);
      }
    }
    
    if (verbose) cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
  }
  
  return totalPageFaults;
}

bool tryLRUHitFrame(Frame frames[], queue<int> frameQueue, int page, int frameCount) {
  for (int i = 0; i < frameCount; i++) {
    if (frames[i].getPageNum() == page) {
      queue<int> tempQueue;
      while (!frameQueue.empty()) {
	int idx = frameQueue.front();
	frameQueue.pop();
	if (idx != i) tempQueue.push(idx);
      }
      tempQueue.push(i);
      frameQueue = tempQueue;
      return true;
    }
  }
  return false;
}

