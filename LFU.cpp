//File: LFU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the LFU is a page swapping algorithm that swaps out the least frequenlty used frame
//  this is the implmentation of that algorithm

// still a work in progress mostly built off of FIFO - NN 12/4
#include "LFU.h"

int lfu(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose){
  int totalPageFaults = 0;
  queue<int> victims;
  int vic;
  
  //pick the first things to fill up the frames
  for (int i = 0; i < frameNumbers; i++) { 
    victims.push(i);
  }
  
  for (auto it = pages.begin(); it != pages.end(); ++it) {
    string pId = it->first;
    int pg;
    bool hit;
    int processPageFaults = 0;
    
    if(verbose){
      cout << "Pid: " << pId << endl;
    }
    
    while(!pages[pId].empty()){
      pg = pages[pId].front();
      pages[pId].pop();
      
      if(verbose){
	cout << "Accessing page: " << pg << endl;
      } 
      hit = false;
      for (int i = 0; i < frameNumbers; i++) {
	if (frames[i].getPageNum() == pg) {
	  frames[i].incFrequency();
	  hit = true;
	  break;
	}
      }
      
      if(!hit){
	totalPageFaults++;
	processPageFaults++;
	
	if(verbose){
	  cout << "Page Fault" << endl;
	}
	
	//vic = victims.front();
	vic = findLeastFreqUsed(frames, frameNumbers); // somethin like this
	
	if (!frames[vic].getValid()) {
	  frames[vic].toggleValid();
	}
	frames[vic].setPageNum(pg);
	frames[vic].setId(pId);
	
	if(verbose){
	  cout << "Page: " << pg << " is now in frame: " << vic << endl;
	} 
        
	//victims.push(vic);
      }
    } 
    if(verbose){
      cout << "Pid: " << pId <<" page faulted " << processPageFaults << " times" << endl;
    }
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
  cout << "Lowest Freq frame is " << leastFreqUsed << endl;
  return leastFreqUsed;
}
    
