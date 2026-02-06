-- ============================================================================
-- Migration: 001_auth_add_realmId_column.sql
-- Database: auth
-- Description: Add missing realmId column to account_warband_groups table
-- Date: 2026-02-06
-- Author: Database Migration Tool
-- ============================================================================

-- Fix for bnetserver.exe startup error:
-- Prepared statement LOGIN_INS_ACCOUNT_WARBAND_GROUP requires realmId column

-- Step 1: Add the realmId column if it doesn't exist
SET @column_exists = (
    SELECT COUNT(*) 
    FROM INFORMATION_SCHEMA.COLUMNS 
    WHERE TABLE_SCHEMA = DATABASE() 
    AND TABLE_NAME = 'account_warband_groups' 
    AND COLUMN_NAME = 'realmId'
);

SET @sql = IF(@column_exists = 0, 
    'ALTER TABLE `account_warband_groups` ADD COLUMN `realmId` INT UNSIGNED NOT NULL DEFAULT 0 FIRST',
    'SELECT "Column realmId already exists, skipping..."'
);
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- Step 2: Update the primary key/index to include realmId
-- Note: This may fail if index already exists, which is safe to ignore
-- ALTER TABLE `account_warband_groups` ADD INDEX `idx_account_realm` (`warBandAccountId`, `realmId`);

-- ============================================================================
-- Verification Query:
-- SELECT * FROM INFORMATION_SCHEMA.COLUMNS 
-- WHERE TABLE_SCHEMA = 'auth' AND TABLE_NAME = 'account_warband_groups';
-- ============================================================================
