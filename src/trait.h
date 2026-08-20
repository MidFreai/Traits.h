#ifndef TRAIT_H
#define TRAIT_H

#include <stdbool.h>

// for size_t
#include <stddef.h>

//for realloc and free
#include <stdlib.h>

// The entry is the way to store traits with the ids
typedef struct{
  const void* id;
  void* trait;
}Trait_entry;

// The dynamic array for types store traits
typedef struct{
  Trait_entry* data;
  size_t count;
  size_t capacity;
}Trait_da;

typedef struct{
  Trait_da traits;
}Trait_entity;

// Decl

// Initial capacity of the DAs
static const size_t Trait_da_capacity = 1;

// To ensure and reserve memory for the array
bool trait_da_reserve(Trait_da* da, size_t expected_capacity);

// free the data of the Trait_da
void freeTrait(void* self);

// Append a new item in the end // This func is used while you dont want/need to cast to void*
bool trait_da_append(Trait_da* da, Trait_entry entry);

// Append a new item in the end // Cast out the Trait_da if is the first in the struct
bool trait_append(void* self, Trait_entry entry);

// Using for find if the type impl the trait // Cast out the Trait_da if is the first in the struct
void* trait_find(void* self, const void* id);

// Using for find if the type impl the trait // This func is used while you dont want/need to cast to void*
void* trait_da_find(Trait_da* da, const char* id);

Trait_entry newTrait_entry(const void* id, void* trait);

bool newTrait(void* self, const void* id, void* trait);

#endif //TRAIT_H

#ifdef TRAIT_IMPL

void* trait_find(void* self, const void* id){
  Trait_da* da = self;
  if(!da) { return NULL; };

  for(size_t i = 0; i < da->count; i++){
    if(da->data[i].id == id){
      return da->data[i].trait;
    }
  }

  return NULL;
}

void* trait_da_find(Trait_da* da, const char* id){
  for(size_t i = 0; i < da->count; i++){
    if(da->data[i].id == id){
      return da->data[i].trait;
    }
  }

  return NULL;
}

bool trait_da_reserve(Trait_da* da, size_t expected_capacity){
  if(expected_capacity > da->capacity){
    if(da->capacity == 0){
      da->capacity = Trait_da_capacity;
    }

    while (expected_capacity > da->capacity) {
      da->capacity *= 2;
    }

    da->data = realloc(da->data, da->capacity * sizeof(*da->data));

    if (da->data == NULL) {
      return false;
    }
  }
  return true;
}

void freeTrait(void* self){
  Trait_da* da = self;
  free(da->data);

  da->data = NULL;
  da->count = 0;
  da->capacity = 0;
}

bool trait_da_append(Trait_da* da, Trait_entry entry){
  if(!trait_da_reserve(da, da->count + 1)) return false;
  da->data[da->count++] = entry;
  return true;
}

bool trait_append(void* self, Trait_entry entry){
  Trait_da* da = self;
  if(!da) return false;
  if(!trait_da_reserve(da, da->count + 1)) return false;
  da->data[da->count++] = entry;
  return true;
}

Trait_entry newTrait_entry(const void* id, void* trait){
  return (Trait_entry){ id, trait };
}

bool newTrait(void* self, const void* id, void* trait){
  return trait_append(self, newTrait_entry(id, trait));
}

#endif // TRAIT_IMPL
