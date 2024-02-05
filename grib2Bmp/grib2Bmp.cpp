#include <stdio.h>
#include <math.h>

#include <Windows.h>
#include <Wingdi.h>

BITMAPFILEHEADER header;
BITMAPINFOHEADER info;

FILE* grib2;
FILE* bitmap;

errno_t err;

float min = 0.0f;
float max = 0.0f;

float range = 0.0f;

int width = 0;
int height = 0;

float dbz = 0.0f;

BYTE RGB;

VOID WriteBitmapHeader(UINT width, UINT height, FILE* fp);

VOID WriteGreyscalePalette(FILE* fp);

int main()
{
    err = fopen_s(&grib2, "final.txt", "r");

    err = fopen_s(&bitmap, "composite.bmp", "wb");

    err = fscanf_s(grib2, "1:0:min=%f:max=%f*", &min, &max);

    range = fabs(min) + fabs(max);

    err = fscanf_s(grib2, "%i %i", &width, &height);

    WriteBitmapHeader(width, height, bitmap);
    
    WriteGreyscalePalette(bitmap);

    err = fscanf_s(grib2, "%f", &dbz);

    while (err == 1)
    {
        RGB = BYTE(int(dbz));

        if (dbz < 0.0)
        {
            RGB = 255;
        }

        fwrite(&RGB, sizeof(BYTE), 1, bitmap);

        err = fscanf_s(grib2, "%f", &dbz);
    }

    fclose(grib2);

    fclose(bitmap);

    return 0;
}

VOID WriteBitmapHeader(UINT width, UINT height, FILE* fp)
{
    BITMAPFILEHEADER	bmapHeader;
    BITMAPINFO		bmapInfo;

    bmapHeader.bfType = 19778;
    fwrite(&bmapHeader.bfType, sizeof(WORD), 1, fp);

    bmapHeader.bfSize = 0;
    fwrite(&bmapHeader.bfSize, sizeof(DWORD), 1, fp);

    bmapHeader.bfReserved1 = 0;
    fwrite(&bmapHeader.bfReserved1, sizeof(WORD), 1, fp);

    bmapHeader.bfReserved2 = 0;
    fwrite(&bmapHeader.bfReserved2, sizeof(WORD), 1, fp);

    bmapHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (256 * sizeof(PALETTEENTRY));
    fwrite(&bmapHeader.bfOffBits, sizeof(DWORD), 1, fp);

    bmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    fwrite(&bmapInfo.bmiHeader.biSize, sizeof(DWORD), 1, fp);

    bmapInfo.bmiHeader.biWidth = width;
    fwrite(&bmapInfo.bmiHeader.biWidth, sizeof(LONG), 1, fp);

    bmapInfo.bmiHeader.biHeight = height;
    fwrite(&bmapInfo.bmiHeader.biHeight, sizeof(LONG), 1, fp);

    bmapInfo.bmiHeader.biPlanes = 1;
    fwrite(&bmapInfo.bmiHeader.biPlanes, sizeof(WORD), 1, fp);

    bmapInfo.bmiHeader.biBitCount = 8;
    fwrite(&bmapInfo.bmiHeader.biBitCount, sizeof(WORD), 1, fp);

    bmapInfo.bmiHeader.biCompression = BI_RGB;
    fwrite(&bmapInfo.bmiHeader.biCompression, sizeof(DWORD), 1, fp);

    bmapInfo.bmiHeader.biSizeImage = bmapInfo.bmiHeader.biWidth * bmapInfo.bmiHeader.biHeight;
    fwrite(&bmapInfo.bmiHeader.biSizeImage, sizeof(DWORD), 1, fp);

    bmapInfo.bmiHeader.biXPelsPerMeter = 0;
    fwrite(&bmapInfo.bmiHeader.biXPelsPerMeter, sizeof(LONG), 1, fp);

    bmapInfo.bmiHeader.biYPelsPerMeter = 0;
    fwrite(&bmapInfo.bmiHeader.biYPelsPerMeter, sizeof(LONG), 1, fp);

    bmapInfo.bmiHeader.biClrUsed = 0;
    fwrite(&bmapInfo.bmiHeader.biClrUsed, sizeof(DWORD), 1, fp);

    bmapInfo.bmiHeader.biClrImportant = 0;
    fwrite(&bmapInfo.bmiHeader.biClrImportant, sizeof(DWORD), 1, fp);
}

