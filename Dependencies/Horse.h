typedef struct RacingHorse {
  char *Name;
  int id;
  struct RacingHorse *before;
  struct RacingHorse *next;
}RacingHorse;

typedef void (*Event)(struct RacingHorse*, int);

typedef struct info{
  Event eventsFuncs[5];
  struct RacingHorse *playerHorse;
  struct RacingHorse *Winner;
  struct RacingHorse *winnerList;
  int horsesNumber;
  int bet;
  int creditsLeft;
  bool start;
  struct RacingHorse *doubleList;
}info;

void InitHorse(RacingHorse *RH);


RacingHorse * newHorse();

void fillInfoHorse(RacingHorse *RH,info *information, bool debugging);

void addHorse(RacingHorse *RH,info *information, bool debugging);

void lastRegistred(RacingHorse *RH,info *information, bool debugging);

void addedButNotFillHorse(RacingHorse *RH,info *information);

void moreCompitingHorses(RacingHorse *RH,info *information, bool debugging);
    
void printCompetitor(RacingHorse *RH);

void printList(RacingHorse *RH);

void serchAndDelete(RacingHorse *RH, info *information);
  
void deleteCompitingHorses(RacingHorse *RH,info *information);

void playerHorseSerch(int idSelected,RacingHorse *RH, info *information);

/*CP*/

void event1(RacingHorse *RH, int place);

void event2(RacingHorse *RH, int place);

void event3(RacingHorse *RH, int place);

void event4(RacingHorse *RH, int place);

void event5(RacingHorse *RH, int place);