#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ocean.h"
#include "boat.h"
#include "cannon.h"
#include "rock.h"
#include "monster.h"
#include "barrel.h"
#include "diamond.h"
#include "power.h"
#include "gift.h"
#include "boss.h"
#include "sail.h"
#include "island.h"
#include "tree.h"
#include "man.h"
#include <bits/stdc++.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//GLFWcursor *cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);

/**************************
* Customizable functions *
**************************/

//Ball ball1;
Ocean ocean;
Boat boat;
Cannon cannon;
Rock rock[100];
Barrel barrel[25];
Diamond diamond[25];
Monster monster[110];
Power power;
Gift gift;
Boss boss;
Sail sail;
Man man;
Ball ball;
Island island;
Tree tree[64];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 10;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


    if(boat.mode==0)
    {
        glm::vec3 eye ( boat.position.x+(0.8f*sin(boat.rotation*M_PI/180.0f)), 3.5f, boat.position.z+(0.8f*cos(boat.rotation*M_PI/180.0f)));
        glm::vec3 target (boat.position.x + 8.8f*sin(boat.rotation*M_PI/180.0f), 0, boat.position.z + 8.8f*cos(boat.rotation*M_PI/180.0f));
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==1)
    {
        glm::vec3 eye ( boat.position.x - 1.5f*sin(boat.rotation*M_PI/180.0f), 13.0f , boat.position.z - 1.5f*cos(boat.rotation*M_PI/180.0f));
        glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==2)
    {
        glm::vec3 eye ( boat.position.x, 13.0f , boat.position.z);
        glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==3)
    {
        glm::vec3 eye ( 20.0f, 13.0f , 0.0f);
        glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==4)
    {
        glm::vec3 eye (boat.position.x - 3.5f*sin(boat.rotation*M_PI/180.0f), 6.5f , boat.position.z - 3.5f*cos(boat.rotation*M_PI/180.0f));
        glm::vec3 target (boat.position.x + 5.0f*sin(boat.rotation*M_PI/180.0f), 1, boat.position.z + 5.0f*cos(boat.rotation*M_PI/180.0f));
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==5)
    {
        glm::vec3 eye ( boat.position.x, 30.0f , boat.position.z);
        glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==-1)
    {
        glm::vec3 eye ( boat.position.x - 8.0f*sin(boat.heliangle*M_PI/180.0f), boat.heliheight , boat.position.z - 8.0f*cos(boat.heliangle*M_PI/180.0f));
        glm::vec3 target ( boat.position.x, 1.0f, boat.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    else if(boat.mode==-2)
    {
        glm::vec3 eye ( man.position.x + 0.6f*sin(man.rotation*M_PI/180.0f), 5 , man.position.z + 0.6f*cos(man.rotation*M_PI/180.0f));
        glm::vec3 target ( man.position.x + 3.6f*sin(man.rotation*M_PI/180.0f), 3,  man.position.z + 3.6f*cos(man.rotation*M_PI/180.0f));
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }

    // Eye - Location of camera. Don't change unless you are sure!!

    // Boat View:        glm::vec3 eye ( boat.position.x+(0.8f*sin(boat.rotation*M_PI/180.0f)), 3.5f, boat.position.z+(0.8f*cos(boat.rotation*M_PI/180.0f)));
    // Top View1:        glm::vec3 eye ( boat.position.x - 1.5f*sin(boat.rotation*M_PI/180.0f), 13.0f , boat.position.z - 1.5f*cos(boat.rotation*M_PI/180.0f));
    // Top View2:        glm::vec3 eye ( boat.position.x, 13.0f , boat.position.z);
    // Tower View:       glm::vec3 eye ( 20.0f, 13.0f , 0.0f);
    // Follow-up View:   glm::vec3 eye (boat.position.x - 3.5f*sin(boat.rotation*M_PI/180.0f), 6.5f , boat.position.z - 3.5f*cos(boat.rotation*M_PI/180.0f));


    // Target - Where is the camera looking at.  Don't change unless you are sure!!

    // Boat View:        glm::vec3 target (boat.position.x + 8.8f*sin(boat.rotation*M_PI/180.0f), 0, boat.position.z + 8.8f*cos(boat.rotation*M_PI/180.0f));
    // Top View1:        glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
    // Top View2:        glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
    // Tower View:       glm::vec3 target ( boat.position.x, boat.position.y, boat.position.z);
    // Follow-up View:   glm::vec3 target (boat.position.x + 5.0f*sin(boat.rotation*M_PI/180.0f), 1, boat.position.z + 5.0f*cos(boat.rotation*M_PI/180.0f));


    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!

    // Boat View:        glm::vec3 up (0, 1, 0);
    // Top View1:        glm::vec3 up (0, 1, 0);
    // Top View2:        glm::vec3 up (0, 0, 1);
    // Tower View:       glm::vec3 up (0, 1, 0);
    // Follow-up View:   glm::vec3 up (0, 1, 0);


    // Compute Camera matrix (view)

    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    //ball1.draw(VP);
//    island.draw(VP);
    for(int i=0;i<64;i++)
        tree[i].draw(VP);
    ocean.draw(VP);
    boat.draw(VP);
    cannon.draw(VP);
    sail.draw(VP);
    for(int i=0;i<100;i++)
        rock[i].draw(VP);
    for(int i=0;i<25;i++)
    {
        diamond[i].draw(VP);
        barrel[i].draw(VP);
    }
    for(int i=0;i<110;i++)
        monster[i].draw(VP);

    if(boat.fire)power.draw(VP);

    gift.draw(VP);
    boss.draw(VP);

    if(boat.shoot==1)
        ball.draw(VP);

    if(boat.hunt == 1)
        man.draw(VP);
  //  island.draw(VP);
}

int check_struck()
{
    for(int i=0;i<100;i++)
    {
        if(rock[i].struck==1)
            return 1;
    }
    return 0;
}

int monster_struck()
{
    for(int i=0;i<110;i++)
    {
        if(monster[i].alive==1 && monster[i].struck==1)
            return 1;
    }

    if(boat.boss>0 && boss.alive==1 && boss.struck==1)return 1;

    return 0;
}

int island_struck()
{
    if(2095 <= boat.position.x && boat.position.x <= 2295 && 2095 <= boat.position.z && boat.position.z <= 2295)return 1;

    return 0;
}

int tree_struck()
{
    for(int i=0;i<64;i++)
        if(tree[i].position.x-0.5 <= boat.position.x && boat.position.x <= tree[i].position.x+0.5 && tree[i].position.z-0.5 <= boat.position.z && boat.position.z <= tree[i].position.z+0.5)return 1;

    return 0;
}

void tick_input(GLFWwindow *window) {
    int space  = glfwGetKey(window, GLFW_KEY_SPACE);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int minusone = glfwGetKey(window, GLFW_KEY_9);
    int zero = glfwGetKey(window, GLFW_KEY_0);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int i = glfwGetKey(window, GLFW_KEY_I);
    int ml = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int mr = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
  //  int ms = glfwSetScrollCallback(window, scroll_callback);

    int k = check_struck();
    int m = monster_struck();
    int is = island_struck();

    if(i && boat.boss==2 && boss.alive==0)
    //if(i)
    {
        boat.hunt = 1;
        man = Man(boat.position.x+(5.0f*sin(boat.rotation*M_PI/180.0f)), 1.0f, boat.position.z+(5.0f*cos(boat.rotation*M_PI/180.0f)), COLOR_BLACK);
        gift = Gift(tree[60].position.x+1.5, 2.0, tree[45].position.z, 1000 ,COLOR_GOLD);
        boat.mode = -2;
    }

    if(f && boat.fire==0)
    {
        //if(boat.fire==0)
        //{
            boat.mode = 5;
            boat.fire = 1;
            power = Power(boat.position.x+(4.0f*sin(boat.rotation*M_PI/180.0f)), 0.0f, boat.position.z+(4.0f*cos(boat.rotation*M_PI/180.0f)), 0, boat.rotation, COLOR_BACKGROUND);
            //draw();
        //}
        //else if(boat.fire==1)
        //{
            //boat.fire = 0;
        //}
//      double xpos, ypos;
//      glfwGetCursorPos(window, &xpos, &ypos);
//      cout<<"f: "<<xpos<<" "<<ypos<<endl;
    }
    if(b && boat.fire==1)
    {
        for(int i=0;i<110;i++)
        {
            if(monster[i].alive==1)
            {
                float tx = power.position.x;
                float tz = power.position.z;

                float mx = monster[i].position.x;
                float mz = monster[i].position.z;

                if(abs(mx-tx)*abs(mx-tx) + abs(mz-tz)*abs(mz-tz) <= 3)
                {
                    ball = Ball(boat.position.x + 2.5*sin(boat.rotation*M_PI/180.0f), 1.0f, boat.position.z + 2.5*cos(boat.rotation*M_PI/180.0f), i, boat.rotation, COLOR_BLACK);
                    boat.shoot = 1;
                    monster[i].accn = -0.05;
                    monster[i].alive = 0;
                    if(monster[i].type==1)
                        gift = Gift(monster[i].position.x, 1, monster[i].position.z, 50, COLOR_SILD);
                    else
                        gift = Gift(monster[i].position.x, 1, monster[i].position.z, 75, COLOR_GOLD);
                    //boat.point += 50;
                }
            }
        }
        if(boat.boss>=1&&boss.alive==1)
        {
            float tx = power.position.x;
            float tz = power.position.z;

            float mx = boss.position.x;
            float mz = boss.position.z;

            if(abs(mx-tx)*abs(mx-tx) + abs(mz-tz)*abs(mz-tz) <= 3)
            {
                boss.accn = -0.05;
                boss.lifes--;
                if(boss.lifes==0)
                {
                    if(boat.boss==2)
                    {
                        boss.alive = 0;
                        boat.position.x = 2000;
                        boat.position.z = 2000;
                        gift = Gift(boat.position.x+10*(cos(boat.rotation*M_PI/180)), 1, boss.position.z+10*(sin(boat.rotation*M_PI/180)), 500, COLOR_GOLD);
                        boat.mode = 0;
                        boat.fire = 0;
                    }
                    boss.alive = 0;
                }
                if(boat.boss==1)
                    gift = Gift(boss.position.x, 1, boss.position.z, 200, COLOR_GOLD);
                else if(boat.boss==2)
                    gift = Gift(boss.position.x, 1, boss.position.z, 500, COLOR_GOLD);
                //boat.point += 50;
            }
        }
        boat.mode = 0;
        boat.fire = 0;
    }
    //cout<<boat.position.y<<endl;
    if(space && boat.jump==0)
    {
        cout<<"space"<<endl;
        boat.speedy = 0.025;
        boat.jump = 1;
        //boat.tick();
    }
    if (left) {
        if(boat.hunt==1)
        {
            man.rotation += 0.5;
        }
        else
        {
            if(is==0 && k==0 && m==0)
            {
                boat.rotate(1);
                cannon.rotate(1);
            }
            else
            {
                boat.speed = -0.05;
                cannon.speed = -0.05;
                boat.move_forward(1);
                cannon.move_forward(1);
            }
        }
    }
    if (right) {
        if(boat.hunt==1)
        {
            man.rotation -= 0.5;
        }
        else
        {
            if(is==0 && k==0 && m==0)
            {
                boat.rotate(-1);
                cannon.rotate(-1);
            }
            else
            {
                boat.speed = -0.05;
                cannon.speed = -0.05;
                boat.move_forward(1);
                cannon.move_forward(1);
            }
        }
    }
    if (up) {
        //cout<<rock.struck<<endl;
        if(boat.hunt==1)
        {
            man.position.x += 0.05f*sin(man.rotation*M_PI/180.0f);
            man.position.z += 0.05f*cos(man.rotation*M_PI/180.0f);

            if(!(2095 <= man.position.x && man.position.x <= 2295 && 2095 <= man.position.z && man.position.z <= 2295))
                boat.health = 0;

            if(tree_struck())
            {
                man.position.x -= 0.05f*sin(man.rotation*M_PI/180.0f);
                man.position.z -= 0.05f*cos(man.rotation*M_PI/180.0f);
            }
            if(gift.position.x >= man.position.x-0.5 && gift.position.x <= man.position.x+0.5 && gift.position.z >= man.position.z-0.5 && gift.position.z <= man.position.z+0.5)
            {
                gift.position.y = -4;
                boat.point += gift.points;
                exit(0);
            }
        }
        else
        {
            if(is==0 && k==0 && m==0)
            {

                boat.speed = 0.05;
                cannon.speed = 0.05;

                if((boat.boss==1 && boss.alive==0) || boat.boss==2)
                    boat.speed = 0.1;
                    cannon.speed = 0.1;

                boat.move_forward(1);
                cannon.move_forward(1);
            }
            else
            {
                boat.speed = -0.05;
                cannon.speed = -0.05;
                boat.move_forward(1);
                cannon.move_forward(1);
            }
            if(boat.jump==0)
            {
                boat.speedy = 0.01;
                boat.jump = 1;
            }
        }
    }
    if (down)
    {
        // write something
    }
    if (zero) {
        boat.mode = 0;
    }
    else if (one) {
        boat.mode = 1;
    }
    else if (two) {
        boat.mode = 2;
    }
    else if (three) {
        boat.mode = 3;
    }
    else if (four) {
        boat.mode = 4;
    }
    else if (minusone) {
        boat.mode = -1;
    }

    if(boat.mode==-1)
    {
        if(w)
        {
            if(boat.heliheight<=20.0)
                boat.heliheight += 0.05;
        }
        else if(s)
        {
            if(boat.heliheight>=5.0)
                boat.heliheight -= 0.05;
        }
        else if(d)boat.heliangle += 0.5;
        else if(a)boat.heliangle -= 0.5;

        if(ml)boat.heliangle -= 0.5;
        else if(mr)boat.heliangle += 0.5;

//        if(ms==1){
//            if(boat.heliheight>=5.0)
//                boat.heliheight -= 0.05;}

//        else if(ms==-1){
//            if(boat.heliheight<=20.0)
//                boat.heliheight += 0.05;

    }
}

int check_barrel()
{
    for(int i=0;i<25;i++)
    {
        barrel[i].tick(boat, cannon);
        diamond[i].rotation += 1;
        if(barrel[i].struck==1)
        {
            if(diamond[i].show==1)
            {
                boat.point += ((i%5)+1)*5;
                diamond[i] = Diamond(barrel[i].position.x, barrel[i].position.y - 10, barrel[i].position.z, COLOR_BLACK);
                diamond[i].show = 0;
            }
            return 1;
        }
    }
    return 0;
}

void tick_elements() {
    sail.tick(boat);
    if(gift.tick(boat, cannon))boat.point += gift.points;

    if(boat.point >= 1000 && boat.boss==0 && boss.alive==0)
    {
        cout<<"boss1"<<endl;
        boss = Boss(boat.position.x + 40*(sin(boat.rotation*M_PI/180)), 0, boat.position.z + 40*(cos(boat.rotation*M_PI/180)), 1, COLOR_GOLD, COLOR_SILD);
        boat.boss++;
    }
    if(boat.point >= 2000 && boat.boss==1 && boss.alive==0)
    {
        cout<<"boss2"<<endl;
        boss = Boss(boat.position.x + 40*(sin(boat.rotation*M_PI/180)), 0, boat.position.z + 40*(cos(boat.rotation*M_PI/180)), 1, COLOR_GOLD, COLOR_SILD);
        boat.boss++;
    }
    //ball1.tick();2
    if(boat.fire==1)
    {
        boat.mode = 5;
       // float fr = power.fraction;
       // if(fr<=0)power.flag = 0;
       // else if(fr>=1)power.flag = 1;
        float dist;
        if(power.flag==0)dist=power.distance+0.1;
        else dist=power.distance-0.1;

        if(dist>25.0)power.flag=1;
        else if(dist<4.0)power.flag=0;

        //cout<<dist<<endl;
        power.distance = dist;
        power.position.x = boat.position.x+(dist*sin(boat.rotation*M_PI/180.0f));
        power.position.y = 0.0;
        power.position.z = boat.position.z+(dist*cos(boat.rotation*M_PI/180.0f));
       // cout<<fr<<endl;
       // if(power.flag==1)
       //     power = Power(boat.position.x+(2.0f*sin(boat.rotation*M_PI/180.0f)), 5.5f, boat.position.z+(10.0f*cos(boat.rotation*M_PI/180.0f)), fr-0.002f, 1, boat.rotation, COLOR_BLACK, COLOR_YELLOW);

       // else if(power.flag==0)
       //     power = Power(boat.position.x+(2.0f*sin(boat.rotation*M_PI/180.0f)), 0.0f, boat.position.z+(2.0f*cos(boat.rotation*M_PI/180.0f)), 0, boat.rotation, COLOR_BACKGROUND);
        //draw();
        //power.position.x, power.position.y, power.position.z  = boat.position.x+(10.0f*sin(boat.rotation*M_PI/180.0f)), 5.5f, boat.position.z+(10.0f*cos(boat.rotation*M_PI/180.0f));
        //draw();
    }

    if(boat.shoot==1)
    {
        ball.position.x += ball.speed*sin(ball.angl*M_PI/180.0f);
        ball.position.z += ball.speed*cos(ball.angl*M_PI/180.0f);

        float tx = ball.position.x;
        float tz = ball.position.z;

        float mx = monster[ball.monster].position.x;
        float mz = monster[ball.monster].position.z;

        if(abs(mx-tx)*abs(mx-tx) + abs(mz-tz)*abs(mz-tz) <= 3){ball.position.y = -100;boat.shoot=0;}
    }

    for(int i=0;i<110;i++)
    {
        if(monster[i].tick(boat, cannon) && monster[i].alive==1)
        {
            if(monster[i].type==1)
                boat.health -= 0.8;
            else
                boat.health -= 1.6;
            boat.speed = -boat.speed/2;
            cannon.speed = -cannon.speed/2;
        }
    }

    if(boat.boss>0 && boss.tick(boat, cannon) && boss.alive==1)
    {
        boat.health -= 5;
        boat.speed = -boat.speed/2;
        cannon.speed = -cannon.speed/2;
    }

    if(boat.health <=0)exit(0);
    char scor[40]={0};
    sprintf(scor, "Points: %d     Health: %.2f", boat.point, boat.health);
    glfwSetWindowTitle(window, scor);

    int chkbarrel = check_barrel();

    if(chkbarrel)
    {
       // cout<<"check barrel"<<endl;
        boat.speedy = 0.012;
        boat.jump = 1;
    }

    boat.tick(check_struck(), monster_struck(), island_struck());
    if(boat.wind>0)
    {
        cannon.wind = boat.wind;
        cannon.speedw = boat.speedw;
        cannon.rotation = boat.rotation;
    }

    cannon.tick();
    cannon.position.x = boat.position.x;
    cannon.position.y = boat.position.y;
    cannon.position.z = boat.position.z;

    //cout<<cannon.speed<<" "<<cannon.speedw<<" "<<boat.speedw<<" "<<boat.speed<<endl;
    //cout<<boat.rotation<<endl;
    for(int i=0;i<100;i++)
    {
        if(rock[i].tick(boat, cannon))
        {
            boat.health -= 0.4;
            boat.speed = -boat.speed/2;
            cannon.speed = -cannon.speed/2;
        }
    }
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    //ball1       = Ball(0, 0, COLOR_RED);
    ocean      = Ocean(0, 0, COLOR_SEABLUE, COLOR_LAWNGREEN);
    //island     = Island(2200, 0, 2200, COLOR_LAWNGREEN);
  //  boat       = Boat(0, 1, 0, COLOR_WOODBROWN);
  //  cannon     = Cannon(0, 1, 0, COLOR_YELLOW);

    boat       = Boat(0, 1, 0, COLOR_WOODBROWN);
    cannon     = Cannon(0, 1, 0, COLOR_YELLOW);
    sail       = Sail(-0.5, 2, 0, COLOR_SAIL);

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            float x,z;
            x = rand()%9900 + 100;
            z = rand()%9900 + 100;
            x = ((float)x)/100.00;
            z = ((float)z)/100.00;
            cout<<x<<" "<<z<<endl;


            float bx, bz;
            bx = rand()%100 - 50;
            bz = rand()%100 - 50;
            bx = bx/3.00;
            bz = bz/3.00;

            if((10*i+j)%4==0)
            {
                barrel[(10*i+j)/4] = Barrel(x+(100.00*i)-500+bx, 0, z+(100.00*j)-500+bz, COLOR_BARREL);
                if(((10*i+j)/4)%5==0)
                    diamond[(10*i+j)/4] = Diamond(x+(100.00*i)-500+bx, 1.6, z+(100.00*j)-500+bz, COLOR_REDD);
                else if(((10*i+j)/4)%5==1)
                    diamond[(10*i+j)/4] = Diamond(x+(100.00*i)-500+bx, 1.6, z+(100.00*j)-500+bz, COLOR_YELD);
                else if(((10*i+j)/4)%5==2)
                    diamond[(10*i+j)/4] = Diamond(x+(100.00*i)-500+bx, 1.6, z+(100.00*j)-500+bz, COLOR_GRND);
                else if(((10*i+j)/4)%5==3)
                    diamond[(10*i+j)/4] = Diamond(x+(100.00*i)-500+bx, 1.6, z+(100.00*j)-500+bz, COLOR_GOLD);
                else if(((10*i+j)/4)%5==4)
                    diamond[(10*i+j)/4] = Diamond(x+(100.00*i)-500+bx, 1.6, z+(100.00*j)-500+bz, COLOR_SILD);
            }

            rock[10*i+j]       = Rock(x+(100.00*i)-500, 0, z+(100.00*j)-500, COLOR_ROCKBROWN);

        }
    }
    gift = Gift(0, -10, -4, 0, COLOR_BLACK);
    boss = Boss(1000000, -1000000, -8, 0, COLOR_BLACK, COLOR_BLACK);
    int k=0;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<2*(i+1);j++)
        {
            float x = rand()%360;
            float m = (rand()%10 + 1)%3;
            if(k%2==0)
                monster[k++]      = Monster(50*(i+1)*(cos(x*m*M_PI/180)), 0, 50*(i+1)*(sin(x*m*M_PI/180)), 1, COLOR_MON, COLOR_MON1);
            else
                monster[k++]      = Monster(50*(i+1)*(cos(x*m*M_PI/180)), 0, 50*(i+1)*(sin(x*m*M_PI/180)), 2, COLOR_MON, COLOR_GOLD);
            cout<<50*(i+1)*(cos(x*m*M_PI/180))<<" "<<50*(i+1)*(sin(x*m*M_PI/180))<<endl;
        }
    }

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            float x,z;
            x = rand()%2400 + 100;
            z = rand()%2400 + 100;
            x = ((float)x)/100.00;
            z = ((float)z)/100.00;
            cout<<x<<" "<<z<<endl;

            tree[8*i+j]       = Tree(x+(25.00*i)+2100, 3, z+(25.00*j)+2100, COLOR_ROCKBROWN, COLOR_TREEGREEN);
        }
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1500;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
            tick_elements();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
