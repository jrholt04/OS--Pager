//File: MFU.h
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Interface for MFU (Most Frequently Used) page replacement algorithm

#ifndef MFU_H
#define MFU_H

#include <string>
#include <iostream>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

// Simulate the MFU page swapping algorithm
int mfu(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose);

// Helper function to find the index of the frame with the highest frequency
int findMostFreqUsed(Frame frames[], int frameNumbers);

#endif
