#ifndef MYHUFFMAN
#define MYHUFFMAN

#define TRUE 1
#define FALSE 0
#define MAXCODELEN 20
#define MAX_CHAR_SIZE 128
#define MAX_FILE_SIZE 10000

/*-----------it学习吧-【自学去】网站【www.itstudy8.net】站长原创,转载需注名出处，谢谢-----------*/

typedef struct HTNode
{
	char ch;
	unsigned int weigth;
	struct HTNode *parent,*lchild,*rchild;
	struct HTNode *next;
} HTNode,*HuffmanTree;

typedef struct Huffman
{
	char ch;
	int frequency;
	char *code;
} HuffmanCode[MAX_CHAR_SIZE];

void HMoveCursor( int & x,int & y );
void MoveCursor( int & x,int & y,int row );
void Menu( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] );
void InitHuffman( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] );
void KeyBoard( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] );
void ShowDocument( char EnteringData[] );
void Document( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[] );
void CountFrequency( HuffmanCode & HC,char EnteringData[] ); //统计频度
void Encoding( HuffmanTree & HT,HuffmanCode & HC,char EnteringData[]  );
void PreOrderEncode( HuffmanTree RootNode,HuffmanCode & HC,char code[],int n );
void HuffmanNodeSort( HuffmanTree & HT,int & len );

void CreateHuffmanTree( HuffmanTree & HT,HuffmanCode & HC );   //编码
void InsertNode( HuffmanTree & SecondFind,HuffmanTree & FirstFind,HuffmanTree &New );
void Decoding( HuffmanTree & HT,HuffmanCode & HC );      //译码
void PrintHuffmanCode( HuffmanCode HC );
void PrintHuffmanTree( HuffmanTree HT,HuffmanCode HC );
void PaintBiTree(HuffmanTree T,int x,int y,int t);
void PreOrderPrintTree( HuffmanTree T,int Level );

#endif