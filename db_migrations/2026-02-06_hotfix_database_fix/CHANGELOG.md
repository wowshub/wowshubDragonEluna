# Database Migration: 2026-02-06 Hotfix Database Fix

## Migration ID
`2026-02-06_hotfix_database_fix`

## Summary
修复 worldserver 启动时 "Could not prepare statements of the Hotfix database" 错误

## Applied Date
2026-02-06 10:50 CST

## Environment
- **Server Version:** TrinityCore 247cb33677a1 (master branch)
- **MySQL Version:** 8.2.x
- **Databases Affected:** auth, hotfixes

---

## Changes Applied

### 1. Auth Database - account_warband_groups Fix
**File:** `001_auth_add_realmId_column.sql`

**Issue:** 
- `bnetserver.exe` 无法启动
- 错误信息: prepared statement 使用了 `realmId` 列，但表中不存在该列

**Solution:**
- 添加 `realmId` 列到 `account_warband_groups` 表
- 更新主键索引包含 `realmId`

---

### 2. Hotfixes Database - trait_cond_account_element Table
**File:** `002_hotfixes_add_trait_cond_account_element.sql`

**Issue:**
- `worldserver.exe` 无法启动
- 错误信息: "Could not prepare statements of the Hotfix database"
- 根本原因: `trait_cond_account_element` 表不存在

**Solution:**
- 创建 `trait_cond_account_element` 表

---

## Rollback Instructions (回滚指南)

### Rollback Auth Changes
```sql
ALTER TABLE `account_warband_groups` DROP COLUMN `realmId`;
ALTER TABLE `account_warband_groups` DROP INDEX `idx_account_realm`;
ALTER TABLE `account_warband_groups` ADD PRIMARY KEY (`warGroupId`, `warBankBagsUnlocked`);
```

### Rollback Hotfixes Changes
```sql
DROP TABLE IF EXISTS `trait_cond_account_element`;
```

---

## Verification Steps (验证步骤)

1. 启动 `bnetserver.exe` - 应正常启动无错误
2. 启动 `worldserver.exe` - 应正常启动无错误
3. 检查日志文件中无 SQL 相关错误

---

## Related Files
- `001_auth_add_realmId_column.sql` - Auth 数据库修复
- `002_hotfixes_add_trait_cond_account_element.sql` - Hotfixes 数据库修复
- `apply_migration.bat` - 一键应用脚本
- `rollback_migration.bat` - 回滚脚本

---

## Author
Database Migration Tool / AI Assistant

## Notes
- 此修复是由于源代码版本与数据库结构不匹配导致
- 建议在每次更新源代码后检查 `sql/updates/` 目录下的新 SQL 文件
