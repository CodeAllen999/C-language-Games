#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/* 【自学去】网站收集 http://www.zixue7.com */

/* 管道句柄的定义 */
HANDLE hStdOutput = INVALID_HANDLE_VALUE;
HANDLE hStdError = INVALID_HANDLE_VALUE;

const WORD COLOR_A = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY; /* 运动中的颜色 */
const WORD COLOR_B = FOREGROUND_GREEN; 									   /* 固定不动的颜色 */
const WORD COLOR_C = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;      /* 空白处的颜色 */
              
bool voice = true;  /* 背景音乐 */
int  score = 0;     /* 得分 */
int  level = 0;     /* 等级 */
char data[19][11] = { 0 };   	   /* 游戏窗口的状态 */
int  next = -1;  			 	   /* 记录下一个图形的随机信息 */
int  x = 4, y = -2, c = -1, z = 0; /* x坐标,坐标,当前方块,方向 */

/* 程序开始为句柄初始化 */
bool Open( void )
{
    hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    hStdError  = GetStdHandle( STD_ERROR_HANDLE );
    return INVALID_HANDLE_VALUE!=hStdOutput && INVALID_HANDLE_VALUE!=hStdError;
}

/* 设置标题 */
bool SetTitle( char* title ) 
{
    return TRUE==SetConsoleTitle(title);
}

/* 去处光标 */
bool RemoveCursor( void ) 
{
    CONSOLE_CURSOR_INFO cci; /* 光标信息 */
	/* 标准输出句柄获取信息出错就返回错误 */
    if( !GetConsoleCursorInfo( hStdOutput, &cci ) ) 
    {
        return false;
    }
    cci.bVisible = false;
	/* 标准输出句柄设置信息出错就返回错误 */
    if( !SetConsoleCursorInfo( hStdOutput, &cci ) ) 
    {
        return false;
    }
	/* 错误输出句柄获取信息出错就返回错误 */
    if( !GetConsoleCursorInfo( hStdError, &cci ) ) 
    {
        return false;
    }
    cci.bVisible = false;
	/* 错误输出句柄设置信息出错就返回错误 */
    if( !SetConsoleCursorInfo( hStdError, &cci ) ) 
    {
        return false;
    }
    return true;
}

 /* 设置窗体尺寸 */
bool SetWindowRect( short x, short y )
{
	/* 定义用于取得console程序的窗口大小的结构 */
	SMALL_RECT wrt = { 0, 0, x, y };
	/* 标准输出设置失败 */
    if( !SetConsoleWindowInfo( hStdOutput, TRUE, &wrt ) ) 
    {
        return false;
    }
	/* 错误输出设置失败 */
    if( !SetConsoleWindowInfo( hStdError, TRUE, &wrt ) ) 
    {
        return false;
    }
    return true;
}

/* 设置缓冲尺寸 */
bool SetBufSize( short x, short y ) 
{
	/* 定义用于获取坐标结构体 */
    COORD coord = { x, y };
	/* 设置标准输出失败 */
    if( !SetConsoleScreenBufferSize( hStdOutput, coord ) ) 
    {
        return false;
    }
	/* 设置错误输出失败 */
    if( !SetConsoleScreenBufferSize( hStdError, coord ) ) 
    {
        return false;
    }
    return true;
}

/* 移动光标 */
bool GotoXY( short x, short y )
{
	/* 定义用于获取坐标结构体 */
    COORD coord = { x, y };
	/* 设置标准输出鼠标位置失败 */
    if( !SetConsoleCursorPosition( hStdOutput, coord ) ) 
    {
        return false;
    }
	/* 设置错误输出鼠标位置失败 */
    if( !SetConsoleCursorPosition( hStdError, coord ) ) 
    {
        return false;
    }
    return true;
}

/* 设置前景色/背景色 */
bool SetColor( WORD color ) 
{
	/* 背景颜色标准输出失败 */
    if( !SetConsoleTextAttribute( hStdOutput, color ) ) 
    {
        return false;
    }
	/* 背景颜色错误输出失败 */
    if( !SetConsoleTextAttribute( hStdError, color ) ) 
    {
        return false;
    }
    return true;
}

/* 输出字符串 */
bool OutputString( const char* pstr, size_t len ) 
{
	/* 32bit 无符号整数 */
    DWORD n = 0;
	/* 输出到控制台 */
    return TRUE == WriteConsole( hStdOutput, pstr, len?len:strlen(pstr), &n, NULL );
}

/* 输出字符串 */
bool OutputStringNoMove( short x, short y, const char* pstr, size_t len) 
{
	/* 定义用于获取坐标结构体 */
    COORD coord = { x, y };
	/* 32bit 无符号整数 */
    DWORD n = 0;
    return TRUE == WriteConsoleOutputCharacter( hStdOutput, pstr, len?len:strlen(pstr), coord, &n );
}

