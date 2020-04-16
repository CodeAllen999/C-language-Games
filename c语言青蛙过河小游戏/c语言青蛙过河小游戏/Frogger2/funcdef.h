//与船相关
void initBoard(BoardType b[]);//给每个木版分配坐标
void excuteBoardFunc(BoardType board[],int ChannelSpeed[],FrogType *frog);//判定，重置，移动，画船
void drawBoard(BoardType board[],ImageType *img);//画船

//与青蛙相关
void resetFrog(FrogType *frog);
void initFrog(FrogType *frog);
void excuteFrogFunc(FrogType *frog,int ChannelSpeed[],BoardType board[]);//青蛙操作综合
void drawFrog(FrogType *frog,ImageType *img);
//河
void drawStream(ImageType *img);//画河
void drawBackground(ImageType *img);//背景

void excuteEvent(FrogType *frog,int ChannelSpeed[],ImageType *img);//执行过关或重置等EVENT

void excuteStateBarFunc(FrogType *frog,int ChannelSpeed[]);//状态栏综合操作
void initFont();//字体

void initImage(ImageType *img);//加载图片

int initWelcome(ImageType *img);//欢迎界面