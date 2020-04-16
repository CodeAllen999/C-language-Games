/*���ؿ��ļ�*/
#pragma comment( lib, "ws2_32.lib" )
/*����ͷ�ļ�*/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

/*����ಥ����*/
#define MCASTADDR     "224.3.5.8"
#define MCASTPORT     25000
#define BUFSIZE       1024
#define MCOUNT        10

/*����㲥����*/
#define BCASTPORT     5050
#define BCOUNT        10

/*����㲥ȫ�ֱ���*/
SOCKET             socketBro;
SOCKET             socketRec;
struct sockaddr_in addrBro;
struct sockaddr_in addrRec;
BOOL               broadSendFlag;
BOOL               broadFlag;

DWORD              bCount;
DWORD              bcastAddr;
short              bPort;

/*����ಥȫ�ֱ���*/
SOCKET             socketMul;
SOCKET             sockJoin;
struct sockaddr_in addrLocal;
struct sockaddr_in addrMul;

BOOL               multiSendFlag;
BOOL               bLoopBack;    
BOOL               multiFlag;

DWORD              dwInterface;  
DWORD              dwMulticastGroup;
DWORD              mCount;         
short              mPort;           

/*�Զ��庯��*/
void initial();
void GetArgments(int argc, char **argv);

void userHelpAll();
void userHelpBro();
void userHelpMul();

void broadcastSend();
void broadcastRec();

void mulControl();
void multicastSend();
void multicastRec();

/*��ʼ��ȫ�ֱ�������*/
void initial()
{
    /*��ʼ���㲥ȫ�ֱ���*/
    bPort = BCASTPORT;
    bCount = BCOUNT;
    bcastAddr = INADDR_BROADCAST;
    broadSendFlag = FALSE;
    broadFlag = FALSE;
    multiFlag = FALSE;

    /*��ʼ���ಥȫ�ֱ���*/
    dwInterface = INADDR_ANY;
    dwMulticastGroup = inet_addr(MCASTADDR);
    mPort = MCASTPORT;
    mCount = MCOUNT;
    multiSendFlag = FALSE;
    bLoopBack = FALSE;
}

/*������ȡ����*/
void GetArgments(int argc, char **argv)
{
    int i;
    /*�����������С��2��*/
    if(argc<=1)
    {
        userHelpAll();
        return ;
    }
    /*��ȡ�㲥ѡ��*/
    if(argv[1][0]=='-'&&argv[1][1]=='b')
    {
        /*�㲥��־����Ϊ��*/
        broadFlag = TRUE;
        for(i=2; i < argc ;i++)
    	{
            if (argv[i][0] == '-')
    		{
                switch (tolower(argv[i][1]))
        		{
                    /*����Ƿ�����*/
                	case 's': 
                        broadSendFlag = TRUE;
            			break;
                    /*�㲥�ĵ�ַ*/
                	case 'h':
                        if (strlen(argv[i]) > 3)
                            bcastAddr = inet_addr(&argv[i][3]);
            			break;
                    /*�㲥�Ķ˿ں�*/
                	case 'p':
                        if (strlen(argv[i]) > 3)
                            bPort = atoi(&argv[i][3]);
            			break;
                    /*�㲥(���ջ��߷���)������*/
                	case 'n': 
                        bCount = atoi(&argv[i][3]);
            			break;
                    /*���������ʾ�û���������ֹ����*/
                	default:
        				{
                        	userHelpBro();
                        	ExitProcess(-1);
        				}
            			break;
        		}
    		}
    	}
        return ;
    }

    /*��ȡ�ಥѡ��*/
    if(argv[1][0]=='-'&&argv[1][1]=='m')
    {
        /*�ಥ��־����Ϊ��*/
        multiFlag = TRUE;
        for(i=2; i < argc ;i++)
    	{
            if (argv[i][0] == '-')
    		{
                switch (tolower(argv[i][1]))
        		{
                    /*����Ƿ�����*/
                	case 's': 
                        multiSendFlag = TRUE;
            			break;
                    /*�ಥ��ַ*/
                	case 'h': 
                        if (strlen(argv[i]) > 3)
                            dwMulticastGroup = inet_addr(&argv[i][3]);
            			break;
                    /*���ؽӿڵ�ַ*/
                	case 'i': 
                        if (strlen(argv[i]) > 3)
                            dwInterface = inet_addr(&argv[i][3]);
            			break;
                    /*�ಥ�˿ں�*/
                	case 'p': 
                        if (strlen(argv[i]) > 3)
                            mPort = atoi(&argv[i][3]);
            			break;
                    /*���ر�־����Ϊ��*/
                	case 'l': 
                        bLoopBack = TRUE;
            			break;
                    /*����(����)������*/
                	case 'n':
                        mCount = atoi(&argv[i][3]);
            			break;
                    /*�����������ʾ�û���������ֹ����*/
                	default:
                    	userHelpMul();
            			break;
        		}
    		}
    	}
    
    }
    return;
}

