#define TICK 10//游戏刻：20ms (更新频率)

#define WINDOW_LEN 1000//窗口长度
#define WINDOW_WID 600//窗口高度

#define STREAM_INIT_Y 100//河流开始的高度（与窗口上边框的距离）
#define STREAM_WID 400//河的宽度

#define CHANNEL_AMOUNT 4//4条河道
#define CHANNEL_WID STREAM_WID/CHANNEL_AMOUNT //每条的宽度

#define BOARD_LEN 120//木板长度
#define BOARD_WID CHANNEL_WID*0.6//木板高度//黄金分割率 
#define MIN_BOARD_INTERVAL 100//最小间隔
#define MAX_BOARD_INTERVAL 250//木板最大间隔
#define BOARD_AMOUNT 6//一条河道的木板数量
#define BOARD_INTERVAL MIN_BOARD_INTERVAL+1+(int)((MAX_BOARD_INTERVAL-MIN_BOARD_INTERVAL)*(rand()/(RAND_MAX+1.0)))//船间距

//青蛙的状态
#define NORMAL 0
#define DEAD 1
#define PASSED 2

//右侧状态栏
#define STATE_BAR_LEN 200
#define STATE_BAR_WID WINDOW_WID
#define WORD_START_X WINDOW_LEN+STATE_BAR_LEN/5//文字开始的横坐标,从几分之一处开始
#define WORD_START_Y STATE_BAR_WID/8//文字开始的纵坐标
#define WORD_LINE_SPACING 50//文字行间距

//青蛙图片
#define FROG_LEN 70
#define FROG_WID 70

#define DEATH_DELAY 150//死亡时转圈时间
#define PASS_DELAY 80//过关延时