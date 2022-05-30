#include <bits/types/FILE.h>
#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#define DEBUG 

void ReadSectionTable32(FILE *fp)
{

}

void ReadSectionTable64(FILE *fp)
{
    
}



void ReadSegmentTable64(FILE *fp)
{

}

void ReadSegmentTable32(FILE *fp)
{

}

/***********读取ELF文件头******************/
void ReadELFHeader64(FILE *fp,int &offset,int &nSize,int &nCount)
{
    Elf64_Ehdr elf64_header;

    fseek(fp, SEEK_SET, SEEK_SET);
    fread(&elf64_header, sizeof(elf64_header), 1, fp);
    printf("\e[32m----------------------------[+]ELF文件头-----------------------------\n");
    printf("\e[37m");
    char szFileType[100]={0};
    switch (elf64_header.e_type) {
        case ET_REL:
        {
            sprintf(szFileType, "%s", "重定位文件");
            break;
        }
        case ET_EXEC:
        {
            sprintf(szFileType, "%s", "EXE可执行程序");
            break;
        }
        case ET_DYN:
        {
            sprintf(szFileType, "%s", "so动态链接库");
            break;
        }
        case ET_CORE:
        {
            sprintf(szFileType, "%s", "Core Dump崩溃存储调试文件");
            break;
        }
    }
    printf("[-] ELF文件类型:%s\n",szFileType);
    char szCpu[100]={0};
    switch (elf64_header.e_machine) {
        case EM_386:
        {
            sprintf(szCpu, "%s", "Intel 80386");
            break;
        }
        case EM_MIPS:
        {
            sprintf(szCpu, "%s", "MIPS 大端");
            break;
        }
        case EM_MIPS_RS3_LE:
        {
            sprintf(szCpu, "%s", "MIPS小端");
            break;
        }
        case EM_X86_64:
        {
            sprintf(szCpu, "%s", "Intel X86");
            break;
        }
        case EM_ARM:
        {
            sprintf(szCpu, "%s", "ARM");
            break;
        }
        case EM_PPC:
        {
            sprintf(szCpu, "%s", "PowerPC");
            break;
        }
        case EM_PPC64:
        {
            sprintf(szCpu, "%s", "PowerPC 64位");
            break;
        }
        case EM_RISCV:
        {
            sprintf(szCpu, "%s", "RISC-V");
            break;
        }
    }
    printf("[-] CPU架构:%s\n",szCpu);
    printf("\e[33m[-] 程序入口点:0x%x\n",elf64_header.e_entry);printf("\e[37m");
    printf("[-] 段表文件偏移:0x%x\n",elf64_header.e_phoff);
    printf("[-] 节表文件偏移:0x%x\n",elf64_header.e_shoff);
    printf("[-] ELF文件头大小:0x%x\n",elf64_header.e_ehsize);
    printf("[-] 段表的大小:0x%x\n",elf64_header.e_phentsize);
    printf("\e[33m[-] 段的数量:0x%x(%d)\n",elf64_header.e_phnum,elf64_header.e_phnum);printf("\e[37m");
    printf("[-] 节表的大小:0x%x\n",elf64_header.e_shentsize);
    printf("\e[33m[-] 节的数量:0x%x(%d)\n",elf64_header.e_shnum,elf64_header.e_shnum);printf("\e[37m");
    printf("[-] 节字符串表的索引:0x%x\n",elf64_header.e_shstrndx);
    printf("\n");

    offset = elf64_header.e_phoff;
    nSize = elf64_header.e_phentsize;
    nCount = elf64_header.e_phnum;
}
void ReadELFHeader32(FILE *fp)
{
    Elf32_Ehdr elf32_header;
    fseek(fp, SEEK_SET, SEEK_SET);
    fread(&elf32_header, sizeof(elf32_header), 1, fp);
    printf("\e[32m----------------------------[+]ELF文件头-----------------------------\n");
    printf("\e[37m");
    char szFileType[100]={0};
    switch (elf32_header.e_type) {
        case ET_REL:
        {
            sprintf(szFileType, "%s", "重定位文件");
            break;
        }
        case ET_EXEC:
        {
            sprintf(szFileType, "%s", "EXE可执行程序");
            break;
        }
        case ET_DYN:
        {
            sprintf(szFileType, "%s", "so动态链接库");
            break;
        }
        case ET_CORE:
        {
            sprintf(szFileType, "%s", "Core Dump崩溃存储调试文件");
            break;
        }
    }
    printf("[-] ELF文件类型:%s\n",szFileType);
    char szCpu[100]={0};
    switch (elf32_header.e_machine) {
        case EM_386:
        {
            sprintf(szCpu, "%s", "Intel 80386");
            break;
        }
        case EM_MIPS:
        {
            sprintf(szCpu, "%s", "MIPS 大端");
            break;
        }
        case EM_MIPS_RS3_LE:
        {
            sprintf(szCpu, "%s", "MIPS小端");
            break;
        }
        case EM_X86_64:
        {
            sprintf(szCpu, "%s", "Intel X86");
            break;
        }
        case EM_ARM:
        {
            sprintf(szCpu, "%s", "ARM");
            break;
        }
        case EM_PPC:
        {
            sprintf(szCpu, "%s", "PowerPC");
            break;
        }
        case EM_PPC64:
        {
            sprintf(szCpu, "%s", "PowerPC 64位");
            break;
        }
        case EM_RISCV:
        {
            sprintf(szCpu, "%s", "RISC-V");
            break;
        }
    }
    printf("[-] CPU架构:%s\n",szCpu);
    printf("\e[33m[-] 程序入口点:0x%x\n",elf32_header.e_entry);printf("\e[37m");
    printf("[-] 段表文件偏移:0x%x\n",elf32_header.e_phoff);
    printf("[-] 节表文件偏移:0x%x\n",elf32_header.e_shoff);
    printf("[-] ELF文件头大小:0x%x\n",elf32_header.e_ehsize);
    printf("[-] 段表的大小:0x%x\n",elf32_header.e_phentsize);
    printf("\e[33m[-] 段的数量:0x%x(%d)\n",elf32_header.e_phnum,elf32_header.e_phnum);printf("\e[37m");
    printf("[-] 节表的大小:0x%x\n",elf32_header.e_shentsize);
    printf("\e[33m[-] 节的数量:0x%x(%d)\n",elf32_header.e_shnum,elf32_header.e_shnum);printf("\e[37m");
    printf("[-] 节字符串表的索引:0x%x\n",elf32_header.e_shstrndx);
    printf("\n");
}
/*****************************************/

