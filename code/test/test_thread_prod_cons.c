#include "syscall.h"

const int N = 10; // Choose it large enough!

typedef struct parametre parametre;
struct parametre
{
    int maxPlace;
    int nbPlaces;
    void* verrou;
    void* producteurAtt;
    void* consomateurAtt;
};

void producteur(parametre* par){
  int i;
  for(i=0;i<N;i++){
    P(par->verrou);
    SynchPutString("Debut Producteur:",30);
    SynchPutInt(i);
    PutChar('\n');
    if(par->nbPlaces<par->maxPlace){
      par->nbPlaces++;
    }else{
      V(par->verrou);
      P(par->producteurAtt);
      P(par->verrou);
    }
    SynchPutString("Fin Producteur:",30);
    SynchPutInt(i);
    PutChar('\n');
    V(par->verrou);
  }
  UserThreadExit();

}


void consomateur(parametre* par){
  int i;
  for(i=0;i<N;i++){
    P(par->verrou);
    SynchPutString("Debut Consomateur:",30);
    SynchPutInt(i);
    PutChar('\n');
    if(par->nbPlaces>0){
      par->nbPlaces--;
    }else{
      V(par->verrou);
      P(par->consomateurAtt);
      P(par->verrou);
    }
    SynchPutString("Fin Consomateur:",30);
    SynchPutInt(i);
    PutChar('\n');
    V(par->verrou);
  }
  UserThreadExit();
}

int main(){
  parametre p={5,0,UserSemaphore ("verrou", 1),UserSemaphore ("producteurAtt", 0),UserSemaphore ("consomateurAtt", 0)};
  int a=UserThreadCreate((void (*)(void *))producteur,(void *)&p);
  int b=UserThreadCreate((void (*)(void *))consomateur,(void *)&p);
  UserThreadJoin(a);
  UserThreadJoin(b);



  return 0;
}
