#include "mypushbutton.h"

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    if (! pix.load(normalImgPath)){
        qDebug() << "图片加载失败 , normalImgPath";
        return;
    }

    // 将按钮设置成与图片相同的固定大小
    this->setFixedSize(pix.width(), pix.height());

    // 设置不规则图片的样式, 将图片的边框像素点占用设置为0
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标, 就是按钮显示的图片样式
    this->setIcon(pix);

    //设置一个图标的大小, 利用图片的大小来设置
    this->setIconSize(QSize(pix.width(),pix.height()));

}

// 向下跳
void
MyPushButton::zoom1(){
    // 创建动画对象, (设置动画的窗口控件, 动画模式 );
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

    // 设置动画时间 间隔, 也就是 动画会在200毫秒内执行完毕
    animation->setDuration(200);

    //起始位置,
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y() +10,this->width(),this->height()));

    //设置弹跳曲线, 也就是动画效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

// 向上跳
void
MyPushButton::zoom2(){
    // 创建动画对象, (设置动画的窗口控件, 动画模式 );
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

    // 设置动画时间 间隔, 也就是 动画会在200毫秒内执行完毕
    animation->setDuration(200);

    //起始位置 (左, 顶部, 下部, 右)
    animation->setStartValue(QRect(this->x(),this->y() +10,this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线, 也就是动画效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}


// 鼠标点击事件
void
MyPushButton::mousePressEvent(QMouseEvent *ev) {
    if( !pressImgPath.isEmpty()){    //鼠标按下了, 并且第二图片不为空,才切换图片
        // qDebug() << "鼠标点击事件, 并且拥有第二参数";
        QPixmap pix;
        if (! pix.load(this->pressImgPath)){
            qDebug() << "图片加载失败 , pressImgPath";
            return;
        }

        // 将按钮设置成与图片相同的固定大小
        this->setFixedSize(pix.width(), pix.height());

        // 设置不规则图片的样式, 将图片的边框像素点占用设置为0
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标, 就是按钮显示的图片样式
        this->setIcon(pix);

        //设置一个图标的大小, 利用图片的大小来设置
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    // 让父类继续执行其他的内容
    QPushButton::mousePressEvent(ev);
}

// 鼠标点击后释放事件
void
MyPushButton::mouseReleaseEvent(QMouseEvent *ev){
    if(!pressImgPath.isEmpty()){
        // qDebug() << "鼠标释放事件, 并且拥有第二参数";
        QPixmap pix;
        if (! pix.load(this->normalImgPath)){
            qDebug() << "图片加载失败 , pressImgPath";
            return;
        }

        // 将按钮设置成与图片相同的固定大小
        this->setFixedSize(pix.width(), pix.height());

        // 设置不规则图片的样式, 将图片的边框像素点占用设置为0
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标, 就是按钮显示的图片样式
        this->setIcon(pix);

        //设置一个图标的大小, 利用图片的大小来设置
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    // 让父类继续执行其他的内容
    QPushButton::mouseReleaseEvent(ev);
}
