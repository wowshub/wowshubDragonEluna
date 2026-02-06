# Database Tools - 数据库工具

本目录包含用于管理 TrinityCore 数据库更新的实用工具。

## 工具列表

### 1. check_pending_updates.bat
**用途:** 检查各数据库中待应用的更新

**使用方法:** 双击运行即可

**输出:** 显示 auth、characters、world、hotfixes 数据库中状态为 PENDING 的更新

---

### 2. apply_db_update.bat  
**用途:** 交互式选择并应用 SQL 更新文件

**使用方法:** 
1. 双击运行
2. 选择要更新的数据库 (1-4)
3. 输入要应用的 SQL 文件名
4. 等待执行完成

---

## 配置说明

在使用前，请打开 `.bat` 文件并修改以下配置：

```batch
set MYSQL="路径到mysql.exe"
set USER=数据库用户名
set PASS=数据库密码
set HOST=数据库主机地址
```

---

## 源代码更新后的工作流程

1. **拉取最新代码**
   ```bash
   git pull origin master
   ```

2. **检查新的 SQL 更新文件**
   - 查看 `sql/updates/` 目录下是否有新的 SQL 文件
   - 文件名格式: `YYYY_MM_DD_序号_数据库名.sql`

3. **按顺序应用更新**
   - 运行 `apply_db_update.bat`
   - 按日期顺序应用新的 SQL 文件

4. **处理常见错误**
   - `Duplicate column name` → 该更新已应用，可跳过
   - `Table doesn't exist` → 需要先应用更早的更新
   - `Unknown column` → 需要应用结构变更的更新

---

## 目录结构

```
tools/
├── README.md                  ← 本文件
├── check_pending_updates.bat  ← 检查待更新
└── apply_db_update.bat        ← 应用更新

db_migrations/                 ← 自定义修复归档
└── YYYY-MM-DD_描述/
    ├── CHANGELOG.md
    ├── 001_xxx.sql
    ├── apply_migration.bat
    └── rollback_migration.bat
```
