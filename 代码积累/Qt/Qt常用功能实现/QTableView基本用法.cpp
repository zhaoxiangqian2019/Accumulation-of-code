qt qtableview�����÷�

QTableView������ʵ�����ݵı����ʾ������������ΰ�����ʵ��ѧ����Ϣ���

һ ��ӱ�ͷ

    //׼������ģ��
    QStandardItemModel *student_model = new QStandardItemModel();
    student_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Name")));
    student_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("NO.")));
    student_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Sex")));
    student_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("Age")));
    student_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("College")));
    //����setModel()����������ģ����QTableView��
    ui->student_tableview->setModel(student_model);


�� ���ñ������

    //�����п��ɱ䶯��������ͨ������϶������п�        
    ui->student_tableview->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(2, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);   
    ui->student_tableview->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);   

    //���ñ��ĸ��еĿ��ֵ        
    ui->student_tableview->setColumnWidth(0,100);    
    ui->student_tableview->setColumnWidth(1,100);    
    ui->student_tableview->setColumnWidth(2,100);    
    ui->student_tableview->setColumnWidth(3,100);    
    ui->student_tableview->setColumnWidth(4,100);       

    //Ĭ����ʾ��ͷ���������ò����۵Ļ������ǿ��Խ�����        
    ui->student_tableview->verticalHeader()->hide();      

    //����ѡ��ʱΪ����ѡ��        
    ui->student_tableview->setSelectionBehavior(QAbstractItemView::SelectRows);         
      
    //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭        
    ui->student_tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);          

    //���������QTableView��ʹ���Ҽ��˵��������ø�����        
    ui->tstudent_tableview->setContextMenuPolicy(Qt::CustomContextMenu);

 

�� ��̬�����

    �ڱ���������ʱ������ֻ��Ҫ��model�в������ݼ��ɣ�һ��model�е����ݷ����仯��QTabelView��ʾ�ͻ�����Ӧ�ı䶯

    //�ڵ�һ�����ѧ�������ĸ�����Ϣ(setItem�����ĵ�һ��������ʾ�кţ��ڶ�����ʾ�кţ�������ΪҪ��ʾ������)
    student_model->setItem(0, 0, new QStandardItem(������"));
    student_model->setItem(0, 1, new QStandardItem("20120202"));
    student_model->setItem(0, 2, new QStandardItem("��"));
    student_model->setItem(0, 3, new QStandardItem("18"));
    student_model->setItem(0, 4, new QStandardItem("��ľѧԺ"));


�� ����������ʾ����ʽ

    //���õ�Ԫ���ı����У���������������Ϊ������ʾ
    student_model->item(0, 0)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 3)->setTextAlignment(Qt::AlignCenter);
    student_model->item(0, 4)->setTextAlignment(Qt::AlignCenter);

    //���õ�Ԫ���ı���ɫ����������������Ϊ��ɫ
    student_model->item(0, 0)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 1)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 2)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 3)->setForeground(QBrush(QColor(255, 0, 0))); 
    student_model->item(0, 4)->setForeground(QBrush(QColor(255, 0, 0)));

    //������Ӵ�
    student_model->item(0, 0)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 1)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 2)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 3)->setFont( QFont( "Times", 10, QFont::Black ) );
    student_model->item(0, 4)->setFont( QFont( "Times", 10, QFont::Black ) );

    //��������ʽ�������併����ʾ
    student_model->sort(3, Qt::DescendingOrder);

����

QTableWidget��QT�����г��õ���ʾ���ݱ��Ŀռ䣬��������VC��C#�е�DataGrid��˵��QTableWidget���ͱ��뽲һ������QTabelView�������ˡ�QTableWidget��QTableView�����࣬��Ҫ��������QTableView����ʹ���Զ��������ģ������ʾ����(Ҳ������Ҫͨ��setModel��������Դ)����QTableWidget��ֻ��ʹ�ñ�׼������ģ�ͣ������䵥Ԫ��������QTableWidgetItem�Ķ�����ʵ�ֵ�(Ҳ���ǲ���Ҫ����Դ���������Ԫ���ڵ���Ϣ��ü���)������Ҫ������QTableView������setModel��Ա������������QTableWidget���У��ó�Ա���������˽�С�ʹ��QTableWidget���벻��QTableWidgetItem��QTableWidgetItem������ʾ����е�һ����Ԫ�����������Ҫ�������Ԫ�񹹽�������


view plain
#include <QtGui/QApplication> 
#include <QTableWidget> 
#include <QTableWidgetItem> 

