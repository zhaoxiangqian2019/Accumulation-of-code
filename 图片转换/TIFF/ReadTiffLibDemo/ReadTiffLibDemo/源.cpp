#include<iostream>

#include"tiffio.h"

using namespace std;

int main()
{
#if 0
	TIFF* xxsimage;
	int width, length;
	if ((xxsimage = TIFFOpen("threeTiff.tif", "r")) != NULL)
	{
		printf("success!\n");
		TIFFGetField(xxsimage, TIFFTAG_IMAGEWIDTH, &width);
		TIFFGetField(xxsimage, TIFFTAG_IMAGELENGTH, &length);
		printf("width: %d\n", width);
		printf("length: %d\n", length);
	}
#elif 0
	TIFF* tif = TIFFOpen("threeTiff.tif", "r");
	if (tif)
	{
		int dircount = 0;
		do
		{
			dircount++;
		} while (TIFFReadDirectory(tif));
		printf("%d directories in %s\n", dircount, "threeTiff.tif");
		TIFFClose(tif);
	}
#elif 1
	TIFF* tif = TIFFOpen("1.tif", "r");
	if (tif)
	{
		uint32 w, h;
		size_t npixels;
		uint32* raster;

		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
		npixels = w * h;
		raster = (uint32*)_TIFFmalloc(npixels * sizeof(uint32));
		if (raster != NULL)
		{
			if (TIFFReadRGBAImage(tif, w, h, raster, 0))
			{
				//...process raster data...
				cout << raster << endl;
			}
			_TIFFfree(raster);
		}
		TIFFClose(tif);
	}
#endif
	system("pause");
	return 0;
}