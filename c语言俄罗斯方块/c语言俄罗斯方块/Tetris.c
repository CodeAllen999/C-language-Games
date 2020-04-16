#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

/* �ܵ�����Ķ��� */
HANDLE hStdOutput = INVALID_HANDLE_VALUE;
HANDLE hStdError = INVALID_HANDLE_VALUE;

const WORD COLOR_A = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY; /* �˶��е���ɫ */
const WORD COLOR_B = FOREGROUND_GREEN; 									   /* �̶���������ɫ */
const WORD COLOR_C = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;      /* �հ״�����ɫ */
              
bool voice = true;  /* �������� */
int  score = 0;     /* �÷� */
int  level = 0;     /* �ȼ� */
char data[19][11] = { 0 };   	   /* ��Ϸ���ڵ�״̬ */
int  next = -1;  			 	   /* ��¼��һ��ͼ�ε������Ϣ */
int  x = 4, y = -2, c = -1, z = 0; /* x����,����,��ǰ����,���� */

/* ����ʼΪ�����ʼ�� */
bool Open( void )
{
    hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    hStdError  = GetStdHandle( STD_ERROR_HANDLE );
    return INVALID_HANDLE_VALUE!=hStdOutput && INVALID_HANDLE_VALUE!=hStdError;
}

/* ���ñ��� */
bool SetTitle( char* title ) 
{
    return TRUE==SetConsoleTitle(title);
}

/* ȥ����� */
bool RemoveCursor( void ) 
{
    CONSOLE_CURSOR_INFO cci; /* �����Ϣ */
	/* ��׼��������ȡ��Ϣ����ͷ��ش��� */
    if( !GetConsoleCursorInfo( hStdOutput, &cci ) ) 
    {
        return false;
    }
    cci.bVisible = false;
	/* ��׼������������Ϣ����ͷ��ش��� */
    if( !SetConsoleCursorInfo( hStdOutput, &cci ) ) 
    {
        return false;
    }
	/* ������������ȡ��Ϣ����ͷ��ش��� */
    if( !GetConsoleCursorInfo( hStdError, &cci ) ) 
    {
        return false;
    }
    cci.bVisible = false;
	/* ����������������Ϣ����ͷ��ش��� */
    if( !SetConsoleCursorInfo( hStdError, &cci ) ) 
    {
        return false;
    }
    return true;
}

 /* ���ô���ߴ� */
bool SetWindowRect( short x, short y )
{
	/* ��������ȡ��console����Ĵ��ڴ�С�Ľṹ */
	SMALL_RECT wrt = { 0, 0, x, y };
	/* ��׼�������ʧ�� */
    if( !SetConsoleWindowInfo( hStdOutput, TRUE, &wrt ) ) 
    {
        return false;
    }
	/* �����������ʧ�� */
    if( !SetConsoleWindowInfo( hStdError, TRUE, &wrt ) ) 
    {
        return false;
    }
    return true;
}

/* ���û���ߴ� */
bool SetBufSize( short x, short y ) 
{
	/* �������ڻ�ȡ����ṹ�� */
    COORD coord = { x, y };
	/* ���ñ�׼���ʧ�� */
    if( !SetConsoleScreenBufferSize( hStdOutput, coord ) ) 
    {
        return false;
    }
	/* ���ô������ʧ�� */
    if( !SetConsoleScreenBufferSize( hStdError, coord ) ) 
    {
        return false;
    }
    return true;
}

/* �ƶ���� */
bool GotoXY( short x, short y )
{
	/* �������ڻ�ȡ����ṹ�� */
    COORD coord = { x, y };
	/* ���ñ�׼������λ��ʧ�� */
    if( !SetConsoleCursorPosition( hStdOutput, coord ) ) 
    {
        return false;
    }
	/* ���ô���������λ��ʧ�� */
    if( !SetConsoleCursorPosition( hStdError, coord ) ) 
    {
        return false;
    }
    return true;
}

