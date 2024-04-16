#include <GL/glut.h>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;


double a = 1000;
double normalize_time = 0;
double jumpheightmax = 280;
double jumppos = 0;
double current_jumppos = 0;
bool jumpstate = false;

double normalize_jumpscale_time;
double scale = 1;
double max_scale = 1.5;
double min_scale = 1;
bool scalling_up = false;
double current_jumpscale;

// ini untuk animasi garis tanah
double b = 0, c = 1150, d = 0, e = 2000;

double f = 0, g = 1000;
double h = 0, i = 1000;

double j = 1000;

double c1 = 100, c2 = 44, c3 = 30;

double min_opacity_c1 = 15;
double min_opacity_c2 = 5;
double min_opacity_c3 = 8;

double max_opacity_c1 = 100;
double max_opacity_c2 = 44;
double max_opacity_c3 = 30;

double k = 0;
bool up = true;

bool opacity_c1 = true, opacity_c2 = true, opacity_c3 = true;

bool keyispressed = false;

int score = 0;
int score_counter;

bool display_menu_screen_state = false;
bool gameisbeingplayed = false;

double opacity_start_letter = 255;
double min_opacity_start_letter = 0;
double max_opacity_start_letter = 255;
bool opacity_on = true;

int scenario1, scenario2, scenario3;

double tampung = 1000, tampung2 = 2000, tampung3 = 1500;
double tampung_a, tampung_b = 1000;
double tampung2_a, tampung2_b = 1700;

bool crash = false;

bool first_state = true, first_state2 = true, first_state3 = true;
//bool loop_play = false, loop_play2 = false, loop_play3 = false;

bool scenario1_on_off = true, scenario2_on_off = true, scenario3_on_off = true;

int scenario_mode3;
//int scenario_mode1, scenario_mode2;

bool game_over_on = false;

int loading_counter;

int l = 150;

void reset_display(){

 a = 1000;
 normalize_time = 0;
 jumppos = 0;
 current_jumppos = 0;
 jumpstate = false;
 scale = 1;
 max_scale = 1.5;
 min_scale = 1;
 scalling_up = false;
 b = 0, c = 1150, d = 0, e = 2000;
 f = 0, g = 1000;
 h = 0, i = 1000;
 j = 1000;
 c1 = 100, c2 = 44, c3 = 30;
 k = 0;
 up = true;

 opacity_c1 = true, opacity_c2 = true, opacity_c3 = true;
 keyispressed = false;

 score = 0;
 score_counter = 0;

 display_menu_screen_state = false;
 gameisbeingplayed = false;

 opacity_start_letter = 255;

 opacity_on = true;

 crash = false;

 tampung = 1000, tampung2 = 2000, tampung3 = 1500;

 first_state = true, first_state2 = true, first_state3  =true;
 //loop_play = false, loop_play2 = true;

 scenario1_on_off = true, scenario2_on_off = true, scenario3_on_off = true;

    game_over_on = false;

    l = 150;
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(5, timer, 0);
}

double eased_function() {
    double eased_value = normalize_time * (2 - normalize_time);
    return eased_value;
}

double jump_scale_eased_function() {
    double eased_value = normalize_jumpscale_time * normalize_jumpscale_time*normalize_jumpscale_time;
    return eased_value;
}

void layar_hitam(){

    glEnable(GL_BLEND); // Aktifkan blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setel fungsi blending

    glBegin(GL_POLYGON);
    glColor4ub(0,0,0, 150);
    glVertex2f(-500, 300);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, 300);
    glEnd();

}

void layar_hitam2(){

    glEnable(GL_BLEND); // Aktifkan blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setel fungsi blending

    glBegin(GL_POLYGON);
    glColor4ub(0,0,0, 20);
    glVertex2f(-500, 300);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, 300);
    glEnd();

}

void game_over_screen(){

    layar_hitam2();

    game_over_on = true;

    glColor3ub(255, 255, 255);
    glRasterPos2f(-55, 0); // Koordinat posisi teks
    stringstream ss;
    ss << "Final Score: " << score; // Teks yang akan ditampilkan
    string startText = ss.str(); // Konversi stringstream menjadi string

    for (int i = 0; i < startText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, startText[i]);
    }

    glRasterPos2f(-60, 30);
    string gameover = "Game Over!";
    for (int i = 0; i < gameover.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameover[i]);
    }

    glRasterPos2f(-70, -30);
    string pressy = "Press 'y' to Play Again";
    for (int i = 0; i < pressy.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, pressy[i]);
    }

    glRasterPos2f(-66, -60);
    string exitgame = "Press 'x' to Exit Game";
    for (int i = 0; i < exitgame.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, exitgame[i]);
    }
    glFlush();
//   glutSwapBuffers();

}

void crash_detection() {
    double playerx =  0 - 325;
    double playery = current_jumppos - 140;

    double logx = tampung - 307.5;
    double logy = 0 - 125;

    double jarak = sqrt(pow(logx - playerx, 2) + pow(logy - playery, 2));

    double jarak_min = 40;

    if (jarak <= jarak_min) {
        glutDisplayFunc(game_over_screen);
        //exit(0);
        crash = true;
    }
    else{
        score_counter++;
        if(score_counter >= 50){
            score++;
            score_counter = 0;
        }

    }

    double playerx2 =  0 - 325;
    double playery2 = current_jumppos - 140;

    double log2x = tampung - 307.5;
    double log2y = 0 - 100;

    double jarak2 = sqrt(pow(log2x - playerx2, 2) + pow(log2y - playery2, 2));

    double jarak_min2 = 50;

    if (jarak2 <= jarak_min2) {
        glutDisplayFunc(game_over_screen);
       // exit(0);
       crash = true;
    }

     else{
        score_counter++;
        if(score_counter >= 50){
            score++;
            score_counter = 0;
        }

    }
}

void crash_detection2(){

    double playerx =  0 - 325;
    double playery = current_jumppos - 140;

    double logx = tampung2 - 307.5;
    double logy = 0 - 125;

    double jarak = sqrt(pow(logx - playerx, 2) + pow(logy - playery, 2));

    double jarak_min = 40;

    if (jarak <= jarak_min) {
        glutDisplayFunc(game_over_screen);
        //exit(0);
        crash = true;
    }
    else{
        score_counter++;
        if(score_counter >= 50){
            score++;
            score_counter = 0;
        }

    }

    double playerx2 =  0 - 325;
    double playery2 = current_jumppos - 140;

    double log2x = tampung2 - 307.5;
    double log2y = 0 - 100;

    double jarak2 = sqrt(pow(log2x - playerx2, 2) + pow(log2y - playery2, 2));

    double jarak_min2 = 50;

    if (jarak2 <= jarak_min2) {
        glutDisplayFunc(game_over_screen);
       // exit(0);
       crash = true;
    }

     else{
        score_counter++;
        if(score_counter >= 50){
            score++;
            score_counter = 0;
        }

    }

}


void crash_detection3(){

    double playerx =  0 - 325;
    double playery = current_jumppos - 140;

    double logx = tampung3 - 307.5;
    double logy = 0 - 125;

    double jarak = sqrt(pow(logx - playerx, 2) + pow(logy - playery, 2));

    double jarak_min = 40;

    if (jarak <= jarak_min) {
        glutDisplayFunc(game_over_screen);
        //exit(0);
        crash = true;
    }
    else{
        score_counter++;
        if(score_counter >= 50){
            score++;
            score_counter = 0;
        }

    }

    double playerx2 =  0 - 325;
    double playery2 = current_jumppos - 140;

    double log2x = tampung3 - 307.5;
    double log2y = 0 - 100;

    double jarak2 = sqrt(pow(log2x - playerx2, 2) + pow(log2y - playery2, 2));

    double jarak_min2 = 50;

    if (jarak2 <= jarak_min2) {
        glutDisplayFunc(game_over_screen);
       // exit(0);
       crash = true;
    }

     else{
        score_counter++;
        if(score_counter >= 50){
            score++;
            score_counter = 0;
        }

    }

}


