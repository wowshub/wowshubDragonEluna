# Database Migrations - 数据库迁移归档

本目录用于归档所有自定义数据库修复和迁移脚本。

## 目录结构规范

每次数据库修复应创建独立的子文件夹，命名格式：
```
YYYY-MM-DD_简短描述/
```

## 子文件夹内容

每个迁移文件夹应包含：

| 文件 | 必需 | 说明 |
|------|------|------|
| `CHANGELOG.md` | ✅ | 变更日志，记录问题、解决方案、回滚指南 |
| `001_xxx.sql` | ✅ | SQL 迁移文件，按编号排序 |
| `apply_migration.bat` | 推荐 | 一键应用脚本 |
| `rollback_migration.bat` | 推荐 | 回滚脚本 |

## 迁移历史

| 日期 | 迁移 ID | 描述 |
|------|---------|------|
| 2026-02-06 | `2026-02-06_hotfix_database_fix` | 修复 worldserver 启动时 Hotfix 数据库错误 |

## 使用指南

### 应用迁移
```bash
cd db_migrations/YYYY-MM-DD_xxx/
apply_migration.bat
```

### 回滚迁移
```bash
cd db_migrations/YYYY-MM-DD_xxx/
rollback_migration.bat
```

## 最佳实践

1. **每次修复创建独立文件夹** - 便于追溯和管理
2. **详细记录 CHANGELOG** - 包含问题描述、解决方案、验证步骤
3. **SQL 使用幂等设计** - 使用 `IF NOT EXISTS` 等检查，确保可重复执行
4. **提供回滚脚本** - 以备需要恢复时使用
5. **提交到 Git** - 确保版本控制
