// DLW Jan 2017: to try out ctypes

#include <stdio.h>

 typedef struct
   { char fueltype[4];
     int mon;
   } inputs ;

  void MeShow(inputs at)
  {
    printf("entering MeShow\n");
    printf("at.mon=%d\n", at.mon);
  }

  void ShowMe(inputs *at)
  {
    printf("entering ShowMe\n");
    printf("at->mon=%d\n", at->mon);
  }
