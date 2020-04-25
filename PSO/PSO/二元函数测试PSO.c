#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"

#define RAND ((rand()%10000+rand()%10000*10000)/100000000.0) //����0-1���������
#define DIM 2//ά��
#define NUM 3//������

struct particle
{
	double x[DIM];//λ��ʸ��
	double bestx[DIM];//��ʷ����λ��
	double f;//��Ӧ��
	double bestf;//��ʷ������Ӧ��
}swarm[NUM];

const double c1 = 2.0;//����
const double c2 = 2.0;//����
double xmin = -10.0;//λ������
double xmax = 10.0;//λ������
double gbestx[DIM];//ȫ������λ��
double gbestf;//ȫ��������Ӧ��

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
		//��ʼ��ȫ������λ��
		gbestx[i] = RAND * (xmax - xmin) + xmin;

	}
	gbestf = 100000000000.0;
	for (i = 0; i < NUM; i++) 
	{
		//��ʼ������Ⱥ
		struct particle* p = &swarm[i];
		for (j = 0; j < DIM; j++)
		{
			p->x[j]= RAND * (xmax - xmin) + xmin;
		}
		p->f = fx(p->x);
		p->bestf = 100000000000.0;
	}
	for (t = 0; t < 1000; t++)//����t��
	{
		for (i = 0; i < NUM; i++)
		{
			struct particle* p = &swarm[i];
			for (j = 0; j < DIM; j++)
			{
				//��ʽ��1����2��
				p->x[j] += c1 * RAND * (p->bestx[j] - p->x[j]) + c2 * RAND * (gbestx[j] - p->x[j]);
			}
			p->f = fx(p->x);
			if (p->f < p->bestf)
			{
				//�ı���ʷ������Ӧ��
				for (j = 0; j < DIM; j++)
				{
					p->bestx[j] = p->x[j];
				}
				p->bestf = p->f;
			}
			if (p->f < gbestf)
			{
				//�ı�ȫ��������Ӧ��
				for (j = 0; j < DIM; j++)
				{
					gbestx[j] = p->x[j];
				}
				for (j = 0; j < DIM; j++)
				{
					//�ѵ�ǰȫ�����ŵ���������ŵ���һλ��
					p->x[j] = RAND * (xmax - xmin) + xmin;
				}
				gbestf = p->f;
			}
		}
	}
	printf("%lf\n", gbestf);
}