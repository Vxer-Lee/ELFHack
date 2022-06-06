#include <bits/types/FILE.h>
#include <new>
#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#define DEBUG 



struct SectionTable64{
    long Offset;
    long Size;
    int count;
    int shindex;
};
struct SectionTable32{
    int Offset;
    int Size;
    int count;
    int shindex;
};
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

/*****************************************读取ELF文件头******************************************************/
void ReadELFHeader64(FILE *fp,SectionTable64 &sectable64,int &offset,int &nSize,int &nCount,int &type)
{
    Elf64_Ehdr elf64_header;

    fseek(fp, SEEK_SET, SEEK_SET);
    fread(&elf64_header, sizeof(elf64_header), 1, fp);
    printf("\e[32m----------------------------[+]ELF文件头-----------------------------\n");
    printf("\e[37m");
    char szFileType[100]={0};
    type = elf64_header.e_type;
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


    sectable64.Offset = elf64_header.e_shoff;
    sectable64.Size = elf64_header.e_shentsize;
    sectable64.count = elf64_header.e_shnum;
    sectable64.shindex = elf64_header.e_shstrndx;

    offset = elf64_header.e_phoff;
    nSize = elf64_header.e_phentsize;
    nCount = elf64_header.e_phnum;
}
void ReadELFHeader32(FILE *fp,SectionTable32 &sectable32,int &offset,int &nSize,int &nCount,int &type)
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

    sectable32.Offset = elf32_header.e_shoff;
    sectable32.Size = elf32_header.e_shentsize;
    sectable32.count = elf32_header.e_shnum;
    sectable32.shindex = elf32_header.e_shstrndx;

    offset = elf32_header.e_phoff;
    nSize =  elf32_header.e_phentsize;
    nCount = elf32_header.e_phnum;
    type =  elf32_header.e_phnum;
}
/***********************************************************************************************************/



