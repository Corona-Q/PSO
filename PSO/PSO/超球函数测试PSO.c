
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"

#define RANDF ((rand()%10000+rand()%10000*10000)/100000000.0) //����0-1���������
#define DIM 3//ά��
#define NUM 4//������

const double c1 = 2.0;//����
const double c2 = 2.0;//����
double xmin = -100.0;//λ������
double xmax = 100.0;//λ������
double gbestx[DIM];//ȫ������λ��
double gbestf;//ȫ��������Ӧ��

struct particle 
{
    //����һ������
    double x[DIM];//��ǰλ��ʸ��
    double bestx[DIM];//��ʷ����λ��
    double f;//��ǰ��Ӧ��
    double bestf;//��ʷ������Ӧ��
}swarm[NUM];//��������Ⱥ


double f1(double x[]) 
{
    //������
    float z = 0;
    for (int i = 0; i < DIM; i++)
        z += (x[i]) * (x[i]);
    return z;
}

void main() {
    for (int i = 0; i < DIM; i++) 
    {
        //��ʼ��ȫ������
        gbestx[i] = RANDF * (xmax - xmin) + xmin;
    }
    gbestf = 100000000000000.0;
    for (int i = 0; i < NUM; i++) 
    {
        //��ʼ������Ⱥ
        struct particle* p1 = &swarm[i];
        for (int j = 0; j < DIM; j++)
            p1->x[j] = RANDF * (xmax - xmin) + xmin;
        p1->f = f1(p1->x);
        p1->bestf = 100000000000000.0;
    }
    for (int t = 0; t < 5000; t++) //��������������5000������
    {
        for (int i = 0; i < NUM; i++) 
        {
            struct particle* p1 = &swarm[i];//p1:��i������
            for (int j = 0; j < DIM; j++)
            {
                //��������
                p1->x[j] += c1 * RANDF * (p1->bestx[j] - p1->x[j])+ c2 * RANDF * (gbestx[j] - p1->x[j]);
            }
            p1->f = f1(p1->x);
            if (p1->f < p1->bestf)
            {
                //�ı���ʷ������Ӧ��
                for (int j = 0; j < DIM; j++)
                    p1->bestx[j] = p1->x[j];
                p1->bestf = p1->f;
            }
            if (p1->f < gbestf)
            {
                //�ı�ȫ��������Ӧ��
                for (int j = 0; j < DIM; j++)
                    gbestx[j] = p1->x[j];
                for (int j = 0; j < DIM; j++)
                {
                    //�ѵ�ǰȫ�����ŵ���������ŵ���һλ��
                    p1->x[j] = RANDF * (xmax - xmin) + xmin;
                }
                gbestf = p1->f;
            }
        }
    }
    printf("%g\n", gbestf);
}