void platform(){
    //tanah atas
    glBegin(GL_POLYGON);
    glColor3ub(133, 86, 40);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, -155);
    glVertex2f(-500, -155);
    glEnd();

    //tanah bawah
    glBegin(GL_POLYGON);
    glColor3ub(89, 42, 16);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, -230);
    glVertex2f(-500, -230);
    glEnd();

    //tanah hijau
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(222, 214, 75);
    glVertex2f(500, -155);
    glVertex2f(-500, -155);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(167, 169, 68);
    glVertex2f(500, -162);
    glVertex2f(-500, -162);
    glEnd();

    //garis vertikal1
    glLineWidth(8.0);
    glBegin(GL_LINES);
    glColor3ub(104, 64, 27);
    glVertex2f(500, -169);
    glVertex2f(-500, -169);
    glEnd();

    //garis vertikal2
    glLineWidth(7.0);
    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(500, -230);
    glVertex2f(-500, -230);
    glEnd();
}

void background_scenery(){

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-500, -150);
    glVertex2f(-250, -150);
    glVertex2f(-250, 0);
    glVertex2f(-500, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-250, -150);
    glVertex2f(-250, -70);
    glVertex2f(-60, -70);
    glVertex2f(-60, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-60, -100);
    glVertex2f(-60, -150);
    glVertex2f(275, -150);
    glVertex2f(275, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(275, -150);
    glVertex2f(275, -70);
    glVertex2f(500, -70);
    glVertex2f(500, -150);
    glEnd();

    //-------bunga1--------
    glLineWidth(8.0);

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(375, -70);
    glVertex2f(375, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(365, -65);
    glVertex2f(365, -60);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(395, -70);
    glVertex2f(395, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(405, -65);
    glVertex2f(405, -60);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(385, -90);
    glVertex2f(385, -55);
    glEnd();

    //--------bunga1------


    //-------bunga2--------
    glLineWidth(8.0);

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-150, -70);
    glVertex2f(-150, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-140, -65);
    glVertex2f(-140, -60);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-170, -70);
    glVertex2f(-170, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-180, -65);
    glVertex2f(-180, -60);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-160, -90);
    glVertex2f(-160, -55);
    glEnd();

    //--------bunga2------

    //------tanaman kecil1-----

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(230, -92);
    glVertex2f(230, -100);
    glEnd();

    glLineWidth(14.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(230, -92);
    glVertex2f(230, -84);
    glEnd();

    //----tanaman kecil1-----

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(200, -92);
    glVertex2f(200, -100);
    glEnd();

    glLineWidth(14.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(200, -92);
    glVertex2f(200, -84);
    glEnd();

    //----tanaman kecil1-----


    //-------rumput besar--------
    glLineWidth(11.0);

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(40, -100);
    glVertex2f(40, -95);
    glEnd();

    glLineWidth(11.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(35, -95);
    glVertex2f(35, -90);
    glEnd();

    glLineWidth(11.0);
     glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(60, -100);
    glVertex2f(60, -90);
    glEnd();

    glLineWidth(11.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(65, -90);
    glVertex2f(65, -80);
    glEnd();

    //--------rumput besar------
}

void background_scenery_lanjutan(){
    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-500, -150);
    glVertex2f(-250, -150);
    glVertex2f(-250, 0);
    glVertex2f(-500, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-250, -150);
    glVertex2f(-250, -70);
    glVertex2f(-60, -70);
    glVertex2f(-60, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-60, -100);
    glVertex2f(-60, -150);
    glVertex2f(275, -150);
    glVertex2f(275, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(275, -150);
    glVertex2f(275, -70);
    glVertex2f(510, -70);
    glVertex2f(510, -150);
    glEnd();

     //------tanaman kecil2-----



    //----tanaman kecil2-----


    //------tanaman kecil2-----

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(200, -92);
    glVertex2f(200, -100);
    glEnd();

    glLineWidth(18.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(200, -92);
    glVertex2f(200, -84);
    glEnd();

    //----tanaman kecil2-----


     //------tanaman kecil3-----

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(350, -70);
    glVertex2f(350, -62);
    glEnd();

    glLineWidth(14.0);
    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(350, -62);
    glVertex2f(350, -54);
    glEnd();

    //----tanaman kecil3-----




    //-------bunga1--------
    glLineWidth(8.0);

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(450, -70);
    glVertex2f(450, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(440, -65);
    glVertex2f(440, -60);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(470, -70);
    glVertex2f(470, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(480, -65);
    glVertex2f(480, -60);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(460, -90);
    glVertex2f(460, -55);
    glEnd();

    //--------bunga1------



    //-------bunga2--------
    glLineWidth(8.0);

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(0, -100);
    glVertex2f(0, -95);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(10, -95);
    glVertex2f(10, -90);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-20, -100);
    glVertex2f(-20, -95);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-30, -95);
    glVertex2f(-30, -90);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-10, -100);
    glVertex2f(-10, -85);
    glEnd();

    //--------bunga2------



    //-------rumput besar--------
    glLineWidth(11.0);

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-160, -70);
    glVertex2f(-160, -65);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-155, -65);
    glVertex2f(-155, -60);
    glEnd();


     glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-180, -70);
    glVertex2f(-180, -68);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(43, 90, 124);
    glVertex2f(-185, -68);
    glVertex2f(-185, -61);
    glEnd();

    //--------rumput besar------

}

void pohon_bg_scenery(){



    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-300, 0);
    glVertex2f(-350, 0);
    glVertex2f(-350, 130);
    glVertex2f(-300, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-450, 130);
    glVertex2f(-200, 130);
    glVertex2f(-200, 220);
    glVertex2f(-450, 220);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-400, 130);
    glVertex2f(-250, 130);
    glVertex2f(-250, 270);
    glVertex2f(-400, 270);
    glEnd();

    //garis cahaya

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-450, 130);
    glVertex2f(-450, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-400, 220);
    glVertex2f(-400, 270);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-450, 220);
    glVertex2f(-350, 220);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-400, 270);
    glVertex2f(-250, 270);
    glEnd();

    //garis cahaya

    //pohon 2
    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(100, -110);
    glVertex2f(150, -110);
    glVertex2f(150, 10);
    glVertex2f(100, 10);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(250, 10);
    glVertex2f(0, 10);
    glVertex2f(0, 100);
    glVertex2f(250, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(50, 10);
    glVertex2f(200, 10);
    glVertex2f(200, 150);
    glVertex2f(50, 150);
    glEnd();

    //garis cahaya2
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(0, 10);
    glVertex2f(0, 100);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(0, 100);
    glVertex2f(100, 100);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(50, 100);
    glVertex2f(50, 150);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(50, 150);
    glVertex2f(200, 150);
    glEnd();

    //garis cahaya2
}

void pohon_bg_scenery_lanjutan(){
    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-300, 0);
    glVertex2f(-350, 0);
    glVertex2f(-350, 110);
    glVertex2f(-300, 110);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-450, 110);
    glVertex2f(-200, 110);
    glVertex2f(-200, 200);
    glVertex2f(-450, 200);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(-400, 110);
    glVertex2f(-250, 110);
    glVertex2f(-250, 250);
    glVertex2f(-400, 250);
    glEnd();


     //garis cahaya

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-450, 110);
    glVertex2f(-450, 200);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-400, 200);
    glVertex2f(-400, 250);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-450, 200);
    glVertex2f(-350, 200);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(-400, 250);
    glVertex2f(-250, 250);
    glEnd();

    //garis cahaya

    //pohon 2
    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(100, -110);
    glVertex2f(150, -110);
    glVertex2f(150, 50);
    glVertex2f(100, 50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(250, 50);
    glVertex2f(0, 50);
    glVertex2f(0, 140);
    glVertex2f(250, 140);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(43, 90, 124);
    glVertex2f(50, 50);
    glVertex2f(200, 50);
    glVertex2f(200, 190);
    glVertex2f(50, 190);
    glEnd();

    //garis cahaya2
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(0, 50);
    glVertex2f(0, 140);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(50, 140);
    glVertex2f(50, 190);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(0, 140);
    glVertex2f(100, 140);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(50, 190);
    glVertex2f(200, 190);
    glEnd();

    //garis cahaya2


}

