#ifndef TOWER_H
#define TOWER_H
#include "disk.h"
#include <vector>
using namespace std;

class Tower
{
public:
    Tower(int order, QLabel* label);
    void pushDisk(Disk* d, bool animate=false);
    bool canPushDisk(Disk* d);
    Disk* peekDisk();
    Disk* popDisk();
    void clear();
    void addDisk(Disk* d);
    int getOrder();

private:
    int order;
    vector<Disk*> disks;
    QImage myImage;
    QLabel* label;
};

#endif // TOWER_H
