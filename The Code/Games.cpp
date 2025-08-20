#define STB_IMAGE_IMPLEMENTATION 
#include <windows.h>  // for MS Windows
#include <GL\glut.h>  // GLUT, include glu.h and gl.h
#include<stb_image.h>
//#include<cmath>
#include<string>
#include<iostream>

//using namespace std;
float diam_coverx , diam_covery , diam_coverz;
float diam_cntx = -15.0, diam_cnty = -25.0, diam_cntz = -16.5, angle1 = 0, Distance;
unsigned int texture;
unsigned char* data;
float eyex = 0, eyey = 20, eyez = -35, upx = 0, upy = 0, upz = -50;
float angle = 0, e1_angel = 0, e2_angel = 180, e3_angel = 90, p_angel = 0 , angle2 = 0;
bool flag = 0, e_flag = 1, e2_flag = 1, e3_flag = 1;
float move_x = 0.0, move_z = 0.0, move2_z = 0.0, Pmove_x = 0.0, Pmove_z = 0.0;
int width, height, nrChannels;
int position_x = 8, position_z = 11, life = 3, num_Diam = 8;
float plat_x = 0.0, plat_y = 0.0, plat_z = -51.0;
int score = 0;
int height_screen, width_screen;
bool fullScreen = 1;
//float matspec[] = { .393548,.271906,.166721,1 };
//float lightspec[] = { .2,.2,.2,1 };

//----------- inside draw variables
float mainx = -25.5, mainz = -51.0, xmin, xmax, ymin = -25.0, ymax = -23.0, zmin, zmax;
float e_mainx = 21.0, e_mainy = -23.5, e_mainz = -37.5, e_xmin = e_mainx - 1.5, e_xmax = e_mainx + 1.5, e_ymin = e_mainy - 1.5, e_ymax = e_mainy + 1.5, e_zmin = e_mainz - 1.5, e_zmax = e_mainz + 1.5;
float e2_mainx = -21.0, e2_mainy = -23.5, e2_mainz = -13.5, e2_xmin = e2_mainx - 1.5, e2_xmax = e2_mainx + 1.5, e2_ymin = e2_mainy - 1.5, e2_ymax = e2_mainy + 1.5, e2_zmin = e2_mainz - 1.5, e2_zmax = e2_mainz + 1.5;
float e3_mainx = -18.0, e3_mainy = -23.5, e3_mainz = -46.5, e3_xmin = e3_mainx - 1.5, e3_xmax = e3_mainx + 1.5, e3_ymin = e3_mainy - 1.5, e3_ymax = e3_mainy + 1.5, e3_zmin = e3_mainz - 1.5, e3_zmax = e3_mainz + 1.5;
float p_mainx = 0, p_mainy = -23.5, p_mainz = -16.5, p_xmin = p_mainx - 1.5, p_xmax = p_mainx + 1.5, p_ymin = p_mainy - 1.5, p_ymax = p_mainy + 1.5, p_zmin = p_mainz - 1.5, p_zmax = p_mainz + 1.5;
float temp = e_mainz, temp2 = e2_mainz, temp3 = e3_mainx, p_tempx = p_mainx, p_tempz = p_mainz;
float option1 = 0.9, option2 = 0.5, chanal = -1;



