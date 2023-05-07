#include <stdio.h>

int main(void) {
  int n, i, h, max, campea;
  int les[100];
  scanf("%d",&n);
  for (i=0;i<n;i++){
    scanf("%d",&les[i]);
  }
  scanf("%d",&h);
  if (h==3){
    max=10;
  } else if (h==2){
    max=20;
  } else if (h==1) {
    max=100;
  }
  campea=-1;
  for (i=0;i<n;i++){
    if (les[i]<=max){
      if (les[i]>campea){
        campea = les[i];
      } 
    }
  }
  
  printf("Valor de max: %d\n", max);
  printf("%d",campea);
}
