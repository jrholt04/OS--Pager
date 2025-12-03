//File: pager.cpp
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  Main program for a page swapping algorithms
//  sources: 
//      Map: https://www.geeksforgeeks.org/cpp/map-associative-containers-the-c-standard-template-library-stl/ accessed 12/3/25
//      credit: Caroline
#include <string>
#include <iostream>
#include <csdio>
#include <map>
#include <queue>
#include "pagerTools.h"
#include "frame.h"
#include "fifo.h"
#include "LRU.h"
#include "MRU.h"
#include "random.h"

using namespace std;

int main (int argc, char **argv){
    string type = "FIFO";
    string fileName = "pager.in";
    int frameNumbers = 3;
    int pageNumbers = 8;
    int framesize = 512;
    bool verbose = false;
    map<string id, queue<int>> pages;
    Frame frames[frameNumbers];

    for (int i = 1; i < argc; ++i) { 
        string arg = argv[i];
        if (arg == "--type" || arg == "-t"){
            string inputType = argv[i + 1];
            if (inputType == "FIFO" || inputType == "fifo"){
                type = "fifo";
                i++;
            }
            else if (inputType == "LRU" || inputType == "lru"){
                type = "lru";
                i++;
            }
            else if (inputType == "MRU" || inputType == "mru"){
                type = "mru";
                i++;
            }
            else if (inputType == "RANDOM" || inputType == "random") {
                type = "random";
                i++;
            }
            else{
                cout << "Algorithm type not found" << endl;
                return 0;
            }
        }
        if (arg == "--verbose" || arg == "--v"){
            verbose = true;
        }
        if (arg == "--frames" || arg == "-f"){
            frameNumbers = stoi(argv[i + 1]);
            if (frameNumbers <= 0){
                cout << "Invalid frame number." << endl;
                exit(1);
            }
            frames[frameNumbers];
            i++;
        }
        if (arg == "--pages" || arg == "-p"){
            pageNumbers = stoi(argv[i + 1]);
            if (pageNumbers <= 0){
                cout << "Invalid page number." << endl;
                exit(1);
            }
            i++;
        }
        if (arg == "--framesize" || arg = "-fs"){
            framesize = stoi(argv[i + 1]);
            if (framesize <= 0){
                cout << "Invalid frame size." << endl;
                exit(1);
            }
            i++; 
        }
        if (arg == "--file" || arg == "--f"){
            fileName = argv[i + 1];
            i++;
        }
         if (arg == "--help" || arg == "--h") {
            printPagerHelp();
            return 0;
        }
    }   

    if (verbose){
        cout << "type: "<<type << endl;
        cout << "fileName: " << fileName << endl;
        cout << "frame size: " << framesize << endl;
        cout << "number of frames: " << frames << endl;
        cout << "number of pages: " << pages << endl;
        cout << "verbose: " << verbose << endl;
    }
   
    pages = readMemoryLocations(fileName, pageNumbers, framesize);
    
    if (type == "fifo") {
        fifo(frames, pages, frameszie, verbose);
    }
    else if (type == "lru") {
        lru(frames, pages, framesize, verbose);
    }
    else if (type == "mru") {
        mru(frames, pages, framesize, verbose);
    }
    else if (type == "random") {
        random(frames, pages, framesize, verbose);
    }
    
    return 0;    
}