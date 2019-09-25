# include <limits>
# include <math.h>
# include "window.hpp"

# define MININT std::numeric_limits<int>::min()

Window::Window()
{
	pixels = NULL;
	pixels_final = NULL;
	width = 700;
	height = 700;
	sample = 1;
	width *= sample;
	height *= sample;
	nb_pixels = width*height;
}

Window::~Window()
{
	if (pixels != NULL)
	{
		delete[] pixels;
	}
	if(pixels_final != NULL)
	{
		delete[] pixels_final;
	}
}

const int Window::get_width()
{
	return width / sample;
}

const int Window::get_height()
{
	return height / sample;
}

unsigned char * Window::get_pixels()
{
	if(sample == 1)
	{
		return pixels;
	}
	else
	{
		return pixels_final;
	}
}

vec3 Window::get_pixel(vec2 p)
{
	if(0<=p.x && p.x<width && 0<=p.y && p.y<height)
	{
		int indice = (p.x + p.y*width) * 3;
		return vec3(c2f(pixels[indice]), c2f(pixels[indice+1]), c2f(pixels[indice+2]));
	}

	return vec3();
}

void Window::draw_pixel(vec2 p, vec3 c)
{
	if(p.x>=0 && p.x<width && p.y>=0 && p.y<height)
	{
		int indice = (p.x + p.y*width) * 3;
		pixels[indice] = f2c(c.x);
		pixels[indice+1] = f2c(c.y);
		pixels[indice+2] = f2c(c.z);
	}
}

void Window::draw_pixel_sampled(vec2 p, vec3 c)
{
	if(0<=p.x && p.x<width && 0<=p.y && p.y<height)
	{
		int indice = (p.x + p.y*width/sample) * 3;
		pixels_final[indice] = f2c(c.x);
		pixels_final[indice+1] = f2c(c.y);
		pixels_final[indice+2] = f2c(c.z);
	}
}

void Window::clear()
{
	//Clear color
	for(int i=0; i<nb_pixels*3; i+=3)
	{
		pixels[i] = 0;
		pixels[i+1] = 0;
		pixels[i+2] = 0;
	}
}

void Window::reshape(int w, int h)
{
	width = w;
	height = h;
	width *= sample;
	height *= sample;
	nb_pixels = width * height;

	if(pixels != NULL)
	{
		delete[] pixels;
	}
	if(pixels_final != NULL)
	{
		delete[] pixels_final;
	}

	pixels = new unsigned char[nb_pixels*3];
	pixels_final = new unsigned char[(nb_pixels/(sample*sample))*3];
	//Clear color
	for(int i=0; i<nb_pixels*3; i+=3)
	{
		pixels[i] = 0;
		pixels[i+1] = 0;
		pixels[i+2] = 0;
	}
}

void Window::antialiasing()
{
    // TODO => TP01
}

