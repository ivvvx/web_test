// project_design.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "ws2tcpip.h"
#include "SIO_RCVALL_file.h"
#pragma comment(lib,"Ws2_32.lib")
#define default_buflen 65536
#define default_namelen 500
// IP头部结构体
typedef struct _iphdr {
    unsigned char h_verlen;//首部长度
    unsigned char tos;//服务类型
    unsigned short total_len;//总长度
    unsigned short ident;//标识符
    unsigned short frag_and_flags;//标志位
    unsigned char ttl;//生存时间
    unsigned char proto;//协议
    unsigned short checksum;//首部校验和
    unsigned int sourceIP;//源IP
    unsigned int destIP;//目的IP
} IPHDR, *PIPHDR;

// TCP头部结构体
typedef struct _tcphdr {
    USHORT source;
    USHORT dest;
    unsigned long seq;//序列号
    unsigned long ack_seq;//确认号
    unsigned char offx2;//数据偏移
    unsigned char flags;
    USHORT window;//窗口大小
    USHORT checksum;//校验和
    USHORT urg_ptr;//紧急指针
} TCPhdr, *PTCPhdr;

// UDP头部结构体
typedef struct _udphdr {
    USHORT source;//源端口
    USHORT dest;//目的端口
    USHORT len;//长度
    USHORT checksum;//校验和
} UDPHdr, *PUDPHdr;
// 解析IP头部
void parseIPHeader(char *buf, int num) {
    PIPHDR iphdr = (PIPHDR)buf;
    printf("IP Header:\n");
    printf("  Version: %d\n", iphdr->h_verlen >> 4);
    printf("  IHL: %d\n", iphdr->h_verlen & 0x0F);
    printf("  TOS: 0x%02X\n", iphdr->tos);
    printf("  Total Length: %d\n", ntohs(iphdr->total_len));
    printf("  ID: %d\n", ntohs(iphdr->ident));
    printf("  Flags: 0x%02X\n", iphdr->frag_and_flags >> 13);
    printf("  Fragment Offset: %d\n", ntohs(iphdr->frag_and_flags) & 0x1FFF);
    printf("  TTL: %d\n", iphdr->ttl);
    printf("  Protocol: %d\n", iphdr->proto);
    printf("  Checksum: 0x%04X\n", ntohs(iphdr->checksum));
    printf("  Source IP: %s\n", inet_ntoa(*(struct in_addr *)&iphdr->sourceIP));
    printf("  Destination IP: %s\n", inet_ntoa(*(struct in_addr *)&iphdr->destIP));
}

// 解析TCP头部
void parseTCPHeader(char *buf) {
    PIPHDR iphdr = (PIPHDR)buf;
    PTCPhdr tcphdr = (PTCPhdr)(buf + (iphdr->h_verlen & 0x0F) * 4);
    printf("TCP Header:\n");
    printf("  Source Port: %d\n", ntohs(tcphdr->source));
    printf("  Destination Port: %d\n", ntohs(tcphdr->dest));
    printf("  Sequence Number: %u\n", ntohl(tcphdr->seq));
    printf("  Acknowledgment Number: %u\n", ntohl(tcphdr->ack_seq));
    printf("  Data Offset: %d\n", tcphdr->offx2 >> 4);
    printf("  Flags: ");
    if (tcphdr->flags & 0x02)
        printf("SYN ");
    if (tcphdr->flags & 0x10)
        printf("ACK ");
    if (tcphdr->flags & 0x08)
        printf("PSH ");
    if (tcphdr->flags & 0x04)
        printf("RST ");
    if (tcphdr->flags & 0x01)
        printf("FIN ");
    if (tcphdr->flags & 0x20)
        printf("URG ");
    printf("\n");
    printf("  Window: %d\n", ntohs(tcphdr->window));
    printf("  Checksum: 0x%04X\n", ntohs(tcphdr->checksum));
    printf("  Urgent Pointer: %d\n", ntohs(tcphdr->urg_ptr));
}

