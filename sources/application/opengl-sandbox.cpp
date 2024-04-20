#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <renderer.h>
#include <vertex_buffer.h>
#include <index_buffer.h>
#include <vertex_array.h>
#include <shader.h>
#include <texture.h>

static void FrameBufferResizeCallback(GLFWwindow* window, int fbW, int fbH) {
    glViewport(0, 0, fbW, fbH);
}

int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
   
    /* Set up OpenGL version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    /* Create a window */
    GLFWwindow* window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);

    /* Check if window have not created */
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make window resizeable */
    glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // vsync

    /* Always after making valid context */
    if (glewInit() != GLEW_OK)
        return -1;

    /* OpenGL options */
    //glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float positions[] = {
        0.0f  , 0.0f  , 0.0f, 0.0f,   // 0
        200.0f, 0.0f  , 1.0f, 0.0f,   // 1
        200.0f, 200.0f, 1.0f, 1.0f,   // 2
        0.0f  , 200.0f, 0.0f, 1.0f    // 3
    };

    // index buffer
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    /* Vertex array object */
    vertex_array vao;

    /* Vertex buffer object */
    vertex_buffer vbo(positions, 4 * 4 * sizeof(float));
    
    /* Adding atributes to the buffer */
    vertex_buffer_layout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    vao.add_buffer(vbo, layout);
    
    /* Index buffer object */
    index_buffer ibo(indices, 6);

    /* Model view projection */
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    glm::vec3 translationA(100, 0, 0);
    glm::vec3 translationB(400, 0, 0);

    /* Load shader */
    shader basic_shader("C:\\dev\\opengl-sandbox\\res\\shaders\\basic.glsl");
    basic_shader.bind();

    /* Textures */
    texture tex("C:\\dev\\opengl-sandbox\\res\\textures\\cubes.png");
    tex.bind();
    basic_shader.set_uniform1i("u_Texture", 0);

    /* Unbinding everything */
    vao.unbind();
    basic_shader.unbind();

    /* Renderer */
    renderer render;

    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Clear frame */
        render.clear();

        /* Draw */
        basic_shader.bind();
        glm::mat4 common_mvp = proj * view;

        /* First model */
        glm::mat4 modelA = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvpA = common_mvp * modelA;
        basic_shader.set_uniformMat4f("u_MVP", mvpA);
        render.draw(vao, ibo, basic_shader);

        /* Second model */
        glm::mat4 modelB = glm::translate(glm::mat4(1.0f), translationB);
        glm::mat4 mvpB = common_mvp * modelB;
        basic_shader.set_uniformMat4f("u_MVP", mvpB);
        render.draw(vao, ibo, basic_shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
