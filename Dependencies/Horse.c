#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include <stdbool.h> 
#include "Horse.h"


void InitHorse(RacingHorse *RH){
  RacingHorse *temporal=RH;
  temporal->Name=NULL;
  temporal->id=0;
  temporal->before=NULL;
  temporal->next=NULL;
}


RacingHorse * newHorse(){
 RacingHorse *new = (RacingHorse *)malloc(sizeof(RacingHorse));
 InitHorse(new);
 return new;
 }

void fillInfoHorse(RacingHorse *RH,info *information, bool debugging){
  
  RacingHorse *temporalInfo=RH;
  int nameLenght;

  temporalInfo->id=information->horsesNumber;
  printf("\n--------Let's add More Competitors:--------------\n");
  printf("\n-->Your horse %i is in here [%p]\n",temporalInfo->id,temporalInfo);
  //printf("-->How long will the name of your %i horse will be? :",temporalInfo->id);
  printf("      What's the name of the Horse %i?: ",temporalInfo->id);

  if( !debugging ) {
    scanf( " %i",&nameLenght);
  } else {
    nameLenght = 5;
    printf("      What's the name of the Horse %i?: ",temporalInfo->id);
  }

  temporalInfo->Name=(char*)malloc(nameLenght*sizeof(char));
  //printf(" What's the name of the Horse? \n");
  
  if( !debugging ) {
    scanf( " %s" ,  temporalInfo->Name);
  } else {
    temporalInfo->Name = "Zerg";
  }
}

void addHorse(RacingHorse *RH,info *information, bool debugging){
  RacingHorse *temporal=RH;
  while(temporal != NULL){
    if(temporal->next==NULL){
      temporal->next=newHorse();
      fillInfoHorse(temporal,information,debugging);
      break;
    }
    else{
      temporal=temporal->next;
    }
  }
}


void lastRegistred(RacingHorse *RH,info *information, bool debugging){
  RacingHorse *temporal=RH;
  while(temporal != NULL){
    if(temporal->next==NULL){
      fillInfoHorse(temporal, information, debugging);
      break;
    }
    else{
      temporal=temporal->next;
    }
  }
}

void addedButNotFillHorse(RacingHorse *RH,info *information){
  RacingHorse *temporal=RH;
  while(temporal != NULL){
    if(temporal->next==NULL){
      temporal->next=newHorse();
      break;
    }
    else{
      temporal=temporal->next;
    }
  }
}

void moreCompitingHorses(RacingHorse *RH,info *information, bool debugging){
  int moreHorses=1;
  char moreHorsesChar='s';

  while(moreHorses){
    if(information->horsesNumber == 12 ){
      printf("You have reached the MAXIMUN number of Competitors\n");
      break;
    }
    moreHorsesChar='s';
    printf("\n\n        You can ADD %i Competitors More!",(12-information->horsesNumber));
    printf("\n +---Do you want to add more Competitors? [Y/n] ---+  ");
    if( !debugging ) {
      scanf(" %c",&moreHorsesChar);
    } else {
      moreHorsesChar = 'n';
    }
    

    if( moreHorsesChar== 'Y' || moreHorsesChar== 'y'){
      information->horsesNumber++;
      addedButNotFillHorse(RH,information);
      lastRegistred(RH,information, debugging);
      moreHorses=1;
    } else if(moreHorsesChar== 'n' || moreHorsesChar== 'N'){
      moreHorses=0;
      break;
    } else {
      printf("Sorry you can ONLY CHOOSE Y OR N");
    }
  }
}

void printCompetitor(RacingHorse *RH){
  printf("+===========================================+\n");
  printf("    The Name of the Horse is : %s  \n",RH->Name);
  printf("    His Number is : %i\n",RH->id);
  printf("    His address is : %p\n",RH);
  printf("+===========================================+\n");
}

void printList(RacingHorse *RH){
  RacingHorse *temp=RH;
  printf("\n               LET'S SEE !!!\n");
  while(temp!=NULL){
    printCompetitor(temp);
    temp=temp->next;
  }
}

