
#include <stdio.h>
#include <math.h> // for floor and log2
#include "buddy_allocator.h"
#include "bit_map.h"

int levelIdx(size_t idx){
  if (!idx) return 0;
  if (idx==1) return 1;
  return (int)floor(log2(idx+1));
};

int buddyIdx(int idx) {
  if (idx & 0x1) {
    return idx + 1;
  }
  return idx - 1;
}

int parentIdx(int idx) { 
     return floor((idx-1)/2);
}
int startIdx(int idx){
  return (idx-((1<<levelIdx(idx))-1));
}

int firstIdx(int lvl){
  return (1 << lvl) - 1;

}


void print_bitmap(BitMap* bit_map){
  for (int i=0; i<bit_map->num_bits; i++){
    if (levelIdx(i)!=levelIdx(i+1)){
      printf("%d ", BitMap_bit(bit_map,i));
      printf("\n");
    }
    else{ 
     printf("%d ", BitMap_bit(bit_map,i));
    }
  }
  printf("\n");
  }
  int check_level(BuddyAllocator *allocator,int size,int bucket_size,int actual_level){
  for(int i = 0; i<allocator->num_levels; i++){ //salgo di livello fino a trovare l'indice con dimensione minima 
  //da soddisfare la richiesta
    if(bucket_size>size) break;
    else{
      bucket_size*=2; //la dimensione raddoppia se salgo
      actual_level--; //sto salendo di livello
    }
  }
  return actual_level;
}
void set_parent(BitMap* bit_map, int bit_num, int status){
  if(bit_num==0){ // sono arrivata al nodo radice
    BitMap_setBit(bit_map, bit_num, status);
  }

  else{
    BitMap_setBit(bit_map, bit_num, status);
    printf("il figlio è %d il padre è %d\n",bit_num,parentIdx(bit_num));
    set_parent(bit_map,parentIdx(bit_num),status);
  }
}



void set_child(BitMap* bit_map, int bit_num, int status){
  if(bit_num<bit_map->num_bits){ //controllo che il bit_num sia  minore del numero massimo di bit
    BitMap_setBit(bit_map, bit_num, status);
    set_child(bit_map, bit_num*2+1, status); //setto a 1 il figlio  sx
    set_child(bit_map, bit_num*2+2, status); //setto a 1 il figlio  dx
  }
}

