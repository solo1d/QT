- [生成过程](#生成过程)

  - **项目名称wideget,  目录名称 wideget, 生成的应用程序的名称wideget.app**
  - [main.cpp](#main.cpp)
  - [wideget.pro](#wideget.pro)

- [窗口函数原型](#窗口函数原型)

- [标签控件函数原型](#标签控件函数原型)

- [按钮控件函数原型](#按钮控件函数原型)

- 

  





# 生成过程

- **建立项目目录  `wideget`**
  - 创建main.cpp 和其他源文件
  - 使用 `qmake -project`  创建 .pro文件
  - 在 .pro文件内添加 `QT+= widgets` 模块
  - 使用 `qmake` 生成 `Makefile`
  - 使用 `make`  编译
    - 如果 .cpp 出现错误 ,   则修改后 继续使用 `make` 编译



## main.cpp

```cpp
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[]){
     // 创建 Qt 应用程序对象, 必须第一个存在
    QApplication app(argc, argv);

//    下面是三种主窗口 , QWidget , QDialog  ,QMainWindow 
//    QWidget parent;   // 该窗口  在 随机 位置显示
//    QDialog  parent;  // 该窗口 在 居中 位置显示, 缺少最小化按钮
    QMainWindow parent;   // 该窗口根据控件自动调整大小   
    parent.move(50,50);
    parent.resize(320,240);
    
// 标签控件,  停靠在父窗口上面, 如果后面不给主窗口参数,则自动创建一个窗口
    QLabel label("标签显示的内容", &parent);

    label.move(20,40);  // 根据父窗口的左上角进行位置调整
//    label.show();

    QPushButton button("按钮显示的内容", &parent);
    button.move(20, 100);   // 按钮出现的位置
    button.resize(80,100);  // 重设按钮的大小
//    button.show();  // 显示按钮


	 parent.show();  // 显示窗口的所有控件

    // 让应用程序进入事件, 这样才能保持窗口一直存在
    return app.exec();
}
```



## wideget.pro

```properties
QT += widgets      #新添加的内容
TEMPLATE = app
TARGET = wideget
INCLUDEPATH += .
SOURCES += main.cpp
```





## 窗口函数原型

```c++
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QMainWindow>
//  在 项目.pro 文件内添加   QT += widgets

主窗口
//    下面是三种主窗口 , QWidget , QDialog  ,QMainWindow 
    QWidget parent;   // 该窗口  在 随机 位置显示
    QDialog  parent;  // 该窗口 在 居中 位置显示, 缺少最小化按钮
    QMainWindow parent;   // 该窗口根据控件自动调整大小


窗口设置
    parent->show();   //显示窗口
    parent->move(50,50);       //窗口 y x  位置
    parent->resize(400,500);   // 窗口 宽度 高度 大小
```

## 标签控件函数原型

```cpp
#include <QDialog>
#include <QLabel>
// 依托于主窗口, 主窗口销毁时, 控件会更着被销毁

    QDialog  parent;  // 该窗口 在 居中 位置显示, 缺少最小化按钮

// 标签控件,  停靠在父窗口上面, 如果后面不给主窗口参数,则自动创建一个窗口
QLabel* label = new QLabel("标签显示的内容", &parent);

    label->move(20,40);  // 根据父窗口的左上角进行位置调整
		label->rezie(80,100);  // 重设标签的大小
    label->show();       // 显示标签

parent->show();  // 显示窗口的所有控件
```

## 按钮控件函数原型

```cpp
#include <QDialog>
#include <QPushButton>
// 依托于主窗口, 主窗口销毁时, 控件会更着被销毁

    QDialog  parent;  // 该窗口 在 居中 位置显示, 缺少最小化按钮

QPushButton* button = new QPushButton("按钮显示的内容", &parent);

	button->move(20, 80);    // 按钮出现的位置, 根据父窗口的左上角进行位置调整
	button->resize(80,100);  // 重设按钮的大小
	button->show();  // 显示按钮

parent.show();  // 显示窗口的所有控件
```

