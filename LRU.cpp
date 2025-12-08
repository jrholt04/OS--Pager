//File: LRU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of LRU (Least Recently Used) page replacement algorithm
// This version uses a queue to track recency of frames, similar to FIFO.

#include "LRU.h"

// Main LRU function
int lru(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose) {
    int totalPageFaults = 0; // Total number of page faults across all pages
    queue<int> frameQueue;    // Queue to track recency of frames (front = least recently used)
    int pg;                   // Current page being accessed
    bool hit;                 // Flag to indicate if page is already in a frame
    int processPageFaults;    // Page faults for the current process
    int vic;                  // Frame index to replace (least recently used)

    // Initialize the queue with frame indices
    for (int i = 0; i < frameNumbers; i++) {
        frameQueue.push(i);
    }

    // Iterate over all processes in the map
    map<string, queue<int>>::iterator processIterator;
    for (processIterator = pages.begin(); processIterator != pages.end(); ++processIterator) {
        string pId = processIterator->first;
        processPageFaults = 0;

        if (verbose) {
            cout << "Pid: " << pId << endl;
        }

        // Process all pages for this process
        while (!pages[pId].empty()) {
            pg = pages[pId].front();
            pages[pId].pop();

            if (verbose) {
                cout << "Accessing page: " << pg << endl;
            }

            hit = false;

            // Check if page is already loaded in a frame
            for (int i = 0; i < frameNumbers; i++) {
                if (frames[i].getPageNum() == pg) {
                    // Page hit: update recency by moving frame to back of queue
                    queue<int> tempQueue;
                    while (!frameQueue.empty()) {
                        int idx = frameQueue.front();
                        frameQueue.pop();
                        if (idx != i) tempQueue.push(idx);
                    }
                    tempQueue.push(i); // push recently used frame to back
                    frameQueue = tempQueue;

                    frames[i].incFrequency(); // keep track of frequency
                    hit = true;
                    break;
                }
            }

            // Page fault: replace least recently used frame
            if (!hit) {
                totalPageFaults++;
                processPageFaults++;

                if (verbose) {
                    cout << "Page Fault" << endl;
                }

                vic = frameQueue.front(); // frame to replace (least recently used)
                frameQueue.pop();

                if (!frames[vic].getValid()) {
                    frames[vic].toggleValid(); // mark frame as valid
                }

                frames[vic].setPageNum(pg);
                frames[vic].setId(pId);

                if (verbose) {
                    cout << "Page: " << pg << " is now in frame: " << vic << endl;
                }

                frameQueue.push(vic); // move newly used frame to back
            }
        }

        if (verbose) {
            cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
        }
    }

    return totalPageFaults;
}