int main(int argc, char *argv[]) 
{ 
QApplication a(argc, argv); 
QTableWidget *tableWidget = new QTableWidget(10,5); // ������һ��QTableWidget�Ķ��󣬲�������Ϊ10�У�5�� 
// Ҳ��������ķ�������QTableWidget���� 
// QTableWidget *tableWidget = new QTableWidget; 
// tableWidget->setRowCount(10); //��������Ϊ10 
// tableWidget->setColumnCount(5); //��������Ϊ5 
tableWidget->setWindowTitle("QTableWidget & Item"); 
tableWidget->resize(350, 200); //���ñ�� 
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






һ. ��QTableWidget�����Ч��ʵ�� 

1. ������Ϊ��ֹ�༭

��Ĭ������£��������ַ��ǿ��Ը��ĵģ�����˫��һ����Ԫ�񣬾Ϳ����޸�ԭ�������ݣ�������ֹ�û������ֲ���������������û�ֻ��������������

tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



QAbstractItemView.NoEditTriggers��QAbstractItemView.EditTriggerö���е�һ�������Ǵ����޸ĵ�Ԫ�����ݵ�������

QAbstractItemView.NoEditTriggers 
0 
No editing possible. ���ܶԱ�����ݽ����޸�

QAbstractItemView.CurrentChanged 
1 
Editing start whenever current item changes.�κ�ʱ���ܶԵ�Ԫ���޸�

QAbstractItemView.DoubleClicked 
2 
Editing starts when an item is double clicked.˫����Ԫ��

QAbstractItemView.SelectedClicked 
4 
Editing starts when clicking on an already selected item.������ѡ�е�����

QAbstractItemView.EditKeyPressed 
8 
Editing starts when the platform edit key has been pressed over an item.

QAbstractItemView.AnyKeyPressed 
16 
Editing starts when any key is pressed over an item.��������������޸�

QAbstractItemView.AllEditTriggers 
31 
Editing starts for all above actions.��������ȫ����





2. ���ñ��Ϊ����ѡ�� 

tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ�еķ�ʽ

QAbstractItemView.SelectionBehaviorö�ٻ�����������

Constant 
Value 
Description

QAbstractItemView.SelectItems 
0 
Selecting single items.ѡ�е�����Ԫ��

QAbstractItemView.SelectRows 
1 
Selecting only rows.ѡ��һ��

QAbstractItemView.SelectColumns 
2 
Selecting only columns.ѡ��һ��




3.����ѡ�кͶ��ѡ�е����ã�

tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //����Ϊ����ѡ�ж��Ŀ��

�ú����Ĳ����������ǣ�

QAbstractItemView.NoSelection ����ѡ��

QAbstractItemView.SingleSelection ѡ�е���Ŀ��

QAbstractItemView.MultiSelection ѡ�ж��Ŀ��

QAbstractItemView.ExtendedSelection QAbstractItemView.ContiguousSelection ���������ԣ���Ҫ����������������ǵ�ѡ��������Ctrl��Shift���󣬿��Զ�ѡ



4. ����ͷ����ʾ������

����ˮƽ��ֱ�����ı�ͷ�����������·�ʽ���� ����/��ʾ �����ã�
view plain
tableWidget->verticalHeader()->setVisible(false); //�����б�ͷ 
tableWidget->horizontalHeader()->setVisible(false); //�����б�ͷ 

ע�⣺��Ҫ #include <QHeaderView>



5. �Ա�ͷ���ֵ����塢��ɫ�������� 
view plain
QTableWidgetItem *columnHeaderItem0 = tableWidget->horizontalHeaderItem(0); //���ˮƽ�����ͷ��Item���� 
columnHeaderItem0->setFont(QFont("Helvetica")); //�������� 
columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //���õ�Ԫ�񱳾���ɫ 
columnHeaderItem0->setTextColor(QColor(200,111,30)); //����������ɫ 

ע�⣺��Ҫ #include <QHeaderView>



6. �ڵ�Ԫ�������ؼ���

QTableWidget������������ּӵ���Ԫ�񣬻�����ѿؼ�Ҳ�ŵ���Ԫ���С����磬��һ����������뵥Ԫ�񣬿�����ô����
view plain
QComboBox *comBox = new QComboBox(); 
comBox->addItem("Y"); 
comBox->addItem("N"); 
tableWidget->setCellWidget(0,2,comBox); 


��. �Ե�Ԫ��Ľ������� 

1. ��Ԫ������������ɫ�ͱ�����ɫ �������ַ�
view plain
QTableWidgetItem *item = new QTableWidgetItem("Apple"); 
item->setBackgroundColor(QColor(0,60,10)); 
item->setTextColor(QColor(200,111,100)); 
item->setFont(QFont("Helvetica")); 
tableWidget->setItem(0,3,item); 

�������Ҫ�����еĵ�Ԫ��ʹ���������壬�����ʹ�� tableWidget->setFont(QFont("Helvetica"));

2. ���õ�Ԫ�������ֵĶ��뷽ʽ

����Ƚϼ򵥣�ʹ��newItem.setTextAlignment()�������ɣ��ú����Ĳ���Ϊ��Ԫ���ڵĶ��뷽ʽ�����ַ�����˳�����������һ�����������

ˮƽ���뷽ʽ�У�
Constant Value Description
Qt.AlignLeft 0x0001 Aligns with the left edge.
Qt.AlignRight 0x0002 Aligns with the right edge.
Qt.AlignHCenter 0x0004 Centers horizontally in the available space.
Qt.AlignJustify 0x0008 Justifies the text in the available space.



��ֱ���뷽ʽ��
Constant Value Description
Qt.AlignTop 0x0020 Aligns with the top.
Qt.AlignBottom 0x0040 Aligns with the bottom.
Qt.AlignVCenter 0x0080 Centers vertically in the available space.


������ֶ�Ҫ���ã�ֻҪ�� Qt.AlignHCenter | Qt.AlignVCenter �ķ�ʽ���� 



3. �ϲ���Ԫ��Ч����ʵ�֣�

tableWidget->setSpan(0, 0, 3, 1) # �����Ϊ�� Ҫ�ı䵥Ԫ��� 1���� 2���� Ҫ�ϲ��� 3���� 4����



4. ���õ�Ԫ��Ĵ�С

���ȣ�����ָ��ĳ���л����еĴ�С
view plain
tableWidget->setColumnWidth(3,200); 
tableWidget->setRowHeight(3,60); 

�����Խ��к��еĴ�С��Ϊ��������ƥ��
view plain
tableWidget->resizeColumnsToContents(); 
tableWidget->resizeRowsToContents(); 


5. ��õ�����Ԫ������� 

ͨ��ʵ�� itemClicked (QTableWidgetItem *) �źŵĲۺ������Ϳ��Ի����굥�����ĵ�Ԫ��ָ�룬����������е�������Ϣ

connect(tableWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this, SLOT( getItem(QTreeWidgetItem*,int)) );

//��itemClicked�ź��뺯��getItem��