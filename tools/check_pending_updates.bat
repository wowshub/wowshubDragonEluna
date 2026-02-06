@echo off
chcp 65001 > nul
echo ========================================
echo  数据库更新检查工具
echo ========================================
echo.
echo 注意: 请根据您的实际环境修改以下配置
echo.

REM ============================================================
REM 配置区域 - 请根据实际情况修改
REM ============================================================
set MYSQL="D:\2025wowOVER\wow10x\DraconicWoW\65727Precompiled\bin\RelWithDebInfo\UniServerZ\core\mysql\bin\mysql.exe"
set USER=root
set PASS=admin
set HOST=127.0.0.1
REM ============================================================

echo [1] 检查 AUTH 数据库待应用更新...
echo SELECT name FROM updates WHERE state = 'PENDING'; | %MYSQL% -u%USER% -p%PASS% -h%HOST% auth 2>nul

echo.
echo [2] 检查 CHARACTERS 数据库待应用更新...
echo SELECT name FROM updates WHERE state = 'PENDING'; | %MYSQL% -u%USER% -p%PASS% -h%HOST% characters 2>nul

echo.
echo [3] 检查 WORLD 数据库待应用更新...
echo SELECT name FROM updates WHERE state = 'PENDING'; | %MYSQL% -u%USER% -p%PASS% -h%HOST% world 2>nul

echo.
echo [4] 检查 HOTFIXES 数据库待应用更新...
echo SELECT name FROM updates WHERE state = 'PENDING'; | %MYSQL% -u%USER% -p%PASS% -h%HOST% hotfixes 2>nul

echo.
echo ========================================
echo 检查完成！
echo 如果有 PENDING 状态的更新，请手动应用对应的 SQL 文件
echo SQL 更新文件位于源代码目录: sql\updates\
echo ========================================
pause
