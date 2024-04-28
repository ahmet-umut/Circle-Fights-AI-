#include <SDL.h>
#include <iostream>

SDL_Renderer *r;
#define ss 222	//screen size
#define pi 3

typedef unsigned char by;
typedef SDL_Color co;

co ba={144,144,144}, cdc={222,1,66};	//COLORS
void sc (co c0) {SDL_SetRenderDrawColor(r,c0.r,c0.g,c0.b,255);}	//sets the drawing color for the renderer

struct ci {by r; co c=cdc; float x,y, xv=0,yv=0, xa=0,ya=0, m=1; by f=0;};
#define drawline(a,s,d,f) SDL_RenderDrawLine(r,a,s,d,f)
void draw(ci*c)
	{
	static SDL_Rect cr1,cr2;	//for drawing filled circles
	sc(c->c);
		for (float a=0; a<=pi*2; a+=.5)	drawline( rint(c->x+c->r*cos(a)) , rint(c->y+c->r*sin(a)) , rint(c->x+c->r*cos(a+.5)) , rint(c->y+c->r*sin(a+.5)) );	//for the outside line
		if (c->f)	for (float a=0; a<=pi/4; a+=.01)	//drawing a filled circle using rectangles
			{
			cr1.x = c->x-c->r*(cos(a)+.015), cr1.y = c->y-c->r*(sin(a)+.015), cr1.w = 2*c->r*(cos(a)+.015), cr1.h = 2*c->r*(sin(a)+.015);
			cr2.x = c->x-c->r*(sin(a)+.015), cr2.y = c->y-c->r*(cos(a)+.015), cr2.w = 2*c->r*(sin(a)+.015), cr2.h = 2*c->r*(cos(a)+.015);
			SDL_RenderFillRect(r,&cr1);
			SDL_RenderFillRect(r,&cr2);
			}
	}

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_VIDEO); SDL_Window* win = SDL_CreateWindow("SDL2 app", 100, 100, ss,ss, SDL_WINDOW_SHOWN); r = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);	//preparation

#define dt (1/60.)
	float tcounter = 0;	//tcounter is the time passed since this line is executed.	dt is the resolution of our "update"s. We could do it faster by reducing dt, or making several updates in a single loop step. My screen is 60 FPS; should it be 144, I'd make dt 1/144 (seconds)

	SDL_Event ev;	//to not make the program seem like in a not responding state, and to get the keyboard input properly since the SDL_PollEvent fn. takes events such as keyboard events...
	while (1)
	{
		SDL_PollEvent(&ev); if (ev.type == SDL_QUIT) break;	//quit properly when desired

		if (SDL_GetTicks() % int(dt * 1000) == 0) {
			sc(ba);	SDL_RenderClear(r);	//clears the renderer with background color
			SDL_RenderPresent(r);	//render the visual output to screen
			tcounter += dt;
		}
	}
	SDL_Quit(); return 0;
}
