#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include <QPropertyAnimation>
#include "dataconfig.h"
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlayScene(QWidget *parent = nullptr);

    // 构造
    explicit PlayScene(int levelNum );

    int levelIndex; // 内部成员属性

    // 重写绘图事件
    void paintEvent(QPaintEvent* e) override;

    int dataUp[16] ;       // 备份按钮数组的状态
    MyCoin* coinBtn[16];   // 按钮数组,用于备份

    // 是否通关的标志
    bool isWin;

signals:
    void palyScLevelScene();   // BACK按钮触发的自定义信号,代表当前窗口被隐藏了.
};

#endif // PLAYSCENE_H
