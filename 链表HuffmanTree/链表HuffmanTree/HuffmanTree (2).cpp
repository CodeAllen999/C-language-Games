#include"OtherFuntion.h"
#include"HuffmanTree.h"
#include<graphics.h>
/*----------------Ҫ�ɹ����б�������Ҫ�������� graphics.h ���ͷ�ļ������޷�����----------*/

/*-----------itѧϰ��-����ѧȥ����վ��www.itstudy8.net��վ��ԭ��,ת����ע��������лл-----------*/

void MoveCursor( int & x,int & y,int row )
{
	char ch;
	int X = x, Y = y;
	HideCursor();
	gotoxy( x,y );
	printf("��");
	while( 1 )
	{
		ch = getch();
		switch( ch )
		{
		case 'S':
		case 's':  {
						gotoxy(x,y);
						printf("  ");
						y = y + 2;
						if( y > ( 2*(row-1) ) + Y )
							y = y - 2*row;
						gotoxy( x,y );
						printf("��");
						break;
				   } 
		case 'W':
		case 'w':  {
						gotoxy(x,y);
						printf("  ");
						y = y - 2;
						if( y < Y )
							y = Y + 2*(row-1);
						gotoxy( x,y );
						printf("��");
						break;
				   }
		case '\r': {
						return;
				   }
		}
	}
}

void HMoveCursor( int & x,int & y )
{
	char ch;
	HideCursor();
	gotoxy( x,y );
	printf("��");
	while( 1 )
	{
		ch = getch();
		switch( ch )
		{
		case 'A':
		case 'a':  {
						gotoxy(x,y);
						printf("  ");
						x = x-11;
						if( x < 12 )
							x = 23;
						gotoxy( x,y );
						printf("��");
						break;
				   } 
		case 'D':
		case 'd':  {
						gotoxy(x,y);
						printf("  ");
						x = x+11;
						if( x > 23 )
							x = 12;
						gotoxy( x,y );
						printf("��");
						break;
				   }
		case '\r': {
						return;
				   }
		}
	}
}

void Menu( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] )
{
	int x = 15,y = 8;
	gotoxy(2,2);
	printf("\n\t���� W,S ���ƶ����,��Enter���롣��www.itstudy8.net��վ��ԭ��\n");
	HideCursor();
	DrawTable( 17,16,12,5 );
	gotoxy(17,8 );
	printf("1.��ʼ����������");
	gotoxy(17,10 );
	printf("2.����");
	gotoxy(17,12 );
	printf("3.����");
	gotoxy(17,14 );
	printf("4.��ӡ����������");
	gotoxy(17,16 );
	printf("5.��ӡ��������");
	gotoxy(17,18 );
	printf("6.�˳�ϵͳ");
	MoveCursor( x,y,6 );
	
	switch( y )
	{
	case 8:   InitHuffman( HT,HC,EnteringData );          break;
	case 10:  Encoding( HT,HC,EnteringData );             break;
	case 12:  Decoding( HT,HC );                          break;
	case 14:  PrintHuffmanCode( HC );                     break;
	case 16:  PrintHuffmanTree( HT,HC );                  break;
	case 18:  gotoxy(0,23);                               exit( 1 ); 
	}
}

void InitHuffman( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] )
{
	int x = 15,y = 2;
	system("cls");
	DrawTable( 7,16,12,1 );
	gotoxy(17,2 );
	printf("1.����");
	gotoxy(17,4 );
	printf("2.�ĵ�");
	gotoxy(17,6 );
	printf("3.�������˵�");
	MoveCursor( x,y,3 );

	switch( y )
	{
	case 2:  KeyBoard( HT,HC,EnteringData );     break;
	case 4:  Document( HT,HC,EnteringData );     break;
	case 6:  system("cls");                      return; 
	}
}

