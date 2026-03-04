@echo off
setlocal enabledelayedexpansion

REM Usage:
REM   build.bat                (Debug)
REM   build.bat Release
REM   build.bat Debug --run
REM   build.bat Release --test
REM   build.bat Debug --clean

set CONFIG=%1
if "%CONFIG%"=="" set CONFIG=Debug
shift

set RUN=0
set TEST=0
set CLEAN=0

:parse
if "%~1"=="" goto parsed
if "%~1"=="--run" (set RUN=1 & shift & goto parse)
if "%~1"=="--test" (set TEST=1 & shift & goto parse)
if "%~1"=="--clean" (set CLEAN=1 & shift & goto parse)
if "%~1"=="-h" goto help
if "%~1"=="--help" goto help

echo Unknown arg: %~1
exit /b 2

:parsed
where cmake >nul 2>nul
if errorlevel 1 (
  echo cmake not found on PATH. Install CMake to build from source.
  exit /b 127
)

set BUILD_DIR=build\%CONFIG%

if %CLEAN%==1 (
  echo [clean] Removing %BUILD_DIR%
  if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
)

echo [configure] %CONFIG% ^> %BUILD_DIR%
cmake -S . -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=%CONFIG%
if errorlevel 1 exit /b %errorlevel%

echo [build] %CONFIG%
cmake --build "%BUILD_DIR%" --parallel --config %CONFIG%
if errorlevel 1 exit /b %errorlevel%

if %TEST%==1 (
  echo [test]
  ctest --test-dir "%BUILD_DIR%" --output-on-failure -C %CONFIG%
  if errorlevel 1 exit /b %errorlevel%
)

if %RUN%==1 (
  set EXE=%BUILD_DIR%\HexPip.exe
  if exist "!EXE!" (
    echo [run] !EXE!
    pushd "%BUILD_DIR%"
    HexPip.exe
    popd
  ) else (
    set EXE=%BUILD_DIR%\%CONFIG%\HexPip.exe
    if exist "!EXE!" (
      echo [run] !EXE!
      pushd "%BUILD_DIR%\%CONFIG%"
      HexPip.exe
      popd
    ) else (
      echo Could not find built executable. Look inside %BUILD_DIR%.
      exit /b 1
    )
  )
)

exit /b 0

:help
type %~f0
exit /b 0
