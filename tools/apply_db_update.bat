@echo off
chcp 65001 > nul
echo ========================================
echo  数据库更新应用工具
echo ========================================
echo.

REM ============================================================
REM 配置区域 - 请根据实际情况修改
REM ============================================================
set MYSQL="D:\2025wowOVER\wow10x\DraconicWoW\65727Precompiled\bin\RelWithDebInfo\UniServerZ\core\mysql\bin\mysql.exe"
set USER=root
set PASS=admin
set HOST=127.0.0.1
set SQL_DIR=%~dp0..\sql\updates
REM ============================================================

echo 请选择要更新的数据库:
echo [1] Auth 数据库
echo [2] Characters 数据库  
echo [3] World 数据库
echo [4] Hotfixes 数据库
echo [5] 退出
echo.
set /p choice="请输入选项 (1-5): "

if "%choice%"=="1" goto auth
if "%choice%"=="2" goto characters
if "%choice%"=="3" goto world
if "%choice%"=="4" goto hotfixes
if "%choice%"=="5" goto end

:auth
echo.
echo 可用的 Auth 更新文件:
dir /b "%SQL_DIR%\auth\master\*.sql" 2>nul
if errorlevel 1 dir /b "%SQL_DIR%\auth\*.sql" 2>nul
echo.
set /p sqlfile="请输入要应用的 SQL 文件名 (或输入 q 退出): "
if "%sqlfile%"=="q" goto end
if exist "%SQL_DIR%\auth\master\%sqlfile%" (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% auth < "%SQL_DIR%\auth\master\%sqlfile%"
) else (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% auth < "%SQL_DIR%\auth\%sqlfile%"
)
if %errorlevel%==0 (
    echo [成功] 已应用: %sqlfile%
) else (
    echo [警告] 可能有错误，请检查上方输出
)
pause
goto end

:characters
echo.
echo 可用的 Characters 更新文件:
dir /b "%SQL_DIR%\characters\master\*.sql" 2>nul
if errorlevel 1 dir /b "%SQL_DIR%\characters\*.sql" 2>nul
echo.
set /p sqlfile="请输入要应用的 SQL 文件名 (或输入 q 退出): "
if "%sqlfile%"=="q" goto end
if exist "%SQL_DIR%\characters\master\%sqlfile%" (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% characters < "%SQL_DIR%\characters\master\%sqlfile%"
) else (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% characters < "%SQL_DIR%\characters\%sqlfile%"
)
if %errorlevel%==0 (
    echo [成功] 已应用: %sqlfile%
) else (
    echo [警告] 可能有错误，请检查上方输出
)
pause
goto end

:world
echo.
echo 可用的 World 更新文件:
dir /b "%SQL_DIR%\world\master\*.sql" 2>nul
if errorlevel 1 dir /b "%SQL_DIR%\world\*.sql" 2>nul
echo.
set /p sqlfile="请输入要应用的 SQL 文件名 (或输入 q 退出): "
if "%sqlfile%"=="q" goto end
if exist "%SQL_DIR%\world\master\%sqlfile%" (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% world < "%SQL_DIR%\world\master\%sqlfile%"
) else (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% world < "%SQL_DIR%\world\%sqlfile%"
)
if %errorlevel%==0 (
    echo [成功] 已应用: %sqlfile%
) else (
    echo [警告] 可能有错误，请检查上方输出
)
pause
goto end

:hotfixes
echo.
echo 可用的 Hotfixes 更新文件:
dir /b "%SQL_DIR%\hotfixes\master\*.sql" 2>nul
if errorlevel 1 dir /b "%SQL_DIR%\hotfixes\*.sql" 2>nul
echo.
set /p sqlfile="请输入要应用的 SQL 文件名 (或输入 q 退出): "
if "%sqlfile%"=="q" goto end
if exist "%SQL_DIR%\hotfixes\master\%sqlfile%" (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% hotfixes < "%SQL_DIR%\hotfixes\master\%sqlfile%"
) else (
    %MYSQL% -u%USER% -p%PASS% -h%HOST% hotfixes < "%SQL_DIR%\hotfixes\%sqlfile%"
)
if %errorlevel%==0 (
    echo [成功] 已应用: %sqlfile%
) else (
    echo [警告] 可能有错误，请检查上方输出
)
pause
goto end

:end
echo.
echo 操作完成!