/* ����ǰ��ɫ/����ɫ */
bool SetColor( WORD color ) 
{
	/* ������ɫ��׼���ʧ�� */
    if( !SetConsoleTextAttribute( hStdOutput, color ) ) 
    {
        return false;
    }
	/* ������ɫ�������ʧ�� */
    if( !SetConsoleTextAttribute( hStdError, color ) ) 
    {
        return false;
    }
    return true;
}

/* ����ַ��� */
bool OutputString( const char* pstr, size_t len ) 
{
	/* 32bit �޷������� */
    DWORD n = 0;
	/* ���������̨ */
    return TRUE == WriteConsole( hStdOutput, pstr, len?len:strlen(pstr), &n, NULL );
}

/* ����ַ��� */
bool OutputStringNoMove( short x, short y, const char* pstr, size_t len) 
{
	/* �������ڻ�ȡ����ṹ�� */
    COORD coord = { x, y };
	/* 32bit �޷������� */
    DWORD n = 0;
    return TRUE == WriteConsoleOutputCharacter( hStdOutput, pstr, len?len:strlen(pstr), coord, &n );
}

/* ���ڽ�����ʾ */
/* ����11*19����Ϸ���� */
const char bg[] =
"��������������������������            "
"�������������������������� ������ ��  "
"�������������������������� Begin      "
"�������������������������� Voice = Yes"
"�������������������������� Sleep      "
"�������������������������� Quit       "
"��������������������������            "
"��������������������������            "
"�������������������������� �Σţأ�   "
"��������������������������������������"
"��������������������������������������"
"��������������������������������������"
"��������������������������������������"
"�������������������������� �̣ţ֣ţ� "
"��������������������������������������"
"���������������������������� 0      ��"
"��������������������������������������"
"�������������������������� �ӣãϣң� "
"��������������������������������������"
"���������������������������� 00000  ��"
"��������������������������������������";


