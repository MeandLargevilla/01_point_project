# GLAD 和 GLFW 配置指南

## 目录结构

已为你创建以下目录结构：

```
3rdparty/
├── glfw/
│   ├── include/
│   │   └── GLFW/
│   │       └── glfw3.h
│   └── lib-vc145/
│       ├── x86/         (32位Debug/Release库文件放这里)
│       ├── x64/         (64位Debug/Release库文件放这里)
│       └── arm64/       (ARM64库文件放这里)
└── glad/
    ├── include/
    │   ├── glad.h
    │   └── glad/
    │       └── gl.h
    └── src/
        └── glad.c
```

## 配置方式

### 方式1：使用属性表（推荐）

1. 在 Visual Studio 中打开你的项目
2. 右键点击项目 → **属性** → **属性管理器**
3. 对于所有配置，导入 `3rdparty/GladGlfw.props` 文件
4. 这样会自动为所有配置添加包含目录和链接依赖

### 方式2：手动配置

如果不想使用属性表，手动配置如下：

**包含目录（项目属性 → C/C++ → 常规 → 附加包含目录）：**
```
$(ProjectDir)3rdparty\glfw\include
$(ProjectDir)3rdparty\glad\include
```

**库目录（项目属性 → 链接器 → 常规 → 附加库目录）：**
```
$(ProjectDir)3rdparty\glfw\lib-vc145\x86       (Win32)
$(ProjectDir)3rdparty\glfw\lib-vc145\x64       (x64)
$(ProjectDir)3rdparty\glfw\lib-vc145\arm64     (ARM64)
```

**链接依赖（项目属性 → 链接器 → 输入 → 附加依赖）：**
```
glfw3.lib;opengl32.lib;
```

## 获取库文件

### GLFW 库文件

1. 下载预编译的 GLFW 库：https://www.glfw.org/download.html
2. 选择 Windows pre-compiled binaries
3. 解压后将对应的 .lib 文件放入：
   - `3rdparty/glfw/lib-vc145/x86/` (32位库)
   - `3rdparty/glfw/lib-vc145/x64/` (64位库)

### GLAD 库文件

1. 访问 https://glad.dav1d.de/
2. 选择 OpenGL 版本（如4.6）
3. 选择 Profile: Core
4. 生成并下载
5. 将生成的文件放入对应目录

或者你也可以编译 GLAD 源文件 `3rdparty/glad/src/glad.c`

## 项目包含头文件

在你的代码中，使用以下方式包含：

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```

## 优势

✅ 所有依赖都在项目文件夹中
✅ 新成员拉下代码后直接可以编译运行
✅ 支持多个平台和架构
✅ 使用相对路径，便于版本控制

## 注意事项

- 确保库文件与 Visual Studio 工具集匹配（v145 = VS 2022）
- x86 和 x64 库文件需要分别放在对应的目录
- 所有 3rdparty 文件夹应该提交到 Git
