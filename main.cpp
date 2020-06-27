#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }

    return ShaderProgramSource{ss[0].str(), ss[1].str()};
}

static unsigned int compileShader(unsigned int type, const std::string& source) {
     unsigned int id = glCreateShader(type);
     const char* src = source.c_str();
     glShaderSource(id, 1, &src, nullptr);
     glCompileShader(id);

     int result;
     glGetShaderiv(id, GL_COMPILE_STATUS, &result);
     if (result == GL_FALSE) {
         int length;
         glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
         char* message = (char*) alloca(length * sizeof(char));
         glGetShaderInfoLog(id, length, &length, message);

         std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"  << std::endl;
         std::cout << message << std::endl;
         glDeleteShader(id);
         return 0;
     }

     return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    auto program = glCreateProgram();

    auto vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    auto fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // OpenGL Context
    glfwMakeContextCurrent(window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    // glew!
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

#define VERTEX_ARRAY_SIZE 8

    const float positions[VERTEX_ARRAY_SIZE] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            // new vertex for second triangle
            -0.5f, 0.5f,
    };
    // this is index buffer
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE * sizeof(float), positions, GL_STATIC_DRAW);
#undef VERTEX_ARRAY_SIZE

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    auto shaderProg = ParseShader("C:\\Users\\Kirill\\CLionProjects\\OpenGL\\res\\shaders\\Basic.shader");
    unsigned int shader = CreateShader(shaderProg.VertexSource, shaderProg.FragmentSource);
    glUseProgram(shader);

    // Loop until window is closed
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glDeleteProgram(shader);

    return 0;
}