/****************************************读取程序头(文件段表)*************************************************/
void ReadProgrameHeader64(FILE *fp,int Offset,int nSize,int nCount)//段表偏移,段表大小,段表数量
{
    printf("\e[32m----------------------------[+]程序头(段表)-----------------------------\n");printf("\e[37m");
    //将文件指针移动到段表头
    fseek(fp, Offset, SEEK_SET);

    printf("大小0x%x\n",sizeof(Elf64_Phdr));

     for (int i=0; i<nCount; i++) {
         Elf64_Phdr elf64_programheader;
         fread(&elf64_programheader, nSize, 1,fp);
         printf("--> (%d)段信息 <--\n", i);

		 printf("*\e[32m[内存中段大小]:0x%x\n", elf64_programheader.p_memsz);printf("\e[37m");
		 printf("*\e[32m[内存中地址]:0x%x\n", elf64_programheader.p_vaddr);printf("\e[37m");
		 printf("*[文件中段大小]:0x%x\n", elf64_programheader.p_filesz);
		 printf("*[文件中地址]:0x%x\n", elf64_programheader.p_offset);
		 printf("*\e[32m[段的对其字节]:0x%x\n", elf64_programheader.p_align);printf("\e[37m");
		 printf("*[标志|属性]:0x%x ", elf64_programheader.p_flags);

         if(elf64_programheader.p_type == PT_LOAD)
         {
             printf("\e[35m(可加载)");printf("\e[37m");
             printf("|");  
         }
         //一共7种状态
         switch (elf64_programheader.p_flags) {
             case 1:
             {
                 printf("(可执行)\n");
                 break;
             }
             case 2:
             {
                 printf("(可写)\n");
                 break;
             }
             case 3:
             {
                 printf("(可写，可执行)\n");
                 break;
             }
             case 4:
             {
                 printf("(只读)\n");
                 break;
             }
             case 5:
             {
                 printf("\e[33m(只读，可执行)<可能是代码段!>\n");printf("\e[37m");
                 break;
             }
             case 6:
             {
                 printf("\e[31m(可读，可写)<可用来放数据!>\n");printf("\e[37m");
                 break;
             }
             case 7:
             {
                 printf("(可读,可写,可执行)<可能被恶意修改!>\n");
                 break;
             }
         }
         printf("\n");
     }
    fseek(fp, SEEK_SET, SEEK_SET);
}
void ReadProgrameHeader32(FILE *fp,int Offset,int nSize,int nCount)//段表偏移,段表大小,段表数量
{
    printf("\e[32m----------------------------[+]程序头(段表)-----------------------------\n");printf("\e[37m");
    //将文件指针移动到段表头
    fseek(fp, Offset, SEEK_SET);

    printf("大小0x%x\n",sizeof(Elf32_Phdr));

     for (int i=0; i<nCount; i++) {
         Elf32_Phdr elf64_programheader;
         fread(&elf64_programheader, nSize, 1,fp);
         printf("--> (%d)段信息 <--\n", i);

		 printf("*\e[32m[内存中段大小]:0x%x\n", elf64_programheader.p_memsz);printf("\e[37m");
		 printf("*\e[32m[内存中地址]:0x%x\n", elf64_programheader.p_vaddr);printf("\e[37m");
		 printf("*[文件中段大小]:0x%x\n", elf64_programheader.p_filesz);
		 printf("*[文件中地址]:0x%x\n", elf64_programheader.p_offset);
		 printf("*\e[32m[段的对其字节]:0x%x\n", elf64_programheader.p_align);printf("\e[37m");
		 printf("*[标志|属性]:0x%x ", elf64_programheader.p_flags);

         if(elf64_programheader.p_type == PT_LOAD)
         {
             printf("\e[35m(可加载)");printf("\e[37m");
             printf("|");  
         }
         //一共7种状态
         switch (elf64_programheader.p_flags) {
             case 1:
             {
                 printf("(可执行)\n");
                 break;
             }
             case 2:
             {
                 printf("(可写)\n");
                 break;
             }
             case 3:
             {
                 printf("(可写，可执行)\n");
                 break;
             }
             case 4:
             {
                 printf("(只读)\n");
                 break;
             }
             case 5:
             {
                 printf("\e[33m(只读，可执行)<可能是代码段!>\n");printf("\e[37m");
                 break;
             }
             case 6:
             {
                 printf("\e[31m(可读，可写)<可用来放数据!>\n");printf("\e[37m");
                 break;
             }
             case 7:
             {
                 printf("(可读,可写,可执行)<可能被恶意修改!>\n");
                 break;
             }
         }
         printf("\n");
     }
    fseek(fp, SEEK_SET, SEEK_SET);
}
/************************************************************************************************************/



