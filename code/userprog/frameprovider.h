#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H
#include "bitmap.h"

class FrameProvider{
  private:
    BitMap * memoire;


  public:
    FrameProvider(int numPagesPhy);
    ~FrameProvider();
    int GetEmptyFrame();
    void ReleaseFrame(int page);
    int NumAvailFrame();
};

#endif // MACHINE_H
