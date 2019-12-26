qt qtableview基本用法

QTableView常用于实现数据的表格显示。下面我们如何按步骤实现学生信息表格：

一 添加表头

    //准备数据模型
    QStandardItemModel *student_model = new QStandardItemModel();
    student_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Name")));
    student_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("NO.")));
    student_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Sex")));
    student_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("Age")));
    student_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("College")));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->student_tableview->setModel(student_model);


二 设置表格属性

    //设置列宽不可变动，即不能通过鼠标拖动增加列宽        
    ui->student_tableview->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(2, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);   

    //设置表格的各列的宽度值        
    ui->student_tableview->setColumnWidth(0,100);    
    ui->student_tableview->setColumnWidth(1,100);    
    ui->student_tableview->setColumnWidth(2,100);    
    ui->student_tableview->setColumnWidth(3,100);    
    ui->student_tableview->setColumnWidth(4,100);       

    //默认显示行头，如果你觉得不美观的话，我们可以将隐藏        
    ui->student_tableview->verticalHeader()->hide();      

    //设置选中时为整行选中        
    ui->student_tableview->setSelectionBehavior(QAbstractItemView::SelectRows);         
      
    //设置表格的单元为只读属性，即不能编辑        
    ui->student_tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);          

    //如果你用在QTableView中使用右键菜单，需启用该属性        
    ui->tstudent_tableview->setContextMenuPolicy(Qt::CustomContextMenu);

 

三 动态添加行

    在表格中添加行时，我们只需要在model中插入数据即可，一旦model中的数据发生变化，QTabelView显示就会做相应的变动

    //在第一行添加学生张三的个人信息(setItem函数的第一个参数表示行号，第二个表示列号，第三个为要显示的数据)
    student_model->setItem(0, 0, new QStandardItem(“张三"));
    student_model->setItem(0, 1, new QStandardItem("20120202"));
    student_model->setItem(0, 2, new QStandardItem("男"));
    student_model->setItem(0, 3, new QStandardItem("18"));
    student_model->setItem(0, 4, new QStandardItem("土木学院"));


四 设置数据显示的样式

    //设置单元格文本居中，张三的数据设置为居中显示
    student_model->item(0, 0)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 3)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 4)->setTextAlignment(Qt::AlignCenter);

    //设置单元格文本颜色，张三的数据设置为红色
    student_model->item(0, 0)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 1)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 2)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 3)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 4)->setForeground(QBrush(QColor(255, 0, 0)));

    //将字体加粗
    student_model->item(0, 0)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 1)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 2)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 3)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 4)->setFont( QFont( "Times", 10, QFont::Black ) );

    //设置排序方式，按年龄降序显示
    student_model->sort(3, Qt::DescendingOrder);

二、

QTableWidget是QT程序中常用的显示数据表格的空间，很类似于VC、C#中的DataGrid。说到QTableWidget，就必须讲一下它跟QTabelView的区别了。QTableWidget是QTableView的子类，主要的区别是QTableView可以使用自定义的数据模型来显示内容(也就是先要通过setModel来绑定数据源)，而QTableWidget则只能使用标准的数据模型，并且其单元格数据是QTableWidgetItem的对象来实现的(也就是不需要数据源，将逐个单元格内的信息填好即可)。这主要体现在QTableView类中有setModel成员函数，而到了QTableWidget类中，该成员函数变成了私有。使用QTableWidget就离不开QTableWidgetItem。QTableWidgetItem用来表示表格中的一个单元格，正个表格都需要用逐个单元格构建起来。


view plain
#include <QtGui/QApplication> 
#include <QTableWidget> 
#include <QTableWidgetItem> 

int main(int argc, char *argv[]) 
{ 
QApplication a(argc, argv); 
QTableWidget *tableWidget = new QTableWidget(10,5); // 构造了一个QTableWidget的对象，并且设置为10行，5列 
// 也可用下面的方法构造QTableWidget对象 
// QTableWidget *tableWidget = new QTableWidget; 
// tableWidget->setRowCount(10); //设置行数为10 
// tableWidget->setColumnCount(5); //设置列数为5 
tableWidget->setWindowTitle("QTableWidget & Item"); 
tableWidget->resize(350, 200); //设置表格 
QStringList header; 
header<<"Month"<<"Description"; 
tableWidget->setHorizontalHeaderLabels(header); 
tableWidget->setItem(0,0,new QTableWidgetItem("Jan")); 
tableWidget->setItem(1,0,new QTableWidgetItem("Feb")); 
tableWidget->setItem(2,0,new QTableWidgetItem("Mar")); 

tableWidget->setItem(0,1,new QTableWidgetItem(QIcon("images/IED.png"), "Jan's month")); 
tableWidget->setItem(1,1,new QTableWidgetItem(QIcon("images/IED.png"), "Feb's month")); 
tableWidget->setItem(2,1,new QTableWidgetItem(QIcon("images/IED.png"), "Mar's month")); 
tableWidget->show(); 

return a.exec(); 
} 






一. 对QTableWidget本身的效果实现 

1. 将表格变为禁止编辑

