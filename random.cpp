#include "random.h"

int pgRandom(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose){
    int pageFaults = 0;
    int vic;
    
    for (auto it = pages.begin(); it != pages.end(); ++it) {
        string pId = it->first;
        int pg;
        bool hit;

        while(!pages[pId].empty()){
            pg = pages[pId].front();
            pages[pId].pop();
            
            if(verbose){
                cout << "Accessing page: " << pg << endl;
            } 
            hit = false;
            for (int i = 0; i < frameNumbers; i++) {
                if (frames[i].getPageNum() == pg) {
                    hit = true;
                    break;
                }
            }
            
            if(!hit){
                pageFaults++;

                if(verbose){
                    cout << "Page Fault" << endl;
                }

                vic = rand() % frameNumbers;
                
                if (!frames[vic].getValid()) {
                    frames[vic].toggleValid();
                }
                frames[vic].setPageNum(pg);
                frames[vic].setId(pId);

                if(verbose){
                    cout << "Page: " << pg << " is now in frame: " << vic << endl;
                } 
                
            }
        } 
    }

    return pageFaults;
}