void garis_tanah(){

    glLineWidth(7.0);
    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-415, -150);
    glVertex2f(-415, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-320, -150);
    glVertex2f(-320, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-225, -150);
    glVertex2f(-225, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-130, -150);
    glVertex2f(-130, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-35, -150);
    glVertex2f(-35, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(65, -150);
    glVertex2f(65, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(165, -150);
    glVertex2f(165, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(265, -150);
    glVertex2f(265, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(365, -150);
    glVertex2f(365, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(465, -150);
    glVertex2f(465, -300);
    glEnd();

}

void garis_tanah2(){

    glLineWidth(7.0);
    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-415, -150);
    glVertex2f(-415, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-320, -150);
    glVertex2f(-320, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-225, -150);
    glVertex2f(-225, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-130, -150);
    glVertex2f(-130, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(-35, -150);
    glVertex2f(-35, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(65, -150);
    glVertex2f(65, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(165, -150);
    glVertex2f(165, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(265, -150);
    glVertex2f(265, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(365, -150);
    glVertex2f(365, -300);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(79, 34, 0);
    glVertex2f(465, -150);
    glVertex2f(465, -300);
    glEnd();

}

void slime() {
    glBegin(GL_POLYGON);
    glColor3ub(52, 172, 214);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 241, 252);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -105);
    glVertex2f(-300, -105);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 241, 252);
    glVertex2f(-300, -100);
    glVertex2f(-305, -100);
    glVertex2f(-305, -150);
    glVertex2f(-300, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(53, 136, 211);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-340, -150);
    glVertex2f(-340, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(133, 206, 224);
    glVertex2f(-350, -100);
    glVertex2f(-350, -105);
    glVertex2f(-340, -105);
    glVertex2f(-340, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 43, 68);
    glVertex2f(-325, -115);
    glVertex2f(-330, -115);
    glVertex2f(-330, -127);
    glVertex2f(-325, -127);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 43, 68);
    glVertex2f(-313, -115);
    glVertex2f(-318, -115);
    glVertex2f(-318, -127);
    glVertex2f(-313, -127);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 43, 68);
    glVertex2f(-319, -133);
    glVertex2f(-324, -133);
    glVertex2f(-324, -138);
    glVertex2f(-319, -138);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);

    glColor3ub(38, 43, 68);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();
}

void log() {

    glBegin(GL_POLYGON);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3ub(147, 108, 53);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-340, -110);
    glVertex2f(-310, -110);
    glVertex2f(-310, -140);
    glVertex2f(-340, -140);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-330, -120);
    glVertex2f(-320, -120);
    glVertex2f(-320, -130);
    glVertex2f(-330, -130);
    glEnd();
}

void logv2() {

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3ub(147, 108, 53);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-340, -110);
    glVertex2f(-310, -110);
    glVertex2f(-310, -140);
    glVertex2f(-340, -140);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-330, -120);
    glVertex2f(-320, -120);
    glVertex2f(-320, -130);
    glVertex2f(-330, -130);
    glEnd();
}

void log2() {

    //kayu atas
    glBegin(GL_POLYGON);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-265, -100);
    glEnd();

    //kayu atas
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-265, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();


    //kayu2
    glBegin(GL_POLYGON);
    glColor3ub(147, 108, 53);
    glVertex2f(-300, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-300, -100);
    glEnd();

    //kayu2
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-300, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-300, -100);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3ub(147, 108, 53);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();


    //kayu2
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-340, -60);
    glVertex2f(-310, -60);
    glVertex2f(-310, -90);
    glVertex2f(-340, -90);
    glEnd();

    //kayu2
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-330, -70);
    glVertex2f(-320, -70);
    glVertex2f(-320, -80);
    glVertex2f(-330, -80);
    glEnd();



    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-340, -110);
    glVertex2f(-310, -110);
    glVertex2f(-310, -140);
    glVertex2f(-340, -140);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-330, -120);
    glVertex2f(-320, -120);
    glVertex2f(-320, -130);
    glVertex2f(-330, -130);
    glEnd();
}


void log3() {

    //kayu atas
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-265, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-265, -100);
    glEnd();

    //kayu atas
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-265, -100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-265, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-265, -150);
    glEnd();


    //kayu2
    glBegin(GL_POLYGON);
    glColor3ub(147, 108, 53);
    glVertex2f(-300, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-300, -100);
    glEnd();

    //kayu2
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-300, -50);
    glVertex2f(-350, -50);
    glVertex2f(-350, -100);
    glVertex2f(-300, -100);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3ub(147, 108, 53);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-300, -100);
    glVertex2f(-350, -100);
    glVertex2f(-350, -150);
    glVertex2f(-300, -150);
    glEnd();


    //kayu2
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-340, -60);
    glVertex2f(-310, -60);
    glVertex2f(-310, -90);
    glVertex2f(-340, -90);
    glEnd();

    //kayu2
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-330, -70);
    glVertex2f(-320, -70);
    glVertex2f(-320, -80);
    glVertex2f(-330, -80);
    glEnd();



    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-340, -110);
    glVertex2f(-310, -110);
    glVertex2f(-310, -140);
    glVertex2f(-340, -140);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3ub(78, 34, 0);
    glVertex2f(-330, -120);
    glVertex2f(-320, -120);
    glVertex2f(-320, -130);
    glVertex2f(-330, -130);
    glEnd();
}

void background(){

    glBegin(GL_POLYGON);
    glColor3ub(168, 203, 199);
    glVertex2f(-500, 300);
    glVertex2f(500, 300);
    glVertex2f(500, -300);
    glVertex2f(-500, -300);
    glEnd();
}

void background_gradient(){

    glEnable(GL_BLEND); // Aktifkan blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setel fungsi blending

    glBegin(GL_POLYGON);
    glColor4ub(249, 237, 174, 150);
    glVertex2f(-500, 300);
    glColor4ub(168, 203, 199, 100);
    glVertex2f(50, 300);
    glVertex2f(50, -300);
    glColor4ub(249, 237, 174, 100);
    glVertex2f(-500, -300);
    glEnd();
}

