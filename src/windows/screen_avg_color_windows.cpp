#include <windows.h>
#include <gdiplus.h>
#include <math.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

int* getScreenAvgColor(const int x, const int y, int W, int H, const int scale) {
	static int rgb[3] = { 0, 0, 0 };

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	{
		// Get the height and width of the screen
		SetProcessDPIAware();

		if (W == 0) {
			W = GetSystemMetrics(SM_CXSCREEN);
		}
		if (H == 0) {
			H = GetSystemMetrics(SM_CYSCREEN);
		}

		const int targetW = W / 100 * scale;
		const int targetH = H / 100 * scale;

		HDC hdc = GetDC(NULL); // Get the desktop device context
		HDC hdcSample = CreateCompatibleDC(hdc); // Create a device context to use yourself

		// Create a bitmap
		HBITMAP hbSample = CreateCompatibleBitmap(hdc, targetW, targetH);

		// Use the previously created device context with the bitmap
		SelectObject(hdcSample, hbSample);

		// Copy from the desktop device context to the bitmap device context
		SetStretchBltMode(hdcSample, HALFTONE);
		StretchBlt(hdcSample, 0, 0, targetW, targetH, hdc, x, y, W, H, SRCCOPY);

		BITMAP bSample;
		// Get the BITMAP from the HBITMAP
		GetObject(hbSample, sizeof(BITMAP), &bSample);

		BITMAPINFOHEADER bi;

		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bSample.bmWidth;
		bi.biHeight = bSample.bmHeight;
		bi.biPlanes = 1;
		bi.biBitCount = 32;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		const int dwBmpSize = ((bSample.bmWidth * bi.biBitCount + 31) / 32) * 4 * bSample.bmHeight;

		HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
		BYTE *lpPixels = (BYTE *)GlobalLock(hDIB);
		//BYTE *lpPixels = new BYTE[dwBmpSize];

		// Gets the "bits" from the bitmap and copies them into a buffer which is pointed to by lpPixels.
		GetDIBits(hdcSample, hbSample, 0, (UINT)bSample.bmHeight, lpPixels, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

		{
			unsigned long long uRed = 0, uGreen = 0, uBlue = 0;

			for (int y = 0; y < bSample.bmHeight; y++)
			{
				for (int x = 0; x < bSample.bmWidth; x++)
				{
					uBlue += (int)pow(lpPixels[0], 2);
					uGreen += (int)pow(lpPixels[1], 2);
					uRed += (int)pow(lpPixels[2], 2);

					lpPixels += 4;
				}
			}

			const int pixelNum = bSample.bmWidth * bSample.bmHeight;

			uRed /= pixelNum;
			uGreen /= pixelNum;
			uBlue /= pixelNum;
			rgb[0] = (int)sqrt((int)uRed);
			rgb[1] = (int)sqrt((int)uGreen);
			rgb[2] = (int)sqrt((int)uBlue);
		}

		// Cleanup
		GlobalUnlock(hDIB);
		GlobalFree(hDIB);

		ReleaseDC(NULL, hdc);
		DeleteObject(hbSample);

		DeleteDC(hdcSample);
	}

	GdiplusShutdown(gdiplusToken);

	return rgb;
}
