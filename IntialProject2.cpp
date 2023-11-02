#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<math.h>
#include <cmath>


#include "Util.h"


using namespace std;

float color1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float color2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float color3[] = { 0.0f, 0.0f, 1.0f, 1.0f };

unsigned int program;
GLint color1Loc, color2Loc, color3Loc;
GLint currentSecondPointerLoc, currentMinutePointerLoc, currentHourPointerLoc;


float velocitySecondPointer = -3.0f;
float velocityMinutePointer = -0.05f;
float velocityHourPointer = -0.004167;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;
float speedUp = 1.0f;

float pi = 3.14159265f;
float derajat = 180.0f;

float konversiRadian = pi / derajat;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        float userJam, userMenit, userDetik;

        cout << "Masukkan Detail Jam Yang Anda Inginkan" << endl;
        cout << "Jam Berapa  : ";
        cin >> userJam;

        cout << "Menit Berapa : ";
        cin >> userMenit;

        cout << "Detik Berapa : ";
        cin >> userDetik;

        float hour = userJam * 3600;
        float minute = userMenit * 60;
        float second = userDetik;

        glfwSetTime(hour + minute + second);
    }


    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        glfwSetTime(currentTime + 60);
    }

    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        glfwSetTime(currentTime + 3600);
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        glfwSetTime(currentTime - 60);
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        glfwSetTime(currentTime - 3600);
    }

    if (key == GLFW_KEY_U && action == GLFW_PRESS) {
        speedUp += 2.0f;
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        speedUp = 1.0f;
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        for (int i = 0; i < 4;i++) {
            color1[i] = (rand() * 1.0f)/RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;

        }

        cout << color1[0] << " " << color1[1] << color1[2] << " " << color1[3] << endl;
        cout << color2[0] << " " << color2[1] << color2[2] << " " << color2[3] << endl;
        cout << color3[0] << " " << color3[1] << color3[2] << " " << color3[3] << endl;
    
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
    }

   

   

  
   
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "JAM DIGITAL - UTS GRAFIKA KOMPUTER", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();


    float vertices[] = {
        1.0, 1.0,
        -1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0

    };

    unsigned int indexArr[] = {
       0,1,2,
       0,2,3

    };



    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    cout<< vertexBuffer <<endl;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);


    unsigned indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexArr, GL_STATIC_DRAW);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);

    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    color3Loc = glGetUniformLocation(program, "color3");
    glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);

    currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime)*speedUp;
        lastTime = currentTime;

        currentSecondPointer = currentSecondPointer + (deltaTime * velocitySecondPointer);
        currentMinutePointer = currentMinutePointer + (deltaTime * velocityMinutePointer);
        currentHourPointer = currentHourPointer + (deltaTime* velocityHourPointer);

        glUniform1f(currentSecondPointerLoc, currentSecondPointer * konversiRadian);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer * konversiRadian);
        glUniform1f(currentHourPointerLoc, currentHourPointer * konversiRadian);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
       

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}