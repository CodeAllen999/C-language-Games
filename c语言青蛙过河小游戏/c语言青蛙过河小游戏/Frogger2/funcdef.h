//�봬���
void initBoard(BoardType b[]);//��ÿ��ľ���������
void excuteBoardFunc(BoardType board[],int ChannelSpeed[],FrogType *frog);//�ж������ã��ƶ�������
void drawBoard(BoardType board[],ImageType *img);//����

//���������
void resetFrog(FrogType *frog);
void initFrog(FrogType *frog);
void excuteFrogFunc(FrogType *frog,int ChannelSpeed[],BoardType board[]);//���ܲ����ۺ�
void drawFrog(FrogType *frog,ImageType *img);
//��
void drawStream(ImageType *img);//����
void drawBackground(ImageType *img);//����

void excuteEvent(FrogType *frog,int ChannelSpeed[],ImageType *img);//ִ�й��ػ����õ�EVENT

void excuteStateBarFunc(FrogType *frog,int ChannelSpeed[]);//״̬���ۺϲ���
void initFont();//����

void initImage(ImageType *img);//����ͼƬ

int initWelcome(ImageType *img);//��ӭ����