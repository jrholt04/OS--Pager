//File: FIFO.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the fifo is a page swapping algorithm that swaps out the first item in the queue
//  this is the implmentation of that algorithm
#include "FIFO.h"
#include "pagerTools.h"

int fifo(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose){
    int totalPageFaults = 0;
    queue<int> victims;
    int vic;

    for (int i = 0; i < frameCount; i++) victims.push(i);
    
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

                vic = victims.front();
                victims.pop();

		swapFrame(frames, pg, pId, vic);
                
                if(verbose) cout << "Page: " << pg << " is now in frame: " << vic << endl;
                
                victims.push(vic);
            }
        }
        if(verbose) cout << "Pid: " << pId <<" page faulted " << processPageFaults << " times" << endl;
    }
    return totalPageFaults;
}
