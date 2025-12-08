// File pagerTools.cpp
// Author: J Holt, N Neagle, and A Seng, Transy U
// Course: CS 3074 Operating Systems
//
// Implementation file for OS Pager Tools

#include "pagerTools.h"
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
using namespace std;

map<string, queue<int>> readMemoryLocations(string fileName, int pageNumbers, int framesize) {
    map<string, queue<int>> pages;
    string pId;
    int memoryAddress;
    int page;
    string temp;

    ifstream input;
    input.open(fileName);
    if (!input) {
        cout << "File not found" << endl;
        exit(0);
    }

    while (getline(input, temp)) {
        if (temp[0] == 'P') {
            pId = temp;

            pages[pId] = queue<int>();
        }
        else {
            memoryAddress = stoi(temp);
            page = memoryAddress / framesize; 
            pages[pId].push(page);
        }
    }

    return pages;
}

string getInputType(string input) {
  if (input == "FIFO" || input == "fifo"){
    return "fifo";
  }
  if (input == "LRU" || input == "lru"){
    return "lru";
  }
  if (input == "MRU" || input == "mru"){
    return "mru";
  }
  if (input == "LFU" || input == "lfu") {
    return "lfu";
  }
  if (input == "MFU" || input == "mfu") {
    return "mfu";
  }
  if (input == "RANDOM" || input == "random") {
    return "random";
  }
  cout << "Algorithm return not found" << endl;
  exit(0);
}

// prints out the helpful how to when the program is called with --help or -h
void printPagerHelp(void) {
    cout << endl << endl
         << "This is a Paging simulator, with the ability to simulate First In First Out (FCFS), Most Recently Used (MRU), Least Recently Used (LRU), Random (RANDOM)" << endl << endl
         << "The program can be called with these command flags: " << endl << endl
         << "\n Usage: ./pager <cmd flags(optional)> <file name (optional)>" << endl
         << "\t--type or -t {FIFO, MRU, LRU, RANDOM}" << endl
         << "\t\tSelects what Paging algorithm you would like to select. The default is FIFO." << endl
	       << "\t--verbose or -v" << endl
         << "\t\tPrints out a detailed description of the processes and information related to the Pager" << endl
         << "\t--frames or -fr" << endl
         << "\t\tthe input will set the number of frames in the simulation" << endl
         << "\t--pages or -p" << endl
         << "\t\tthe input will set the number of pages in the simulation" << endl
         << "\t--framesize or -fs" << endl
         << "\t\tthe input will set the size of the frames" << endl
         << "\t--help or -h" << endl
         << "\t\tPrints out this helpful how-to!" << endl
         << endl;
}

// swaps the frame information of the victim frame with new page
void swapFrame(Frame frames[], int page, string pId, int victim) {
  if (!frames[victim].getValid()) {
    frames[victim].toggleValid();
  }
  frames[victim].setPageNum(page);
  frames[victim].setId(pId);
}

// sees if the page is in the frames
bool tryHitFrame(Frame frames[], int page, int frameCount) {
  for (int i = 0; i < frameCount; i++) {
    if (frames[i].getPageNum() == page) {
      frames[i].incFrequency();
      return true;
    }
  }
  return false;
}
