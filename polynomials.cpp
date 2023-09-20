#include"polynomials.h"
using namespace std;
//实现构造、析构、construct和print等基本输入输出功能
poly::poly(){
    head=new Node;
    m=0;
}
poly::~poly(){
    Node* p=head;
    while(p){
        Node* tmp=p;
        p=p->next;
        delete tmp;
    }
    m=0;
}
poly::poly(poly const &poly){
    m=poly.m;
    head=new Node;
    Node* pobj=poly.head->next;
    Node* p=head;
    while(pobj){
        p->next=new Node(pobj->coefficient,pobj->exponent, nullptr);
        p=p->next;
        pobj=pobj->next;
    }
}
//此插入方式严格保证了多项式的降幂排列与无重复项，同时是下面同时也是构建函数、加减乘函数的核心，并能应用于以后有望添加的更多运算功能的实现中，大大提高了代码的复用性与可读性！
void poly::insert(float coef,int expo){
    Node* p=head->next;
    while(p){                        //输入系数和指数后对多项式进行遍历
        Node* pre=head;
        if(p->exponent==expo){       //如果发现有某项的指数与新加入的项的指数相同，则可以合并，即系数相加(可以不用先创建Node节点而先进行合并判断，这样就省去了开辟内存还要随即释放的麻烦)
            p->coefficient+=coef;
//            if(p->coefficient==0){    //缺陷1：理应在这里实现项的抵消，但这样操作有bug暂未想到更好的方法，在print中实现了表象的系数为0项不输出，实际这一项仍存在于多项式(链表)中
//                pre->next=p->next;
//                delete p;
//                m--;
//            }
            break;
        }
        pre=p;
        p=p->next;
    }
    if(p==nullptr){                  //如果p是空指针，说明多项式中不存在指数为expo的项，则需要新加入此项
        p=head->next;
        Node* pre=head;
        while(pre){
            if(!p||p->exponent<=expo){   //保证新输入的项可插入在多项式尾部
                pre->next=new Node(coef,expo,p);
                break;
            }
            pre=p;
            p=p->next;
        }
        m++;
    }
}
void poly::construct(int nums_of_terms){
    //m=nums_of_terms;
    printf("请依次输入每一项的系数和指数\n");
//一开始写的时候设置了函数返回值为poly而我函数内部实现时却忽略了return，ide在这里抛出了一个我从没见过的异常EXC_BREAKPOINT(code=1, subcode=0x100ae6e9c)
// 查阅大量资料并反复检查代码也没搞清是哪里的问题，最后完善函数时把返回值的问题修正后突然就跑通了
    while(nums_of_terms--){
        float coef;
        int expo;
        cin>>coef>>expo;                 //输入系数和指数
        this->insert(coef,expo);
    }
}
//我在原有实验报告要求的基础上进行了输出格式的优化，使其看起来更通俗易懂
void poly::print(){
    Node* pre=head;
    Node* p=head->next;
    if(!p){
        printf("0");
    }
    while(p){
        if(p->coefficient!=1&&p->coefficient!=-1) {
            if(p->exponent!=0&&p->exponent!=1) {
                if (pre == head) cout << p->coefficient << "x^" << p->exponent;
                else if (p->coefficient > 0) cout << "+" << p->coefficient << "x^" << p->exponent;
                else if (p->coefficient < 0) cout << p->coefficient << "x^" << p->exponent;
            }
            else if(p->exponent==0){
                if (pre == head) cout << p->coefficient;
                else if (p->coefficient > 0) cout << "+" << p->coefficient;
                else if (p->coefficient < 0) cout << p->coefficient;
            }
            else if(p->exponent==1){
                if (pre == head) cout << p->coefficient << "x";
                else if (p->coefficient > 0) cout << "+" << p->coefficient << "x";
                else if (p->coefficient < 0) cout << p->coefficient << "x";
            }
        }
        else if(p->coefficient==1){
            if(p->exponent!=0&&p->exponent!=1) {
                if (pre == head) cout << "x^" << p->exponent;
                else cout << "+" << "x^" << p->exponent;
            }
            else if(p->exponent==0) {
                if (pre == head) cout << p->coefficient;
                else cout << "+" << p->coefficient;
            }
            else if(p->exponent==1) {
                if (pre == head) cout << "x";
                else cout << "+" << "x";
            }
        }
        else if(p->coefficient==-1){
            if(p->exponent!=0&&p->exponent!=1) {
                if (pre == head) cout << "-x^" << p->exponent;
                else cout << "-x^" << p->exponent;
            }
            else if(p->exponent==0) {
                if (pre == head) cout << p->coefficient;
                else cout << p->coefficient;
            }
            else if(p->exponent==1) {
                if (pre == head) cout << "-x";
                else cout << "-x";
            }
        }
        pre=p;
        p=p->next;
    }
    printf("  共%d项\n",m);
}

