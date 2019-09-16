#include <stdio.h>

void print_hex(unsigned short int n);
void check_bin(unsigned short int num);
unsigned int ReverseBytes(unsigned short int val);
int main()
{	
    unsigned short int x = 0xCAFE;  //Declaration of the starting variable value. 	
    print_hex(x);
    check_bin(x);
    unsigned short int y = ReverseBytes(x);
    print_hex(y);
    check_bin(y);
    y= (y<<4 | y>>12);
    print_hex(y);
    check_bin(y);
    y= (y>>8 | y<<8);
    print_hex(y);
    check_bin(y);
    //y= y && 0xF0;    
    //printf("\n %X",y);
    return 0;
}

void print_hex(unsigned short int n)
{
    printf("\n%X",n); // Print the value in hexa decimal.
}
void check_bin(unsigned short int num)
    {   int bin[16];
        int ct,i;
        int flag=0;
        ct=0;
//Computation of the binary array            
         while(num>0)
    {
        bin[15-ct]=num%2;
        num=num/2;
        ct++;
    }
//Print the binary value 
    printf("\nBinary value is: ");
    for(i=0; i<16;i++)
       { printf("%d",bin[i]);}
    for(i=12; i<16;i++)
        {
        if (bin[i]==1)
            flag=flag+1;
        }
    if (flag ==3 || flag ==4)
            printf("\nTrue");
    else   
            printf("\nFalse");
        
}
   
unsigned int ReverseBytes(unsigned short int val)
{
 return ((val) << 8 | (val) >> 8);
}  
