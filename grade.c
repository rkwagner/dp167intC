//Grade report project.

#include <stdio.h>
#include <stdlib.h>

struct stud{
  char first[30];
  char last[30];
  int score[5];
  int avg;
  struct stud * next;
};

void insertOrder(struct stud * root, struct stud * current){
  struct stud * next = root;
  struct stud * previous;
  while(next->avg < current->avg){
    previous = next;
    next = next->next;
  }
  previous->next = current;
  current->next = next;
}

int main(void){
  FILE * in = fopen("input.dat", "r");
  struct stud * root = (struct stud *)malloc(sizeof(struct stud));
  root->next=0;
  if(!feof(in)){
    fscanf(in,"%15[^,] %15[^0123456789] %d %d %d %d %d",root->first,
        root->last,root->score,&root->score[1],&root->score[2],
        &root->score[3],&root->score[4]);
    root->avg=(root->score[0]+root->score[1]+root->score[2]+
       root->score[3]+root->score[4])/5;
  }
  while(!feof(in)){
    struct stud * node = (struct stud *)malloc(sizeof(struct stud));
    fscanf(in,"%15[^,] %15[^0123456789] %d %d %d %d %d",node->first,
        node->last,node->score,&node->score[1],&node->score[2],
        &node->score[3],&node->score[4]);
    node->avg=(node->score[0]+node->score[1]+node->score[2]+
       node->score[3]+node->score[4])/5;
    struct stud * current = root;
    if(current != 0){
      while(current->next != 0){
        current=current->next;
      }
    }
  }
  fclose(in);
  struct stud * current=root;
  while(current->next!=0){
    (void)printf("%s\n", current->first);
    current=current->next;
  }
}
