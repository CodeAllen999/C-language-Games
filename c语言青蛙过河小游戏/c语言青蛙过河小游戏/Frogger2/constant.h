#define TICK 10//��Ϸ�̣�20ms (����Ƶ��)

#define WINDOW_LEN 1000//���ڳ���
#define WINDOW_WID 600//���ڸ߶�

#define STREAM_INIT_Y 100//������ʼ�ĸ߶ȣ��봰���ϱ߿�ľ��룩
#define STREAM_WID 400//�ӵĿ��

#define CHANNEL_AMOUNT 4//4���ӵ�
#define CHANNEL_WID STREAM_WID/CHANNEL_AMOUNT //ÿ���Ŀ��

#define BOARD_LEN 120//ľ�峤��
#define BOARD_WID CHANNEL_WID*0.6//ľ��߶�//�ƽ�ָ��� 
#define MIN_BOARD_INTERVAL 100//��С���
#define MAX_BOARD_INTERVAL 250//ľ�������
#define BOARD_AMOUNT 6//һ���ӵ���ľ������
#define BOARD_INTERVAL MIN_BOARD_INTERVAL+1+(int)((MAX_BOARD_INTERVAL-MIN_BOARD_INTERVAL)*(rand()/(RAND_MAX+1.0)))//�����

//���ܵ�״̬
#define NORMAL 0
#define DEAD 1
#define PASSED 2

//�Ҳ�״̬��
#define STATE_BAR_LEN 200
#define STATE_BAR_WID WINDOW_WID
#define WORD_START_X WINDOW_LEN+STATE_BAR_LEN/5//���ֿ�ʼ�ĺ�����,�Ӽ���֮һ����ʼ
#define WORD_START_Y STATE_BAR_WID/8//���ֿ�ʼ��������
#define WORD_LINE_SPACING 50//�����м��

//����ͼƬ
#define FROG_LEN 70
#define FROG_WID 70

#define DEATH_DELAY 150//����ʱתȦʱ��
#define PASS_DELAY 80//������ʱ