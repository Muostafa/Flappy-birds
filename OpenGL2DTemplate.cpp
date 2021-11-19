//  Includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

//-----------------
// 
//  Methods Signatures
void drawRect(int x,int y, int w, int h);
void drawplayer(int x, int y, float r);
void drawcircle(int x, int y, float r);
void drawpowerup(int x, int y, int r);
void Key(unsigned char key, int x, int y);
void Timer(int value);
void Timer2(int value);
void Timer3(int value);
void Timer4(int value);
void Display();
void output(int x, int y, float r, float g, float b, char* string);
bool intersects(int x, int y, int w, int bx, int by, int bw, int bg);
bool intersectRect(int x1, int y1, int x2, int y2, int bx1, int by1, int bx2, int by2);
bool tookpowerup(int x, int y, int w, int px, int py, int pw);
void lose();
//-----------------

//  Global Variables
int playerY = 200;
int playerX = 150;
int bar1X = 0;   
int bar1y = 0;       
int bar2X = 400;       
int bar2y = (rand()*playerY) % 500 + 40;
bool bar1pu = false;
bool bar2pu = false;
bool bar1readypowerup = false;
bool bar2readypowerup = false;
int bargap = 130;
int barwidth = 30;
int jump = 70;
bool jumping = false;
bool powerup = false;
int barriesrspassed =0 ;
bool lost = false;
long score = 0;
int lives = 3;
int colliding = 2;
int ptime = 2;
//-----------------

