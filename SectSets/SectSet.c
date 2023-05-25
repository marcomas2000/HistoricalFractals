#include <stdio.h>
#include <stdlib.h>
#include <math.h>


const double ymin = 0.0;     
const double ymax = 1.5;
const double xmin = 0.0;
const double xmax = 1.5;


int msetlevel(double cx0, double cy0, double cx1, double cy1);
void writePPMHeader(FILE *outPNG, int width, int height);
double modulo(double a, double b);
void effedizeta(double a, double b, double * rris, double * iris);
double power();

int main(int argc, char *argv[])
{
   int    ix,iy,ny, nx;
   int    ris;
   double cx, cy, lx, ly;
   FILE   *fd_out;
   int ret = -1;
   int point;
   
   if (argc < 6)
   {
      printf("Usage: SectSet <outFile> <resolutionX> <resolutionY> <xIntervalMin> <sectParamLx> <sectParamLy> \n");
      printf("No checks on parameters passed.\n");
      printf("This was software used personally. Crashes were acceptable :)\n");
      ret = -1;
   }
   else
   {
      fopen_s(&fd_out, argv[1],"wb");
      if (fd_out == 0)
      {
            printf("Error: could not open output file\n");
            ret = -1;
      }
      else
      {
         lx= atof(argv[4]);
         ly= atof(argv[5]);
         ny=atoi(argv[3]);
         nx=atoi(argv[2]);
         writePPMHeader(fd_out, nx, ny);
         for(iy=0;iy<ny;iy++)
         {
            cy=ymin+iy*(ymax-ymin)/(ny-1);
            for(ix=0;ix<nx;ix++)
            {
               cx=xmin+ix*(xmax-xmin)/(nx-1);
               ris=msetlevel(cx-(cx/60),cy-(cy/60), cx, cy);
               point=check(ris);
               fprintf(fd_out, "%c%c%c", 0xff-0xff*(point%2), 0xff-0xff*(point%2), 0xff-0xff*(point%2));
            }
         }
         fclose(fd_out);
      }
   }
    return(ret);
}

check(num)
int num;
{
int color;

if(num>30)
   return(9);
if(num<6)
   return(0);
if(num<9)
   return(1);
if(num<11)
   return(2);
if(num<14)
   return(3);
if(num<17)
   return(4);
if(num<20)
   return(5);
if(num<23)
   return(6);
if(num<25)
   return(7);
if(num<28)
   return(8);
if(num<30)
   return(9);
}

int msetlevel(double cx0, double cy0, double cx1, double cy1)
{
int    iter;
double re, im;
double rez0, imz0;
double rez1, imz1;
double rez2, imz2;
double reris0, imris0;
double reris1, imris1;
double reris2, imris2;
double rediff, imdiff;
double rerisdiff, imrisdiff;
double reprod, improd;
double moduloquadro;
int flag;

re=cx1-cx0;
im=cy1-cy0;
rez0=cx0;
imz0=cy0;
rez1=cx1;
imz1=cy1;
iter=0;
while(modulo(re,im)>0.001)
    {
    effedizeta(rez0, imz0, &reris0, &imris0);
    effedizeta(rez1, imz1, &reris1, &imris1);
    rediff=rez1-rez0;
    imdiff=imz1-imz0;
    reprod=reris1*rediff-imris1*imdiff;
    improd=reris1*imdiff+imris1*rediff;
    rerisdiff=reris1-reris0;
    imrisdiff=imris1-imris0;
    moduloquadro=rerisdiff*rerisdiff+imrisdiff*imrisdiff;
    re=(reprod*rerisdiff+improd*imrisdiff)/moduloquadro;
    im=(improd*rerisdiff-reprod*imrisdiff)/moduloquadro;
    rez2=rez1-re;
    imz2=imz1-im;
    rez0=rez1;
    imz0=imz1;
    rez1=rez2;
    imz1=imz2;
    iter++;
    }
return(iter);
}

void effedizeta(double a, double b, double * rris, double * iris)
{
double re, im;

re=power(a,4)-6*power(a,2)*power(b,2)+power(b,4)-1;
im=4*power(a,3)*b-4*a*power(b,3);
*rris=re;
*iris=im;
}

double power(double x, int y)
{
int i;
double ris;

if(y==0)
   ris=1.0;
else
   {
   ris=x;
   for(i=1;i<y;i++)
      {
      ris=ris*x;
      }
   }
return(ris);
}

double modulo(double a, double b)
{
double ris;
ris=sqrt(a*a+b*b);
return(ris);
}


void writePPMHeader(FILE *outPNG, int width, int height)
{
    fprintf(outPNG, "P6%c%d %d%c%d%c", 0x0a, width, height, 0x0a, 0xFF, 0x0a);
}
