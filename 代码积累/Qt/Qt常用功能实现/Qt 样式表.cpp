QT样式表
 

一、QT样式表简介
1、QT样式表简介
    QSS的主要功能是使界面的表现与界面的元素分离，使得设计皮肤与界面控件分离的软件成为可能。

QT样式表是允许用户定制widgets组件外观的强大机制，此外，子类化QStyle也可以定制widgets组件外观。QT样式表的概念、术语、语法很大程度上受到了CSS层叠样式表的影响。

样式表是使用QApplication::setStyleSheet()设置在应用程序或是使用QWidget::setStyleSheet()设置在具体组件及其子对象的文字说明。

例如，以下样式表指明QLineEdit使用黄色作为背景色，QCheckBox使用红色作为文本颜色。

    QLineEdit { background: yellow }

    QCheckBox { color: red }

    对于这种定制，样式表比QPalette更强大。例如，要获取一个红色的按钮，可以设置QPushButton的QPalette::Button角色为红色。然而，这并不保证对所有的样式有效，因为样式的构造者会被不同平台的原则和本地的主题引擎所限制。

    样式表可以实现那些很难或是不可能使用QPalette实现的所有定制。

    如果想要某些强制字段为黄色背景，按钮为红色文字，或是绚丽的复选框，样式表可以完成。

2、QT样式表编程
A、在代码中直接设置QSS

    QPushButton *button = new QPushButton(this);

    button->setText("hello");

    button->setStyleSheet("QPushButton{ color:blue}");

B、通过文件设置QSS

将QSS代码写入.qss文件

将.qss文件加入资源文件qrc.qrc中

在代码中读取QSS文件设置组件QSS

    QPushButton *button = new QPushButton(this);

    button->setText("hello");

    QFile file(":/qss/dev.qss");

    file.open(QIODevice::ReadOnly);

    QString stylesheet = QLatin1String(file.readAll());

    button->setStyleSheet(stylesheet);

    file.close();

 

二、QT样式表语法
QT样式表的术语和语法规则与HTML CSS很相似。

1、样式规则
样式表由样式规则序列组成。样式规则由选择器和声明组成。选择器指定了那些组件受规则影响，声明指定了组件设置了哪些属性。例如：

    QPushButton { color: red }

以上样式规则中，QPushButton是选择器，{ color: red }是声明。样式规则指定了QPushButton及其子类应使用红色作为前景色。

QT样式表大小写不敏感，除了类名、对象名、QT属性名是大小写敏感的。

多个选择器可以指定同一个声明，使用逗号分隔选择器。例如以下规则：

    QPushButton, QLineEdit, QComboBox { color: red }

等效于三个规则：

    QPushButton { color: red }

    QLineEdit { color: red }

    QComboBox { color: red }

