#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

float angle=0.0;
int board[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
int x = 1, y = 1;

int player = 0;

int winner = 0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void verifyBoard() {
    int counter = 0;
    int initial;
    for(int i = 0; i < 3; i++) {
        initial = board[i][0];
        for (int j = 0; j < 3; j++) {
            if(board[i][j] != initial) {
                counter = 0;
                break;
            }
            else {
                ++counter;
                if (counter == 3) {
                        winner = initial;
                        return;
                }
            }
        }
    }

    for(int j = 0; j < 3; j++) {
        initial = board[0][j];
        for (int i = 0; i < 3; i++) {
            if(board[i][j] != initial) {
                counter = 0;
                break;
            }
            else {
                ++counter;
                if (counter == 3) {
                        winner = initial;
                        return;
                }
            }
        }
    }

    initial = board[0][0];
    for (int i = 0; i < 3; i++) {
        int j = i;
        if (board[i][j] != initial) {
            counter = 0;
            break;
        }
        else {
            counter++;
            if (counter == 3) {
                    winner = initial;
            return;
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle,0.0,0.0,1.0);
    glColor3f(0.752941, 0.752941, 0.752941);
    double initialX = -2, initialY = 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            if (winner == -1) {
                glColor3f(0, 1, 0);
            }
            else if (winner == 1) {
                glColor3f(1.0, 0.0, 0.0);
            }
            else if (x == i && y == j && board[i][j] == 0)
            {
                glColor3f(0.184314, 0.309804, 0.309804);
            }
            else if (x == i && y == j && board[i][j] == -1) {
                glColor3f(0, 1, 0);
            }
            else if (x == i && y == j && board[i][j] == 1) {
                glColor3f(1.0, 0.0, 0.0);
            }
            else if (board[i][j] == -1) {
                glColor3f(0.419608, 0.556863, 0.137255);
            }
            else if (board[i][j] == 1) {
                glColor3f(0.5, 0.0, 0.0);
            }
            else {
                glColor3f(0.752941, 0.752941, 0.752941);
            }
            glBegin(GL_QUADS);
            glVertex3f( initialX, initialY, -5.0);
            glVertex3f(initialX, initialY - 1, -5.0);
            glVertex3f( initialX + 1, initialY - 1, -5.0);
            glVertex3f( initialX + 1, initialY, -5.0);
            glEnd();
            initialX += 1.5;
        }
        initialY -= 1.5;
        initialX = -2;
    }
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    init();
    while (loop==1)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym==SDLK_LEFT && y > 0) {
                    y -= 1;
                }
                else if (myevent.key.keysym.sym==SDLK_RIGHT && y < 2)
                {
                    y += 1;
                }
                else if (myevent.key.keysym.sym==SDLK_UP && x > 0) {
                    x -= 1;
                }
                else if (myevent.key.keysym.sym==SDLK_DOWN && x < 2) {
                    x += 1;
                }

                if(myevent.key.keysym.sym == SDLK_SPACE && board[x][y] == 0) {
                        if (player == 0)
                        {
                            board[x][y] = -1;
                        }
                        else
                        {
                             board[x][y] = 1;
                        }
                        verifyBoard();
                        player = !player;
                }

                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
