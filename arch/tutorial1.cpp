//// io stuff
//#include <stdio.h>
//#include <stdlib.h>
//
//#include<GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//using namespace glm;
//
//int main() {
//    glewExperimental = true;
//    if (!glfwInit()) {
//        fprintf(stderr, "Failed to intialize GLFW\n");
//        return -1;
//    }
//    
//    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Open GL 3.3
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // make MacOS chill out
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // don't open old OpenGL
//    
//    GLFWwindow* window;
//    window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
//    if (window == NULL) {
//        fprintf(stderr, "Failed to open OpenGL Window");
//        glfwTerminate();
//        return -1;
//    }
//    
//    glfwMakeContextCurrent(window); // init GLEW
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        fprintf(stderr, "Failed to init GLEW\n");
//        return -1;
//    }
//    
//    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // capture escape key
//    do {
//        glClear(GL_COLOR_BUFFER_BIT);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
//}
//
//
