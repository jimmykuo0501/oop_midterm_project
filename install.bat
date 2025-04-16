@echo off
echo Starting project initialization and build process...

:: 建立build目錄
if not exist build (
    echo Creating build directory...
    mkdir build
) else (
    echo Build directory already exists.
)
cd build

:: 下載並解壓縮CMake
echo Downloading CMake...
curl -L -o cmake.zip https://github.com/Kitware/CMake/releases/download/v3.31.7/cmake-3.31.7-windows-x86_64.zip
echo Extracting CMake...
powershell -command "Expand-Archive -Force -Path cmake.zip -DestinationPath ."
echo CMake extracted successfully.

:: 使用CMake初始化和編譯專案
echo Initializing project with CMake...
.\cmake-3.31.7-windows-x86_64\bin\cmake.exe .. -DCMAKE_BUILD_TYPE=Release

echo Building project...
.\cmake-3.31.7-windows-x86_64\bin\cmake.exe --build . --config Release --parallel

:: 檢查編譯是否成功
if exist bin\ (
    echo Build completed successfully!
    echo Executable can be found at: .\build\bin\
) else (
    echo Build may have failed. Please check for errors.
)

:: 返回到原始目錄
cd ..

echo Process completed.
pause