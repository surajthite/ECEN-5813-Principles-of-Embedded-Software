#include<math.h>
#include <stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
void print_input(int,int,int);
void hex_to_dec(int,int,int);
void decimal_bin(int num, int n);
void compute_max(int n);
void compute_min(int n);
void compute_max_decimal(int n);
void compute_max_hex(int n);
void compute_min_hex(int n);
void compute_max_oct(int n);
void compute_min_oct(int n);
void compute_min_dec();
void compute_oct(int);
void compute_hex(int);
void compute_ones(int);
void compute_twos(int);
void sign_magni(int,int);
void compute_signed_max(int);
void compute_signed_min1(int);
void compute_signed_min2(int);
void compute_signed_min3(int);
char bin_prefix[] = "ob";
int bin[16] = {0};
int ones[16] = {0};
int main()
{ 
    const int dataset[11][3] = {{-6, 10, 4}, {-6, 9, 4}, {-6, 10, 5}, {-9, 10, 4}, {237, 10, 8}, {125, 8, 8}, {0xEB, 16, 8}, {-125, 10, 8},  {65400, 10, 8}, {65400, 10, 16}, {-32701, 10, 16} };
    int i=0;
    int deci = 0;
    int bin[16] = {0};
    int err_flag;
    int negative_flag;
	 for (i=0;i<11;i++)
    {   negative_flag = 0;
        if( dataset[i][0]<0)
           { negative_flag =1;
             printf("\n Negative Flag:%d",negative_flag);
            }
        print_input(dataset[i][0],dataset[i][1],dataset[i][2]);                              //Printing Input values
        
        if(dataset[i][1]!=8 && dataset[i][1]!=10 && dataset[i][1]!=16 )
			{                    //Error for radix
            printf("\n Error: Radix value is wrong for the input set  %d %d %d \nRadix value should be 8,10 or 16 but here it's %d \n",dataset[i][0],dataset[i][1],dataset[i][2],dataset[i][1]);
            continue;
			}
        if(dataset[i][2]!=4 && dataset[i][2]!=8 && dataset[i][2]!=16 )
			{                    //Error for Operand
            printf("\n Error: Operand value is wrong for the input set %d %d %d \nOperand value should be 4,8 or 16 but here it's %d \n",dataset[i][0],dataset[i][1],dataset[i][2],dataset[i][2]);
            continue;
			}
			
	       deci= abs(dataset[i][0]);
	       //Error for Size
            if (deci> pow(2, dataset[i][2])){
                printf("\n Error since operand size limit exceeded\n");
                continue;
            }
            
            if ((dataset[i][0]> pow(2, (dataset[i][2] - 1)))
                ||(dataset[i][0] < - pow(2, (dataset[i][2] - 1))))
                    err_flag = 1;
            else
                    err_flag = 0;
                
                    
          //printf("\n decimal number is %d\n",deci);
           /* decimal_bin(deci,dataset[i][2]); 
           compute_max(dataset[i][2]); 
           compute_min(dataset[i][2]);  
           compute_max_oct(dataset[i][2]);
           compute_min_oct(dataset[i][2]);
            printf("\n%d\n",i); */
        
	
            printf("Output:\t\tValue\t\t\tMaximum\t\t\tMinimum\t\t\n");                         //Printing Output headings
            //printf("\n decimal number is %d\n",deci);  
            decimal_bin(deci,dataset[i][2]);
            compute_max(dataset[i][2]); 
            compute_min(dataset[i][2]);
            printf("\nDecimal:        %d",deci);
            compute_max_decimal(dataset[i][2]);   
            compute_min_dec(dataset[i][2]);    
            compute_oct(deci);
            compute_max_oct(dataset[i][2]);
            compute_min_oct(dataset[i][2]);
            compute_hex(deci);
            compute_max_hex(dataset[i][2]);
            compute_min_hex(dataset[i][2]);
            printf("\n1's Complement\t");
            if(err_flag == 0)
                compute_ones(dataset[i][2]);
            else{                
            printf("Error");
            //if(dataset[i][2]==4) { printf(""); } //spacing for binary
            if(dataset[i][2]==8) { printf("\t"); } //spacing for binary
            if(dataset[i][2]==16) { printf("\t\t"); } //spacing for binary
            }
	    compute_signed_max(dataset[i][2]);
	    compute_signed_min1(dataset[i][2]);
            printf("\n2's Complement\t");
            if(err_flag == 0)
                compute_twos(dataset[i][2]);
            else
            {    printf("Error");
	    if(dataset[i][2]==8) { printf("\t"); } //spacing for binary
            if(dataset[i][2]==16) { printf("\t\t"); } //spacing for binary
            }
	    compute_signed_max(dataset[i][2]);
	    compute_signed_min2(dataset[i][2]);
            printf("\nSign magnitude\t");
            if(err_flag == 0)
             sign_magni(negative_flag,dataset[i][2]);
            else
               { printf("Error");
            if(dataset[i][2]==8) { printf("\t"); } //spacing for binary
            if(dataset[i][2]==16) { printf("\t\t"); } //spacing for binary
                }
	    compute_signed_max(dataset[i][2]);
	    compute_signed_min3(dataset[i][2]);
        //deci_to_otherconversions(deci,dataset[i][2]);
    printf("\n");
    }

    return 0;
}