/*ȫ���û���������*/
void userHelpAll()
{
    printf("Please choose broadcast[-b] or multicast[-m] !\n"); 
    printf("userHelpAll: -b [-s][p][-h][-n] | -m[-s][-h][-p][-i][-l][-n]\n");
    userHelpBro();
    userHelpMul();
}

/*�㲥�û���������*/
void userHelpBro()
{
    printf("Broadcast: -b -s:str -p:int -h:str -n:int\n");
    printf("           -b     Start the broadcast program.\n");
    printf("           -s     Act as server (send data); otherwise\n");
    printf("                  receive data. Default is receiver.\n");
    printf("           -p:int Port number to use\n ");
    printf("                  The default port is 5050.\n");
    printf("           -h:str The decimal broadcast IP address.\n");
    printf("           -n:int The Number of messages to send/receive.\n");
    printf("                  The default number is 10.\n");
}

/*�ಥ�û���������*/
void userHelpMul()
{
    printf("Multicast: -m -s -h:str -p:int -i:str -l -n:int\n");
    printf("           -m     Start the multicast program.\n");
    printf("           -s      Act as server (send data); otherwise\n");
    printf("                   receive data. Default is receiver.\n");
    printf("           -h:str  The decimal multicast IP address to join\n");
    printf("                   The default group is: %s\n", MCASTADDR);
    printf("           -p:int  Port number to use\n");
    printf("                   The default port is: %d\n", MCASTPORT);
    printf("           -i:str  Local interface to bind to; by default \n");
    printf("                   use INADDRY_ANY\n");
    printf("           -l      Disable loopback\n");
    printf("           -n:int  Number of messages to send/receive\n");
    ExitProcess(-1);
}

/*�㲥��Ϣ���ͺ���*/
void broadcastSend()
{
    /*���ù㲥����Ϣ*/
    char *smsg="The message received is from sender!";
    BOOL opt=TRUE;
    int nlen=sizeof(addrBro);
    int ret;
    DWORD i=0;
    
    /*����UDP�׽���*/
    socketBro=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
    /*�������ʧ��*/
    if(socketBro==INVALID_SOCKET)
    {
        printf("Create socket failed:%d\n",WSAGetLastError());
        WSACleanup();
        return;
    }
    
    /*���ù㲥��ַ����ѡ��*/
    addrBro.sin_family=AF_INET;
    addrBro.sin_addr.s_addr=bcastAddr;
    addrBro.sin_port=htons(bPort);
    
    /*���ø��׽���Ϊ�㲥����*/
    if (setsockopt(socketBro,SOL_SOCKET,SO_BROADCAST,(char FAR *)&opt,
                                        		sizeof(opt))==SOCKET_ERROR)
    /*�������ʧ��*/
    {
        printf("setsockopt failed:%d",WSAGetLastError());
        closesocket(socketBro);
        WSACleanup();
        return;
    }
    /*ѭ��������Ϣ*/
    while(i<bCount)
    {
        /*�ӳ�1��*/
        Sleep(1000);
        /*�ӹ㲥��ַ������Ϣ*/
        ret=sendto(socketBro,smsg,256,0,(struct sockaddr*)&addrBro,nlen);
        /*�������ʧ��*/
        if(ret==SOCKET_ERROR)
            printf("Send failed:%d",WSAGetLastError());
        /*������ͳɹ�*/
        else
        {		
            printf("Send message %d!\n",i);	
    	}
        i++;
    }
    /*������Ϻ�ر��׽��֡��ͷ�ռ����Դ*/
    closesocket(socketBro);
    WSACleanup();
}

