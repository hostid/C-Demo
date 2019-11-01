#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
// Function prototype
void StreamClient(char *szServer, short nPort, char *szMessage);
// Helper macro for displaying errors
////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	char hostname[255];
	int nRet;
	short nPort;
	nPort =25;
	StreamClient("smtp.126.com", nPort, "AUTH LOGIN\r\n");
	return 0;
}
////////////////////////////////////////////////////////////
void StreamClient(char *szServer, short nPort, char *szMessage)
{
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	struct hostent *host;
	if((host=gethostbyname(szServer))==NULL)/*取得主机IP地址*/
	{
		fprintf(stderr,"Gethostname error, %s\n", strerror(errno));
		exit(1);
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)/*建立SOCKET连接*/
	{
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
		exit(1);
	}
	/* 客户程序填充服务端的资料 */
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(nPort);
	server_addr.sin_addr=*((struct in_addr *)host->h_addr);
	/* 客户程序发起连接请求 */
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)/*连接网站*/
	{
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
		exit(1);
	}
	printf("\nStream Client connecting to server: %s on port: %d",szServer, nPort);
	char szBuf[1024];
	memset(szBuf,0,1024);
	int nRet;
    //strcpy(szBuf, "From the Client");
	char buf[350]="0";
	char server[250];
	gethostname(server,250);
	strcpy(buf, "HELO ");
	strcat(buf, szServer);
	strcat(buf, " \r\n");
	printf("%s:::%d",buf,strlen(buf));
	//
	// Wait for a reply
	//
	nRet = recv(sockfd,szBuf,sizeof(szBuf)+1,0);  printf("\nData received OVER DATA: %s", szBuf);
	nRet = send(sockfd, buf, strlen(buf), 0);printf("\nsend %s",buf);
	nRet = recv(sockfd, szBuf, sizeof(szBuf), 0); printf("\nData received2: %s", szBuf);
	
	
	//发送准备登陆信息
	nRet = send(sockfd, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0);
	nRet = recv(sockfd, szBuf, sizeof(szBuf), 0); 
	printf("\nData received LOGIN: %s", szBuf);
	
	
	//发送用户名和密码,这里的用户名和密码必须用base64进行转码,发送转码以后的字符串，对于126邮箱来说用户名是@前面的字符串  //注意这里的密码指的是授权码
	nRet = send(sockfd,"cmV0cmllcw==\r\n", strlen("cmV0cmllcw==\r\n"),0);
	printf("\nData Send USERNAME");
	nRet = recv(sockfd, szBuf, sizeof(szBuf),0);
	printf("\nData received USERNAME: %s", szBuf);
	printf("\nData Send PASS");
	//发送用户密码
	nRet = send(sockfd,"QWE0MDg0NDE=\r\n", strlen("QWE0MDg0NDE=\r\n"), 0);
	//printf("\nData Send PASS");
	nRet = recv(sockfd, szBuf, sizeof(szBuf),0); printf("\nData received USERPASSWORD: %s", szBuf);
	
	
	//发送[发送邮件]的信箱(改成你的邮箱!），该邮箱要与用户名一致，否则发送不成功
	send(sockfd,"MAIL FROM: <retries@126.com>\r\n",strlen("MAIL FROM: <retries@126.com>\r\n"),0);printf("\nsend MAIL FROM\n");
	nRet = recv(sockfd, szBuf, sizeof(szBuf), 0);printf("\nData received MAILFROM: %s", szBuf);
	
	
	//发送[接收邮件]的邮箱
	nRet= send(sockfd,"RCPT TO: <jiangfeng.zhang@aliyun.com>\r\n",strlen("RCPT TO: <jiangfeng.zhang@aliyun.com>\r\n"),0);printf("\nsend RCPT TO\r\n");
	nRet = recv(sockfd, szBuf, sizeof(szBuf), 0);   printf("\nData received TO MAIL: %s", szBuf);
	/*
	nRet= send(sockfd,"RCPT TO: <server_ip_alert@hotmail.com>\r\n",strlen("RCPT TO: <server_ip_alert@hotmail.com>\r\n"),0);printf("\nsend RCPT TO\r\n");
	nRet = recv(sockfd, szBuf, sizeof(szBuf), 0);   printf("\nData received TO MAIL: %s", szBuf);
	*/
	char MailData[] ="From: \"retries@126.com\"<retries@126.com>\r\nTo: jiangfeng.zhang@aliyun.com\r\nSubject: IP Address\r\n\r\n"; //主题可以改成别的
	//各诉邮件服务器，准备发送邮件内容
	send(sockfd,"DATA\r\n", strlen("DATA\r\n"),0);printf("\nsend DATA\n");
	//  nRet = recv(sockfd, szBuf, sizeof(szBuf)+1, 0); printf("\nData receivedSEND DATA: %s", szBuf);
	//发送邮件标题
	send(sockfd,MailData, strlen(MailData),0);
	//发送邮件内容
	send(sockfd,"test!!!!\r\n", strlen("abcdefg\r\n"),0);//我随便写了几个字符进行测试
	//发送邮件结束
	send(sockfd,"\r\n.\r\n", strlen("\r\n.\r\n"),0);
	//接收邮件服务器返回信息
	nRet = recv(sockfd,szBuf,sizeof(szBuf),0);  printf("\nData received OVER DATA: %s", szBuf);
	send(sockfd,"QUIT\r\n", strlen("QUIT\r\n"),0);
	nRet = recv(sockfd,szBuf,sizeof(szBuf),0);  printf("\nData received QUIT: %s", szBuf);
	//
	// Display the received data
	//
	//printf("\nData received3: %s", szBuf);
	close(sockfd);
	return;
}