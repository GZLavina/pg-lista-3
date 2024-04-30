#include <iostream>
#include <string>
#include <glad/glad.h>
#include "shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void error_callback(int error, const char *msg);

GLuint ex5();

void drawEx5(Shader *shader);

GLuint ex8();

void drawEx8();

void drawEx1(Shader *shader);

void drawEx2(Shader *shader, float geometryCenter[]);

void drawEx3(Shader *shader, float geometryCenter[], bool directions[], int width, int height);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

std::unordered_map<int, bool> keyMap = {};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

//    Shader shader("../shaders/HelloTriangle.vert", "../shaders/HelloTriangle.frag");
    //Shader para triagulo colorido
    Shader shader("../shaders/HelloTriangle.vert", "../shaders/ColoredTriangle.frag");

//    // dois triangulos com borda e vertice
//    GLuint VAO = ex5();

    // Triangulo colorido
    GLuint VAO = ex8();

    shader.use();

    glm::mat4 projection = glm::ortho(0.0f,800.0f,0.0f,600.0f,-1.0f,1.0f);
    shader.setMat4("projection", glm::value_ptr(projection));

    float geometryCenter[] = {0.0f, 0.0f};
    bool directions[] = {true, true};

    // render loop
    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

//        drawEx1(&shader);
//        drawEx2(&shader, geometryCenter);
        drawEx3(&shader, geometryCenter, directions, width, height);

        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    keyMap[GLFW_KEY_W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    keyMap[GLFW_KEY_A] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    keyMap[GLFW_KEY_S] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    keyMap[GLFW_KEY_D] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}

void error_callback(int error, const char *msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

void drawEx1(Shader *shader) {
    glm::mat4 model = glm::mat4(1); //matriz identidade
    model = glm::translate(model, glm::vec3(400.0, 300.0, 0.0));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(300.0, 300.0, 0.0));
    shader->setMat4("model", glm::value_ptr(model));
    drawEx8();

    glm::mat4 model1 = glm::mat4(1); //matriz identidade
    model1 = glm::translate(model1, glm::vec3(700.0, 300.0, 0.0));
    model1 = glm::scale(model1, glm::vec3(100.0, 100.0, 0.0));
    shader->setMat4("model", glm::value_ptr(model1));
    drawEx8();

    glm::mat4 model2 = glm::mat4(1); //matriz identidade
    model2 = glm::translate(model2, glm::vec3(700.0, 500.0, 0.0));
    model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    model2 = glm::scale(model2, glm::vec3(100.0, 100.0, 0.0));
    shader->setMat4("model", glm::value_ptr(model2));
    drawEx8();
}

void drawEx2(Shader *shader, float geometryCenter[]) {
    if (keyMap[GLFW_KEY_W]) {
        geometryCenter[1] += 0.5f;
    }
    if (keyMap[GLFW_KEY_A]) {
        geometryCenter[0] -= 0.5f;
    }
    if (keyMap[GLFW_KEY_S]) {
        geometryCenter[1] -= 0.5f;
    }
    if (keyMap[GLFW_KEY_D]) {
        geometryCenter[0] += 0.5f;
    }

    glm::mat4 model = glm::mat4(1); //matriz identidade
    model = glm::translate(model, glm::vec3(geometryCenter[0], geometryCenter[1], 0.0));
    model = glm::translate(model, glm::vec3(400.0, 300.0, 0.0));
    model = glm::scale(model, glm::vec3(100.0, 100.0, 0.0));
    shader->setMat4("model", glm::value_ptr(model));
    drawEx8();
}

void drawEx3(Shader *shader, float geometryCenter[], bool directions[], int width, int height) {
    if (geometryCenter[0] + 400 >= (float) width - 50 || geometryCenter[0] + 400 <= 50) {
        directions[0] = !directions[0];
    }
    if (geometryCenter[1] + 300 >= (float) height - 50 || geometryCenter[1] + 300 <= 50) {
        directions[1] = !directions[1];
    }

    geometryCenter[0] += directions[0] ? 0.05f : -0.05f;
    geometryCenter[1] += directions[1] ? 0.05f : -0.05f;

    glm::mat4 model = glm::mat4(1); //matriz identidade
    model = glm::translate(model, glm::vec3(geometryCenter[0], geometryCenter[1], 0.0));
    model = glm::translate(model, glm::vec3(400.0, 300.0, 0.0));
    model = glm::scale(model, glm::vec3(100.0, 100.0, 0.0));
    shader->setMat4("model", glm::value_ptr(model));
    drawEx8();
}

GLuint ex5() {
    GLfloat vertices[] = {
            // Triangle 1
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.0f,  0.0f, 0.0f,
            // Triangle 2
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.0f, 0.0f, 0.0f
    };

    GLuint VBO, VAO;
    //Geração do identificador do VBO
    glGenBuffers(1, &VBO);
    //Faz a conexão (vincula) do buffer como um buffer de array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Envia os dados do array de floats para o buffer da OpenGl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Geração do identificador do VAO (Vertex Array Object)
    glGenVertexArrays(1, &VAO);
    // Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
    // e os ponteiros para os atributos
    glBindVertexArray(VAO);
    // Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando:
    // Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
    // Numero de valores que o atributo tem (por ex, 3 coordenadas xyz)
    // Tipo do dado
    // Se está normalizado (entre zero e um)
    // Tamanho em bytes
    // Deslocamento a partir do byte zero
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    // Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice
    // atualmente vinculado - para que depois possamos desvincular com segurança
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
    glBindVertexArray(0);

    return VAO;
}

void drawEx5(Shader *shader) {
    glLineWidth(10);
    glPointSize(20);

    // Triangulos preenchidos
    shader->setVec4("inputColor", 0.0f, 0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    // Contornos
    shader->setVec4("inputColor", 0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glDrawArrays(GL_LINE_LOOP, 3, 3);

    // Pontos
    shader->setVec4("inputColor", 1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_POINTS, 0, 6);
}

GLuint ex8() {
    GLfloat vertices[] = {
            // positions        // colors
            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f   // top
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    return VAO;
}

void drawEx8() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
