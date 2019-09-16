#include <stdio.h>
#include <ctype.h>

int main(void)
{
   int a[21]={66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,48,49,57};
   int i=0;
   int Code;
   for ( i=0;a[i]!=0;i++) {
      printf("%c ", a[i]);
      }
   for (i=0;a[i]!=0;i++){

     if( islower(a[i]))
     {
         printf("\n Code: %d \t \t Type: Lower Case \t \t ASCII char =%c ",a[i],a[i]);
     }
     if( isupper(a[i]))
     {
         printf("\n Code: %d \t \t Type: Upper Case \t \t ASCII char =%c ",a[i],a[i]);
     }
     if( isdigit(a[i]))
     {
         printf("\n Code: %d \t \t Type: digit \t \t \t ASCII char =%c ",a[i],a[i]);
     }
     if( ispunct(a[i]))
     {
         printf("\n Code: %d \t \t Type: special char \t \t ASCII char =%c ",a[i],a[i]);
     }
      if( isspace(a[i]) || a[i]==7)
     {
         printf("\n Code: %d \t \t Type: space \t \t \t ASCII char =%c ",a[i],a[i]);
      }
}
   printf(" \n");
   return 0;
}


