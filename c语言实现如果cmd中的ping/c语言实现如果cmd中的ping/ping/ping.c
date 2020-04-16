/*������ļ�*/
#pragma comment( lib, "ws2_32.lib" )
/*����ͷ�ļ�*/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
/*���峣��*/
/*��ʾҪ��¼·��*/
#define IP_RECORD_ROUTE  0x7
/*Ĭ�����ݱ���С*/
#define DEF_PACKET_SIZE  32 
/*����ICMP���ݱ���С*/
#define MAX_PACKET       1024    
/*���IPͷ����*/
#define MAX_IP_HDR_SIZE  60 
/*ICMP�������ͣ���������*/      
#define ICMP_ECHO        8
/*ICMP�������ͣ�����Ӧ��*/ 
#define ICMP_ECHOREPLY   0
/*��С��ICMP���ݱ���С*/
#define ICMP_MIN         8

/*�Զ��庯��ԭ��*/
void InitPing();
void UserHelp();

void GetArgments(int argc, char** argv); 
USHORT CheckSum(USHORT *buffer, int size);
void FillICMPData(char *icmp_data, int datasize);
void FreeRes();

void DecodeIPOptions(char *buf, int bytes);
void DecodeICMPHeader(char *buf, int bytes, SOCKADDR_IN* from);

void PingTest(int timeout);



/*IP��ͷ�ֶ����ݽṹ*/
typedef struct _iphdr 
{
    unsigned int   h_len:4;        /*IP��ͷ����*/
    unsigned int   version:4;      /*IP�İ汾��*/
    unsigned char  tos;            /*���������*/
    unsigned short total_len;      /*���ݱ��ܳ���*/
    unsigned short ident;          /*Ωһ�ı�ʶ��*/
    unsigned short frag_flags;     /*�ֶα�־*/
    unsigned char  ttl;            /*������*/
    unsigned char  proto;          /*Э������(TCP��UDP��)*/
    unsigned short checksum;       /*У���*/
    unsigned int   sourceIP;       /*ԴIP��ַ*/
    unsigned int   destIP;         /*Ŀ��IP��ַ*/
} IpHeader;

/*ICMP��ͷ�ֶ����ݽṹ*/
typedef struct _icmphdr 
{
    BYTE   i_type;				   /*ICMP��������*/
    BYTE   i_code;                 /*�������еĴ����*/
    USHORT i_cksum;                /*У���*/ 
    USHORT i_id;                   /*Ωһ�ı�ʶ��*/
    USHORT i_seq;                  /*���к�*/
    ULONG  timestamp;              /*ʱ���*/  
} IcmpHeader;

/*IPѡ��ͷ�ֶ����ݽṹ*/
typedef struct _ipoptionhdr
{
   
	unsigned char  code;           /*ѡ������*/
    unsigned char  len;            /*ѡ��ͷ����*/
    unsigned char  ptr;            /*��ַƫ�Ƴ���*/
	unsigned long  addr[9];        /*��¼��IP��ַ�б�*/
} IpOptionHeader;

/*����ȫ�ֱ���*/
SOCKET m_socket;
IpOptionHeader IpOption;
SOCKADDR_IN DestAddr;
SOCKADDR_IN SourceAddr;
char *icmp_data;
char *recvbuf;
USHORT seq_no ;
char *lpdest;
int datasize;
BOOL RecordFlag;
double PacketNum;
BOOL SucessFlag;


/*��ʼ����������*/   
void InitPing()
{
  WSADATA wsaData;
  icmp_data = NULL;
  seq_no = 0;
  recvbuf = NULL;
  RecordFlag = FALSE;
  lpdest = NULL;
  datasize = DEF_PACKET_SIZE;
  PacketNum = 5;
  SucessFlag = FALSE;

  /*Winsock��ʼ��*/
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        /*�����ʼ�����ɹ��򱨴�GetLastError()���ط����Ĵ�����Ϣ*/
		printf("WSAStartup() failed: %d\n", GetLastError());
        return ;
    }
  m_socket = INVALID_SOCKET;
}

/*��ʾ��Ϣ����*/
void UserHelp()
{
	printf("UserHelp: ping -r <host> [data size]\n");
    printf("          -r           record route\n");
	printf("          -n           record amount\n");
    printf("          host         remote machine to ping\n");
    printf("          datasize     can be up to 1KB\n");
		
    ExitProcess(-1); 
}


