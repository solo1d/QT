#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>   // 弹跳动画类, 拥有特效
#include <QTimer>
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    // normalImg 默认显示的图片路径, pressImg 按下后显示的图片路径
    explicit MyPushButton(QString normalImg, QString pressImg = "");

    //弹跳的特效 1,  就是按钮向下 进行缓慢移动. 并且设置事件和移动位置
    void zoom1();
    //弹跳的特效 2,  就是按钮向上 进行缓慢移动. 并且设置事件和移动位置
    void zoom2();


    // 点击后切换另一张图的特效动作
    // 鼠标点击事件
    void    mousePressEvent(QMouseEvent *ev) override;
    // 点击后切换另一张图的特效动作
    // 鼠标点击后释放事件
    void    mouseReleaseEvent(QMouseEvent *ev) override;

private:
    QString normalImgPath;   // 保存默认显示的图片路径
    QString pressImgPath;    // 保存按下后显示的图片路径
signals:

};

#endif // MYPUSHBUTTON_H