void cahaya(){

    glEnable(GL_BLEND); // Aktifkan blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setel fungsi blending

    glBegin(GL_POLYGON);
    glColor4ub(43, 90, 124, c1);
    glVertex2f(-310, 300);
    glVertex2f(-170, 300);
    glVertex2f(70, -150);
    glVertex2f(-70, -150);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(43, 90, 124, c2);
    glVertex2f(-90, 300);
    glVertex2f(-40, 300);
    glVertex2f(200, -150);
    glVertex2f(150, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(43, 90, 124, c3);
    glVertex2f(-480, 300);
    glVertex2f(-530, 300);
    glVertex2f(-255, -150);
    glVertex2f(-205, -150);
    glEnd();

}

void pohon_foreground(){

    glLineWidth(20.0);

    //rumput 1
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-350, -190);
    glVertex2f(-350, -165);
    glEnd();
    //rumput 1
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-360, -165);
    glVertex2f(-360, -140);
    glEnd();

    //rumput 2
     glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-320, -190);
    glVertex2f(-320, -165);
    glEnd();
    //rumput2
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-310, -165);
    glVertex2f(-310, -140);
    glEnd();

    //rumput2
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-300, -140);
    glVertex2f(-300, -115);
    glEnd();


    //-------bunga1--------

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(450, -190);
    glVertex2f(450, -180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(440, -180);
    glVertex2f(440, -170);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(490, -190);
    glVertex2f(490, -180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -180);
    glVertex2f(500, -170);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(470, -190);
    glVertex2f(470, -150);
    glEnd();

    //--------bunga1------





    //-------bunga2--------
  //  glLineWidth(15.0);

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(130, -230);
    glVertex2f(130, -220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(120, -220);
    glVertex2f(120, -210);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(170, -230);
    glVertex2f(170, -220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(180, -220);
    glVertex2f(180, -210);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(150, -230);
    glVertex2f(150, -190);
    glEnd();

    //--------bunga2------


    //------rumput kecil1------
    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-200, -240);
    glVertex2f(-200, -235);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-170, -240);
    glVertex2f(-170, -230);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-160, -230);
    glVertex2f(-160, -220);
    glEnd();

    //------rumput kecil1------


    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -230);
    glVertex2f(100, -230);
    glVertex2f(100, -300);
    glVertex2f(500, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -190);
    glVertex2f(200, -190);
    glVertex2f(200, -230);
    glVertex2f(500, -230);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -260);
    glVertex2f(-250, -260);
    glVertex2f(-250, -300);
    glVertex2f(500, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(-250, -190);
    glVertex2f(-250, -300);
    glVertex2f(-520, -300);
    glVertex2f(-520, -190);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(-250, -240);
    glVertex2f(-250, -300);
    glVertex2f(-100, -300);
    glVertex2f(-100, -240);
    glEnd();

    //batang pohon
    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(360, 30);
    glVertex2f(275, 30);
    glVertex2f(275, -190);
    glVertex2f(360, -190);
    glEnd();

    //daun
    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(125, 30);
    glVertex2f(515, 30);
    glVertex2f(515, 150);
    glVertex2f(125, 150);
    glEnd();

    //daun
    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(450, 130);
    glVertex2f(200, 130);
    glVertex2f(200, 230);
    glVertex2f(450, 230);
    glEnd();

    //garis cahaya
   // glLineWidth(5.0);
   // glBegin(GL_LINES);
   // glColor3ub(249, 255, 164);
   // glVertex2f(125, 30);
   // glVertex2f(125, 150);
  //  glEnd();

   // glLineWidth(5.0);
   // glBegin(GL_LINES);
   // glColor3ub(249, 255, 164);
   // glVertex2f(125, 150);
   // glVertex2f(250, 150);
   // glEnd();

 //   glLineWidth(5.0);
 //   glBegin(GL_LINES);
 //   glColor3ub(249, 255, 164);
 //   glVertex2f(200, 150);
 //   glVertex2f(200, 230);
 //   glEnd();

 //   glLineWidth(5.0);
 //   glBegin(GL_LINES);
  //  glColor3ub(249, 255, 164);
 //   glVertex2f(200, 230);
 //   glVertex2f(450, 230);
 //   glEnd();

    //garis cahaya

    //------tanaman kecil2-----

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-130, -240);
    glVertex2f(-130, -210);
    glEnd();

    glLineWidth(50.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-130, -210);
    glVertex2f(-130, -190);
    glEnd();

    //----tanaman kecil2-----
}

void pohon_foreground_lanjutan(){

    //----tanaman kecil1-----
    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-200, -240);
    glVertex2f(-200, -185);
    glEnd();

    glLineWidth(70.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-200, -185);
    glVertex2f(-200, -140);
    glEnd();
    //-------tanaman kecil1------

    //------tanaman kecil2-----

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-130, -240);
    glVertex2f(-130, -210);
    glEnd();

    glLineWidth(50.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-130, -210);
    glVertex2f(-130, -190);
    glEnd();

    //----tanaman kecil2-----

    //------rumput kecil1------
    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-400, -210);
    glVertex2f(-400, -185);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-370, -210);
    glVertex2f(-370, -185);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(-360, -185);
    glVertex2f(-360, -180);
    glEnd();

    //------rumput kecil1------


    //------rumput kecil2------
    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(430, -210);
    glVertex2f(430, -185);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(400, -210);
    glVertex2f(400, -185);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(390, -185);
    glVertex2f(390, -180);
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(22, 36, 53);
    glVertex2f(460, -210);
    glVertex2f(460, -185);
    glEnd();

    //------rumput kecil2------

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -230);
    glVertex2f(100, -230);
    glVertex2f(100, -300);
    glVertex2f(500, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -190);
    glVertex2f(200, -190);
    glVertex2f(200, -230);
    glVertex2f(500, -230);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(500, -260);
    glVertex2f(-250, -260);
    glVertex2f(-250, -300);
    glVertex2f(500, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(-250, -190);
    glVertex2f(-250, -300);
    glVertex2f(-500, -300);
    glVertex2f(-500, -190);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(-250, -240);
    glVertex2f(-250, -300);
    glVertex2f(-100, -300);
    glVertex2f(-100, -240);
    glEnd();

    //batang pohon
    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(360, 70);
    glVertex2f(275, 70);
    glVertex2f(275, -190);
    glVertex2f(360, -190);
    glEnd();

    //daun
    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(125, 70);
    glVertex2f(515, 70);
    glVertex2f(515, 190);
    glVertex2f(125, 190);
    glEnd();

    //daun
    glBegin(GL_POLYGON);
    glColor3ub(22, 36, 53);
    glVertex2f(450, 170);
    glVertex2f(200, 170);
    glVertex2f(200, 270);
    glVertex2f(450, 270);
    glEnd();

   /* //garis cahaya
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(125, 70);
    glVertex2f(125, 190);
    glEnd();

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(125, 190);
    glVertex2f(250, 190);
    glEnd();

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(200, 190);
    glVertex2f(200, 270);
    glEnd();

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3ub(249, 255, 164);
    glVertex2f(200, 270);
    glVertex2f(450, 270);
    glEnd();*/

    //garis cahaya
}

void bg_scenery2(){

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(325, -150);
    glVertex2f(500, -150);
    glVertex2f(500, 50);
    glVertex2f(325, 50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(325, -170);
    glVertex2f(325, -20);
    glVertex2f(150, -20);
    glVertex2f(150, -170);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(150, -125);
    glVertex2f(150, -50);
    glVertex2f(-250, -50);
    glVertex2f(-250, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-250, -75);
    glVertex2f(-250, -125);
    glVertex2f(-450, -125);
    glVertex2f(-450, -75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-250, -75);
    glVertex2f(-250, -125);
    glVertex2f(-550, -125);
    glVertex2f(-550, -75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-350, -125);
    glVertex2f(-550, -25);
    glVertex2f(-550, -25);
    glVertex2f(-350, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-350, -125);
    glVertex2f(-350, -25);
    glVertex2f(-550, -25);
    glVertex2f(-550, -125);
    glEnd();

    //----bunga1----

    glLineWidth(6.0);
    glBegin(GL_LINES);
    glVertex2f(80,-50);
    glVertex2f(80,-40);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(87,-50);
    glVertex2f(87,-46);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(90,-46);
    glVertex2f(90,-42);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(73,-50);
    glVertex2f(73,-46);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(70,-46);
    glVertex2f(70,-42);
    glEnd();

    //----bunga1-----


    //----runput2----

    glBegin(GL_LINES);
    glVertex2f(-43,-50);
    glVertex2f(-43,-46);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-40,-46);
    glVertex2f(-40,-42);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-52,-50);
    glVertex2f(-52,-46);
    glEnd();

     glBegin(GL_LINES);
    glVertex2f(-55,-46);
    glVertex2f(-55,-42);
    glEnd();


    //----rumput2----


     //----runput2----

    glBegin(GL_LINES);
    glVertex2f(-293,-75);
    glVertex2f(-293,-71);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-290,-71);
    glVertex2f(-290,-67);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-302,-75);
    glVertex2f(-302,-71);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-305,-71);
    glVertex2f(-305,-67);
    glEnd();


    //----rumput2----

    //----tanaman kecil----
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(385, 50);
    glVertex2f(385, 57);
    glEnd();

    glLineWidth(9.0);
    glBegin(GL_LINES);
    glVertex2f(385, 57);
    glVertex2f(385, 62);
    glEnd();



    //----tanamnan kecil-----



}

