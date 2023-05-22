#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int MAXCOLORS = 4;
const int MAXITERATIONS = 4000;

const double INITIAL_LYAP_START = 0.5;
/*
originally tested values for intervals (Lyap09)
const double EQUATION_A_PARAMETER = 2.8;
const double EQUATION_B_PARAMETER = 3.7;
A interval = 1.04
B interval = 0.1485

For subsequent pictures
amin=3.460;
amax=4.000;
bmin=2.520;
bmax=3.650;
*/

double lyap(double a, double b, double x, unsigned short s[], int s_length);
int find_color(double num);
void writePPMHeader(FILE *outPNG, int width, int height);

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
    int schema_length;
  
    if (argc < 9)
    {
        printf("Usage: LyapunovSpace <outFile> <schema> <Amin> <Amax> <Bmin> <Bmax> <resolutionX> <resolutionY>\n");
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
            // Convert numerical characters to values 
            schema_length = strlen(argv[2]);
            for (i = 0; i < schema_length; i++)
            {
                suc[i] = argv[2][i] - 48;
            }
            x = INITIAL_LYAP_START;
            int xres = atoi(argv[7]);
            int yres = atoi(argv[8]);
            double aMin = atof(argv[3]);
            double aMax = atof(argv[4]);
            double bMin = atof(argv[5]);
            double bMax = atof(argv[6]);
            double a_step = (aMax-aMin)/xres;
            double b_step = (aMax-aMin)/yres;
            writePPMHeader(fp, nx, ny);
            for (i = 0; i < xres; i++)
            {
                a = aMin + i * a_step;
                for (j = 0; j < yres; j++)
                {
                    b = bMin + i * b_step;
                    l = lyap(a, b, x, suc, schema_length);
                    if (l > 0.0)
                    {
                        rit = 0;
                    }
                    else
                    {
                        rit = find_color(l);
                    }
                    sprintf(buf, "%d", rit);
                    fprintf(fp, "%c%c%c", rit*32, rit*32, 0x0);
                }
                fflush(fp);
            }
            fclose(fp);
        }
    }
}

int find_color(double num)
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

double lyap(double a, double b,double x,unsigned short s[], int s_length)
{
    int i,j;
    int iterations;
    double c=log(2);
    double tot=0.0;
    double r,y;
    int  ind_tab;

    i=0;
    iterations= MAXITERATIONS;
    for(i=0;i<iterations;i++)
    {
        for(j=0;j<s_length;j++)
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
            tot=tot+(log(y))/c;
            iterations++;
        }
    }
    return(tot/iterations);
}

void writePPMHeader(FILE *outPNG, int width, int height)
{
    fprintf(outPNG, "P6%c%d %d%c%d%c", 0x0a, width, height, 0x0a, 0xFF, 0x0a);
}
