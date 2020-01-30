#include "syscall.h"

const int NB_THREAD = 20; // nombre de thread Producteur et consomateur lancer par le programe

typedef struct parametre parametre;
struct parametre
{
    int id;
    int verrou;
    int plein;
    int vide;
};

void producteur(parametre* par){
    P(par->verrou);
    SynchPutString("Debut Producteur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    V(par->verrou);

    P(par->vide);

    V(par->plein);

    P(par->verrou);
    SynchPutString("Fin Producteur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    V(par->verrou);
  UserThreadExit();

}


void consomateur(parametre* par){
  P(par->verrou);
  SynchPutString("Debut Consomateur:",30);
  SynchPutInt(par->id);
  PutChar('\n');
  V(par->verrou);

  P(par->plein);
  V(par->vide);

  P(par->verrou);
  SynchPutString("Fin Consomateur:",30);
  SynchPutInt(par->id);
  PutChar('\n');
  V(par->verrou);

  UserThreadExit();
}


int main(){
  //////////////////////////////////////////////////////////////////////////////
  //initialisation structure pour les threads
  //////////////////////////////////////////////////////////////////////////////

  int verrou=UserSemaphore ("verrou", 1);//permet la synchronisation lors des ecriture en console
  int plein=UserSemaphore ("plein", 0);
  int vide=UserSemaphore ("vide", 5);
  int tab[NB_THREAD*2];//stock les id des thread lancer pour pouveoir join a la fin
  parametre parametres[NB_THREAD*2];
  int nbThread=0;

  //////////////////////////////////////////////////////////////////////////////
  //lancement des thread Producteur et Consomateur
  //////////////////////////////////////////////////////////////////////////////
  for(;nbThread<NB_THREAD;nbThread++){
    parametre p={nbThread,verrou,plein,vide};
    parametres[nbThread]=p;
    tab[nbThread]=UserThreadCreate((void (*)(void *))producteur,(void *)&parametres[nbThread]);
  }
  for(;nbThread<NB_THREAD*2;nbThread++){
    parametre p={nbThread,verrou,plein,vide};
    parametres[nbThread]=p;
    tab[nbThread]=UserThreadCreate((void (*)(void *))consomateur,(void *)&parametres[nbThread]);
  }
  //////////////////////////////////////////////////////////////////////////////
  //Attente des thread lancer durant le test
  //////////////////////////////////////////////////////////////////////////////
  int i;
  for(i=0;i<nbThread;i++){
    if(tab[i]!=-1){//si le trhead a bien etait lancé
      P(verrou);
      SynchPutString("join::",30);
      SynchPutInt(i);
      PutChar('\n');
      V(verrou);
      UserThreadJoin(tab[i]);
    }
  }

  return 0;
}
