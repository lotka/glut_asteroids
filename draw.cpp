#include "main.h"

void drawShape(objectShape shape,GLenum type)
{
   int i;

   glBegin(type);
   for(i=0; i<shape.vertexNumber; i++)
   {
     glVertex2f(shape.vertex[i][0],shape.vertex[i][1]);
   }
   glEnd();

}

objectShape asteroid[10];
int asteroidNumberType = 1;
objectShape ship;

void setShapes()
{

    int i,j;
    float drawAngle=0;
    float size;

    ship.vertexNumber=3;

    ship.vertex={ { 0.00 ,0.15},
                  { 0.05 ,0.00},
                  {-0.05 ,0.00}};

   for(j=0;j<ASTEROID_SHAPE_NUMBER;j++)
   {
    drawAngle=0;
    size=randNumber(1000)/10000.00;

    if(size<0.1)
    {
        size += 0.1;
    }
    asteroid[j].vertexNumber=8;
    for(i=0; i<asteroid[1].vertexNumber;i++)
    {
        asteroid[j].vertex[i][0] = size*(cosf(drawAngle) + (randNumber(100) - 50)/100.00);
        asteroid[j].vertex[i][1] = size*(sinf(drawAngle) + (randNumber(100) - 50)/100.00);
        drawAngle += 2*M_PI/(float)asteroid[1].vertexNumber;
    }
   }

    printf("Finished Generating Shapes\n");

}

/* Stolen from the internet because it claimed to be mega efficient */
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float tangetial_factor = tanf(theta);//calculate the tangential factor

    float radial_factor = cosf(theta);//calculate the radial factor

    float x = r;//we start at angle = 0

    float y = 0;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);//output vertex

        //calculate the tangential vector
        //remember, the radial vector is (x, y)
        //to get the tangential vector we flip those coordinates and negate one of them

        float tx = -y;
        float ty = x;

        //add the tangential vector

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        //correct using the radial factor

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

void DrawAsteroid()
{
    glBegin(GL_POLYGON);
    glVertex2f(0.1,0.1);
    glVertex2f(0.1,0.0);
    glVertex2f(0.05,-0.05);
    glVertex2f(-0.05,-0.05);
    glVertex2f(-0.05,0.05);
    glEnd();
}

void DrawShip()
{

}