void bg_scenery2_lanjutan(){

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(325, -150);
    glVertex2f(500, -150);
    glVertex2f(500, 50);
    glVertex2f(325, 50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(325, -170);
    glVertex2f(325, -20);
    glVertex2f(150, -20);
    glVertex2f(150, -170);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(150, -125);
    glVertex2f(150, -50);
    glVertex2f(-250, -50);
    glVertex2f(-250, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-250, -75);
    glVertex2f(-250, -125);
    glVertex2f(-450, -125);
    glVertex2f(-450, -75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-250, -75);
    glVertex2f(-250, -125);
    glVertex2f(-450, -125);
    glVertex2f(-450, -75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-350, -125);
    glVertex2f(-350, -25);
    glVertex2f(-550, -25);
    glVertex2f(-550, -125);
    glEnd();

    //----bunga1----

    glLineWidth(6.0);
    glBegin(GL_LINES);
    glVertex2f(80,-50);
    glVertex2f(80,-40);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(87,-50);
    glVertex2f(87,-46);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(90,-46);
    glVertex2f(90,-42);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(73,-50);
    glVertex2f(73,-46);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(70,-46);
    glVertex2f(70,-42);
    glEnd();

    //----bunga1-----

    //----runput----

    glBegin(GL_LINES);
    glVertex2f(-73,-50);
    glVertex2f(-73,-46);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-70,-46);
    glVertex2f(-70,-42);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-82,-50);
    glVertex2f(-82,-46);
    glEnd();

     glBegin(GL_LINES);
    glVertex2f(-85,-46);
    glVertex2f(-85,-42);
    glEnd();


    //----rumput----


     //----runput2----

    glBegin(GL_LINES);
    glVertex2f(-293,-75);
    glVertex2f(-293,-71);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-290,-71);
    glVertex2f(-290,-67);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-302,-75);
    glVertex2f(-302,-71);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-305,-71);
    glVertex2f(-305,-67);
    glEnd();


    //----rumput2----

     //----runput4----

    glBegin(GL_LINES);
    glVertex2f(-443,-26);
    glVertex2f(-443,-22);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-440,-22);
    glVertex2f(-440,-18);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-452,-26);
    glVertex2f(-452,-22);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-455,-22);
    glVertex2f(-455,-18);
    glEnd();


    //----rumput4----

     //----tanaman kecil----
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(245,-20);
    glVertex2f(245, -15);
    glEnd();

    glLineWidth(8.0);
    glBegin(GL_LINES);
    glVertex2f(245,-15);
    glVertex2f(245, -11);
    glEnd();

    //----tanamnan kecil-----


}

void pohon_bg_scenery2(){

    //pohon 1
    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(215, -20);
    glVertex2f(180, -20);
    glVertex2f(180, 90);
    glVertex2f(215, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(100, 50);
    glVertex2f(300, 50);
    glVertex2f(300, 130);
    glVertex2f(100, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(140, 50);
    glVertex2f(260, 50);
    glVertex2f(260, 170);
    glVertex2f(140, 170);
    glEnd();

    //garis cahaya

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(100, 50);
    glVertex2f(100, 130);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(100, 130);
    glVertex2f(175, 130);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(140, 130);
    glVertex2f(140, 170);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(140, 130);
    glVertex2f(140, 170);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(140, 170);
    glVertex2f(260, 170);
    glEnd();
    //garis cahaya

    //pohon 2

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(445, 30);
    glVertex2f(410, 30);
    glVertex2f(410, 140);
    glVertex2f(445, 140);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(330, 100);
    glVertex2f(530, 100);
    glVertex2f(530, 180);
    glVertex2f(330, 180);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(370, 100);
    glVertex2f(490, 100);
    glVertex2f(490, 220);
    glVertex2f(370, 220);
    glEnd();

    //garis cahaya

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(330, 100);
    glVertex2f(330, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(330, 180);
    glVertex2f(400, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(370, 180);
    glVertex2f(370, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(370, 180);
    glVertex2f(370, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(370, 220);
    glVertex2f(490, 220);
    glEnd();

    //garis cahaya

    //pohon 3

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-220, -50);
    glVertex2f(-180, -50);
    glVertex2f(-180, 110);
    glVertex2f(-220, 110);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-300, 100);
    glVertex2f(-100, 100);
    glVertex2f(-100, 180);
    glVertex2f(-300, 180);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-265, 100);
    glVertex2f(-140, 100);
    glVertex2f(-140, 220);
    glVertex2f(-265, 220);
    glEnd();

    //garis cahaya

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-300, 100);
    glVertex2f(-300, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-300, 180);
    glVertex2f(-225, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-265, 180);
    glVertex2f(-265, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-265, 220);
    glVertex2f(-140, 220);
    glEnd();

    //garis cahaya
}

void pohon_bg_scenery2_lanjutan(){

    //pohon 1
    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(215, -20);
    glVertex2f(180, -20);
    glVertex2f(180, 90);
    glVertex2f(215, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(100, 50);
    glVertex2f(300, 50);
    glVertex2f(300, 130);
    glVertex2f(100, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(140, 50);
    glVertex2f(260, 50);
    glVertex2f(260, 170);
    glVertex2f(140, 170);
    glEnd();

    //garis cahaya

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(100, 50);
    glVertex2f(100, 130);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(100, 130);
    glVertex2f(175, 130);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(140, 130);
    glVertex2f(140, 170);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(140, 130);
    glVertex2f(140, 170);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(140, 170);
    glVertex2f(260, 170);
    glEnd();
    //garis cahaya

    //pohon 2

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(445, 30);
    glVertex2f(410, 30);
    glVertex2f(410, 140);
    glVertex2f(445, 140);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(330, 100);
    glVertex2f(530, 100);
    glVertex2f(530, 180);
    glVertex2f(330, 180);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(370, 100);
    glVertex2f(490, 100);
    glVertex2f(490, 220);
    glVertex2f(370, 220);
    glEnd();

     //garis cahaya

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(330, 100);
    glVertex2f(330, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(330, 180);
    glVertex2f(400, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(370, 180);
    glVertex2f(370, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(370, 180);
    glVertex2f(370, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(370, 220);
    glVertex2f(490, 220);
    glEnd();

    //garis cahaya

    //pohon 3

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-220, -50);
    glVertex2f(-180, -50);
    glVertex2f(-180, 110);
    glVertex2f(-220, 110);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-300, 100);
    glVertex2f(-100, 100);
    glVertex2f(-100, 180);
    glVertex2f(-300, 180);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(117, 132, 169);
    glVertex2f(-265, 100);
    glVertex2f(-140, 100);
    glVertex2f(-140, 220);
    glVertex2f(-265, 220);
    glEnd();

     //garis cahaya

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-300, 100);
    glVertex2f(-300, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-300, 180);
    glVertex2f(-225, 180);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-265, 180);
    glVertex2f(-265, 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-265, 220);
    glVertex2f(-140, 220);
    glEnd();

    //garis cahaya
}

void awan_1v1(){

    glBegin(GL_POLYGON);
    glColor3ub(190, 200, 171);
    glVertex2f(-480, 270);
    glVertex2f(-480, 250);
    glVertex2f(-350, 250);
    glVertex2f(-350, 270);
    glEnd();

    glLineWidth(2.0);

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-480, 270);
    glVertex2f(-480, 250);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-350, 260);
    glVertex2f(-350, 270);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-480, 250);
    glVertex2f(-420, 250);
    glEnd();


    glBegin(GL_LINES);
    glColor3ub(255, 255, 215);
    glVertex2f(-480, 270);
    glVertex2f(-350, 270);
    glEnd();
}

void awan_1v2(){

    glBegin(GL_POLYGON);
    glColor3ub(190, 200, 171);
    glVertex2f(-420, 260);
    glVertex2f(-320, 260);
    glVertex2f(-320, 240);
    glVertex2f(-420, 240);
    glEnd();

    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 255, 215);
    glVertex2f(-420, 260);
    glVertex2f(-320, 260);
    glVertex2f(-320, 240);
    glVertex2f(-420, 240);
    glEnd();

}


