//File: random.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the random is a page swapping algorithm that swaps pages randomly this is the implementation of that algorithm
#include "random.h"

int pgRandom(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose){
    int totalPageFaults = 0;
    int vic;
    
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

                vic = rand() % frameNumbers;
                
                if (!frames[vic].getValid()) {
                    frames[vic].toggleValid();
                }
                frames[vic].setPageNum(pg);
                frames[vic].setId(pId);

                if(verbose){
                    cout << "Page: " << pg << " is now in frame: " << vic << endl;
                } 
                
            }
        } 
        if(verbose){
            cout << "Pid: " << pId <<" page faulted " << processPageFaults << " times" << endl;
        }
    }

    return totalPageFaults;
}