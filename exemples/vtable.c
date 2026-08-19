#define TRAIT_IMPL
#include <trait.h>
#include <stdio.h>


typedef struct{
  void(*show)(void* self);
}Show;
static const char Show_id;

void show(void* self){
  Show* trait = trait_find(self, &Show_id);
  if(!trait) return;

  trait->show(self);
}

typedef struct{
  Trait_da traits;
  int cap;
}Cap_count;

void capshow(void* self){
  Cap_count* t = self;
  printf("%d\n", t->cap);
}

int main(void){
  Cap_count t = {0};
  trait_append(&t, (Trait_entry){ &Show_id, &(Show){ capshow } });
  t.cap = 69;
  show(&t);

  return 0;
}
