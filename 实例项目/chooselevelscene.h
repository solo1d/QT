#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include <QSound>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);


    //重写绘图事件
    void paintEvent(QPaintEvent* e) override;

private:
    PlayScene * play = nullptr;
signals:
    void chooseScLevelScene();   // BACK按钮触发的自定义信号,代表当前窗口被隐藏了.
};

#endif // CHOOSELEVELSCENE_H
