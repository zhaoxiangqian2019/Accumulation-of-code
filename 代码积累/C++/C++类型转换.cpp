static_cast
C 风格（C-style）强制转型例如以下：

(T) exdivssion // cast exdivssion to be of type T

函数风格（Function-style）强制转型使用这种语法：

T(exdivssion) // cast exdivssion to be of type T

 

这两种形式之间没有本质上的不同，它纯粹就是一个把括号放在哪的问题。我把这两种形式称为旧风格（old-style）的强制转型。

使用标准C++的类型转换符：static_cast 、dynamic_cast、reinterdivt_cast、和const_cast。

3.1 static_cast 
使用方法：static_cast < type-id > ( exdivssion ) 
该运算符把exdivssion转换为type-id类型，但没有执行时类型检查来保证转换的安全性。它主要有例如以下几种使用方法：
①用于类层次结构中基类和子类之间指针或引用的转换。进行上行转换（把子类的指针或引用转换成基类表示）是安全的；
	进行下行转换（把基类指针或引用转换成子类表示）时，因为没有动态类型检查，所以是不安全的。
②用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这样的转换的安全性也要开发者来保证。
③把空指针转换成目标类型的空指针。
④把不论什么类型的表达式转换成void类型。

注意：static_cast 不能转换掉exdivssion的const、volitale、或者__unaligned属性。


3.2 dynamic_cast
使用方法：dynamic_cast < type-id > ( exdivssion )
该运算符把exdivssion转换成type-id类型的对象。Type-id必须是类的指针、类的引用或者void *；
假设type-id是类指针类型，那么exdivssion也必须是一个指针，假设type-id是一个引用，那么exdivssion也必须是一个引用。

dynamic_cast主要用于类层次间的上行转换和下行转换，还能够用于类之间的交叉转换。
在类层次间进行上行转换时，dynamic_cast和static_cast 的效果是一样的；
在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast 更安全。
class B{
public:
int m_iNum;
virtual void foo();
};

class D:public B{
public:
char *m_szName[100];
};

void func(B *pb){
D *pd1 = static_cast (pb);
D *pd2 = dynamic_cast(pb);
}

在上面的代码段中，假设pb指向一个D类型的对象，pd1和pd2是一样的，而且对这两个指针运行D类型的不论什么操作都是安全的；
可是，假设pb指向的是一个B类型的对象，那么pd1将是一个指向该对象的指针，对它进行D类型的操作将是不安全的（如訪问m_szName），
而pd2将是一个空指针。

另外要注意：B要有虚函数，否则会编译出错；static_cast 则没有这个限制。
这是因为执行时类型检查须要执行时类型信息，而这个信息存储在类的虚函数表（
关于虚函数表的概念，具体可见）中，仅仅有定义了虚函数的类才有虚函数表，
未定义虚函数的类是没有虚函数表的。

另外，dynamic_cast还支持交叉转换（cross cast）。例如以下代码所看到的。
class A{
public:
int m_iNum;
virtual void f(){}
};

class B:public A{
};

class D:public A{
};

void foo(){
B *pb = new B;
pb->m_iNum = 100;

D *pd1 = static_cast (pb); //compile error
D *pd2 = dynamic_cast(pb); //pd2 is NULL
delete pb;
}

在函数foo中，使用static_cast 进行转换是不被同意的，将在编译时出错；而使用 dynamic_cast的转换则是同意的，结果是空指针。


3.3 reindivter_cast
使用方法：reindivter_cast (exdivssion)
type-id必须是一个指针、引用、算术类型、函数指针或者成员指针。
它能够把一个指针转换成一个整数，也能够把一个整数转换成一个指针（先把一个指针转换成一个整数，
在把该整数转换成原类型的指针，还能够得到原先的指针值）。

该运算符的使用方法比較多。

3.4 const_cast 
使用方法：const_cast (exdivssion)
该运算符用来改动类型的const或volatile属性。除了const 或volatile修饰之外， type_id和exdivssion的类型是一样的。
常量指针被转化成很量指针，而且仍然指向原来的对象；
常量引用被转换成很量引用，而且仍然指向原来的对象；常量对象被转换成很量对象。

Voiatile和const类试。举例如以下一例：
class B{
public:
int m_iNum;
}
void foo(){
const B b1;
b1.m_iNum = 100; //comile error
B b2 = const_cast(b1);
b2. m_iNum = 200; //fine
}
上面的代码编译时会报错，由于b1是一个常量对象，不能对它进行改变；
使用const_cast把它转换成一个常量对象，就能够对它的数据成员随意改变。注意：b1和b2是两个不同的对象。
 

== ===========================================

== dynamic_cast .vs. static_cast 
== =========================================== 

class B { ... }; 
class D : public B { ... }; 

void f(B* pb) 
{

D* pd1 = dynamic_cast (pb);

D* pd2 = static_cast (pb); 
} 


If pb really points to an object of type D, then pd1 and pd2 will get the same value. They will also get the same value if pb == 0. 


If pb points to an object of type B and not to the complete D class, then dynamic_cast will know enough to return zero. However, static_cast relies on the programmer’s assertion that pb points to an object of type D and simply returns a pointer to that supposed D object. 


即 dynamic_cast 可用于继承体系中的向下转型，即将基类指针转换为派生类指针，比 static_cast 更严格更安全。 dynamic_cast 在运行效率上比 static_cast 要差一些，但 static_cast 在更宽上范围内能够完毕映射，这样的不加限制的映射伴随着不安全性。 static_cast 覆盖的变换类型除类层次的静态导航以外，还包含无映射变换、窄化变换 ( 这样的变换会导致对象切片 , 丢失信息 ) 、用 VOID* 的强制变换、隐式类型变换等 ... 


== =========================================== 
== static_cast .vs. reinterdivt_cast 
== ================================================ 


reinterdivt_cast 是为了映射到一个全然不同类型的意思，这个关键词在我们须要把类型映射回原有类型时用到它。我们映射到的类型不过为了故弄玄虚和其它目的，这是全部映射中最危急的。 ( 这句话是 C++ 编程思想中的原话 )

static_cast 和 reinterdivt_cast 操作符改动了操作数类型。它们不是互逆的； static_cast 在编译时使用类型信息运行转换，在转换运行必要的检測 ( 诸如指针越界计算 , 类型检查 ). 其操作数相对是安全的。还有一方面； reinterdivt_cast 不过又一次解释了给出的对象的比特模型而没有进行二进制转换， 样例例如以下： 


int n=9; double d=static_cast < double > (n); 


上面的样例中 , 我们将一个变量从 int 转换到 double 。 这些类型的二进制表达式是不同的。 要将整数 9 转换到 双精度整数 9 ， static_cast 须要正确地为双精度整数 d 补足比特位。其结果为 9.0 。而 reinterdivt_cast 的行为却不同 : 


int n=9;

double d=reinterdivt_cast (n);


这次 , 结果有所不同 . 在进行计算以后 , d 包括无用值 . 这是由于 reinterdivt_cast 不过复制 n 的比特位到 d, 没有进行必要的分析 . 


因此 , 你须要慎重使用 reinterdivt_cast .