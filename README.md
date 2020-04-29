## 目录

- [QT笔记](#QT笔记)
- [头文件说明](#头文件说明)
- [工程文件说明](#工程文件说明)
- [详细类对象说明](#详细类对象说明)
- [宏和类说明](#宏和类说明)
- [信号和槽](#信号和槽)
  - [自定义信号和槽](#自定义信号和槽)
  - [按钮发出信号触发自定义的槽函数](#按钮发出信号触发自定义的槽函数)
  - [使用Lambda表达式来触发自定义槽函数](#使用Lambda表达式来触发自定义槽函数)
  - [1信号连接槽函数,2信号再连接1信号](#1信号连接槽函数,2信号再连接1信号)
  - [断开信号和槽的连接](#断开信号和槽的连接)
- [按钮和窗口标题以及窗口固定大小](#按钮和窗口标题以及窗口固定大小)
- [菜单栏和工具栏](#菜单栏和工具栏)
- [网络](#网络)
- [QString转chat*](#QString转chat*)
- [添加QT资源文件](#添加QT资源文件)
- [对话框](#对话框)
  - [标准对话框](#标准对话框)
- [界面布局](#界面布局)
- [按钮控件](#按钮控件)
- [基于模型-包括数据库的排列控件](#基于模型-包括数据库的排列控件)
- [基于对象项目的排列控件](#基于对象项目的排列控件)
- [其他的一些窗口控件](#其他的一些窗口控件)
  - [可滚动区域窗口控件](#可滚动区域窗口控件)
  - [分组窗口控件](#分组窗口控件)
  - [网页标签类窗口控件](#网页标签类窗口控件)
  - [分页标签类窗口控件](#分页标签类窗口控件)
  - [下拉框-常用](#下拉框-常用)
- [自定义封装控件](#自定义封装控件)
- 



## QT笔记

> **一般情况下,创建项目为 `Application` 中的 `QT Widgets Applecation` 桌面QT应用主窗体即可.**
>
> - 创建的项目中不允许出现中文.
> - **默认创建的类信息很重要**
>   - **基类(有三种,继承关系):**
>     - `QWidget` : **最基本的基类, 只有空窗口,其他的什么都没有**
>     - `QMainWindow`   :**继承于`QWidget` 的派生类, 除空窗口外还拥有  菜单栏,状态栏,工具栏**
>     - `QDialog` :**继承于`QWidget` 的派生类, 除空窗口外还拥有 对话框,和对话框内的一些选择性按钮**
> - **命名规范:**
>   - 类名 : 首字母大写, 单词与单词之间首字母大写 
>   - 函数名和变量名 :首字母小写,  单词与单词之间首字母大写
> - **所有对象的类都继承于 QObject这个基类.**
> - **对象树:**
>   - **在QT中创建对象的时候会提供一个Parent对象指针.**
>     - 当创建的对象在堆区时候, 如果指定的父类时QObject派生下来的类或者QObject子类派生下来的类,可以不用管理释放的操作, 将对象放入到对象树中(children表).
>   - **所有new 出来的对象, 不用管释放, 都会自动挂到 children 表中.**
>   - **原因是 children 表中的对象会在窗口关闭后进行自动释放.**
>   - **一定程度上简化了内存回收机制**
> - <u>**Qt中的坐标系:   x 左上角到右 ,  y 左上角到底部, 全部都是增加,没有负数.**</u>
> - **`emit` 关键字可以触发信号和槽函数. `(emit MyClass::Myfun("123");)`**
> - **Qt中的图片资源都叫做 `Pixmap`, 使用图片资源的函数都会携带这个关键字**
> - **使用图片资源时, 必须在图片资源路径之前添加一个 `:` 来进行声明**
>   - `QPixmap imagePath(":/sre/png/1.png");`
>   - **`QLabel` 标签类还可以显示动图 .gif 格式的**
>     - `QMovie* movie =  new QMovie (":/gif/gif/tea.gif"); //准备动图资源`
>     - `ui->lbl_move->setMovie(movie); //让QLabel 标签显示动图`
>     - `movie->start(); // 动图开始播放`
> - **信号函数出现重载时,必须使用函数指针来进行指向**

- **优点**
  - **跨平台.**
  - **接口简单,容易上手**
  - **一定程度上简化了内存回收**

- **显示中文时, 一定要设置UTF-8来进行输出**



## 头文件说明

```c++
<QApplication>  包含一个应用程序类的头文件 
<QWidget>       窗口类
<QPushButton>   使用按钮需要包含该头文件  QPushButton
<QMenuBar>      菜单栏头文件   QMenuBar
<QToolBar>      工具栏头文件   QToolBar
<QLabel>        状态栏提示信息文本,标签部件
<QStatusBar>    状态栏
<QDockWidget>   浮动窗口(铆接部件)
<QTextEdit>     文本编辑器(可以是中心部件, 很常用)
<QDialog>       对话框(拟态和非拟态)
<QMessageBox>   系统标准的成员函数
<QColorDialog>  选择颜色对话框
<QFileDialog>   文件选择对话框
<QDebug>        调试信息,可以输出一些调试内容和文本,   qDebug() << "内容";
```



## 工程文件说明

**工程文件就是以项目名命名的 `ProjectName.pro` 文件**

```c++
// Qt包含的模块,默认包含了两个模块 core核心模块 和 gui图像模块, qmake 表示需要添加到这里的模块名称
QT       += core gui
  
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets   //大于4版本, 包含widget模块, 为了兼容旧版本.
  
CONFIG += c++      //使用c++11版本和特性
DEFINES += QT_DEPRECATED_WARNINGS   //定义 QT的警告
TARGET = 01FirstPerject   // 目标 就是生成的应用程序的名称
TEMPLATE = app       // 模版 app应用程序模版,有lib  vclib 等等的项目文件.就是生产出来的程序,还是动态库
  
// 项目中包含的源文件
SOURCES += \
    main.cpp \
    mywidget.cpp

// 项目中包含的源头文件
HEADERS += \
    mywidget.h

// ui界面文件
FORMS += \	
    mainwindow.ui
  
// 部署的默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
```





## 详细类对象说明

- **`QApplication a(argc, argv);`  // a是应用程序对象, 在QT中该对象 有且仅有一个,该对象必须存在一个**

```c++
#include <QApplication>    /* 包含一个应用程序类的头文件 */
int main(int argc, char* argv[])
{
  // argc是参数的数量, argv保存的参数.   鼠标和键盘的所有输入都会在这个变量中体现
  
  QApplication a(argc, argv);   
  /* 这个对象a 应用程序对象, 保存了所有的键盘和鼠标的输入
   * 在QT中该对象 有且仅有一个
   */
  
  Widget w;
  /* 窗口对象. 这个类继承于 QWidget 类, 这个类就是空窗口
   * 窗口对象在创建后并不会直接显示出来,必须要调用方法.
   */
  
  w.show(); 
  // 显示窗口, 必须手动调用这个方法来显示.
  
  int ret = a.exec();
  /* 让应用程序对象进入消息循环(死循环)
   * 消息循环中,会持续捕获和等待键盘和鼠标的输入,直到退出该应用
   */
  
  return ret;
}
```







## 宏和类说明

```c++
#include <QWidget>

class myWidget : public QWidget
{
private:
  
    Q_OBJECT
/* 这个宏必须出现在类定义的私有部分中,允许该类声明其自身的信号和插槽，或者使用Qt的元对象系统提供的其他服务 */

public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();
};
```





## 信号和槽

>  <u>**信号函数出现重载时,必须使用函数指针来进行指向**</u>

- **`connect (信号发送者->按钮类, 发送的信号->按钮类的成员函数地址, 接受信号者->按钮所在窗口this, 处理的槽函数->依赖类中的槽函数地址也就是窗口槽函数地址)`**
  - `信号发送者`: 按钮
  - `发送的具体信号`: 点击之类的操作
  - `信号的接收者` : 窗口或将要进行的动作
  - `信号的处理` : 具体实现的动作. **(这个就是槽)**
  - <u>**当信号发生重载时,就必须使用函数指针来间接传递 信号函数和槽函数**</u>
    - `void (类::*函数指针名)(参数类型) = &类::信号函数名; //信号函数指针,类作用域`
    - `void (类::*函数指针名)(参数类型) = &类::槽函数名; //槽函数指针,类作用域`
- **如果当前类没有信号`(帮助文档中是 Signal)`帮助文档, 那么应该向上查找继承的父类中是否存在信号帮助文档.直到找到为止.**
  - `QPushButton 这个类的帮助文档就没有写signal, 应该在它的父类 QAbstractButton 中寻找`
    - `在这个父类中找到了四种Signals内容`
      - `void clicked(bool  checked=false);` 点击按钮触发信号
      - `void pressed();`   按压按钮触发信号
      - `void releassed();`    释放按钮触发信号
      - `void toggled();`   切换状态触发信号
  - **信号函数的图标类似于音量的三个圆弧形状**
- **接下来就需要关于槽`(帮助文档中是 public slots)`的函数,应该去按钮依赖的窗口类中去寻找槽方法.`(QWidget 窗口类)`**
  - `bool  close();`   关闭当前窗口 
  - `void hide();`  隐藏当前窗口
  - **槽函数的图标类似于 皇冠,有三个尖角**

> **`connect()` 可以链接两个毫不相关的信号和槽, 完全自由.**
>
> - **信号可以连接信号.**
> - **一个信号可以连接多个槽**
> - **多个信号可以连接同一个槽**
> - **信号和槽参数类型必须一一对应**
> - **信号的参数个数可以多余和槽的参数个数, 但反过来不行**



```c++
/* connect (信号发送者->按钮 类, 发送的信号->按钮类的成员函数地址, 接受信号者->按钮所在窗口this, 处理的槽函数->依赖类中的槽函数地址也就是窗口槽函数地址) */
#include <QPushButton>
#include <QWidget>
class myWidget : public QWidget
{
private:
    Q_OBJECT

public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();
};

myWidget::myWidget(QWidget *parent): QWidget(parent) {
	QPushButton* btn = new QPushButton("two",this);   // 创建按钮,并绑定到当前窗口
  resize(400,200);      //重置窗口大小,左上角为基本坐标原点,正比例增长, (x宽,y高)
	connect(btn,&QPushButton::clicked, this, &QWidget::close);  // 当点击按钮时就关闭当前窗口
}
```

### 重载信号和槽函数的解决

- 当自定义信号和槽出现重载的时候,原先写法失效,因为执行的函数地址不明确.
- <u>**当信号发生重载时,就必须使用函数指针来间接传递 信号函数和槽函数**</u>
  - `void (类::*函数指针名)(参数类型) = &类::信号函数名; //信号函数指针,类作用域`
  - `void (类::*函数指针名)(参数类型) = &类::槽函数名; //槽函数指针,类作用域`

```c++
// st , zt 都是类对象指针,  hungry 和  treat 是两个类中的成员函数,并与无参的同名函数进行了重载
this->zt = new Teacher(this);
this->st = new Student(this);
// 带参数的 信号和槽
void (Teacher::*teacherSignal)(QString) = &Teacher::hungry;
void (Student::*studentSlot)(QString) = &Student::treat;

connect(this->zt, teacherSignal, this->st, studentSlot);
classIsOver();   //这个函数用来触发信号


//发送自定义信号, 这个函数格式并没有标准
void Widget::classIsOver(void){
//    emit   zt->hungry();
      emit   zt->hungry("宫保鸡丁");  // 这样来进行传参数
}

// 槽函数的实现
void Student::treat(void){
    qDebug() << "请老师吃饭" ;
}

// 槽函数的实现
void Student::treat(QString foodName){
    qDebug() << "请老师吃饭, 吃" << foodName;
}

    void hungry(void);    //声明,不可以实现
    void hungry(QString foodName);    //重载信号
```



## 自定义信号和槽

> - **自定义信号:**
>   - 自定义信号函数写到 **类中的 `signals:` 区域下**
>     - `class A{ public: A(){}  signals: void ele(); };`
>   - **返回值:  没有 void**
>   - **参数: 可以有一个或多个**
>   - **重载: 可以重载**
>   - **信号函数只可以有声明,不可以有实现**



> - **自定义槽:**
>   - 自定义槽函数写到**任意区域内以及全局,但不要出现在`signals`内**
>     - `class B{ public: B(){}  public: void ele(); };`
>       - 但是5.0版本以前,必须写到 `public slots:` 区域内
>   - **返回值:  没有 void**
>   - **参数: 可以有一个或多个**
>   - **重载: 可以重载**
>   - **槽函数必须有实现和声明**



> - **发送(触发)自定义信号和参数:**
>   - **发送自定义信号 需要一个关键字 `emit`**
>     - `void Widget::clIs(void){ emit a->ele();  }`
>       - `a 是 Widget 的类成员,指向 class A结构体的指针,已经 new 申请空间了`
>         - `ele()  是A类的 signals: 下的信号函数声明`
>   - **这个发送信号的动作,应该写入在某个函数中.**

```c++
#include <QObject>
#include <QWidget>

//学生类
class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);
    void treat(void);  // 槽函数, 请客
};

//老师类
class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    // 自定义信号要写到 signals: 区域内
    // 自定义信号没有返回值,  void
    // 只需要声明, 不需要实现
    void hungry(void);    //声明,不可以实现
};

//窗口类
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Teacher*  zt;  // 老师结构体指针 
    Student*  st;  // 老师结构体体指针
    void classIsOver(void);   // 触发信号的函数
};

Student::Student(QObject *parent) : QObject(parent) {}

// 槽函数的实现
void Student::treat(void){
    qDebug() << "请老师吃饭" ;
}
// 槽函数的实现
void Student::treat(QString foodName){
    qDebug() << "请老师吃饭, 吃" << foodName.toUtf8().data();
}


Teacher::Teacher(QObject *parent) : QObject(parent) {}

// Teacher  类 老师类
// Student  类 学生类
// 老师发送信号, 发送的是饥饿信号, 学生相应信号, 处理这个信号,动作是请老师吃饭(槽)


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->zt = new Teacher(this);
    this->st = new Student(this);

      // 下面只是普通的传递
//    connect(this->zt, &Teacher::hungry, this->st, &Student::treat);
//    classIsOver();
      
    // 带参数的 信号和槽
    void (Teacher::*teacherSignal)(QString) = &Teacher::hungry;
    void (Student::*studentSlot)(QString) = &Student::treat;

    connect(this->zt, teacherSignal, this->st, studentSlot);
  	classIsOver();
}
void Widget::classIsOver(void){
//发送自定义信号
//  emit   zt->hungry();
	  emit   zt->hungry("宫保鸡丁");
}
```



### 按钮发出信号触发自定义的槽函数

- **自定义的槽函数如果有参数,应该使用与按钮绑定的窗口类中的成员函数进行封装.**
  - 也可以使用 Lamdba 表达式来进行, 也非常方便

```c++
#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    // 自定义信号要写到 signals: 区域内
    // 自定义信号没有返回值,  void
    // 只需要声明, 不需要实现
    void hungry(void);    //声明,不可以实现

    void hungry(QString foodName);    //重载信号
};

//触发这里的则是 第二个 connect, 按钮
void Widget::classIsOver(void){
//发送自定义信号
//    emit   zt->hungry();
      emit   zt->hungry("宫保鸡丁"); // 这里实际触发的是第一个connect
}

Widget::Widget(QWidget *parent): QWidget(parent)
{
      // 带参数的 信号和槽
    void (Teacher::*teacherSignal)(QString) = &Teacher::hungry;
    void (Student::*studentSlot)(QString) = &Student::treat;

    // 链接自定义信号和自定义槽, 触发信号就会运行槽函数,这里很重要
    connect(this->zt, teacherSignal, this->st, studentSlot);

    //点击按钮再触发自定义槽函数(槽函数被封装到一个普通函数中,用于传输参数,然后再触发槽函数)
     QPushButton* btn = new QPushButton("下课",this);
     this->resize(400,300);
     connect(btn, &QPushButton::clicked, this, &Widget::classIsOver);
}

```



### 使用Lambda表达式来触发自定义槽函数

```c++
QPushButton* btn = new QPushButton("按钮", this);
connect(btn, &QPushButton::clicked, this, [this,ben3](){  //这里应该传值, 否则会触发锁的bug
  emit QWidget::close();  //显示触发槽函数,也就相当于触发信号
  //也可以触发信号, 但是该信号应该已经连接过某个槽函数了,否则也没效果
  this->close(); //同等 ,就算这里关闭了窗口, 但下面还是会执行, 毕竟不是主进程结束,直接窗口结束
  emit MyClass::myFun("参数");  //这样来将无参信号绑定到有参槽函数上面. myFun是槽函数
  this->setWindowTitle("重设的窗口标题");  //还可以重设窗口名称
  btn3->setText("helloa");   //修改按钮名称,但有时候需要点击两下
}; );
```





### 1信号连接槽函数,2信号再连接1信号

- **如果槽函数带参数,那么需要将1信号连接到一个无参数类的函数成员,这个函数成员封装槽函数即可.**

```c++
   // 带参数的 信号和槽
    void (Teacher::*teacherSignal)(QString) = &Teacher::hungry;
    void (Student::*studentSlot)(QString) = &Student::treat;

    connect(this->zt, teacherSignal, this->st, studentSlot);

//    classIsOver();

    //点击按钮再触发自定义槽函数(槽函数被封装到一个普通函数中,用于传输参数,然后再触发槽函数)
     QPushButton* btn = new QPushButton("下课",this);
     this->resize(400,300);
  //  connect(btn, &QPushButton::clicked, this, &Widget::classIsOver);


    void (Teacher::*teacherSignal2)(void) = &Teacher::hungry;
    void (Student::*studentSlot2)(void) = &Student::treat;
    connect(this->zt, teacherSignal2, this->st, studentSlot2);
    connect(btn, &QPushButton::clicked, this->zt, teacherSignal2);
```



### 断开信号和槽的连接

- `disconnect(里面的参数与connect一模一样)`

```c++
connect(this->zt, teacherSignal2, this->st, studentSlot2);
disconnect(this->zt, teacherSignal2, this->st, studentSlot2);
```











# 按钮和窗口标题以及窗口固定大小

> 应该使用帮助文档索引QPushButton.来寻找按钮.方法
>
> - **`qmake: QT+=widgets` 提示附属于 widgets模块,在工程文件中, 4版本以上都包含了这个模块.**
> - **`inherits: QAbstractButton   按钮类继承于QAbstractButton类`**
> - **`inherited by: QCommandLinkButton 继承按钮类的子类`**

- **窗口操作**
  - **设置固定窗口大小函数,需要在 继承窗口类(QWidget)的子类中构造函数内使用**
    - `this->setFixedSize(400,500);   //400宽度, 500长度`
  - **设置可自由伸缩的窗口大小函数,需要在 继承窗口类(QWidget)的子类中构造函数内使用**
    - `this->resize(400,200);  //宽和高`
  - **重设窗口名称需要在 继承窗口类(QWidget)的子类中构造函数内使用**
    - `this->setWindowTitle("重设的窗口标题");`
- **按钮创建和操作API, 需要在 继承窗口类(QWidget)的子类中构造函数内使用:**
  - **逐步设置的操作,可以避免重置依赖的窗口大小**
    - **创建一个按钮对象**
      - `QPushButton* btn = new QPushButton;  //默认构造函数`
    - <u>**将按钮绑定或依赖在某个窗体中并显示出来的成员函数**</u>
      - `btn->setParent(this); //这个this是主窗体对象,class QWidget;`
    - **让按钮内显示文本**
      - `btn->setText("one");`
  - **一步设置,使用构造函数, 但却需要重置依赖窗口的大小**
    - **创建按钮对象,设置显示文本,设置依赖窗口,并直接显示出来**
      - `QPushButton* btn2 = new QPushButton("two",this);`
  - **移动按钮的位置,使用的坐标轴是主窗口的相对坐标轴原点(左上角).**
    - `btn2->move(0,30);   // 按照主窗口内的相对坐标轴计算 (x,y)`
  - **修改按钮的默认大小**
    - `btn2->resize(40,50); //宽和高`

```c++
/*
 * 下面的代码可以显示一个固定长度的主窗口,以及主窗口上有两个位置不同的按钮. 窗口标题也重设了.
 */

#include <QPushButton>   //QPushButton小部件提供命令按钮, 使用按钮就应该包含这个头文件
#include <QWidget>

class myWidget : public QWidget
{
private:
    Q_OBJECT
/* 这个宏必须出现在类定义的私有部分中,允许该类声明其自身的信号和插槽，或者使用Qt的元对象系统提供的其他服务 */
public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();
};

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
{
    /* 第一个按钮 */
    //创建一个按钮
    QPushButton* btn = new QPushButton;
    {
        // 以顶层方式弹出控件,但不会出现在主窗口中,而且在另一个窗口中弹出,但不应该这么来使用
        // btn->show();

        //设置btn按钮对象 依赖在 myWidget 这个主窗口中. 也就是显示在主窗口上.
        btn->setParent(this);

        //让按钮内显示文本, 文本越长,按钮长度就越长,支持转义字符 \n
        btn->setText("one");
    }


    /* 第二个按钮 */
    //创建第二个按钮,在构造中直接设置显示的 文本和依赖的窗口,
    // 但却会按照按钮的大小来创建窗口,应该重制主窗口大小才能这么用
    QPushButton* btn2 = new QPushButton("two",this);
    {
        //重置窗口大小,左上角为基本坐标原点,正比例增长, (x宽,y高)
        resize(400,200);

        //由于这是第二个按钮,会直接把第一个按钮覆盖掉, 需要挪动这第二个按钮的位置
        btn2->move(0,30);   // 按照主窗口内的相对坐标轴计算 (x,y)
    }


    /* 设置窗口标题 和 固定窗口大小,不允许用户修改 */
    {
        // 这样设置的话,用户可以自由放大和缩小窗口
        setWindowTitle("重设的窗口标题");

        //设置固定窗口大小, 不允许用户改变
        setFixedSize(400,500);   //400宽度, 500长度
    }

}

myWidget::~myWidget()
{
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);  // 应用程序对象
    myWidget w; //窗口对象, myWidget 继承于 QWidget (空窗口基类)
    w.show();   // 调用窗口对象的 show 方法,来显示窗口
    return a.exec();
}
```





## 菜单栏和工具栏

> **需要将项目创建为`MainWindow`, 并且将菜单和工具栏等内容写到 `QMainWindows` 的构造函数内.**
>
> **需要头文件`<QApplication>` ,`<QMainWindow>` , `<QToolBar>` , `<QMenuBar>`**
>
> **`QMainWindow` 是一个为用户提供 主窗口程序的类.包含:**
>
> - **一个菜单栏 (menu bar):**
>   - 头文件`<QMenuBar>`
>   - 创建菜单栏 `QMenuBar* bar = menuBar(); //menuBar()系统函数,返回一个菜单栏对象`
>   - 将菜单栏添加到窗口中 `setMenuBar(bar);`
> - **多个工具栏 (tool bars):**
>   - 头文件`<QToolBar>`
>   - 创建工具栏`QToolBar* toolBar = new QToolBar(this);  //多种构造函数`
>   - 添加到窗口中,并初始化默认停靠位置 `addToolBar(Qt::LeftToolBarArea,toolBar);`
> - **多个铆接部件或浮动窗口部件 (bock windgets):**
>   - 头文件 `<QDockWidget>`
>   - 创建一个铆接部件`QDockWidget* dockWigdet = new QDockWidget("浮动", this);`
>   - `addDockWidget(Qt::BottomDockWidgetArea, dockWigdet);   //独立设置到窗口中, 并设置默认位置,铆接部件的位置是围绕着中心部件 去定位的`
> - **一个状态栏 (status bar):**
>   - 头文件`<QStatusBar>`
>   - 创建一个状态栏 `QStatusBar* stBar  =  statusBar(); `
>   - 添加到窗口中 `setStatusBar(stBar);`
> - **标签控件,可以添加到状态栏中,也可以添加到其他栏中**
>   - 头文件`<QLabel>`
>   - 创建一个标签控件 `QLabel* label = new QLabel("提示信息",this);`
> - **一个中心部件( central widget):**
>   - 头文件`<QTextEdit>`, 其中一种中心部件,文本编辑器
>   - 创建一个中心部件`QTextEdit*edit = new QTextEdit();   //创建一个文本编辑器的中心部件`
>   - 将中心部件添加到窗口中`setCentralWidget(edit);   //设置中心部件`

```c++
 #include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTextEdit>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,400);  //重制窗口大小


/* 菜单栏 */
    //创建菜单栏  menu Bar, 该对象只可以存在一个
    QMenuBar* bar =  menuBar();  //系统提供的方法,会直接在对象树上

    //将菜单栏放入窗口中,与绑定类似, 系统提供的方法
    // 目前还是空栏, 所以什么都不显示
    setMenuBar(bar) ;

    //创建菜单栏中的 菜单(方法) ,返回值QMenu可以用来创建菜单项, 也就是二级页面
    QMenu *fileMenu =  bar->addMenu("文件");
    QMenu *editMenu =  bar->addMenu("编辑");

    // 菜单栏中的方法, 必须拥有菜单项才可以显示出来(macos)
    // 点击菜单栏中的文件,就会在文件下面弹出二级页面,里面就会出现新建
    // 存在多个时,会按照顺序创建
    // QAction* 返回值是给工具栏使用的, 可以让工具栏拥有和这个 菜单选项相同的功能
    QAction* newAction =  fileMenu->addAction("新建");
    fileMenu->addSeparator();  //分隔符,分割二级页面中相邻的两项,可以更直观的看到内容
    QAction* openAction = fileMenu->addAction("打开");
    editMenu->addAction("全选");

    //在 文件 菜单栏中创建 历史二级页面, 这个历史里面会存在一个三级页面
    QMenu* fileMenu1 =  fileMenu->addMenu("历史");

    //在三级页面中创建一个方法
    fileMenu1->addAction("最近历史");
      
    //点击新建会重命名 主窗口名称, 信号和槽, 发送 truggered 信号(点击菜单栏的新建),  会弹出一个对话框
    // ui->actionnew 就是 newAction   ,是菜单项
    connect(ui->actionnew, &QAction::triggered, [=](){
			setWindowTitle("newWin");
    });


/* 工具栏 */
    //创建工具栏, 可以存在多个 .
    QToolBar* toolBar = new QToolBar(this);

    // 将工具栏添加到窗口 也可以初始化默认停靠位置
    addToolBar(Qt::LeftToolBarArea,toolBar);

    //后期设置, 只允许工具栏左右停靠, 但却可以完全不停靠,直接浮动
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea /*| Qt::AllToolBarAreas */) ;

    // 设置浮动开关, 不允许工具栏进行浮动了,false 就是不允许在任意位置浮动,必须停靠
    toolBar->setFloatable(false);

    // 设置移动开关, false 就是不允许移动,也不允许浮动. 哪怕再次设置浮动,也不可以进行移动
    toolBar->setMovable(false);

    //在工具栏中添加内容, 可以添加对象或文本选项 以及对应的槽函数
    toolBar->addAction(newAction);
    toolBar->addSeparator();   // 分割线
    toolBar->addAction(openAction);

    //工具栏中 添加控件(按钮就是控件)
    QPushButton* btn = new QPushButton("按钮",this);
    toolBar->addWidget(btn); // 按钮会出现在工具栏中,并且自动调整好大小和位置



/* 状态栏 和 标签控件*/
    //状态栏最多只有一个, 系统提供的方法.
    QStatusBar* stBar  =  statusBar();

    //设置到窗口中
    setStatusBar(stBar);

    //创建一个 标签控件
    QLabel* label = new QLabel("提示信息",this);

    //将标签放入状态栏中, 默认从左到右
    stBar->addWidget(label);

    QLabel* lable2 = new QLabel("右侧提示信息", this);

    //将标签放入状态栏中, 默认从右到左
    stBar->addPermanentWidget(lable2);

    QLabel* lable3 = new QLabel("333", this);
    stBar->addPermanentWidget(lable3);


/* 铆接部件(浮动窗口),和中心部件 , 铆接部件的位置是围绕着 中心部件 去定位的*/
    // 创建铆接部件,并添加到窗口中,  也可以独立设置到窗口中
    QDockWidget* dockWigdet = new QDockWidget("浮动", this);
    addDockWidget(Qt::BottomDockWidgetArea, dockWigdet);   //独立设置到窗口中, 并设置默认位置,铆接部件的位置是围绕着中心部件 去定位的
    dockWigdet->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);  // 设置浮动窗口只可以停留在上面或下面


    //设置中心部件
    QTextEdit*edit = new QTextEdit();   //创建一个文本编辑器的中心部件
    setCentralWidget(edit);   //设置中心部件
}

MainWindow::~MainWindow()
{
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

```









## 网络

> `QUdpSocket, 和 QTcpSocket 以及 QTcpServer`



## QString转chat*

- QString 会直接输出数据并添加两个 引号
  - char* 并不会.

```c++
QString s = "asdasd";  std::cout << s.toUtf8().data();
```





## 添加QT资源文件

- 先把资源(图片之类的) 复制到当前项目中
- 随后在 QT的IDE编辑器 项目 中添加新文件
  - 会弹出一个选择模版
    - 选择 `Qt`
    - **再选择`Qt resource File` 资源文件**
  - 随后给资源名称命名. 例如叫 `res`
  - 会创建一个 叫 `res.qrc` 文件( . qrc 就是QT下的资源文件的后缀名)
- 在IDE的项目中会出现一个 `Resources` 的目录, 使用右键点击 `Open in editor` 打开目录下的文件
  - 在下方会有个 `Add Prefix` 添加前缀,点击它添加资源
    - 属性内的前缀是 : `对类型的区分`
      - 不想区分的话,给个 `/` 即可
  - 添加前缀后再点击 `Add Files` 添加资源文件
    - 在弹出的窗口内选择多个需要添加的文件( 图片之类的)
- 添加完成后, 编译一次, 资源的图片内容都会存放在项目内了

- 使用时 用字符串初始化`QIcon` 类
  - 字符串表示资源所在的目录的位置 格式为 `":前缀名 + 相对路径"`
    - `QIcon(":/png/1.png"); //  :  前缀名是 / ,png/1.png是相对路径`

```c++
ui->setupUi(this);  

//添加Qt资源, 将按钮变成图标
ui->actionNew->setIcon(QIcon(":/1/png/1.png"));   
// : 标准写法  / 是前缀  png/1.png 是资源文件的相对路径
// actionNew 是在ui文件中建立的菜单栏中的菜单项,也是工具栏

ui->actionopen->setIcon(QIcon(":/2/2/pp.png"));
```





## 对话框

- 对话框分为两类.模态对话框与非模态对话框
  - 头文件`<QDialog>`
- **模态对话框:**
  - **在对话框弹出后,不可以对其他的任何窗口进行操作.**
  - 创建一个对话框 对象,可以放在栈上`QDialog dlg (this);`
  - 弹出对话框并进行阻塞  `dlg.exec(); //运行到这里之后,会进行阻塞, 等待这个对话框任务结束`
- **非模态对话框:**
  - **对话框弹出后,还可以对其他窗口进行操作和点击**
  - 创建一个对话框对象,应该放在堆上 `QDialog* dlg2 =  new QDialog (this);`
    - **这样的创建多次点击就多次创建, 下面是单例模式,一次点击只出现一次**
    - `static QDialog* dlg2 =  new QDialog (this);`
  - **弹出对话框, 但不会进行阻塞 `dlg2->show();`**

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 发送 truggered 信号(点击菜单栏的新建),  会弹出一个对话框
    connect(ui->actionnew, &QAction::triggered, [=](){

        /*
         * 创建模态对话框, 对话框弹出后,不可以点击其他窗口
         */
        {
                QDialog dlg (this);
                dlg.resize(150,140);    // 重制一下 对话框大小,应该大于116*670
                dlg.exec();             //运行到这里之后,会进行阻塞, 等待这个对话框任务结束
                qDebug() << "模态对话框";
        }

        /*
         * 创建 非模态对话框, 对话框弹出后,可以点击其他窗口, 可以弹出多个相同的 对话框
         */
        {
            QDialog* dlg2 =  new QDialog (this);
            dlg2->show();
            dlg2->setAttribute(Qt::WA_DeleteOnClose);  //设置属性, 关闭对话框时,释放这个对象内存
            qDebug() << "非模态对话框";
        }

        /*
         * 创建 非模态对话框, 对话框弹出后,可以点击其他窗口, 只可以弹出一个对话框,但却占用固定内存,并且不可以手动释放掉
         */
        {
            static QDialog* dlg2 =  new QDialog (this);
            dlg2->show();
            qDebug() << "非模态对话框";
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


```





## 标准对话框

- **标注对话框就是 Qt内置的一系列对话框, 包括:**
  - `QColorDialog`  选择颜色 (非模态), 头文件`<QColorDialog>`
  - `QFileDialog`  选择文件或目录(非模态),头文件 `<QFileDialog>`
  - `QFontDialog`  选择字体(非模态)
  - **`QInputDialog`   允许用户输入一个值, 并将其值返回(非模态)**
  - **`QMessageBox` 消息对话框,用于显示信息, 询问问题等(模态).**
    - `Question` 问题消息
    - `Information` 信息消息
    - `Warning`  警告消息
    - `Critical` 错误消息

```c++
QMessageBox 拥有静态公有成员函数, 通过返回值可以判断用户按了什么按钮.
  错误消息成员: criticel(父窗口, 标题, 显示文本内容, 出现的按钮, 回车默认按钮)
 if (QMessageBox::Ok == \
     QMessageBox::critical(this, "critical", "错误" ,QMessageBox::Ok, QMessageBox::Ok)) 
	   { ... /* 判断用户按了 ok 按钮  */ }

选择颜色对话框
  QColor color =  QColorDialog::getColor(QColor(255,0,0)); //获得选择的颜色 rgb
	qDebug() << "r = " <<  color.red()  << "g = " << color.green() << "b = " << color.blue();
   

文件选择对话框(父窗口, 窗口标题, 默认打开路径, 只选择图片文件后缀是.png .xpm .jpg文件, ) ;  
	 只可以选择单个文件, getOpenFileNames 可以选择多个文件
返回的是这个文件的 绝对路径和名称   /Users/Shared/a.txt
  QString str =  QFileDialog::getOpenFileName(this, "打开文件", tr("/Users/Shared"), tr("*.txt"));
  qDebug() << str;


字体选择对话框 (是否选择成功, 默认字体和字号, 父窗口, 窗口标题);  返回选择的字体和字号 QFont 栈对象
  bool flag = false;
  QFont font =  QFontDialog::getFont(&flag, QFont("Hei", 22),this, "选择");
  qDebug() << font.family().toUtf8().data() << " ,size = " << font.pointSize()
            << ", 是否加粗" << font.bold() << ", 是否倾斜 " << font.italic()  
            << "是否又下划线" << font.underline();
			/* 输出 字体 和字号 */

```







## 界面布局

- 使用 `Label` 标签 显示用户名和密码输入提示
- 将按钮之类的控件聚集后单独的放入一个独立的 `Widget` 中可以更好的布局

- 弹簧选择  `sizeTyep`  选项中, `Fixed` 可以将弹簧的值固定. 让控件之间的距离更好控制
- 将窗口的最大与最小值都设置成相同的值,就可以达到固定窗口,不可缩放的目的. (`minimumSize` 与`macimumsSize`)
- 用户输入框应该选择 `Line Edit` 控件. 密文输入的话选择属性中的  `echoMode = password`
  - Linux下的密码输入会看不到, 所以应该选择 `echoMode = NoEcho`







## 按钮控件

- `Tool Button`  工具按钮, 一般用来显示图片和说明.比 `Push Button` 要好用一些
  - **`QToolButton` 工具按钮类, 用于显示图片和文字.**
    - `toolButtonStyle`   突起风格 `autoRaise`
- **`Radio Button` 是单选框, 以当前所在窗口为基础, 只能选择一个**
  - 可以使用控件 `Group Box` 来达到在一个窗口中 拥有多个单选框,并且相对独立的控件.
  - `ui->QRadioButton对象指针->setChecked(true); //设置默认选择单选项`
  - 开启 `autoRsize` 选项,可以达到 鼠标放在按钮时有个凸起的效果, 鼠标移开后,恢复与背景相同颜色.
- **`Check Box`  复选框. 也是以当前所在窗口为基础, 能同时选择多个. 与`Radio Button` 不会发生冲突**
  - 可以使用控件 `Group Box` 来达到在一个窗口中 拥有多个复选框,并且相对独立的控件.
  - 使用信号和槽和组合 可以监听复选框的状态
    - `connect(ui->boxOne, &QCheckBox::stateChanged, [=](int i){qDebug() << "check one = " << i ;}); // 多选框, 反馈 2 1 0 这三种内容`
    - 开启 `QcheckBox` 中的 `tristate` 选项即可看到 1这个半选状态, 一般只会有0 和2.
      - **2 选中, 1 半选, 0 未选择**





## 基于模型-包括数据库的排列控件

- 使用 `Item Views` 下的控件 `List view` ,  `Tree view`, `Table view`, `Column View`  来到达目的.里面可以排列从数据库返回的数据

- 使用方式与下面 [基于项目排列控件](#基于项目排列控件) 相同





## 基于对象项目的排列控件

- 使用 `Item Widgets` 下的控件`List Widget` ,  `Tree Widget`, `Table Widget` 来实现. `QListWidget`
- **`List Widget`  显示文本, 其中的数据每行都基于 `QListWidgetItem` 这个对象**
- `Tree Widget`  以树形方式显示文本, 类似小箭头的下拉方式
- `Table Widget`  表格方式显示

```c++
/* List Widget  控件*/
/*  第一种创建数据并添加到控件中的方式 */
    {
        //创建一行数据, 准备放到 listWigetd 控件中
        QListWidgetItem* item = new QListWidgetItem("显示的内容");
        QListWidgetItem* item2 = new QListWidgetItem("显示的内容2");

        //设置显示内容的格式. 居中, QListWidgetItem 对象
        item->setTextAlignment(0x0004);

        // listWigetd 控件中, 并且显示出来,  显示出来的内容可以被用户复制
        ui->listWidget->addItem(item);
        ui->listWidget->addItem(item2);
    }
/*  第二种创建数据并添加到控件中的方式, 方便但不可以设置字符显示格式 */
    {
      // 通过这个容器来进行添加,  也可以直接用字符串添加.
        QStringList list;
        list << "可以用拼接" << "的方式" << "来显示字符串"  << "但都是分行显示的,并不会显示在同一行";
        ui->listWidget->addItems(list);
    }
```



```c++
/* TreeWidget 树控件的使用 */
    {
        //设置顶部表中的列, 创建了两个列,  英雄, 简介.
        ui->treeWidget->setHeaderLabels(QStringList() << "英雄" <<  "简介");

        // 创建一个节点(也是头,也是节点),  里面保存数据内容, 前面设置为头 , 注意 列 的数量
        QTreeWidgetItem * liItem = new QTreeWidgetItem(QStringList() << "力量");
        QTreeWidgetItem * mjItem = new QTreeWidgetItem(QStringList() << "敏捷");
        QTreeWidgetItem * zlItem = new QTreeWidgetItem(QStringList() << "智力");

        // 这个设置为节点,以 liItem 为头. 创建方式和头相同, 只不过使用方式不同罢了, 注意 列 的数量
        QTreeWidgetItem *li1 = new QTreeWidgetItem(QStringList() << "德玛" << "很肉" );

        // 添加 li1 节点到 liItem
        liItem->addChild(li1);

        // 将上面创建的树 添加到 treeWidget 表中, 并显示出来
        ui->treeWidget->addTopLevelItem(liItem);  // 因为他拥有节点, 所以前面会有个三角,能折叠
        ui->treeWidget->addTopLevelItem(mjItem);
        ui->treeWidget->addTopLevelItem(zlItem);
    }
```

```c++
/* TableWidget 表格 */
    {
        // 先设置 列 的数量, 也就是 top 标签的数量, 跟任务管理的  | cup使用率 | 内存使用率 | ... 等等 的数量
        ui->tableWidget->setColumnCount(3);

        // 设置水平表头显示的名称, 就是顶部的标签名称
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "名称" << "性别" << "年龄" );

        //设置行数
        ui->tableWidget->setRowCount(5);

        //添加数据, 每个数据都是 TableWidgetItem
        ui->tableWidget->setItem(0,0, new QTableWidgetItem("0%"));

        // 下面是两种可以插入的数据. (相同的)
        QStringList nameList;
        nameList << "10%" << "20%" << "30%" << "40%" << "50%" ;

        QList<QString> sexList;
        sexList << "男" << "男" << "男"  << "女" << "未知";


        //用for 循环添加数据. j是列, i是行
        for(int i =0 ; i <5 ; i++){
            int j = 0;
            ui->tableWidget->setItem(i,j++, new QTableWidgetItem(nameList[i]));
            ui->tableWidget->setItem(i,j++, new QTableWidgetItem(sexList.at(i)));
            ui->tableWidget->setItem(i,j++, new QTableWidgetItem(QString::number(i+18)));
        }
    }
```





## 其他的一些窗口控件

### 可滚动区域窗口控件

- 就是一个窗口控件, 里面控件或按钮之类的内容很多的话,会出现滚动条而已
- `Scroll Area` 控件,  是 `QScrollArea` 类型



### 分组窗口控件

- 类似于 05年的QQ 界面, 好友,黑名单, 群 之类多个页面共用一个窗口位置, 可以反复替换和显示
  - 里面的内容按照页来进行区分
- `Tool Box` 控件
  - 控件中的子控件 `Qwidget` 可以通过 `toolBox` 控件中的 `currentIndex` 来进行选择
    - 然后在 `currentItemText` 来修改子标签显示的名称
    - `currentItemName` 是子标签的 对象名



### 网页标签类窗口控件

- `Tab Widget` 控件,  和浏览器的窗口标签非常类似
  - `currentIndex` 选择某个子标签
  - `currentTabText`  子标签显示的名称
  - `currentTabName` 子标签的对象名



### 分页标签类窗口控件

- `Stacked Widget` 控件, 与 网页标签类 相似.  需要一个按钮来控制页面间的转换

```c++
    //设置默认界面
    ui->stackedWidget->setCurrentIndex(1);

// 按钮来控制界面切换
    connect(ui->btn_toolBox, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btn_scrollArea, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
```



### 下拉框-常用

- `Combo Box` 带小三角的按钮, 会出现下拉选项. 使用代码可以在下拉框中添加内容

```c++
    {
        ui->comboBox->addItem("a");
        ui->comboBox->addItem("b");
        ui->comboBox->addItem("c");
        ui->comboBox->addItem("e");
        ui->comboBox->addItem("d");

        // 使用按钮来进行快速选择
        connect(ui->btn_setC, &QPushButton::clicked, [=](){
            // 使用索引进行选择
//            ui->comboBox->setCurrentIndex(2);

            //使用文本进行选择
            ui->comboBox->setCurrentText("c");

            // 使用按钮选择之后可能会出现无动作现象, 这个时候隐藏一下,再显示一下, 相当于刷新按钮了
            ui->comboBox->hide();
            ui->comboBox->show();
        });
    }
```





## 自定义封装控件

- **添加Qt设计师界面类(ui)**
  - 在新ui 界面添加 `QSlider` (Spin Box) 旋转框小部件  和 `QSpinBox` (horizontal Scroll Bar) 水平进度条滑块控件. 在这里面设计控件
- 然后在主窗口 `Widget` 中使用自定义控件
  - 添加一个 `Widget` 控件
  - 选择 提升
  - 添加 `Qt` 新界面的类名和头文件
  - 选中后即可提升.为自定义控件
- **自定义控件应该实现相对于的功能, 以及给主窗口调用的API接口.**

```c++
    //spinBox 是QSpinBox 控件,  horizontalSlider 是QSlider 控件,
    // spinBox 数值改变时,进度条进行相对位置的移动 0-99  (可以修改成100)
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->horizontalSlider ,&QSlider::setValue);
		
{  /* 还可以这么写 */     
  void (QSpinBox::*fun)(int) = &QSpinBox::valueChanged;
	connect(ui->spinBox, fun , ui->horizontalSlider ,&QSlider::setValue);
}

  // 进度条进行位置的移动时, spinBox 数值改变
    connect(ui->horizontalSlider, &QSlider::sliderMoved, ui->spinBox, &QSpinBox::setValue);
```