void print_input(int val,int radix,int operand)
{
 if(radix==8){
     printf("\nInput:\t\tValue:%o\t\tRadix:%d\t\tOperand Size:%d\t\t\n",val,radix,operand); //print octal input values
       } 
if(radix==16){
     printf("\nInput:\t\tValue:%x\t\tRadix:%d\t\tOperand Size:%d\t\t\n",val,radix,operand); //print hexadecimal input values
       } 
if(radix==10){                       // else condition was worong !!! due to which value was printing 
     printf("\nInput:\t\tValue:%d\t\tRadix:%d\t\tOperand Size:%d\t\t\n",val,radix,operand); //print other input values
       }   
}
   		
void decimal_bin(int num, int n)
{   
	int binnum[n];
	int i, j;
	for(i=0;i<n;i++)
	{
		binnum[i]=num%2;
		num=num/2;
	}
	printf("Binary(abs)\t0b");
	for(i = n-1, j= 0; i>=0, j < n;i--,j++)
    {
        bin[j] = binnum[i];
        printf("%d",binnum[i]);
    }
    
}

void compute_max(int n)
   {
        int i;
        int max_value[n];
        for(i=0;i<n;i++)
           {
                max_value[i]=1;
            
           }
           if(n==4) { printf("\t\t\t0b"); } //spacing for binary
            if(n==8) { printf("\t\t0b"); } //spacing for binary
            if(n==16) { printf("\t0b"); } //spacing for binary
       for ( i=0;i<n;i++)
            {
                printf("%d",max_value[i]);
            }
    }


void compute_min(int n)
   {
        int i;
        int min_value[n];
        for(i=0;i<n;i++)
           {
                min_value[i]=0;
            }
        if(n==4) { printf("\t\t\t0b"); } //spacing for binary
        if(n==8) { printf("\t\t0b"); } //spacing for binary
        if(n==16) { printf("\t0b"); } //spacing for binary
       for ( i=0;i<n;i++)
            {
                printf("%d",min_value[i]);
            }
}

void decimal(int n)
 {
    printf("\nDec(abs):     %-5d",n); 
}
void compute_max_decimal(int n)
 {
    int i;
    uint16_t max_value = 0;
    for(i=0;i<n;i++)
    {   
        max_value = max_value + pow(2,i);
    }
    printf("\t\t\t%-5d",max_value);
}


void compute_max_hex(int n)
    {   
        int i;
        uint16_t max_value = 0;
        for(i=0;i<n;i++)
         {   max_value = max_value + pow(2,i);
            // printf("%d\n",pow(2,i));
         }
    printf("\t\t\t%-1X",max_value);
    }


void compute_min_hex(int n)
    {   int i;
        unsigned short int min_value=0;
    printf("\t\t\t%-1X",min_value);
    }