/****************************************读取节表(Section Table)**********************************************/
void Read_shstrtab(FILE *fp,SectionTable64 sectable64,std::map<int,std::string> &map_shstr)
{
    //先读取.shstrtab节表
    Elf64_Shdr elf_shstrtab;
    fseek(fp, (sectable64.Offset+sectable64.Size) + ((sectable64.shindex-1)*sectable64.Size), SEEK_SET);
    fread(&elf_shstrtab, sectable64.Size, 1, fp);

    //将shstrtab节表数据放入到vector里面.
    int nIndex = elf_shstrtab.sh_offset;
    int nSize  = elf_shstrtab.sh_size;
    fseek(fp, nIndex, SEEK_SET);
    char *buf = (char*)malloc(nSize);
    memset(buf,0,nSize);
    fread(buf, nSize, 1, fp);
    int i2;
    int index=0;
    for (int i=0; i<nSize; i++) {
        char str[256] = {0};
        for (int j = i+1; j<nSize ; j++) 
        {
            if(buf[j] == 0)
            {
                i2 = j;
                break;
            }
        }
        if (i==0) {
        memcpy(str, buf+i+1, (i2-i+1));
        index = 1;
        }else {
            memcpy(str, buf+i, (i2-i));
            index = i;
        }
        i=i2;
        map_shstr.insert(std::pair<int, std::string>(index,str));
        //vec_shstr.push_back(str);
    }

    int i = 0;
    // for (std::vector<std::string>::iterator iter=vec_shstr.begin(); iter!=vec_shstr.end(); iter++) {
    //     printf("section name:%s %d\n",(*iter).c_str(),i);
    //     i++;
    // }
    fseek(fp, SEEK_SET, SEEK_SET);
}
void ReadSectionTable64(FILE *fp,SectionTable64 sectable64)
{
    printf("\e[32m----------------------------[+]节表(Section Table)-----------------------------\n");printf("\e[37m");
    printf("节数量:%d\n",sectable64.count);
    //读取shstrtab 所有节名都在这.
    //std::vector<std::string> vec_shstr;
    std::map<int , std::string> map_shstr;
    Read_shstrtab(fp,sectable64,map_shstr);
    //读取strtab 所有字符串都在这.
    
    //将文件指针移动到节表头
    fseek(fp, sectable64.Offset+sectable64.Size,SEEK_SET);
    for (int i=1; i<sectable64.count; i++) 
    {
        Elf64_Shdr elf_shdr;
        int n = sizeof(Elf64_Shdr);
        fread(&elf_shdr, sectable64.Size, 1, fp);
        switch (elf_shdr.sh_type) {
            case SHT_NULL:
            {
                //无效段
                break;
            }
            case SHT_PROGBITS:
            {
                //程序段
                break;
            }
            case SHT_SYMTAB:
            {
                //符号表
                break;
            }
            case SHT_STRTAB:
            {
                //字符串表
                break;
            }
            case SHT_RELA:
            {
                //重定位表
                break;
            }
            case SHT_HASH:
            {
                //符号表的HASH表
                break;
            }
            case SHT_DYNAMIC:
            {
                //动态链接信息
                break;
            }
            case SHT_NOTE:
            {
                //提示性信息
                break;
            }
            case SHT_NOBITS:
            {
                //该段在文件中没有内容
                break;
            }
            case SHT_REL:
            {
                //重定位信息
                break;
            }
            case SHT_SHLIB:
            {
                //保留
                break;
            }
            case SHT_DYNSYM:
            {
                //动态链接的符号
                break;
            }
        }

        // switch (elf_shdr.sh_flags) {
        //     case SHF_WRITE:
        //     {
        //         //表示该段在进程空间中可写
        //         break;
        //     }
        //     case SHF_ALLOC:
        //     {
        //         //表示该段在进程空间中需要分配空间。
        //         //.text .data. bss段都会有这个标志位
        //         break;
        //     }
        //     case SHF_EXECINSTR:
        //     {
        //         //表示该段在进程空间中可以被执行，一般是指代码段.
        //         break;
        //     }
        // }
       // if(elf_shdr.sh_type == SHT_STRTAB)
        printf("--> (%s)节信息 <--\n", map_shstr.at(elf_shdr.sh_name).c_str());
        printf("[sh_name:%d]\n",elf_shdr.sh_name);
        printf("[sh_type:0x%x]\n",elf_shdr.sh_type);
        printf("[sh_flags:0x%x]\n",elf_shdr.sh_flags);
        printf("[sh_addr:0x%x]\n",elf_shdr.sh_addr);
        printf("[sh_offset:0x%x]\n",elf_shdr.sh_offset);
        printf("[sh_size:0x%x]\n",elf_shdr.sh_size);
        printf("[sh_link:0x%x]\n",elf_shdr.sh_link);
        printf("[sh_info:0x%x]\n",elf_shdr.sh_info);
        printf("[sh_addralign:0x%x]\n",elf_shdr.sh_addralign);
        printf("[sh_entsize:0x%x]\n",elf_shdr.sh_entsize);
        printf("\n");
    }
    
}

void ReadSectionTable32(FILE *fp,SectionTable32 sectable32)
{

}
/************************************************************************************************************/

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
        int nType;
        SectionTable64 sectable64;
        //ELF头
        ReadELFHeader64(fp,sectable64,nOffset,nSize,nCount,nType); 
        if(nType != ET_REL)
        {
            //段表
            ReadProgrameHeader64(fp,nOffset,nSize,nCount);
        }
        //节表
        ReadSectionTable64(fp, sectable64);

    }else {
        //32位程序
        printf("[+] 32位\n");
        int nOffset ;
        int nSize;
        int nCount;
        int nType;
        SectionTable32 sectable32;
        ReadELFHeader32(fp,sectable32,nOffset,nSize,nCount,nType); 
        if(nType != ET_REL)
        {
            ReadProgrameHeader32(fp,nOffset,nSize,nCount);
        }
    }
    return 0;
}