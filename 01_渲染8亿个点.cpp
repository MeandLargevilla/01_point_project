#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include"common.h"
#include"point.h"
//point生成个数
#define count 1000
//point结构体输出函数
std::ostream& operator<<(std::ostream& os, const point& p) {
    return os << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.m1 << ", " << p.m2 << ")";
}
//片段着色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n" // 输出最终颜色
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // 暂时统一涂成橘黄色\n"
"}\n\0";

//顶点着色器
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // 读入 0 号属性（坐标）
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // 确定点在 3D 空间的位置
"}\0";

int main() {
    //创建point结构体的vector
    std::vector<point> pts = creatpoints(count);
    //输出全部点
    std::cout << "我拿到了" << pts.size() << "个点\n";
    for (const auto& p : pts) std::cout << p << "\n ";







    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Setup Test", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 1. 定义两个身份证号
    unsigned int VBO; // Vertex Buffer Object (顶点缓冲对象 - 仓库)
    unsigned int VAO; // Vertex Array Object (顶点数组对象 - 说明书)

    // 2. 让显卡生成这些 ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 3. 激活说明书（接下来所有的设置都会记录在这个 VAO 里）
    glBindVertexArray(VAO);

    // 绑定仓库
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 搬运：把 vector 里的数据复制到显卡
    glBufferData(GL_ARRAY_BUFFER,
        pts.size() * sizeof(point), // 总字节数：点数 * 每个点的大小
        pts.data(),                // 数据真正的开头位置
        GL_STATIC_DRAW);                 // 告诉显卡：这些点我不打算常改，请优化读取速度

    // 告诉显卡：0 号属性是坐标
    glVertexAttribPointer(
        0,                  // 编号：对应以后 Shader 里的 location = 0
        3,                  // 数量：坐标有 3 个数 (x, y, z)
        GL_FLOAT,           // 类型：都是 float
        GL_TRUE,           // 是否归一化：是
        5 * sizeof(float),  // 步长 (Stride)：每隔 5 个 float 读下一个点
        (void*)0            // 偏移 (Offset)：坐标从每个点的第 0 个位置开始读
    );

    // 启用这个 0 号属性
    glEnableVertexAttribArray(0);

    // 1. 创建并编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 2. 创建并编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 3. 创建一个“程序对象”（把两个着色器打包在一起）
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // 链接

    // 4. 链接完就可以把单体删了，省内存
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // 1. 绑定你的说明书
        glBindVertexArray(VAO);

        // 2. 设置点的大小（让你在 Mac 屏幕上看得清楚）
        glPointSize(5.0f);

        // 3. 命令显卡：画！
        // 格式：glDrawArrays(形状, 开始位置, 点的数量);
        glDrawArrays(GL_POINTS, 0, (GLsizei)pts.size());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
