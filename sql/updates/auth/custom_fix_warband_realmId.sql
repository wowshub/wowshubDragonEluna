ALTER TABLE `account_warband_groups` 
ADD COLUMN `realmId` int(10) unsigned NOT NULL DEFAULT '1' AFTER `accountId`,
DROP INDEX `idx_account`,
ADD KEY `idx_account_realm` (`accountId`, `realmId`);
