#ifndef POLYNOMIALS_POLYNOMIALS_H
#define POLYNOMIALS_POLYNOMIALS_H

#include<iostream>
#include<cmath>
using namespace std;
#define MAX_POLYNOMIALS_COUNTS 10      //现有的方法就是把上限值调大，从而规避后面的设计缺陷
//多项式底层采用链表这一种数据结构
//每一项表示一个节点
typedef struct Node{
    float coefficient;       //系数
    int exponent;       //指数
    struct Node* next;
    Node():coefficient(-99),exponent(-99),next(nullptr){}
    Node(float coef,int expo,Node* p):coefficient(coef),exponent(expo),next(p){}
}Node;

//使用c++面向对象编程思想，用类描述一个一元多项式
class poly{
private:
    Node* head;  //头节点,不存储有效项
    int m;   //项数(后面在实现过程中发现并不必要)
public:
    poly();
    ~poly();
    //拷贝构造
    poly(const poly &poly);
    void operator=(poly poly);
    //添加项(辅助函数,同时也是构建、加减乘的核心函数)
    void insert(float coef,int expo);
    //构建多项式
    void construct(int nums_of_terms);
    //打印多项式
    void print();
    //多项式加法
    poly add(poly &poly);
    poly operator+(poly &poly);
    //多项式减法
    poly sub(poly &poly);
    poly operator-(poly &poly);
    //计算多项式在x处的值
    double compute(float x);
    //多项式乘法
    poly mul(poly &poly);
    poly operator*(poly &poly);
    //复合赋值运算符
    void operator+=(poly& poly);
    void operator-=(poly& poly);
    //void operator*=(poly& poly);  //暂且未能实现复合乘法运算，因此乘法暂时只能实现两个多项式相乘，后续会尽力完善相关功能
    //多项式求导
    poly derivative(int n);  //在一阶导的基础上扩展了求n阶导
    //多项式删除(归0)
    void clear();
};

#endif //POLYNOMIALS_POLYNOMIALS_H
