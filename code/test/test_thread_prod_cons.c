#include "syscall.h"

const int N = 10; // Choose it large enough!

typedef struct parametre parametre;
struct parametre
{
    int id;
    int maxPlace;
    int* nbPlaces;
    void* verrou;
    int* nbPAtt;
    void* producteurAtt;
    int* nbCAtt;
    void* consomateurAtt;
};

void producteur(parametre* par){
  /*int i;
  for(i=0;i<N;i++){*/
    P(par->verrou);
    SynchPutString("Debut Producteur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    
    if(*par->nbPlaces<par->maxPlace){
      (*par->nbPlaces)++;
      int a;
      for(a=0;a<*par->nbCAtt;a++){
        V(par->consomateurAtt);
      }
      *par->nbCAtt=0;
    }else{
      V(par->verrou);
      (*par->nbPAtt)++;
      P(par->producteurAtt);
      P(par->verrou);
    }
    SynchPutString("Fin Producteur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    V(par->verrou);
  //}
  UserThreadExit();

}


void consomateur(parametre* par){
  /*int i;
  for(i=0;i<N;i++){*/
    P(par->verrou);
    SynchPutString("Debut Consomateur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    if(*par->nbPlaces>0){
      (*par->nbPlaces)--;
      int a;
      for(a=0;a<*par->nbPAtt;a++){
        V(par->producteurAtt);
      }
      *par->nbPAtt=0;
    }else{
      V(par->verrou);
      (*par->nbCAtt)++;
      P(par->consomateurAtt);
      P(par->verrou);
    }
    SynchPutString("Fin Consomateur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    V(par->verrou);
  //}
  UserThreadExit();
}


int main(){
  //////////////////////////////////////////////////////////////////////////////
  //initialisation structure pour les threads
  //////////////////////////////////////////////////////////////////////////////
  int nbPlaces=0;
  int nbPAtt=0;
  int nbCAtt=0;
  void * verrou=UserSemaphore ("verrou", 1);
  void * producteurAtt=UserSemaphore ("producteurAtt", 0);
  void * consomateurAtt=UserSemaphore ("consomateurAtt", 0);
  int tab[100];
  parametre parametres[100];
  int nbThread=0;
  //////////////////////////////////////////////////////////////////////////////
  //lance
  //////////////////////////////////////////////////////////////////////////////
  for(;nbThread<10;nbThread++){
    //SynchPutInt(nbThread);
    parametre p={nbThread,5,&nbPlaces,verrou,&nbPAtt,producteurAtt,&nbCAtt,consomateurAtt};
    parametres[nbThread]=p;
    tab[nbThread]=UserThreadCreate((void (*)(void *))producteur,(void *)&parametres[nbThread]);
  }
  for(;nbThread<20;nbThread++){
    parametre p={nbThread,5,&nbPlaces,verrou,&nbPAtt,producteurAtt,&nbCAtt,consomateurAtt};
    parametres[nbThread]=p;
    tab[nbThread]=UserThreadCreate((void (*)(void *))consomateur,(void *)&parametres[nbThread]);
  }
  //////////////////////////////////////////////////////////////////////////////
  //Attente des thread lancer durant le test
  //////////////////////////////////////////////////////////////////////////////
  /*PutChar('a');
  UserThreadJoin(tab[10]);
  PutChar('b');*/
  int i;
  for(i=0;i<nbThread;i++){
    SynchPutString("join::",30);
    SynchPutInt(i);
    PutChar('\n');
    UserThreadJoin(tab[i]);
  }

  return 0;
}
