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
"layout (location = 0) in vec2 rawData;\n"  // 仅仅读入文件里的 2 个原始 float
"uniform float t_y;\n"                      // CPU 传进来的变量
"uniform float t_z;\n"
"void main()\n"
"{\n"
"   int i = gl_VertexID;\n"                 // 拿到当前顶点的序号
	// 计算坐标：根据序号算出 x, y, z
    "   float x = float(i / int(t_y * t_z));\n"
    "   float y = float(i % int(t_y));\n"
    "   float z = float(i / int(t_y) % int(t_z));\n"

    // 最终告诉显卡：这就是坐标！
    "   gl_Position = vec4(x*0.1, y*0.1, z*0.1, 1.0);\n"
    "}\0";

int main() {
    //创建float的vector
    std::vector<float> mms = creatmm(count);
    //输出全部点
    std::cout << "我拿到了" << mms.size() / 2 << "个点\n";
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
        mms.size() * sizeof(float), // 总字节数：点数 * 每个点的大小
        mms.data(),                // 数据真正的开头位置
        GL_STATIC_DRAW);                 // 告诉显卡：这些点我不打算常改，请优化读取速度

    // 告诉显卡：0 号属性
    glVertexAttribPointer(
        0,                  // 编号：对应以后 Shader 里的 location = 0
        1,                  // 数量：m1
        GL_FLOAT,           // 类型：都是 float
        GL_TRUE,           // 是否归一化：是
        2* sizeof(float),  // 步长 (Stride)：每隔 2个 float 读下一个点
        (void*)0            // 偏移 (Offset)：坐标从每个点的第 0 个位置开始读
    );
    glVertexAttribPointer(
        1,                  // 编号：对应以后 Shader 里的 location = 1
        1,                  // 数量：m2
        GL_FLOAT,           // 类型：都是 float
        GL_TRUE,           // 是否归一化：是
        2 * sizeof(float),  // 步长 (Stride)：每隔 2 个 float 读下一个点
        (void*)(sizeof(float)*1)           // 偏移 (Offset)：坐标从第一个float数据后开始读
    );

    // 启用这个 0 号属性
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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
        // 获取变量在 Shader 中的“地址”
        GLint tyLoc = glGetUniformLocation(shaderProgram, "t_y");
        GLint tzLoc = glGetUniformLocation(shaderProgram, "t_z");

        // 传入你之前定义好的 t_y 和 t_z 的值 (假设它们是 float)
        glUniform1f(tyLoc, t_y);
        glUniform1f(tzLoc, t_z); 

        // 1. 绑定你的说明书
        glBindVertexArray(VAO);

        // 2. 设置点的大小（让你在 Mac 屏幕上看得清楚）
        glPointSize(5.0f);

        // 3. 命令显卡：画！
        // 格式：glDrawArrays(形状, 开始位置, 点的数量);
        glDrawArrays(GL_POINTS, 0, (GLsizei)(mms.size() / 2));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
