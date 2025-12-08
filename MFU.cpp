//File: MFU.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Implementation of MFU (Most Frequently Used) page replacement algorithm
// Replaces the frame that has been accessed the most frequently

#include "MFU.h"

// Main MFU function
int mfu(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose) {
    int totalPageFaults = 0; // total page faults across all pages
    int pg;                   // current page being accessed
    bool hit;                 // flag for page hit
    int processPageFaults;    // page faults for current process
    int vic;                  // frame index to replace

    // Iterate over all processes in the map
    map<string, queue<int>>::iterator processIterator;
    for (processIterator = pages.begin(); processIterator != pages.end(); ++processIterator) {
        string pId = processIterator->first;
        processPageFaults = 0;

        if (verbose) {
            cout << "Pid: " << pId << endl;
        }

        // Process all 
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
                    frames[i].incFrequency(); // increment frequency on hit
                    hit = true;
                    break;
                }
            }

            // Page fault, replace the most frequently used frame
            if (!hit) {
                totalPageFaults++;
                processPageFaults++;

                if (verbose) {
                    cout << "Page Fault" << endl;
                }

                vic = findMostFreqUsed(frames, frameNumbers); // frame with highest frequency

                if (!frames[vic].getValid()) {
                    frames[vic].toggleValid(); // mark frame as valid
                }

                frames[vic].setPageNum(pg);
                frames[vic].setId(pId);
                frames[vic].setFrequency(1); // reset frequency for new page

                if (verbose) {
                    cout << "Page: " << pg << " is now in frame: " << vic << endl;
                }
            }
        }

        if (verbose) {
            cout << "Pid: " << pId << " page faulted " << processPageFaults << " times" << endl;
        }
    }

    return totalPageFaults;
}

// Helper function to find the frame with the highest frequency
int findMostFreqUsed(Frame frames[], int frameCount) {
    int highestFreq = -1;
    int mostFreqUsed = 0;

    for (int i = 0; i < frameCount; i++) {
        if (!frames[i].getValid()) {
            // If frame is invalid, replace it immediately
            return i;
        }

        if (frames[i].getFreq() > highestFreq) {
            highestFreq = frames[i].getFreq();
            mostFreqUsed = i;
        }
    }

    if (highestFreq == -1) {
        mostFreqUsed = 0; // fallback
    }

    return mostFreqUsed;
}