void KeyBoard( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] )
{
	gotoxy(0,8);
	HideCursor1();
	printf("�����ı�����(��#����)��\n");
	printf("=====================================================\n");

	int i = 0;
	char ch = getchar(),flag;
	while( ch != '#' )
	{
		EnteringData[i] = ch;
		++i;
		ch = getchar();
	}
	EnteringData[i] = '\0';
	CountFrequency( HC,EnteringData );   //ͳ��Ƶ��

	printf("\n�Ƿ�Ҫ�����ı�? Y/N? : ");
	getchar();
	flag = getchar();
	if( flag == 'Y' || flag == 'y' )
	{
		FILE *fp = fopen("document.txt","wb");
		if( ! fp )
		{
			MessageBox(NULL,"�ļ���ʧ��!","��ʾ",MB_OK);
			system("cls");
			return;
		}
		i = 0;
		while( EnteringData[i] != '\0' )
		{
			ch = EnteringData[i];
			fputc( ch,fp );
			++i;
		}
		fclose( fp );
	}

	printf("\n�Ƿ���ʾ�ı�? Y/N? ��");
	getchar();
	flag = getchar();
	if( flag == 'Y' || flag == 'y' )
	{
		ShowDocument( EnteringData );
	}
	else
	{
		system("cls");
		return;
	}
}

void Document( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] )
{
	char path[30];
	int i = 0;

	gotoxy(0,9);
	HideCursor1();
	printf("�������ĵ�·��(�� C:\\english.txt) : ");
	gets( path );
	FILE *fp = fopen(path,"rb");
	if( ! fp )
	{
		MessageBox(NULL,"�ļ���ʧ��!","��ʾ",MB_OK);
		system("cls");
		return;
	}
	while( ! feof( fp ) )
	{
		EnteringData[i] = fgetc( fp );
		++i;
	}
	EnteringData[i] = '\0';
	fclose( fp );

	ShowDocument( EnteringData );
	CountFrequency( HC,EnteringData );
}

void ShowDocument( char EnteringData[] )
{
	system("cls");
	gotoxy(7,0);
	printf("�ı�����");
	DrawTable(23,20,0,1);
	DrawTable(23,20,20,1);
	gotoxy(1,2);

	int x = 1,y = 24;
	int i = 0,row = 2,flag = 0;
	while( EnteringData[i] != '\0' )
	{
		if( EnteringData[i] == '\n' )
		{
			row = row + 2;
			gotoxy(x,row);
			flag = 0;
			++i;
		}
		printf("%c",EnteringData[i]);
		++flag;
		if( flag == 36 )
		{
			row = row + 2;
			gotoxy(x,row);
			flag = 0;
		}
		++i;
		if( x == 21 && row > 20 )
		{
			printf("......");
			break;
		}
		if( row > 20 )
		{
			x = 21;
			row = 0;
			flag = 0;
		}
	}

	x = 12,y = 24;
	gotoxy(13,24);
	printf("1.����\t\t2.�˳�");
	HMoveCursor(x,y);

	switch( x )
	{
	case 12:  system("cls");   return;
	case 23:  gotoxy(0,25);    exit( 1 );
	}
}

void CountFrequency( HuffmanCode & HC,char EnteringData[] )
{
	int i = 0;
	for( i = 0; i < MAX_CHAR_SIZE; ++i )
	{
		HC[i].ch = i;
		HC[i].frequency = 0;
		HC[i].code = NULL;
	}
	for( i = 0; EnteringData[i] != '\0'; ++i )
	{
		int Ascii = EnteringData[i];
		HC[Ascii].frequency++;
	}

	FILE *fp = fopen("HuffmanTree.txt","wb");
	if( ! fp )
	{
		MessageBox(NULL,"HuffmanTree�ļ���ʧ��!","��ʾ",MB_ICONERROR | MB_OK);
		system("cls");
		return;
	}
	else
	{
		for( i = 0; i < MAX_CHAR_SIZE; ++i )
		{
			fwrite( &HC[i],sizeof( struct Huffman ),1,fp );
		}
		fclose( fp );
	}
}

