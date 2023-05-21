#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int MAXITER = 175;
const double MAXDIVERGE = 10000.0;

int msetlevel(double cx, double cy, int max);
void writePPMHeader(FILE* outPNG, int width, int height);

int main(int argc, char * argv[])
{
    int ret = -1;
    int point;
    double ymin, ymax, xmin, xmax;
    int    ix, iy, ny, nx;
    int    ris;
    double cx, cy;
    FILE* fd_out = 0;


    if (argc < 8)
    {
        printf("Usage: MandelbrotSet <outFile> <mandLocationXmin> <mandLocationXmax> <mandLocationYmin> <mandLocationYmax> <resolutionX> <resolutionY>\n");
        printf("No checks on parameters passed.\n");
        printf("This was software used personally. Crashes were acceptable :)\n");
        ret = -1;
    }
    else
    {

        fopen_s(&fd_out, argv[1], "wb");
        if (fd_out == 0)
        {
            printf("Error: could not open output file\n");
            ret = -1;
        }
        else
        {
            ymin = atof(argv[4]);
            ymax = atof(argv[5]);
            xmin = atof(argv[2]);
            xmax = atof(argv[3]);
            ny = atoi(argv[7]);
            nx = atoi(argv[6]);

            // Initialize PPM file. We use the P6 format (RGB 1-byte values)
            writePPMHeader(fd_out, nx, ny);
            for (iy = 0; iy < ny; iy++)
            {
                cy = ymin + iy * (ymax - ymin) / (ny - 1);
                for (ix = 0; ix < nx; ix++)
                {
                    cx = xmin + ix * (xmax - xmin) / (nx - 1);
                    ris = msetlevel(cx, cy, MAXITER);
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
        }
    }
    return(ret);
}

int msetlevel(double cx, double cy, int max)
{
	double x, y, x2, y2, temp;
	int iter;

	x = 0.0;
	y = 0.0;
	x2 = 0.0;
	y2 = 0.0;
	for (iter = 0; (iter < max) && ((x2 + y2) < MAXDIVERGE); iter++)
	{
		temp = x2 - y2 + cx;
		y = 2 * x * y + cy;
		x = temp;
		x2 = x * x;
		y2 = y * y;
	}
	return(iter);
}

void writePPMHeader(FILE* outPNG, int width, int height)
{
    fprintf(outPNG, "P6%c%d %d%c%d%c", 0x0a, width, height, 0x0a, 0xFF, 0x0a);
}

