#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{

    ui->setupUi(this);

    // 配置主场景
    // 设置固定主窗口大小
    this->setFixedSize(320,588);

    // 设置主窗口图标 , MacOS 需要在 .pro 文件内添加 ICON = Icon.icns 来进行设置
     //this->setWindowIcon(QIcon(":/icon/Icon.icns"));
     //设置主窗口标题
     this->setWindowTitle("翻金币");

     //退出按钮实现
     connect(ui->actionquit ,&QAction::triggered, [=](){
         this->close();
     });

     ///// 背景图片, 需要重写 paintEvent() 事件函数

     // 准备 start 按钮的 音效
     QSound* startSound = new QSound(":/sound/startTouchSound.wav",this);
     // 准备 BACK 按钮的 音效
     QSound* backSound = new QSound(":/sound/backSound.wav",this);


     //实例化 创建一个 选择关卡场景
     chooseScene  = new ChooseLevelScene;

     //开始按钮, 1.png
     MyPushButton* startBtn = new MyPushButton(":/png/1.png");
     startBtn->setParent(this);
     startBtn->move(this->width() * 0.5  - startBtn->width() *0.5 ,this->height() * 0.7 - startBtn->height() * 0.5);
     startBtn->show();

     //点击开始按钮 start 后 进入到选择关卡场景中
     connect(startBtn, &QPushButton::clicked,[=](){
         qDebug() << "点击开始";

         startSound->play();// 开始音频

         // 做一个弹起的特效
         startBtn-> zoom1();
         startBtn-> zoom2();


         // 延时一些时间, 等待动画完成, 在进入到新的选择关卡场景, 会增加用户体验
         QTimer::singleShot(300,this,[=](){
             chooseScene->setGeometry(this->geometry()); // 变成上个窗口在屏幕的位置出现
             // 隐藏主窗口的整个场景,
             this->hide();
             //显示 新的 选择关卡场景
             chooseScene->show();
         });
     });

     // 监听选择关卡的 BACK 按钮触发信号,准备显示主窗口
     connect(chooseScene,&ChooseLevelScene::chooseScLevelScene,[=](){
         this->setGeometry(chooseScene->geometry());  // 变成上个窗口在屏幕的位置出现
         backSound->play();
         qDebug() << "back 按钮被触发了, 收到 chooseScLevelScene 信号";
         chooseScene->hide();
         this->show();
     });

}

// 重写 paintEvent 事件, 画背景图
void
MainScene::paintEvent(QPaintEvent* e){
    QPainter painter(this);  //设置绘画设备
    QPixmap pix;
    pix.load(":/png/back.jpg");    // 绘画背景
    pix = pix.scaled(pix.width() * 0.95, pix.height()*0.95);     // 将载入的图片进行缩放, 需要pix 来接受,进行刷新
    painter.drawPixmap(0,0, pix);    //绘画图片, 并拉伸图片, 占满整个窗口

// 绘画背景上的图标
    pix.load(":/png/9.png");   // 载入另一个图片
    pix = pix.scaled(pix.width() *0.3, pix.height() * 0.3);     // 将载入的图片进行缩放, 是原始图片的 0.3 倍大小
    painter.drawPixmap(0,0, pix);    //再次 绘画图片
}

MainScene::~MainScene()
{
    delete ui;
}

