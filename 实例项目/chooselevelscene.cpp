#include "chooselevelscene.h"


// 配置选择关卡场景
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{

    // 配置 选择关卡场景的窗口
    // 设置固定主窗口大小
    this->setFixedSize(320,588);

    // 设置主窗口图标 , MacOS 需要在 .pro 文件内添加 ICON = Icon.icns 来进行设置
     this->setWindowIcon(QIcon(":/icon/Icon.icns"));

     //设置主窗口标题
     this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar* bar =  menuBar();
    this->setMenuBar(bar) ;   // 将菜单栏添加到 选择关卡场景 窗口中
    QMenu *startMenu =  bar->addMenu("开始-1");  // 创建开始菜单
    QAction* quitMenu =  startMenu->addAction("退出-1");  // 创建 退出菜单项

    // 点击退出 实现 退出游戏
    connect(quitMenu,&QAction::triggered,[=](){
        this->close();
    });

    // BACK 返回按钮
    MyPushButton* backBtn = new MyPushButton(":/png/5_60x60.png", ":/png/3_60x60.png");
    backBtn->setParent(this);   // 让 这个按钮 依附于这个窗口, 并显示出来
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height()); // 移动到有右下角
    // 点击按钮就返回
    connect(backBtn, &QPushButton::clicked, [=](){
        qDebug() << "点击了返回按钮";
        QTimer::singleShot(300,[=](){
            emit this->chooseScLevelScene();  // 发送点击了 BACK的信号
        });
    });


    // 设置选择关卡的 音效
    QSound* chooSound = new QSound(":/sound/selectTouchSound.wav", this);
    // 设置 BACK 回退按钮音效
    QSound* backSound = new QSound(":/sound/backSound.wav",this);

    // 创建选择关卡的按钮
    for(int i =0 ; i < 20 ; i++){
        MyPushButton * menuBtn =new MyPushButton(":/png/icon_64x64.png");
        menuBtn->setParent(this);
        menuBtn->move( 0+(i%5)*64, 100 +  i/5 *70);   //排列成一个 5*5 矩阵
        QLabel * label = new  QLabel(this);
        label->setNum(i+1);
        label->setStyleSheet("color:red;");  // 标签显示的文本变成红色
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->move( 0+(i%5)*64 , 100 + i/5 *70);   //排列成一个 5*5 矩阵
        // 减去了 menuBtn->width()/2 参与到运算, 因为使用了下面的对齐方式

        //设置 label 上, 文字的对齐方式,  水平居中 和 垂直居中, (仅仅调整单个label)
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        // 设置属性, 让鼠标动作进行穿透,作用在 按钮menuBtn上
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        // 监听每个按钮的点击事件,并选择关卡
        connect(menuBtn, &MyPushButton::clicked,[=](){
            chooSound->play();   // 播放选择关卡的 音效
            QString str = QString("选择 第 %1 关").arg(i+1);
            qDebug() << str.toUtf8().data();


            // 进入游戏场景,这个是核心界面
            // 创建 自定义的游戏场景,
            play = new PlayScene( i+1 );
            play->setGeometry(this->geometry());  // 设置游戏窗口出现的位置
            this->hide();
            play->show();

            //监听核心关卡中发出的 BACK 信号
            connect(play, &PlayScene::palyScLevelScene, [=](){
                this->setGeometry(play->geometry());
                backSound->play();  //BACK  按钮音效播放
                qDebug() << "核心关卡选择了返回";
                this->show();
                delete play;   //直接删除即可, 不需要常驻
                play = nullptr;
            });
        });
    };

}


//重写绘图事件
void
ChooseLevelScene::paintEvent(QPaintEvent* e){
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
