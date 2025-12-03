// File pagerTools.cpp
// Author: J Holt, N Neagle, and A Seng, Transy U
// Course: CS 3074 Operating Systems
//
// Implementation file for OS Pager Tools
#include "pagerTools.h"

map<string, queue<int>> readMemoryLocations(string fileName, int pageNumbers, int framesize){
    map<string, queue<int>> pages;
    string pId;
    int memoryAddress;
    int page;
    string temp;

    input.open(fileName);
    if (!input){
      cout << "File not found" << endl;
      exit(0);
    }

    while(getline(input, temp)){
        if (temp[0] == "P"){
            pId = temp;
            pages.insert({pId, queue<int> pageNumber})
        }
        else{
            memoryAddress = stoi(temp);
            page = memoryAddress / framesize; //find out what page that memory location is on
            pages[pId].push(page);
        }
    }
    return pages;
}

void printVerbose(void){

}

void printPagerHelp(void){
cout << endl << endl
       << "This is a Paging simulator, with the ability to simulate First In First Out (FCFS), Most Recently Used (MRU), Least Recently Used (LRU), Random (RANDOM)" << endl << endl
       << "The program can be called with these command flags: " << endl << endl
       << "\t--type {FIFO, MRU, LRU, RANDOM}" << endl
       << "\t\tSelects what Pagining algorithm you would like to select. The default is FIFO." << endl
       << "\t--verbose or --v" << endl
       << "\t\tPrints out a detailed description of the processes and information related to the Pager" << endl
       << "\t--file {FILEPATH} or --f {FILEPATH}" << endl
       << "\t\tInput the file that conatains the process information used for the pager. The file takes the format of rows of ID Arrival_Time Total_CPU_Burst Priority. The default value is sched.in" << endl
       << "\t--help or --h" << endl
       << "\t\tPrints out this helpful how to!" << endl
       << endl;
}