# 实验3：连连看游戏实践

在实验课的要求中，本应使用 MFC 框架去构建，但是由于本人主要使用 macOS 系统，加之 MFC 框架实在是过于陈旧，所以考虑使用 Qt 来实现相同的界面逻辑。为了使本项目可以正常运行，请确保
- 你已经正确配置了 CLion
- 你已经安装了 Qt
- 系统为 macOS

如果不满足上述条件，虽然 Qt 是跨平台的，但也不确保能正常运行。在编写本项目时，环境如下：
- macOS 15.0.1
- Qt 6.8.2
- CLion 2024.2

## 需要修改的地方

标 `*` 的必改，否则跑不起来或者无法正常运行。

`*` CMakeLists.txt:9

```cpp
set(CMAKE_PREFIX_PATH "/path/to/cmake")
```
将 `/path/to/cmake` 修改为你系统上的 Qt cmake 所在的位置，例如 `/Users/username/Qt/6.8.2/macos/lib/cmake`。

`*` GlobalData.h:8

```cpp
#define BG_FILE "resources/fruit_bg.bmp"
```

将该路径更换为 `fruit_bg.bmp` 文件的绝对路径。

`*` GlobalData.cpp:4
```cpp
recordManager = new RecordManager("records.txt");
```

将该路径更换为一个绝对路径。

`*` mainwindow.cpp:9
```cpp
setBackground(this, "resources/llk_main.bmp");
```
将该路径更换为一个绝对路径。

`*` Game.cpp:13,14

```cpp
const QImage elementImage("resources/fruit_element.bmp");
const QImage maskImage("resources/fruit_mask.bmp");
```
将这些路径更换为绝对路径。

test.cpp:215,244,277

```cpp
ofstream testoutput("map-rates." + std::to_string(rate) + ".txt");

ofstream testoutput("map." + std::to_string(rate) + ".txt");

auto manager = RecordManager("records-test.txt");
```

将这些路径更换为恰当的绝对路径。如果你不需要测试这些数据，可以忽略。