void compute_max_oct(int n)
    {   int i;
        uint16_t max_value = 0;
        for(i=0;i<n;i++)
         {   max_value = max_value + pow(2,i);
           }
    printf("\t\t\t%1o",max_value);
    }

void compute_min_oct(int n)
    {   int i;
        unsigned short int min_value=0;
    printf("\t\t\t%-1o",min_value);
    }
void compute_min_dec()
    {   int i;
        unsigned short int min_value=0;
    printf("\t\t\t%-1d",min_value);
    }
void compute_oct(int n)
    {
    printf("\nOctal(abs):     %-1o",n);    
    }  
void compute_hex(int n)
    {
    printf("\nHex(abs):       %-2X",n);    
    }   
void compute_ones(int n)
{
    int i=0;
    while(i<n) {
        ones[i]= !bin[i];
        i++;
    }
    printf("0b");
    for(i=0; i<n; i++)
        printf("%d",ones[i]);
}
void compute_twos(int n)
{
    
    int i;
    int add=0;
    int bintwo[n];
    if(ones[n-1]==1){
        bintwo[n-1]=0;
        add=1;
        
    }
    else{
        bintwo[n-1]=1;
        add=0;
    }
    for(i=1;i<n;i++){
    
    if (ones[n-i-1]==1 && add==1){
        bintwo[n-i-1]=0;
        add=1;
    }
    else if (ones[n-i-1]==0 && add==1){
        bintwo[n-i-1]=1;
        add=0;
    }
    else{
        bintwo[n-i-1]=ones[n-i-1];
    }
    }
    printf("0b");
    for(i=0; i<n; i++){
        printf("%d",bintwo[i]);
}
}
void sign_magni(int neg,int n)
{
    int i=0;
    if(neg==0){
        printf("0b");
        for(i=0;i<n;i++){
            printf("%d",bin[i]);
        }
    }
    else{
        printf("0b");
        bin[0]=1;
        for(i=0;i<n;i++){
            printf("%d",bin[i]);
        }
    }
}

void compute_signed_max( int x)
	{
		int max[x];
		max[0]=0;
		int i;
		for (i=1;i<x;i++)
			{
				max[i]=1;
			}
            if(x==4) { printf("\t\t\t0b"); } //spacing for binary
            if(x==8) { printf("\t\t0b"); } //spacing for binary
            if(x==16) { printf("\t0b"); } //spacing for binary
		for(i=0;i<x;i++)
		{
            printf("%-d",max[i]);
        	}
	}
void compute_signed_min1( int x)
	{
		int min[x];
		min[0]=1;
		int i;
		for (i=1;i<x;i++)
			{
				min[i]=0;
			}
            if(x==4) { printf("\t\t\t0b"); } //spacing for binary
            if(x==8) { printf("\t\t0b"); } //spacing for binary
            if(x==16) { printf("\t0b"); } //spacing for binary
		for(i=0;i<x;i++)
		{
            printf("%-d",min[i]);
        	}
	}
void compute_signed_min2( int x)
	{
		int min[x];
		min[0]=1;
		min[x]=1;
		int i;
		for (i=1;i<x-1;i++)
			{
				min[i]=0;
			}
            if(x==4) { printf("\t\t\t0b"); } //spacing for binary
            if(x==8) { printf("\t\t0b"); } //spacing for binary
            if(x==16) { printf("\t0b"); } //spacing for binary
		for(i=0;i<x;i++)
		{
            printf("%-d",min[i]);
        	}
	}

void compute_signed_min3( int x)
{
		int min[x];
		min[0]=1;
		min[x]=1;
		int i;
		for (i=1;i<x-1;i++)
			{
				min[i]=1;
			}
            if(x==4) { printf("\t\t\t0b"); } //spacing for binary
            if(x==8) { printf("\t\t0b"); } //spacing for binary
            if(x==16) { printf("\t0b"); } //spacing for binary
		for(i=0;i<x;i++)
		{
            printf("%-d",min[i]);
        	}
	}
