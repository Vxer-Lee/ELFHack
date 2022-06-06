#include <stdio.h>

extern char __executable_start[];
extern char etext[],_etext[],__etext[];
extern char edata[],_edata[];
extern char end[],_end[];

int main()
{
    printf("Executable Start 0x%X\n",__executable_start);
    printf("Text End 0x%X 0x%X 0x%X\n",etext,_etext,__etext);
    printf("Data End 0x%X 0x%X\n",edata,_edata);
    printf("Executable End 0x%X 0x%X\n",end,_end);
    return 0;
}