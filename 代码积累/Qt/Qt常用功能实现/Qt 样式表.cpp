QT��ʽ��
 

һ��QT��ʽ����
1��QT��ʽ����
    QSS����Ҫ������ʹ����ı���������Ԫ�ط��룬ʹ�����Ƥ�������ؼ�����������Ϊ���ܡ�

QT��ʽ���������û�����widgets�����۵�ǿ����ƣ����⣬���໯QStyleҲ���Զ���widgets�����ۡ�QT��ʽ��ĸ������﷨�ܴ�̶����ܵ���CSS�����ʽ���Ӱ�졣

��ʽ����ʹ��QApplication::setStyleSheet()������Ӧ�ó������ʹ��QWidget::setStyleSheet()�����ھ�����������Ӷ��������˵����

���磬������ʽ��ָ��QLineEditʹ�û�ɫ��Ϊ����ɫ��QCheckBoxʹ�ú�ɫ��Ϊ�ı���ɫ��

    QLineEdit { background: yellow }

    QCheckBox { color: red }

    �������ֶ��ƣ���ʽ���QPalette��ǿ�����磬Ҫ��ȡһ����ɫ�İ�ť����������QPushButton��QPalette::Button��ɫΪ��ɫ��Ȼ�����Ⲣ����֤�����е���ʽ��Ч����Ϊ��ʽ�Ĺ����߻ᱻ��ͬƽ̨��ԭ��ͱ��ص��������������ơ�

    ��ʽ�����ʵ����Щ���ѻ��ǲ�����ʹ��QPaletteʵ�ֵ����ж��ơ�

    �����ҪĳЩǿ���ֶ�Ϊ��ɫ��������ťΪ��ɫ���֣�����Ѥ���ĸ�ѡ����ʽ�������ɡ�

2��QT��ʽ����
A���ڴ�����ֱ������QSS

    QPushButton *button = new QPushButton(this);

    button->setText("hello");

    button->setStyleSheet("QPushButton{ color:blue}");

B��ͨ���ļ�����QSS

��QSS����д��.qss�ļ�

��.qss�ļ�������Դ�ļ�qrc.qrc��

�ڴ����ж�ȡQSS�ļ��������QSS

    QPushButton *button = new QPushButton(this);

    button->setText("hello");

    QFile file(":/qss/dev.qss");

    file.open(QIODevice::ReadOnly);

    QString stylesheet = QLatin1String(file.readAll());

    button->setStyleSheet(stylesheet);

    file.close();

 

����QT��ʽ���﷨
QT��ʽ���������﷨������HTML CSS�����ơ�

1����ʽ����
��ʽ������ʽ����������ɡ���ʽ������ѡ������������ɡ�ѡ����ָ������Щ����ܹ���Ӱ�죬����ָ���������������Щ���ԡ����磺

    QPushButton { color: red }

������ʽ�����У�QPushButton��ѡ������{ color: red }����������ʽ����ָ����QPushButton��������Ӧʹ�ú�ɫ��Ϊǰ��ɫ��

QT��ʽ���Сд�����У�������������������QT�������Ǵ�Сд���еġ�

���ѡ��������ָ��ͬһ��������ʹ�ö��ŷָ�ѡ�������������¹���

    QPushButton, QLineEdit, QComboBox { color: red }

��Ч����������

    QPushButton { color: red }

    QLineEdit { color: red }

    QComboBox { color: red }

