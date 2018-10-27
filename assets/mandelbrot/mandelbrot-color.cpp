#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

//x coord.
double Real_Map(int x, int wth, double rmin, double rmax)
{
	double range = rmax - rmin;

	return x * range / wth + rmin;
}

//y coord
double Img_Map(int x, int ht, double imin, double imax)
{
	double range = imax - imin;

	return x * range / ht + imin;
}

//the mandelbrot function
int Mandelbrot(double re, double im, int max_iter)
{
	int i = 0;
	double Zr = 0.0, Zi = 0.0;

	while (i < max_iter && Zr * Zr + Zi * Zi < 4.0)
	{
		double temp = Zr * Zr - Zi * Zi + re;

		Zi = 2.0 * Zr * Zi + im;
		Zr = temp;
		i++;
	}

	return i;
}

int main()
{
	int wth, ht, mx;
	double rmin, rmax, imin, imax;

    //input file

        ifstream fin("input.txt");

        if (!fin)
        {
            cout << "Error! Unable to open file input.txt" << endl;
            cin.ignore();
            return 0;
        }

        fin >> wth >> ht >> mx;
        fin >> rmin >> rmax >> imin >> imax;
        fin.close();

    //output file and color mapping

	ofstream fout("output-color-2.ppm");
	fout << "P3" << endl;
	fout << wth << " " << ht << endl;
	fout << "256" << endl;

	for (int y = 0; y < ht; y++)
	{

		for (int x = 0; x < wth; x++)
		{
			double real = Real_Map(x, wth, rmin, rmax);
			double img = Img_Map(y, ht, imin, imax);
			int n = Mandelbrot(real, img, mx);
			int r = (4 * n) % 265, g = ((int)sinf(n) * n) % 265, b = n % 265;

			fout << r << " " << g << " " << b << " ";
		}

		fout << endl;

	}

	fout.close();

	cout << "Image processing completed!" << endl;

	return 0;
}
