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

#include "lcd_lib.h"
// Simple graphic interface

struct Point2D 
{
    int32_t x, y;
};


struct RGB
{
    uint8_t r, g, b;
};


class GraphElement
{
public:
    // foreground and background color
    RGB m_fg_color, m_bg_color;

    // constructor
    GraphElement( RGB t_fg_color, RGB t_bg_color ) : 
        m_fg_color( t_fg_color ), m_bg_color( t_bg_color ) {}

    // ONLY ONE INTERFACE WITH LCD HARDWARE!!!
    
    // Draw graphics element
    virtual void draw() = 0;
    
    // Hide graphics element
    virtual void hide() { swap_fg_bg_color(); draw(); swap_fg_bg_color(); }
    void drawPixel( int32_t t_x, int32_t t_y ) { 
        lcd_put_pixel( t_x, t_y, convert_RGB888_to_RGB565( m_fg_color ) ); 
    }
private:
    // swap foreground and backgroud colors
    void swap_fg_bg_color() { RGB l_tmp = m_fg_color; m_fg_color = m_bg_color; m_bg_color = l_tmp; } 

    // IMPLEMENT!!!
    // conversion of 24-bit RGB color into 16-bit color format
    uint16_t convert_RGB888_to_RGB565( RGB t_color ) { 
        uint16_t r = (t_color.r >> 3) & 0x1F; // Extract top 5 bits of red
        uint16_t g = (t_color.g >> 2) & 0x3F; // Extract top 6 bits of green
        uint16_t b = (t_color.b >> 3) & 0x1F; // Extract top 5 bits of blue

        return (r << 11) | (g << 5) | b; // Combine into RGB565 format
    }// Combine into RGB565 format}
};


class Pixel : public GraphElement
{
public:
    // constructor
    Pixel( Point2D t_pos, RGB t_fg_color, RGB t_bg_color ) : GraphElement( t_fg_color, t_bg_color ), m_pos( t_pos ) {}
    // Draw method implementation
    virtual void draw() { drawPixel( m_pos.x, m_pos.y ); }
    // Position of Pixel
    Point2D m_pos;
};


class Circle : public GraphElement
{
public:
    // Center of circle
    Point2D m_center;
    // Radius of circle
    int32_t m_radius;

    Circle( Point2D t_center, int32_t t_radius, RGB t_fg, RGB t_bg ) : 
        GraphElement( t_fg, t_bg ), m_center( t_center ), m_radius( t_radius ) {}

    void draw() override 
        {
            int32_t x = 0;
            int32_t y = m_radius;
            int32_t d = 3 - 2 * m_radius;
    
            // Draw initial points
            drawCirclePoints(m_center.x, m_center.y, x, y);
            while (y >= x) 
            {
                x++;
                if (d > 0) 
                {
                    y--;
                    d = d + 4 * (x - y) + 10;
                } 
                else 
                {
                    d = d + 4 * x + 6;
                }
                drawCirclePoints(m_center.x, m_center.y, x, y);
            }
        }
    
    private:
        // Helper function to draw symmetric points of the circle
        void drawCirclePoints(int32_t xc, int32_t yc, int32_t x, int32_t y) 
        {
            drawPixel(xc + x, yc + y);
            drawPixel(xc - x, yc + y);
            drawPixel(xc + x, yc - y);
            drawPixel(xc - x, yc - y);
            drawPixel(xc + y, yc + x);
            drawPixel(xc - y, yc + x);
            drawPixel(xc + y, yc - x);
            drawPixel(xc - y, yc - x);
        }
};



class Character : public GraphElement 
{
public:
    // position of character
    Point2D m_pos;
    // character
    char m_character;

    Character( Point2D t_pos, char t_char, RGB t_fg, RGB t_bg ) : 
      GraphElement( t_fg, t_bg ), m_pos( t_pos ), m_character( t_char ) {};
      void draw() override 
      {
          // Get the ASCII value of the character
          int ascii_value = static_cast<int>(m_character);
          // Draw the character using the font8x8 array
          for (int i = 0; i < 8; i++) 
          {
              for (int j = 0; j < 8; j++) 
              {
                  if (font8x8[ascii_value][i] & (1 << (7 - j))) 
                  {
                      drawPixel(m_pos.x + j, m_pos.y + i);
                  }
              }
          }
      }
};


class Line : public GraphElement
{
public:
    // the first and the last point of line
    Point2D m_pos1, m_pos2;

    Line( Point2D t_pos1, Point2D t_pos2, RGB t_fg, RGB t_bg ) : 
      GraphElement( t_fg, t_bg ), m_pos1( t_pos1 ), m_pos2( t_pos2 ) {}

    void draw() {
        int32_t dx = m_pos2.x - m_pos1.x;
        int32_t dy = m_pos2.y - m_pos1.y;
        int32_t steps = std::max(abs(dx), abs(dy));
        float xIncrement = static_cast<float>(dx) / steps;
        float yIncrement = static_cast<float>(dy) / steps;

        float x = m_pos1.x;
        float y = m_pos1.y;

        for (int i = 0; i <= steps; i++) {
            drawPixel(static_cast<int32_t>(x), static_cast<int32_t>(y));
            x += xIncrement;
            y += yIncrement;
        }
    }; // IMPLEMENT!!!
};