样式规则的声明部分是一个“属性：值”对的链表。声明部分在{}内，不同的属性：值”对使用分号分隔。例如：

    QPushButton { color: red; margin: 0px; color: rgb(85, 85, 85); font-family: 宋体, "Arial Narrow", arial, serif;">2、选择器的类型

到目前为止所有的例子使用的都是最简单的选择器类型。QT样式表支持CSS2定义的所有选择器。下表总结了最常用的选择器类型。

选择器

示例

说明

通用选择器

*

匹配所有的组件

类型选择器

QPushButton

匹配所有QPushButton机器子类的实例

属性选择器

QPushButton[flat="false"]

匹配所有QPushButton的属性flat为false的实例。属性分为静态属性和动态属性，静态属性可以通过Q_PROPERTY()来指定，动态属性可以使用setProperty来指定。

类选择器

.QPushButton

匹配QPushButton的实例，子类除外

ID选择器

QPushButton#okButton

匹配对象名为okButton的所有QPushButton实例

 

后代选择器

QDialog QPushButton

匹配QDialog后代的所有QPushButton实例

子选择器

QDialog > QPushButton

匹配QDialog子类对象QPushButton的所有实例

3、子控件选择器
对于样式复杂的组件，需要访问组件的子控件，如QComboBox的下拉按钮或QSpinBox的上下箭头。选择器可以包含子控件来对组件的特定子控件应用规则。

    QComboBox::drop-down { image: url(dropdown.png) }

以上规则会对所有QComboBox的下拉框应用样式规则。尽管双冒号：：很像CSS3的伪元素，但QT子控件选择器在概念上是不同的，有不同的级联语义。

子控件选择器通常根据另一个参考元素进行定位。参考元素可以是组件或是另一个子控件选择器。例如，QComboBox的::drop-down默认放置在QComboBox衬底矩形的右上角。::drop-down默认放置在::drop-down子控件选择器的内容矩形的中心。

可以使用subcontrol-origin属性改变原点矩形。例如，如果想要将drop-down放置在边界矩形而不是默认的衬底矩形，可以指定：

    QComboBox {

      margin-right: 20px;

  }

  QComboBox::drop-down {

      subcontrol-origin: margin;

  }

drop-down在边界矩形内的对齐方式通过subcontrol-position属性改变。宽属性和高属性用于控制子控件选择器的大小。注意，设置一幅图片会隐式地设置子控件选择器的大小。

相对定位方法（position：relative）允许子控件选择器的位置偏离它原来的位置。例如，当QComboBox的下拉按钮按下，想要一种被按下的效果可以通过指定如下实现：

    QComboBox::down-arrow {

          image: url(down_arrow.png);

      }

      QComboBox::down-arrow:pressed {

          position: relative;

          top: 1px; left: 1px;

      }

绝对定位方法（position：absolute）允许子控件选择器的位置和大小的改变与参考元素有关。

一旦定位，就可以像组件那样使用盒子模型对其进行造型。

注意，像QComboBox和QScrollBar这样复杂的组件，如果有一个属性或是子控件选择器被定制，所有其他的属性或是子控件选择器也要必须被定制。

常用辅助控制器：

::indicator              单选框、复选框、可选菜单项或可选群组项的指示器  

::menu-indicator         按钮的菜单指示器  

::item                   菜单、菜单栏或状态栏项  

::up-button              微调框或滚动条的向下按钮  

::down-button            微调框或滚动条的向上按钮  

::up-arrow               微调框、滚动条或标题视图的向上按钮  

::down-arrow             微调框、滚动条或标题视图的向下按钮  

::drop-down              组合框的下拉箭头  

::title                  群组框的标题

4、伪选择器
选择器可能包含限制基于组件状态的规则应用的伪状态。伪状态出现在选择器的尾部，中间使用分号连接。例如，以下规则用于鼠标悬停在一个QPushButton上：

    QPushButton:hover { color: white }

伪状态可以使用叹号取反，例如，以下规则用于鼠标不悬停在QRadioButton：

    QRadioButton:!hover { color: red }

伪状态可以以逻辑与的方式连接使用，例如，以下规则应用于鼠标悬停在一个选中的QCheckBox上：

    QCheckBox:hover:checked { color: white }

取反伪状态可以出现在伪状态链中。例如，以下规则用于鼠标悬停在一个QPsuButton上，但没有按下：

    QPushButton:hover:!pressed { color: blue; }

    如果需要，使用逗号可以将伪状态以逻辑或连接。

    QCheckBox:hover, QCheckBox:checked { color: white }

    伪状态可以结合子控件选择器使用：

    QComboBox::drop-down:hover { image: url(dropdown_bright.png) }

常用状态：

:disabled                   禁用的窗口部件  

:enabled                    启用的窗口部件  

:focus                      窗口部件有输入焦点  

:hover                      鼠标在窗口部件上悬停  

:pressed                    鼠标按键点击窗口部件  

:checked                    按钮已被选中  

:unchecked                  按钮未被选中  

:indeterminate              按钮被部分选中  

:open                       窗口部件处于打开或扩展的状态  

:closed                     窗口部件处于关闭或销毁状态  

:on                         窗口部件的状态是on  

:off                        窗口部件的状态是on  

5、冲突处理
当多个样式规则使用多个值指定同一个属性时会产生冲突。

    QPushButton#okButton { color: gray }

    QPushButton { color: red }

    以上两条规则匹配名为okButton的QPushButton实例，在color属性上有冲突。为了解决冲突，需要考虑选择器的特征。上例中，QPushButton#okButton比QPushButton要更具体，因为QPushButton#okButton指向单个的对象，而不是类的所有实例。

类似，伪选择器比未指定伪状态的选择器更具体。因而，以下样式表指定，当鼠标悬停在QPushButton上时，QPushButton的文本为白色，否则为红色。

    QPushButton:hover { color: white }

    QPushButton { color: red }

    严谨一点应该是：

    QPushButton:hover { color: white }

    QPushButton:enabled { color: red }

    如果鼠标悬停在按钮上，两个选择器有相同的特性，则第二条规则优先。如果想要文本为白色，需要重新排序规则：

    QPushButton:enabled { color: red }

    QPushButton:hover { color: white }

    或者，可以使第一条规则更加具体：

    QPushButton:hover:enabled { color: white }

    QPushButton:enabled { color: red }

    和类型选择器一起使用时，类似的问题也会发生

    QPushButton { color: red }

    QAbstractButton { color: gray }

    以上两条规则用于QPushButton实例（由于QPushButton继承自QAbstractButton），并有color属性的冲突。由于QPushButton继承自QAbstractButton，所以会假设QPushButton比QAbstractButton更具体。然而，对于样式表的计算，所有的类型选择器有相同的特性，最后出现的规则优先。换句话说，所有的QAbstractButton的color属性会被设置为gray，包括QPushButton。如果真的想要QPushButton的文本为red，通常会重新排序规则。

    为了确定规则的特性，QT样式表遵循CSS2规范：

    选择器特性的计算方法如下：

    计算选择器中ID属性的数量（=a）

    计算选择器中其他属性和伪状态类的数量（=b）

    计算选择器中元素的数量（=c）

    忽略伪元素（如子控件选择器）

    串联的三个数字a-b-c给出了特性。

      *   {} /* a=0 b=0 c=0 -> specificity = 0 */

  LI            {}  /* a=0 b=0 c=1 -> specificity =   1 */

  UL LI         {}  /* a=0 b=0 c=2 -> specificity =   2 */

  UL OL+LI      {}  /* a=0 b=0 c=3 -> specificity =   3 */

  H1 + *[REL=up]{}  /* a=0 b=1 c=1 -> specificity =  11 */

  UL OL LI.red  {}  /* a=0 b=1 c=3 -> specificity =  13 */

  LI.red.level  {}  /* a=0 b=2 c=1 -> specificity =  21 */

  #x34y         {}  /* a=1 b=0 c=0 -> specificity = 100 */

6、级联
QT样式表可以设置在应用程序、父组件、子组件上。通过合并组件的祖先（父亲、祖父等）可以获取任意组件的有效样式表，以及设置在应用程序上的任何样式表。

冲突发生时，不论冲突规则的特性如何，组件自己的样式表总是优先于任何继承而来的样式表。同样，父组件的样式表优先于祖父组件的样式表。

这样的结果是，在一个组件上设置样式规则会自动获得比祖先组件的样式表或是应用程序的样式表指定的其他规则更高的优先级。例如,首先在应用程序设置样式表

    qApp->setStyleSheet("QPushButton { color: white }");

然后，在QPushButton对象设置一个样式表

    myPushButton->setStyleSheet("* { color: blue }");

QPushButton的样式表会强制QPushButton（及其任何子组件）显示蓝色文本，尽管应用程序范围的样式表提供了更具体的规则。

下列写法也会得到相同的结果：

    myPushButton->setStyleSheet("color: blue");

但如果QPushButton有子组件，样式表不会对子组件有效果。

样式表级联是一个复杂的主题，更详细的内容请参考CSS2规范。QT目前没有实现。

7、继承
在经典的CSS中，当元素的字体和颜色没有显示设置时，会自动从父组件继承。使用QT样式表时，一个组件不会自动继承父组件设置的字体和颜色。例如，一个QGroupBox包含一个QPushButton：

    qApp->setStyleSheet("QGroupBox { color: red; } ");

QPushButton并没有显示设置颜色，因此并不是继承父组件QGroupBox的颜色，而是拥有系统的颜色。如果要设置QGroupBox及其子组件的颜色，如下：

    qApp->setStyleSheet("QGroupBox, QGroupBox * { color: red; }");

相比之下，使用QWidget::setFont() 和 QWidget::setPalette()为子组件设置字体和画板。

8、C++命名空间内部的组件
类型选择器特殊类型的组件的样式定制。例如：

class MyPushButton : public QPushButton {

      // ...

  }

  // ...

  qApp->setStyleSheet("MyPushButton { background: yellow; }");

    QT样式表使用组件的QObject::className() 确定何时应选择器。当自定义组件在命名空间内部时，QObject::className()会返回<namespace>::<classname>。这会与子控件选择器的语法产生冲突。为了解决这个问题，当在命名空间内使用组件的类型选择器时，必须使用“--”代替“：：”。

namespace ns {

      class MyPushButton : public QPushButton {

          // ...

      }

  }

  // ...

  qApp->setStyleSheet("ns--MyPushButton { background: yellow; }");

9、设置QObject属性
从QT4.3开始，任何可被设计的Q_PROPERTY都可以使用qproperty-<property name>语法设置。

MyLabel { qproperty-pixmap: url(pixmap.png); }

MyGroupBox { qproperty-titleColor: rgb(100, 200, 100); }

QPushButton { qproperty-iconSize: 20px 20px; }

如果属性引用了Q_ENUMS声明的枚举，应该通过名字引用常量值，而不是数字。

三、QT设计器中的样式表
    Qt Designer是一款预览样式表的优秀工具，右击设计器中的任何组件，选择Change styleSheet...可以设置样式表。

    QT4.2开始，Qt Designer包含了一个样式表语法高亮器和验证器。如果语法合法或非法，验证器可以在Edit Style Sheet对话框的左下角指示。

wKioL1hqOeHQzX8uAABuZVArzzo582.png

    当点击Ok或Apply按钮时，Qt Designer会自动使用新样式表显示组件。

四、使用样式表定制QT组件
当使用样式表时，每个组件会被当作有四个同心矩形：空白矩形、边界矩形、衬底矩形、内容矩形的盒子。

1、盒子模型
四个同心矩形如下所示：

wKiom1hqOgejndJNAABhRmdmdHg832.png

    margin, border-width,padding属性默认都是0。此时四个矩形完全相同。

    可以使用background-image属性指定组件的背景。默认，background-image只会在边界矩形内被绘制，使用background-clip属性可以修改。使用background-repeat属性和background-origin属性来控制背景图片的重复和来源。

    background-image属性不会缩放组件的大小。为了提供随着组件大小缩放的皮肤或背景，必须使用border-image属性。由于border-image属性提供了一个可选择的背景，当指定border-image属性时，不会要求指定background-image属性。当background-image属性和border-image属性都被指定时，border-image属性会被绘制在background-image属性之上。

    此外，image属性可以用于在border-image属性上绘制一幅图像。当组件的大小与image的大小不匹配时，指定的image不会伸缩，对齐方式可以使用image-position属性设置。与background-image属性和border-image属性不同，image属性可以指定SVG，使image根据组件的大小自动缩放。

    渲染规则的步骤如下：

    A、为整个渲染操作设置clip（border-radius）

    B、绘制背景（background-image）

 C、绘制边界（border-image，border）

 D、绘制覆盖图像（image）

2、子控件
一个组件可以看作一颗子控件树。例如QComboBox绘制下拉按钮子控件，下拉按钮子控件绘制了向下箭头子控件。

    子控件享有父子关系。QComboBox中，向下箭头的父亲是下拉按钮，下拉按钮的父亲的QComboBox组件本身。子控件可以使用subcontrol-position熟悉和subcontrol-origin属性定位在父组件内。

    一旦定位，子控件就可以使用盒子模型定制样式。

注意，像QComboBox和QScrollBar这样复杂的组件，如果有一个属性或是子控件选择器被定制，所有其他的属性或是子控件选择器也要必须被定制。

 

五、QT样式表参考
QT样式表支持多种的属性、状态和子控件，使得定制组件的外观成为可能。

1、组件
以下组件都可以使用样式表定制样式。

组件

如何设置样式

QAbstractScrollArea

支持盒子模型。

QAbstractScrollArea的所有继承类，包括QTextEdit和QAbstractItemView（所有的项视图类），都支持可滚动的背景，使用background-attachment来设置是否滚动。将background-attachment设置成fixed的话，就会使得background-image不随视口（viewport）而滚动。如果将background-attachment设置成scroll，移动滚动条时，background-image会滚动。

参考自定义QAbstractScrollArea的示例。

QCheckBox

支持盒子模型。选中状态的指示器可使用::indicator子控件（subcontrol）来进行样式设置。默认情况下，指示器放在组件的内容矩形的左上角。

spacing属性指定选中状态指示器与文字之间的空隙。

参考自定义QCheckBox示例。

QColumnView

可使用image属性来对收缩状态进行样式设置。箭头指示器（arrow indicators）可使用::left-arrow和::right-arrow子控件来进行样式设置。

QComboBox

组合框的框架（frame）可使用盒子模型来进行样式设置。下拉按钮可使用::drop-down子控件来进行样式设置。默认情况下，下拉按钮放置在组件的衬底区域的右上角。下拉按钮中的箭头标志可使用::down-arrow子控件来进行样式设置。默认情况下，箭头是放置在下拉按钮子控件的内容区域的中心。

参考自定义QComboBox示例。

QDialog

只支持background、background-clip和background-origin属性。

警告：确保在自定义的组件中定义了Q_OBJECT宏。

QDialogButtonBox

按钮的布局方式可使用button-layout属性来改变。

QDockWidget

在停靠状态（docked），支持对标题栏和标题栏的按钮进行样式设置。

停靠组件的边框（border）可使用border属性来进行样式设置。::title子控件可用来对标题栏进行样式设置。关闭按钮和悬浮按钮相对于::title子控件的位置可分别使用::close-button和::float-button来进行设置。如果标题栏是竖直的，会设置:vertical伪类。

此外，根据QDockWidget::DockWidgetFeature值，设置:closable、:floatable和:movable伪状态。

注意：使用QMainWindow::separator对改变大小的句柄进行样式设置。

警告：在QDockWidget不处于停靠状态时，样式表无效。

参考自定义QDockWidget示例。

QFrame

支持盒子模型。

从QT4.3 开始，对QLabel设置样式表，会自动将QFrame::frameStyle属性设置成QFrame::StyledPanel。

参考自定义QFrame示例。

QGroupBox

支持盒子模型。标题可使用::title子控件来进行样式设置。默认情况下，标题根据QGroupBox::textAlignment 属性进行定位。

对于选中的QGroupBox，标题包含选中状态指示器。指示器可使用::indicator子控件来进行样式设置。spacing属性用来设置文字与指示器之间的间隔。

参考自定义QGroupBox示例。

QHeaderView

支持盒子模型。表头视图的各个区域使用::section子控件来进行样式设置的。section子控件支持:middle、:first、:last、 spacer.gifonly-one、

:next-selected、:previous-selected、:selected和:checked伪状态。

排序指示器使用::up-arrow和::down-arrow子控件来进行样式设置。

参考自定义QHeaderView示例。

QLabel

支持盒子模型。不支持:hover伪状态。

从QT4.3 开始，对QLabel设置样式表会自动将QFrame::frameStyle 属性设置成QFrame::StyledPanel。

参考自定义QFrame示例（QLabel继承自QFrame）。

QLineEdit

支持盒子模型。

选中的项的颜色和背景分别是使用selection-color和selection-background-color来进行样式设置。

密码字符可使用lineedit-password-character属性来进行样式设置。

密码掩码延迟可使用lineedit-password-mask-delay属性修改。

参考自定义QLineEdit示例。

QListView/

QListWidget

支持盒子模型。如果交替改变行颜色功能打开，交替的颜色使用alternate-background-color属性来进行样式设置。

选中的项的颜色和背景分别是使用selection-color和selection-background-color来进行样式设置。

选择行为由show-decoration-selected属性来进行控制。

使用::item子控件来对QListView中的项进行更精细控制。

参考QAbsractScrollArea以了解对可滚动的背景的样式设置。

参考自定义QListView示例。

QMainWindow

支持对分隔符进行样式设置。

在QMainWindow中使用QDockWidget时产生的分隔符使用::separator子控件来进行样式设置。

参考自定义QMainWindow示例。

QMenu

支持盒子模型。

单个的项使用::item子控件来进行样式设置。除通常的伪状态外，item子控件还支持:selected、:default、:exclusive和non-exclusive伪状态。

复选选的菜单项指示器是通过::indicator子控件来进行样式设置。

分隔符是使用::separator子控件进行样式设置。

对于有子菜单的项，箭头标记是使用right-arrow和left-arrow进行样式设置。

滚动器使用::scroller进行样式设置。

分离菜单使用::tearoff来进行样式设置。

参考自定义QMenu示例。

QMenuBar

支持盒子模型。spacing属性指定菜单项之间的空隙大小。

单个的项使用::item子控件进行样式设置。

警告：在Qt/Mac平台上，菜单栏通常嵌入到系统的全局菜单条中。在这种情况下，样式单无效。

参考自定义QMenuBar示例。

QMessageBox

messagebox-text-interaction-flags属性用来选择消息框中文字的交互模式。

QProgressBar

支持盒子模型。进度条的进度块使用::chunk子控件来进行样式设置。进度块显示在组件的内容区域中。

如果进度条显示文字，使用text-align属性来设置文字的位置。

不确定的进度条使用:indeterminate伪状态设置。

参考自定义QProgressBar示例。

QPushButton

支持盒子模型。支持:default、:flat、:checked伪状态。

对于带菜单的QPushButton，其菜单指示器是使用::menu-indicator子控件来进行样式设置的。复选的按钮的外观可使用:pen和:closed伪状态进行样式设置。

警告：如果只为QPushButton设置background-color，背景可能不会显示出来，除非将边框属性设置成某个值。这是因为，在默认情况下，QPushButton会绘制一个完全覆盖了背景色的本地边框。例如，

QPushButton { border: none; }

参考自定义QPushButton示例。

QRadioButton

支持盒子模型。选中指示器使用::indicator子控件进行样式设置。默认情况下，指示器放置在组件内容区域的左上角。

spacing属性指定选中指示器与文字之间的空隙。

参考自定义QRadioButton示例。

QScrollBar

支持盒子模型。组件中的内容区域就是滑块滑动的槽。QScrollBar的广度是使用width或height属性设置的。要确定方向，使用:horizontal和:vertical伪状态。

滑块使用::handle子控件进行样式设置。设置min-width或min-height按照方向来对滑块提供尺寸的限制。

::add-line子控件用来对增加一行的按钮进行样式设置。默认情况下，add-line子控件放置在组件边框区域的右下角。默认情况下，箭头放置在::add-line子控件内容区域的中心。

::sub-line子控件用来对减少一行的按钮进行样式设置。默认情况下，sub-line子控件被放置在组件边框区域的左上角。默认情况下，箭头放置在sub-line子控件内容区域的中心。

::sub-page子控件用来对减一页作用的滑块区域进行样式设置。::add-page子控件用来对起到加一页作用的滑块区域进行样式设置。

参考自定义QScrollBar示例。

QSizeGrip

支持width、height和image属性。

参考自定义QSizeGrip示例。

QSlider

支持盒子模型。对于水平滑动器，必须提供min-width和height属性。对于竖直滑动器，必须提供min-height和width属性。

滑动器的滑槽使用::groove进行样式设置。默认情况下，滑槽被放置在组件的内容区域中。滑动器的滑块使用::handle子控件进行样式设置。子控件在滑槽的内容区域中移动。

参考自定义QSlider示例。

QSpinBox

QDateEdit

QDateTimeEdit

QDoubleSpinBox

QTimeEdit

旋转框的框架使用盒子模型来进行样式设置。

向上按钮和箭头可使用::up-button和::up-arrow子控件来进行样式设置。默认情况下，向上按钮被放置在组件填充区域的右上角。如果没有显式设置尺寸，会占据参考区域的一半高度。向上箭头被放置在向上按钮的内容区域的中心。

向下按钮和箭头使用::down-button和::down-arrow子控件进行样式设置。默认情况下，向下按钮被放置在组件填充区域的右下角。如果没有显式设置尺寸，会占据参考区域的一半高度。向下箭头被放置在向下按钮的内容区域的中心。

参考自定义QSpinBox示例。

QSplitter

支持盒子模型。分割器的句柄使用::handle子控件进行样式设置。

参考自定义QSplitter示例。

QStatusBar

只支持background属性。单个项的框架使用::item子控件进行样式设置。

参考自定义QStatusBar示例。

QTabBar

单个标签使用::tab子控件进行样式设置。关闭按钮使用::close-button子控件进行样式设置。标签支持 only-one、:first、:last、:middle、:previous–selected、:next-selected、:selected伪状态。

标签的方向决定是否有:top、:left、:right、:bottom伪状态。

对于选中状态的重叠标签通过使用负数的边距或绝对位置模式来创建。

QTabBar的分离指示器使用::tear子控件进行样式设置。

QTabBar用两个QToolButtons作为滚动器，使用QTabBar QToolButton选择器进行样式设置。使用::scroller子控件指定滚动按钮的宽度。

QTabBar中标签的对齐方式使用alignment属性进行设置。

警告：要改变QTabWidget中的QTabBar的位置，使用tab-bar子控件。

参考自定义QTabBar示例。

QTabWidget

标签组件的框架使用::pane子控件进行样式设置。左边角和右边角分别使用::left-corner和::right-corner进行样式设置。标签条的位置使用::tab-bar子控件控制。

默认情况下，QTabWidget的子控件的位置按照QWindowsStyle风格来确定。要将QTabBar放置在中央的位置，设置tab-bar子控件的subcontrol-position属性。

标签组方向决定是否有:top、:left、:right、:bottom伪状态。

参考自定义QTabWidget示例。

QTableView

支持盒子模型。如果交替改变行颜色功能开启，交替的颜色使用alternate-background-color属性进行样式设置。

选中的项的颜色和背景分别是使用selection-color和selection-background-color进行样式设置。

QTableView中的边角组件由QAbstractButton实现，使用QTableViewQTableCornerButton::section选择器进行样式设置。

警告：如果只在QTableCornerButton上设置背景色，背景可能不会显示出来，除非将边框属性设置成某个值。这是因为，默认情况下，QTableCornerButton会绘制一个完全覆盖背景色的本地边框。

网格的颜色使用gridline-color属性进行设置。

参考QAbsractScrollArea以了解如何设置可滚动的背景。

参考自定义QTableView示例。

QTextEdit

支持盒子模型。

选中文字的颜色和背景分别使用selection-color和selection-background-color进行样式设置。

参考QAbsractScrollArea以了解如何设置可滚动的背景。

QToolBar

支持盒子模型。

工具栏所在的区域（停靠方向）决定是否会有:top、:left、:right、:bottom伪状态。

:first、:last、:middle、:only-one伪状态指示工具栏的位置是一个线性组（参考QStyleOptionToolBar::positionWithinLine）

QToolBar的分隔符使用::separator子控件进行样式设置。

用来移动工具栏的句柄使用::handle子控件进行样式设置。

参考自定义QToolBar示例。

QToolButton

支持盒子模型。

如果QToolButton有菜单，::menu-indicator子控件用来对菜单指示器进行样式设置。默认情况下，菜单指示器放置在组件填充区域的右下角。

如果QToolButton是QToolButton::MenuButtonPopup模式，::menu-button子控件用来绘制菜单按钮。::menu-arrow子控件用来在菜单按钮里面绘制菜单箭头。默认情况下，菜单按钮子控件位于内容区域的中心。

当QToolButton显示箭头时，会使用::up-arrow、::down-arrow、::left-arrow和::right-arrow子控件。

警告：如果只在QToolButton 设置背景色，背景可能不会显示出来，除非将边框属性设置成某个值。这是因为，默认情况下，QToolButton会绘制一个完全覆盖背景色的本地边框。例如，

QToolButton { border: none; }

参考自定义QToolButton示例。

QToolBox

支持盒子模型。

单个标签使用::tab子控件进行样式设置。标签支持 :only-one、:first、:last、:middle、:previous-selected、:next-selected、:selected伪状态。

QToolTip

支持盒子模型。opacity属性控制工具提示的透明度。

参考自定义QFrame示例（QToolTip是QFrame）。

QTreeView

QTreeWidget

QTableWidget

支持盒子模型。如果交替改变行颜色功能开启，交替的颜色使用alternate-background-color属性进行样式设置。

选中项的颜色和背景分别是使用selection-color和selection-background-color进行样式设置。

选择行为由show-decoration-selected属性进行控制。

树型视图的分支使用::branch子控件进行样式设置。::branch子控件支持:open、:closed、:has-sibling和:has-children伪状态。

使用::item子控件对QTreeView中的项进行更精细控制。

参考QAbsractScrollArea以了解如何设置可滚动的背景。

参考自定义QTreeView示例以了解如何对分支进行样式设置。

QWidget

只支持background、background-clip和background-origin属性。

如果从QWidget派生子类，需要为自定义组件提供绘制事件处理函数（paintEvent）：

void CustomWidget::paintEvent(QPaintEvent *)

{

QStyleOption opt;

opt.init(this);

QPainter p(this);

style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

如果没有设置样式单，以上的代码不起任何作用。

警告：确保在自定义组件中定义了Q_OBJECT宏。

 

 

 

六、QT样式表实例
1、样式表的使用
A、定制前景色和背景色

    设置应用程序中的所有QLineEdit组件的背景色为黄色

    qApp->setStyleSheet("QLineEdit {

    如果只想要属性用于具体某个对话框的QLineEdit及子类组件。

    myDialog->setStyleSheet("QLineEdit {

    如果只想将属性用于某个具体的QLineEdit组件，可以使用QObject::setObjectName() 和ID选择器。

    myDialog->setStyleSheet("QLineEdit#nameEdit {

    可以直接设置QLieEdit组件的background-color属性，忽略选择器

    nameEdit->setStyleSheet("

    为了确保对比效果，应该指定文本合适的颜色

    nameEdit->setStyleSheet("color: blue;

    修改选中文本的颜色如下：

    nameEdit->setStyleSheet("color: blue;"

                          ""

                          "selection-color: yellow;"

                          "selection-");

B、使用动态属性定制样式

为了提示用户字段是必填的，对这些字段使用黄色作为背景色。要使用QT样式表是现实很容易的。首先，应该使用应用程序的样式表：

*[mandatoryField="true"] { margin: 0px; clear: both; height: auto; overflow: hidden; color: rgb(85, 85, 85); font-family: 宋体, "Arial Narrow", arial, serif; text-indent: 28px; text-align: justify;">这意味着mandatoryField字段设置为true的组件的背景色为黄色。

对于每个必备字段组件，我们匆忙中简单创建了一个mandatoryField属性并设置为true。

    QLineEdit *nameEdit = new QLineEdit(this);

    nameEdit->setProperty("mandatoryField", true);

 

    QLineEdit *emailEdit = new QLineEdit(this);

    emailEdit->setProperty("mandatoryField", true);

 

   QSpinBox *ageSpinBox = new QSpinBox(this);

   ageSpinBox->setProperty("mandatoryField", true);

C、使用盒子模型定制QPushButton

本节我们展示如何创建一个红色的按钮。

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

D、定制按钮菜单指示器子控件

    子控件可以访问组件的子元素。例如，按钮会使用QPushButton::setMenu()关联菜单与菜单指示器。定制红色按钮的菜单指示器如下：

QPushButton#evilButton::menu-indicator

{

      image: url(myindicator.png);

 }

    默认，菜单指示器定位在衬底区域的右下角。通过改变subcontrol-position、subcontrol-origin属性可以定位指示器。

QPushButton::menu-indicator

{

      image: url(myindicator.png);

      subcontrol-position: right center;

      subcontrol-origin: padding;

      left: -2px;

  }

    Myindicator.png的位置在按钮衬底区域的右中心。

E、复杂选择器示例

    设置应用程序样式表中QLineEdit文本为红色。

    QLineEdit { color: red }

    然而，想要设置一个只读QLineEdit的文本颜色为灰色如下：

    QLineEdit { color: red }

    QLineEdit[readOnly="true"] { color: gray }

    某些情况下，如果要求注册表单中的所有QLineEdit为棕色。

    QLineEdit { color: red }

     QLineEdit[readOnly="true"] { color: gray }

     #registrationDialog QLineEdit { color: brown }

    如果要求所有对话框中的QLineEdit为棕色。

    QLineEdit { color: red }

    QLineEdit[readOnly="true"] { color: gray }

    QDialog QLineEdit { color: brown }

 

2、定制特殊组件
本节提供使用样式表定制特定组件的实例。

（1）、定制QAbstractScrollArea

任何QAbstractScrollArea组件(项视图、QTextEdit、QTextBrowser)的背景都可以使用bakcground属性设置。例如，设置带有滚动条滚动的背景图属性如下：

QTextEdit, QListView 

{

      

      background-image: url(draft.png);

      background-attachment: scroll;

  }

如果设置background-image属性在视口中固定。

QTextEdit, QListView 

{

      

      background-image: url(draft.png);

      background-attachment: fixed;

  }

（2）、定制QCheckBox

进行QCheckBox样式设置与QRadioButton样式设置相同。主要区别在于三态的QCheckBox有一个模糊态。

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

（3）、定制组合框QComboBox

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

    组合框的弹出菜单是QAbstractItemView，使用后代选择器进行样式设置。

  QComboBox QAbstractItemView {

      border: 2px solid darkgray;

      selection-

  }

（4）、定制QDockWidget

QDockWidget的标题栏和按钮可以按如下进行样式设置。

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

如果要移动停靠组件按钮到左侧，可以使用如下样式表设置：

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

（5）、定制QFrame

QFrame, QLabel, QToolTip 

{

      border: 2px solid green;

      border-radius: 4px;

      padding: 2px;

      background-image: url(images/welcome.png);

}

（6）、定制QGroupBox

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

（7）、定制QHeaderView

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

（8）、定制QLineEdit

QLineEdit的框架使用盒子模型进行样式设置。

QLineEdit 

{

    border: 2px solid gray;

    border-radius: 10px;

    padding: 0 8px;

    background: yellow;

    selection-background-color: darkgray;

}

QLineEdit的密码字符使用QLineEdit::Password显示模式设置。

QLineEdit[echoMode="2"] 

{

    lineedit-password-character: 9679;

}

只读QLineEdit的背景可以如下修改：

QLineEdit:read-only 

{

    background: lightblue;

}

 

可以参考的文章链接：

http://9291927.blog.51cto.com/9281927/1888380/

http://9291927.blog.51cto.com/9281927/1888395

http://9291927.blog.51cto.com/9281927/1888400

http://blog.csdn.net/goforwardtostep/article/details/60884870

http://blog.csdn.net/GoForwardToStep/article/details/64169734

http://blog.csdn.net/GoForwardToStep/article/details/65451416