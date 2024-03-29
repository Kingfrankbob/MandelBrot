#include <SDL.h>
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <dos.h>

int WIDTH = 1920;
int HEIGHT = 1080;

long double min =  -2.0;
long double max =  2.0;

long double MAX_ITERATIONS = 200;

long double factor = 1;


long double map(long double value, long double in_min, long double in_max, long double out_min, long double out_max) {
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event;

	SDL_CreateWindowAndRenderer(1920, 1080, 0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

	


	while (1) {
		
		int count = 0;




		//printf("This is %500.499f", max);
		
		//Sleep(5000);

		//std::cout << "Hello";

		if (count > 30) {
			MAX_ITERATIONS *= 1.02;
		}


		SDL_RenderPresent(renderer);

		for (int x = 0; x < WIDTH; x++) { // x = a


			if (GetKeyState('Q') && 0x8000)
				return 0;

			for (int y = 0; y < HEIGHT; y++) { // y = a

				long double a = map(x, 0, WIDTH, min, max);
				long double b = map(y, 0, HEIGHT, min, max);

				long double ai = a;
				long double bi = b;

				int n = 0;
				for (int i = 0; i < MAX_ITERATIONS; i++) {

					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;

					a = a1 + ai;
					b = b1 + bi;

					if ((a + b) > 2) {
						break;	
					}



					n++;
				}

				int bright = map(n, 0, MAX_ITERATIONS, 0, 255);
				int re = map(bright * bright, 0, 6502, 0, 255);
				int gr = bright;
				int bl = map(sqrt(bright), 0, sqrt(255), 0, 255);

				if (n == MAX_ITERATIONS || bright < 20) {
					//SDL_SetRenderDrawColor(&renderer, r, g, b);
					re = 0;
					gr = 0;
					bl = 0;
				}

				SDL_SetRenderDrawColor(renderer, re, gr, bl, 255);
				SDL_RenderDrawPoint(renderer, x, y);


			}

		}
		count++;

		

		//max *= 0.1;
		//min *= 0.1;

		MAX_ITERATIONS += 5;
		
	}


	return 0;

}