// 解析UDP头部
void parseUDPHeader(char *buf) {
    PIPHDR iphdr = (PIPHDR)buf;
    PUDPHdr udphdr = (PUDPHdr)(buf + (iphdr->h_verlen & 0x0F) * 4);
    printf("UDP Header:\n");
    printf("  Source Port: %d\n", ntohs(udphdr->source));
    printf("  Destination Port: %d\n", ntohs(udphdr->dest));
    printf("  Length: %d\n", ntohs(udphdr->len));
    printf("  Checksum: 0x%04X\n", ntohs(udphdr->checksum));
}
// 根据IP地址查找数据包
bool findPacketByIP(char *buf, int num, char *targetIP) {
    PIPHDR iphdr = (PIPHDR)buf;
    char sourceIP[50];
    char destIP[50];
    strcpy(sourceIP, inet_ntoa(*(struct in_addr *)&iphdr->sourceIP));
    strcpy(destIP, inet_ntoa(*(struct in_addr *)&iphdr->destIP));
    if (strcmp(sourceIP, targetIP) == 0 || strcmp(destIP, targetIP) == 0)
        return true;
    return false;
}
int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET s=INVALID_SOCKET;
	char buf[default_buflen];
	int iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iResult!=0)
	{
		printf("初始化错误");
		return 1;
	}
	s=socket(AF_INET,SOCK_RAW,IPPROTO_IP);
	if(s==INVALID_SOCKET)
	{
		printf("创建套接字失败");
		WSACleanup();
		return 1;
	}
	printf("创建原始套接字成功");
	struct hostent *local;
	char Hostname[default_namelen];
	struct in_addr addr;
	struct sockaddr_in LocalAddr,RemoteAddr;
	int addrlen=sizeof(struct sockaddr_in);
	/*memset(&LocalAddr,0,sizeof(LocalAddr));
	LocalAddr.sin_family=AF_INET;
	LocalAddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	LocalAddr.sin_port=htons(0);*/
	//获取本机地址
	memset(Hostname,0,default_namelen);
	iResult=gethostname(Hostname,sizeof(Hostname));
	if(iResult==SOCKET_ERROR)
	{
		printf("获取本机地址失败：%ld\n",WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//获取可用的IP
	local=gethostbyname(Hostname);
	printf("\n本机可用的IP为：\n");
	if(local==NULL)
	{
		printf("获取可用IP失败：%ld\n",WSAGetLastError());
		WSACleanup();
		return 1;
	}
	int i=0,in=0;
	while(local->h_addr_list[i] !=0){
		addr.s_addr=*(u_long*)local->h_addr_list[i++];
		printf("\t可用ip地址 %d：%s\n",i,inet_ntoa(addr));
	}
	printf("\n选择接口号来捕获数据：");
	scanf("%d",&in);
	memset(&LocalAddr,0,sizeof(LocalAddr));
	memcpy(&LocalAddr.sin_addr.S_un.S_addr,local->h_addr_list[in-1],sizeof(LocalAddr.sin_addr.S_un.S_addr));
	LocalAddr.sin_family=AF_INET;
	LocalAddr.sin_port=0;
	iResult=bind(s,(struct sockaddr*)&LocalAddr,sizeof(LocalAddr));
	if(iResult==SOCKET_ERROR)
	{
		printf("绑定本地地址失败：%ld\n",WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	//printf("\n套接字绑定成功");
	printf("\n套接字与%d号接口地址绑定成功",in);
	//设置套接字接收命令（混合模式）
	DWORD dwBufferLen[10];
	DWORD Optval=1;
	DWORD dwBytesReturned=0;
	iResult=WSAIoctl(s,SIO_RCVALL,&Optval,sizeof(Optval),&dwBufferLen,sizeof(dwBufferLen),&dwBytesReturned,NULL,NULL);
	if(iResult==SOCKET_ERROR)
	{
		printf("混合模式设置失败：%ld\n",WSAGetLastError());
		closesocket(s);
		WSACleanup();
	}
	//DWORD dw_rcval=1;
	//ioctlsocket(s,SIO_RCVALL,&dw_rcval);
	printf("\n开始接收数据\n");
	int m=0;
	do{
		iResult=recvfrom(s,buf,default_buflen,0,(struct sockaddr*)&RemoteAddr,&addrlen);
		if(iResult>0)
		{
			printf("\n接收到来自%s的数据包，长度为：%d\n",inet_ntoa(RemoteAddr.sin_addr),iResult);
			//analy(buf);
			// 解析IP头部
			parseIPHeader(buf, iResult);
			// 根据协议类型进一步解析上层协议头部
			PIPHDR iphdr = (PIPHDR)buf;
			switch (iphdr->proto) {
			case IPPROTO_TCP:
				parseTCPHeader(buf);
			case IPPROTO_UDP:
				parseUDPHeader(buf);
				break;
				break;
			default:
				break;
			}
			printf("\n");
		}
		else{
			printf("\n数据接收失败：%ld\n",WSAGetLastError());
		}
		m++;
	}while(m<3);
	printf("根据IP地址查找数据包\n");
	char targetIP[50] ;
	printf("输入要查找的IP：");
	scanf("%s",&targetIP);
	if (findPacketByIP(buf, iResult, targetIP)) {
		printf("\nPacket with target IP:%s found!\n",targetIP);
	}
	else{
		printf("\nNot Found!\n");
	}
	closesocket(s);
	WSACleanup();
	return 0;
}

