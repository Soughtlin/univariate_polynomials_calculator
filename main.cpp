#include"polynomials.h"
#include"menu.h"
using namespace std;

int main() {
    showMenu();
    poly *polynomials[MAX_POLYNOMIALS_COUNTS];
    for (int i = 0; i < MAX_POLYNOMIALS_COUNTS; i++) polynomials[i] = new poly;
    int poly_counts = 0;
    while (true) {
        if (poly_counts >= MAX_POLYNOMIALS_COUNTS) {
            printf("注意存储的多项式数目已达上限，无法继续添加\n");
        }
        printf("请选择操作>:");
        int choice;
        cin >> choice;
        if (choice == 0) {  //退出计算器
            printf("Goodbye!\n");
            break;
        }
        int cnt;
        switch (choice) {
            case 1: {  //显示多项式
                if (poly_counts) { printf("以下是已构建的多项式:\n"); }
                else {
                    printf("现在没有多项式哦owo\n");
                    break;
                }
                for (int i = 0; i < poly_counts; i++) {
                    printf("P%d=", i + 1);
                    polynomials[i]->print();
                }
            }
                break;
            case 2: {  //构建多项式
                if (poly_counts >= MAX_POLYNOMIALS_COUNTS) {
                    printf("存储的多项式数目已达上限,禁止构建!\n");
                }
                polynomials[poly_counts] = new poly;
                printf("请输入多项式的项数>:");
                int m;
                cin >> m;
                polynomials[poly_counts]->construct(m);
                poly_counts++;
            }
                break;
            case 3: {  //加
                poly *tmp = new poly;
                printf("请输入想要求和的多项式个数>:");
                cin >> cnt;
                printf("请输入想要求和的多项式(求差方式为从前向后依次减)对应数字序号>:");
                while (cnt--) {
                    int p;
                    cin >> p;
                    if (p < 0 || p > poly_counts) {
                        printf("不存在此多项式，请重新输入!\n");
                        cnt++;
                        continue;
                    }
                    *tmp += *polynomials[p - 1];   //输入序号与对应的数组下标差1
                }
                //这下面的部分对于加减乘导都是几乎一样的，后续完善或许可以单拉出一个function来覆盖这块代码，提高代码可读性
                printf("求和的结果为:");
                tmp->print();
                if (poly_counts < MAX_POLYNOMIALS_COUNTS) {
                    printf("请问是否要保存？\n1:是 0:否\n");
                    int x;
                    cin >> x;
                    if (x == 1) {
                        *polynomials[poly_counts] = *tmp;
                        poly_counts++;
                        printf("已保存在P%d\n", poly_counts);
                    }
                }
            }
                break;
            case 4: {  //减
                poly *tmp = new poly;
                printf("请输入想要求差的多项式个数>:");
                cin >> cnt;
                printf("请输入想要求差的多项式(求差方式为从前向后依次减)对应数字序号>:");
                while (cnt--) {
                    int p;
                    cin >> p;
                    if (p < 0 || p > poly_counts) {
                        printf("不存在此多项式，请重新输入!\n");
                        cnt++;
                        continue;
                    }
                    *tmp -= *polynomials[p - 1];
                }
                printf("求差的结果为:");
                tmp->print();
                if (poly_counts < MAX_POLYNOMIALS_COUNTS) {
                    printf("请问是否要保存？\n1:是 0:否\n");
                    int x;
                    cin >> x;
                    if (x == 1) {
                        *polynomials[poly_counts] = *tmp;
                        poly_counts++;
                        printf("已保存在P%d\n", poly_counts);
                    }
                }
            }
                break;
            case 5: {  //乘
                poly *tmp = new poly;
                while (true) {
                    printf("请输入想要求积的2个多项式对应数字序号>:");
                    int p1, p2;
                    cin >> p1 >> p2;
                    if (p1 < 0 || p1 > poly_counts || p2 < 0 || p2 > poly_counts) {
                        printf("不存在此多项式，请重新输入!\n");
                        continue;
                    }
                    *tmp = *polynomials[p1 - 1] * *polynomials[p2 - 1];
                    break;
                }
                printf("求积的结果为:");
                tmp->print();
                if (poly_counts < MAX_POLYNOMIALS_COUNTS) {
                    printf("请问是否要保存？\n1:是 0:否\n");
                    int x;
                    cin >> x;
                    if (x == 1) {
                        *polynomials[poly_counts] = *tmp;
                        poly_counts++;
                        printf("已保存在P%d\n", poly_counts);
                    }
                }
            }
                break;
            case 6: {  //求导
                poly *tmp = new poly;
                while (true) {
                    printf("请输入要求导的多项式序号>:");
                    int p;
                    cin >> p;
                    printf("请输入要求的导数阶数>:");
                    int n;
                    cin >> n;
                    if (p < 0 || p > poly_counts) {
                        printf("不存在此多项式，请重新输入!\n");
                        continue;
                    }
                    *tmp = polynomials[p - 1]->derivative(n);;
                    break;
                }
                printf("求导的结果为:");
                tmp->print();
                if (poly_counts < MAX_POLYNOMIALS_COUNTS) {
                    printf("请问是否要保存？\n1:是 0:否\n");
                    int x;
                    cin >> x;
                    if (x == 1) {
                        *polynomials[poly_counts] = *tmp;
                        poly_counts++;
                        printf("已保存在P%d\n", poly_counts);
                    }
                }
            }
                break;
            case 7: {  //求在x处的值
                while (true) {
                    printf("请输入要求值的多项式序号>:");
                    int p;
                    cin >> p;
                    printf("请输入变量x的值>:");
                    float x;
                    cin >> x;
                    if (p < 0 || p > poly_counts) {
                        printf("不存在此多项式，请重新输入!\n");
                        continue;
                    }
                    cout << "P" << p << "在x=" << x << "处的值为" << polynomials[p - 1]->compute(x) << endl;
                    break;
                }
            }
                break;
            case 8: {  //删除多项式
                while (true) {
                    printf("请选择想要删除的多项式的序号>:");
                    int p;
                    cin >> p;
                    if (p < 0 || p > poly_counts) {
                        printf("不存在此多项式，请重新输入!\n");
                        continue;
                    }
                    polynomials[p - 1]->clear();
                    for (int i = p - 1; i < poly_counts - 1; i++) {
                        polynomials[i] = polynomials[i + 1];
                    }
                    poly_counts--;
                    break;
                }
            }
                break;
            case 9:{
                showMenu();
                break;
            }
            default:
                printf("输入违法，请重新输入!\n");
        }
    }
    return 0;
}
