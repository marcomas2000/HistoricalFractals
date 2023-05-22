#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define  MAXCOLORS 4

double lyap(double a, double b, double x, unsigned short s[]);
int cerca(double num);
void mktablog();

long colors[MAXCOLORS];
double   tab[5000];

int main(int argc, char* argv[])
{
    int ret = -1;
    unsigned short suc[20];
    char buf[2];
    FILE *fp = 0;
    double  l,a,b,x;
    int i,j,k,c0=0;
    int c1=0;
    int rit;
  
    if (argc < 6)
    {
        printf("Usage: LyapunovSpace <outFile> <juliaParamLx> <juliaParamLy> <resolutionX> <resolutionY>\n");
        printf("No checks on parameters passed.\n");
        printf("This was software used personally. Crashes were acceptable :)\n");
        ret = -1;
    }
    else
    {
        if(fopen_s(&fp, argv[1], "wb")==0)
        {
            printf("Error: Can't open output file\n");
        }
        else
        {
            for (i = 0; i < strlen(argv[2]); i++)
            {
                suc[i] = argv[2][i] - 48;
            }
            for (i = 0; i < MAXCOLORS; i++)
            {
                colors[i] = 0;
            }
            mktablog();
            x = 0.5;
            a = 2.8;
            for (i = 0; i < 2080; i++)
            {
                a = a + 0.0005;
                b = 3.7;
                for (j = 0; j < 1350; j++)
                {
                    b = b + 0.00011;
                    l = lyap(a, b, x, suc);
                    if (l > 0.0)
                    {
                        rit = 0;
                    }
                    else
                    {
                        rit = cerca(l);
                    }
                    colors[rit]++;
                    sprintf(buf, "%d", rit);
                    fprintf(fp, "%1s", buf);
                }
                fflush(fp);
                for (k = 0; k < MAXCOLORS; k++)
                {
                    printf("%d-%d/", k, colors[k]);
                }
                printf("------%d\n", i);
            }
            fclose(fp);
        }
    }
}

int cerca(double num)
{
    int ret = MAXCOLORS;
    if (num >= 0.25)
    {
        ret = MAXCOLORS - 3;
    }
    if ((num < 0.25) && (num >= -0.25))
    {
        ret = MAXCOLORS - 2;
    }
    if ((num < -0.25) && (num >= -0.40))
    {
        ret = MAXCOLORS - 1;
    }
    if (num <- 0.40)
    {
       ret = MAXCOLORS;
    }
    return(ret);
}

double lyap(double a, double b,double x,unsigned short s[])
{
    int len_suc=0;
    int i,j;
    int ciclo;
    double c=log(2);
    double tot=0.0;
    double r,y;
    long cont=0;
    int  ind_tab;

    i=0;
    while (s[i++] != 2)
    {
        len_suc++;
    }
    ciclo= 4000/len_suc;
    for(i=0;i<ciclo;i++)
    {
        for(j=0;j<len_suc;j++)
        {
            if (s[j] == 0)
            {
                r = a;
            }
            else
            {
                r = b;
            }
            x=r*x*(1-x);
            y=r-2.0*r*x;
            if (y < 0)
            {
                y = -y;
            }
            ind_tab=y*5000.0/4.0;
            tot=tot+(tab[ind_tab])/c;
            /********
                tot=tot+(log(y))/c;
            **********/
            cont++;
        }
    }
    return(tot/cont);
}

void mktablog()
{
    double num;
    int i;

    for(i=1;i<5000;i++)
    {
        num=i*4.0/5000.0;
        tab[i-1]=log(num);
    }
}