bool map_arr[17][17] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                         {1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
                         {1,0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,1},{1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1},
                         {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
                         {1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},{1,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,1},
                         {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1},{1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
                         {1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1},{1,0,1,0,0,0,1,1,0,1,1,0,0,0,1,0,1},
                         {1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
float diam_arr[16] = { -21.0 , -46.5 , 21.0 , -46.5 , -21.0 , -40.5 , 21.0 , -40.5,
                       -21.0,-10.5,21.0,-10.5,-15.0,-16.5,15.0,-16.5 };
bool map_dima[8] = { 1,1,1,1,1,1,1,1 };
//----------------------
void writeStr(float x, float y, std::string  str, void* font)
{
    int len = str.length();
    glRasterPos2f(x, y);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

//-----------------------
void initial_value() {
    Pmove_x = 0;
    Pmove_z = 0;
    position_z = 11;
    position_x = 8;
    p_mainx = 0;
    p_mainz = -16.5;
    p_tempx = p_mainx;
    p_tempz = p_mainz;
   /* eyex = 0;
    eyey = 20;
    eyez = -35;
    upx = 0;
    upy = 0;
    upz = -50;*/
    p_angel = 0;
    plat_x = 0.0; plat_y = 0.0; plat_z = -51.0;
}
//------------------------
void load(int imgnum);
void check(unsigned char* data);
//----------- Initial Funcation
void initGL() {
      glClearColor(0.0f, 0.8f, 0.8f, 0.0f); // Set background color to black and opaque
    //glClearColor(0.211, 0.329, 0.447, 1.0);
   /*   glLightfv(GL_LIGHT0, GL_SPECULAR, lightspec);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHTING);
      glMaterialfv(GL_FRONT, GL_SPECULAR, matspec);*/
    //glClearColor(0.211, 0.329, 0.447, 1.0);
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glEnable(GL_TEXTURE_2D);

    //glShadeModel(GL_SMOOTH);   // Enable smooth shading



}
//----------- Display Funcation
void drow() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();// Reset the model-view matrix
    gluLookAt(
        /*0, 20, -35,
        0, 0, -50,
        0, 100, 0*/
        eyex, eyey, eyez,
        upx, upy, upz,
        0, 100, 0
    );


    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -51.0f);  // Move right and into the screen



    glColor3f(1.0, 1.0, 0);
    writeStr(-13.5, 9, "LIFE : ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-12.0, 9, std::to_string(life), GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-15.5,6, "SCORE :", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-13.0, 6, std::to_string(score), GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0, 1.0, 1.0);
    writeStr(-14.5, 8, "DIAMONDS :", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-11.25, 8, std::to_string(num_Diam), GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(9.3, 8, "  If You Need To Go ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(10.0, 7, "Menu Pls, Press [0] ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(11, 5, "If You Need To Close", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(13, 4, "The Game", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(12.5, 3, "  Pls, Press [ESC] ", GLUT_BITMAP_TIMES_ROMAN_24);

    //writeStr(-14.5, 8, "DIAMONDS :", GLUT_BITMAP_TIMES_ROMAN_24);

    glPopMatrix();

    glTranslatef(plat_x, plat_y, plat_z);  // Move right and into the screen
    load(1);

    //glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
    glTranslatef(0.0f, 0.0f, -25.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);   //Z
    glTranslatef(0.0f, 0.0f, 25.0f);

    
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
       // Top face (y = 1.0f)
       // Define vertices in counter-clockwise (CCW) order with normal pointing out
    //glColor3f(0, 0.721, 0.003);     // gray
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(25.5f, -25.0f, 0.0f);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(-25.5f, -25.0f, 0.0f);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(-25.5f, -25.0f, -51.0f);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(25.5f, -25.0f, -51.0f);
    glEnd();   // Done drawing the plat
 
 //-------------------------------------------------------------

    load(4);
    glPushMatrix();
    for (int i = 0; i < 16; i += 2)
    {
        if (map_dima[i / 2])
        {
            diam_cntx = diam_arr[i];
            glPushMatrix();
            diam_cntz = diam_arr[i + 1];
            glTranslatef(diam_cntx, diam_cnty, diam_cntz);
            glRotatef(angle1, 0.0f, 1.0f, 0.0f);   //around y 
            glTranslatef(-1 * diam_cntx, -1 * diam_cnty, -1 * diam_cntz);
            glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
            //glColor3f(1.0f, 0.0f, 0.0f);     // Red
            //top
            //glColor3f(1, 1, 1);
            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz - 1);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz - 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz - 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz + 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz + 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz + 1);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz + 1);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz + 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz + 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz - 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz - 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz - 1);

            //TOP
            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 3, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz - 1);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz - 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 3, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz - 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz + 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 3, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx + 1, diam_cnty + 2, diam_cntz + 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz + 1);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 3, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz + 1);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz + 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 3, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz + 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz - 0.5);

            glTexCoord2d(0.5f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 3, diam_cntz);
            glTexCoord2d(0.0f, 0.0f);
            glVertex3f(diam_cntx - 1, diam_cnty + 2, diam_cntz - 0.5);
            glTexCoord2d(0.0f, 1.0f);
            glVertex3f(diam_cntx, diam_cnty + 2, diam_cntz - 1);


            glEnd();
            glPopMatrix();

        }
    }
    glPopMatrix();
    //************************************************************************
    glPushMatrix();
    //face
    glTranslatef(0, 0, move_z);
    glTranslatef(e_mainx, e_mainy, e_mainz);
    glRotatef(e1_angel, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1 * e_mainx, -1 * e_mainy, -1 * e_mainz);

    /* glBegin(GL_TRIANGLES);
    //glColor3f(1.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmax - 0.5, e_ymax, e_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmax - 1, e_ymax, e_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmax - 0.75, e_ymax + 0.5, e_zmax);

    glColor3f(1.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmin + 0.5, e_ymax, e_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmin + 1, e_ymax, e_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmin + 0.75, e_ymax + 0.5, e_zmax);

    //-----

    glColor3f(1.0f, 1.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmax - 0.25, e_ymax - 1.25, e_zmax + 0.01);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmax - 1.25, e_ymax - 1.25, e_zmax + 0.01);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmax - 0.25, e_ymax - 0.75, e_zmax + 0.01);

    glColor3f(1.0f, 1.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmin + 0.25, e_ymax - 1.25, e_zmax + 0.01);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmin + 1.25, e_ymax - 1.25, e_zmax + 0.01);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmin + 0.25, e_ymax - 0.75, e_zmax + 0.01);

    //--------------------
    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(e_xmax - 0.75, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1.25, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1, e_ymax - 1.9, e_zmax + 0.01);



    glVertex3f(e_xmax - 1.25, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1.75, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1.5, e_ymax - 1.9, e_zmax + 0.01);



    glVertex3f(e_xmax - 1.75, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 2.25, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 2, e_ymax - 1.9, e_zmax + 0.01);

    //------
    glVertex3f(e_xmax - 0.75, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1.25, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1, e_ymax - 2.1, e_zmax + 0.01);



    glVertex3f(e_xmax - 1.25, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1.75, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 1.5, e_ymax - 2.1, e_zmax + 0.01);



    glVertex3f(e_xmax - 1.75, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 2.25, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 2, e_ymax - 2.1, e_zmax + 0.01);



    glEnd();


    //------
    glPointSize(5);
    glBegin(GL_POINTS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(e_xmax - 0.9, e_ymax - 1.2, e_zmax + 0.02);
    glVertex3f(e_xmin + 0.9, e_ymax - 1.2, e_zmax + 0.02);
    glEnd();
    //-------
    glPointSize(3);
    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(e_xmax - 0.5, e_ymax - 1.5, e_zmax + 0.01);
    glVertex3f(e_xmax - 0.5, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmin + 0.5, e_ymax - 2.5, e_zmax + 0.01);
    glVertex3f(e_xmin + 0.5, e_ymax - 1.5, e_zmax + 0.01);
    glEnd();
    //-------
    */

    // MMMMMMMMMMMMOOOOOOOOOOOONNNNNNNNNNNSSSSSTTTTTTOOOOOR
    load(5);
    glBegin(GL_QUADS);
    //face
    //glColor3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmax, e_ymax, e_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmin, e_ymax, e_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmin, e_ymin, e_zmax);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e_xmax, e_ymin, e_zmax);
    
    //top
    //glColor3f(0.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmax, e_ymax, e_zmax);
   // glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmin, e_ymax, e_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmin, e_ymax, e_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e_xmax, e_ymax, e_zmin);



    //--------- right 
    //load(6);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmax, e_ymax, e_zmax);
   // glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmax, e_ymax, e_zmin);
   // glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmax, e_ymin, e_zmin);
   // glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e_xmax, e_ymin, e_zmax);


    //--------- left 
   // load(6);
   // glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e_xmin, e_ymax, e_zmax);
   // glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmin, e_ymax, e_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmin, e_ymin, e_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e_xmin, e_ymin, e_zmax);

    //------------ back
    //load(6);
    glTexCoord2d(0.0f, 0.0f);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(e_xmax, e_ymax, e_zmin);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e_xmin, e_ymax, e_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e_xmin, e_ymin, e_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e_xmax, e_ymin, e_zmin);//

    glEnd();   // Done drawing the plat
    glPopMatrix();


    glPushMatrix();
    //face

    glTranslatef(0, 0, move2_z);

    glTranslatef(e2_mainx, e2_mainy, e2_mainz);
    glRotatef(e2_angel, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1 * e2_mainx, -1 * e2_mainy, -1 * e2_mainz);
    //-------
    load(5);
    glBegin(GL_QUADS);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmax);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmax);

    //glColor3f(0.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmin);



    //--------- right 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmax);


    //--------- left 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmax);

    //------------ back 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmin);//

    glEnd();   // Done drawing the plat
    glPopMatrix();


    glPushMatrix();
    //face

    glTranslatef(move_x, 0, 0);

    glTranslatef(e3_mainx, e3_mainy, e3_mainz);
    glRotatef(e3_angel, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1 * e3_mainx, -1 * e3_mainy, -1 * e3_mainz);
    load(5);
    glBegin(GL_QUADS);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmax);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmax);

    //glColor3f(0.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmin);



    //--------- right 

    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmax);


    //--------- left 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmax);

    //------------ back 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmin);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmin);//

    glEnd();   // Done drawing the plat
    glPopMatrix();

    glPushMatrix();

    // PPPPPPPPPPPPPPPPPLLLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAAAAAAAYYYYYYYYYYEEEEEERRRRR

    glTranslatef(Pmove_x, 0, Pmove_z);

    glTranslatef(p_mainx, p_mainy, p_mainz);
    glRotatef(p_angel, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1 * p_mainx, -1 * p_mainy, -1 * p_mainz);
    
    load(6);
    glBegin(GL_QUADS);
    //glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(p_xmax, p_ymax, p_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(p_xmin, p_ymax, p_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(p_xmin, p_ymin, p_zmax);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(p_xmax, p_ymin, p_zmax);

    //glColor3f(0.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(p_xmax, p_ymax, p_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(p_xmin, p_ymax, p_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(p_xmin, p_ymax, p_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(p_xmax, p_ymax, p_zmin);



    //--------- right 

    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(p_xmax, p_ymax, p_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(p_xmax, p_ymax, p_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(p_xmax, p_ymin, p_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(p_xmax, p_ymin, p_zmax);


    //--------- left 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(p_xmin, p_ymax, p_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(p_xmin, p_ymax, p_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(p_xmin, p_ymin, p_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(p_xmin, p_ymin, p_zmax);

    //------------ back 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(p_xmax, p_ymax, p_zmin);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(p_xmin, p_ymax, p_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(p_xmin, p_ymin, p_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(p_xmax, p_ymin, p_zmin);//

    glEnd();   // Done drawing the plat




    glPopMatrix();







/*



    //**********************************************************************************

        //******************************
        //*******************************
        //*******************************
        //*********************************


    glPushMatrix();
    //face

    glTranslatef(0, 0, move2_z);

    glTranslatef(e2_mainx, e2_mainy, e2_mainz);
    glRotatef(e2_angel, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1 * e2_mainx, -1 * e2_mainy, -1 * e2_mainz);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax - 0.5, e2_ymax, e2_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmax - 1, e2_ymax, e2_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmax - 0.75, e2_ymax + 0.5, e2_zmax);

    glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmin + 0.5, e2_ymax, e2_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin + 1, e2_ymax, e2_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin + 0.75, e2_ymax + 0.5, e2_zmax);

    //-----

    glColor3f(1.0f, 1.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax - 0.25, e2_ymax - 1.25, e2_zmax + 0.01);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmax - 1.25, e2_ymax - 1.25, e2_zmax + 0.01);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmax - 0.25, e2_ymax - 0.75, e2_zmax + 0.01);

    glColor3f(1.0f, 1.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmin + 0.25, e2_ymax - 1.25, e2_zmax + 0.01);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin + 1.25, e2_ymax - 1.25, e2_zmax + 0.01);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin + 0.25, e2_ymax - 0.75, e2_zmax + 0.01);

    //--------------------
    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(e2_xmax - 0.75, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1.25, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1, e2_ymax - 1.9, e2_zmax + 0.01);



    glVertex3f(e2_xmax - 1.25, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1.75, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1.5, e2_ymax - 1.9, e2_zmax + 0.01);



    glVertex3f(e2_xmax - 1.75, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 2.25, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 2, e2_ymax - 1.9, e2_zmax + 0.01);

    //------
    glVertex3f(e2_xmax - 0.75, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1.25, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1, e2_ymax - 2.1, e2_zmax + 0.01);



    glVertex3f(e2_xmax - 1.25, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1.75, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 1.5, e2_ymax - 2.1, e2_zmax + 0.01);



    glVertex3f(e2_xmax - 1.75, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 2.25, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 2, e2_ymax - 2.1, e2_zmax + 0.01);



    glEnd();

    //------
    glPointSize(5);
    glBegin(GL_POINTS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(e2_xmax - 0.9, e2_ymax - 1.2, e2_zmax + 0.02);
    glVertex3f(e2_xmin + 0.9, e2_ymax - 1.2, e2_zmax + 0.02);
    glEnd();
    //-------
    glPointSize(3);
    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(e2_xmax - 0.5, e2_ymax - 1.5, e2_zmax + 0.01);
    glVertex3f(e2_xmax - 0.5, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmin + 0.5, e2_ymax - 2.5, e2_zmax + 0.01);
    glVertex3f(e2_xmin + 0.5, e2_ymax - 1.5, e2_zmax + 0.01);
    glEnd();
    //-------
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmax);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmax);

    glColor3f(0.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmin);



    //--------- right 

    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmax);


    //--------- left 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmax);

    //------------ back 
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e2_xmax, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e2_xmin, e2_ymax, e2_zmin);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e2_xmin, e2_ymin, e2_zmin);
    //glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e2_xmax, e2_ymin, e2_zmin);//

    glEnd();   // Done drawing the plat

    glPopMatrix();

    //********************************************************************************
        //***********************************
        //*****************************
        //************************




    glPushMatrix();
    //face

    glTranslatef(move_x, 0, 0);

    glTranslatef(e3_mainx, e3_mainy, e3_mainz);
    glRotatef(e3_angel, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1 * e3_mainx, -1 * e3_mainy, -1 * e3_mainz);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax - 0.5, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmax - 1, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmax - 0.75, e3_ymax + 0.5, e3_zmax);

    glColor3f(1.0f, 0.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmin + 0.5, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin + 1, e3_ymax, e3_zmax);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin + 0.75, e3_ymax + 0.5, e3_zmax);

    //-----

    glColor3f(1.0f, 1.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax - 0.25, e3_ymax - 1.25, e3_zmax + 0.01);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmax - 1.25, e3_ymax - 1.25, e3_zmax + 0.01);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmax - 0.25, e3_ymax - 0.75, e3_zmax + 0.01);

    glColor3f(1.0f, 1.0f, 0.0f);
    //glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmin + 0.25, e3_ymax - 1.25, e3_zmax + 0.01);
    //glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin + 1.25, e3_ymax - 1.25, e3_zmax + 0.01);
    //glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin + 0.25, e3_ymax - 0.75, e3_zmax + 0.01);

    //--------------------
    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(e3_xmax - 0.75, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1.25, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1, e3_ymax - 1.9, e3_zmax + 0.01);



    glVertex3f(e3_xmax - 1.25, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1.75, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1.5, e3_ymax - 1.9, e3_zmax + 0.01);



    glVertex3f(e3_xmax - 1.75, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 2.25, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 2, e3_ymax - 1.9, e3_zmax + 0.01);

    //------
    glVertex3f(e3_xmax - 0.75, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1.25, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1, e3_ymax - 2.1, e3_zmax + 0.01);



    glVertex3f(e3_xmax - 1.25, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1.75, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 1.5, e3_ymax - 2.1, e3_zmax + 0.01);



    glVertex3f(e3_xmax - 1.75, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 2.25, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 2, e3_ymax - 2.1, e3_zmax + 0.01);



    glEnd();

    //------
    glPointSize(5);
    glBegin(GL_POINTS);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(e3_xmax - 0.9, e3_ymax - 1.2, e3_zmax + 0.02);
    glVertex3f(e3_xmin + 0.9, e3_ymax - 1.2, e3_zmax + 0.02);
    glEnd();
    //-------
    glPointSize(3);
    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex3f(e3_xmax - 0.5, e3_ymax - 1.5, e3_zmax + 0.01);
    glVertex3f(e3_xmax - 0.5, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmin + 0.5, e3_ymax - 2.5, e3_zmax + 0.01);
    glVertex3f(e3_xmin + 0.5, e3_ymax - 1.5, e3_zmax + 0.01);
    glEnd();
    //-------
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmax);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmax);

    glColor3f(0.0f, 0.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmin);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmin);



    //--------- right 

    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmin);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmin);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmax);


    //--------- left 
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmax);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmin);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmin);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmax);

    //------------ back 
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(e3_xmax, e3_ymax, e3_zmin);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(e3_xmin, e3_ymax, e3_zmin);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(e3_xmin, e3_ymin, e3_zmin);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(e3_xmax, e3_ymin, e3_zmin);//

    glEnd();   // Done drawing the plat

    glPopMatrix();
*/

    //---------------------
    load(2);
    // SSSSSSSSSSSSSSSHHHHHHHHHHHHHHHHHHHHHAAAAAAAAAAAAAAAAAAPPPPPPPPPPE
    glBegin(GL_QUADS);

    for (int i = 0; i < 17; i++)
    {
        zmin = mainz;
        zmax = mainz + 3;
        for (int j = 0; j < 17; j++)
        {

            xmin = mainx;
            xmax = mainx + 3;
            if (map_arr[i][j])
            {
                // draw box
                // --------- top 
                //glColor3f(0.976, 0.623, 0.003);
                glTexCoord2d(0.0f, 0.0f);
                glVertex3f(xmax, ymax, zmax);
                glTexCoord2d(1.0f, 0.0f);
                glVertex3f(xmin, ymax, zmax);
                glTexCoord2d(1.0f, 1.0f);
                glVertex3f(xmin, ymax, zmin);
                glTexCoord2d(0.0f, 1.0f);
                glVertex3f(xmax, ymax, zmin);



                 //-------- front 
                //glColor3f(0.796, 0.509, 0.003);
                glTexCoord2d(0.0f, 0.0f);
                glVertex3f(xmax, ymax, zmax);
                glTexCoord2d(1.0f, 0.0f);
                glVertex3f(xmin, ymax, zmax);
                glTexCoord2d(1.0f, 1.0f);
                glVertex3f(xmin, ymin, zmax);
                glTexCoord2d(0.0f, 1.0f);
                glVertex3f(xmax, ymin, zmax);
                //--------- right 

                glTexCoord2d(0.0f, 0.0f);
                glVertex3f(xmax, ymax, zmax);
                glTexCoord2d(1.0f, 0.0f);
                glVertex3f(xmax, ymax, zmin);
                glTexCoord2d(1.0f, 1.0f);
                glVertex3f(xmax, ymin, zmin);
                glTexCoord2d(0.0f, 1.0f);
                glVertex3f(xmax, ymin, zmax);


                //--------- left 
                glTexCoord2d(0.0f, 0.0f);
                glVertex3f(xmin, ymax, zmax);
                glTexCoord2d(1.0f, 0.0f);
                glVertex3f(xmin, ymax, zmin);
                glTexCoord2d(1.0f, 1.0f);
                glVertex3f(xmin, ymin, zmin);
                glTexCoord2d(0.0f, 1.0f);
                glVertex3f(xmin, ymin, zmax);

                //------------ back 
                glTexCoord2d(0.0f, 0.0f);
                glVertex3f(xmax, ymax, zmin);
                glTexCoord2d(1.0f, 0.0f);
                glVertex3f(xmin, ymax, zmin);
                glTexCoord2d(1.0f, 1.0f);
                glVertex3f(xmin, ymin, zmin);
                glTexCoord2d(0.0f, 1.0f);
                glVertex3f(xmax, ymin, zmin);
            }
            mainx += 3;


        }
        mainz += 3;
        mainx = -25.5;

    }
    mainz = -51.0;




    glEnd();   // Done drawing the plat



    glutSwapBuffers();

}
//--------------------- start Screen 
void cover() {
    // glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -25.5);
    glColor3f(0, 0, 0);
    writeStr(-6.0, 6, " WELLCOME IN PAC_MAN GAME ", GLUT_BITMAP_TIMES_ROMAN_24);
    //glColor3f(0.0, 0.0, 0.0);
    glColor3f(option2, option2, 0);
    writeStr(-3.5, 4.0, "START THE GAME", GLUT_BITMAP_HELVETICA_18);
    glColor3f(option1, option1, 0);
    writeStr(-3.5, 3.0, "CLOSE", GLUT_BITMAP_HELVETICA_18);
    //glClearColor(0.211, 0.329, 0.447, 1.0);
    glClearColor(0.0f, 0.8f, 0.8f, 0.0f); // Set background color to black and opaque
    load(4);


    diam_coverx = -0.75;
    glPushMatrix();
    diam_coverz = 15;
    diam_covery = -3;
    glTranslatef(diam_coverx, diam_covery, diam_coverz);
    glRotatef(angle2, 0.0f, 1.0f, 0.0f);   //around y 
    glTranslatef(-1 * diam_coverx, -1 * diam_covery, -1 * diam_coverz);
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
    //glColor3f(1.0f, 0.0f, 0.0f);     // Red
    //top
    //glColor3f(1, 1, 1);
    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz - 1);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz - 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz - 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz + 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz + 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz + 1);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz + 1);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz + 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz + 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz - 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz - 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz - 1);

    //TOP
    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 3, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz - 1);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz - 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 3, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz - 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz + 0.5);
    //1
    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 3, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx + 1, diam_covery + 2, diam_coverz + 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz + 1);
    //2
    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 3, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz + 1);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz + 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 3, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz + 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz - 0.5);

    glTexCoord2d(0.5f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 3, diam_coverz);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(diam_coverx - 1, diam_covery + 2, diam_coverz - 0.5);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(diam_coverx, diam_covery + 2, diam_coverz - 1);


    glEnd();
    glPopMatrix();
    glutSwapBuffers();
    // glPopMatrix();

}
//--------------------- Win Screen
void winScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -25.5);
    glColor3f(0.113, 0.650, 0.047);
    writeStr(-6.0, 6, " CONGRACTLAITON..! YOU WIN ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-6.0, 4.5, " YOUR SCORE :", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-1, 4.5, std::to_string(score), GLUT_BITMAP_TIMES_ROMAN_24);
    //glColor3f(0.1, 0.0, 0.0);
    glColor3f(option1, option1, 0);
    writeStr(-3.5, 3.0, "RE-START THE GAME", GLUT_BITMAP_HELVETICA_18);
    glColor3f(option2, option2, 0);
    writeStr(-3.5,2.0, "CLOSE", GLUT_BITMAP_HELVETICA_18);
    //glClearColor(0.211, 0.329, 0.447, 1.0);
    glClearColor(0.0f, 0.8f, 0.8f, 0.0f); // Set background color to black and opaque


    glutSwapBuffers();
}
//--------------------- Lose Screen
void loseScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0.0f, 0.8f, 0.8f, 0.0f); // Set background color to black and opaque
    //glClearColor(0.211, 0.329, 0.447, 1.0);
    glTranslatef(0, 0, -25.5f);
    glColor3f(1, 0, 0);
    writeStr(-6.0, 6, "OOPS..! YOU LOSE THE GAME", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(option1, option1, 0);
    //glColor3f(1.0, 1.0, 1.0);
    writeStr(-6.0, 4.0, "RE-START THE GAME AGAIN", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(option2, option2, 0);
    writeStr(-6.0, 3.0, "CLOSE", GLUT_BITMAP_TIMES_ROMAN_24);
    glutSwapBuffers();
}
//Swap between Screen
void display() {
    if (chanal == -1) cover();
    else if (chanal == 1) drow();
    else if (chanal == 2) loseScreen();
    else if (chanal == 3) winScreen();
    if (num_Diam == 0) chanal = 3;
    if (chanal != 1) {
        initial_value();
        num_Diam = 8;
        if (chanal != 3)
        {
            score = 0;
        }
        e_mainx = 21.0; e_mainy = -23.5; e_mainz = -37.5;
        e2_mainx = -21.0; e2_mainy = -23.5; e2_mainz = -13.5;
        e3_mainx = -18.0; e3_mainy = -23.5; e3_mainz = -46.5;
        for (int i = 0; i < 8; i++)
        {
            map_dima[i] = 1;
        }
        life = 3;
    }
}
//----------- Timer Funcation
void timer(int value) {
    glutPostRedisplay();
    if (angle2 + 1 == 360)
    {
        angle2 = 0;
    }
    else
        angle2 += 1;

    if (angle1 + 10 == 360)
    {
        angle1 = 0;
    }
    else
        angle1 += 10;
    //--------------------------------- movment of right Side
    if (e_flag == 1)
    {
        e1_angel = 0;
        if (temp + 3 <= -8)
        {
            if (temp + 3 == -10.5)
            {
                if (map_dima[5] == 0)
                {
                    move_z = move_z + 1;
                    temp = temp + 1;
                }
                else
                    e_flag = 0;
            }
            else
            {
                move_z = move_z + 1;
                temp = temp + 1;
            }
        }
        else
            e_flag = 0;
        Distance = sqrtf((temp - p_tempz) * (temp - p_tempz));
        if (Distance <= 3 && p_tempx == e_mainx)
        {
            std::cout << Distance << std::endl;
            initial_value();
            life--;
          
        }
    }
    //-----------

    if (e_flag == 0)
    {
        e1_angel = 180;
        if (temp - 3 >= -43)
        {
            if (temp - 3 == -40.5)
            {
                if (map_dima[3] == 0)
                {
                    move_z = move_z - 1;
                    temp = temp - 1;
                }
                else
                    e_flag = 1;
            }
            else
            {
                move_z = move_z - 1;
                temp = temp - 1;
            }
        }
        else
            e_flag = 1;
        Distance = sqrtf((temp - p_tempz) * (temp - p_tempz));
        if (Distance <= 3 && p_tempx == e_mainx)
        {
            std::cout << Distance << std::endl;
            initial_value();
            life--;
         
        }
    }

    //--------------------------------- movment of left Side
    if (e2_flag == 1)
    {
        e2_angel = 0;
        if (temp2 + 3 <= -8)
        {
            if (temp2 + 3 == -10.5)
            {
                if (map_dima[4] == 0)
                {
                    move2_z = move2_z + 1;
                    temp2 = temp2 + 1;
                }
                else
                    e2_flag = 0;
            }
            else
            {
                move2_z = move2_z + 1;
                temp2 = temp2 + 1;
            }
        }
        else
            e2_flag = 0;
        Distance = sqrtf((temp2 - p_tempz) * (temp2 - p_tempz));
        if (Distance <= 3 && p_tempx == e2_mainx)
        {
            std::cout << Distance << std::endl;
            initial_value();
            life--;
         
        }
    }
    //-----------

    if (e2_flag == 0)
    {
        e2_angel = 180;
        if (temp2 - 3 >= -43.0)
        {
            if (temp2 - 3 == -40.5)
            {
                if (map_dima[2] == 0)
                {
                    move2_z = move2_z - 1;
                    temp2 = temp2 - 1;
                }
                else
                    e2_flag = 1;
            }
            else
            {
                move2_z = move2_z - 1;
                temp2 = temp2 - 1;
            }
        }
        else
            e2_flag = 1;
        Distance = sqrtf((temp2 - p_tempz) * (temp2 - p_tempz));
        if (Distance <= 3 && p_tempx == e2_mainx)
        {
            std::cout << Distance << std::endl;
            initial_value();
            life--;
          
        }
    }

    //--------------------------------- movment of top Side
    if (e3_flag == 1)
    {
        e3_angel = 90;
        if (temp3 + 3 <= 23.5)
        {
            if (temp3 + 3 == 21.0)
            {
                if (map_dima[1] == 0)
                {
                    move_x = move_x + 1.5;
                    temp3 = temp3 + 1.5;
                }
                else
                    e3_flag = 0;
            }
            else
            {
                move_x = move_x + 1.5;
                temp3 = temp3 + 1.5;
            }
        }
        else
            e3_flag = 0;
        Distance = sqrtf((temp3 - p_tempx) * (temp3 - p_tempx));
        if (Distance <= 3 && p_tempz == e3_mainz)
        {
            std::cout << Distance << std::endl;
            initial_value();
            life--;
        
        }
    }
    //-----------

    if (e3_flag == 0)
    {
        e3_angel = 270;
        if (temp3 - 3 >= -23.5)
        {
            if (temp3 - 3 == -21.0)
            {
                if (map_dima[0] == 0)
                {
                    move_x = move_x - 1.5;
                    temp3 = temp3 - 1.5;
                }
                else
                    e3_flag = 1;
            }
            else
            {
                move_x = move_x - 1.5;
                temp3 = temp3 - 1.5;
            }
        }
        else
            e3_flag = 1;
        Distance = sqrtf((temp3 - p_tempx) * (temp3 - p_tempx));

        if (Distance < 3 && p_tempz == e3_mainz)
        {
            std::cout << Distance << std::endl;
            initial_value();
            life--;
        }
    }
    if (life == 0)
        chanal = 2;

    glutTimerFunc(1000 / 60, timer, 0);

}
//-----------SpecialKeyboard Funcation
void Keyboard(unsigned char key, int x, int y) {
    if (key == 13)
    {
        if(chanal!= 1 )
            score = 0;
        //std::cout << "enter pressing " << std::endl;
        if (option1 > option2)
        {
            chanal = 1;

        }
        else
            exit(0);
    }
    if (key == 27)
        exit(0);
    if (key == 48)
        chanal = - 1;
    
}
void specialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        fullScreen = !fullScreen;
        if (fullScreen)
            glutFullScreen();
        else {
            glutPositionWindow(0,25);
            glutReshapeWindow(width_screen, height_screen-66);
        }
    }
    if (key == GLUT_KEY_UP) {
        if (chanal != 1) std::swap(option1, option2);
        if (position_x >= 0 && position_x < 17 && position_z >= 0 && position_z < 17 && !map_arr[position_z - 1][position_x])
        {
            p_angel = 180;
            Pmove_z -= 3;
            p_tempz -= 3;
             //eyez -= 0.5;
            plat_z += 0.5;
             //upz -= 0.5; 
                if (position_z == 4)
                    if (position_x == 1 && map_dima[2])
                    {
                        map_dima[2] = 0;
                        num_Diam--;
                        score += 3000;
                    }

                    else if (position_x == 15 && map_dima[3])
                    {
                        map_dima[3] = 0;
                        num_Diam--;
                        score += 3000;
                    }
            position_z--;
            //std::cout << position_z << "\t" << position_x << std::endl;
        }

    }
    if (key == GLUT_KEY_DOWN) {
        if (chanal != 1) std::swap(option1, option2);
        if (position_x >= 0 && position_x < 17 && position_z >= 0 && position_z < 17 && !map_arr[position_z + 1][position_x])
        {
            p_angel = 0;
            Pmove_z += 3;
            p_tempz += 3;
            //eyez += 0.5;
            plat_z -= 0.5;
           // upz += 0.5; 
                if (position_z == 12)
                    if (position_x == 1 && map_dima[4] )
                    {
                        map_dima[4] = 0;
                        num_Diam--;
                        score += 3000;
                    }
                    else if (position_x == 15 && map_dima[5])
                    {
                        map_dima[5] = 0;
                        num_Diam--;
                        score += 3000;
                    }
            if (position_z == 10)
                if (position_x == 3 && map_dima[6])
                {
                    map_dima[6] = 0;
                    num_Diam--;
                    score += 1000;
                }
                else if (position_x == 13 && map_dima[7])
                {
                    map_dima[7] = 0;
                    num_Diam--;
                    score += 1000;
                }
            position_z++;
            //std::cout << position_z << "\t" << position_x << std::endl;
        }
    }
    if (key == GLUT_KEY_RIGHT) {
        if (position_x >= 0 && position_x < 17 && position_z >= 0 && position_z < 17 && !map_arr[position_z][position_x + 1])
        {
            p_angel = 90;
            Pmove_x += 3;
            p_tempx += 3;
            plat_x -= 0.5;
            //eyex += 0.5;
            //upx += 0.5; 
            if (position_z == 1 && position_x == 14 && map_dima[1])
            {
                map_dima[1] = 0;
                num_Diam--;
                score += 3000;
            }
            position_x++;
            // std::cout << position_z << "\t" << position_x << std::endl;
        }
    }
    if (key == GLUT_KEY_LEFT) {
        if (position_x >= 0 && position_x < 17 && position_z >= 0 && position_z < 17 && !map_arr[position_z][position_x - 1])
        {
            p_angel = 270;
            Pmove_x -= 3;
            p_tempx -= 3;
            plat_x += 0.5;
            //eyex -= 0.5;
            //upx -= 0.5; 
            if (position_z == 1 && position_x == 2 && map_dima[0])
            {
                map_dima[0] = 0;
                num_Diam--;
                score += 3000;
            }
            position_x--;
            // std::cout << position_z << "\t" << position_x << std::endl;
        }
    }
}
//----------- Mouse Funcation
void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        flag = 0;
        angle += 1;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        flag = 1;
        angle -= 1;

    }

}
//----------- Load Funcation
void load(int imgnum) {
    if (imgnum == 1) {

        data = stbi_load("F:\wall.bmp", &width, &height, &nrChannels, 0);
        check(data);
    }
    else if (imgnum == 2) {

        data = stbi_load("F:\Boking.jpg", &width, &height, &nrChannels, 0);
     check(data);
   }
    //else if (imgnum == 3) {
    //    data = stbi_load("F:\Boking.jpg", &width, &height, &nrChannels, 0);
    //    check(data);
    //}
    else if (imgnum == 4) {

        data = stbi_load("F:\diamond1.jpg", &width, &height, &nrChannels, 0);
        check(data);
    }
    else if (imgnum == 5) {

        data = stbi_load("F:\Mon.jpg", &width, &height, &nrChannels, 0);
        check(data);
    }

    else if (imgnum == 6) {

        data = stbi_load("F:\image5.jpg", &width, &height, &nrChannels, 0);
        check(data);
    }
   
 

}
//----------- Check Funcation
void check(unsigned char* data) {
    if (data)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        //std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
//----------- ReShape Funcation
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window 
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(50.0f, aspect, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);

}
//----------- Main Funcation
int main(int argc, char** argv) {

    width_screen = GetSystemMetrics(SM_CXSCREEN);
    height_screen = GetSystemMetrics(SM_CYSCREEN);
    std::cout << width_screen << "\t" << height_screen << std::endl;
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Enable double buffered mode
    //glutInitWindowSize(640, 480);   // Set the window's initial width & height
    //glutInitWindowPosition(0, 25); // Position the window's initial top-left corner

    //glutInitWindowSize(width_screen, height_screen - 66);
    glutCreateWindow("PAC_MAN GAME");          // Create window with the given title
    glutFullScreen();
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();           // Our own OpenGL initialization
    glutMouseFunc(mouse);
    glutSpecialFunc(specialKeyboard);
    glutTimerFunc(1000, timer, 0);  // First timer call immediately [NEW]

    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