void Encoding( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[]  )  //����
{	
	if( HC[0].ch == NULL )
	{
		char code[MAXCODELEN];
		CreateHuffmanTree( HT,HC );
		HuffmanTree RootNode = HT->next;
		while( RootNode->next != NULL )  //�Ҹ����
		{
			RootNode = RootNode->next;
		}
		PreOrderEncode( RootNode,HC,code,0 );  //�����������
	}
	else
	{
		MessageBox(NULL,"û���ĵ�¼��,��¼���ĵ������!","��ʾ",MB_ICONERROR | MB_OK);
		return;
	}
	int ref = MessageBox(NULL,"����ɹ�,�Ƿ�Ҫ�������������?","��ʾ",MB_ICONQUESTION | MB_YESNO);
	if( IDYES == ref )
	{
		FILE *fp = fopen("HuffmanCode.txt","wb");
		if( ! fp )
		{
			MessageBox(NULL,"�ļ���ʧ��!","��ʾ",MB_ICONERROR | MB_OK);
			system("cls");
			return;
		}
		for( int i = 0; EnteringData[i] != '\0'; ++i )
		{
			int Ascii = EnteringData[i];
			if( Ascii < 0 )   //�������ڲ���0��128��Asciiʱ������ʵ�ֱ��룬�˳�ѭ��
				break;
			fputs( HC[Ascii].code,fp );
		}
		fclose( fp );
	}
	else
	{
		system("cls");
		return;
	}
}

void PreOrderEncode( HuffmanTree RootNode,HuffmanCode & HC,char code[],int n ) //����������룬�õݹ�ʵ��
{
	if( RootNode->lchild == NULL && RootNode->rchild == NULL )
	{
		int Ascii = RootNode->ch;
		HC[Ascii].code = ( char * )malloc( (n+1) * sizeof( char ) );
		if( ! HC[Ascii].code )
			exit( OVERFLOW );
		for( int i = 0; i < n; ++i )
		{
			HC[Ascii].code[i] = code[i];
		}
		HC[Ascii].code[i] = '\0';
		return;
	}
	if( RootNode->lchild )
	{
		code[n] = '0';
		PreOrderEncode( RootNode->lchild,HC,code,n+1 );
	}
	if( RootNode->rchild )
	{
		code[n] = '1';
		PreOrderEncode( RootNode->rchild,HC,code,n+1 );
	}
}

void CreateHuffmanTree( HuffmanTree & HT,HuffmanCode & HC )
{
	int len;
	HT = ( HuffmanTree )malloc( sizeof( HTNode ) );
	HT->next = NULL;
	HT->weigth = 0;
	HT->lchild = NULL;
	HT->rchild = NULL;
	HT->parent = NULL;
	HT->ch = NULL;

	HuffmanTree Head = HT,Next,New;
	for( int i = 0; i < MAX_CHAR_SIZE; ++i )
	{
		if( HC[i].frequency != 0 )
		{
			Next = ( HuffmanTree )malloc( sizeof( HTNode ) );
			if( ! Next )
				exit( OVERFLOW );
			Next->weigth = HC[i].frequency;
			Next->lchild = NULL;
			Next->rchild = NULL;
			Next->parent = NULL;
			Next->next = NULL;
			Next->ch = HC[i].ch;
			Head->next = Next;
			Head = Next;
		}
	}
	HuffmanNodeSort( HT,len );  //�������������

	HuffmanTree FirstFind,SecondFind;
	FirstFind = HT->next;
	SecondFind = FirstFind->next;
	for( i = 0; i < len-1; ++i )
	{
		New = ( HuffmanTree )malloc( sizeof( HTNode ) );
		if( ! New )
			exit( OVERFLOW );
		FirstFind->parent = New;
		SecondFind->parent = New;
		New->weigth = FirstFind->weigth + SecondFind->weigth;
		New->lchild = FirstFind;
		New->rchild = SecondFind;
		New->parent = NULL;
		New->next   = NULL;
		New->ch = NULL;
		InsertNode( SecondFind,FirstFind,New );  //�����½��
	}
}

void HuffmanNodeSort( HuffmanTree & HT,int & Len )  //������
{
	int len = 0;
	HuffmanTree Head = HT->next,Prior,Next;
	while( Head != NULL )
	{
		++len;
		Head = Head->next;
	}
	Len = len;

	bool exchange = TRUE;
	while( exchange )   //�������������, �����Ż����ð�������㷨
	{
		exchange = FALSE;
		Prior = HT;
		Head = HT->next;
		Next = Head->next;
		for( int i = 0; i < len-1; ++i )
		{
			if( Head->weigth > Next->weigth )
			{
				Prior->next = Next;
				Head->next = Next->next;
				Next->next = Head;
				Prior = Next;
				Next = Head->next;
				exchange = TRUE;
			}
			else
			{
				Prior = Prior->next;
				Head = Head->next;
				Next = Head->next;
			}
		}
		len--;
	}
}