在默认情况下，表格里的字符是可以更改的，比如双击一个单元格，就可以修改原来的内容，如果想禁止用户的这种操作，让这个表格对用户只读，可以这样：

tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



QAbstractItemView.NoEditTriggers是QAbstractItemView.EditTrigger枚举中的一个，都是触发修改单元格内容的条件：

QAbstractItemView.NoEditTriggers 
0 
No editing possible. 不能对表格内容进行修改

QAbstractItemView.CurrentChanged 
1 
Editing start whenever current item changes.任何时候都能对单元格修改

QAbstractItemView.DoubleClicked 
2 
Editing starts when an item is double clicked.双击单元格

QAbstractItemView.SelectedClicked 
4 
Editing starts when clicking on an already selected item.单击已选中的内容

QAbstractItemView.EditKeyPressed 
8 
Editing starts when the platform edit key has been pressed over an item.

QAbstractItemView.AnyKeyPressed 
16 
Editing starts when any key is pressed over an item.按下任意键就能修改

QAbstractItemView.AllEditTriggers 
31 
Editing starts for all above actions.以上条件全包括





2. 设置表格为整行选择 

tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式

QAbstractItemView.SelectionBehavior枚举还有如下类型

Constant 
Value 
Description

QAbstractItemView.SelectItems 
0 
Selecting single items.选中单个单元格

QAbstractItemView.SelectRows 
1 
Selecting only rows.选中一行

QAbstractItemView.SelectColumns 
2 
Selecting only columns.选中一列




3.单个选中和多个选中的设置：

tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //设置为可以选中多个目标

该函数的参数还可以是：

QAbstractItemView.NoSelection 不能选择

QAbstractItemView.SingleSelection 选中单个目标

QAbstractItemView.MultiSelection 选中多个目标

QAbstractItemView.ExtendedSelection QAbstractItemView.ContiguousSelection 的区别不明显，主要功能是正常情况下是单选，但按下Ctrl或Shift键后，可以多选



4. 表格表头的显示与隐藏

对于水平或垂直方法的表头，可以用以下方式进行 隐藏/显示 的设置：
view plain
tableWidget->verticalHeader()->setVisible(false); //隐藏列表头 
tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头 

注意：需要 #include <QHeaderView>



5. 对表头文字的字体、颜色进行设置 
view plain
QTableWidgetItem *columnHeaderItem0 = tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象 
columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体 
columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色 
columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色 

注意：需要 #include <QHeaderView>



6. 在单元格里加入控件：

QTableWidget不仅允许把文字加到单元格，还允许把控件也放到单元格中。比如，把一个下拉框加入单元格，可以这么做：
view plain
QComboBox *comBox = new QComboBox(); 
comBox->addItem("Y"); 
comBox->addItem("N"); 
tableWidget->setCellWidget(0,2,comBox); 


二. 对单元格的进行设置 

1. 单元格设置字体颜色和背景颜色 及字体字符
view plain
QTableWidgetItem *item = new QTableWidgetItem("Apple"); 
item->setBackgroundColor(QColor(0,60,10)); 
item->setTextColor(QColor(200,111,100)); 
item->setFont(QFont("Helvetica")); 
tableWidget->setItem(0,3,item); 

另：如果需要对所有的单元格都使用这种字体，则可以使用 tableWidget->setFont(QFont("Helvetica"));

2. 设置单元格内文字的对齐方式

这个比较简单，使用newItem.setTextAlignment()函数即可，该函数的参数为单元格内的对齐方式，和字符输入顺序是自左相右还是自右向左。

水平对齐方式有：
Constant Value Description
Qt.AlignLeft 0x0001 Aligns with the left edge.
Qt.AlignRight 0x0002 Aligns with the right edge.
Qt.AlignHCenter 0x0004 Centers horizontally in the available space.
Qt.AlignJustify 0x0008 Justifies the text in the available space.



垂直对齐方式：
Constant Value Description
Qt.AlignTop 0x0020 Aligns with the top.
Qt.AlignBottom 0x0040 Aligns with the bottom.
Qt.AlignVCenter 0x0080 Centers vertically in the available space.


如果两种都要设置，只要用 Qt.AlignHCenter | Qt.AlignVCenter 的方式即可 



3. 合并单元格效果的实现：

tableWidget->setSpan(0, 0, 3, 1) # 其参数为： 要改变单元格的 1行数 2列数 要合并的 3行数 4列数



4. 设置单元格的大小

首先，可以指定某个行或者列的大小
view plain
tableWidget->setColumnWidth(3,200); 
tableWidget->setRowHeight(3,60); 

还可以将行和列的大小设为与内容相匹配
view plain
tableWidget->resizeColumnsToContents(); 
tableWidget->resizeRowsToContents(); 


5. 获得单击单元格的内容 

通过实现 itemClicked (QTableWidgetItem *) 信号的槽函数，就可以获得鼠标单击到的单元格指针，进而获得其中的文字信息

connect(tableWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this, SLOT( getItem(QTreeWidgetItem*,int)) );

//将itemClicked信号与函数getItem绑定