@echo off
chcp 65001 > nul
echo ============================================================
echo  Database Migration: 2026-02-06 Hotfix Database Fix
echo ============================================================
echo.

set MYSQL="D:\2025wowOVER\wow10x\DraconicWoW\65727Precompiled\bin\RelWithDebInfo\UniServerZ\core\mysql\bin\mysql.exe"
set USER=root
set PASS=admin
set HOST=127.0.0.1
set MIGRATION_DIR=%~dp0

echo [1/2] Applying Auth Database Fix...
echo      - Adding realmId column to account_warband_groups
%MYSQL% -u%USER% -p%PASS% -h%HOST% auth < "%MIGRATION_DIR%001_auth_add_realmId_column.sql"
if %errorlevel%==0 (
    echo      [OK] Auth fix applied successfully
) else (
    echo      [WARN] Auth fix may have had issues, check output above
)

echo.
echo [2/2] Applying Hotfixes Database Fix...
echo      - Creating trait_cond_account_element table
%MYSQL% -u%USER% -p%PASS% -h%HOST% hotfixes < "%MIGRATION_DIR%002_hotfixes_add_trait_cond_account_element.sql"
if %errorlevel%==0 (
    echo      [OK] Hotfixes fix applied successfully
) else (
    echo      [WARN] Hotfixes fix may have had issues, check output above
)

echo.
echo ============================================================
echo  Migration Complete!
echo ============================================================
echo.
echo Next Steps:
echo   1. Start bnetserver.exe
echo   2. Start worldserver.exe
echo   3. Verify no SQL errors in Server.log
echo.
pause
