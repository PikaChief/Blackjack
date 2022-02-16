@echo off

rem ##############################################################
rem This batch script must be run from Visual Studio's 
rem "Developer Command Prompt for VS XXXX" or as a Visual Studio
rem Pre-Built Event within the project's properties with the 
rem command line:
rem     call "$(ProjectDir)tools\install_sdl_visual_c.bat"
rem
rem This batch script assumes by default that
rem 1. it is located your project's rem "tools" (or as another 
rem    name) directory
rem 2. your project directory is located under the solution's directory. 
rem        ex: SolDir\MyProj\tools\install_sdl_visual_c.bat
rem 3. SDL directory (as a git submodule) is in the "Dependencies" 
rem    directory which is under the solution's directory (and 
rem    sibling to your project(s))
rem        ex: SolDir\Dependencies\SDL
rem
rem Edit the following lines to reflect your environment and make
rem sure Git (git.exe) is installed and in your PATH
rem ##############################################################

rem #########          Edit here if necessary           ##########
rem Relative path to SDL directory from .sln file's directory (no leading or trailing slash)
set sol_to_sdl_dir=Dependencies\SDL

rem Git tag/commmit hash/branch for the SDL version to use
set sdl_version_tag=release-2.0.20
rem ##############################################################


rem Detecting Platform
reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32BIT || set OS=64BIT


set script_dir=%~dp0
pushd %~dp0..\..
set sol_dir=%CD%
set sdl_dir=%sol_dir%\%sol_to_sdl_dir%
set install_dir=%sol_dir%\%sol_to_sdl_dir%\VisualC
popd

rem Looking in SDL git submodule directory...
set _git_submod=F
pushd %sdl_dir%
for %%X in (git.exe) do (set _GIT_FOUND=%%~$PATH:X)
if defined _GIT_FOUND (
    echo git.exe found
) else (
    echo git.exe not found in PATH!
)
if exist .git\config (
    set _git_submod=T
    echo SDL git submodule found!
) else (
    echo No SDL git submodule found!
)
popd

if "%_git_submod%"=="F" if defined _GIT_FOUND (
    echo Updating SDL git submodule...
    pushd %sdl_dir%
    git submodule update --init
    git checkout %sdl_version_tag%
    popd
)
pushd %sol_dir%

pushd %install_dir%
echo Looking for necessary SDL libraries from %install_dir%\SDL.sln

echo Checking %install_dir%\Win32\Debug
set d32=F
if not exist %install_dir%\Win32\Debug\SDL2.dll (
    set d32=T
    echo SDL2.dll not found, attempting to build
)
if not exist %install_dir%\Win32\Debug\SDL2.lib (
    set d32=T
    echo SDL2.lib not found, attempting to build
)
if not exist %install_dir%\Win32\Debug\SDL2main.lib (
    set d32=T
    echo SDL2main.lib not found, attempting to build
)
if not exist %install_dir%\Win32\Debug\SDL2test.lib (
    set d32=T
    echo SDL2test.lib not found, attempting to build
)
if "%d32%"=="T" (
    devenv.exe SDL.sln /Build "Debug|Win32"
) else (
    echo SDL2.dll, SDL2.lib, SDL2main.lib, and SDL2test.lib found, skipping build
)

echo Checking %install_dir%\Win32\Release
set r32=F
if not exist %install_dir%\Win32\Release\SDL2.dll (
    set r32=T
    echo SDL2.dll not found, attempting to build
)
if not exist %install_dir%\Win32\Release\SDL2.lib (
    set r32=T
    echo SDL2.lib not found, attempting to build
)
if not exist %install_dir%\Win32\Release\SDL2main.lib (
    set r32=T
    echo SDL2main.lib not found, attempting to build
)
if not exist %install_dir%\Win32\Release\SDL2test.lib (
    set r32=T
    echo SDL2test.lib not found, attempting to build
)
if "%r32%"=="T" (
    devenv.exe SDL.sln /Build "Release|Win32"
) else (
    echo SDL2.dll, SDL2.lib, SDL2main.lib, and SDL2test.lib found, skipping build
)

echo Checking %install_dir%\x64\Debug\
set d64=F
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Debug\SDL2.dll (
    set d64=T
    echo SDL2.dll not found, attempting to build
)
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Debug\SDL2.lib (
    set d64=T
    echo SDL2.lib not found, attempting to build
)
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Debug\SDL2main.lib (
    set d64=T
    echo SDL2main.lib not found, attempting to build
)
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Debug\SDL2test.lib (
    set d64=T
    echo SDL2test.lib not found, attempting to build
)
if %d64%==T (
    devenv.exe SDL.sln /Build "Debug|x64" 
) else (
    echo SDL2.dll, SDL2.lib, SDL2main.lib, and SDL2test.lib found, skipping build
)

echo Checking %install_dir%\x64\Release\
set r64=F
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Release\SDL2.dll (
    set r64=T
    echo SDL2.dll not found, attempting to build
)
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Release\SDL2.lib (
    set r64=T
    echo SDL2.lib not found, attempting to build
)
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Release\SDL2main.lib (
    set r64=T
    echo SDL2main.lib not found, attempting to build
)
if "%OS%"=="64BIT" if not exist %install_dir%\x64\Release\SDL2test.lib (
    set r64=T
    echo SDL2test.lib not found, attempting to build
)
if "%r64%"=="T" (
    devenv.exe SDL.sln /Build "Release|x64" 
) else (
    echo SDL2.dll, SDL2.lib, SDL2main.lib, and SDL2test.lib found, skipping build
)
popd