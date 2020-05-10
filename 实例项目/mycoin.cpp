#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}



// 传入 图片, 金币
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;

    bool ret = pix.load(btnImg);
    if(!ret){
        qDebug() << "图片加载失败: " << btnImg.toUtf8().data();
        return;
    }

    pix = pix.scaled(46,46);   // 设置图片缩放
    this->setFixedSize(pix.width(), pix.height());  // 设置按钮大小, 与图片相同
    this->setStyleSheet("QPushButton{border:0px;}");   /// 设置不规则图片的样式, 将图片的边框像素点占用设置为0
    this->setIcon(pix);   // 设置显示的图片
    this->setIconSize(QSize(pix.width(), pix.height())); // 设置显示图片大小

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/game/%1.png").arg(this->min++);  // 从金到蓝
        pix.load(str);

        pix = pix.scaled(46,46);   // 设置图片缩放
        this->setFixedSize(pix.width(), pix.height());  // 设置按钮大小, 与图片相同
        this->setStyleSheet("QPushButton{border:0px;}");   /// 设置不规则图片的样式, 将图片的边框像素点占用设置为0
        this->setIcon(pix);   // 设置显示的图片
        this->setIconSize(QSize(pix.width(), pix.height())); // 设置显示图片大小


        if(this->min > this->max){
            this->flag = false;
            this->min  = 0;
            this->timer1->stop();
            isAnimation = false;  //动画执行完毕了
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/game/%1.png").arg(this->max--);  // 从金到蓝
        pix.load(str);

        pix = pix.scaled(46,46);   // 设置图片缩放
        this->setFixedSize(pix.width(), pix.height());  // 设置按钮大小, 与图片相同
        this->setStyleSheet("QPushButton{border:0px;}");   /// 设置不规则图片的样式, 将图片的边框像素点占用设置为0
        this->setIcon(pix);   // 设置显示的图片
        this->setIconSize(QSize(pix.width(), pix.height())); // 设置显示图片大小


        if(this->max < this->min){
            this->flag = true;
            this->max  = 3;
            this->timer2->stop();
            isAnimation = false;  //动画执行完毕了
        }
    });
}


void
MyCoin::changFlag(void){

    isAnimation = true;  // 开始执行动画了
    if(true == flag)
        timer1->start(30);
    else
        timer2->start(30);
}

void
MyCoin::mousePressEvent(QMouseEvent *e) {
    if( this->isWin || isAnimation){ // 胜利了, 截取鼠标点击动作,拦截 动画还未执行完毕就出现的点击事件
        return;
    }
  QPushButton::mousePressEvent(e);
}
