//该类用于动态切割窗口
#include <QSplitter>
//成员函数
void addWidget(QWidget *widget);                    //在所有其他项之后将给定的小部件添加到拆分器的布局中。
void insertWidget(int index, QWidget *widget);      //将指定的小部件插入到给定索引处拆分器的布局中。
void setChildrenCollapsible(bool);                  //此属性保存用户是否可以将子部件的大小调整为0。
void setStretchFactor(int index, int stretch);      //更新小部件在位置索引处的大小策略，使其具有拉伸因子。