/*��ȡpingѡ���*/
void GetArgments(int argc,char** argv)
{
   int i;
   int j;
   int exp;
   int len;
   int m;
   /*���û��ָ��Ŀ�ĵص�ַ���κ�ѡ��*/
   if(argc == 1)
	{
		printf("\nPlease specify the destination IP address and the ping option as follow!\n");
	    UserHelp();
	}

	for(i = 1; i < argc; i++)
    {
        len = strlen(argv[i]);
		if (argv[i][0] == '-')
        {
            /*ѡ��ָʾҪ��ȡ��¼������*/
			if(isdigit(argv[i][1]))
			{
				PacketNum = 0;
				for(j=len-1,exp=0;j>=1;j--,exp++)
					/*����argv[i][j]�е�ASCIIֵ����Ҫ��ȡ�ļ�¼����(ʮ������)*/
					PacketNum += ((double)(argv[i][j]-48))*pow(10,exp);
			}
			else
			{
				switch (tolower(argv[i][1]))
				{
					/*ѡ��ָʾҪ��ȡ·����Ϣ*/
					case 'r':        
						RecordFlag = TRUE;
						break;
					/*û�а�Ҫ���ṩѡ��*/
					default:
						UserHelp();
						break;
				}
			}
        }
		/*���������ݱ���С����IP��ַ*/
        else if (isdigit(argv[i][0]))
		{
			for(m=1;m<len;m++)
			{
				if(!(isdigit(argv[i][m])))
				{
					/*��IP��ַ*/
					lpdest = argv[i];
					break;
				}
				/*�����ݱ���С*/
				else if(m==len-1)
					datasize = atoi(argv[i]);				 
			}
		}
		/*������������*/
        else
            lpdest = argv[i];
    }
}

/*��У��ͺ���*/
USHORT CheckSum(USHORT *buffer, int size)
{
	unsigned long cksum=0;
    while (size > 1) 
    {
        cksum += *buffer++;
        size -= sizeof(USHORT);
    }
    if (size) 
    {
        cksum += *(UCHAR*)buffer;
    }
	/*��ÿ��16bit���ж����Ʒ������*/
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);
    return (USHORT)(~cksum);
}


/*���ICMP���ݱ��ֶκ���*/
void FillICMPData(char *icmp_data, int datasize)
{
    IcmpHeader *icmp_hdr = NULL;
    char      *datapart = NULL;

    icmp_hdr = (IcmpHeader*)icmp_data;
	/*ICMP������������Ϊ��������*/
    icmp_hdr->i_type = ICMP_ECHO;        
    icmp_hdr->i_code = 0;
	/*��ȡ��ǰ����IP��Ϊ��ʶ��*/
    icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
    icmp_hdr->i_cksum = 0;
    icmp_hdr->i_seq = 0;
	datapart = icmp_data + sizeof(IcmpHeader);
	/*������0���ʣ��ռ�*/
	memset(datapart,'0',datasize-sizeof(IcmpHeader));
}

/*�ͷ���Դ����*/
void FreeRes()
{
	/*�رմ������׽���*/
	if (m_socket != INVALID_SOCKET) 
        closesocket(m_socket);
	/*�ͷŷ�����ڴ�*/
    HeapFree(GetProcessHeap(), 0, recvbuf);
    HeapFree(GetProcessHeap(), 0, icmp_data);
	/*ע��WSAStartup()����*/
    WSACleanup();
    return ;
}


/*���IPѡ��ͷ����*/
void DecodeIPOptions(char *buf, int bytes)
{
	IpOptionHeader *ipopt = NULL;
    IN_ADDR inaddr;
    int i;
    HOSTENT *host = NULL;
	/*��ȡ·����Ϣ�ĵ�ַ���*/
    ipopt = (IpOptionHeader *)(buf + 20);

    printf("RR:   ");
    for(i = 0; i < (ipopt->ptr / 4) - 1; i++)
    {
        inaddr.S_un.S_addr = ipopt->addr[i];
        if (i != 0)
            printf("      ");
		/*����IP��ַ��ȡ������*/
        host = gethostbyaddr((char *)&inaddr.S_un.S_addr,sizeof(inaddr.S_un.S_addr), AF_INET);
        /*�����ȡ�����������������������*/
		if (host)
            printf("(%-15s) %s\n", inet_ntoa(inaddr), host->h_name);
        /*�������IP��ַ*/
		else
            printf("(%-15s)\n", inet_ntoa(inaddr));
    }
    return;
}

