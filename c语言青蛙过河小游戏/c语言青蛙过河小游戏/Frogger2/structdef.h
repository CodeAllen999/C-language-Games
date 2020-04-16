struct EachBoard
{
	int x;//木板左上角X坐标
	int onMap;//是否在地图上 1或0
};

struct BoardType
{
	EachBoard b[BOARD_AMOUNT];
};

struct FrogType
{

	int x;
	int ch;//channel
	int speed;
	int life;
	int passed;
	int state;//状态，用于出界判定
	//0:正常（在地图上） 1:死亡 2:已过关
	int coin;//金币
	int score;//积分
	int esc;//退出游戏
};

struct ImageType//图片类
{
	IMAGE frog0;
	IMAGE frog0Mask;
	IMAGE wood;
	IMAGE woodMask;
	IMAGE stream;
	IMAGE grass1;
	IMAGE grass2;
	IMAGE welcome;
};