//赋值运算符重载
void poly::operator=(poly poly){
    m=poly.m;
    Node* pobj=poly.head->next;
    Node* p=head;
    while(pobj){
        p->next=new Node(pobj->coefficient,pobj->exponent, nullptr);
        p=p->next;
        pobj=pobj->next;
    }
}

//加减乘及相应运算符重载
poly poly::add(poly &poly){
    class poly ret=*this;
    Node* p=poly.head->next;
    while(p){
        ret.insert(p->coefficient,p->exponent);  //复用函数提高效率
        p=p->next;
    }
    return ret;
}
poly poly::operator+(poly &poly){
    class poly ret=this->add(poly);
    return ret;
}
void poly::operator+=(poly& poly){
    //*this=this->add(poly);   //这种方式行不通
    Node* pobj=poly.head->next;
    while(pobj){
        this->insert(pobj->coefficient,pobj->exponent);
        pobj=pobj->next;
    }
}

poly poly::sub(poly &poly){
    class poly ret=*this;
    Node* p=poly.head->next;
    while(p){
        ret.insert(-p->coefficient,p->exponent);  //复用函数提高效率，只给coefficient前面加负号即可
        p=p->next;
    }
    return ret;
}
poly poly::operator-(poly &poly){
    return this->sub(poly);
}
void poly::operator-=(poly& poly){
    Node* pobj=poly.head->next;
    if(head->next==nullptr){
        while(pobj){
            this->insert(pobj->coefficient,pobj->exponent);
            pobj=pobj->next;
        }
        return ;
    }
    while(pobj){
        this->insert(-pobj->coefficient,pobj->exponent);
        pobj=pobj->next;
    }
}

poly poly::mul(poly &poly){
    class poly ret;
    Node* p1=head->next;
    Node* p2=poly.head->next;
    while(p1){
        p2=poly.head->next;
        while(p2){
            ret.insert(p1->coefficient*p2->coefficient,p1->exponent+p2->exponent);
            p2=p2->next;
        }
        p1=p1->next;
    }
    return ret;
}
poly poly::operator*(poly &poly){
    return this->mul(poly);
}

//计算多项式在x处的值
double poly::compute(float x){
    double ret=0;
    Node* p=head->next;
    while(p){
        ret+=p->coefficient*pow(x,p->exponent);
        p=p->next;
    }
    return ret;
}

//求n阶导数
poly poly::derivative(int n){
    class poly ret=*this;
    while(n--){
        Node* pre=ret.head;
        Node* p=ret.head->next;
        while(p){
            if(p->exponent==0){
                pre->next=p->next;
                Node* tmp=p;
                p=p->next;
                delete tmp;
            }
            else{
                p->coefficient*=p->exponent;
                p->exponent--;
                pre=p;
                p=p->next;
            }
        }
    }
    return ret;
}

void poly::clear(){
    Node* p=head->next;
    while(p){
        Node* tmp=p;
        p=p->next;
        delete tmp;
    }
    head->next=nullptr;
    printf("删除成功!\n");
}

//缺陷2:暂未能实现*=运算，所以暂时还无法支持多个多项式连续相乘的运算
//void poly::operator*=(poly& poly){
//    Node* p1=head->next;
//    Node* p2=poly.head->next;
//    if(p1==nullptr){
//        while(p2){
//            this->insert(p2->coefficient,p2->exponent);
//            p2=p2->next;
//        }
//    }
//    else {
//        class poly ret;
//        while(p1){
//            p2=poly.head->next;
//            while(p2){
//                ret.insert(p1->coefficient*p2->coefficient,p1->exponent+p2->exponent);
//                p2=p2->next;
//            }
//            p1=p1->next;
//        }
//        //*this=ret;   //关键是不知道这里怎么把p1和p2的结果覆盖到p1
//    }
//}