void InsertNode( HuffmanTree & SecondFind,HuffmanTree & FirstFind,HuffmanTree &New )
{
	HuffmanTree Prior,Next;
	Prior = SecondFind;
	Next  = SecondFind->next;
	if( SecondFind->next == NULL )  //SecondFind ָ�������β������������½���������
	{
		SecondFind->next = New;
		return;
	}
	while( New->weigth > Next->weigth && Next->next != NULL )  //SecondFind û��ָ����β�������������
	{
		Prior = Prior->next;
		Next  = Next->next;
	}
	if( Next->next == NULL )   //ʵ������Ĳ���
	{
		Next->next = New;
	}
	else
	{
		New->next = Next;
		Prior->next = New;
	}
	FirstFind = SecondFind->next;   //First Second �ֱ�ָ�����������
	SecondFind = FirstFind->next;
}

void Decoding( HuffmanTree & HT,HuffmanCode & HC )
{
	int i = 0;
	char EnteringData[MAX_FILE_SIZE];
	HT = ( HuffmanTree )malloc( sizeof( HTNode ) );
	HT->next = NULL;
	HT->weigth = 0;
	HT->lchild = NULL;
	HT->rchild = NULL;
	HT->parent = NULL;
	HT->ch = NULL;
	
	FILE *fp = fopen("HuffmanTree.txt","rb");
	if( ! fp )
	{
		MessageBox(NULL,"�ļ���ʧ��!","��ʾ",MB_OK);
		system("cls");
		return;
	}
	else
	{
		for( int i = 0; i < MAX_CHAR_SIZE; ++i )
		{
			fread( &HC[i],sizeof( struct Huffman ),1,fp );
		}
		fclose( fp );
		CreateHuffmanTree( HT,HC );
	}

	fp = fopen("HuffmanCode.txt","rb");
	if( ! fp )
	{
		MessageBox(NULL,"�ļ���ʧ��!","����",MB_ICONERROR | MB_OK);
		system("cls");
		return;
	}
	HuffmanTree RootNode = HT->next,Decode;
	while( RootNode->next != NULL )  //�Ҹ����
	{
		RootNode = RootNode->next;
	}
	Decode = RootNode;

	gotoxy(0,23);
	while( ! feof( fp ) )  //���룬���÷ǵݹ��㷨
	{
		char ch = fgetc( fp );
		if( ch == '0' && Decode->lchild )
		{
			Decode = Decode->lchild;
		}
		if( ch == '1' && Decode->rchild )
		{
			Decode = Decode->rchild;
		}
		if( Decode->lchild == NULL && Decode->rchild == NULL )
		{
			EnteringData[i] = Decode->ch;
			++i;
			printf("%c",Decode->ch);
			Decode = RootNode;
		}
	}
	EnteringData[i] = '\0';
	fclose( fp );
	printf("\n�밴���������...\n");
	getch();

	int ref = MessageBox(NULL,"����ɹ�,�Ƿ�Ҫ������������?","��ʾ",MB_ICONQUESTION | MB_YESNO);
	if( IDYES == ref )
	{
		fp = fopen("contents.txt","wb");
		if( ! fp )
		{
			MessageBox(NULL,"�ļ���ʧ��!","��ʾ",MB_ICONERROR | MB_OK);
			system("cls");
			return;
		}
		i = 0;
		while( EnteringData[i] != '\0' )
		{
			fputc( EnteringData[i],fp );
			++i;
		}
		fclose( fp );
		system("cls");
	}
	else
	{
		system("cls");
		return;
	}
}

