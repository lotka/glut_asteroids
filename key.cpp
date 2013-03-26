#include "main.h"

extern int thrust;
extern int steer;

void keyPressed(unsigned char key, int x, int y)
{
    switch(key)
    {
    case ' ':
        addBullet();
        break;
    case 'n':
        addAsteroid(0,0);
        break;
    case 'r':
        printf("%d\n", randNumber(100));
        break;
    case 'w':
        thrust=POSITIVE;
        break;

    case 's':
        thrust=NEGATIVE;
        break;

    case 27:
        exit(0);
        break;

    case 'a':
        steer=POSITIVE;
        break;

    case 'd':
        steer=NEGATIVE;
        break;
    }
}

void keyUp (unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'w':
        thrust=ZERO;
        break;

    case 's':
        thrust=ZERO;
        break;

    case 'a':
        steer=ZERO;
        break;

    case 'd':
        steer=ZERO;
        break;
    }
}

