#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include "chooselevelscene.h"
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    // 重写 paintEvent 事件, 画背景图
    void paintEvent(QPaintEvent* e) override;

    // 选择关卡场景类
    ChooseLevelScene* chooseScene = nullptr;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
