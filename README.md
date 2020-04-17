## 目录

- [QT笔记](#QT笔记)
- [信号和槽](#信号和槽)
  - [自定义信号和槽](#自定义信号和槽)
  - [按钮发出信号触发自定义的槽函数](#按钮发出信号触发自定义的槽函数)
  - [使用Lambda表达式来触发自定义槽函数](#使用Lambda表达式来触发自定义槽函数)
  - [1信号连接槽函数,2信号再连接1信号](#1信号连接槽函数,2信号再连接1信号)
  - [断开信号和槽的连接](#断开信号和槽的连接)
- [头文件说明](#头文件说明)
- [工程文件说明](#工程文件说明)
- [详细类对象说明](#详细类对象说明)
- [宏和类说明](#宏和类说明)
- [按钮和窗口标题以及窗口固定大小](#按钮和窗口标题以及窗口固定大小)
- [网络](#网络)
- [QString转chat*](#QString转chat*)
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

- **优点**
  - **跨平台.**
  - **接口简单,容易上手**
  - **一定程度上简化了内存回收**

- **显示中文时, 一定要设置UTF-8来进行输出**





## 信号和槽

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
  - 
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





## 头文件说明

```c++
<QApplication>  包含一个应用程序类的头文件 
<QWidget>       窗口类
<QPushButton>   使用按钮需要包含该头文件  QPushButton
<QMenuBar>      菜单栏头文件   QMenuBar
<QToolBar>      工具栏头文件   QToolBar
<QLabel>        状态栏提示信息文本
<QStatusBar>    状态栏
<QDockWidget>   浮动窗口(铆接部件)
<QTextEdit>     文本编辑器(可以是核心部件)
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





# 网络

> `QUdpSocket, 和 QTcpSocket 以及 QTcpServer`



## QString转chat*

- QString 会直接输出数据并添加两个 引号
  - char* 并不会.

```c++
QString s = "asdasd";  std::cout << s.toUtf8().data();
```

