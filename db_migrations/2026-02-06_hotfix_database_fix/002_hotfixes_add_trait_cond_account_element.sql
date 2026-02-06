-- ============================================================================
-- Migration: 002_hotfixes_add_trait_cond_account_element.sql
-- Database: hotfixes
-- Description: Create trait_cond_account_element table
-- Date: 2026-02-06
-- Author: Database Migration Tool
-- Source: D:\10xcode\wowshubDragonEluna\sql\updates\hotfixes\master\2026_02_03_00_hotfixes.sql
-- ============================================================================

-- Fix for worldserver.exe startup error:
-- "Could not prepare statements of the Hotfix database"
-- Missing table: trait_cond_account_element

-- Create table if not exists
DROP TABLE IF EXISTS `trait_cond_account_element`;
CREATE TABLE `trait_cond_account_element` (
  `ElementValueInt` bigint NOT NULL DEFAULT '0',
  `ID` int unsigned NOT NULL DEFAULT '0',
  `PlayerDataElementAccountID` int unsigned NOT NULL DEFAULT '0',
  `Comparison` tinyint unsigned NOT NULL DEFAULT '0',
  `Unused1110` int NOT NULL DEFAULT '0',
  `PlayerDataElementCharacterID` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================================================
-- Verification Query:
-- SHOW CREATE TABLE trait_cond_account_element;
-- ============================================================================
