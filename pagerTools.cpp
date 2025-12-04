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

void printVerbose(void) {
    return;
}

void printPagerHelp(void) {
    cout << endl << endl
         << "This is a Paging simulator, with the ability to simulate First In First Out (FCFS), Most Recently Used (MRU), Least Recently Used (LRU), Random (RANDOM)" << endl << endl
         << "The program can be called with these command flags: " << endl << endl
         << "\t--type {FIFO, MRU, LRU, RANDOM}" << endl
         << "\t\tSelects what Paging algorithm you would like to select. The default is FIFO." << endl
         << "\t--verbose or --v" << endl
         << "\t\tPrints out a detailed description of the processes and information related to the Pager" << endl
         << "\t--frames or --f" << endl
         << "\t\tthe input will set the number of frames in the simulation" << endl
         << "\t--pages or --p" << endl
         << "\t\tthe input will set the number of pages in the simulation" << endl
         << "\t--framesize or --fs" << endl
         << "\t\tthe input will set the size of the frames" << endl
         << "\t--file {FILEPATH} or --f {FILEPATH}" << endl
         << "\t\tThe input file that contains the process/memory access information." << endl
         << "\t--help or --h" << endl
         << "\t\tPrints out this helpful how-to!" << endl
         << endl;
}
