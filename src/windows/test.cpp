#include "screen_avg_color_windows.h"
#include <iostream>
#include <chrono>

int main()
{
	int runtimeSeconds = 10,
		onNewFramecounter = 0;

	std::cout << "Running for " << runtimeSeconds << " seconds" << std::endl;

	auto onNewFramestart = std::chrono::high_resolution_clock::now();
	while (int* rgb = getScreenAvgColor(0, 0, 0, 0, 10)) {
		std::cout << "Red: " << rgb[0] << " Green: " << rgb[1] << " Blue: " << rgb[2] << std::endl;

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - onNewFramestart).count() >=
			1000) {
			std::cout << std::endl << "FPS: " << onNewFramecounter << std::endl << std::endl;
			onNewFramecounter = 0;
			onNewFramestart = std::chrono::high_resolution_clock::now();

			if (--runtimeSeconds == 0) {
				break;
			}
		}
		onNewFramecounter += 1;
	}

	return 0;
}