/* 窗口界面显示 */
/* 构建11*19的游戏窗口 */
const char bg[] =
"┏━━━━━━━━━━━┓            "
"┃■■■■■■■■■■■┃ ←↓→ ↑  "
"┃■■■■■■■■■■■┃ Begin      "
"┃■■■■■■■■■■■┃ Voice = Yes"
"┃■■■■■■■■■■■┃ Sleep      "
"┃■■■■■■■■■■■┃ Quit       "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃            "
"┃■■■■■■■■■■■┃ ＮＥＸＴ   "
"┃■■■■■■■■■■■┃┏━━━━┓"
"┃■■■■■■■■■■■┃┃　　　　┃"
"┃■■■■■■■■■■■┃┃　　　　┃"
"┃■■■■■■■■■■■┃┗━━━━┛"
"┃■■■■■■■■■■■┃ ＬＥＶＥＬ "
"┃■■■■■■■■■■■┃┏━━━━┓"
"┃■■■■■■■■■■■┃┃ 0      ┃"
"┃■■■■■■■■■■■┃┗━━━━┛"
"┃■■■■■■■■■■■┃ ＳＣＯＲＥ "
"┃■■■■■■■■■■■┃┏━━━━┓"
"┃■■■■■■■■■■■┃┃ 00000  ┃"
"┗━━━━━━━━━━━┛┗━━━━┛";


/* 七种图形的各种情况 */
/* 第一维为图形种类，第二维为图形的方向，三四维为图形的4*4的填充方式 */
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

/* 控制声音开启函数 */
void VoiceBeep( void )
{
    if( voice )       /* 如果声音开启了 */
    Beep( 1760, 10 ); /* 调用系统声音 */
}

/* 绘制得分 */
void DrawScoreLevel( void )
{
    char tmp[6];
    /* 输出得分 */
    sprintf( tmp, "%05d", score );
    OutputStringNoMove( 31, 19, tmp, 5 );

	/* 输出等级 */
    sprintf( tmp, "%1d", level );
    OutputStringNoMove( 35, 15, tmp, 1 );
}

/* 绘制声音的开关 */
void DrawVoice( void )
{
    OutputStringNoMove( 35, 3, voice?"Yes":"No ", 0 );
}

/* 绘制 "next框" 中的图形 */
void DrawNext( void )
{
    int i, j; 
	/* next框由2*4的格子组成，绘制bk中每种图形的第一个形状 */
    for( i=0; i<2; ++i )
    {
        for( j=0; j<4; ++j )
        {
            OutputStringNoMove( 28+j*2, 10+i, bk[next][0][i][j]== 0?"  ":"■", 2 );
        }
    }
}

/* 游戏结束 */
void DrawOver( void )
{
    OutputStringNoMove( 28, 10, "ＧＡＭＥ", 0 );
    OutputStringNoMove( 28, 11, "ＯＶＥＲ", 0 );
}

/* 绘制图形 */
void Draw( WORD color )
{
    int i, j;
    for( i = 0; i < 4; ++i )
    {
    	/* 判断是否绘制出界 */
        if( (y + i < 0) || (y + i >= 19) ) 
        {
            continue;
        }
        for( j = 0; j < 4; ++j )
        {
            if( bk[c][z][i][j] == 1 )
            {
                SetColor( color );		   /* 设置颜色 */
                GotoXY( 2+x*2+j*2, 1+y+i );/* 从左到右依次绘制 */
                OutputString( "■", 2 );
            }
        }
    }
}