��ʽ���������������һ�������ԣ�ֵ���Ե���������������{}�ڣ���ͬ�����ԣ�ֵ����ʹ�÷ֺŷָ������磺

    QPushButton { color: red; margin: 0px; color: rgb(85, 85, 85); font-family: ����, "Arial Narrow", arial, serif;">2��ѡ����������

��ĿǰΪֹ���е�����ʹ�õĶ�����򵥵�ѡ�������͡�QT��ʽ��֧��CSS2���������ѡ�������±��ܽ�����õ�ѡ�������͡�

ѡ����

ʾ��

˵��

ͨ��ѡ����

*

ƥ�����е����

����ѡ����

QPushButton

ƥ������QPushButton���������ʵ��

����ѡ����

QPushButton[flat="false"]

ƥ������QPushButton������flatΪfalse��ʵ�������Է�Ϊ��̬���ԺͶ�̬���ԣ���̬���Կ���ͨ��Q_PROPERTY()��ָ������̬���Կ���ʹ��setProperty��ָ����

��ѡ����

.QPushButton

ƥ��QPushButton��ʵ�����������

IDѡ����

QPushButton#okButton

ƥ�������ΪokButton������QPushButtonʵ��

 

���ѡ����

QDialog QPushButton

ƥ��QDialog���������QPushButtonʵ��

��ѡ����

QDialog > QPushButton

ƥ��QDialog�������QPushButton������ʵ��

3���ӿؼ�ѡ����
������ʽ���ӵ��������Ҫ����������ӿؼ�����QComboBox��������ť��QSpinBox�����¼�ͷ��ѡ�������԰����ӿؼ�����������ض��ӿؼ�Ӧ�ù���

    QComboBox::drop-down { image: url(dropdown.png) }

���Ϲ���������QComboBox��������Ӧ����ʽ���򡣾���˫ð�ţ�������CSS3��αԪ�أ���QT�ӿؼ�ѡ�����ڸ������ǲ�ͬ�ģ��в�ͬ�ļ������塣

�ӿؼ�ѡ����ͨ��������һ���ο�Ԫ�ؽ��ж�λ���ο�Ԫ�ؿ��������������һ���ӿؼ�ѡ���������磬QComboBox��::drop-downĬ�Ϸ�����QComboBox�ĵ׾��ε����Ͻǡ�::drop-downĬ�Ϸ�����::drop-down�ӿؼ�ѡ���������ݾ��ε����ġ�

����ʹ��subcontrol-origin���Ըı�ԭ����Ρ����磬�����Ҫ��drop-down�����ڱ߽���ζ�����Ĭ�ϵĳĵ׾��Σ�����ָ����

    QComboBox {

      margin-right: 20px;

  }

  QComboBox::drop-down {

      subcontrol-origin: margin;

  }

drop-down�ڱ߽�����ڵĶ��뷽ʽͨ��subcontrol-position���Ըı䡣�����Ժ͸��������ڿ����ӿؼ�ѡ�����Ĵ�С��ע�⣬����һ��ͼƬ����ʽ�������ӿؼ�ѡ�����Ĵ�С��

��Զ�λ������position��relative�������ӿؼ�ѡ������λ��ƫ����ԭ����λ�á����磬��QComboBox��������ť���£���Ҫһ�ֱ����µ�Ч������ͨ��ָ������ʵ�֣�

    QComboBox::down-arrow {

          image: url(down_arrow.png);

      }

      QComboBox::down-arrow:pressed {

          position: relative;

          top: 1px; left: 1px;

      }

���Զ�λ������position��absolute�������ӿؼ�ѡ������λ�úʹ�С�ĸı���ο�Ԫ���йء�

һ����λ���Ϳ������������ʹ�ú���ģ�Ͷ���������͡�

ע�⣬��QComboBox��QScrollBar�������ӵ�����������һ�����Ի����ӿؼ�ѡ���������ƣ��������������Ի����ӿؼ�ѡ����ҲҪ���뱻���ơ�

���ø�����������

::indicator              ��ѡ�򡢸�ѡ�򡢿�ѡ�˵�����ѡȺ�����ָʾ��  

::menu-indicator         ��ť�Ĳ˵�ָʾ��  

::item                   �˵����˵�����״̬����  

::up-button              ΢���������������°�ť  

::down-button            ΢���������������ϰ�ť  

::up-arrow               ΢���򡢹������������ͼ�����ϰ�ť  

::down-arrow             ΢���򡢹������������ͼ�����°�ť  

::drop-down              ��Ͽ��������ͷ  

::title                  Ⱥ���ı���

4��αѡ����
ѡ�������ܰ������ƻ������״̬�Ĺ���Ӧ�õ�α״̬��α״̬������ѡ������β�����м�ʹ�÷ֺ����ӡ����磬���¹������������ͣ��һ��QPushButton�ϣ�

    QPushButton:hover { color: white }

α״̬����ʹ��̾��ȡ�������磬���¹���������겻��ͣ��QRadioButton��

    QRadioButton:!hover { color: red }

α״̬�������߼���ķ�ʽ����ʹ�ã����磬���¹���Ӧ���������ͣ��һ��ѡ�е�QCheckBox�ϣ�

    QCheckBox:hover:checked { color: white }

ȡ��α״̬���Գ�����α״̬���С����磬���¹������������ͣ��һ��QPsuButton�ϣ���û�а��£�

    QPushButton:hover:!pressed { color: blue; }

    �����Ҫ��ʹ�ö��ſ��Խ�α״̬���߼������ӡ�

    QCheckBox:hover, QCheckBox:checked { color: white }

    α״̬���Խ���ӿؼ�ѡ����ʹ�ã�

    QComboBox::drop-down:hover { image: url(dropdown_bright.png) }

����״̬��

:disabled                   ���õĴ��ڲ���  

:enabled                    ���õĴ��ڲ���  

:focus                      ���ڲ��������뽹��  

:hover                      ����ڴ��ڲ�������ͣ  

:pressed                    ��갴��������ڲ���  

:checked                    ��ť�ѱ�ѡ��  

:unchecked                  ��ťδ��ѡ��  

:indeterminate              ��ť������ѡ��  

:open                       ���ڲ������ڴ򿪻���չ��״̬  

:closed                     ���ڲ������ڹرջ�����״̬  

:on                         ���ڲ�����״̬��on  

:off                        ���ڲ�����״̬��on  

5����ͻ����
�������ʽ����ʹ�ö��ֵָ��ͬһ������ʱ�������ͻ��

    QPushButton#okButton { color: gray }

    QPushButton { color: red }

    ������������ƥ����ΪokButton��QPushButtonʵ������color�������г�ͻ��Ϊ�˽����ͻ����Ҫ����ѡ�����������������У�QPushButton#okButton��QPushButtonҪ�����壬��ΪQPushButton#okButtonָ�򵥸��Ķ��󣬶������������ʵ����

���ƣ�αѡ������δָ��α״̬��ѡ���������塣�����������ʽ��ָ�����������ͣ��QPushButton��ʱ��QPushButton���ı�Ϊ��ɫ������Ϊ��ɫ��

    QPushButton:hover { color: white }

    QPushButton { color: red }

    �Ͻ�һ��Ӧ���ǣ�

    QPushButton:hover { color: white }

    QPushButton:enabled { color: red }

    ��������ͣ�ڰ�ť�ϣ�����ѡ��������ͬ�����ԣ���ڶ����������ȡ������Ҫ�ı�Ϊ��ɫ����Ҫ�����������

    QPushButton:enabled { color: red }

    QPushButton:hover { color: white }

    ���ߣ�����ʹ��һ��������Ӿ��壺

    QPushButton:hover:enabled { color: white }

    QPushButton:enabled { color: red }

    ������ѡ����һ��ʹ��ʱ�����Ƶ�����Ҳ�ᷢ��

    QPushButton { color: red }

    QAbstractButton { color: gray }

    ����������������QPushButtonʵ��������QPushButton�̳���QAbstractButton��������color���Եĳ�ͻ������QPushButton�̳���QAbstractButton�����Ի����QPushButton��QAbstractButton�����塣Ȼ����������ʽ��ļ��㣬���е�����ѡ��������ͬ�����ԣ������ֵĹ������ȡ����仰˵�����е�QAbstractButton��color���Իᱻ����Ϊgray������QPushButton����������ҪQPushButton���ı�Ϊred��ͨ���������������

    Ϊ��ȷ����������ԣ�QT��ʽ����ѭCSS2�淶��

    ѡ�������Եļ��㷽�����£�

    ����ѡ������ID���Ե�������=a��

    ����ѡ�������������Ժ�α״̬���������=b��

    ����ѡ������Ԫ�ص�������=c��

    ����αԪ�أ����ӿؼ�ѡ������

    ��������������a-b-c���������ԡ�

      *   {} /* a=0 b=0 c=0 -> specificity = 0 */

  LI            {}  /* a=0 b=0 c=1 -> specificity =   1 */

  UL LI         {}  /* a=0 b=0 c=2 -> specificity =   2 */

  UL OL+LI      {}  /* a=0 b=0 c=3 -> specificity =   3 */

  H1 + *[REL=up]{}  /* a=0 b=1 c=1 -> specificity =  11 */

  UL OL LI.red  {}  /* a=0 b=1 c=3 -> specificity =  13 */

  LI.red.level  {}  /* a=0 b=2 c=1 -> specificity =  21 */

  #x34y         {}  /* a=1 b=0 c=0 -> specificity = 100 */

6������
QT��ʽ�����������Ӧ�ó��򡢸������������ϡ�ͨ���ϲ���������ȣ����ס��游�ȣ����Ի�ȡ�����������Ч��ʽ���Լ�������Ӧ�ó����ϵ��κ���ʽ��

��ͻ����ʱ�����۳�ͻ�����������Σ�����Լ�����ʽ�������������κμ̳ж�������ʽ��ͬ�������������ʽ���������游�������ʽ��

�����Ľ���ǣ���һ�������������ʽ������Զ���ñ������������ʽ�����Ӧ�ó������ʽ��ָ��������������ߵ����ȼ�������,������Ӧ�ó���������ʽ��

    qApp->setStyleSheet("QPushButton { color: white }");

Ȼ����QPushButton��������һ����ʽ��

    myPushButton->setStyleSheet("* { color: blue }");

QPushButton����ʽ���ǿ��QPushButton�������κ����������ʾ��ɫ�ı�������Ӧ�ó���Χ����ʽ���ṩ�˸�����Ĺ���

����д��Ҳ��õ���ͬ�Ľ����

    myPushButton->setStyleSheet("color: blue");

�����QPushButton�����������ʽ������������Ч����

��ʽ������һ�����ӵ����⣬����ϸ��������ο�CSS2�淶��QTĿǰû��ʵ�֡�

7���̳�
�ھ����CSS�У���Ԫ�ص��������ɫû����ʾ����ʱ�����Զ��Ӹ�����̳С�ʹ��QT��ʽ��ʱ��һ����������Զ��̳и�������õ��������ɫ�����磬һ��QGroupBox����һ��QPushButton��

    qApp->setStyleSheet("QGroupBox { color: red; } ");

QPushButton��û����ʾ������ɫ����˲����Ǽ̳и����QGroupBox����ɫ������ӵ��ϵͳ����ɫ�����Ҫ����QGroupBox�������������ɫ�����£�

    qApp->setStyleSheet("QGroupBox, QGroupBox * { color: red; }");

���֮�£�ʹ��QWidget::setFont() �� QWidget::setPalette()Ϊ�������������ͻ��塣

8��C++�����ռ��ڲ������
����ѡ�����������͵��������ʽ���ơ����磺

class MyPushButton : public QPushButton {

      // ...

  }

  // ...

  qApp->setStyleSheet("MyPushButton { background: yellow; }");

    QT��ʽ��ʹ�������QObject::className() ȷ����ʱӦѡ���������Զ�������������ռ��ڲ�ʱ��QObject::className()�᷵��<namespace>::<classname>��������ӿؼ�ѡ�������﷨������ͻ��Ϊ�˽��������⣬���������ռ���ʹ�����������ѡ����ʱ������ʹ�á�--�����桰��������

namespace ns {

      class MyPushButton : public QPushButton {

          // ...

      }

  }

  // ...

  qApp->setStyleSheet("ns--MyPushButton { background: yellow; }");

9������QObject����
��QT4.3��ʼ���κοɱ���Ƶ�Q_PROPERTY������ʹ��qproperty-<property name>�﷨���á�

MyLabel { qproperty-pixmap: url(pixmap.png); }

MyGroupBox { qproperty-titleColor: rgb(100, 200, 100); }

QPushButton { qproperty-iconSize: 20px 20px; }

�������������Q_ENUMS������ö�٣�Ӧ��ͨ���������ó���ֵ�����������֡�

����QT������е���ʽ��
    Qt Designer��һ��Ԥ����ʽ������㹤�ߣ��һ�������е��κ������ѡ��Change styleSheet...����������ʽ��

    QT4.2��ʼ��Qt Designer������һ����ʽ���﷨����������֤��������﷨�Ϸ���Ƿ�����֤��������Edit Style Sheet�Ի�������½�ָʾ��

wKioL1hqOeHQzX8uAABuZVArzzo582.png

    �����Ok��Apply��ťʱ��Qt Designer���Զ�ʹ������ʽ����ʾ�����

�ġ�ʹ����ʽ����QT���
��ʹ����ʽ��ʱ��ÿ������ᱻ�������ĸ�ͬ�ľ��Σ��հ׾��Ρ��߽���Ρ��ĵ׾��Ρ����ݾ��εĺ��ӡ�

1������ģ��
�ĸ�ͬ�ľ���������ʾ��

wKiom1hqOgejndJNAABhRmdmdHg832.png

    margin, border-width,padding����Ĭ�϶���0����ʱ�ĸ�������ȫ��ͬ��

    ����ʹ��background-image����ָ������ı�����Ĭ�ϣ�background-imageֻ���ڱ߽�����ڱ����ƣ�ʹ��background-clip���Կ����޸ġ�ʹ��background-repeat���Ժ�background-origin���������Ʊ���ͼƬ���ظ�����Դ��

    background-image���Բ�����������Ĵ�С��Ϊ���ṩ���������С���ŵ�Ƥ���򱳾�������ʹ��border-image���ԡ�����border-image�����ṩ��һ����ѡ��ı�������ָ��border-image����ʱ������Ҫ��ָ��background-image���ԡ���background-image���Ժ�border-image���Զ���ָ��ʱ��border-image���Իᱻ������background-image����֮�ϡ�

    ���⣬image���Կ���������border-image�����ϻ���һ��ͼ�񡣵�����Ĵ�С��image�Ĵ�С��ƥ��ʱ��ָ����image�������������뷽ʽ����ʹ��image-position�������á���background-image���Ժ�border-image���Բ�ͬ��image���Կ���ָ��SVG��ʹimage��������Ĵ�С�Զ����š�

    ��Ⱦ����Ĳ������£�

    A��Ϊ������Ⱦ��������clip��border-radius��

    B�����Ʊ�����background-image��

 C�����Ʊ߽磨border-image��border��

 D�����Ƹ���ͼ��image��

2���ӿؼ�
һ��������Կ���һ���ӿؼ���������QComboBox����������ť�ӿؼ���������ť�ӿؼ����������¼�ͷ�ӿؼ���

    �ӿؼ����и��ӹ�ϵ��QComboBox�У����¼�ͷ�ĸ�����������ť��������ť�ĸ��׵�QComboBox��������ӿؼ�����ʹ��subcontrol-position��Ϥ��subcontrol-origin���Զ�λ�ڸ�����ڡ�

    һ����λ���ӿؼ��Ϳ���ʹ�ú���ģ�Ͷ�����ʽ��

ע�⣬��QComboBox��QScrollBar�������ӵ�����������һ�����Ի����ӿؼ�ѡ���������ƣ��������������Ի����ӿؼ�ѡ����ҲҪ���뱻���ơ�

 

�塢QT��ʽ��ο�
QT��ʽ��֧�ֶ��ֵ����ԡ�״̬���ӿؼ���ʹ�ö����������۳�Ϊ���ܡ�

1�����
�������������ʹ����ʽ������ʽ��

���

���������ʽ

QAbstractScrollArea

֧�ֺ���ģ�͡�

QAbstractScrollArea�����м̳��࣬����QTextEdit��QAbstractItemView�����е�����ͼ�ࣩ����֧�ֿɹ����ı�����ʹ��background-attachment�������Ƿ��������background-attachment���ó�fixed�Ļ����ͻ�ʹ��background-image�����ӿڣ�viewport���������������background-attachment���ó�scroll���ƶ�������ʱ��background-image�������

�ο��Զ���QAbstractScrollArea��ʾ����

QCheckBox

֧�ֺ���ģ�͡�ѡ��״̬��ָʾ����ʹ��::indicator�ӿؼ���subcontrol����������ʽ���á�Ĭ������£�ָʾ��������������ݾ��ε����Ͻǡ�

spacing����ָ��ѡ��״ָ̬ʾ��������֮��Ŀ�϶��

�ο��Զ���QCheckBoxʾ����

QColumnView

��ʹ��image������������״̬������ʽ���á���ͷָʾ����arrow indicators����ʹ��::left-arrow��::right-arrow�ӿؼ���������ʽ���á�

QComboBox

��Ͽ�Ŀ�ܣ�frame����ʹ�ú���ģ����������ʽ���á�������ť��ʹ��::drop-down�ӿؼ���������ʽ���á�Ĭ������£�������ť����������ĳĵ���������Ͻǡ�������ť�еļ�ͷ��־��ʹ��::down-arrow�ӿؼ���������ʽ���á�Ĭ������£���ͷ�Ƿ�����������ť�ӿؼ���������������ġ�

�ο��Զ���QComboBoxʾ����

QDialog

ֻ֧��background��background-clip��background-origin���ԡ�

���棺ȷ�����Զ��������ж�����Q_OBJECT�ꡣ

QDialogButtonBox

��ť�Ĳ��ַ�ʽ��ʹ��button-layout�������ı䡣

QDockWidget

��ͣ��״̬��docked����֧�ֶԱ������ͱ������İ�ť������ʽ���á�

ͣ������ı߿�border����ʹ��border������������ʽ���á�::title�ӿؼ��������Ա�����������ʽ���á��رհ�ť��������ť�����::title�ӿؼ���λ�ÿɷֱ�ʹ��::close-button��::float-button���������á��������������ֱ�ģ�������:verticalα�ࡣ

���⣬����QDockWidget::DockWidgetFeatureֵ������:closable��:floatable��:movableα״̬��

ע�⣺ʹ��QMainWindow::separator�Ըı��С�ľ��������ʽ���á�

���棺��QDockWidget������ͣ��״̬ʱ����ʽ����Ч��

�ο��Զ���QDockWidgetʾ����

QFrame

֧�ֺ���ģ�͡�

��QT4.3 ��ʼ����QLabel������ʽ�����Զ���QFrame::frameStyle�������ó�QFrame::StyledPanel��

�ο��Զ���QFrameʾ����

QGroupBox

֧�ֺ���ģ�͡������ʹ��::title�ӿؼ���������ʽ���á�Ĭ������£��������QGroupBox::textAlignment ���Խ��ж�λ��

����ѡ�е�QGroupBox���������ѡ��״ָ̬ʾ����ָʾ����ʹ��::indicator�ӿؼ���������ʽ���á�spacing������������������ָʾ��֮��ļ����

�ο��Զ���QGroupBoxʾ����

QHeaderView

֧�ֺ���ģ�͡���ͷ��ͼ�ĸ�������ʹ��::section�ӿؼ���������ʽ���õġ�section�ӿؼ�֧��:middle��:first��:last�� spacer.gifonly-one��

:next-selected��:previous-selected��:selected��:checkedα״̬��

����ָʾ��ʹ��::up-arrow��::down-arrow�ӿؼ���������ʽ���á�

�ο��Զ���QHeaderViewʾ����

QLabel

֧�ֺ���ģ�͡���֧��:hoverα״̬��

��QT4.3 ��ʼ����QLabel������ʽ����Զ���QFrame::frameStyle �������ó�QFrame::StyledPanel��

�ο��Զ���QFrameʾ����QLabel�̳���QFrame����

QLineEdit

֧�ֺ���ģ�͡�

ѡ�е������ɫ�ͱ����ֱ���ʹ��selection-color��selection-background-color��������ʽ���á�

�����ַ���ʹ��lineedit-password-character������������ʽ���á�

���������ӳٿ�ʹ��lineedit-password-mask-delay�����޸ġ�

�ο��Զ���QLineEditʾ����

QListView/

QListWidget

֧�ֺ���ģ�͡��������ı�����ɫ���ܴ򿪣��������ɫʹ��alternate-background-color������������ʽ���á�

ѡ�е������ɫ�ͱ����ֱ���ʹ��selection-color��selection-background-color��������ʽ���á�

ѡ����Ϊ��show-decoration-selected���������п��ơ�

ʹ��::item�ӿؼ�����QListView�е�����и���ϸ���ơ�

�ο�QAbsractScrollArea���˽�Կɹ����ı�������ʽ���á�

�ο��Զ���QListViewʾ����

QMainWindow

֧�ֶԷָ���������ʽ���á�

��QMainWindow��ʹ��QDockWidgetʱ�����ķָ���ʹ��::separator�ӿؼ���������ʽ���á�

�ο��Զ���QMainWindowʾ����

QMenu

֧�ֺ���ģ�͡�

��������ʹ��::item�ӿؼ���������ʽ���á���ͨ����α״̬�⣬item�ӿؼ���֧��:selected��:default��:exclusive��non-exclusiveα״̬��

��ѡѡ�Ĳ˵���ָʾ����ͨ��::indicator�ӿؼ���������ʽ���á�

�ָ�����ʹ��::separator�ӿؼ�������ʽ���á�

�������Ӳ˵������ͷ�����ʹ��right-arrow��left-arrow������ʽ���á�

������ʹ��::scroller������ʽ���á�

����˵�ʹ��::tearoff��������ʽ���á�

�ο��Զ���QMenuʾ����

QMenuBar

֧�ֺ���ģ�͡�spacing����ָ���˵���֮��Ŀ�϶��С��

��������ʹ��::item�ӿؼ�������ʽ���á�

���棺��Qt/Macƽ̨�ϣ��˵���ͨ��Ƕ�뵽ϵͳ��ȫ�ֲ˵����С�����������£���ʽ����Ч��

�ο��Զ���QMenuBarʾ����

QMessageBox

messagebox-text-interaction-flags��������ѡ����Ϣ�������ֵĽ���ģʽ��

QProgressBar

֧�ֺ���ģ�͡��������Ľ��ȿ�ʹ��::chunk�ӿؼ���������ʽ���á����ȿ���ʾ����������������С�

�����������ʾ���֣�ʹ��text-align�������������ֵ�λ�á�

��ȷ���Ľ�����ʹ��:indeterminateα״̬���á�

�ο��Զ���QProgressBarʾ����

QPushButton

֧�ֺ���ģ�͡�֧��:default��:flat��:checkedα״̬��

���ڴ��˵���QPushButton����˵�ָʾ����ʹ��::menu-indicator�ӿؼ���������ʽ���õġ���ѡ�İ�ť����ۿ�ʹ��:pen��:closedα״̬������ʽ���á�

���棺���ֻΪQPushButton����background-color���������ܲ�����ʾ���������ǽ��߿��������ó�ĳ��ֵ��������Ϊ����Ĭ������£�QPushButton�����һ����ȫ�����˱���ɫ�ı��ر߿����磬

QPushButton { border: none; }

�ο��Զ���QPushButtonʾ����

QRadioButton

֧�ֺ���ģ�͡�ѡ��ָʾ��ʹ��::indicator�ӿؼ�������ʽ���á�Ĭ������£�ָʾ�����������������������Ͻǡ�

spacing����ָ��ѡ��ָʾ��������֮��Ŀ�϶��

�ο��Զ���QRadioButtonʾ����

QScrollBar

֧�ֺ���ģ�͡�����е�����������ǻ��黬���Ĳۡ�QScrollBar�Ĺ����ʹ��width��height�������õġ�Ҫȷ������ʹ��:horizontal��:verticalα״̬��

����ʹ��::handle�ӿؼ�������ʽ���á�����min-width��min-height���շ������Ի����ṩ�ߴ�����ơ�

::add-line�ӿؼ�����������һ�еİ�ť������ʽ���á�Ĭ������£�add-line�ӿؼ�����������߿���������½ǡ�Ĭ������£���ͷ������::add-line�ӿؼ�������������ġ�

::sub-line�ӿؼ������Լ���һ�еİ�ť������ʽ���á�Ĭ������£�sub-line�ӿؼ�������������߿���������Ͻǡ�Ĭ������£���ͷ������sub-line�ӿؼ�������������ġ�

::sub-page�ӿؼ������Լ�һҳ���õĻ������������ʽ���á�::add-page�ӿؼ��������𵽼�һҳ���õĻ������������ʽ���á�

�ο��Զ���QScrollBarʾ����

QSizeGrip

֧��width��height��image���ԡ�

�ο��Զ���QSizeGripʾ����

QSlider

֧�ֺ���ģ�͡�����ˮƽ�������������ṩmin-width��height���ԡ�������ֱ�������������ṩmin-height��width���ԡ�

�������Ļ���ʹ��::groove������ʽ���á�Ĭ������£����۱���������������������С��������Ļ���ʹ��::handle�ӿؼ�������ʽ���á��ӿؼ��ڻ��۵������������ƶ���

�ο��Զ���QSliderʾ����

QSpinBox

QDateEdit

QDateTimeEdit

QDoubleSpinBox

QTimeEdit

��ת��Ŀ��ʹ�ú���ģ����������ʽ���á�

���ϰ�ť�ͼ�ͷ��ʹ��::up-button��::up-arrow�ӿؼ���������ʽ���á�Ĭ������£����ϰ�ť����������������������Ͻǡ����û����ʽ���óߴ磬��ռ�ݲο������һ��߶ȡ����ϼ�ͷ�����������ϰ�ť��������������ġ�

���°�ť�ͼ�ͷʹ��::down-button��::down-arrow�ӿؼ�������ʽ���á�Ĭ������£����°�ť����������������������½ǡ����û����ʽ���óߴ磬��ռ�ݲο������һ��߶ȡ����¼�ͷ�����������°�ť��������������ġ�

�ο��Զ���QSpinBoxʾ����

QSplitter

֧�ֺ���ģ�͡��ָ����ľ��ʹ��::handle�ӿؼ�������ʽ���á�

�ο��Զ���QSplitterʾ����

QStatusBar

ֻ֧��background���ԡ�������Ŀ��ʹ��::item�ӿؼ�������ʽ���á�

�ο��Զ���QStatusBarʾ����

QTabBar

������ǩʹ��::tab�ӿؼ�������ʽ���á��رհ�ťʹ��::close-button�ӿؼ�������ʽ���á���ǩ֧�� only-one��:first��:last��:middle��:previous�Cselected��:next-selected��:selectedα״̬��

��ǩ�ķ�������Ƿ���:top��:left��:right��:bottomα״̬��

����ѡ��״̬���ص���ǩͨ��ʹ�ø����ı߾�����λ��ģʽ��������

QTabBar�ķ���ָʾ��ʹ��::tear�ӿؼ�������ʽ���á�

QTabBar������QToolButtons��Ϊ��������ʹ��QTabBar QToolButtonѡ����������ʽ���á�ʹ��::scroller�ӿؼ�ָ��������ť�Ŀ�ȡ�

QTabBar�б�ǩ�Ķ��뷽ʽʹ��alignment���Խ������á�

���棺Ҫ�ı�QTabWidget�е�QTabBar��λ�ã�ʹ��tab-bar�ӿؼ���

�ο��Զ���QTabBarʾ����

QTabWidget

��ǩ����Ŀ��ʹ��::pane�ӿؼ�������ʽ���á���߽Ǻ��ұ߽Ƿֱ�ʹ��::left-corner��::right-corner������ʽ���á���ǩ����λ��ʹ��::tab-bar�ӿؼ����ơ�

Ĭ������£�QTabWidget���ӿؼ���λ�ð���QWindowsStyle�����ȷ����Ҫ��QTabBar�����������λ�ã�����tab-bar�ӿؼ���subcontrol-position���ԡ�

��ǩ�鷽������Ƿ���:top��:left��:right��:bottomα״̬��

�ο��Զ���QTabWidgetʾ����

QTableView

֧�ֺ���ģ�͡��������ı�����ɫ���ܿ������������ɫʹ��alternate-background-color���Խ�����ʽ���á�

ѡ�е������ɫ�ͱ����ֱ���ʹ��selection-color��selection-background-color������ʽ���á�

QTableView�еı߽������QAbstractButtonʵ�֣�ʹ��QTableViewQTableCornerButton::sectionѡ����������ʽ���á�

���棺���ֻ��QTableCornerButton�����ñ���ɫ���������ܲ�����ʾ���������ǽ��߿��������ó�ĳ��ֵ��������Ϊ��Ĭ������£�QTableCornerButton�����һ����ȫ���Ǳ���ɫ�ı��ر߿�

�������ɫʹ��gridline-color���Խ������á�

�ο�QAbsractScrollArea���˽�������ÿɹ����ı�����

�ο��Զ���QTableViewʾ����

QTextEdit

֧�ֺ���ģ�͡�

ѡ�����ֵ���ɫ�ͱ����ֱ�ʹ��selection-color��selection-background-color������ʽ���á�

�ο�QAbsractScrollArea���˽�������ÿɹ����ı�����

QToolBar

֧�ֺ���ģ�͡�

���������ڵ�����ͣ�����򣩾����Ƿ����:top��:left��:right��:bottomα״̬��

:first��:last��:middle��:only-oneα״ָ̬ʾ��������λ����һ�������飨�ο�QStyleOptionToolBar::positionWithinLine��

QToolBar�ķָ���ʹ��::separator�ӿؼ�������ʽ���á�

�����ƶ��������ľ��ʹ��::handle�ӿؼ�������ʽ���á�

�ο��Զ���QToolBarʾ����

QToolButton

֧�ֺ���ģ�͡�

���QToolButton�в˵���::menu-indicator�ӿؼ������Բ˵�ָʾ��������ʽ���á�Ĭ������£��˵�ָʾ����������������������½ǡ�

���QToolButton��QToolButton::MenuButtonPopupģʽ��::menu-button�ӿؼ��������Ʋ˵���ť��::menu-arrow�ӿؼ������ڲ˵���ť������Ʋ˵���ͷ��Ĭ������£��˵���ť�ӿؼ�λ��������������ġ�

��QToolButton��ʾ��ͷʱ����ʹ��::up-arrow��::down-arrow��::left-arrow��::right-arrow�ӿؼ���

���棺���ֻ��QToolButton ���ñ���ɫ���������ܲ�����ʾ���������ǽ��߿��������ó�ĳ��ֵ��������Ϊ��Ĭ������£�QToolButton�����һ����ȫ���Ǳ���ɫ�ı��ر߿����磬

QToolButton { border: none; }

�ο��Զ���QToolButtonʾ����

QToolBox

֧�ֺ���ģ�͡�

������ǩʹ��::tab�ӿؼ�������ʽ���á���ǩ֧�� :only-one��:first��:last��:middle��:previous-selected��:next-selected��:selectedα״̬��

QToolTip

֧�ֺ���ģ�͡�opacity���Կ��ƹ�����ʾ��͸���ȡ�

�ο��Զ���QFrameʾ����QToolTip��QFrame����

QTreeView

QTreeWidget

QTableWidget

֧�ֺ���ģ�͡��������ı�����ɫ���ܿ������������ɫʹ��alternate-background-color���Խ�����ʽ���á�

ѡ�������ɫ�ͱ����ֱ���ʹ��selection-color��selection-background-color������ʽ���á�

ѡ����Ϊ��show-decoration-selected���Խ��п��ơ�

������ͼ�ķ�֧ʹ��::branch�ӿؼ�������ʽ���á�::branch�ӿؼ�֧��:open��:closed��:has-sibling��:has-childrenα״̬��

ʹ��::item�ӿؼ���QTreeView�е�����и���ϸ���ơ�

�ο�QAbsractScrollArea���˽�������ÿɹ����ı�����

�ο��Զ���QTreeViewʾ�����˽���ζԷ�֧������ʽ���á�

QWidget

ֻ֧��background��background-clip��background-origin���ԡ�

�����QWidget�������࣬��ҪΪ�Զ�������ṩ�����¼���������paintEvent����

void CustomWidget::paintEvent(QPaintEvent *)

{

QStyleOption opt;

opt.init(this);

QPainter p(this);

style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

���û��������ʽ�������ϵĴ��벻���κ����á�

���棺ȷ�����Զ�������ж�����Q_OBJECT�ꡣ

 

 

 

����QT��ʽ��ʵ��
1����ʽ���ʹ��
A������ǰ��ɫ�ͱ���ɫ

    ����Ӧ�ó����е�����QLineEdit����ı���ɫΪ��ɫ

    qApp->setStyleSheet("QLineEdit {

    ���ֻ��Ҫ�������ھ���ĳ���Ի����QLineEdit�����������

    myDialog->setStyleSheet("QLineEdit {

    ���ֻ�뽫��������ĳ�������QLineEdit���������ʹ��QObject::setObjectName() ��IDѡ������

    myDialog->setStyleSheet("QLineEdit#nameEdit {

    ����ֱ������QLieEdit�����background-color���ԣ�����ѡ����

    nameEdit->setStyleSheet("

    Ϊ��ȷ���Ա�Ч����Ӧ��ָ���ı����ʵ���ɫ

    nameEdit->setStyleSheet("color: blue;

    �޸�ѡ���ı�����ɫ���£�

    nameEdit->setStyleSheet("color: blue;"

                          ""

                          "selection-color: yellow;"

                          "selection-");

B��ʹ�ö�̬���Զ�����ʽ

Ϊ����ʾ�û��ֶ��Ǳ���ģ�����Щ�ֶ�ʹ�û�ɫ��Ϊ����ɫ��Ҫʹ��QT��ʽ������ʵ�����׵ġ����ȣ�Ӧ��ʹ��Ӧ�ó������ʽ��

*[mandatoryField="true"] { margin: 0px; clear: both; height: auto; overflow: hidden; color: rgb(85, 85, 85); font-family: ����, "Arial Narrow", arial, serif; text-indent: 28px; text-align: justify;">����ζ��mandatoryField�ֶ�����Ϊtrue������ı���ɫΪ��ɫ��

����ÿ���ر��ֶ���������Ǵ�æ�м򵥴�����һ��mandatoryField���Բ�����Ϊtrue��

    QLineEdit *nameEdit = new QLineEdit(this);

    nameEdit->setProperty("mandatoryField", true);

 

    QLineEdit *emailEdit = new QLineEdit(this);

    emailEdit->setProperty("mandatoryField", true);

 

   QSpinBox *ageSpinBox = new QSpinBox(this);

   ageSpinBox->setProperty("mandatoryField", true);

C��ʹ�ú���ģ�Ͷ���QPushButton

��������չʾ��δ���һ����ɫ�İ�ť��

QPushButton#evilButton

{

      

      border-style: outset;

      border-width: 2px;

      border-radius: 10px;

      border-color: beige;

      font: bold 14px;

      min-width: 10em;

      padding: 6px;

  }

  QPushButton#evilButton:pressed

{

      

      border-style: inset;

  }

D�����ư�ť�˵�ָʾ���ӿؼ�

    �ӿؼ����Է����������Ԫ�ء����磬��ť��ʹ��QPushButton::setMenu()�����˵���˵�ָʾ�������ƺ�ɫ��ť�Ĳ˵�ָʾ�����£�

QPushButton#evilButton::menu-indicator

{

      image: url(myindicator.png);

 }

    Ĭ�ϣ��˵�ָʾ����λ�ڳĵ���������½ǡ�ͨ���ı�subcontrol-position��subcontrol-origin���Կ��Զ�λָʾ����

QPushButton::menu-indicator

{

      image: url(myindicator.png);

      subcontrol-position: right center;

      subcontrol-origin: padding;

      left: -2px;

  }

    Myindicator.png��λ���ڰ�ť�ĵ�����������ġ�

E������ѡ����ʾ��

    ����Ӧ�ó�����ʽ����QLineEdit�ı�Ϊ��ɫ��

    QLineEdit { color: red }

    Ȼ������Ҫ����һ��ֻ��QLineEdit���ı���ɫΪ��ɫ���£�

    QLineEdit { color: red }

    QLineEdit[readOnly="true"] { color: gray }

    ĳЩ����£����Ҫ��ע����е�����QLineEditΪ��ɫ��

    QLineEdit { color: red }

     QLineEdit[readOnly="true"] { color: gray }

     #registrationDialog QLineEdit { color: brown }

    ���Ҫ�����жԻ����е�QLineEditΪ��ɫ��

    QLineEdit { color: red }

    QLineEdit[readOnly="true"] { color: gray }

    QDialog QLineEdit { color: brown }

 

2�������������
�����ṩʹ����ʽ�����ض������ʵ����

��1��������QAbstractScrollArea

�κ�QAbstractScrollArea���(����ͼ��QTextEdit��QTextBrowser)�ı���������ʹ��bakcground�������á����磬���ô��й����������ı���ͼ�������£�

QTextEdit, QListView 

{

      

      background-image: url(draft.png);

      background-attachment: scroll;

  }

�������background-image�������ӿ��й̶���

QTextEdit, QListView 

{

      

      background-image: url(draft.png);

      background-attachment: fixed;

  }

��2��������QCheckBox

����QCheckBox��ʽ������QRadioButton��ʽ������ͬ����Ҫ����������̬��QCheckBox��һ��ģ��̬��

QCheckBox 

{

      spacing: 5px;

  }

 

  QCheckBox::indicator

{

      width: 13px;

      height: 13px;

  }

 

  QCheckBox::indicator:unchecked

{

      image: url(:/images/checkbox_unchecked.png);

  }

 

  QCheckBox::indicator:unchecked:hover

{

      image: url(:/images/checkbox_unchecked_hover.png);

  }

 

  QCheckBox::indicator:unchecked:pressed

{

      image: url(:/images/checkbox_unchecked_pressed.png);

  }

 

  QCheckBox::indicator:checked

{

      image: url(:/images/checkbox_checked.png);

  }

 

  QCheckBox::indicator:checked:hover

{

      image: url(:/images/checkbox_checked_hover.png);

  }

 

  QCheckBox::indicator:checked:pressed

{

      image: url(:/images/checkbox_checked_pressed.png);

  }

 

  QCheckBox::indicator:indeterminate:hover

{

      image: url(:/images/checkbox_indeterminate_hover.png);

  }

 

  QCheckBox::indicator:indeterminate:pressed {

      image: url(:/images/checkbox_indeterminate_pressed.png);

  }

��3����������Ͽ�QComboBox

QComboBox {

      border: 1px solid gray;

      border-radius: 3px;

      padding: 1px 18px 1px 3px;

      min-width: 6em;

  }

 

  QComboBox:editable {

      background: white;

  }

 

  QComboBox:!editable, QComboBox::drop-down:editable {

       background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,

                                   stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,

                                   stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);

  }

 

  /* QComboBox gets the "on" state when the popup is open */

  QComboBox:!editable:on, QComboBox::drop-down:editable:on {

      background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,

                                  stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,

                                  stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);

  }

 

  QComboBox:on { /* shift the text when the popup opens */

      padding-top: 3px;

      padding-left: 4px;

  }

 

  QComboBox::drop-down {

      subcontrol-origin: padding;

      subcontrol-position: top right;

      width: 15px;

 

      border-left-width: 1px;

      border-left-color: darkgray;

      border-left-style: solid; /* just a single line */

      border-top-right-radius: 3px; /* same radius as the QComboBox */

      border-bottom-right-radius: 3px;

  }

 

  QComboBox::down-arrow {

      image: url(/usr/share/icons/crystalsvg/16x16/actions/1downarrow.png);

  }

 

  QComboBox::down-arrow:on { /* shift the arrow when popup is open */

      top: 1px;

      left: 1px;

  }

    ��Ͽ�ĵ����˵���QAbstractItemView��ʹ�ú��ѡ����������ʽ���á�

  QComboBox QAbstractItemView {

      border: 2px solid darkgray;

      selection-

  }

��4��������QDockWidget

QDockWidget�ı������Ͱ�ť���԰����½�����ʽ���á�

QDockWidget

{

    border: 1px solid lightgray;

    titlebar-close-icon: url(close.png);

    titlebar-normal-icon: url(undock.png);

}

 

QDockWidget::title

{

    text-align: left; /* align the text to the left */

    background: lightgray;

    padding-left: 5px;

}

 

QDockWidget::close-button, QDockWidget::float-button

{

    border: 1px solid transparent;

    background: darkgray;

    padding: 0px;

}

 

QDockWidget::close-button:hover, QDockWidget::float-button:hover

{

    background: gray;

}

 

QDockWidget::close-button:pressed, QDockWidget::float-button:pressed

{

    padding: 1px -1px -1px 1px;

}

���Ҫ�ƶ�ͣ�������ť����࣬����ʹ��������ʽ�����ã�

QDockWidget 

{

      border: 1px solid lightgray;

      titlebar-close-icon: url(close.png);

      titlebar-normal-icon: url(float.png);

 }

 

  QDockWidget::title 

  {

      text-align: left;

      background: lightgray;

      padding-left: 35px;

  }

 

  QDockWidget::close-button, QDockWidget::float-button 

  {

      background: darkgray;

      padding: 0px;

      icon-size: 14px; /* maximum icon size */

  }

 

  QDockWidget::close-button:hover, QDockWidget::float-button:hover 

  {

      background: gray;

  }

 

  QDockWidget::close-button:pressed, QDockWidget::float-button:pressed 

  {

      padding: 1px -1px -1px 1px;

  }

 

  QDockWidget::close-button 

  {

      subcontrol-position: top left;

      subcontrol-origin: margin;

      position: absolute;

      top: 0px; left: 0px; bottom: 0px;

      width: 14px;

  }

 

  QDockWidget::float-button 

  {

      subcontrol-position: top left;

      subcontrol-origin: margin;

      position: absolute;

      top: 0px; left: 16px; bottom: 0px;

      width: 14px;

  }

��5��������QFrame

QFrame, QLabel, QToolTip 

{

      border: 2px solid green;

      border-radius: 4px;

      padding: 2px;

      background-image: url(images/welcome.png);

}

��6��������QGroupBox

QGroupBox

{

    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,

                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);

    border: 2px solid gray;

    border-radius: 5px;

    margin-top: 1ex; /* leave space at the top for the title */

}

QGroupBox::title

{

    subcontrol-origin: margin;

    subcontrol-position: top center; /* position at the top center */

    padding: 0 3px;

    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,

                                      stop: 0 #FF0ECE, stop: 1 #FFFFFF);

}

QGroupBox::indicator

{

    width: 13px;

    height: 13px;

}

 

QGroupBox::indicator:unchecked

{

    image: url(:/images/checkbox_unchecked.png);

}

��7��������QHeaderView

QHeaderView::section 

{

    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,

                                      stop:0 #616161, stop: 0.5 #505050,

                                      stop: 0.6 #434343, stop:1 #656565);

color: white;

    padding-left: 4px;

border: 1px solid #6c6c6c;

}

 

QHeaderView::section:checked

{

    background-color: red;

}

 

QHeaderView::down-arrow 

{

    image: url(down_arrow.png);

}

 

QHeaderView::up-arrow 

{

    image: url(up_arrow.png);

}

��8��������QLineEdit

QLineEdit�Ŀ��ʹ�ú���ģ�ͽ�����ʽ���á�

QLineEdit 

{

    border: 2px solid gray;

    border-radius: 10px;

    padding: 0 8px;

    background: yellow;

    selection-background-color: darkgray;

}

QLineEdit�������ַ�ʹ��QLineEdit::Password��ʾģʽ���á�

QLineEdit[echoMode="2"] 

{

    lineedit-password-character: 9679;

}

ֻ��QLineEdit�ı������������޸ģ�

QLineEdit:read-only 

{

    background: lightblue;

}

 

���Բο����������ӣ�

http://9291927.blog.51cto.com/9281927/1888380/

http://9291927.blog.51cto.com/9281927/1888395

http://9291927.blog.51cto.com/9281927/1888400

http://blog.csdn.net/goforwardtostep/article/details/60884870

http://blog.csdn.net/GoForwardToStep/article/details/64169734

http://blog.csdn.net/GoForwardToStep/article/details/65451416