/*���ICMP��ͷ����*/
void DecodeICMPHeader(char *buf, int bytes, SOCKADDR_IN *from)
{
	IpHeader *iphdr = NULL;
    IcmpHeader *icmphdr = NULL;
    unsigned short iphdrlen;
    DWORD tick;
    static int icmpcount = 0;

    iphdr = (IpHeader *)buf;
    /*����IP��ͷ�ĳ���*/
    iphdrlen = iphdr->h_len * 4;
    tick = GetTickCount();
	
	/*���IP��ͷ�ĳ���Ϊ��󳤶�(����������20�ֽ�)������Ϊ��IPѡ���Ҫ���IPѡ��*/
    if ((iphdrlen == MAX_IP_HDR_SIZE) && (!icmpcount))
		/*���IPѡ���·����Ϣ*/
        DecodeIPOptions(buf, bytes);

	/*�����ȡ������̫С*/
    if (bytes < iphdrlen + ICMP_MIN) 
    {
        printf("Too few bytes from %s\n", 
            inet_ntoa(from->sin_addr));
    }
    icmphdr = (IcmpHeader*)(buf + iphdrlen);

	/*����յ��Ĳ��ǻ���Ӧ�����򱨴�*/
    if (icmphdr->i_type != ICMP_ECHOREPLY) 
    {
        printf("nonecho type %d recvd\n", icmphdr->i_type);
        return;
    }
    /*��ʵ�յ���ID�źͷ��͵��Ƿ�һ��*/
    if (icmphdr->i_id != (USHORT)GetCurrentProcessId()) 
    {
        printf("someone else's packet!\n");
        return ;
    }
	SucessFlag = TRUE;
	/*�����¼��Ϣ*/
    printf("%d bytes from %s:", bytes, inet_ntoa(from->sin_addr));
    printf(" icmp_seq = %d. ", icmphdr->i_seq);
    printf(" time: %d ms", tick - icmphdr->timestamp);
    printf("\n");

    icmpcount++;
    return;
}

