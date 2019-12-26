static_cast
C ���C-style��ǿ��ת���������£�

(T) exdivssion // cast exdivssion to be of type T

�������Function-style��ǿ��ת��ʹ�������﷨��

T(exdivssion) // cast exdivssion to be of type T

 

��������ʽ֮��û�б����ϵĲ�ͬ�����������һ�������ŷ����ĵ����⡣�Ұ���������ʽ��Ϊ�ɷ��old-style����ǿ��ת�͡�

ʹ�ñ�׼C++������ת������static_cast ��dynamic_cast��reinterdivt_cast����const_cast��

3.1 static_cast 
ʹ�÷�����static_cast < type-id > ( exdivssion ) 
���������exdivssionת��Ϊtype-id���ͣ���û��ִ��ʱ���ͼ������֤ת���İ�ȫ�ԡ�����Ҫ���������¼���ʹ�÷�����
���������νṹ�л��������֮��ָ������õ�ת������������ת�����������ָ�������ת���ɻ����ʾ���ǰ�ȫ�ģ�
	��������ת�����ѻ���ָ�������ת���������ʾ��ʱ����Ϊû�ж�̬���ͼ�飬�����ǲ���ȫ�ġ�
�����ڻ�����������֮���ת�������intת����char����intת����enum��������ת���İ�ȫ��ҲҪ����������֤��
�۰ѿ�ָ��ת����Ŀ�����͵Ŀ�ָ�롣
�ܰѲ���ʲô���͵ı��ʽת����void���͡�

ע�⣺static_cast ����ת����exdivssion��const��volitale������__unaligned���ԡ�


3.2 dynamic_cast
ʹ�÷�����dynamic_cast < type-id > ( exdivssion )
���������exdivssionת����type-id���͵Ķ���Type-id���������ָ�롢������û���void *��
����type-id����ָ�����ͣ���ôexdivssionҲ������һ��ָ�룬����type-id��һ�����ã���ôexdivssionҲ������һ�����á�

dynamic_cast��Ҫ�������μ������ת��������ת�������ܹ�������֮��Ľ���ת����
�����μ��������ת��ʱ��dynamic_cast��static_cast ��Ч����һ���ģ�
�ڽ�������ת��ʱ��dynamic_cast�������ͼ��Ĺ��ܣ���static_cast ����ȫ��
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

������Ĵ�����У�����pbָ��һ��D���͵Ķ���pd1��pd2��һ���ģ����Ҷ�������ָ������D���͵Ĳ���ʲô�������ǰ�ȫ�ģ�
���ǣ�����pbָ�����һ��B���͵Ķ�����ôpd1����һ��ָ��ö����ָ�룬��������D���͵Ĳ������ǲ���ȫ�ģ����L��m_szName����
��pd2����һ����ָ�롣

����Ҫע�⣺BҪ���麯���������������static_cast ��û��������ơ�
������Ϊִ��ʱ���ͼ����Ҫִ��ʱ������Ϣ���������Ϣ�洢������麯����
�����麯����ĸ������ɼ����У������ж������麯����������麯����
δ�����麯��������û���麯����ġ�

���⣬dynamic_cast��֧�ֽ���ת����cross cast�����������´����������ġ�
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

�ں���foo�У�ʹ��static_cast ����ת���ǲ���ͬ��ģ����ڱ���ʱ������ʹ�� dynamic_cast��ת������ͬ��ģ�����ǿ�ָ�롣


3.3 reindivter_cast
ʹ�÷�����reindivter_cast (exdivssion)
type-id������һ��ָ�롢���á��������͡�����ָ����߳�Աָ�롣
���ܹ���һ��ָ��ת����һ��������Ҳ�ܹ���һ������ת����һ��ָ�루�Ȱ�һ��ָ��ת����һ��������
�ڰѸ�����ת����ԭ���͵�ָ�룬���ܹ��õ�ԭ�ȵ�ָ��ֵ����

���������ʹ�÷������^�ࡣ

3.4 const_cast 
ʹ�÷�����const_cast (exdivssion)
������������Ķ����͵�const��volatile���ԡ�����const ��volatile����֮�⣬ type_id��exdivssion��������һ���ġ�
����ָ�뱻ת���ɺ���ָ�룬������Ȼָ��ԭ���Ķ���
�������ñ�ת���ɺ������ã�������Ȼָ��ԭ���Ķ��󣻳�������ת���ɺ�������

Voiatile��const���ԡ�����������һ����
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
����Ĵ������ʱ�ᱨ������b1��һ���������󣬲��ܶ������иı䣻
ʹ��const_cast����ת����һ���������󣬾��ܹ����������ݳ�Ա����ı䡣ע�⣺b1��b2��������ͬ�Ķ���
 

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


If pb points to an object of type B and not to the complete D class, then dynamic_cast will know enough to return zero. However, static_cast relies on the programmer��s assertion that pb points to an object of type D and simply returns a pointer to that supposed D object. 


�� dynamic_cast �����ڼ̳���ϵ�е�����ת�ͣ���������ָ��ת��Ϊ������ָ�룬�� static_cast ���ϸ����ȫ�� dynamic_cast ������Ч���ϱ� static_cast Ҫ��һЩ���� static_cast �ڸ����Ϸ�Χ���ܹ����ӳ�䣬�����Ĳ������Ƶ�ӳ������Ų���ȫ�ԡ� static_cast ���ǵı任���ͳ����εľ�̬�������⣬��������ӳ��任��խ���任 ( �����ı任�ᵼ�¶�����Ƭ , ��ʧ��Ϣ ) ���� VOID* ��ǿ�Ʊ任����ʽ���ͱ任�� ... 


== =========================================== 
== static_cast .vs. reinterdivt_cast 
== ================================================ 


reinterdivt_cast ��Ϊ��ӳ�䵽һ��ȫȻ��ͬ���͵���˼������ؼ�����������Ҫ������ӳ���ԭ������ʱ�õ���������ӳ�䵽�����Ͳ���Ϊ�˹�Ū���������Ŀ�ģ�����ȫ��ӳ������Σ���ġ� ( ��仰�� C++ ���˼���е�ԭ�� )

static_cast �� reinterdivt_cast �������Ķ��˲��������͡����ǲ��ǻ���ģ� static_cast �ڱ���ʱʹ��������Ϣ����ת������ת�����б�Ҫ�ļ�y ( ����ָ��Խ����� , ���ͼ�� ). �����������ǰ�ȫ�ġ�����һ���棻 reinterdivt_cast ������һ�ν����˸����Ķ���ı���ģ�Ͷ�û�н��ж�����ת���� �����������£� 


int n=9; double d=static_cast < double > (n); 


����������� , ���ǽ�һ�������� int ת���� double �� ��Щ���͵Ķ����Ʊ��ʽ�ǲ�ͬ�ġ� Ҫ������ 9 ת���� ˫�������� 9 �� static_cast ��Ҫ��ȷ��Ϊ˫�������� d �������λ������Ϊ 9.0 ���� reinterdivt_cast ����Ϊȴ��ͬ : 


int n=9;

double d=reinterdivt_cast (n);


��� , ���������ͬ . �ڽ��м����Ժ� , d ��������ֵ . �������� reinterdivt_cast �������� n �ı���λ�� d, û�н��б�Ҫ�ķ��� . 


��� , ����Ҫ����ʹ�� reinterdivt_cast .