/*�㲥��Ϣ���պ���*/
void broadcastRec()
{   
    BOOL optval = TRUE;
    int addrBroLen;
    char buf[256];
    DWORD i=0;
    /*�õ�ַ�������׽���*/
    addrRec.sin_family=AF_INET;
    addrRec.sin_addr.s_addr=0;
    addrRec.sin_port=htons(bPort);

    /*�õ�ַ����������·�Ϲ㲥����Ϣ*/
    addrBro.sin_family=AF_INET;
    addrBro.sin_addr.s_addr=bcastAddr;
    addrBro.sin_port=htons(bPort);
    
    addrBroLen=sizeof(addrBro);
    //����UDP�׽���
    socketRec=socket(AF_INET,SOCK_DGRAM,0);
    /*�������ʧ��*/
    if(socketRec==INVALID_SOCKET)
    {
        printf("Create socket error:%d",WSAGetLastError());
        WSACleanup();
        return;
    }

    /*���ø��׽���Ϊ����������*/
    if(setsockopt(socketRec,SOL_SOCKET,SO_REUSEADDR,(char FAR *)&optval,
                                                			sizeof(optval))==SOCKET_ERROR)
    /*�������ʧ��*/
    {
        printf("setsockopt failed:%d",WSAGetLastError());
        closesocket(socketRec);
        WSACleanup();
        return;
    }
    /*���׽��ֺ͵�ַ*/
    if(bind(socketRec,(struct sockaddr *)&addrRec,
                                sizeof(struct sockaddr_in))==SOCKET_ERROR)
    /*�����ʧ��*/
    {
        printf("bind failed with: %d\n", WSAGetLastError());
        closesocket(socketRec);
        WSACleanup();
        return ;
    }
    /*�ӹ㲥��ַ������Ϣ*/
    while(i<bCount)
    {
        recvfrom(socketRec,buf,256,0,(struct sockaddr FAR *)&addrBro,(int FAR *)&addrBroLen);
        /*�ӳ�2����*/
        Sleep(2000);
        /*������յ�����������Ϣ*/
        printf("%s\n",buf);
        /*���������*/
        ZeroMemory(buf,256);
        i++;
    }
    /*������Ϻ�ر��׽��֡��ͷ�ռ����Դ*/
    closesocket(socketRec);
    WSACleanup();
}