void main(int argc, char** argr) {
    glutInit(&argc, argr);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Flappy bird");
    //PlaySound(TEXT("a.wav"), NULL, SND_ASYNC | SND_FILENAME);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed
    glutTimerFunc(0, Timer, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
    glutTimerFunc(0, Timer2, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
    glutTimerFunc(0, Timer3, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
   // glutTimerFunc(0, Timer4, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.8, 0.8, 1, 0);
    gluOrtho2D(0, 800, 0, 800);
    glutMainLoop();
}

void reset() {
    //  Global Variables

//  Global Variables
    playerY = 200;
    playerX = 150;
    bar1X = 0;
    bar1y = 0;
    bar2X = 400;
    bar2y = (rand() * playerY) % 500 + 40;
     bar1pu = false;
     bar2pu = false;
     bar1readypowerup = false;
     bar2readypowerup = false;
     bargap = 130;
     barwidth = 30;
     jump = 70;
     jumping = false;
     powerup = false;
     barriesrspassed = 0;
     lost = false;
     score = 0;
     lives = 3;
     colliding = 2;
     ptime = 2;

}
void print(int x, int y, char* string)
{
    glColor3f(1, 0, 0);
    int len, i;

    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawHeart(int x, int y, int w) {
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w/2, y+w/4);
    glVertex2f(x + w, y+w/8);
    glVertex2f(x+7*w/8, y-w/4);
    glVertex2f(x+w/2, y-2*w/3);
    glVertex2f(x, y-w);
    glVertex2f(x - w / 2, y - 2 * w / 3);
    glVertex2f(x - 7 * w / 8, y - w / 4);
    glVertex2f(x - w, y + w / 8);
    glVertex2f(x - w / 2, y + w / 4);
    glEnd();
}
void drawRect(int x,int y, int w, int gap) {
    glColor3f(0, 1, 0);
    if(powerup){ glColor3f(0.2, 0.5, 0.5); }
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, 0);
    glVertex2f(x, 0);
    glEnd();  
    //if (powdis <= 0) { drawpowerup((int)(x + w / 2), (int)(y + gap / 2), 10);}
    glColor3f(0, 1, 0);
    if (powerup) { glColor3f(0.2, 0.5, 0.5); }
    glBegin(GL_POLYGON);
    glVertex2f(x, y+gap);
    glVertex2f(x + w, y+gap);
    glVertex2f(x + w,800);
    glVertex2f(x, 800);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y - 15);
    glVertex2f(x + w, y - 15);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x, y + 15+gap);
    glVertex2f(x + w, y +gap +15);
    glEnd();
}
void drawRectpowerup(int x, int y, int w, int gap) {
    glColor3f(0, 1, 0);
    if (powerup) { glColor3f(0.2, 0.5, 0.5); }
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, 0);
    glVertex2f(x, 0);
    glEnd();
    drawpowerup((int)(x + w / 2), (int)(y + gap / 2), 10);
    glColor3f(0, 1, 0);
    if (powerup) { glColor3f(0.2, 0.5, 0.5); }
    glBegin(GL_POLYGON);
    glVertex2f(x, y + gap);
    glVertex2f(x + w, y + gap);
    glVertex2f(x + w, 800);
    glVertex2f(x, 800);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y - 15);
    glVertex2f(x + w, y - 15);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x, y + 15 + gap);
    glVertex2f(x + w, y + gap + 15);
    glEnd();
}
void drawpowerup(int x, int y, int w) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - w, y - w);
    glVertex2f(x + w, y - w);
    glVertex2f(x + w, y + w);
    glVertex2f(x - w, y + w);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x - w, y - w);
    glVertex2f(x + w, y + w);
    glEnd();
}
void drawRectangle(int x, int y, int w) {
    glBegin(GL_POLYGON);
    glVertex2f(x-w, y-w);
    glVertex2f(x + w, y-w);
    glVertex2f(x + w, y+w);
    glVertex2f(x-w, y+w);
    glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawplayer(int x, int y, float r) {
    glColor3f(1, 0.5, 0);
    if (powerup)glColor3f(1, 0, 0);
    drawRectangle(x, y, r);
    glColor3f(0, 0, 0);
    drawcircle((int)x+r/2, (int)y+r/2, r/7);
    drawcircle((int)x-r/2, (int)y+r/2, r/7);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x-r/2,y-r/2 );
    if(powerup)glVertex2f(x , y );
    glVertex2f(x+r/2, y-r/2);
    glEnd();
}
void drawcircle(int x, int y, float r) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric* quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}
bool intersects(int x, int y, int w,int bx,int by,int bw,int bg) {
    return(intersectRect(x - w, y + w, x + w, y - w,bx,by,bx+bw,0) || intersectRect(x - w, y + w, x + w, y - w, bx, 800, bx + bw,by+bg ));
}
bool tookpowerup(int x, int y, int w,int px,int py,int pw) {
    return(intersectRect(x - w, y + w, x + w, y - w, px-pw, py+pw, px + pw, py-pw));
}
bool intersectRect(int x1,int y1,int x2,int y2, int bx1,int by1,int bx2,int by2 ) {
    //                   l1                 r1          l2              r2
    // If one rectangle is on left side of other
    if (x1 > bx2 || bx1 >x2)
        return false;

    // If one rectangle is above other
    if (y2 >= by1||by2 >= y1)
        return false;
    return true;
}

// Keyboard handler function
//   key: the key pressed on the keyboard
//   x  : the X coordinate of the mouse cursor at the moment of pressing the key
//   y  : the Y coordinate of the mouse cursor at the moment of pressing the key
void Key(unsigned char key, int x, int y) {

    if (key == ' '&&!lost)
    {   
        jump = playerY + 70;
        jumping = true;
        glutTimerFunc(1, Timer2, 0);
    }
    if ((key == 'r') && lost)
    {
        reset();
    }

    glutPostRedisplay();
}

