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

    // returns the PID associated with the frame
    string getId(void) const;

    // returns the frequency assocaited with the frame
    int getFreq(void) const;

    // returns the value of the valid bit associated with the frame
    bool getValid(void) const;

    // returns the page number associated with the frame
    int getPageNum(void) const;

    // sets the PID associated with the frame
    void setId(string inputId);

    // sets the frequency associated with the frame
    void setFrequency(int inputFreq);

    // increments the frequency assocated with the frame by 1
    void incFrequency(void);

    // toggles the valid bit associted with the frame
    void toggleValid(void);

    // sets the page number associated with the frame
    void setPageNum(int pgNum);

private:
    int pageNumber;
    string id;
    int frequency;
    bool valid;
};

#endif