void PrintHuffmanCode( HuffmanCode HC )
{
	system("cls");
	printf("\t\t\t\t  �ַ�����\n");
	printf("================================================================================");
	printf("�ַ�            ���ִ���               ����������                             \n");
	printf("================================================================================");
	if( HC[0].ch == NULL )
	{
		for( int i = 31; i < MAX_CHAR_SIZE; ++i )
		{	
			if( HC[i].frequency == 0 )
				continue;
			if( HC[i].ch == ' ' )
			{
				printf("NULL\t\t%d\t\t\t%s\n",HC[i].frequency,HC[i].code);
				continue;
			}
			printf("%c\t\t%d\t\t\t%s\n",HC[i].ch,HC[i].frequency,HC[i].code);
		}
	}
	else
	{
		MessageBox(NULL,"û���ĵ�¼��,��¼���ĵ������!","��ʾ",MB_ICONERROR | MB_OK);
		system("cls");
		return;
	}
	printf("\n\n�밴���������...");
	getch();
	system("cls");
}

void PrintHuffmanTree( HuffmanTree HT,HuffmanCode HC )
{
	gotoxy(0,23);
	int n;
	printf("1.ֱ�Ӵ�ӡ��\t2.������ӡ��\n");
	scanf("%d",&n);

	if( HC[0].ch == NULL )
	{
		HuffmanTree RootNode = HT->next;
		while( RootNode->next != NULL )  //�Ҹ����
		{
			RootNode = RootNode->next;
		}
		if( n == 1 )
		{
			initgraph(1300,600);
			PaintBiTree(RootNode,630,20,300);
			outtextxy(0,500,"�밴���������...");
			getch();
			closegraph();
		}
		else if( n == 2 )
		{
			system("cls");
			PreOrderPrintTree(RootNode,1);
			printf("�밴���������...\n");
			getch();
		}
		system("cls");
	}
	else
	{
		MessageBox(NULL,"û�й�������������빹������������ӡ!","��ʾ",MB_ICONERROR | MB_OK);
		system("cls");
		return;
	}
}

void PaintBiTree(HuffmanTree T,int x,int y,int t)
{ 
	int m,n,x1,y1,x2,y2,x3,y3,x4,y4;
	char str[10];
	char c[2];
	m = (int)sqrt( 100.0*t*t / (1600+t*t) );	//x��
	n = (int)sqrt( 160000.0  / (1600+t*t) );	//y��
	x1 = x-m;
	y1 = y+n;
	x2 = x-t+m;
	y2 = y+40-n;
	x3 = x+m;
	y3 = y+n;
	x4 = x+t-m;
	y4 = y+40-n;
	if( T )
	{
		circle(x,y,10);
		if( T->lchild )
			line(x1,y1,x2,y2);
		if( T->rchild )
			line(x3,y3,x4,y4);
		itoa(T->weigth,str,10);
		outtextxy(x-5,y-8,str);
		if( T->ch != NULL )
		{
			if( T->ch == ' ' )
			{
				outtextxy(x-5,y+12," �ո�");
			}
			c[0] = T->ch;
			c[1] = '\0';
			outtextxy(x-5,y+12,c);
		}
		PaintBiTree(T->lchild,x-t,y+40,t/2);
		PaintBiTree(T->rchild,x+t,y+40,t/2);
	}
}

void PreOrderPrintTree( HuffmanTree T,int Level )
{
	if( T )
	{
		if( Level == 1 )
		{
			printf("%d\n",T->weigth);
		}
		else if( Level == 2 )
		{
			printf("����%d\n",T->weigth);
		}
		else
		{
			printf("��");
			int SpaceNum = 2*(Level-2) - 1;
			for( int i = 1; i <= SpaceNum; ++i )
			{
				if( i % 2 == 0 )
					printf("��");
				else
					printf("  ");
			}
			if( T->lchild == NULL && T->rchild == NULL )
			{
				if( T->ch == ' ' )
					printf("����%d NULL\n",T->weigth);
				else if( T->ch == '\n' )
					printf("����%d  \\n\n",T->weigth);
				else
					printf("����%d  %c\n",T->weigth,T->ch);
			}
			else
			{
				printf("����%d\n",T->weigth);
			}
		}

		if( T->lchild )
			PreOrderPrintTree(T->lchild,Level+1);
		if( T->rchild )
			PreOrderPrintTree(T->rchild,Level+1);
	}
}
