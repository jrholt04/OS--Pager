//File: random.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the random is a page swapping algorithm that swaps pages randomly this is the implementation of that algorithm
#include "random.h"
#include "pagerTools.h"

int pgRandom(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose){
    int totalPageFaults = 0;
    int vic;
    
    for (auto it = pages.begin(); it != pages.end(); ++it) {
        string pId = it->first;
        int pg;
        bool hit;
        int processPageFaults = 0;

        if(verbose) cout << "Pid: " << pId << endl;

        while(!pages[pId].empty()){
            pg = pages[pId].front();
            pages[pId].pop();
            
            if(verbose) cout << "Accessing page: " << pg << endl;

	    hit = tryHitFrame(frames, pg, frameCount);
            
            if(!hit){
                totalPageFaults++;
                processPageFaults++;
                
                if(verbose) cout << "Page Fault" << endl;

                vic = rand() % frameCount;

		swapFrame(frames, pg, pId, vic);

                if(verbose) cout << "Page: " << pg << " is now in frame: " << vic << endl;
                
            }
        } 
        if(verbose) cout << "Pid: " << pId <<" page faulted " << processPageFaults << " times" << endl;
    }

    return totalPageFaults;
}
