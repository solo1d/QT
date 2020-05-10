#ifndef MYCOIN_H
#define MYCOIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QPixmap>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //  explicit MyCoin(QWidget *parent = nullptr);


    // 传入 图片,
    explicit MyCoin(QString btnImg);


    // 金币的属性
    int posX ; // x坐标位置
    int posY ; // y坐标位置
    bool  flag; // 正反标志


    // 改变标志的方法
    void changFlag(void);
    QTimer* timer1;   // 正面翻反面的定时器
    QTimer* timer2;   // 反面翻正面的定时器

    int min = 0;  // 图片最小值
    int max = 3;  // 图片最大值, 也就是文件名  0-3

    ///执行动画的标志
    bool isAnimation= false;


    void
    mousePressEvent(QMouseEvent *e) override;


    // 是否通关的标志
    bool isWin = false;
signals:

};

#endif // MYCOIN_H
