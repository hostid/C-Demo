#include <stdio.h>
#include <stdlib.h>

typedef int (*PF_PROC)(int, int);

PF_PROC g_pfProcess;

int AddProcess(int a, int b)
{
    return a + b;
}

void RegisterHookFun(PF_PROC pfProcess)
{
    g_pfProcess = AddProcess;
    //调用的时候加上函数的参数
    printf("call back = %d\n", g_pfProcess(2, 5));
}

void main()
{
    RegisterHookFun(AddProcess);
    return;
}
