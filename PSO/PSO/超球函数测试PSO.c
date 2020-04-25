
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"

#define RANDF ((rand()%10000+rand()%10000*10000)/100000000.0) //产生0-1随机浮点数
#define DIM 3//维数
#define NUM 4//粒子数

const double c1 = 2.0;//参数
const double c2 = 2.0;//参数
double xmin = -100.0;//位置下限
double xmax = 100.0;//位置上限
double gbestx[DIM];//全局最优位置
double gbestf;//全局最优适应度

struct particle 
{
    //定义一个粒子
    double x[DIM];//当前位置矢量
    double bestx[DIM];//历史最优位置
    double f;//当前适应度
    double bestf;//历史最优适应度
}swarm[NUM];//定义粒子群


double f1(double x[]) 
{
    //超球函数
    float z = 0;
    for (int i = 0; i < DIM; i++)
        z += (x[i]) * (x[i]);
    return z;
}

void main() {
    for (int i = 0; i < DIM; i++) 
    {
        //初始化全局最优
        gbestx[i] = RANDF * (xmax - xmin) + xmin;
    }
    gbestf = 100000000000000.0;
    for (int i = 0; i < NUM; i++) 
    {
        //初始化粒子群
        struct particle* p1 = &swarm[i];
        for (int j = 0; j < DIM; j++)
            p1->x[j] = RANDF * (xmax - xmin) + xmin;
        p1->f = f1(p1->x);
        p1->bestf = 100000000000000.0;
    }
    for (int t = 0; t < 5000; t++) //结束条件：进行5000次搜索
    {
        for (int i = 0; i < NUM; i++) 
        {
            struct particle* p1 = &swarm[i];//p1:第i个粒子
            for (int j = 0; j < DIM; j++)
            {
                //进化方程
                p1->x[j] += c1 * RANDF * (p1->bestx[j] - p1->x[j])+ c2 * RANDF * (gbestx[j] - p1->x[j]);
            }
            p1->f = f1(p1->x);
            if (p1->f < p1->bestf)
            {
                //改变历史最优适应度
                for (int j = 0; j < DIM; j++)
                    p1->bestx[j] = p1->x[j];
                p1->bestf = p1->f;
            }
            if (p1->f < gbestf)
            {
                //改变全局最优适应度
                for (int j = 0; j < DIM; j++)
                    gbestx[j] = p1->x[j];
                for (int j = 0; j < DIM; j++)
                {
                    //把当前全局最优的粒子随机放到另一位置
                    p1->x[j] = RANDF * (xmax - xmin) + xmin;
                }
                gbestf = p1->f;
            }
        }
    }
    printf("%g\n", gbestf);
}
