#define TRAIT_IMPL
#include <trait.h>
#include <stdio.h>

typedef struct{
  float x;
  float y;
}Position;
static const char Position_id;

void printPosition(void* self){
  Position* pos = trait_find(self, &Position_id);
  if(pos == NULL) return;
  printf("Position: x %f, y %f\n", pos->x, pos->y);
}

typedef struct{  }Player;
static const char Player_id;

int main(void){
  Trait_entity te;

  newTrait(&te, &Player_id, &(Player){  });
  newTrait(&te, &Position_id, &(Position){ 3, 4 });

  if(trait_find(&te, &Player_id)) printf("Is the player\n");

  printPosition(&te);
}
