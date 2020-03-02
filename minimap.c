#include "cub3d.h"

void draw_line(int X0, int Y0, int X1, int Y1, int color)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
    int i = 0;
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    // calculate increment in x & y for each steps
	float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    while (i <= steps)
    {
        img_update(X * g_mini ,Y * g_mini, color);  // put pixel at (X,Y)
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step
                             // generation step by step
        i++;
    }
}

void	drawemptysquare(int x,int y,int color)
{
	int i = 0;
	int j = 0;

	while (i < T_S)
	{
		j = 0;
		while (j < T_S)
		{
			  if(i == 0 || i == T_S -1 || j == 0 || j == T_S -1)
            {
                img_update((x + j) * g_mini, (y + i) * g_mini, color);
            }
			
			j++;
		}
		i++;
	}
}

void	drawsquare(int x,int y ,int color)
{
	int i = 0;
	int j = 0;

	while (i < T_S)
	{
		j = 0;
		while (j < T_S)
		{
			img_update((x + i) * g_mini, (y + j) * g_mini, color);
			j++;
		}
		i++;
	}
}

void	draw_map()
{
	int x = 0;
	int y = 0;
	int i = -1;
	int j;
	while (++i < g_game_data.map.rows)
	{
		j = -1;
		x = 0;
		while (++j < g_game_data.map.columns)
		{
			if (g_game_data.map.map[(g_game_data.map.columns * i) + j] == '1')
				drawsquare(x, y, 0x00ff00);
			else 
				drawemptysquare(x, y, 0xffffff);
			x += T_S;
		}
		y += T_S;
	}
}

float	normalizeangle(float angle)
{
	angle = remainder(angle,2 * M_PI);
	if(angle < 0)
		angle =  (2 * M_PI) + angle;
	return angle;
}