/***********读取程序头(文件段表)******************/

void ReadProgrameHeader(FILE *fp,int Offset,int nSize,int nCount)//段表偏移,段表大小,段表数量
{
    printf("\e[32m----------------------------[+]程序头(段表)-----------------------------\n");printf("\e[37m");
    //将文件指针移动到段表头
    fseek(fp, SEEK_SET, Offset);

    printf("大小0x%x\n",sizeof(Elf64_Phdr));

     for (int i=0; i<nCount; i++) {
         Elf64_Phdr elf64_programheader;
         fread(&elf64_programheader, nSize, 1,fp);
         printf("-=-=-=-=-=-=[段%d]=-=-=-=-=-=\n",i);
         if(elf64_programheader.p_type == PT_LOAD)
         {
            printf("\e[33m[-] 当前段可以加载! PT_LOAD\n");printf("\e[37m");
         }else {
            printf("[-] 段的类型:%x\n",elf64_programheader.p_type);
         }

        // #define PF_X		(1 << 0)	/* Segment is executable */
        // #define PF_W		(1 << 1)	/* Segment is writable */
        // #define PF_R		(1 << 2)	/* Segment is readable */
         printf("[-] 段权限:0x%x [0x%x,0x%x,0x%x]\n",elf64_programheader.p_flags,PF_X,PF_W,PF_R);
         if (elf64_programheader.p_flags == PF_X) {
             printf("\e[33m[-] 当前段可执行!\n");printf("\e[37m");
         }else if(elf64_programheader.p_flags == PF_W)
         {
             printf("\e[33m[-] 当前段可写!\n");printf("\e[37m");
         }else if(elf64_programheader.p_flags == PF_R)
         {
             printf("\e[33m[-] 当前段只读!\n");printf("\e[37m");
         }else if(elf64_programheader.p_flags == (PF_X + PF_W))
         {
             printf("\e[33m[-] 当前段(可写)(可执行!)\n",elf64_programheader.p_flags);printf("\e[37m");
         }else if(elf64_programheader.p_flags == (PF_X + PF_R))
         {
             printf("\e[33m[-] 当前段(可执行)(只读)!\n");printf("\e[37m");
         }else if(elf64_programheader.p_flags == (PF_W+PF_R) )
         {
             printf("\e[33m[-] 当前段(可读可写)(不可执行!)\n");printf("\e[37m");
         }
         else if(elf64_programheader.p_flags == (PF_X+PF_W+PF_R) )
         {
             printf("\e[33m[-] 当前段(可读)(可写)(可执行!)\n");printf("\e[37m");
         }
         else {
            printf("[-] 段的权限:0x%x\n",elf64_programheader.p_flags);//p_flags
         }
         printf("[-] 段在文件中的偏移:0x%x\n",elf64_programheader.p_offset);//offset
         printf("\e[33m[-] 段的虚拟地址:0x%x\n",elf64_programheader.p_vaddr);printf("\e[37m");//va
         printf("[-] 段的内存大小:0x%x\n",elf64_programheader.p_memsz);
         printf("[-] 段的物理地址:0x%x\n",elf64_programheader.p_paddr);//pa
         printf("[-] 段的文件大小:0x%x\n",elf64_programheader.p_filesz);
         printf("[-] 段的对其字节:0x%x\n",elf64_programheader.p_align);
         printf("\n");
     }


    // printf("段的权限:");//p_flags
    // printf("段在文件中的偏移:");//offset
    // printf("段的虚拟地址:");//va
    // printf("段的物理地址:");//pa
    // printf("段的文件大小:");
    // printf("段的内存大小:");
    // printf("段的对其方式:");
    // printf("段的类型:");
    // switch (elf64_programheader.p_type) {
    //     case PT_NULL:
    //     {
    //         break;
    //     }
    //     case PT_LOAD:
    //     {
    //         printf("该段可以被加载到内存中执行!\n");
    //         break;
    //     }
    //     case PT_DYNAMIC:
    //     {
    //         break;
    //     }
    //     case PT_INTERP:
    //     {
    //         break;
    //     }
    //     case PT_NOTE:
    //     {
    //         break;
    //     }
    //     case PT_SHLIB:
    //     {
    //         break;
    //     }
    //     case PT_PHDR:
    //     {
    //         printf("段表本身");
    //         break;
    //     }
    //     case PT_TLS:
    //     {
    //         break;
    //     }
    //     case PT_NUM:
    //     {
    //         break;
    //     }
    //     case PT_LOOS:
    //     {
    //         break;
    //     }
    //     case PT_GNU_EH_FRAME:
    //     {
    //         break;
    //     }
    //     case PT_GNU_STACK:
    //     {
    //         break;
    //     }
    //     case PT_GNU_RELRO:
    //     {
    //         break;
    //     }
    //     case PT_LOSUNW:
    //          //PT_SUNWBSS:
    //     {
    //         break;
    //     }  
    //     case PT_SUNWSTACK:
    //     {
    //         break;
    //     }  
    //     case PT_HISUNW:
    //          //PT_HIOS:
    //     {
    //         break;
    //     }  
    //     case PT_LOPROC:
    //     {
    //         break;
    //     }  
    //     case PT_HIPROC:
    //     {
    //         break;
    //     }

   //}

    // #define	PT_NULL		0		/* Program header table entry unused */
    // #define PT_LOAD		1		/* Loadable program segment */
    // #define PT_DYNAMIC	2		/* Dynamic linking information */
    // #define PT_INTERP	3		/* Program interpreter */
    // #define PT_NOTE		4		/* Auxiliary information */
    // #define PT_SHLIB	5		/* Reserved */
    // #define PT_PHDR		6		/* Entry for header table itself */
    // #define PT_TLS		7		/* Thread-local storage segment */
    // #define	PT_NUM		8		/* Number of defined types */
    // #define PT_LOOS		0x60000000	/* Start of OS-specific */
    // #define PT_GNU_EH_FRAME	0x6474e550	/* GCC .eh_frame_hdr segment */
    // #define PT_GNU_STACK	0x6474e551	/* Indicates stack executability */
    // #define PT_GNU_RELRO	0x6474e552	/* Read-only after relocation */
    // #define PT_LOSUNW	0x6ffffffa
    // #define PT_SUNWBSS	0x6ffffffa	/* Sun Specific segment */
    // #define PT_SUNWSTACK	0x6ffffffb	/* Stack segment */
    // #define PT_HISUNW	0x6fffffff
    // #define PT_HIOS		0x6fffffff	/* End of OS-specific */
    // #define PT_LOPROC	0x70000000	/* Start of processor-specific */
    // #define PT_HIPROC	0x7fffffff	/* End of processor-specific */
    //int nnn = 6;
}
/*******************************************/


