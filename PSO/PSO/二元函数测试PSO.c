#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"

#define RAND ((rand()%10000+rand()%10000*10000)/100000000.0) //产生0-1随机浮点数
#define DIM 2//维数
#define NUM 3//粒子数

struct particle
{
	double x[DIM];//位置矢量
	double bestx[DIM];//历史最优位置
	double f;//适应度
	double bestf;//历史最优适应度
}swarm[NUM];

const double c1 = 2.0;//参数
const double c2 = 2.0;//参数
double xmin = -10.0;//位置下限
double xmax = 10.0;//位置上限
double gbestx[DIM];//全局最优位置
double gbestf;//全局最优适应度

double fx(double x[])//y=x1^2+x2^2
{  
	double y=0;
	for (int i = 0; i < DIM; i++)
	{
		y += x[i] * x[i];
	}
	return y;
}

void main()
{
	int i = 0;
	int j = 0;
	int t = 0;
	for (i = 0; i < DIM; i++)
	{
		//初始化全局最优位置
		gbestx[i] = RAND * (xmax - xmin) + xmin;

	}
	gbestf = 100000000000.0;
	for (i = 0; i < NUM; i++) 
	{
		//初始化粒子群
		struct particle* p = &swarm[i];
		for (j = 0; j < DIM; j++)
		{
			p->x[j]= RAND * (xmax - xmin) + xmin;
		}
		p->f = fx(p->x);
		p->bestf = 100000000000.0;
	}
	for (t = 0; t < 1000; t++)//迭代t次
	{
		for (i = 0; i < NUM; i++)
		{
			struct particle* p = &swarm[i];
			for (j = 0; j < DIM; j++)
			{
				//公式（1）（2）
				p->x[j] += c1 * RAND * (p->bestx[j] - p->x[j]) + c2 * RAND * (gbestx[j] - p->x[j]);
			}
			p->f = fx(p->x);
			if (p->f < p->bestf)
			{
				//改变历史最优适应度
				for (j = 0; j < DIM; j++)
				{
					p->bestx[j] = p->x[j];
				}
				p->bestf = p->f;
			}
			if (p->f < gbestf)
			{
				//改变全局最优适应度
				for (j = 0; j < DIM; j++)
				{
					gbestx[j] = p->x[j];
				}
				for (j = 0; j < DIM; j++)
				{
					//把当前全局最优的粒子随机放到另一位置
					p->x[j] = RAND * (xmax - xmin) + xmin;
				}
				gbestf = p->f;
			}
		}
	}
	printf("%lf\n", gbestf);
}