/* ����ͼ�εĸ������ */
/* ��һάΪͼ�����࣬�ڶ�άΪͼ�εķ�������άΪͼ�ε�4*4����䷽ʽ */
const char bk[7][4][4][4] =
{
    {
        { { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
        { { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
        { { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } },
        { { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
        { { 1,1,1,0 },{ 1,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,0,0,0 } },
        { { 0,0,1,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
        { { 1,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,1,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 0,1,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
        { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
        { { 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 0,1,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
        { { 1,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
        { { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } },
        { { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
        { { 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } }
    }
};

/* ���������������� */
void VoiceBeep( void )
{
    if( voice )       /* ������������� */
    Beep( 1760, 10 ); /* ����ϵͳ���� */
}

/* ���Ƶ÷� */
void DrawScoreLevel( void )
{
    char tmp[6];
    /* ����÷� */
    sprintf( tmp, "%05d", score );
    OutputStringNoMove( 31, 19, tmp, 5 );

	/* ����ȼ� */
    sprintf( tmp, "%1d", level );
    OutputStringNoMove( 35, 15, tmp, 1 );
}

/* ���������Ŀ��� */
void DrawVoice( void )
{
    OutputStringNoMove( 35, 3, voice?"Yes":"No ", 0 );
}

/* ���� "next��" �е�ͼ�� */
void DrawNext( void )
{
    int i, j; 
	/* next����2*4�ĸ�����ɣ�����bk��ÿ��ͼ�εĵ�һ����״ */
    for( i=0; i<2; ++i )
    {
        for( j=0; j<4; ++j )
        {
            OutputStringNoMove( 28+j*2, 10+i, bk[next][0][i][j]== 0?"  ":"��", 2 );
        }
    }
}

/* ��Ϸ���� */
void DrawOver( void )
{
    OutputStringNoMove( 28, 10, "�ǣ��ͣ�", 0 );
    OutputStringNoMove( 28, 11, "�ϣ֣ţ�", 0 );
}

/* ����ͼ�� */
void Draw( WORD color )
{
    int i, j;
    for( i = 0; i < 4; ++i )
    {
    	/* �ж��Ƿ���Ƴ��� */
        if( (y + i < 0) || (y + i >= 19) ) 
        {
            continue;
        }
        for( j = 0; j < 4; ++j )
        {
            if( bk[c][z][i][j] == 1 )
            {
                SetColor( color );		   /* ������ɫ */
                GotoXY( 2+x*2+j*2, 1+y+i );/* ���������λ��� */
                OutputString( "��", 2 );
            }
        }
    }
}

/* �жϸ�����x,y,c,z�Ƿ���� */
bool IsFit( int x, int y, int c, int z ) 
{
    int i, j;
    for( i=0; i<4; ++i )
    {
        for( j=0; j<4; ++j )
        {
            if( bk[c][z][i][j]==1 )
            {
            	/* ���� */
                if( y+i < 0 ) 
                {
                    continue;
                }
                if( y+i>=19 || x+j<0 || x+j>=11 || data[y+i][x+j]==1 ) 
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/* ���� */
void RemoveRow( void )
{
    char FULLLINE[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int  linecount = 0;
    int  _score = 0; /* �ӷ� */
    int i, m, n;
	/* ���������ڶ�����һ�飬���ϵ����������� */
    for( i=0; i<19; ++i )
    {
    	/* �ҵ�һ������ */
        if( 0 == memcmp( data[i], FULLLINE, 11 ) )
        {
            ++linecount;
            for( m=0; m<11; ++m )
            {
            	/* ������֮������������ */
                for( n=i; n>1; --n )
                {
                    data[n][m] = data[n-1][m];
                    SetColor( data[n][m]==1?COLOR_B:COLOR_C );
                    GotoXY( 2+m*2, 1+n );
                    OutputString( "��", 2 );
                }
                data[0][m] = 0;/* �޸ĸ��еļ�¼Ϊ�� */
                OutputStringNoMove( 2+m*2, 1, "��", 2 );/* �ָ����� */
            }
        }
    }
	/* ������ɺ�ָ���Ϸ���ڵļ�¼ */
    char data[19][11] = { 0 };
	
	/* ���û������ */
    if( linecount == 0 ) 
    {
        return;
    }

	/* �÷ֵַȼ� */
    switch( linecount )
    {
        case 1: _score = 100; break;
        case 2: _score = 300; break;
        case 3: _score = 700; break;
        case 4: _score = 1500;break;
    }
	/* ���ӷּ����ܷ� */
    score += _score;
	/* �÷�����Ϊ99999 */
    if( score > 99999 ) 
    {
        score = 99999;
    }
	/* �ȼ�Ϊ�÷ֳ���10000���������Ϊ9�� */
    level = score/10000;
	/* ���Ƶ÷ֺ͵ȼ� */
    DrawScoreLevel();
}

/* ��ʱ�뷭ת */
void MoveTrans( void ) 
{
	/* �жϷ�ת���Ƿ��ʺϴ��� */
    if( IsFit( x, y, c, (z+1)%4 ) )
    {
    	/* �������� */
        VoiceBeep();
		/* ���Ʊ���ɫ */
        Draw( COLOR_C );
		/* ���淽�鷽��ı仯 */
        z = (z + 1) % 4;
		/* ���Ʒ�����ɫ */
        Draw( COLOR_A );
    }
}

/* ������ */
void MoveLeft( void ) 
{
	/* �жϷ�ת���Ƿ��ʺϴ��� */
    if( IsFit( x-1, y, c, z ) )
    {
    	/* �������� */
        VoiceBeep();
		/* ���Ʊ���ɫ */
        Draw( COLOR_C );
		/* �������һ */
        --x;
		/* ���Ʒ�����ɫ */
        Draw( COLOR_A );
    }
}

/* ������ */
void MoveRight( void ) 
{
	/* �жϷ�ת���Ƿ��ʺϴ��� */
    if( IsFit( x+1, y, c, z ) )
    {
    	/* �������� */
        VoiceBeep();
		/* ���Ʊ���ɫ */
        Draw( COLOR_C );
		/* �������һ */
        ++x;
		/* ���Ʒ�����ɫ */
        Draw( COLOR_A );
    }
}

/* ������ */
void MoveDown( void ) 
{
    int i, j;
	/* �ж����ƺ��Ƿ��ʺϴ��� */
    if( IsFit( x, y+1, c, z ) )
    {
    	/* �������� */
        VoiceBeep();
		/* ���Ʊ���ɫ */
        Draw( COLOR_C );
		/* �������һ */
        ++y;
		/* ���Ʒ�����ɫ */
        Draw( COLOR_A );
    }
	/* ���鴥�� */
    else if( y != -2 ) 
    {
    	/* ���Ʒ������ɫΪ��ɫ */
        Draw( COLOR_B );
		/* ��¼�������ڵ���Ϣ */
        for( i=0; i<4; ++i )
        {
            if( y+i<0 ) 
            {
                continue;
            }
            for( j=0; j<4; ++j )
            {
                if( bk[c][z][i][j] == 1 )
                {
                    data[y+i][x+j] = 1;
                }
            }
        }
		/* ����һ�������һ�����к��� */
        RemoveRow();
		/* ����x��y������Ϊ���鿪ʼ���ֵĵط���ͬʱ���÷�������� */
        x=4, y=-2, c=next, z=0;
		/* �������0~6 */
        next = rand()%7;
		/* ���Ȼ���next��ʾ���ڵ�ͼ�� */
        DrawNext();
    }
	/* ��Ϸ���� */
    else 
    {
    	/* ���ƽ���������Ϣ */
        DrawOver();
    }
}

/* ���ܼ���������Ϣ���� */
void MessageDeal( void )
{
    int cycle = 10 - level;
    int i;
    for( ; ; )
    {
        for( i=0; i<cycle; ++i )
        {
            if( _kbhit() )
            {
                switch( _getch() )
                {
                    case 'Q':
                    case 'q': /* �˳� */
                        return;
                        break;
                    case 'S': /* ��ͣ */
                    case 's':
                        for( ; ; )
                        {
                            switch( _getch() )
                            {
                                case 'Q':
                                case 'q': /* �˳� */
                                    return;
                                case 'V': /* ���� */
                                case 'v':
                                    voice = !voice;/* �ı��������� */
                                    DrawVoice();   /* ������������ͼ�� */
                                    break;
                                case 'S':
                                case 's':
                                    goto LABLE_CONTINUE;
                                    break;
                            }
                        }
                        LABLE_CONTINUE:
                        break;
                    case 'V': /* ���� */
                    case 'v':
                        voice = !voice;
                        DrawVoice();
                        break;
                    case 0xe0: /* ������ �� */
                        switch( _getch() )
                        {
                            case 0x4B: /* �� */
                                MoveLeft();
                                break;
                            case 0x50: /*  �� */
                                MoveDown();
                                break;
                            case 0x4d: /*  �� */
                                MoveRight();
                                break; /* �� ���� */
                            case 0x48:
                                MoveTrans();
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
			/* ����������ͼ�ε�ʱ�� */
            Sleep( 55 );
        }
        MoveDown();
    }
}

int main()
{
    char c;
    Open();
    /* ���ñ��� */
    SetTitle( "����˹���� made by ������" );
    /* ȥ����� */
    RemoveCursor();
    /* ���ô���ߴ� */
    SetWindowRect( 38-1, 21-1 );
    /* ���û���ߴ� */
    SetBufSize( 38, 21 );
    /* ��������ַ� */
    OutputStringNoMove( 0,0,bg,0 );
    /* ʹ��ϵͳʱ������������� */
    srand( time(0) );
	/* ����ͼ������������ */
    next = rand()%7;
	/* ����next���� */
    DrawNext();
	/* ��ʼ Begin */
    for( c = (char)_getch(); (c != 'B') &&(c != 'b'); c = (char)_getch() ) 
    {
    	/* �������� Vocie���� */
        if( (c == 'V') || (c == 'v') ) 
        {
            if( voice )
            {
                voice = false;
                OutputStringNoMove( 35, 3, "No ", 0 );
            }
            else
            {
                voice = true;
                OutputStringNoMove( 35, 3, "Yes", 0 );
            }
        }
    }
	/* �ָ���ʼ���� */
    x = 4, y = -2, c = next, z = 0;
    next = rand()%7;
    DrawNext();
	/* �����û�������Ϣ */
    MessageDeal();
    return 0;
}


