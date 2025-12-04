//File: FIFO.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the fifo is a page swapping algorithm that swaps out the first item in the queue
//  this is the implmentation of that algorithm
#include "FIFO.h"

int fifo(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose){
    int pageFaults = 0;
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
                pageFaults++;

                if(verbose){
                    cout << "Page Fault" << endl;
                }

                vic = victims.front();
                victims.pop();
                
                if (!frames[vic].getValid()) {
                    frames[vic].toggleValid();
                }
                frames[vic].setPageNum(pg);
                frames[vic].setId(pId);

                if(verbose){
                    cout << "Page: " << pg << " is now in frame: " << vic << endl;
                } 
                
                victims.push(vic);
            }
        } 
    }
    
    return pageFaults;
}