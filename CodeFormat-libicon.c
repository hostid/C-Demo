/*
 * @FileName: 
 * @Descripttion: 
 * @Author: jiangfeng.zhang(jiangfeng.zhang@aliyun.com)
 * @LastEditTime: 2019-11-11 14:41:42
 */

#include <iconv.h>
#include <stdio.h>
#include <string.h>
int code_convert(char *inbuf,int inlen,char *outbuf,int outlen)
{
        iconv_t cd;
        int rc;
        char **pin = &inbuf;
        char **pout = &outbuf;
        cd = iconv_open("GB2312","UTF-8");
        if (cd==0)
                return -1;
        memset(outbuf,0,outlen);
        if (iconv(cd,pin,&inlen,pout,&outlen) == -1)
                return -1;
        iconv_close(cd);
        return 0;
}

int main()
{
  char src[4096] = "中";
  //注意：此处写为char src[4096] = "ccb7bfad";将不会被转换，因为系统认为是英文字母、而不是gbk的内码！
  char dst[4096];
  int srclen = 4096;
  int dstlen = 4096;
  int ret = code_convert(src,srclen,dst,dstlen);
  printf("TK--------->>>>ret is %d\nsrc is %s\ndst is %s\n",ret,src,dst);
  return 0;
}