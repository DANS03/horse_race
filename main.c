#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include <stdbool.h> 

  /* Dependencies */
#include "Dependencies/Drawings.h"
#include "Dependencies/Horse.h"


#define DEBUGGING false


  /* Evaluacion 2 */
  /* 
  Evaluacion 2. Fecha de entre 12 de Abril del 2021.

  Conversion de Carrera de Caballos.

  El programa de caballos debe dejar de ser estatico y convertirse en dinamico.

  Es decir:
    - Los Caballos tienen que ser creados dinamicamente en memoria.
    - Por lo que es necesario agregar las siguientes opciones al menu:
      - Agregar Caballo
      - Quitar Caballo
      - Imprimir Caballos
    - Hay que pedir el nombre del caballo al querer agregarlo.
    - Es necesario hacer uso de una lista doblemente ligada.
    - El programa tiene que correr minimo con 5 caballos
    - El maximo de caballos es 12
    - Los Caballos tienen que estar en una libreria a partir de ahora.
    - Es importante que antes de iniciar la carrera, los threads tambien deben de ser creados dinamicamente, es decir. Si son 12 caballos, hay que correr 12 threads.
    
  Criterios:
    20 puntos por cada criterio.
    - Uso de malloc (Tanto en la estructura caballo como para el nombre del caballo)
    - Libreria para Caballo
    - Listas doblemente ligadas
    - Menu y salida
    - Modificacion de Threads para que el programa funcione respecto a la cantidad de caballos
*/
struct thData {                                                   
  int i; 
  info *globalData;
} ThData; 


void randomNumbers(int *random) {  
  int lower = 0, upper = 4;
   *random=(rand() % (upper - lower + 1)) + lower; 
} 

info globalData = {
  { &event1, &event2, &event3, &event4, &event5 },
  NULL,
  NULL,
  NULL,
  0,
  0,
  10000,
  false,
  NULL
};

void makeBet(){
   
  bool valid = true;
  
  do{
    if (!valid){
      printf("\nSorry You CAN ONLY BET the money that you have, AND YOU HAVE TO BET something !!!!\n");
    }
    printf("You Have: %i Credits\n", globalData.creditsLeft);
    printf("How many credits do you want to bet to your champion? :");
    
    if( !DEBUGGING ) {
      scanf(" %i", &globalData.bet);
    } else {
      globalData.bet = 1000;
    }
    valid = false;
    
  }while( globalData.creditsLeft < globalData.bet || globalData.bet <= 0);
}

void character_choise(){
  int character=0;
  int rightChoise=1;
  printf("\n+============LET'S CHOOSE YOUR HORSE============+\n");
  while(rightChoise){
    printf("Put the NUMBER of the Horse that you want to bet to:");
    
     if( !DEBUGGING ) {
      scanf(" %i",&character);
    } else {
      character = 1;
    }
    printf("%i",character);
    printf("%i",globalData.horsesNumber);
    if(globalData.horsesNumber >= character && character > 0){
      playerHorseSerch(character,globalData.doubleList,&globalData);
      printf("You have choosen !!!\n");
      printCompetitor(globalData.playerHorse);
      rightChoise=0;
    }else{
      printf("\nSorry you can only choose beetween 1 - %i\n",globalData.horsesNumber);
      
    }
  }
}


void *race(void *vParams){
  printf("Thread Created - Waiting...\n");
  // struct arg_struct *args = (struct arg_struct *)args;
  
  struct thData *params = (struct thData *)vParams;
  info *gd = (info *)&(params->globalData);
  RacingHorse *RH=params->globalData->doubleList;
  RacingHorse *CurrentHorse;


  int randomDelay;
  int timeFragment;
  while(RH != NULL){
    if(params->i+1==RH->id){
      CurrentHorse=RH;
      break;
    }
    RH=RH->next;
  }

  while(!params->globalData->start);
  
  for(int i=0;i<15;i++){
    
    randomNumbers(&randomDelay);
  
    params->globalData->eventsFuncs[randomDelay](CurrentHorse, i);
    
  }
  if( params->globalData->Winner == NULL){ 
    printf("\n\n\n%s  %i WON the Race!!!! \n\n\n ",CurrentHorse->Name,CurrentHorse->id);
    params->globalData->Winner=CurrentHorse;
    params->globalData->winnerList=malloc(sizeof(RacingHorse)); // static// malloc 
    InitHorse(params->globalData->winnerList);
    params->globalData->winnerList->Name=CurrentHorse->Name; //strcpy()
    params->globalData->winnerList->id=CurrentHorse->id;
  }
  else{
    printf("\n\n%s  %i Has FinisH the Race!!!! \n\n ",CurrentHorse->Name,CurrentHorse->id);
    addedButNotFillHorse(params->globalData->winnerList,params->globalData);

    RacingHorse *temporal=params->globalData->winnerList;
    while(temporal != NULL){
    if(temporal->next==NULL){
      temporal->Name=CurrentHorse->Name;
      temporal->id=CurrentHorse->id;
      break;
    }
    else{
      temporal=temporal->next;
      }
    }
  }

  pthread_exit(NULL);
}


