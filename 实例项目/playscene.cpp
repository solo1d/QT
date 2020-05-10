#include "playscene.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

// 创建 关卡 页面
PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;
    QString str  = QString("第 %1 关").arg(this->levelIndex);
    qDebug() << str.toUtf8().data();

    //设置固定大小, 图标 , 标题,之类的
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/icon/Icon.icns"));
    this->setWindowTitle(str);

    //创建菜单栏
    QMenuBar* bar = new QMenuBar();
    this->setMenuBar(bar);
    QMenu* startMenu =  bar->addMenu("开始");
    QAction* closeAction =  startMenu->addAction("退出");   // 创建一个菜单项
    connect(closeAction, &QAction::triggered, [=](){
            close();
    });

    // BACK 返回按钮
    MyPushButton* backBtn = new MyPushButton(":/png/5_60x60.png", ":/png/3_60x60.png");
    backBtn->setParent(this);   // 让 这个按钮 依附于这个窗口, 并显示出来
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height()); // 移动到有右下角

    // 设置 BACK 回退按钮音效
    QSound* backSound = new QSound(":/sound/backSound.wav",this);
    // 设置 通关 音效
    QSound* failureSound = new QSound(":/sound/failureSound.wav",this);
    // 翻牌子音效
    QSound* fanSound = new QSound(":/sound/clearanceSound.wav",this);


    // 点击按钮就返回
    connect(backBtn, &QPushButton::clicked, [=](){
        backSound->play();
        qDebug() << "核心关卡 点击了返回按钮";
        QTimer::singleShot(200,[=](){
            emit this->palyScLevelScene();  // 发送点击了 BACK的信号
        });
    });




    // 修改标签显示文字的  字体
    QFont font;
    font.setFamily("Hei");   // 字体
    font.setPointSize(20);      // 字号
    font.setBold(true);        // 设置 字体加粗
    str = QString("Level : %1").arg(this->levelIndex); // 准备放入label中的内容

    // 显示当前关卡数, 左下角提示 标签
    QLabel * label = new QLabel;
    label->setParent(this);
    label->setText(str);
    label->setGeometry(30, this->height() -50, 120,50);   // 设置标签位置和大小
    label->setFont(font);    // 设置显示的字体

    dataConfig  gameConfig;
    gameConfig.init(levelIndex);


    // 显示 金币翻转区域的背景图
    // 创建金币的灰色背景
    QPixmap pix(":/png/11.png");  // 背景图标
    pix = pix.scaled(50,50);   // 缩放图片
    for(int i =0; i< 4; i++){
        for(int j =0; j< 4; j++){  // j =x , i = y
            //绘制背景图片 矩阵
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);  // 设置大小和初始化位置,
            label->setPixmap(pix);    //显示图片
            label->setParent(this);   // 绑定的窗口
            label->move(57 + j*50, 200+i*50);  // 移动位置

            // 通关标签和动画效果
            QPixmap pixWin;
            pixWin.load(":/png/4.png");
            pixWin = pixWin.scaled(80,60);
            QLabel* winBel = new QLabel(this);
            winBel->setPixmap(pixWin);
            winBel->setGeometry(0,0,pixWin.width(), pixWin.height());  // 设置大小和初始化位置,
            winBel->move(this->width()/2 - pixWin.width()/2, -pixWin.height());
            winBel->setParent(this);

            //动画效果
            QPropertyAnimation* animation = new QPropertyAnimation(winBel, "geometry");
            // 设置动画时间 间隔, 也就是 动画会在200毫秒内执行完毕
            animation->setDuration(200);
            //起始位置
            animation->setStartValue(QRect(winBel->x(),winBel->y(),winBel->width(),winBel->height()));
            //结束位置
            animation->setEndValue(QRect(winBel->x(),winBel->y() +150,winBel->width(),winBel->height()));
            //设置弹跳曲线, 也就是动画效果
            animation->setEasingCurve(QEasingCurve::OutBounce);


            // 创建金币, 在背景的上面
            MyCoin* coin = nullptr;
            // 交手关卡数据
            dataUp[i*4+j] = gameConfig.array1[i*4+j];

//            if (gameConfig.array1[i*4+j] == 1){
            if (dataUp[i*4+j] == 1){
                coin = new MyCoin(":/game/0.png");   // 显示金色的

            }
            else{
                coin = new MyCoin(":/game/3.png");   // 显示蓝色的
            }
            // 保存 金币按钮, 便于后期维护
            this->coinBtn[i*4+j] = coin;

            coin->setParent(this);
            int coinPathX =label->width() / 2 - coin->width()/2;
            int coinPathY =label->height() / 2 - coin->height()/2;
            coin->move(coinPathX+ 57 +j*50,coinPathY+200+i*50);  // 居中的计算步骤.

            //给金币属性 赋值
            coin->posX = j;
            coin->posY = i;
            coin->flag = gameConfig.array1[i*4+j]; // 1正面, 0 反面

            //点击金币或银币就进行翻转
            connect(coin, &MyCoin::clicked,[=]()mutable{
                fanSound->play(); // 翻金币音效
                for(int i =0 ; i<16 ; i++){
                    coinBtn[i]->isAnimation = true;
                }
                coin->changFlag();
                dataUp[coin->posY*4+coin->posX] = dataUp[coin->posY*4+coin->posX] == 1 ? 0 : 1;
                qDebug() << "dataUp = " <<  dataUp[i*4+j];

                // 进行延时翻转, 为了观赏性
                QTimer::singleShot(200,[=](){
                    //翻转周围金币的操作
                    if(coin->posX +1 <= 3){ // 右边
                        coinBtn[coin->posX + coin->posY *4 +1]->changFlag();
                        coinBtn[coin->posX + coin->posY *4 +1]->flag = coinBtn[coin->posX + coin->posY *4 +1]->flag ? false : true;
                        dataUp[coin->posX + coin->posY *4 +1] = dataUp[coin->posX + coin->posY *4 +1] == 1 ? 0 : 1;

                    }
                    if(coin->posX - 1  >= 0){  // 左边
                        coinBtn[coin->posX + coin->posY *4 -1]->changFlag();
                        coinBtn[coin->posX + coin->posY *4 -1]->flag = coinBtn[coin->posX + coin->posY *4 -1]->flag ? false : true;
                        dataUp[coin->posX + coin->posY *4 -1] = dataUp[coin->posX + coin->posY *4 -1] == 1 ? 0 : 1;
                    }
                    if(coin->posY +1 <= 3){  // 下边
                        coinBtn[coin->posX + (coin->posY+1) *4 ]->changFlag();
                        coinBtn[coin->posX + (coin->posY+1) *4]->flag = coinBtn[coin->posX + (coin->posY+1) *4]->flag ? false : true;
                        dataUp[coin->posX + (coin->posY+1) *4] = dataUp[coin->posX + (coin->posY+1) *4] == 1 ? 0 : 1;
                    }
                    if(coin->posY - 1  >= 0){  // 上边
                        coinBtn[coin->posX + (coin->posY-1) *4 ]->changFlag();
                        coinBtn[coin->posX + (coin->posY-1) *4]->flag = coinBtn[coin->posX + (coin->posY-1) *4]->flag ? false : true;
                        dataUp[coin->posX + (coin->posY-1) *4 ] = dataUp[coin->posX + (coin->posY-1) *4 ] == 1 ? 0 : 1;
                    }

                    for(int i =0 ; i<16 ; i++){
                        coinBtn[i]->isAnimation = false;
                    }
                    // 判断是否通关
                    this->isWin = true;

                    for(int i =0; i < 16 ; i++){
                        if(coinBtn[i]->flag == false){
                            this->isWin = false;   //有一个反面就算失败
                            break;
                        }
                    }

                    if(this->isWin){
                        fanSound->stop();
//                        qDebug() <<" 胜利了";
                        for(int i =0; i < 16 ; i++)
                            coinBtn[i]->isWin=true;
                        failureSound->play();  // 胜利音效
                        // 将胜利的图片 弹跳下来
                        animation->start();
                    }
                });
            });
        }
    }
}

// 重写绘图事件
void
PlayScene::paintEvent(QPaintEvent* e){
    //背景界面
    QPainter painter(this);
    QPixmap pix ;
    pix.load(":/png/back.jpg");
    pix = pix.scaled(pix.width() * 0.95, pix.height()*0.95);
    painter.drawPixmap(0,0,pix);

    // 加载一个标题
    pix.load(":/png/12.png");
    pix= pix.scaled(pix.width()*0.3, pix.height()*0.3);
    painter.drawPixmap( (this->width() - pix.width()) *0.5 ,pix.height() * 0.5, pix);
}
