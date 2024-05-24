/*
sdl2_renderparty_example1.c
This file is part of:
Example for SDL2_RenderParty ( Do not include in projects )
https://www.pawbyte.com/sdl2_renderparty
Copyright (c) 2024 Nathan Hurde, Chase Lee.

Copyright (c) 2024 PawByte.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the �Software�), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-SDL2_RenderParty <https://www.pawbyte.com/sdl2_renderparty>


*/


#include "SDL2/SDL.h" //Includes SDL2. Remmeber you need SDL 2.x and SDL 2.0.18 or higher. Not yet tested in SDL3...
#include "sdl2_renderparty.h" //Include the SDL2_RenderParty header
#include <time.h> //Next we include the sacred time library needed to simulate random number generation

//Random function for testing
int example_random(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int example_random_float(float min, float max){
   return min + rand() / (RAND_MAX / (max - min + 1.f) + 1.f);
}

int main(int argv, char** args)
{
    //Initialize the random number generator
    srand(time(NULL));

    //First we initalize SDL2, your program may have more flags than this, but it should still work
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
        return false;
	}

	//Let's use the good ole classic size of 640x480
    int app_window_width = 640;
    int app_window_height = 480;


    //With SDL2 Initialized, let's make a Window centered on the screen using the dimensions we specified above.
	SDL_Window * app_window = SDL_CreateWindow("SDL2_RenderParty - Test Example",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,app_window_width,app_window_height,SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE   );

	/*If somehow our window doesnt init, we return -1 and close program.
    If this happens, it is likely SDL2 is not initialized or installed properly.
	*/
	if( app_window == NULL )
	{
        return -1;
	}

	//Inits the renderer, the flags can vary, but this is for a SDL Program which has control over the renderer
	SDL_Renderer * sdl_apprenderer = SDL_CreateRenderer( app_window, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );//  | SDL_RENDERER_PRESENTVSYNC );


	/*If somehow our sdl_apprenderer doesnt init, we return -1 and close program.
    If this happens, it is likely SDL2 is not initialized or installed properly.
	*/
	if( sdl_apprenderer == NULL )
	{
		return -2;
	}


	//Now we initialize the party. This is optional, but advised to keep in codebases in case of updates to library.
	SDL2_RenderParty_Init();

	//Yippie, now we have a WHOOLE WINDOW, let's setup the gameloop code.


	//The power of this boolean will determine if we exit the example gameloop.
	bool app_closed = false;

	//Next we initialize the mouse coordinates
	int app_mouse_x = 0;
	int app_mouse_y = 0;

	//Now let's setup the center screen point
    SDL_Point center_point = {};

    //Speaking of points, let's prepare for the SDL_Point which stores the mouse X,Y coordinates.
    SDL_Point mouse_point = {};

    //Now we have a random polygon color for rendering
    SDL_Color filled_poly_color = {0,0,255,255};
    filled_poly_color.r = example_random(0,255);
    filled_poly_color.g = example_random(0,255);
    filled_poly_color.b = example_random(0,255);

    //More joyful initialization of the amount of points within our polygon.
    int shape_point_count = 3;

    //Initializes the angle of the polygonal shape we plan on drawing later.
    float shaped_angle = 0;

    //Defaults the radius of this polygon to 32 pixels
    int shape_size = 32;

    /*Defaults the texture shape to full ( Feel free to play with this in your code
      In this example we are not dealing with textures.
    */

    int gfx_effect = sdl_partyeffect_full;


    //Almost there, let's define a rectangle to compare our polygons against.
    SDL_Rect test_red_rect = {0,0,128, 128};


    //Next initialize the event state
    SDL_Event ev;

    //Polygons can also be rendered as triangle-fans or triangle-strips

    //Let's make an enum to keep track of which one we will like to select.
    //With only 640x480, the screen can get quite crowded
    enum
    {
        render_triangle_mode_strips = 0,
        render_triangle_mode_fans = 1,
        render_triangle_mode_quads = 2,
        render_triangle_mode_off = 3,
    };


    //Our triangle_mode_state is just an int.
    int triangle_mode_state = render_triangle_mode_strips;

    //Let's randomly say we have a max of 5000 points in our polygon...
    //We only gave ourselves 640x480 pixels to play with remember :-)

    const int max_random_polygon_points = 5000;

    SDL_Vertex random_polygon_vertices[max_random_polygon_points];

    //Ok let's initialize all of those vertices. This may take a lil time... ( Not really, tho)
    int i_v = 0;
    for( i_v = 0; i_v < max_random_polygon_points; i_v++ )
    {
        random_polygon_vertices[i_v].position.x = 0; //Defaults to point (0,0)
        random_polygon_vertices[i_v].position.y = 0; //Defaults to point (0,0)
        random_polygon_vertices[i_v].color.r = random_polygon_vertices[i_v].color.g = 0;
        random_polygon_vertices[i_v].color.b = random_polygon_vertices[i_v].color.a = 255;//defaltng to rgba(0,0,255,255) aka pure blue
        random_polygon_vertices[i_v].tex_coord.x = random_polygon_vertices[i_v].tex_coord.y = 0; //Defaults to point (0,0)
    }

    //Let's keep track of how many vertices we are going to begin with...
    //All polygons begin with 3 points, otherwise its a point or line...
    int triangle_mode_current_count = 3;

    /*
    To make this tutorial short I have not added texture loading.
    Feel free to add a texture variable here and load it in from data, file or memory.
    */

    //Now our gameloop is here. As long as app_closed is false the game will run until TaskManager closers it or your computer crashes
	while( app_closed == false )
    {
        //Let's get grab the mouse coordinates using SDL2
        SDL_GetMouseState( &app_mouse_x, &app_mouse_y );
        mouse_point.x = app_mouse_x;
        mouse_point.y = app_mouse_y;

        //Next let's get the window size using SDL2
        SDL_GetWindowSize(app_window, &app_window_width, &app_window_height);

        center_point.x = app_window_width/2;
        center_point.y = app_window_height/2;

        //This while loop is used for checking all input
        while (SDL_PollEvent(&ev) != 0)
        {
            switch(ev.type)
            {
                //If the Quit button or another program requests app to quit, we end the gameloop by setting app_closed to true
                case SDL_QUIT:
                    app_closed = true;
                break;

                //Next let's check all keyboard input
                case SDL_KEYDOWN:
                    //Select surfaces based on key press
                    switch( ev.key.keysym.sym )
                    {

                        //Let's begin playing with our polygon
                        case SDLK_w:
                            //Ok let's initialize all of those vertices. This may take a lil time... ( Not really, tho)

                            //Makes use we stay in bounds...
                            if( triangle_mode_current_count >= max_random_polygon_points )
                            {
                                triangle_mode_current_count = max_random_polygon_points;
                            }

                            //Now let's give each value something random to enjoy :-)
                            random_polygon_vertices[i_v].position.x = app_window_width/2;
                            random_polygon_vertices[i_v].position.y = app_window_height/2;
                            for(  i_v = 1; i_v < triangle_mode_current_count; i_v++ )
                            {
                                random_polygon_vertices[i_v].position.x = example_random(0, app_window_width );
                                random_polygon_vertices[i_v].position.y = example_random(0, app_window_height );
                                random_polygon_vertices[i_v].color.r = example_random(0, 255 );
                                random_polygon_vertices[i_v].color.g = example_random(0, 255 );
                                random_polygon_vertices[i_v].color.b = example_random(0, 255 );
                                random_polygon_vertices[i_v].color.a = example_random(0, 255 );
                                random_polygon_vertices[i_v].tex_coord.x = example_random_float(0, 1);
                                random_polygon_vertices[i_v].tex_coord.y = example_random_float(0, 1);
                            }
                        break;

                        case SDLK_a:
                            triangle_mode_state += 1;
                            if( triangle_mode_state > render_triangle_mode_off )
                            {
                                triangle_mode_state = render_triangle_mode_strips;
                            }
                        break;

                        case SDLK_s:
                            triangle_mode_current_count -= example_random(1,4); //Let's add between 1 and 4 random points on next W button press
                            if( triangle_mode_current_count < 3 )
                            {
                                triangle_mode_current_count = 3;
                            }
                        break;


                        case SDLK_d:
                            triangle_mode_current_count += example_random(1,4); //Let's add between 1 and 4 random points on next W button press
                        break;

                        //Ok let's play with the mouse bound polygon now:
                        //Let's toggle the gfx effect if the space key is hit
                        case SDLK_SPACE:
                            gfx_effect++;
                            if( gfx_effect > sdl_partyeffect_none )
                            {
                                gfx_effect = sdl_partyeffect_full;
                            }
                            if( gfx_effect < sdl_partyeffect_full )
                            {
                                gfx_effect = sdl_partyeffect_none;
                            }
                        break;

                        //If the Z key is press we remove a point from our polygon
                        case SDLK_z:
                            if( shape_point_count > 3)
                            {
                                shape_point_count -= 1;
                            }
                        break;

                        //If the X key is press we add another point to our polygon
                         case SDLK_x:
                             if( shape_point_count < sdl_renderparty_math_degrees_multiplier )
                             {
                                shape_point_count +=1;
                             }
                        break;

                        //If the C key is press we DECRASE our polygon's radius by 8
                        case SDLK_c:
                            if( shape_size > 32 )
                            {
                                shape_size -=8;
                            }
                        break;

                        //If the V key is press we INCREASE our polygon's radius by 8
                         case SDLK_v:
                            if( shape_size < 1024 )
                            {
                                shape_size +=8;
                            }
                        break;

                        //If the B key is press we DECRASE our polygon's angle by 8
                        case SDLK_b:
                            shaped_angle -=8;
                        break;

                        //If the N key is press we INCREASE our polygon's angle by 8
                         case SDLK_n:
                            shaped_angle +=8;
                        break;

                        //If the M key is press we give our random polygon a new random color
                         case SDLK_m:
                            filled_poly_color.r = example_random(0,255);
                            filled_poly_color.g = example_random(0,255);
                            filled_poly_color.b = example_random(0,255);
                        break;

                    }
                break;

                default:

                break;
            }
        }

        //Now let's begin the render phase of the example

        //Let's clear the screen to a dark shade of blue
        SDL_SetRenderDrawColor(sdl_apprenderer, 0, 0, 96, 255);
        SDL_RenderClear(sdl_apprenderer);

        //Then let's draw a little red rectangle using the test_red_rect variable from the start of the program
        SDL_SetRenderDrawColor(sdl_apprenderer, 255, 0, 0, 255);
        SDL_RenderFillRect( sdl_apprenderer,&test_red_rect );

        //Finally we reset the rendercolor of the program back to white with a 255/255 alpha value
        SDL_SetRenderDrawColor(sdl_apprenderer, 255, 255, 255, 255);

        //Ok, our first time rendering with SDL_RenderParty!

        //We render a polygon with 20 points/sides with a radius of 128 pixels
        SDL_RenderParty_Polygon( sdl_apprenderer, NULL, center_point, 128, 20, NULL, 255, shaped_angle, gfx_effect, 0 );

        //Ok let's render the super randomized polygon to screen depending on which state we are in...

        if( triangle_mode_state == render_triangle_mode_strips )
        {
            SDL_RenderParty_Strips( sdl_apprenderer, NULL, random_polygon_vertices, triangle_mode_current_count, false, 0,0  );
        }
        else if( triangle_mode_state == render_triangle_mode_fans )
        {
            SDL_RenderParty_Fans( sdl_apprenderer,NULL, random_polygon_vertices, triangle_mode_current_count, 0,0);
        }
        else if( triangle_mode_state == render_triangle_mode_quads )
        {
            SDL_RenderParty_Quad( sdl_apprenderer, NULL, random_polygon_vertices, true, false );
        }

    //Our triangle_mode_state is just an int.
    int triangle_mode_state = render_triangle_mode_strips;
        /*Ok lets render our next polygon bound to the mouse coordinates
        This polygon uses the shape_size for it's radius, the shape_point_count for it's amount of sides
        */
        SDL_RenderParty_Polygon( sdl_apprenderer, NULL , mouse_point, shape_size, shape_point_count, &filled_poly_color, 255, shaped_angle, gfx_effect, 0 );




        /*Now your time. Try adding a texture to this example and replacing the second parameter of SDL_RenderParty_Polygon with it.
        SDL2_RenderParty has some cool effects for textures, so feel free to Press the Space key a few times until you get your desired effect
        */

        SDL_RenderPresent(sdl_apprenderer);
    }
    SDL2_RenderParty_Quit();


    if( sdl_apprenderer != NULL )
    {
        SDL_DestroyRenderer( sdl_apprenderer );
        sdl_apprenderer = NULL;
    }

    if( app_window != NULL )
    {
        SDL_DestroyWindow(app_window);
        app_window = NULL;
    }
    SDL_Quit();

    return 0;
}
