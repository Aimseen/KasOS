#include "frameprovider.h"
#include <strings.h>
#include "system.h"


FrameProvider::FrameProvider(int numPagesPhy){
  memoire=new BitMap(numPagesPhy);
}
FrameProvider::~FrameProvider(){
  delete memoire;
}
int FrameProvider::GetEmptyFrame(){
  int ret=memoire->Find();
  bzero (machine->mainMemory+ret*PageSize, PageSize);
  return ret;
}
void FrameProvider::ReleaseFrame(int page){
  memoire->Clear(page);
}
int FrameProvider::NumAvailFrame(){
  return memoire->NumClear();
}
