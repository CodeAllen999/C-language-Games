struct EachBoard
{
	int x;//ľ�����Ͻ�X����
	int onMap;//�Ƿ��ڵ�ͼ�� 1��0
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
	int state;//״̬�����ڳ����ж�
	//0:�������ڵ�ͼ�ϣ� 1:���� 2:�ѹ���
	int coin;//���
	int score;//����
	int esc;//�˳���Ϸ
};

struct ImageType//ͼƬ��
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