void serchAndDelete(RacingHorse *RH, info *information){
  RacingHorse *temporalDelete=RH;
  RacingHorse *temporalBeforeDelete=RH;
  RacingHorse *temporalAfterDeleted=RH;
  int idDelete=0;
  printf("What is the NUMBER of the Horse that you want to eliminate? :");
  scanf(" %i",&idDelete);
 
  if(idDelete==1){
    information->doubleList=temporalDelete->next;
    RH=information->doubleList;
    temporalDelete=RH;
    temporalDelete->before=NULL;
    information->horsesNumber=information->horsesNumber-1;
    temporalDelete->id=temporalDelete->id-1;

    temporalAfterDeleted=temporalDelete->next;
    temporalAfterDeleted->before=temporalBeforeDelete;
    temporalAfterDeleted->id=temporalAfterDeleted->id-1;
    while(temporalAfterDeleted->next != NULL){
      temporalAfterDeleted=temporalAfterDeleted->next;
      temporalAfterDeleted->id=temporalAfterDeleted->id-1; 
      }

  }
  else if(idDelete <= information->horsesNumber){
    while(temporalDelete != NULL){
      if(temporalDelete->id == idDelete){
        temporalBeforeDelete->next=temporalDelete->next;
        information->horsesNumber=information->horsesNumber-1;
        if(temporalDelete->next != NULL){

          temporalAfterDeleted=temporalDelete->next;
          temporalAfterDeleted->before=temporalBeforeDelete;
          temporalAfterDeleted->id=temporalAfterDeleted->id-1;

          while(temporalAfterDeleted->next != NULL){
            temporalAfterDeleted=temporalAfterDeleted->next;
            temporalAfterDeleted->id=temporalAfterDeleted->id-1; 
            
          }
        }
        free(temporalDelete);
        break;  
      }
      temporalBeforeDelete=temporalDelete;
      temporalDelete=temporalDelete->next;
    }
  }else{
    printf("\n\n          Horse OUT OF RANGE\n");
  }
} 

void deleteCompitingHorses(RacingHorse *RH,info *information){
  int noMoreHorses=1;
  char noMoreHorsesChar='s';

while(noMoreHorses){

  if(information->horsesNumber == 5 ){
    printf("You have reached the MINIMUM number of Competitors\n");
    break;
  }
  noMoreHorsesChar='s';
  printf("\n\n               You can DELETE %i Competitors!",(information->horsesNumber-5));
  printf("\n +------------Do you want to DELETE Competitors? [Y/n] -----------+  ");
  printf("\n Warning If you DELETE a Competitor the ID of other Horses may change! :");
  scanf(" %c",&noMoreHorsesChar);

  if( noMoreHorsesChar== 'Y' || noMoreHorsesChar== 'y'){
    serchAndDelete(information->doubleList,information); 
    noMoreHorses=1;
    printList(information->doubleList);
   }
  else if(noMoreHorsesChar== 'n' || noMoreHorsesChar== 'N'){
    noMoreHorses=0;
    break;
   }
  else{
    printf("Sorry you can ONLY CHOOSE Y OR N");
    }
  }
}

void playerHorseSerch(int idSelected,RacingHorse *RH, info *information){
  RacingHorse *temp=RH;
  while(temp!=NULL){
     if(idSelected ==temp->id){
       information->playerHorse=temp;
       break;
     }
     temp=temp->next;
  }
}
void horseSerch(info *information,int i){
  RacingHorse *temp=information->doubleList;
  while(temp!=NULL){
     if((i+1) ==temp->id){
       information->playerHorse=temp;
       break;
     }
     temp=temp->next;
  }
}

/*CP*/

void event1(RacingHorse *RH, int place){
  usleep(500000);
  place++;
  printf("\n%i / 15 - Course part. %s %i has been pushed too hard by the Jokey he/she HAS SLOWED DOWN took him 5 second to go throught !!!\n", place, RH->Name,RH->id);
}

void event2(RacingHorse *RH, int place){
  usleep(400000);
  place++;
  printf("\n%i / 15 - Course part. %s %i is getting distracted by the crowd he/she SLOWED DOWN took him 4 second to go throught !!!\n", place,RH->Name,RH->id);
}

void event3(RacingHorse *RH, int place){
  usleep(300000);
  place++;
  printf("\n%i / 15 - Course part. %s  %i is GOING At A STEADY PASE took him 3 second to go throught !!!\n", place, RH->Name,RH->id);
}

void event4(RacingHorse *RH, int place){
  usleep(200000);
  place++;
  printf("\n%i / 15 - Course part. %s %i is getting FASTER than before Only took him 2 second to go throught !!!\n", place, RH->Name,RH->id);
}

void event5(RacingHorse *RH, int place){
  usleep(100000);
  place++;
  printf("\n%i / 15 - Course part. %s %i is DEAD FOCUS on the PRICE! him 1 second to go throught!!!\n", place, RH->Name,RH->id);
}