/*�ಥ���ƺ���*/
void mulControl()
{
    int optval; 
    /*����UDP�׽��֣����ڶಥ*/
    if ((socketMul = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0,
                  WSA_FLAG_MULTIPOINT_C_LEAF 
                  | WSA_FLAG_MULTIPOINT_D_LEAF 
                  | WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
        printf("socket failed with: %d\n", WSAGetLastError());
        WSACleanup();
        return ;
    }
    
    /*���ñ��ؽӿڵ�ַ*/
    addrLocal.sin_family = AF_INET;
    addrLocal.sin_port = htons(mPort);
    addrLocal.sin_addr.s_addr = dwInterface;
    
    /*��UDP�׽��ְ󶨵����ص�ַ��*/
    if (bind(socketMul, (struct sockaddr *)&addrLocal, 
                                    sizeof(addrLocal)) == SOCKET_ERROR)
    /*�����ʧ��*/
    {
        printf("bind failed with: %d\n", WSAGetLastError());
        closesocket(socketMul);
        WSACleanup();
        return ;
    }

    /*���öಥ��ַ����ѡ��*/
    addrMul.sin_family      = AF_INET;
    addrMul.sin_port        = htons(mPort);
    addrMul.sin_addr.s_addr = dwMulticastGroup;

    /*��������TTLֵ*/
    optval = 8;
    /*���öಥ���ݵ�TTL(����ʱ��)ֵ��Ĭ������£�TTLֵ��1*/
    if (setsockopt(socketMul, IPPROTO_IP, IP_MULTICAST_TTL, 
        (char *)&optval, sizeof(int)) == SOCKET_ERROR)
    /*�������ʧ��*/
    {
        printf("setsockopt(IP_MULTICAST_TTL) failed: %d\n",WSAGetLastError());
        closesocket(socketMul);
        WSACleanup();
        return ;
    }

    /*���ָ���˷���ѡ��*/
    if (bLoopBack)
    {
        /*���÷���ѡ��Ϊ�٣���ֹ�����͵����ݷ��������ؽӿ�*/
        optval = 0;
        if (setsockopt(socketMul, IPPROTO_IP, IP_MULTICAST_LOOP,
            (char *)&optval, sizeof(optval)) == SOCKET_ERROR)
        /*�������ʧ��*/
    	{
            printf("setsockopt(IP_MULTICAST_LOOP) failed: %d\n",
                WSAGetLastError());
            closesocket(socketMul);
            WSACleanup();
            return ;
        }
    }
    
    /*����ಥ��*/
    if ((sockJoin = WSAJoinLeaf(socketMul, (SOCKADDR *)&addrMul, 
                             sizeof(addrMul), NULL, NULL, NULL, NULL, 
                             JL_BOTH)) == INVALID_SOCKET)
    /*������벻�ɹ�*/
    {
        printf("WSAJoinLeaf() failed: %d\n", WSAGetLastError());
        closesocket(socketMul);
        WSACleanup();
        return ;
    }
}

/*�ಥ��Ϣ���ͺ���*/
void multicastSend()
{
    
    TCHAR  sendbuf[BUFSIZE];
    DWORD i;
    int ret;

    mulControl();
    /*����mCount����Ϣ*/
    for(i = 0; i < mCount; i++)
    {
        /*�������͵���Ϣд�뷢�ͻ�����*/
        sprintf(sendbuf, "server 1: This is a test: %d", i);
        ret=sendto(socketMul, (char *)sendbuf, strlen(sendbuf), 0,
                (struct sockaddr *)&addrMul, sizeof(addrMul));
        /*�������ʧ��*/
        if(ret==SOCKET_ERROR)
        {
            printf("sendto failed with: %d\n",WSAGetLastError());
            closesocket(sockJoin);
            closesocket(socketMul);
            WSACleanup();
            return ;
        }
        /*������ͳɹ�*/
        else
            printf("Send message %d\n",i);
         Sleep(500);
     }
    /*�ر��׽��֡��ͷ�ռ����Դ*/
    closesocket(socketMul);
    WSACleanup();
}

/*�ಥ��Ϣ���պ���*/
void multicastRec()
{
    DWORD i;
    struct sockaddr_in  from;
    TCHAR recvbuf[BUFSIZE];
    int ret;
    int len = sizeof(struct sockaddr_in);

    mulControl();
    /*����mCount����Ϣ*/
    for(i = 0; i < mCount; i++)
    {
        /*�����յ���Ϣд����ջ�����*/
        if ((ret = recvfrom(socketMul, recvbuf, BUFSIZE, 0,
                (struct sockaddr *)&from, &len)) == SOCKET_ERROR)
        /*������ղ��ɹ�*/
    	{
            printf("recvfrom failed with: %d\n",WSAGetLastError());
            closesocket(sockJoin);
            closesocket(socketMul);
            WSACleanup();
             return ;
        }
        /*���ճɹ���������յ���Ϣ*/
        recvbuf[ret] = 0;
        printf("RECV: '%s' from <%s>\n", recvbuf,inet_ntoa(from.sin_addr));
     }
    /*�ر��׽��֡��ͷ�ռ����Դ*/
    closesocket(socketMul);
    WSACleanup();
}

/*������*/
int main(int argc, char **argv)
{
    WSADATA wsd;

    initial();
    GetArgments(argc, argv);

    /*��ʼ��Winsock*/
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        printf("WSAStartup() failed\n");
        return -1;
    }

    /*�����ִ�й㲥����*/
    if(broadFlag)
    {
        /*�Է�������ݷ�����Ϣ*/
        if(broadSendFlag)
    	{
            broadcastSend();
            return 0;
    	}
        /*�Խ�������ݽ�����Ϣ*/
        else
    	{
            broadcastRec();
            return 0;
    	}
    }

    /*�����ִ�жಥ����*/
    if(multiFlag)
    {
        /*�Է�������ݷ�����Ϣ*/
        if(multiSendFlag) 
    	{
            multicastSend();
            return 0;
        }
        /*�Խ�������ݽ�����Ϣ*/
        else    
    	{
            multicastRec();
            return 0;
    	}
    }
    return 0;
}