void game_title(){

    //-----shadow huruf-------
     //huruf S
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-265, 65); // -355 + 90
    glVertex2f(-225, 65); // -315 + 90
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-255, 65); // -345 + 90
    glVertex2f(-255, 50);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-265, 38); // -355 + 90
    glVertex2f(-225, 38); // -315 + 90
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-235, 45); // -325 + 90
    glVertex2f(-235, 35);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-265, 32); // -355 + 90
    glVertex2f(-225, 32); // -315 + 90
    glEnd();

    //huruf S

    //huruf L

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-205, 69); // -295 + 90
    glVertex2f(-205, 27);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-205, 32);
    glVertex2f(-175, 32);
    glEnd();

    //huruf L

    //huruf I

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-155, 69); // -245 + 90
    glVertex2f(-155, 27);
    glEnd();

    //Huruf I

    //huruf M

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-125, 69); // -215 + 90
    glVertex2f(-125, 27);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-85, 69); // -175 + 90
    glVertex2f(-85, 27);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-105, 69); // -195 + 90
    glVertex2f(-105, 35);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-125, 61); // -215 + 90
    glVertex2f(-85, 61);  // -175 + 90
    glEnd();

    //huruf M

    //huruf E

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-60, 79); // -150 + 90
    glVertex2f(-60, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-68, 32);
    glVertex2f(-30, 32);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-60, 64); // -150 + 90
    glVertex2f(-30, 64); // -120 + 90
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-60, 48);
    glVertex2f(-40, 48);
    glEnd();

    //huruf E

    //huruf J

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(5, 47); // -85 + 90
    glVertex2f(5, 47);
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(35, 69); // -55 + 90
    glVertex2f(35, 27);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(-5, 32);
    glVertex2f(35, 32); // -55 + 90
    glEnd();

    //huruf J

    //huruf U

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(65, 69); // -25 + 90
    glVertex2f(65, 27);
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(95, 69); // 5 + 90
    glVertex2f(95, 27);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(65, 32);
    glVertex2f(95, 32); // 5 + 90
    glEnd();

    //huruf U

    //huruf M

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(125, 69); // 35 + 90
    glVertex2f(125, 27);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(165, 69); // 75 + 90
    glVertex2f(165, 27);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(145, 69); // 55 + 90
    glVertex2f(145, 35);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(125, 61); // 35 + 90
    glVertex2f(165, 61); // 75 + 90
    glEnd();

    //huruf M

    //huruf P

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(190, 69); // 100 + 90
    glVertex2f(190, 27);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(190, 64); // 100 + 90
    glVertex2f(220, 64); // 130 + 90
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(190, 40); // 100 + 90
    glVertex2f(225, 40); // 135 + 90
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(2, 53, 134);
    glVertex2f(220, 69);
    glVertex2f(220, 40); // 130 + 90
    glEnd();

    //-------shadow huruf-------

    //huruf S
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-265, 75); // -355 + 90
    glVertex2f(-225, 75); // -315 + 90
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-255, 75); // -345 + 90
    glVertex2f(-255, 60);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-265, 58); // -355 + 90
    glVertex2f(-225, 58); // -315 + 90
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-235, 55); // -325 + 90
    glVertex2f(-235, 45);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-265, 42); // -355 + 90
    glVertex2f(-225, 42); // -315 + 90
    glEnd();

    //huruf S

    //huruf L

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-205, 79); // -295 + 90
    glVertex2f(-205, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-205, 42);
    glVertex2f(-175, 42);
    glEnd();

    //huruf L

    //huruf I

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-155, 79); // -245 + 90
    glVertex2f(-155, 37);
    glEnd();

    //Huruf I

    //huruf M

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-125, 79); // -215 + 90
    glVertex2f(-125, 37);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-85, 79); // -175 + 90
    glVertex2f(-85, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-105, 79); // -195 + 90
    glVertex2f(-105, 45);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-125, 71); // -215 + 90
    glVertex2f(-85, 71);  // -175 + 90
    glEnd();

    //huruf M

    //huruf E

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-60, 79); // -150 + 90
    glVertex2f(-60, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-60, 42);
    glVertex2f(-30, 42);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-60, 74); // -150 + 90
    glVertex2f(-30, 74); // -120 + 90
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(-60, 58);
    glVertex2f(-40, 58);
    glEnd();

    //huruf E

    //huruf J

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(5, 57); // -85 + 90
    glVertex2f(5, 37);
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(35, 79); // -55 + 90
    glVertex2f(35, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(5, 42);
    glVertex2f(35, 42); // -55 + 90
    glEnd();

    //huruf J

    //huruf U

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(65, 79); // -25 + 90
    glVertex2f(65, 37);
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(95, 79); // 5 + 90
    glVertex2f(95, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(65, 42);
    glVertex2f(95, 42); // 5 + 90
    glEnd();

    //huruf U

    //huruf M

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(125, 79); // 35 + 90
    glVertex2f(125, 37);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(165, 79); // 75 + 90
    glVertex2f(165, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(145, 79); // 55 + 90
    glVertex2f(145, 45);
    glEnd();

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(125, 71); // 35 + 90
    glVertex2f(165, 71); // 75 + 90
    glEnd();

    //huruf M

    //huruf P

    glLineWidth(15.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(190, 79); // 100 + 90
    glVertex2f(190, 37);
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(190, 74); // 100 + 90
    glVertex2f(220, 74); // 130 + 90
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(190, 50); // 100 + 90
    glVertex2f(225, 50); // 135 + 90
    glEnd();

    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3ub(127, 224, 255);
    glVertex2f(220, 79);
    glVertex2f(220, 50); // 130 + 90
    glEnd();

    //-------shadow huruf-------



}



void display_menu_screen(){

    display_menu_screen_state = true;


     glClear(GL_COLOR_BUFFER_BIT);

    background();
    background_gradient();

   // awan_1v2();
  //  awan_1v1();


    cahaya();

    //animasi cahaya

    if(opacity_c1 == 1 && c1 > min_opacity_c1){
        c1 = c1 - 0.2;

        if(c1 <= min_opacity_c1){
            opacity_c1 = false;
        }
    }
    else if (opacity_c1 == 0){
        c1 = c1 + 0.2;

        if(c1 >= max_opacity_c1){
            opacity_c1 = true;
        }
    }

    //c2

    if(opacity_c2 == 1 && c2 > min_opacity_c2){
        c2 = c2 - 0.05;

        if(c2 <= min_opacity_c2){
            opacity_c2 = false;
        }
    }
    else if (opacity_c2 == 0){
        c2 = c2 + 0.05;

        if(c2 >= max_opacity_c2){
            opacity_c2 = true;
        }
    }


      //c3

    if(opacity_c3 == 1 && c3 > min_opacity_c3){
        c3 = c3 - 0.08;

        if(c3 <= min_opacity_c3){
            opacity_c3 = false;
        }
    }
    else if (opacity_c3 == 0){
        c3 = c3 + 0.08;

        if(c3 >= max_opacity_c3){
            opacity_c3 = true;
        }
    }

    glPushMatrix();
    glTranslated(h, 0, 0);
    bg_scenery2();
    pohon_bg_scenery2();
    glPopMatrix();

    h -=0.1;
    if(h < -1000){
        h=1000;
    }

    glPushMatrix();
    glTranslated(i, 0, 0);
    bg_scenery2_lanjutan();
    pohon_bg_scenery2_lanjutan();
    glPopMatrix();

    i -=0.1;
    if(i < -1000){
        i=1000;
    }


    glPushMatrix();
    glTranslated(f, 0, 0);
    background_scenery();
    pohon_bg_scenery();
    glPopMatrix();

    f -= 0.2;
    if(f < - 1000){
        f=1000;
    }

    glPushMatrix();
    glTranslated(g, 0, 0);
    background_scenery_lanjutan();
    pohon_bg_scenery_lanjutan();
    glPopMatrix();

    g -= 0.2;
    if(g < - 1000){
        g=1000;
    }


    platform();





    glPushMatrix();
    glTranslated(0, k, 0);
    slime();
    glPopMatrix();

  //  glPushMatrix();

   // glScalef(1, scale, 1);
   // slime();
    //glPopMatrix();


    if((up == 1)&&(jumpstate==false)){
        k = k+0.4;

        if(k > 10){
            up = false;
        }
    }
    else if((up == 0)&&(jumpstate == false)){
        k = k-0.4;
        if(k <= 0){
            up = true;
        }
    }

    glPushMatrix();
    glTranslated(d, 0, 0);
    pohon_foreground();
    glPopMatrix();

    d = d-4;
    if(d < -1000){
        d=1000;
    }

    glPushMatrix();
    glTranslated(j, 0, 0);
    pohon_foreground_lanjutan();
    glPopMatrix();

    j = j-4;
    if(j < -1000){
        j=1000;
    }

    layar_hitam();


    if((opacity_start_letter >= min_opacity_start_letter)&&(opacity_on == true)){
        opacity_start_letter -= 1.5;

        if(opacity_start_letter <= min_opacity_start_letter){
            opacity_on = false;
        }
    }

    else if(opacity_on == false) {
        opacity_start_letter += 1.5;

        if(opacity_start_letter >= max_opacity_start_letter){
            opacity_on = true;
        }
    }

    game_title();

    glEnable(GL_BLEND); // Aktifkan blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setel fungsi blending

    glPushMatrix();
    glColor4ub(255, 255, 255, opacity_start_letter);
    glRasterPos2f(-100, -20);
    stringstream ss;
    ss << "Press 'S' to Start";
    string startStr = ss.str();
    for (int i = 0; i < startStr.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, startStr[i]);
    }
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glRasterPos2f(-92.5, -50);
    string pressspace = "Press 'space' to Jump";
    for (int i = 0; i < pressspace.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, pressspace[i]);
    }


    glFlush();
    //glutSwapBuffers();

}

// Display function
void display() {

    gameisbeingplayed = true;
    glClear(GL_COLOR_BUFFER_BIT);

    background();
    background_gradient();

   // awan_1v2();
  //  awan_1v1();


    cahaya();

    //animasi cahaya

    if(opacity_c1 == 1 && c1 > min_opacity_c1){
        c1 = c1 - 0.2;

        if(c1 <= min_opacity_c1){
            opacity_c1 = false;
        }
    }
    else if (opacity_c1 == 0){
        c1 = c1 + 0.2;

        if(c1 >= max_opacity_c1){
            opacity_c1 = true;
        }
    }

    //c2

    if(opacity_c2 == 1 && c2 > min_opacity_c2){
        c2 = c2 - 0.05;

        if(c2 <= min_opacity_c2){
            opacity_c2 = false;
        }
    }
    else if (opacity_c2 == 0){
        c2 = c2 + 0.05;

        if(c2 >= max_opacity_c2){
            opacity_c2 = true;
        }
    }


      //c3

    if(opacity_c3 == 1 && c3 > min_opacity_c3){
        c3 = c3 - 0.08;

        if(c3 <= min_opacity_c3){
            opacity_c3 = false;
        }
    }
    else if (opacity_c3 == 0){
        c3 = c3 + 0.08;

        if(c3 >= max_opacity_c3){
            opacity_c3 = true;
        }
    }

    glPushMatrix();
    glTranslated(h, 0, 0);
    bg_scenery2();
    pohon_bg_scenery2();
    glPopMatrix();

    if(score >= 1000){
        h -=0.3;
    }

    else if(score >= 500){
        h -=0.2;
    }

    else{
        h -=0.1;
    }

    if(h < -1000){
        h=1000;
    }

    glPushMatrix();
    glTranslated(i, 0, 0);
    bg_scenery2_lanjutan();
    pohon_bg_scenery2_lanjutan();
    glPopMatrix();

    if(score >= 1000){
        i -=0.3;
    }

    else if(score >= 500){
        i -=0.2;
    }

    else{
        i -=0.1;
    }


    if(i < -1000){
        i=1000;
    }


    glPushMatrix();
    glTranslated(f, 0, 0);
    background_scenery();
    pohon_bg_scenery();
    glPopMatrix();

   if(score >= 1000){
        f -= 0.4;
    }

    else if(score >= 500){
        f -= 0.3;
    }

    else{
        f -= 0.2;
    }

    if(f < - 1000){
        f=1000;
    }

    glPushMatrix();
    glTranslated(g, 0, 0);
    background_scenery_lanjutan();
    pohon_bg_scenery_lanjutan();
    glPopMatrix();

    if(score >=1000){
        g -=0.4;
    }

    else if(score >= 500){
        g -= 0.3;
    }

    else{
        g -= 0.2;
    }

    if(g < - 1000){
        g=1000;
    }


    platform();

   // glPushMatrix();
  //  glTranslated(b, 0, 0);
  //  garis_tanah();
  //  glPopMatrix();

  //  b = b-2;
   // if(b < -2000){
   //     b=2000;
  //  }

  //  glPushMatrix();
  //  glTranslated(c, 0, 0);
  //  garis_tanah2();
  //  glPopMatrix();

  //  c = c-2;
  //  if(c < -2000){
  //      c=2000;
 //   }


    normalize_time = jumppos / jumpheightmax;
    double eased_val = eased_function();
    current_jumppos = jumpheightmax * eased_val;


  //  normalize_jumpscale_time = scale/max_scale;
  //  double eased_val_jumpscale = jump_scale_eased_function();
 //   current_jumpscale = max_scale * pow(eased_val, 2);


    if ((jumpstate == true)&& (keyispressed == true)) {
        jumppos = jumppos + 5;

      //  scalling_up = true;

        if((scalling_up == true)&&(scale <= max_scale)){
            scale = scale + 0.01;
            if(scale >= max_scale){
                scalling_up = false;
            }
        }

        if (jumppos >= jumpheightmax) {
            jumpstate = false;
        }

    } else {
        jumppos = jumppos - 5;
        if((scalling_up == false)&&(scale >= min_scale)){
            scale = scale - 0.01;
            if(scale <= min_scale){
                scale = min_scale;
            }
        }

        if (jumppos <= 0) {
            jumppos = 0;
            keyispressed = false;
        }
    }


    glPushMatrix();
    glTranslated(0, current_jumppos, 0);
    glTranslated(0, k, 0);
    glScalef(1, scale, 0);
    slime();
    glPopMatrix();


    if((up == 1)&&(jumpstate==false)&&(keyispressed == false)){
        k = k+0.4;

        if(k > 10){
            up = false;
        }
    }
    else if((up == 0)&&(jumpstate == false)&&(keyispressed == false)){
        k = k-0.4;
        if(k <= 0){
            up = true;
        }
    }

     //   glPushMatrix();
     //   glTranslated(a, 0, 0);
     //   log();
     //   glPopMatrix();

     //   a -= 2;
      //  if (a < -1000) {
     //       a = 1000;
      //  }


    /*

    glPushMatrix();
    glTranslated(a, 0, 0);
    log();
    glPopMatrix();

    a -= 2;
    if (a < -1000) {
        a = 1000;
    }


    glPushMatrix();
    glTranslated(e, 0, 0);
    log2();
    glPopMatrix();

    e -= 3;
    if (e < -1500) {
        e = 2000;
    }*/

    //musuh 1

    if(scenario1_on_off == true){
        scenario1 = rand()%2 + 1;
        scenario1_on_off = false;
    }

        switch(scenario1){
            case 1:
            glPushMatrix();
            glTranslated(tampung, 0, 0);
            log();
            glPopMatrix();

            if(score >= 1000){
                tampung -= 3;
            }

            else if(score >= 500){
                tampung -= 2.6;
            }

            else{
                tampung -= 2;
            }

            if (tampung < -1000) {
                /*
                scenario_mode1 = rand()%2+1;
                switch(scenario_mode1){
                case 1:
                    tampung = 1000;
                break;
                case 2:
                    tampung = 1000;
                }
                */
                tampung = 1000;
                scenario1_on_off = true;
            }
        break;
            case 2:

            glPushMatrix();
            glTranslated(tampung, 0, 0);
            log2();
            glPopMatrix();

             if(score >= 1000){
                tampung -= 3;
            }

            else if(score >= 500){
                tampung -= 2.6;
            }

            else{
                tampung -= 2;
            }

            if (tampung < -1000) {
                /*
                scenario_mode1 = rand()%2+1;
                switch(scenario_mode1){
                case 1:
                    tampung = 1000;
                break;
                case 2:
                    tampung = 1000;
                }
                */
                tampung = 1000;
                scenario1_on_off = true;
            }
        }



     //-----musuh 2--------
    //-----musuh 2--------

    if(scenario2_on_off == true){
        scenario2 = rand()%2 + 1;
        scenario2_on_off = false;
    }

        switch(scenario2){
            case 1:
            glPushMatrix();
            glTranslated(tampung2, 0, 0);
            log();
            glPopMatrix();

            if(score >= 1000){
                tampung2 -= 3;
            }

            else if(score >= 500){
                tampung2 -= 2.6;
            }

            else{
                tampung2 -= 2;
            }

            if (tampung2 < -1000) {
                /*
                scenario_mode2 = rand()%2+1;
                switch(scenario_mode2){
                case 1:
                    tampung2 = 1000;
                break;
                case 2:
                    tampung2 = 1500;
                }*/
                tampung2 = 1000;
                scenario2_on_off = true;
            }
        break;
            case 2:

            glPushMatrix();
            glTranslated(tampung2, 0, 0);
            log2();
            glPopMatrix();

             if(score >= 1000){
                tampung2 -= 3;
            }

            else if(score >= 500){
                tampung2 -= 2.6;
            }

            else{
                tampung2 -= 2;
            }

            if (tampung2 < -1000) {
                /*
                scenario_mode2 = rand()%2+1;
                switch(scenario_mode2){
                case 1:
                    tampung2 = 1000;
                break;
                case 2:
                    tampung2 = 1500;
                }*/
                tampung2 = 1000;
                scenario2_on_off = true;
            }
        }
    //-----musuh 2--------



    //-----musuh 3--------

    if(scenario3_on_off == true){
        scenario3 = rand()%2 + 1;
        scenario3_on_off = false;
    }

        switch(scenario3){
            case 1:
            glPushMatrix();
            glTranslated(tampung3, 0, 0);
            log2();
            glPopMatrix();

            if(score >= 1000){
                tampung3 -= 3;
            }

            else if(score >= 500){
                tampung3 -= 2.6;
            }

            else{
                tampung3 -= 2;
            }

            if (tampung3 < -1000) {
                scenario_mode3 = rand()%2+1;
                switch(scenario_mode3){
                case 1:
                    tampung3 = 2000;
                break;
                case 2:
                    tampung3 = 1000;
                }
                scenario3_on_off = true;
            }
        break;
            case 2:

            glPushMatrix();
            glTranslated(tampung3, 0, 0);
            log();
            glPopMatrix();

             if(score >= 1000){
                tampung3 -= 3;
            }

            else if(score >= 500){
                tampung3 -= 2.6;
            }

            else{
                tampung3 -= 2;
            }

            if (tampung3 < -1000) {
                scenario_mode3 = rand()%2+1;
                switch(scenario_mode3){
                case 1:
                    tampung3 = 2000;
                break;
                case 2:
                    tampung3 = 1000;
                }
                scenario3_on_off = true;
            }
        }
    //-----musuh 3--------

    glPushMatrix();
    glTranslated(d, 0, 0);
    pohon_foreground();
    glPopMatrix();

    if(score >=1000){
        d=d-4.6;
    }
    else if(score >=500){
        d=d-4.3;
    }

    else{
        d = d-4;
    }

    if(d < -1000){
        d=1000;
    }

    glPushMatrix();
    glTranslated(j, 0, 0);
    pohon_foreground_lanjutan();
    glPopMatrix();

    if(score >=1000){
        j = j-4.6;
    }

    else if(score >= 500){
        j = j-4.3;
    }
    else{
        j = j-4;
    }

    if(j < -1000){
        j=1000;
    }


    crash_detection();
    crash_detection2();
    crash_detection3();



 //ini tuntuk menampilkan skor
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glRasterPos2f(-400, -250);
    stringstream ss;
    ss << "Score: " << score;
    string scoreStr = ss.str();
    for (int i = 0; i < scoreStr.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreStr[i]);
    }
    glPopMatrix();


    glEnable(GL_BLEND); // Aktifkan blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setel fungsi blending

    glBegin(GL_POLYGON);
    glColor4ub(0,0,0, l);
    glVertex2f(-500, 300);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, 300);
    glEnd();

    l -= 0.2;
    if(l<=0){
        l = 0;
    }

    glFlush();
    //glutSwapBuffers();

}


