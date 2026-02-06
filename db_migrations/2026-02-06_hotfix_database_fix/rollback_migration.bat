@echo off
chcp 65001 > nul
echo ============================================================
echo  ROLLBACK: 2026-02-06 Hotfix Database Fix
echo ============================================================
echo.
echo WARNING: This will undo the database changes!
echo.
set /p confirm="Are you sure you want to rollback? (yes/no): "
if /i NOT "%confirm%"=="yes" (
    echo Rollback cancelled.
    pause
    exit /b
)

set MYSQL="D:\2025wowOVER\wow10x\DraconicWoW\65727Precompiled\bin\RelWithDebInfo\UniServerZ\core\mysql\bin\mysql.exe"
set USER=root
set PASS=admin
set HOST=127.0.0.1

echo.
echo [1/2] Rolling back Hotfixes Database...
echo DROP TABLE IF EXISTS trait_cond_account_element; | %MYSQL% -u%USER% -p%PASS% -h%HOST% hotfixes
echo      [OK] Removed trait_cond_account_element table

echo.
echo [2/2] Rolling back Auth Database...
echo ALTER TABLE account_warband_groups DROP COLUMN realmId; | %MYSQL% -u%USER% -p%PASS% -h%HOST% auth 2>nul
echo      [OK] Removed realmId column (if it existed)

echo.
echo ============================================================
echo  Rollback Complete!
echo ============================================================
echo.
echo NOTE: Server will NOT start correctly after rollback!
echo       Re-run apply_migration.bat to restore.
echo.
pause