int main(void) {
  if( DEBUGGING ) {
    printf("\n\n  ========= we're debugging! ===========\n\n");
  }
  int keepPlaying=0;
  drawings(1);
  int moreHorses;

  printf("\nYou have No horses my friend,You NEED At LEAST 5 horses to begin!!!\n");
  RacingHorse head;
  InitHorse(&head);
  globalData.doubleList=&head;
  globalData.horsesNumber++;
  head.id=globalData.horsesNumber;
  printf("[%p]",globalData.doubleList);
  while(globalData.horsesNumber<5){
    addHorse(&head,&globalData, DEBUGGING);
    globalData.horsesNumber++;
  }
  lastRegistred(globalData.doubleList,&globalData, DEBUGGING);
  
  do {
    globalData.Winner=NULL;
    moreCompitingHorses(globalData.doubleList,&globalData, DEBUGGING);
    printList(globalData.doubleList);
    deleteCompitingHorses(globalData.doubleList,&globalData);
    printList(globalData.doubleList);
    character_choise();  
    makeBet();

    printf("Get Ready for the race!!!\n       Your Competitor is: %s\n         GOOD LUCK!!!\n\n", globalData.playerHorse->Name );
    
    for (int i=3;i>=1;i--){
      printf("The Race  STARTS in....%i\n\n",i);
      if( !DEBUGGING ) {
        usleep(700000);
      } else {
        usleep(100000);
      }
       
    }
    printf(" -> GOOOO ! ! ! \n\n\n");

    srand(time(0));

    int numTreads=globalData.horsesNumber;

    pthread_t MyHorses[numTreads];
    
    for(int i=0;i < numTreads; i++){
      
      struct thData *params;

      params = malloc(sizeof(*params));// (sizeof(struct thData))
      params->i = i;
      params->globalData =&globalData;

      pthread_create(&MyHorses[i], NULL, race, params);     
    }

    globalData.start = true;
    
    for (int i = 0; i < numTreads; i++){ 
      pthread_join(MyHorses[i], NULL);
    }
    
    drawings(6);

    if(globalData.playerHorse == globalData.Winner){
      //sumamos
      globalData.creditsLeft += globalData.bet;
      printf("You have won Congratulations!!!\n");
      drawings(5);
    } else {
      // restamos
      globalData.creditsLeft -= globalData.bet;
      printf("SORRY Mate better Luck next time!!!\n");
      drawings(4);
    }

  printList(globalData.winnerList);  

 int writeAnswer=1;
    do {
      char keepPlayingChar;
  
      printf("\n\nCREDITS LEFT %i", globalData.creditsLeft);
      if(globalData.creditsLeft <= 0) {
        printf("\n\nDude! You're out of cash! Go to work and come back later with some juice");
        drawings(3);
        keepPlaying = false;
        return 0;
      }
      printf("\n\n---------->Do you want to Keep Playing pal?: [Y/n]\n");
      scanf(" %c",&keepPlayingChar);
      
      if(keepPlayingChar == 'Y' || keepPlayingChar == 'y' ) {
        printf("            Greate!!! Lets'play\n");
        keepPlaying=1;
        writeAnswer=0;
      } else if(keepPlayingChar == 'N' || keepPlayingChar == 'n' ) {
        keepPlaying=0;
        writeAnswer=0;
      } else {
        printf("Sorry THERE WAS A MISTAKE!");

      }
    }while(writeAnswer);

  }while(keepPlaying);
  
  drawings(2);
  
  return 0;

}