/*
 * 判断ELF程序位数
 */
bool isELF64(FILE* fp){
    //通过读取头文件，的第5个字节来判断是否是64位的ELF程序.
    bool bret = false;
    
    char is64Byte[1] = {0};
    fread(is64Byte, 1, 1, fp);

    if (is64Byte[0] == '\x02') {
    bret = true;
    }
    return bret;
}

/*
 * 判断ELF文件格式
 */
bool isELF(FILE *fp){
    bool bret = false;
    char Magic[4]={0};
    fread(Magic, 4, 1, fp);

    //7f 45 4c 46 
    if (Magic[0] == '\x7f' && Magic[1] == '\x45' && Magic[2] == '\x4c' && Magic[3] == '\x46') {
    bret = true;
    }
    return bret;
}

/*
 * ELFHack 帮助信息
 */
void usage(){  
    printf("\e[34m███████╗██╗     ███████╗██╗  ██╗ █████╗  ██████╗██╗  ██╗\n");
    printf("\e[34m██╔════╝██║     ██╔════╝██║  ██║██╔══██╗██╔════╝██║ ██╔╝\n");
    printf("\e[34m█████╗  ██║     █████╗  ███████║███████║██║     █████╔╝ \n");
    printf("\e[34m██╔══╝  ██║     ██╔══╝  ██╔══██║██╔══██║██║     ██╔═██╗ \n");
    printf("\e[34m███████╗███████╗██║     ██║  ██║██║  ██║╚██████╗██║  ██╗\n");
    printf("\e[34m╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n");
    printf("                                \e[32mFrom PWN菜鸡小分队 Lee\n");
    printf("\e[37m(ELFHack是一款ELF文件分析工具，可以分析出文件头、节表名、导入导出函数等.)\n");
    printf("\n");
    printf("Usage:\n");
    printf("      ELFHack ./hello\n");
    printf("\n");
}


int main(int argc,char *argv[])
{
    //判断用户输入的参数是否正确，如果不正确则输出usage帮助手册
    #ifndef DEBUG
    if(argc<2) {
    usage();
    return 0;
    }
    #endif

    //通过只读二进制方式打开要读取的ELF程序
    #ifndef DEBUG
    const char* path = argv[1];
    #else
    const char* path = "/home/pwn/ELFHack/build/hello";
    #endif

    FILE *fp = fopen(path, "rb");

    //通过读取文件魔术来判断是否是属于ELF文件，如果不是直接return掉
    if(!isELF(fp))
    {
        printf("\e[31m该文件不是ELF格式，无法进行分析！");
        printf("\e[37m\n");
        return 0;
    }

    //通过读取第5个字节来判断是否是64位程序
    if (isELF64(fp)) {
        //64位程序
        printf("[+] 64位\n");
        int nOffset ;
        int nSize;
        int nCount;
        ReadELFHeader64(fp,nOffset,nSize,nCount); 
        ReadProgrameHeader(fp,nOffset,nSize,nCount);

    }else {
        //32位程序
        printf("[+] 32位\n");
        ReadELFHeader32(fp);
    }
    return 0;
}