void Timer4(int value) {
    //if ((playerY + bar1X) % 2 == 1) {bar1readypowerup =true;} else {   if(!bar1readypowerup) bar2readypowerup = true; }
    if (ptime == 0) {
        powerup = true;
        bar1pu = false;
        bar2pu = false;
        bar1readypowerup = false;
        bar2readypowerup = false;
        ptime++;
        glutPostRedisplay();
        glutTimerFunc(7 * 1000, Timer4, 0);
    }
    else
    {
        if (ptime == 1) { ptime++; powerup = false; }
    }
    glutPostRedisplay();
}
void Timer3(int value) {
    if (colliding == 0) {if(!powerup) if(lives>0)lives--; colliding++; }
    glutPostRedisplay();
    if (colliding == 1) { colliding+=2; glutTimerFunc(1 * 500, Timer3, 0); }
}
void Timer2(int value) {
    playerY+=9;
    glutPostRedisplay();
    if (playerY < jump) {
        glutTimerFunc(1, Timer2, 0);
    }
    else {
        jumping = false;
    }
}
void Timer(int value) {
    if (!lost) {
    playerY -= 4;
    bar1X -= 3;
    bar2X -= 3;
    score++;
    }
    glutPostRedisplay();
    glutTimerFunc(10, Timer, 0);
}
void lose() {
    PlaySound(TEXT("lose.wav"), NULL, SND_ASYNC | SND_FILENAME);
    lost = true;
}
void output(int x, int y, float r, float g, float b,  char* string)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
void Display() {
    char* p0s[20];   
    if (bar1X + barwidth == playerX || bar2X + barwidth == playerX) { barriesrspassed += 1; }
    if (bar1X < 0) {
        bar1X = 800;
        bar1y = (rand() * playerY) % 500 + 40;
        if (bar1readypowerup)bar1pu = true; else bar1pu = false;
    }
    if (bar2X < 0) {
        bar2X = 800;
        bar2y = (rand() * playerY) % 500 + 40;
        if (bar2readypowerup)bar2pu = true;
    }
    if (barriesrspassed % 3 == 0 || barriesrspassed % 3 == 1) { if(!powerup)bar1readypowerup = true; }
    else bar1readypowerup = false;
    glClear(GL_COLOR_BUFFER_BIT);
    drawHeart(80, 713, 15);
    drawRect(bar1X, bar1y, barwidth, bargap);
    drawRect(bar2X, bar2y, barwidth, bargap);
    sprintf((char*)p0s, "Score: %d", score);
    print(400, 700, (char*)p0s);
    sprintf((char*)p0s, "=%d", lives);
    print(100, 700, (char*)p0s);
    if (lost) {
        output(350, 400, 0, 0, 0, "YOU LOST");
        output(350, 350, 0, 0, 0, "PRESS R TO TRY AGAIN");
    }
    drawplayer(playerX, playerY, 15);
    if ((playerY > 785 || playerY < 15||lives<=0)&&!lost) { lose(); }
    if(intersects(playerX, playerY, 15, bar1X, bar1y, barwidth, bargap)) {
        if (colliding >= 2) { colliding = 0; glutTimerFunc(1 * 460, Timer3, 0); }
       // if (playerY > bar1y)playerY = bar1y + bargap - 30;
    }
    if (intersects(playerX, playerY, 15, bar2X, bar2y, barwidth, bargap)) {
        if (colliding >= 2) { colliding = 0; glutTimerFunc(1 * 460, Timer3, 0); }
    }

    if ((tookpowerup(playerX, playerY, 15, bar1X + barwidth / 2, bar1y + bargap / 2, 10)&&bar1pu)|| (tookpowerup(playerX, playerY, 15, bar2X + barwidth / 2, bar2y + bargap / 2, 10) && bar2pu)) {
        if (colliding == 0) 
            { lives--; colliding++;}
        //if(ptime>=2)
        {  ptime = 0; bar1pu = false; glutTimerFunc(1 * 1, Timer4, 0);  }
        PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC | SND_FILENAME);
        //powerup = true;
    }

    if(bar1pu&&!powerup)drawpowerup((int)(bar1X + barwidth / 2), (int)(bar1y + bargap / 2), 10);
    if(bar2pu&&!powerup)drawpowerup((int)(bar2X + barwidth / 2), (int)(bar2y + bargap / 2), 10);
    glFlush();
}
