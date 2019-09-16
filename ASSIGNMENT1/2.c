/************************************************************************************************************************************
Author  1) Atharv Desai      (atharv.desai@colorado.edu)
        2) Suraj Thite       (suraj.thite@colorado.edu)
       
Problem Statement 2: Write a program that uses a logical expression that tests whether a given character code is a
      lower case 
      upper case 
      digit 
      white space (like null, backspace, space, tabs, etc.) 
      or a special character (like ! or >) in ASCII.          
***********************************************************************************************************************************/        
        
#include <stdio.h>
#include <ctype.h>

/***********************************************************************************************************************************/
/* Function name: Main            Parameters: void             Description: Function from where execution of any C program begins. */
/***********************************************************************************************************************************/
int main(void)
{
   int a[21]={66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,48,49,57};    //Taking input
   int i=0;
   int Code;
   for ( i=0;a[i]!=0;i++) {
      printf("%c ", a[i]);
      }
   for (i=0;a[i]!=0;i++){

     if( islower(a[i]))                    //to check if the ASCII char is in lower case
     {
         printf("\n Code: %d \t \t Type: Lower Case \t \t ASCII char =%c ",a[i],a[i]);
     }
     if( isupper(a[i]))                    //to check if the ASCII char is in upper case
     {
         printf("\n Code: %d \t \t Type: Upper Case \t \t ASCII char =%c ",a[i],a[i]);
     }
     if( isdigit(a[i]))                    //to check if the ASCII char is a number between 0-9
     {
         printf("\n Code: %d \t \t Type: digit \t \t \t ASCII char =%c ",a[i],a[i]);
     }
     if( ispunct(a[i]))                   //to check if the ASCII char is a special character
     {
         printf("\n Code: %d \t \t Type: special char \t \t ASCII char =%c ",a[i],a[i]);
     }
      if( isspace(a[i]) || a[i]==7)       //to check if the ASCII char indicates space
     {
         printf("\n Code: %d \t \t Type: space \t \t \t ASCII char =space ",a[i]);  
      }
}
   printf(" \n");
   return 0;
}


