#include<stdio.h>
#include<stdlib.h>

typedef struct movie{
  char title[100];
  double rating;
}MOVIE;

int main ()
{
  MOVIE *movies;
  int size, i;

  printf("몇 편 저장하실래요?");
  scanf("%d", &size);
  getchar();

  movies =(MOVIE *)malloc(sizeof(MOVIE)* size);
  if(movies == NULL) {
    printf("메모리 할당 오류");
    exit(1);
  }

  for(i=0; i<size; i++){
    printf("영화 제목:");
    gets_s(movies[i].title, 100);
    printf("영화 평점:");
    scanf("%lf", &(movies[i].rating));
    getchar();
  }
  printf("=====================\n");
  printf("제목\t\t평점\n");
  printf("=====================\n");
  for (i=0;i<size;i++)
    printf("%s \t %.2f \n", movies[i].title, movies[i].rating);
  printf("=====================\n");
  free(movies);
  return 0;
}
