// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main( void )
{
   // Initialize GLFW
   if( !glfwInit() )
   {
       fprintf( stderr, "Failed to initialize GLFW\n" );
       getchar();
       return -1;
   }
   
   glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
   // Open a window and create its OpenGL context
   window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
   if( window == NULL ){
       fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
       getchar();
       glfwTerminate();
       return -1;
   }
   glfwMakeContextCurrent(window);
   
   // Initialize GLEW
   glewExperimental = true; // Needed for core profile
   if (glewInit() != GLEW_OK) {
       fprintf(stderr, "Failed to initialize GLEW\n");
       getchar();
       glfwTerminate();
       return -1;
   }
   
   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
   
   // Dark blue background
   glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


   
   // The VAO
   GLuint VertexArrayID;
   glGenVertexArrays(1, &VertexArrayID);
   glBindVertexArray(VertexArrayID);
   
   // 
   static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
   };
   
   GLuint vertexbuffer;
   
   // generate 1 buffer and put it in vertex buffer
   glGenBuffers(1, &vertexbuffer);
   
   // talk about our vertex buffer
   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   
   // give our vertices to OpenGL
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
   
   
   GLuint programID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");

   // 45 degree field of view displayed between 0.1 and 100 for near and far
   glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

   glm::mat4 View = glm::lookAt(
    glm::vec3(4, 3, 3), // camera position
    glm::vec3(0, 0, 0), // at
    glm::vec3(0, 1, 0) // up direction
   );

   // identity since model at origin
   glm::mat4 Model = glm::mat4(1.0f);
   glm::mat4 MVP = Projection * View * Model;

   GLuint MatrixID = glGetUniformLocation(programID, "MVP");


   do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        // send transform to the current shader
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                            0,        // match layout in the shader
                            3,        // size
                            GL_FLOAT, // type
                            GL_FALSE, // normalized?
                            0,        // stride?
                            (void*)0  // array buffer offset?
                        );
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
   }
   while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

   	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
   
   return 0;
}
