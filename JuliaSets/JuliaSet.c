#include <stdio.h>
#include <stdlib.h>
#include <math.h>


const int MAXITER = 30;
const double MAXMODULE = 3.0;

int msetlevel(double cx, double cy, double lx, double ly, int max);
void writePPMHeader(FILE *outPNG, int width, int height);

int main(int argc, char *argv[])
{
    int point;
    double ymin, ymax, xmin, xmax;
    int ix, iy, ny, nx;
    double cx, cy, lx, ly;
    int ris, ret;
    FILE* fd_out = 0;

    if (argc < 10)
    {
        printf("Usage: JuliaSet <outFile> <juliaParamLx> <juliaParamLy> <resolutionX> <resolutionY> <xIntervalMin> <xIntervalMax> <yIntervalMin> <yIntervalMax>\n");
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
            /* Set Julia Set Window */
            ymin = atof(argv[8]);
            ymax = atof(argv[9]);
            xmin = atof(argv[6]);
            xmax = atof(argv[7]);
            // Set Julia Set Parameters
            lx = atof(argv[2]);
            ly = atof(argv[3]);
            // Set Picture resolution
            nx = atoi(argv[4]);
            ny = atoi(argv[5]);
            // Initialize PPM file. We use the P6 format (RGB 1-byte values)
            writePPMHeader(fd_out, nx, ny);
            for (iy = 0; iy < ny; iy++)
            {
                cy = ymin + iy * (ymax - ymin) / (ny - 1);
                for (ix = 0; ix < nx; ix++)
                {
                    cx = xmin + ix * (xmax - xmin) / (nx - 1);
                    ris = msetlevel(cx, cy, lx, ly, MAXITER);
                    point = ris % 2;
                    if (point == 1)
                    {
                        // Write a white pixel 
                        fprintf(fd_out, "%c%c%c", 0xff, 0xff, 0xff);
                    }
                    else
                    {
                        // Write a black pixel 
                        fprintf(fd_out, "%c%c%c", 0x0, 0x0, 0x0);
                    }
                }
            }
            fclose(fd_out);
            ret = 0;
        }
    }
    return(ret);
}

int msetlevel(double cx, double cy, double lx, double ly, int max)
{
    double x, y, x2, y2, mod;
    int iter;

    mod = 0.0;
    x = cx;
    y = cy;
    for (iter = 0; (iter < max) && (mod < MAXMODULE); iter++)
    {
        x2 = x * x - y * y + lx;
        y2 = 2 * x * y + ly;
        x = x2;
        y = y2;
        mod = sqrt(x * x + y * y);
    }
    return(iter);
}

void writePPMHeader(FILE *outPNG, int width, int height)
{
    fprintf(outPNG, "P6%c%d %d%c%d%c", 0x0a, width, height, 0x0a, 0xFF, 0x0a);
}
