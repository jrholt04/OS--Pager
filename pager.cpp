//File: pager.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
//  Main program for a page swapping algorithms
//  sources: 
//      Map: https://www.geeksforgeeks.org/cpp/map-associative-containers-the-c-standard-template-library-stl/ accessed 12/3/25
//      credit: Caroline
//      Dynamic arrays: https://cplusplus.com/forum/beginner/235498/#google_vignette accessed 12/3/25
#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "pagerTools.h"
#include "frame.h"
#include "FIFO.h"
#include "LRU.h"
#include "MRU.h"
#include "LFU.h"
#include "MFU.h"
#include "random.h"

using namespace std;

int main (int argc, char **argv){
  int pageFaults;
  string type = "fifo";
  string fileName = "pager.in";
  int frameNumbers = 3;
  int pageNumbers = 8;
  int framesize = 512;
  bool verbose = false;
  map<string, queue<int>> pages;
  
  for (int i = 1; i < argc; ++i) { 
    string arg = argv[i];
    if (arg == "--type" || arg == "-t"){
      type = getInputType(argv[i + 1]);
      i++;
    }
    else if (arg == "--frames" || arg == "-fr"){
      frameNumbers = stoi(argv[i + 1]);
      if (frameNumbers <= 0){
        cout << "Invalid number of frames." << endl;
        exit(1);
      }
      i++;
    }
    else if (arg == "--verbose" || arg == "-v"){
      verbose = true;
    }
    else if (arg == "--pages" || arg == "-p"){
      pageNumbers = stoi(argv[i + 1]);
      if (pageNumbers <= 0){
	      cout << "Invalid number of pages." << endl;
	      exit(1);
      }
      i++;
    }
    else if (arg == "--framesize" || arg == "-fs"){
      framesize = stoi(argv[i + 1]);
      if (framesize <= 0){
	cout << "Invalid frame size." << endl;
	exit(1);
      }
      i++; 
    }
    else if (arg == "--help" || arg == "-h") {
      printPagerHelp();
      return 0;
    }
    // is the last element of input then it should be a file ;
    else if (argc - 1 == i){
      fileName = argv[i];
    }
    else {
      cout << "invalid flags --help for information on how to call pager" << endl;
      exit(1);
    }
  }   
  
  if (verbose){
    cout << "type: "<<type << endl;
    cout << "fileName: " << fileName << endl;
    cout << "frame size: " << framesize << endl;
    cout << "number of frames: " << frameNumbers << endl;
    cout << "number of pages: " << pageNumbers << endl;
    cout << "verbose: " << verbose << endl << endl;
  }
  
  Frame* frames = new Frame[frameNumbers];
  pages = readMemoryLocations(fileName, pageNumbers, framesize);
  
  if (type == "fifo") {
    pageFaults = fifo(frames, pages, frameNumbers, verbose);
  }
  else if (type == "lru") {
    pageFaults = lru(frames, pages, frameNumbers, verbose);
  }
  else if (type == "mru") {
    pageFaults = mru(frames, pages, frameNumbers, verbose);
  }
  else if (type == "lfu") {
    pageFaults = lfu(frames, pages, frameNumbers, verbose);
  }
  else if (type == "mfu") {
    pageFaults = mfu(frames, pages, frameNumbers, verbose);
  }
  else if (type == "random") {
    pageFaults = pgRandom(frames, pages, frameNumbers, verbose);
  }
  
  cout << "page faults: " << pageFaults << endl;
  delete[] frames;
  
  return 0;    
}
