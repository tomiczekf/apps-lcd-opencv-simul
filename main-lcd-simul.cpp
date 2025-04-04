// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 09/2019
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         OpenCV simulator of LCD
//
// **************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lcd_lib.h"
#include "font8x8.h"
#include "graph_class.hpp"

int main()
{
    lcd_init();                     // LCD initialization

    /*uint16_t l_color_red = 0xF800;
    uint16_t l_color_green = 0x07E0;
    uint16_t l_color_blue = 0x001F;
    uint16_t l_color_white = 0xFFFF;

    // simple animation display four color square using LCD_put_pixel function
    int l_limit = LCD_HEIGHT - 40;
    for ( int ofs = 0; ofs < 20; ofs++ ) // square offset in x and y axis
    {
        for ( int i = 0; i < l_limit; i++ )
        {
            lcd_put_pixel( ofs + i, ofs + 0, l_color_red );
            lcd_put_pixel( ofs + 0, ofs + i, l_color_green );
            lcd_put_pixel( ofs + i, ofs + l_limit, l_color_blue );
            lcd_put_pixel( ofs + l_limit, ofs + i, l_color_white );
        }
    }*/
    RGB red = {255, 0, 0};
    RGB green = {0, 255, 0};
    RGB blue = {0, 0, 255};
    RGB white = {255, 255, 255};
    RGB black = {0, 0, 0};

    Point2D center = {LCD_WIDTH / 2, LCD_HEIGHT / 2};
    int radius = 150;

    Circle circle(center, radius, red, white);
    circle.draw();

    // Create a Character object
    Point2D char_pos = {50, 50}; // Position on the screen
    Character character(char_pos, 'X', white, black);
    character.draw();


    

    // Define points for the tall rectangle
    Point2D tall_top_left = {50, 50};
    Point2D tall_top_right = {100, 50};
    Point2D tall_bottom_left = {50, 200};
    Point2D tall_bottom_right = {100, 200};

    // Draw the tall rectangle
    Line tall_top(tall_top_left, tall_top_right, red, white);
    Line tall_bottom(tall_bottom_left, tall_bottom_right, red, white);
    Line tall_left(tall_top_left, tall_bottom_left, red, white);
    Line tall_right(tall_top_right, tall_bottom_right, red, white);

    tall_top.draw();
    tall_bottom.draw();
    tall_left.draw();
    tall_right.draw();

    // Define points for the wide rectangle
    Point2D wide_top_left = {150, 100};
    Point2D wide_top_right = {300, 100};
    Point2D wide_bottom_left = {150, 150};
    Point2D wide_bottom_right = {300, 150};

    // Draw the wide rectangle
    Line wide_top(wide_top_left, wide_top_right, green, white);
    Line wide_bottom(wide_bottom_left, wide_bottom_right, green, white);
    Line wide_left(wide_top_left, wide_bottom_left, green, white);
    Line wide_right(wide_top_right, wide_bottom_right, green, white);

    wide_top.draw();
    wide_bottom.draw();
    wide_left.draw();
    wide_right.draw();

    // Draw diagonal lines for the tall rectangle
    Line tall_diagonal1(tall_top_left, tall_bottom_right, blue, white);
    Line tall_diagonal2(tall_top_right, tall_bottom_left, blue, white);

    tall_diagonal1.draw();
    tall_diagonal2.draw();

    // Draw diagonal lines for the wide rectangle
    Line wide_diagonal1(wide_top_left, wide_bottom_right, blue, white);
    Line wide_diagonal2(wide_top_right, wide_bottom_left, blue, white);

    wide_diagonal1.draw();
    wide_diagonal2.draw();


    cv::imshow( LCD_NAME, g_canvas );   // refresh content of "LCD"
    cv::waitKey( 0 );                   // wait for key 
}