/* 判断给定的x,y,c,z是否可行 */
bool IsFit( int x, int y, int c, int z ) 
{
    int i, j;
    for( i=0; i<4; ++i )
    {
        for( j=0; j<4; ++j )
        {
            if( bk[c][z][i][j]==1 )
            {
            	/* 出界 */
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

/* 消行 */
void RemoveRow( void )
{
    char FULLLINE[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int  linecount = 0;
    int  _score = 0; /* 加分 */
    int i, m, n;
	/* 把整个窗口都遍历一遍，从上到下搜索满行 */
    for( i=0; i<19; ++i )
    {
    	/* 找到一个满行 */
        if( 0 == memcmp( data[i], FULLLINE, 11 ) )
        {
            ++linecount;
            for( m=0; m<11; ++m )
            {
            	/* 将满行之上所有行下移 */
                for( n=i; n>1; --n )
                {
                    data[n][m] = data[n-1][m];
                    SetColor( data[n][m]==1?COLOR_B:COLOR_C );
                    GotoXY( 2+m*2, 1+n );
                    OutputString( "■", 2 );
                }
                data[0][m] = 0;/* 修改该行的记录为空 */
                OutputStringNoMove( 2+m*2, 1, "■", 2 );/* 恢复该行 */
            }
        }
    }
	/* 遍历完成后恢复游戏窗口的记录 */
    char data[19][11] = { 0 };
	
	/* 如果没有满行 */
    if( linecount == 0 ) 
    {
        return;
    }

	/* 得分分等级 */
    switch( linecount )
    {
        case 1: _score = 100; break;
        case 2: _score = 300; break;
        case 3: _score = 700; break;
        case 4: _score = 1500;break;
    }
	/* 将加分加入总分 */
    score += _score;
	/* 得分上限为99999 */
    if( score > 99999 ) 
    {
        score = 99999;
    }
	/* 等级为得分除以10000，所以最高为9级 */
    level = score/10000;
	/* 绘制得分和等级 */
    DrawScoreLevel();
}

/* 逆时针翻转 */
void MoveTrans( void ) 
{
	/* 判断翻转后是否适合窗口 */
    if( IsFit( x, y, c, (z+1)%4 ) )
    {
    	/* 开启声音 */
        VoiceBeep();
		/* 绘制背景色 */
        Draw( COLOR_C );
		/* 保存方块方向的变化 */
        z = (z + 1) % 4;
		/* 绘制方块颜色 */
        Draw( COLOR_A );
    }
}

/* 向左移 */
void MoveLeft( void ) 
{
	/* 判断翻转后是否适合窗口 */
    if( IsFit( x-1, y, c, z ) )
    {
    	/* 开启声音 */
        VoiceBeep();
		/* 绘制背景色 */
        Draw( COLOR_C );
		/* 横坐标减一 */
        --x;
		/* 绘制方块颜色 */
        Draw( COLOR_A );
    }
}

/* 向右移 */
void MoveRight( void ) 
{
	/* 判断翻转后是否适合窗口 */
    if( IsFit( x+1, y, c, z ) )
    {
    	/* 开启声音 */
        VoiceBeep();
		/* 绘制背景色 */
        Draw( COLOR_C );
		/* 横坐标加一 */
        ++x;
		/* 绘制方块颜色 */
        Draw( COLOR_A );
    }
}

/* 向下移 */
void MoveDown( void ) 
{
    int i, j;
	/* 判断下移后是否适合窗口 */
    if( IsFit( x, y+1, c, z ) )
    {
    	/* 开启声音 */
        VoiceBeep();
		/* 绘制背景色 */
        Draw( COLOR_C );
		/* 纵坐标加一 */
        ++y;
		/* 绘制方块颜色 */
        Draw( COLOR_A );
    }
	/* 方块触底 */
    else if( y != -2 ) 
    {
    	/* 绘制方块的颜色为绿色 */
        Draw( COLOR_B );
		/* 记录窗口现在的信息 */
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
		/* 落下一块就运行一次消行函数 */
        RemoveRow();
		/* 重置x，y坐标作为方块开始出现的地方；同时重置方向和种类 */
        x=4, y=-2, c=next, z=0;
		/* 随机出现0~6 */
        next = rand()%7;
		/* 首先绘制next提示窗口的图形 */
        DrawNext();
    }
	/* 游戏结束 */
    else 
    {
    	/* 绘制结束窗口信息 */
        DrawOver();
    }
}

/* 接受键盘输入信息函数 */
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
                    case 'q': /* 退出 */
                        return;
                        break;
                    case 'S': /* 暂停 */
                    case 's':
                        for( ; ; )
                        {
                            switch( _getch() )
                            {
                                case 'Q':
                                case 'q': /* 退出 */
                                    return;
                                case 'V': /* 声音 */
                                case 'v':
                                    voice = !voice;/* 改变声音设置 */
                                    DrawVoice();   /* 绘制声音窗口图形 */
                                    break;
                                case 'S':
                                case 's':
                                    goto LABLE_CONTINUE;
                                    break;
                            }
                        }
                        LABLE_CONTINUE:
                        break;
                    case 'V': /* 声音 */
                    case 'v':
                        voice = !voice;
                        DrawVoice();
                        break;
                    case 0xe0: /* ←↓→ ↑ */
                        switch( _getch() )
                        {
                            case 0x4B: /* ← */
                                MoveLeft();
                                break;
                            case 0x50: /*  ↓ */
                                MoveDown();
                                break;
                            case 0x4d: /*  → */
                                MoveRight();
                                break; /* ↑ 变形 */
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
			/* 减慢出现新图形的时间 */
            Sleep( 55 );
        }
        MoveDown();
    }
}

int main()
{
    char c;
    Open();
    /* 设置标题 */
    SetTitle( "俄罗斯方块 made by 宋文亮" );
    /* 去处光标 */
    RemoveCursor();
    /* 设置窗体尺寸 */
    SetWindowRect( 38-1, 21-1 );
    /* 设置缓冲尺寸 */
    SetBufSize( 38, 21 );
    /* 输出背景字符 */
    OutputStringNoMove( 0,0,bg,0 );
    /* 使用系统时间设置随机种子 */
    srand( time(0) );
	/* 设置图形种类的随机数 */
    next = rand()%7;
	/* 绘制next窗口 */
    DrawNext();
	/* 开始 Begin */
    for( c = (char)_getch(); (c != 'B') &&(c != 'b'); c = (char)_getch() ) 
    {
    	/* 更改铃声 Vocie设置 */
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
	/* 恢复初始数据 */
    x = 4, y = -2, c = next, z = 0;
    next = rand()%7;
    DrawNext();
	/* 接受用户输入信息 */
    MessageDeal();
    return 0;
}