VOID WriteGreyscalePalette(FILE* fp)
{
    PALETTEENTRY paletteentry;

    for (UINT i = 0; i < 256; i++)
    {
        paletteentry.peRed = i;
        paletteentry.peGreen = i;
        paletteentry.peBlue = i;
        paletteentry.peFlags = 255;

        if ((i >= 0) && (i <= 4))
        {
            paletteentry.peRed = 227;
            paletteentry.peGreen = 227;
            paletteentry.peBlue = 227;
        }

        if ((i >= 5) && (i <= 9))
        {
            paletteentry.peRed = 4 + i - 5;
            paletteentry.peGreen = 233 + i - 5;
            paletteentry.peBlue = 231 + i - 5;
        }

        if ((i >= 10) && (i <= 14))
        {
            paletteentry.peRed = 1 + i - 10;
            paletteentry.peGreen = 159 + i - 10;
            paletteentry.peBlue = 244 + i - 10;
        }

        if ((i >= 15) && (i <= 19))
        {
            paletteentry.peRed = 3 + i - 15;
            paletteentry.peGreen = 0 + i - 15;
            paletteentry.peBlue = 244 + i - 15;
        }

        if ((i >= 20) && (i <= 24))
        {
            paletteentry.peRed = 2 + i - 20;
            paletteentry.peGreen = 250 + i - 20;
            paletteentry.peBlue = 2 + i - 20;
        }

        if ((i >= 25) && (i <= 29))
        {
            paletteentry.peRed = 1 + i - 25;
            paletteentry.peGreen = 197 + i - 25;
            paletteentry.peBlue = 1 + i - 25;
        }

        if ((i >= 30) && (i <= 34))
        {
            paletteentry.peRed = 0 + i - 30;
            paletteentry.peGreen = 142 + i - 30;
            paletteentry.peBlue = 0 + i - 30;
        }

        if ((i >= 35) && (i <= 39))
        {
            paletteentry.peRed = 250 + i - 35;
            paletteentry.peGreen = 248 + i - 35;
            paletteentry.peBlue = 2 + i - 35;
        }

        if ((i >= 40) && (i <= 44))
        {
            paletteentry.peRed = 229 + i - 40;
            paletteentry.peGreen = 188 + i - 40;
            paletteentry.peBlue = 2 + i - 40;
        }

        if ((i >= 45) && (i <= 49))
        {
            paletteentry.peRed = 250 + i - 45;
            paletteentry.peGreen = 148 + i - 45;
            paletteentry.peBlue = 0 + i - 45;
        }

        if ((i >= 50) && (i <= 54))
        {
            paletteentry.peRed = 250 + i - 50;
            paletteentry.peGreen = 0 + i - 50;
            paletteentry.peBlue = 0 + i - 50;
        }

        if ((i >= 55) && (i <= 59))
        {
            paletteentry.peRed = 212 + i - 55;
            paletteentry.peGreen = 0 + i - 55;
            paletteentry.peBlue = 0 + i - 55;
        }

        if ((i >= 60) && (i <= 64))
        {
            paletteentry.peRed = 188 + i - 60;
            paletteentry.peGreen = 0 + i - 60;
            paletteentry.peBlue = 0 + i - 60;
        }

        if ((i >= 65) && (i <= 69))
        {
            paletteentry.peRed = 248 + i - 65;
            paletteentry.peGreen = 0 + i - 65;
            paletteentry.peBlue = 250 + i - 65;
        }

        if ((i >= 70) && (i <= 74))
        {
            paletteentry.peRed = 152 + i - 70;
            paletteentry.peGreen = 84 + i - 70;
            paletteentry.peBlue = 198 + i - 70;
        }

        if ((i >= 75) && (i <= 79))
        {
            paletteentry.peRed = 250 + i - 75;
            paletteentry.peGreen = 250 + i - 75;
            paletteentry.peBlue = 250 + i - 75;
        }

        if (i == 255)
        {
            paletteentry.peRed = 0;
            paletteentry.peGreen = 0;
            paletteentry.peBlue = 0;
            paletteentry.peFlags = 0;
        }

        fwrite(&paletteentry.peBlue, sizeof(BYTE), 1, fp);
        fwrite(&paletteentry.peGreen, sizeof(BYTE), 1, fp);
        fwrite(&paletteentry.peRed, sizeof(BYTE), 1, fp);
        fwrite(&paletteentry.peFlags, sizeof(BYTE), 1, fp);
    }
}