void Window::draw_line(vec2 p1, vec2 p2, vec3 c)
{
	/**int dx, dy, e;
	vec2 p(p1.x, p1.y);
  dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	int incD = 2*(dy-dx);
	int incH = 2*dy;
	if (dx != 0) {
		if (dx > 0) {
			if (dy != 0) {
				if (dy > 0) {
					if (dx >= dy) { //Premier octan
						e = 2*dy-dx;
						// dx *= 2;
						// dy *= 2;
						while(p.x < p2.x) {
							draw_pixel(p, c);
							p.x++;
							if (e < 0) {
								p.y++;
								e += incD;//dx;
							} else {
								e -= incH;//dy;
							}
						}
					} else { //Deuxieme octant
						e = dy;
						// dx *= 2;
						// dy *= 2;
						while(p.y < p2.y) {
							//draw_pixel(p, c);
							p.y++;
							if (e < 0) {
								p.x++;
								e += incH;//dy;
							} else {
								e -= incD;//dx;
							}
						}
					}
				} else {
					if (dx >= -dy) {
						e = dx;
						// dx *= 2;
						// dy *= 2;
						while(p.x < p2.x) {
							draw_pixel(p, c);
							p.x++;
							if (e < 0) {
								p.y--;
								e += incD;//dx;
							} else {
								e += incH;//dy;
							}
						}
					} else {
						e = dy;
						// dx *= 2;
						// dy *= 2;
						while(p.y > p2.y) {
							draw_pixel(p, c);
							p.y--;
							if (e < 0) {
								p.x++;
								e += incH;//dy;
							} else {
								e += incD;//dx;
							}
						}
					}
				}
			} else {
				while(p.x < p2.x) {
					draw_pixel(p, c);
					p.x++;
				}
			}
		} else {
			if (dy != 0) {
				if (dy > 0) {
					if (-dx >= dy) {
						e = dx;
						// dx *= 2;
						// dy *= 2;
						while(p.x > p2.x) {
							draw_pixel(p, c);
							p.x--;
							if (e >= 0) {
								p.y++;
								e += incD;//dx;
							} else {
								e += incH;//dy;
							}
						}
					} else {
						e = dy;
						// dx *= 2;
						// dy *= 2;
						while(p.y < p2.y) {
							draw_pixel(p, c);
							p.y++;
							if (e <= 0) {
								p.x--;
								e += incH;//dy;
							} else {
								e += incD;//dx;
							}
						}
					}
				} else {
					if (dx <= dy) {
						e = dx;
						// dx *= 2;
						// dy *= 2;
						while(p.x > p2.x) {
							draw_pixel(p, c);
							p.x--;
							if (e >= 0) {
								p.y--;
								e += incD;//dx;
							} else {
								e -= incH;//dy;
							}
						}
					} else {
						e = dy;
						// dx *= 2;
						// dy *= 2;
						while(p.y > p2.y) {
							draw_pixel(p, c);
							p.y--;
							if (e < 0) {
								p.x--;
								e += incH;//dy;
							} else {
								e -= incD;//dx;
							}
						}
					}
				}
			} else {
				while (p.x > p2.x) {
					draw_pixel(p, c);
					p.x--;
				}
			}
		} 
	} else {
		if (dy != 0) {
			if (dy > 0) {
				while(p.y < p2.y) {
					draw_pixel(p, c);
					p.y++;
				}
			} else {
				while(p.y > p2.y) {
					draw_pixel(p, c);
					p.y--;
				}
			}
		}
	}**/
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	vec2 p(p1.x, p1.y);
	int e = 2*dy-dx;;
	int incH = 2*dy;
	int incD = 2*(dy-dx);
	while(p.x < p2.x) {
		draw_pixel(p, c);
		p.x++;
		if (e > 0) {
			p.y++;
			e += incD;
		} else {
			e -= incH;
		}
	}
}

void Window::draw_circle(vec2 center, unsigned int r, vec3 c)
{
  vec2 p(center.x, center.y + r);
	double h = 1 - r;
	draw_pixel(p, c);
	while (p.y > p.x) {
		if (h < 0) {
			h += 2*p.x + 3;
		} else {
			h += 2*p.x - 2*p.y + 5;
			p.y--;
		}
		draw_pixel(p, c);
		p.x++;
	}
}

void Window::draw_circle_parts(vec2 p, vec2 center, vec3 c)
{
    // TODO => TP01
}

void Window::raster_buffer_insert(int x, int raster_buffer[2])
{
	// TODO => TP03
}

void Window::raster_buffer_insert(int x, int raster_buffer[2], vec3 color, vec3 color_buffer[2])
{
	// TODO => TP04
}

void Window::draw_horizontal_line(int y, int x1, int x2, vec3 c)
{
	// TODO => TP03
}

void Window::draw_horizontal_line(int y, int x1, int x2, vec3 c[2])
{
	// TODO => TP04
}

void Window::draw_quad(vec2 p[4], vec3 c)
{
	// TODO => TP03
}

void Window::draw_quad(vec2 p[4], vec3 c[4])
{
	// TODO => TP04
}

unsigned char Window::f2c(float f)
{
	return (unsigned char)(f * 255);
}

float Window::c2f(unsigned char c)
{
	return ((float)c / 255.0f);
}
