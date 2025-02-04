# Integrating VTK into Qt Designer on Ubuntu

## Overview
This guide provides step-by-step instructions to integrate VTK (Visualization Toolkit) into Qt Designer on an Ubuntu system. This allows developers to utilize VTK widgets within Qt-based applications.

## Prerequisites
Ensure you have the following installed on your system:
- Ubuntu 20.04 or later
- Qt 5 or Qt 6 (including Qt Creator and Qt Designer)
- VTK (Version 9.3+ recommended)
- CMake and GCC
- Qt Plugin Development Packages

## Step 1: Install Required Dependencies
```sh
sudo apt update && sudo apt install -y qtbase5-dev qttools5-dev qttools5-dev-tools libqt5svg5-dev cmake g++ libvtk9-dev
```

## Step 2: Build VTK with Qt Support
If VTK is not installed with Qt support, you need to compile it manually:
```sh
git clone https://gitlab.kitware.com/vtk/vtk.git
cd vtk
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DVTK_QT_VERSION=5 -DVTK_Group_Qt=ON -DVTK_MODULE_ENABLE_VTK_GUISupportQt=YES -DVTK_MODULE_ENABLE_VTK_RenderingQt=YES -DQt5_DIR=/usr/lib/cmake/Qt5
make -j$(nproc)
sudo make install
```

## Step 3: Create a Qt Plugin for VTK Widgets
1. Create a new directory:
   ```sh
   mkdir -p ~/vtk_qt_plugin && cd ~/vtk_qt_plugin
   ```
2. Create `qvtkplugin.cpp`:
   ```cpp
   #include <QtUiPlugin/QDesignerCustomWidgetInterface>
   #include <QVTKOpenGLNativeWidget.h>
   
   class QVTKPlugin : public QObject, public QDesignerCustomWidgetInterface {
       Q_OBJECT
       Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
       Q_INTERFACES(QDesignerCustomWidgetInterface)
   public:
       QVTKPlugin(QObject *parent = nullptr) : QObject(parent) {}
       QString name() const override { return "QVTKOpenGLNativeWidget"; }
       QString group() const override { return "VTK Widgets"; }
       QString toolTip() const override { return "VTK-based OpenGL Widget"; }
       QString whatsThis() const override { return "VTK widget for Qt Designer"; }
       QWidget *createWidget(QWidget *parent) override { return new QVTKOpenGLNativeWidget(parent); }
       bool isContainer() const override { return false; }
   };
   ```

3. Create `CMakeLists.txt`:
   ```cmake
   cmake_minimum_required(VERSION 3.8)
   project(qvtkplugin)

   find_package(Qt5 COMPONENTS Widgets Designer REQUIRED)
   find_package(VTK REQUIRED)

   add_library(qvtkplugin SHARED qvtkplugin.cpp)
   target_link_libraries(qvtkplugin Qt5::Widgets Qt5::Designer ${VTK_LIBRARIES})
   install(TARGETS qvtkplugin DESTINATION ~/.designer/plugins)
   ```

4. Compile and install:
   ```sh
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   make install
   ```

## Step 4: Load Plugin in Qt Designer
1. Open Qt Designer:
   ```sh
   designer
   ```
2. Navigate to `Tools > Form Editor > Widget Box`.
3. Click `Add Plugin` and select `qvtkplugin`.
4. Drag and drop `QVTKOpenGLNativeWidget` into your UI.

## Conclusion
You have successfully integrated VTK into Qt Designer, enabling direct manipulation of VTK widgets within Qt applications on Ubuntu.

