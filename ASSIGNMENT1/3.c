/**********************************************************************************************************
Author 1) Atharv Desai  (atharv.desai@colorado.edu)
       2) Suraj Thite   (suraj.thite@colorado.edu)

Problem Statement 3 :

Given the starting integer value 0xCAFE, perform each of these operations in
series, that is, each operation should be performed on the result of the previous function. Print the
results of each function to the command line (to capture as ProgramThree.out).

Question 1.Print the original input in hexadecimal
Question 2.Test if 3 of last 4 bits are on, and print the value in binary (along with the result of the test –
true/false)
Question 3.Reverse the byte order, print the value in hexadecimal
Question 4.Test if 3 of last 4 bits are on, and print the value in binary (along with the result of the test –
true/false)
Question 5.Rotate the value by four bits to the left, print the value in hexadecimal
Question 6.Test if 3 of last 4 bits are on, and print the value in binary (along with the result of the test –
true/false)
Question 7.Rotate the value by eight bits to the right, print the value in hexadecimal
Question 8.Test if 3 of last 4 bits are on, and print the value in binary (along with the result of the test –
true/false) 
    
********************************************************************************************************/
#include <stdio.h>

void print_hex(unsigned short int n);
void check_bin(unsigned short int num);
unsigned int ReverseBytes(unsigned short int val);

/***********************************************************************************************************************************/
/* Function name: Main            Parameters: void             Description: Function from where execution of any C program begins. */
/***********************************************************************************************************************************/
int main()
{	
    unsigned short int x = 0xCAFE;  //Declaration of the starting variable value. 	
    print_hex(x);   
    check_bin(x);
    unsigned short int y = ReverseBytes(x); // Reverse the bytes of the input variable
    print_hex(y);
    check_bin(y);
    y= (y<<4 | y>>12);            //Rotate the value by 4 bits to the left and move them to the rightmost 4 bits retaining all the input values while rotation. 
    print_hex(y);
    check_bin(y);
    y= (y>>8 | y<<8);           ////Rotate the value by 8 bits to the right and move them to the rightmost 8 bits retaining all the input values while rotation.
    print_hex(y);
    check_bin(y);               
    return 0;
}

/***********************************************************************************************************************************/
/* Function name: print_hex            Parameters: Hex number                 Description: Function to print hex value             */
/***********************************************************************************************************************************/
void print_hex(unsigned short int n)
{
    printf("\n Hex value %X",n); // function to print the value in hexa decimal.
}
void check_bin(unsigned short int num)
    {   int bin[16];
        int ct,i;       // function to convert input value into binary array. 
        int flag=0;
        ct=0;            
         while(num>0)
    {
        bin[15-ct]=num%2;
        num=num/2;
        ct++;
    }
    printf("\n Binary value is: "); //Print the binary value
    for(i=0; i<16;i++)
       { printf("%d",bin[i]);}
    for(i=12; i<16;i++)
        {
        if (bin[i]==1)
            flag=flag+1;
        }
    if (flag ==3 || flag ==4)
            printf("\n Condition--> 3 of last 4 bits high--True");
    else   
            printf("\n Condition--> 3 of last 4 bits high--False");
        
}


/***********************************************************************************************************************************/
/* Function name: ReverseBytes     Parameters: Hex number     Description: Function to reverse byte order by retaining the data    */
/***********************************************************************************************************************************/   
unsigned int ReverseBytes(unsigned short int val) //Function to reverse the byte order
{
 return ((val) << 8 | (val) >> 8);   //Swap the bytes implementing shift operators and retaining the input data using OR operator.
}  