/*ping����*/
void PingTest(int timeout)
{   
	int ret;
	int readNum;
	int fromlen;
	struct hostent *hp = NULL;
	/*����ԭʼ�׽��֣����׽�������ICMPЭ��*/
	m_socket = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0,WSA_FLAG_OVERLAPPED);
	/*����׽��ִ������ɹ�*/
    if (m_socket == INVALID_SOCKET) 
    {
        printf("WSASocket() failed: %d\n", WSAGetLastError());
        return ;
    }

	/*��Ҫ���¼·��ѡ��*/
    if (RecordFlag)
    {
        /*IPѡ��ÿ���ֶ���0��ʼ��*/
        ZeroMemory(&IpOption, sizeof(IpOption));
		/*Ϊÿ��ICMP������·��ѡ��*/
        IpOption.code = IP_RECORD_ROUTE; 
        IpOption.ptr  = 4;               
        IpOption.len  = 39;              
  
        ret = setsockopt(m_socket, IPPROTO_IP, IP_OPTIONS,(char *)&IpOption, sizeof(IpOption));
        if (ret == SOCKET_ERROR)
        {
            printf("setsockopt(IP_OPTIONS) failed: %d\n",WSAGetLastError());
        }
    }

    /*���ý��յĳ�ʱֵ*/
    readNum = setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO,(char*)&timeout, sizeof(timeout));
    if(readNum == SOCKET_ERROR) 
    {
        printf("setsockopt(SO_RCVTIMEO) failed: %d\n",WSAGetLastError());
        return ;
    }
	/*���÷��͵ĳ�ʱֵ*/
    timeout = 1000;
    readNum = setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO,(char*)&timeout, sizeof(timeout));
    if (readNum == SOCKET_ERROR) 
    {
        printf("setsockopt(SO_SNDTIMEO) failed: %d\n",WSAGetLastError());
        return ;
    }

	/*��0��ʼ��Ŀ�ĵص�ַ*/
    memset(&DestAddr, 0, sizeof(DestAddr));
	/*���õ�ַ�壬�����ʾʹ��IP��ַ��*/
	DestAddr.sin_family = AF_INET;
    if ((DestAddr.sin_addr.s_addr = inet_addr(lpdest)) == INADDR_NONE)
    {   
        	
        /*���ֽ�����������������ȡIP��ַ*/
		if ((hp = gethostbyname(lpdest)) != NULL)
        {
            /*����ȡ����IPֵ����Ŀ�ĵص�ַ�е���Ӧ�ֶ�*/
			memcpy(&(DestAddr.sin_addr), hp->h_addr, hp->h_length);
			/*����ȡ���ĵ�ַ��ֵ����Ŀ�ĵص�ַ�е���Ӧ�ֶ�*/
            DestAddr.sin_family = hp->h_addrtype;
            printf("DestAddr.sin_addr = %s\n", inet_ntoa(DestAddr.sin_addr));
        }
        /*��ȡ���ɹ�*/
		else
        {
            printf("gethostbyname() failed: %d\n",WSAGetLastError());
            return ;
        }
    }        

	/*���ݱ��Ĵ�С��Ҫ����ICMP��ͷ*/
    datasize += sizeof(IcmpHeader);  
	/*����Ĭ�϶Ѿ�����Ӷ��з���MAX_PACKET�ڴ�飬�·����ڴ�����ݽ�����ʼ��Ϊ0*/
    icmp_data =(char*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,MAX_PACKET);
    recvbuf =(char*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,MAX_PACKET);

	/*��������ڴ治�ɹ�*/
    if (!icmp_data) 
    {
        printf("HeapAlloc() failed: %d\n", GetLastError());
        return ;
    }
	/* ����ICMP����*/
    memset(icmp_data,0,MAX_PACKET);
    FillICMPData(icmp_data,datasize);

    
    while(1) 
    {
        static int nCount = 0;
        int writeNum;
        /*����ָ���ļ�¼�������˳�*/        
        if (nCount++ == PacketNum) 
            break;

         /*����У���ǰҪ��У����ֶ�����Ϊ0*/       
        ((IcmpHeader*)icmp_data)->i_cksum = 0;
		/*��ȡ����ϵͳ�����������������ĺ�����������ʱ���*/
        ((IcmpHeader*)icmp_data)->timestamp = GetTickCount();
		/*�������к�*/
        ((IcmpHeader*)icmp_data)->i_seq = seq_no++;
		/*����У���*/
        ((IcmpHeader*)icmp_data)->i_cksum = CheckSum((USHORT*)icmp_data, datasize);
		/*��ʼ����ICMP���� */
        writeNum = sendto(m_socket, icmp_data, datasize, 0,(struct sockaddr*)&DestAddr, sizeof(DestAddr));
        
		/*������Ͳ��ɹ�*/
		if (writeNum == SOCKET_ERROR)
        {
            /*��������ڳ�ʱ���ɹ�*/
			if (WSAGetLastError() == WSAETIMEDOUT) 
            {
                printf("timed out\n");
				continue;
            }
			/*�������Ͳ��ɹ�ԭ��*/
            printf("sendto() failed: %d\n", WSAGetLastError());
            return ;
        }

		/*��ʼ����ICMPӦ�� */
        fromlen = sizeof(SourceAddr);
        readNum = recvfrom(m_socket, recvbuf, MAX_PACKET, 0,(struct sockaddr*)&SourceAddr, &fromlen);
        /*������ղ��ɹ�*/
		if (readNum == SOCKET_ERROR)
        {
            /*��������ڳ�ʱ���ɹ�*/
			if (WSAGetLastError() == WSAETIMEDOUT) 
            {
                printf("timed out\n");
				continue;
            }
			/*�������ղ��ɹ�ԭ��*/
            printf("recvfrom() failed: %d\n", WSAGetLastError());
            return ;
        }
		/*������յ���ICMP���ݱ�*/
        DecodeICMPHeader(recvbuf, readNum, &SourceAddr);
    }
}


int main(int argc, char* argv[])
{   
    InitPing();  
	GetArgments(argc, argv); 
		
    PingTest(1000);
	
	/*�ӳ�1��*/
    Sleep(1000);

	if(SucessFlag)
		printf("\nPing end, you have got %.0f records!\n",PacketNum);
	 
	else
		printf("Ping end, no record!");	
    FreeRes();
    getchar();
    getch();
}
