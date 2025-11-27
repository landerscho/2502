#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define S_SIZE 50

typedef struct NODE {
      char title[S_SIZE];
      int year;
      struct NODE *link;
}NODE;

int main(){
  NODE *list =NULL;
  NODE *prev, *p, *next;
  char buffer[S_SIZE];
  int year;

  while(){
    printf("책 제목을 입력하세요.");
    gets_s(buffer, S_SIZE-1);
    if(buffer[0] =='\0')
      break;
    
    p=(node*)malloc(sizeof(NODE));
    strcpy(p->title, buffer);
    printf("책의 출판 연도를 입력하세요.");
    gets_s(buffer,S_SIZE-1);
    year =atoi(buffer);
    p->year =year;

    if(list==NULL)
      list =p;
    else
      prev->link=p;
    p->link=NULL;
    prev=p;
  }
  printf("\n");

  p=list;
  while(p!=NULL)
    {
      printf("[%s, %d]->",p->title, p->year);
      p=p->link;
    }

  printf("\n");

  p=list;
  while(p!= NULL){
    next = p->link;
    free(p);
    p=next;
  }

  return 0;
}
