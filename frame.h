// FILE: frame.h
// Author: J Holt, N Neagle, and A Seng, Transy U
// CS 3074, Fall 2025
//
// Interface - frame class

#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <string>

using namespace std;

class Frame {
public:
    Frame(void);
    ~Frame(void);

    string getId(void) const;
    int getFreq(void) const;
    bool getValid(void) const;
    int getPageNum(void) const;

    void setId(string inputId);
    void setFrequency(int inputFreq);
    void toggleValid(void);
    void setPageNum(int pgNum);

private:
    int pageNumber;
    string id;
    int frequency;
    bool valid;
};

#endif
