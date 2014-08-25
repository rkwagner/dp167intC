#include <stdio.h>
#include <stdlib.h>

struct stud{
  char first[30];
  char last[30];
  int score[5];
  int avg;
  struct stud * next;
};

int main(void){
  FILE * in = fopen("input.dat", "r");
  struct stud * root;
  root = (struct stud *)malloc(sizeof(struct stud));
  root->next=0;
  if(!feof(in)){
    fscanf(in,"%s %*s %s %d %d %d %d %d", root->first, root->last,root->score,
        &root->score[1],&root->score[2],&root->score[3],&root->score[4]);
    root->avg=(root->score[0]+root->score[1]+root->score[2]+
       root->score[3]+root->score[4])/5;
  }
  while(!feof(in)){
    struct stud * node = (struct stud *)malloc(sizeof(struct stud));
    fscanf(in,"%s %*s %s %d %d %d %d %d", root->first, root->last,root->score,
        &root->score[1],&root->score[2],&root->score[3],&root->score[4]);
    root->avg=(root->score[0]+root->score[1]+root->score[2]+
       root->score[3]+root->score[4])/5;
    struct stud * current = root;
    node->next=root;
    while(node->avg >= node->next->avg){
      current = node->next;
      node->next=current->next;
    }
    if(node->next==0){
      
    }
    else if(node->next->avg==root->avg){
      root=node;
    }
    else{
      current->next=node;
    }
  }
  fclose(in);
  struct stud * current=root;
  while(current->next!=0){
    (void)printf("%s\n", current->first);
    current=current->next;
  }
}