void loading_screen(){

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2f(-500, 300);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, 300);
    glEnd();

    glColor3ub(255, 255, 255);

    glRasterPos2f(-50, 20);
    string loadtext = "Loading.....";
    for (int i = 0; i < loadtext.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, loadtext[i]);
    }

    glRasterPos2f(-40, -20);
    string guide = "Guide:";
    for (int i = 0; i < guide.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, guide[i]);
    }

    glRasterPos2f(-80, -50);
    string pressspace = "Press 'space' to Jump";
    for (int i = 0; i < pressspace.length(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, pressspace[i]);
    }

    loading_counter ++;

    if(loading_counter >= 500){
        glutDisplayFunc(display);
    }

    glFlush();

}


// Keyboard function
void myKeyboard(unsigned char key, int x, int y) {
    if ((key == ' ' && jumpstate == false) && (keyispressed == false)&&(gameisbeingplayed == true)) {
        jumpstate = true;
        scalling_up = true;
        keyispressed = true;

    }

    else if((key == 's' || key == 'S')&&(display_menu_screen_state = true)&&(game_over_on == false)){
        display_menu_screen_state = false;
        glutDisplayFunc(display);
    }

    else if((key == 'y' || key == 'Y')&&(crash == true)){
        reset_display();
        glutDisplayFunc(display);
        crash = false;
    }

    else if((key == 'x' || key == 'X')&&(crash == true)){
       exit(0);
    }
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(175, 75);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Slime Jump");

    gluOrtho2D(-500, 500, -300, 300);

    glutDisplayFunc(display_menu_screen);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(5, timer, 0);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutMainLoop();

    return 0;
}
