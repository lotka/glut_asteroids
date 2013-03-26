#include "main.h"

using namespace std;

int thrust;
int steer;
extern objectShape asteroid[5];
extern objectShape ship;

#define ANGULAR_VELOCITY 4
#define MAX_SPEED 2

class object
{
public:
    float x;
    float y;
    float angle;
    float speed;
    float spin;
    int type;
    int asteroidType;
    objectShape shape;

    object()
    {
        thrust = ZERO;
        steer = ZERO;
        x = 0.0;
        y = 0.0;
        angle = 0.0;
        speed = 0.0;
        spin = 0.0;
        type = 0;
    }

    void update()
    {
        if(type==1)
        updateShip();

        if(type==2)
        updateBullet();

        if(type==3)
        updateAsteroid();

        checkNotOutOfBounds();

    }

    void updateBullet()
    {
        x += -speed*sinf(2*M_PI*angle/360.0f)/100.0f;
        y += speed*cosf(2*M_PI*angle/360.0f)/100.0f;
    }

    void updateAsteroid()
    {
        x += -speed*sinf(2*M_PI*angle/360.0f)/100.0f;
        y += speed*cosf(2*M_PI*angle/360.0f)/100.0f;
        angle += 1;
    }

    void updateShip()
    {
        switch(thrust)
        {
        case POSITIVE:
            if(speed<MAX_SPEED)
            {
                speed += 0.1;
            }
            break;
        case ZERO:
            break;
        case NEGATIVE:
            if(speed>-MAX_SPEED)
            {
                speed -= 0.1;
            }
            break;
        }

        x += -speed*sinf(2*M_PI*angle/360.0f)/100.0f;
        y += speed*cosf(2*M_PI*angle/360.0f)/100.0f;

        switch(steer)
        {
        case POSITIVE:
            if(spin<1)
            {
                spin += 0.1;
            }
            break;
        case ZERO:
            if( spin<0.01 && spin>-0.01 )
                spin=0;
            else if(spin > 0)
                spin -= 0.05;
            else if(spin < 0)
                spin += 0.05;
            break;
        case NEGATIVE:
            if(spin>-1)
            {
                spin -= 0.1;
            }
            break;
        }

        angle += ANGULAR_VELOCITY*spin;
    }

    void checkNotOutOfBounds()
    {
        if( fabs(x)>1.05 || fabs(y) > 1.05)
        {
            x=-x;
            y=-y;
        }
    }

    void draw()
    {
        //Player Ship
        if(type==1)
        {
            glTranslatef(x,y,0);
            glRotatef(angle,0.0,0.0,1);
            drawShape(shape,GL_LINE_LOOP);
        }

        //Bullet
        if(type==2)
        {
            glTranslatef(x,y,0);
            DrawCircle(0,0,0.005,5);
        }


        //Asteroid
        if(type==3)
        {
            glTranslatef(x,y,0);
            glRotatef(angle,0.0,0.0,1);
            drawShape(shape,GL_LINE_LOOP);
            //drawShape(asteroid[0],GL_LINE_LOOP);
        }
    }

    int detectCollision ()
    {
        return 0;
    }
};

int object_number;
vector<object> object_list(1);

void renderScene(void)
{
    int i;

    for(i=0; i<object_number; i++)
    {
        object_list[i].update();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for(i=0; i<object_number; i++)
    {
        glColor3f(1,1,1);
        glPushMatrix();
        glLoadIdentity();
        object_list[i].draw();
        glPopMatrix();
    }

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{

    printf("Loading glut..\n");

    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(900,900);
    glutCreateWindow("asteroids");

    //keyboard
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    printf("Generating Shapes.\n");
    //Int objects
    setShapes();
    object_number=1;
    object_list[0].type = 1; //Make ship
    object_list[0].shape=ship;
    addAsteroid(0,0);
    addAsteroid(0.5,0);
    addAsteroid(0,.2);
    addAsteroid(0,0.7);
    addAsteroid(0.3,0);
    addAsteroid(1,1);

    printf("Entering render loop.\n");
    // register callbacks
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    // enter GLUT event processing cycle
    glutMainLoop();

    printf("Goodbye!\n");

    return 1;
}

void addBullet()
{
    ++object_number;
    object_list.resize(object_number);
    object_list[object_number-1].type=2;
    object_list[object_number-1].x=object_list[0].x-(0.15*sinf(2*M_PI*object_list[0].angle/360.0f)); //Beware: evil code lurks around here
    object_list[object_number-1].y=object_list[0].y+(0.15*(cosf(2*M_PI*object_list[0].angle/360.0f)));
    object_list[object_number-1].speed=object_list[0].speed+0.5;
    object_list[object_number-1].angle=object_list[0].angle;
}

void addAsteroid(float x, float y)
{
    static int i = 0;

    ++object_number;
    object_list.resize(object_number);
    object_list[object_number-1].type=3;
    object_list[object_number-1].asteroidType=0;
    object_list[object_number-1].shape=asteroid[i];
    object_list[object_number-1].x=x;
    object_list[object_number-1].y=y;
    object_list[object_number-1].speed=object_list[0].speed+0.5;
    object_list[object_number-1].angle=object_list[0].angle;

    i++;

    if(i==ASTEROID_SHAPE_NUMBER)
    {
        i=0;
    }
}

/* Not finished */
void removeObject()
{
    object_list[object_number].type=0;
}

int randNumber(int number)
{
   return rand() & number;
}







