#include "tower.h"

Tower::Tower(int order, QLabel* label)
{
    this->order = order;
    this->label = label;
    myImage.load(":/tower.png");
    this->label->setPixmap(QPixmap::fromImage(myImage));
}

void Tower::pushDisk(Disk* d, bool animate)
{
    int x = 136 + (order-1)*260 - 0.5*d->getWidth();
    int y = 295 - disks.size()*d->getHeight();
    addDisk(d);
    if(animate)
        d->animate(x,y);
    else
        d->move(x,y);
}
Disk* Tower::popDisk()
{
    Disk* d = disks.at(disks.size()-1);
    disks.pop_back();
    return d;
}

Disk* Tower::peekDisk()
{
    return disks.at(disks.size()-1);
}
bool Tower::canPushDisk(Disk* d)
{
    if(disks.size() == 0)
        return true;
    if(*d < *peekDisk())
        return true;
    return false;
}
void Tower::clear(){
    disks.clear();
}

void Tower::addDisk(Disk* d)
{
    disks.push_back(d);
}
int Tower::getOrder()
{
    return order;
}
