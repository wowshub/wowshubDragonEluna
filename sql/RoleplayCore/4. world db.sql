-- ----------------------------
-- Table structure for creature_template_outfits
-- ----------------------------
DROP TABLE IF EXISTS `creature_template_outfits`;
CREATE TABLE `creature_template_outfits`  (
  `entry` int UNSIGNED NOT NULL,
  `npcsoundsid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'entry from NPCSounds.dbc/db2',
  `race` tinyint UNSIGNED NOT NULL DEFAULT 1,
  `class` tinyint UNSIGNED NOT NULL DEFAULT 1,
  `gender` tinyint UNSIGNED NOT NULL DEFAULT 0 COMMENT '0 for male, 1 for female',
  `spellvisualkitid` int NOT NULL DEFAULT 0,
  `customizations` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `head` bigint NOT NULL DEFAULT 0,
  `head_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `shoulders` bigint NOT NULL DEFAULT 0,
  `shoulders_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `body` bigint NOT NULL DEFAULT 0,
  `body_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `chest` bigint NOT NULL DEFAULT 0,
  `chest_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `waist` bigint NOT NULL DEFAULT 0,
  `waist_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `legs` bigint NOT NULL DEFAULT 0,
  `legs_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `feet` bigint NOT NULL DEFAULT 0,
  `feet_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `wrists` bigint NOT NULL DEFAULT 0,
  `wrists_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `hands` bigint NOT NULL DEFAULT 0,
  `hands_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `back` bigint NOT NULL DEFAULT 0,
  `back_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `tabard` bigint NOT NULL DEFAULT 0,
  `tabard_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `guildid` bigint UNSIGNED NOT NULL DEFAULT 0,
  `description` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = 'Use positive values for item entries and negative to use item displayid for head, shoulders etc.' ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for creature_template_outfits_customizations
-- ----------------------------
DROP TABLE IF EXISTS `creature_template_outfits_customizations`;
CREATE TABLE `creature_template_outfits_customizations`  (
  `chrCustomizationOptionID` int UNSIGNED NOT NULL,
  `chrCustomizationChoiceID` int UNSIGNED NOT NULL DEFAULT 0,
  `outfitID` bigint NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of creature_template_outfits_customizations
-- ----------------------------

-- ----------------------------
-- Table structure for scrapping_loot_template
-- ----------------------------
DROP TABLE IF EXISTS `scrapping_loot_template`;
CREATE TABLE `scrapping_loot_template`  (
  `Entry` mediumint UNSIGNED NOT NULL DEFAULT 0,
  `Item` mediumint NOT NULL DEFAULT 0,
  `Reference` mediumint UNSIGNED NOT NULL DEFAULT 0,
  `Chance` float NOT NULL DEFAULT 100,
  `QuestRequired` tinyint(1) NOT NULL DEFAULT 0,
  `LootMode` smallint UNSIGNED NOT NULL DEFAULT 1,
  `GroupId` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `MinCount` int UNSIGNED NOT NULL DEFAULT 1,
  `MaxCount` int UNSIGNED NOT NULL DEFAULT 1,
  `Comment` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`Entry`, `Item`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci COMMENT = 'Loot System' ROW_FORMAT = FIXED;

-- ----------------------------
-- Records of scrapping_loot_template
-- ----------------------------
DELETE FROM `scrapping_loot_template`;
INSERT INTO `scrapping_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
	(1, 160266, 0, 100, 0, 1, 0, 1, 1, NULL),
	(2, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(2, 154165, 0, 100, 0, 1, 0, 1, 8, NULL),
	(2, 11291, 0, 100, 0, 1, 0, 1, 3, NULL),
	(3, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(3, 154165, 0, 100, 0, 1, 0, 2, 8, NULL),
	(3, 11291, 0, 100, 0, 1, 0, 1, 4, NULL),
	(4, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(4, 154165, 0, 100, 0, 1, 0, 4, 8, NULL),
	(4, 11291, 0, 100, 0, 1, 0, 3, 6, NULL),
	(5, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(5, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(5, 159959, 0, 100, 0, 1, 0, 1, 5, NULL),
	(6, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(6, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(6, 152577, 0, 20, 0, 1, 0, 5, 8, NULL),
	(6, 158378, 0, 5, 0, 1, 0, 2, 6, NULL),
	(6, 159959, 0, 100, 0, 1, 0, 1, 8, NULL),
	(7, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(7, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(7, 152577, 0, 5, 0, 1, 0, 4, 6, NULL),
	(7, 158378, 0, 5, 0, 1, 0, 2, 4, NULL),
	(7, 159959, 0, 100, 0, 1, 0, 1, 8, NULL),
	(8, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(8, 152577, 0, 100, 0, 1, 0, 8, 21, NULL),
	(8, 158378, 0, 100, 0, 1, 0, 3, 8, NULL),
	(8, 159959, 0, 100, 0, 1, 0, 5, 10, NULL),
	(9, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(9, 152577, 0, 100, 0, 1, 0, 4, 10, NULL),
	(9, 158378, 0, 100, 0, 1, 0, 2, 6, NULL),
	(9, 159959, 0, 100, 0, 1, 0, 3, 9, NULL),
	(10, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(11, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(12, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(13, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(13, 152541, 0, 100, 0, 1, 0, 1, 3, NULL),
	(13, 154164, 0, 100, 0, 1, 0, 1, 2, NULL),
	(14, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(14, 152541, 0, 100, 0, 1, 0, 2, 5, NULL),
	(14, 152542, 0, 5, 0, 1, 0, 2, 5, NULL),
	(14, 154164, 0, 100, 0, 1, 0, 1, 3, NULL),
	(14, 154165, 0, 20, 0, 1, 0, 3, 9, NULL),
	(15, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(15, 152541, 0, 100, 0, 1, 0, 2, 5, NULL),
	(15, 152542, 0, 5, 0, 1, 0, 1, 4, NULL),
	(15, 154164, 0, 100, 0, 1, 0, 1, 3, NULL),
	(15, 154165, 0, 5, 0, 1, 0, 2, 7, NULL),
	(16, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(16, 152542, 0, 100, 0, 1, 0, 4, 9, NULL),
	(16, 154165, 0, 100, 0, 1, 0, 7, 12, NULL),
	(16, 154722, 0, 100, 0, 1, 0, 3, 21, NULL),
	(17, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(17, 152542, 0, 100, 0, 1, 0, 1, 4, NULL),
	(17, 154165, 0, 100, 0, 1, 0, 5, 8, NULL),
	(17, 154722, 0, 100, 0, 1, 0, 5, 12, NULL),
	(18, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(19, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(20, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(21, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(21, 153050, 0, 100, 0, 1, 0, 1, 3, NULL),
	(21, 154164, 0, 100, 0, 1, 0, 1, 2, NULL),
	(22, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(22, 153051, 0, 10, 0, 1, 0, 8, 17, NULL),
	(22, 154165, 0, 10, 0, 1, 0, 5, 8, NULL),
	(22, 153050, 0, 100, 0, 1, 0, 2, 5, NULL),
	(22, 154164, 0, 100, 0, 1, 0, 2, 3, NULL),
	(23, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(23, 153051, 0, 10, 0, 1, 0, 4, 9, NULL),
	(23, 154165, 0, 10, 0, 1, 0, 2, 8, NULL),
	(23, 153050, 0, 100, 0, 1, 0, 2, 5, NULL),
	(23, 154164, 0, 100, 0, 1, 0, 2, 3, NULL),
	(24, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(24, 152542, 0, 100, 0, 1, 0, 4, 8, NULL),
	(24, 154165, 0, 100, 0, 1, 0, 6, 16, NULL),
	(24, 153051, 0, 100, 0, 1, 0, 8, 18, NULL),
	(24, 160059, 0, 100, 0, 1, 0, 6, 10, NULL),
	(25, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(25, 152542, 0, 100, 0, 1, 0, 1, 2, NULL),
	(25, 154165, 0, 100, 0, 1, 0, 6, 8, NULL),
	(25, 153051, 0, 100, 0, 1, 0, 10, 14, NULL),
	(25, 160059, 0, 100, 0, 1, 0, 3, 7, NULL),
	(26, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(27, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(28, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(29, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(29, 152512, 0, 100, 0, 1, 0, 1, 2, NULL),
	(29, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(30, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(30, 152513, 0, 10, 0, 1, 0, 2, 7, NULL),
	(30, 152579, 0, 10, 0, 1, 0, 2, 9, NULL),
	(30, 152512, 0, 100, 0, 1, 0, 1, 4, NULL),
	(30, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(31, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(31, 152513, 0, 10, 0, 1, 0, 1, 5, NULL),
	(31, 152579, 0, 10, 0, 1, 0, 2, 5, NULL),
	(31, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(31, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(32, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(32, 152542, 0, 100, 0, 1, 0, 4, 8, NULL),
	(32, 154165, 0, 100, 0, 1, 0, 6, 16, NULL),
	(32, 153051, 0, 100, 0, 1, 0, 8, 18, NULL),
	(32, 160059, 0, 100, 0, 1, 0, 6, 10, NULL),
	(33, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(33, 152542, 0, 100, 0, 1, 0, 1, 2, NULL),
	(33, 154165, 0, 100, 0, 1, 0, 6, 8, NULL),
	(33, 153051, 0, 100, 0, 1, 0, 10, 14, NULL),
	(33, 160059, 0, 100, 0, 1, 0, 3, 7, NULL),
	(34, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(35, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(36, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(37, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(37, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(37, 159959, 0, 100, 0, 1, 0, 1, 5, NULL),
	(38, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(38, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(38, 152577, 0, 5, 0, 1, 0, 4, 6, NULL),
	(38, 158378, 0, 5, 0, 1, 0, 2, 4, NULL),
	(38, 159959, 0, 100, 0, 1, 0, 1, 8, NULL),
	(39, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(39, 152577, 0, 100, 0, 1, 0, 4, 10, NULL),
	(39, 158378, 0, 100, 0, 1, 0, 2, 6, NULL),
	(39, 159959, 0, 100, 0, 1, 0, 3, 9, NULL),
	(40, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(40, 153700, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153701, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153702, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153703, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153704, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153705, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(41, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(41, 154120, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154121, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154122, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154123, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154124, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154125, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 152579, 0, 100, 0, 1, 0, 1, 5, NULL),
	(42, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(42, 154120, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154121, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154122, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154123, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154124, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154125, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 152513, 0, 100, 0, 1, 0, 1, 5, NULL),
	(43, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(44, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(45, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(46, 152668, 0, 100, 0, 1, 0, 1, 1, NULL),
	(47, 152510, 0, 100, 0, 1, 0, 1, 3, NULL),
	(47, 152507, 0, 100, 0, 1, 0, 1, 12, NULL),
	(47, 152505, 0, 100, 0, 1, 0, 1, 12, NULL),
	(47, 152511, 0, 100, 0, 1, 0, 1, 12, NULL),
	(47, 152509, 0, 100, 0, 1, 0, 1, 8, NULL),
	(47, 152506, 0, 100, 0, 1, 0, 1, 8, NULL),
	(47, 152508, 0, 100, 0, 1, 0, 1, 12, NULL),
	(48, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(48, 158188, 0, 50, 0, 1, 0, 2, 8, NULL),
	(48, 158187, 0, 100, 0, 1, 0, 5, 10, NULL),
	(49, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(49, 158188, 0, 50, 0, 1, 0, 5, 11, NULL),
	(49, 158187, 0, 100, 0, 1, 0, 5, 10, NULL),
	(50, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(50, 158189, 0, 25, 0, 1, 0, 1, 4, NULL),
	(50, 158188, 0, 50, 0, 1, 0, 5, 13, NULL),
	(50, 158187, 0, 100, 0, 1, 0, 5, 10, NULL),
	(51, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(51, 11291, 0, 50, 0, 1, 0, 1, 1, NULL),
	(51, 152875, 0, 100, 0, 1, 0, 1, 3, NULL),
	(52, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(52, 11291, 0, 50, 0, 1, 0, 1, 1, NULL),
	(52, 152875, 0, 100, 0, 1, 0, 1, 3, NULL),
	(53, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(53, 11291, 0, 50, 0, 1, 0, 1, 1, NULL),
	(53, 152876, 0, 100, 0, 1, 0, 1, 1, NULL),
	(54, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(54, 153050, 0, 80, 0, 1, 0, 1, 4, NULL),
	(54, 154164, 0, 80, 0, 1, 0, 1, 2, NULL),
	(54, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(55, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(55, 154165, 0, 80, 0, 1, 0, 5, 10, NULL),
	(55, 153051, 0, 80, 0, 1, 0, 5, 10, NULL),
	(55, 160059, 0, 100, 0, 1, 0, 4, 10, NULL),
	(56, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(56, 154165, 0, 80, 0, 1, 0, 9, 12, NULL),
	(56, 153051, 0, 80, 0, 1, 0, 7, 17, NULL),
	(56, 160059, 0, 100, 0, 1, 0, 4, 15, NULL),
	(57, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(57, 153700, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153701, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153702, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153703, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153704, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153705, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(58, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(58, 154120, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154121, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154122, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154123, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154124, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154125, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 152579, 0, 100, 0, 1, 0, 1, 5, NULL),
	(59, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(59, 154120, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154121, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154122, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154123, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154124, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154125, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 152579, 0, 100, 0, 1, 0, 1, 5, NULL),
	(60, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(60, 152512, 0, 100, 0, 1, 0, 1, 2, NULL),
	(60, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(61, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(61, 152513, 0, 10, 0, 1, 0, 1, 5, NULL),
	(61, 152579, 0, 10, 0, 1, 0, 2, 5, NULL),
	(61, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(61, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(62, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(62, 152542, 0, 100, 0, 1, 0, 1, 2, NULL),
	(62, 154165, 0, 100, 0, 1, 0, 6, 8, NULL),
	(62, 153051, 0, 100, 0, 1, 0, 10, 14, NULL),
	(62, 160059, 0, 100, 0, 1, 0, 3, 7, NULL),
	(63, 152512, 0, 100, 0, 1, 0, 1, 3, ''),
	(63, 152513, 0, 10, 0, 1, 0, 1, 5, ''),
	(63, 152579, 0, 10, 0, 1, 0, 2, 5, ''),
	(63, 152668, 0, 16, 0, 1, 0, 1, 1, ''),
	(63, 160298, 0, 100, 0, 1, 0, 1, 1, '');

DROP TABLE IF EXISTS `archaeology_artifacts`;
CREATE TABLE IF NOT EXISTS `archaeology_artifacts` (
  `spellId` int unsigned NOT NULL DEFAULT '0',
  `minSkillValue` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla world.archaeology_artifacts: ~266 rows (aproximadamente)
DELETE FROM `archaeology_artifacts`;
INSERT INTO `archaeology_artifacts` (`spellId`, `minSkillValue`) VALUES
	(84796, 50),
	(86857, 35),
	(86864, 35),
	(86865, 30),
	(86866, 32),
	(88180, 35),
	(88181, 34),
	(88262, 27),
	(88907, 30),
	(88908, 32),
	(88909, 28),
	(88910, 34),
	(88929, 31),
	(88930, 25),
	(89009, 30),
	(89012, 30),
	(89014, 30),
	(89693, 85),
	(89696, 35),
	(89701, 35),
	(89711, 34),
	(89717, 34),
	(89890, 35),
	(89891, 35),
	(89893, 35),
	(89894, 35),
	(89895, 35),
	(89896, 35),
	(90410, 35),
	(90411, 35),
	(90412, 34),
	(90413, 35),
	(90415, 35),
	(90419, 36),
	(90420, 35),
	(90421, 35),
	(90423, 35),
	(90429, 35),
	(90432, 35),
	(90433, 35),
	(90451, 35),
	(90452, 35),
	(90453, 35),
	(90458, 35),
	(90464, 100),
	(90493, 100),
	(90504, 35),
	(90506, 35),
	(90509, 35),
	(90518, 35),
	(90519, 35),
	(90521, 100),
	(90553, 100),
	(90558, 35),
	(90581, 35),
	(90608, 150),
	(90609, 35),
	(90610, 34),
	(90611, 35),
	(90612, 35),
	(90614, 98),
	(90616, 100),
	(90617, 33),
	(90618, 35),
	(90619, 100),
	(90622, 45),
	(90720, 45),
	(90728, 45),
	(90730, 45),
	(90732, 45),
	(90734, 45),
	(90831, 45),
	(90832, 45),
	(90833, 45),
	(90843, 130),
	(90853, 45),
	(90860, 45),
	(90861, 46),
	(90864, 46),
	(90968, 46),
	(90974, 44),
	(90975, 45),
	(90983, 124),
	(90984, 130),
	(90987, 45),
	(90988, 45),
	(90997, 130),
	(91008, 45),
	(91012, 45),
	(91014, 45),
	(91084, 45),
	(91089, 45),
	(91132, 45),
	(91133, 45),
	(91170, 45),
	(91188, 45),
	(91191, 45),
	(91197, 45),
	(91209, 45),
	(91211, 45),
	(91214, 140),
	(91215, 140),
	(91219, 45),
	(91221, 45),
	(91223, 45),
	(91224, 45),
	(91225, 45),
	(91226, 150),
	(91227, 150),
	(91757, 150),
	(91761, 150),
	(91762, 45),
	(91766, 45),
	(91769, 45),
	(91773, 150),
	(91775, 45),
	(91779, 45),
	(91780, 45),
	(91782, 45),
	(91785, 45),
	(91790, 45),
	(91792, 45),
	(91793, 45),
	(92137, 150),
	(92139, 150),
	(92145, 150),
	(92148, 150),
	(92163, 150),
	(92168, 150),
	(93440, 30),
	(93441, 30),
	(93442, 30),
	(93443, 35),
	(93444, 32),
	(98533, 150),
	(98556, 100),
	(98560, 100),
	(98569, 100),
	(98582, 120),
	(98588, 100),
	(113968, 50),
	(113971, 40),
	(113972, 50),
	(113973, 50),
	(113974, 50),
	(113975, 50),
	(113976, 50),
	(113977, 50),
	(113978, 60),
	(113979, 50),
	(113980, 180),
	(113981, 180),
	(113982, 50),
	(113983, 50),
	(113984, 50),
	(113985, 50),
	(113986, 50),
	(113987, 60),
	(113988, 50),
	(113989, 50),
	(113990, 30),
	(113991, 50),
	(113992, 180),
	(113993, 180),
	(124102, 30),
	(139776, 50),
	(139779, 50),
	(139780, 50),
	(139781, 50),
	(139782, 50),
	(139783, 50),
	(139784, 50),
	(139785, 50),
	(139786, 180),
	(139787, 180),
	(168290, 50),
	(168291, 60),
	(168292, 45),
	(168293, 45),
	(168294, 55),
	(168295, 60),
	(168296, 50),
	(168297, 65),
	(168298, 50),
	(168299, 45),
	(168300, 60),
	(168301, 45),
	(168302, 45),
	(168303, 40),
	(168304, 45),
	(168305, 55),
	(168306, 50),
	(168307, 55),
	(168308, 40),
	(168309, 40),
	(168310, 55),
	(168311, 45),
	(168312, 55),
	(168313, 50),
	(168314, 55),
	(168315, 70),
	(168316, 50),
	(168317, 55),
	(168318, 45),
	(168319, 150),
	(168320, 200),
	(168321, 45),
	(168322, 55),
	(168323, 50),
	(168324, 45),
	(168325, 60),
	(168326, 50),
	(168327, 45),
	(168328, 70),
	(168329, 65),
	(168330, 50),
	(168331, 190),
	(172459, 180),
	(172460, 200),
	(172466, 175),
	(196470, 35),
	(196471, 45),
	(196472, 50),
	(196473, 120),
	(196474, 100),
	(196475, 65),
	(196476, 30),
	(196477, 50),
	(196478, 115),
	(196479, 105),
	(196480, 60),
	(196481, 85),
	(196482, 95),
	(196483, 140),
	(196484, 170),
	(223844, 100),
	(223846, 100),
	(223848, 100),
	(223849, 100),
	(223850, 100),
	(223851, 100),
	(223852, 100),
	(223853, 100),
	(223854, 100),
	(223855, 100),
	(223856, 100),
	(223857, 100),
	(223858, 100),
	(257715, 40),
	(257716, 50),
	(257717, 45),
	(257718, 35),
	(257719, 35),
	(257720, 35),
	(257721, 45),
	(257722, 50),
	(257723, 50),
	(257724, 65),
	(273812, 35),
	(273815, 150),
	(273817, 185),
	(273819, 200),
	(273851, 70),
	(273852, 150),
	(273854, 185),
	(273855, 200);
	
DROP TABLE IF EXISTS `archaeology_digsites`;
CREATE TABLE IF NOT EXISTS `archaeology_digsites` (
  `id` smallint unsigned NOT NULL DEFAULT '0',
  `minLevel` tinyint unsigned NOT NULL DEFAULT '0',
  `minSkillLevel` smallint unsigned NOT NULL DEFAULT '0',
  `currencyId` smallint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla world.archaeology_digsites: ~450 rows (aproximadamente)
DELETE FROM `archaeology_digsites`;
INSERT INTO `archaeology_digsites` (`id`, `minLevel`, `minSkillLevel`, `currencyId`) VALUES
	(9, 1, 1, 384),
	(10, 1, 1, 384),
	(12, 1, 1, 384),
	(13, 1, 1, 393),
	(15, 1, 1, 384),
	(18, 1, 1, 385),
	(19, 1, 1, 384),
	(20, 1, 1, 393),
	(21, 1, 1, 393),
	(22, 1, 1, 384),
	(23, 1, 1, 385),
	(24, 1, 1, 385),
	(25, 1, 1, 385),
	(26, 1, 1, 385),
	(27, 1, 1, 385),
	(140, 1, 1, 385),
	(142, 1, 1, 384),
	(144, 1, 1, 384),
	(146, 1, 1, 384),
	(150, 1, 1, 384),
	(152, 1, 1, 385),
	(154, 1, 1, 393),
	(161, 1, 1, 394),
	(163, 1, 1, 394),
	(165, 1, 1, 393),
	(167, 1, 1, 394),
	(169, 1, 1, 394),
	(171, 1, 1, 394),
	(173, 1, 1, 394),
	(175, 1, 1, 394),
	(177, 1, 1, 394),
	(179, 1, 1, 394),
	(181, 1, 1, 393),
	(183, 1, 1, 384),
	(185, 1, 1, 394),
	(187, 1, 1, 394),
	(189, 1, 1, 393),
	(191, 1, 1, 394),
	(193, 1, 1, 394),
	(195, 1, 1, 393),
	(197, 1, 1, 394),
	(199, 1, 1, 393),
	(201, 1, 1, 394),
	(203, 1, 1, 393),
	(205, 1, 1, 393),
	(207, 1, 1, 384),
	(209, 1, 1, 384),
	(211, 1, 1, 384),
	(213, 1, 1, 384),
	(215, 1, 1, 393),
	(217, 1, 1, 385),
	(219, 1, 1, 394),
	(221, 1, 1, 393),
	(223, 1, 1, 385),
	(225, 1, 1, 385),
	(227, 1, 1, 385),
	(229, 1, 1, 385),
	(231, 1, 1, 385),
	(233, 1, 1, 385),
	(235, 1, 1, 385),
	(237, 1, 1, 393),
	(239, 1, 1, 385),
	(241, 1, 1, 385),
	(243, 1, 1, 385),
	(245, 1, 1, 385),
	(247, 1, 1, 393),
	(249, 1, 1, 393),
	(251, 1, 1, 393),
	(259, 1, 1, 393),
	(261, 1, 1, 393),
	(279, 1, 1, 394),
	(281, 1, 1, 394),
	(283, 1, 1, 394),
	(285, 1, 1, 394),
	(287, 1, 1, 394),
	(289, 1, 1, 394),
	(291, 1, 1, 394),
	(293, 1, 1, 394),
	(295, 1, 1, 394),
	(297, 1, 1, 394),
	(299, 1, 1, 394),
	(301, 1, 1, 394),
	(303, 1, 1, 394),
	(305, 1, 1, 394),
	(307, 1, 1, 394),
	(309, 1, 1, 393),
	(313, 1, 1, 394),
	(315, 1, 1, 385),
	(317, 1, 1, 385),
	(319, 1, 1, 385),
	(321, 1, 1, 385),
	(323, 1, 1, 393),
	(325, 1, 1, 393),
	(327, 1, 1, 393),
	(329, 1, 1, 393),
	(331, 1, 1, 393),
	(333, 1, 1, 393),
	(335, 1, 1, 393),
	(337, 1, 1, 394),
	(339, 1, 1, 397),
	(341, 1, 1, 397),
	(343, 1, 1, 397),
	(345, 1, 1, 397),
	(347, 1, 1, 398),
	(349, 1, 1, 398),
	(351, 1, 1, 398),
	(353, 1, 1, 398),
	(355, 1, 1, 398),
	(357, 1, 1, 398),
	(359, 1, 1, 397),
	(363, 1, 1, 397),
	(365, 1, 1, 397),
	(367, 1, 1, 397),
	(369, 1, 1, 398),
	(371, 1, 1, 397),
	(373, 1, 1, 398),
	(375, 1, 1, 397),
	(377, 1, 1, 397),
	(379, 1, 1, 398),
	(381, 1, 1, 398),
	(383, 1, 1, 398),
	(385, 1, 1, 398),
	(387, 1, 1, 398),
	(391, 1, 1, 398),
	(393, 1, 1, 398),
	(395, 1, 1, 397),
	(399, 1, 1, 397),
	(401, 1, 1, 399),
	(403, 1, 1, 399),
	(405, 1, 1, 399),
	(407, 1, 1, 399),
	(409, 1, 1, 399),
	(411, 1, 1, 399),
	(413, 1, 1, 399),
	(415, 1, 1, 400),
	(417, 1, 1, 394),
	(419, 1, 1, 400),
	(421, 1, 1, 400),
	(423, 1, 1, 394),
	(425, 1, 1, 394),
	(427, 1, 1, 394),
	(429, 1, 1, 385),
	(431, 1, 1, 385),
	(433, 1, 1, 385),
	(435, 1, 1, 385),
	(437, 1, 1, 400),
	(439, 1, 1, 399),
	(443, 1, 1, 385),
	(445, 1, 1, 399),
	(447, 1, 1, 399),
	(449, 1, 1, 399),
	(451, 1, 1, 400),
	(455, 1, 1, 399),
	(457, 1, 1, 399),
	(459, 1, 1, 399),
	(461, 1, 1, 394),
	(463, 1, 1, 394),
	(465, 1, 1, 394),
	(467, 1, 1, 394),
	(469, 1, 1, 394),
	(471, 1, 1, 394),
	(473, 1, 1, 394),
	(475, 1, 1, 394),
	(477, 1, 1, 384),
	(479, 1, 1, 384),
	(481, 1, 1, 384),
	(485, 1, 1, 401),
	(487, 1, 1, 401),
	(489, 1, 1, 401),
	(491, 1, 1, 401),
	(493, 1, 1, 401),
	(495, 1, 1, 401),
	(497, 1, 1, 401),
	(499, 1, 1, 401),
	(501, 1, 1, 401),
	(570, 1, 1, 401),
	(572, 1, 1, 401),
	(574, 1, 1, 401),
	(576, 1, 1, 401),
	(578, 1, 1, 401),
	(581, 1, 1, 401),
	(583, 1, 1, 401),
	(587, 1, 1, 400),
	(589, 1, 1, 400),
	(615, 1, 1, 400),
	(617, 1, 1, 400),
	(918, 1, 1, 676),
	(923, 1, 1, 676),
	(928, 1, 1, 676),
	(934, 1, 1, 677),
	(936, 1, 1, 676),
	(938, 1, 1, 676),
	(941, 1, 1, 677),
	(949, 1, 1, 677),
	(951, 1, 1, 676),
	(955, 1, 1, 677),
	(957, 1, 1, 677),
	(961, 1, 1, 677),
	(963, 1, 1, 677),
	(967, 1, 1, 677),
	(971, 1, 1, 676),
	(973, 1, 1, 676),
	(977, 1, 1, 676),
	(979, 1, 1, 676),
	(981, 1, 1, 677),
	(983, 1, 1, 677),
	(987, 1, 1, 677),
	(989, 1, 1, 677),
	(995, 1, 1, 676),
	(999, 1, 1, 676),
	(1003, 1, 1, 677),
	(1005, 1, 1, 677),
	(1007, 1, 1, 677),
	(1009, 1, 1, 677),
	(1011, 1, 1, 676),
	(1015, 1, 1, 676),
	(1017, 1, 1, 676),
	(1019, 1, 1, 676),
	(1021, 1, 1, 676),
	(1023, 1, 1, 676),
	(1025, 1, 1, 676),
	(1029, 1, 1, 676),
	(1033, 1, 1, 676),
	(1035, 1, 1, 676),
	(1037, 1, 1, 676),
	(1039, 1, 1, 676),
	(1043, 1, 1, 676),
	(1045, 1, 1, 676),
	(1047, 1, 1, 676),
	(1049, 1, 1, 676),
	(1051, 1, 1, 676),
	(1284, 1, 1, 676),
	(1286, 1, 1, 676),
	(1288, 1, 1, 676),
	(1292, 1, 1, 677),
	(1294, 1, 1, 677),
	(1300, 1, 1, 677),
	(1308, 1, 1, 677),
	(1316, 1, 1, 677),
	(1318, 1, 1, 677),
	(1322, 1, 1, 677),
	(1326, 1, 1, 677),
	(1332, 1, 1, 754),
	(1334, 1, 1, 676),
	(1338, 1, 1, 677),
	(1340, 1, 1, 677),
	(1342, 1, 1, 677),
	(1346, 1, 1, 754),
	(1348, 1, 1, 677),
	(1352, 1, 1, 677),
	(1356, 1, 1, 677),
	(1358, 1, 1, 677),
	(1463, 1, 1, 754),
	(1465, 1, 1, 754),
	(1467, 1, 1, 754),
	(1469, 1, 1, 754),
	(1471, 1, 1, 754),
	(1473, 1, 1, 754),
	(1475, 1, 1, 754),
	(1479, 1, 1, 754),
	(1481, 1, 1, 754),
	(1483, 1, 1, 754),
	(1485, 1, 1, 754),
	(1487, 1, 1, 754),
	(1489, 1, 1, 754),
	(1491, 1, 1, 754),
	(1493, 1, 1, 754),
	(1495, 1, 1, 754),
	(1497, 1, 1, 754),
	(1501, 1, 1, 754),
	(1503, 1, 1, 754),
	(1507, 1, 1, 754),
	(1681, 1, 1, 821),
	(1683, 1, 1, 821),
	(1685, 1, 1, 821),
	(1687, 1, 1, 821),
	(1689, 1, 1, 821),
	(1691, 1, 1, 821),
	(1695, 1, 1, 821),
	(1732, 1, 1, 821),
	(1734, 1, 1, 821),
	(1736, 1, 1, 821),
	(1738, 1, 1, 821),
	(1740, 1, 1, 821),
	(1742, 1, 1, 821),
	(1744, 1, 1, 821),
	(1746, 1, 1, 821),
	(1748, 1, 1, 821),
	(1750, 1, 1, 828),
	(1752, 1, 1, 829),
	(1756, 1, 1, 821),
	(1758, 1, 1, 829),
	(1760, 1, 1, 829),
	(1762, 1, 1, 829),
	(1764, 1, 1, 828),
	(1766, 1, 1, 829),
	(1768, 1, 1, 829),
	(1770, 1, 1, 829),
	(1772, 1, 1, 829),
	(1774, 1, 1, 829),
	(1776, 1, 1, 828),
	(1778, 1, 1, 829),
	(1780, 1, 1, 828),
	(1782, 1, 1, 828),
	(1784, 1, 1, 829),
	(1786, 1, 1, 828),
	(1788, 1, 1, 828),
	(1790, 1, 1, 828),
	(1792, 1, 1, 828),
	(1794, 1, 1, 821),
	(1796, 1, 1, 828),
	(1798, 1, 1, 829),
	(1800, 1, 1, 821),
	(1802, 1, 1, 821),
	(1804, 1, 1, 821),
	(1806, 1, 1, 821),
	(1808, 1, 1, 821),
	(1810, 1, 1, 821),
	(1812, 1, 1, 821),
	(1816, 1, 1, 828),
	(1818, 1, 1, 828),
	(1820, 1, 1, 821),
	(1822, 1, 1, 828),
	(1826, 1, 1, 828),
	(1828, 1, 1, 828),
	(1830, 1, 1, 828),
	(1832, 1, 1, 821),
	(1877, 1, 1, 1173),
	(1880, 1, 1, 1174),
	(1882, 1, 1, 1174),
	(1884, 1, 1, 1174),
	(1886, 1, 1, 1174),
	(1888, 1, 1, 1173),
	(1890, 1, 1, 1173),
	(1892, 1, 1, 1173),
	(1894, 1, 1, 1174),
	(1896, 1, 1, 1172),
	(1898, 1, 1, 1172),
	(1900, 1, 1, 1172),
	(1902, 1, 1, 1174),
	(1904, 1, 1, 1174),
	(1906, 1, 1, 1174),
	(1908, 1, 1, 1172),
	(1910, 1, 1, 1174),
	(1912, 1, 1, 1172),
	(1933, 1, 1, 1174),
	(1935, 1, 1, 1174),
	(1937, 1, 1, 1174),
	(1939, 1, 1, 1174),
	(1941, 1, 1, 1174),
	(1943, 1, 1, 1174),
	(1945, 1, 1, 1174),
	(1947, 1, 1, 1174),
	(1949, 1, 1, 1174),
	(1951, 1, 1, 1173),
	(1953, 1, 1, 1173),
	(1955, 1, 1, 1173),
	(1957, 1, 1, 1173),
	(1959, 1, 1, 1173),
	(1961, 1, 1, 1173),
	(1963, 1, 1, 1173),
	(1965, 1, 1, 1173),
	(1967, 1, 1, 1173),
	(1969, 1, 1, 1174),
	(1971, 1, 1, 1174),
	(1973, 1, 1, 1174),
	(1976, 1, 1, 1174),
	(1978, 1, 1, 1174),
	(1980, 1, 1, 1174),
	(1982, 1, 1, 1174),
	(1984, 1, 1, 1172),
	(1986, 1, 1, 1172),
	(1988, 1, 1, 1172),
	(1990, 1, 1, 1172),
	(1992, 1, 1, 1172),
	(1994, 1, 1, 1172),
	(1996, 1, 1, 1172),
	(1998, 1, 1, 1172),
	(2000, 1, 1, 1172),
	(2002, 1, 1, 1172),
	(2004, 1, 1, 1172),
	(2011, 1, 1, 1174),
	(2013, 1, 1, 1174),
	(2017, 1, 1, 1174),
	(2027, 1, 1, 1172),
	(2029, 1, 1, 1172),
	(2031, 1, 1, 1172),
	(2033, 1, 1, 1172),
	(2035, 1, 1, 1172),
	(2037, 1, 1, 1172),
	(2039, 1, 1, 1172),
	(2041, 1, 1, 1174),
	(2043, 1, 1, 1174),
	(2045, 1, 1, 1174),
	(2047, 1, 1, 1174),
	(2049, 1, 1, 1174),
	(2073, 1, 1, 1174),
	(2075, 1, 1, 1172),
	(2077, 1, 1, 1173),
	(2079, 1, 1, 1173),
	(2081, 1, 1, 1172),
	(2085, 1, 1, 1174),
	(2279, 1, 1, 1174),
	(2399, 1, 1, 424),
	(2401, 1, 1, 424),
	(2403, 1, 1, 424),
	(2405, 1, 1, 424),
	(2407, 1, 1, 424),
	(2409, 1, 1, 424),
	(2411, 1, 1, 424),
	(2413, 1, 1, 424),
	(2415, 1, 1, 424),
	(2417, 1, 1, 424),
	(2419, 1, 1, 424),
	(2421, 1, 1, 424),
	(2423, 1, 1, 424),
	(2425, 1, 1, 424),
	(2427, 1, 1, 424),
	(2429, 1, 1, 424),
	(2431, 1, 1, 424),
	(2433, 1, 1, 424),
	(2435, 1, 1, 424),
	(2437, 1, 1, 424),
	(2439, 1, 1, 424),
	(2441, 1, 1, 424),
	(2443, 1, 1, 424),
	(2445, 1, 1, 424),
	(2447, 1, 1, 423),
	(2449, 1, 1, 423),
	(2451, 1, 1, 423),
	(2453, 1, 1, 423),
	(2455, 1, 1, 423),
	(2457, 1, 1, 423),
	(2459, 1, 1, 423),
	(2461, 1, 1, 423),
	(2463, 1, 1, 423),
	(2465, 1, 1, 423),
	(2467, 1, 1, 423),
	(2469, 1, 1, 423),
	(2471, 1, 1, 423),
	(2473, 1, 1, 423),
	(2475, 1, 1, 423),
	(2477, 1, 1, 423),
	(2479, 1, 1, 423),
	(2481, 1, 1, 423),
	(2483, 1, 1, 423),
	(2485, 1, 1, 423),
	(2487, 1, 1, 423),
	(2489, 1, 1, 423),
	(2491, 1, 1, 423);

REPLACE INTO `creature_model_info` VALUES (105540, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (105328, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (105213, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (112642, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (113958, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (114211, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (106003, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (107058, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (107056, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (105268, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (115279, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (115281, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (116539, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (116687, 0, 0, 0, 0);

-- ----------------------------
-- Warlock spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (5782, 'spell_warl_fear');
REPLACE INTO `spell_script_names` VALUES (204730, 'spell_warl_fear_buff');
REPLACE INTO `spell_script_names` VALUES (146739, 'spell_warl_corruption_effect');
REPLACE INTO `spell_script_names` VALUES (234153, 'spell_warlock_drain_life');
REPLACE INTO `spell_script_names` VALUES (205179, 'aura_warl_phantomatic_singularity');
REPLACE INTO `spell_script_names` VALUES (48181, 'aura_warl_haunt');
REPLACE INTO `spell_script_names` VALUES (205180, 'spell_warlock_summon_darkglare');

REPLACE INTO `creature_template` VALUES (103673, 0, 0, 'Darkglare', '', '', NULL, '', 0, 0, 954, 0, 1, 0.857143, 1, 0, 0, 1477, 2000, 1, 1, 8, 32768, 2048, 0, 19, 0, 3, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, 'npc_pet_warlock_darkglare', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (5697, 'spell_warlock_unending_breath');
REPLACE INTO `spell_script_names` VALUES (111771, 'spell_warl_demonic_gateway');

REPLACE INTO `creature_template` VALUES (59262, 0, 0, 'Demonic Gateway', '', NULL, '', 'interact', 0, 0, 35, 16777216, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 1, 512, 67108896, 17825793, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_warl_demonic_gateway', NULL, 53040);
REPLACE INTO `creature_template` VALUES (59271, 0, 0, 'Demonic Gateway', '', NULL, '', 'interact', 0, 0, 35, 16777216, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 1, 512, 67108896, 17825793, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_warl_demonic_gateway', NULL, 53040);

REPLACE INTO `npc_spellclick_spells` VALUES (59262, 113902, 0, 0);
REPLACE INTO `npc_spellclick_spells` VALUES (59271, 113902, 0, 0);

REPLACE INTO `spell_script_names` VALUES (105174, 'spell_warl_hand_of_guldan');
REPLACE INTO `spell_script_names` VALUES (86040, 'spell_warl_hand_of_guldan_damage');
REPLACE INTO `spell_script_names` VALUES (104316, 'spell_warlock_call_dreadstalkers');

REPLACE INTO `creature_template` VALUES (98035, 0, 0, 'Dreadstalker', '', '', NULL, '', 0, 0, 90, 0, 1, 1.28571, 1, 6, 0, 1444, 2000, 1, 1, 4, 0, 0, 0, 0, 0, 3, 0, '', 0, 1, 0, 133, 0, 0, 1, 0, 0, 'npc_warlock_dreadstalker', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (205231, 'spell_warl_eye_laser');
REPLACE INTO `spell_script_names` VALUES (264178, 'spell_warlock_demonbolt_new');
REPLACE INTO `spell_script_names` VALUES (205145, 'spell_warl_demonic_calling');
REPLACE INTO `spell_script_names` VALUES (157695, 'spell_warl_demonbolt');
REPLACE INTO `spell_script_names` VALUES (196277, 'spell_warl_implosion');
REPLACE INTO `spell_script_names` VALUES (603, 'spell_warlock_doom');
REPLACE INTO `spell_script_names` VALUES (6353, 'spell_warlock_soul_fire');
REPLACE INTO `spell_script_names` VALUES (196447, 'spell_warl_channel_demonfire');
REPLACE INTO `spell_script_names` VALUES (215941, 'spell_warl_soul_conduit');
REPLACE INTO `spell_script_names` VALUES (232670, 'spell_warr_shadowbolt_affliction');
REPLACE INTO `spell_script_names` VALUES (104318, 'spell_warlock_fel_firebolt_wild_imp');

REPLACE INTO `creature_template` VALUES (99739, 0, 0, 'Wild Imps', '', '', NULL, '', 0, 0, 90, 0, 1, 1.14286, 1, 0, 0, 0, 2000, 1, 1, 4, 0, 0, 0, 0, 0, 3, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, 'npc_pet_warlock_wild_imp', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (386344, 'spell_warlock_inquisitors_gaze');
REPLACE INTO `spell_script_names` VALUES (29722, 'spell_warl_incinerate');
REPLACE INTO `spell_script_names` VALUES (980, 'spell_warlock_agony');
REPLACE INTO `spell_script_names` VALUES (3110, 'spell_warlock_imp_firebolt');
REPLACE INTO `spell_script_names` VALUES (17962, 'spell_warl_conflagrate');
REPLACE INTO `spell_script_names` VALUES (17962, 'spell_warl_conflagrate_aura');
REPLACE INTO `spell_script_names` VALUES (152108, 'spell_warl_cataclysm');

-- ----------------------------
-- Warrior spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (23920, 'spell_warr_spell_reflect');
REPLACE INTO `spell_script_names` VALUES (228920, 'spell_warr_ravager');
REPLACE INTO `spell_script_names` VALUES (152277, 'spell_warr_ravager');

REPLACE INTO `creature_template` VALUES (76168, 0, 0, 'Ravager', '', '', NULL, '', 0, 0, 35, 0, 2, 0.714286, 1, 0, 0, 2000, 2000, 1, 1, 1, 33587200, 67667968, 16809984, 0, 0, 10, 0, '', 0, 1, 0, 94, 0, 0, 1, 0, 0, 'npc_warr_ravager', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (156287, 'spell_warr_ravager_damage');
REPLACE INTO `spell_script_names` VALUES (190456, 'spell_warr_ignore_pain');
REPLACE INTO `spell_script_names` VALUES (12975,	'spell_warr_last_stand');
REPLACE INTO `spell_script_names` VALUES (64380, 'spell_warr_shattering_throw');
REPLACE INTO `spell_script_names` VALUES (65941, 'spell_warr_shattering_throw');
REPLACE INTO `spell_script_names` VALUES (469, 'spell_warr_shout');
REPLACE INTO `spell_script_names` VALUES (6673, 'spell_warr_shout');
REPLACE INTO `spell_script_names` VALUES (1680, 'spell_warr_wirlwind_dmg');
REPLACE INTO `spell_script_names` VALUES (385952, 'spell_warr_shiel_charge');
REPLACE INTO `spell_script_names` VALUES (190411, 'spell_warr_whirlwind');
REPLACE INTO `spell_script_names` VALUES (76856, 'spell_warr_unshackled_fury');
REPLACE INTO `spell_script_names` VALUES (184361, 'spell_warr_enrage');
REPLACE INTO `spell_script_names` VALUES (184362, 'spell_warr_enrage_aura');
REPLACE INTO `spell_script_names` VALUES (215571, 'spell_warr_frothing_berserker');
REPLACE INTO `spell_script_names` VALUES (214871, 'spell_warr_odyns_fury');
REPLACE INTO `spell_script_names` VALUES (7384, 'spell_warr_overpower');
REPLACE INTO `spell_script_names` VALUES (6343, 'spell_warr_thunder_clap');
REPLACE INTO `spell_script_names` VALUES (845, 'spell_warr_cleave_dmg');

-- ----------------------------
-- Mage spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (153561, 'spell_mage_meteor');
REPLACE INTO `spell_script_names` VALUES (153564, 'spell_mage_meteor_damage');

REPLACE INTO `areatrigger_scripts` VALUES (8089, 'at_mage_meteor_timer');
REPLACE INTO `areatrigger_scripts` VALUES (6211, 'at_mage_meteor_burn');

REPLACE INTO `areatrigger_create_properties` VALUES (177345, 1, 8089, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 3000, 4, 8, 8, 4, 4, 0.3, 0.3, 0, 0, 'at_mage_meteor_timer', 27101);

REPLACE INTO `spell_script_names` VALUES (205025, 'spell_mage_presence_of_mind');

REPLACE INTO `areatrigger_scripts` VALUES (1612, 'at_mage_arcane_orb');
REPLACE INTO `areatrigger_scripts` VALUES (8661,'at_mage_frozen_orb');

REPLACE INTO `spell_script_names` VALUES (148022, 'spell_mage_icicle_damage');
REPLACE INTO `spell_script_names` VALUES (76613, 'spell_mastery_icicles_proc');
REPLACE INTO `spell_script_names` VALUES (148023, 'spell_mastery_icicles_periodic');
REPLACE INTO `spell_script_names` VALUES (214124, 'spell_mastery_icicles_mod_aura');
REPLACE INTO `spell_script_names` VALUES (214125, 'spell_mastery_icicles_mod_aura');
REPLACE INTO `spell_script_names` VALUES (214126, 'spell_mastery_icicles_mod_aura');
REPLACE INTO `spell_script_names` VALUES (214127, 'spell_mastery_icicles_mod_aura');
REPLACE INTO `spell_script_names` VALUES (214130, 'spell_mastery_icicles_mod_aura');
REPLACE INTO `spell_script_names` VALUES (199786, 'spell_mastery_icicles_glacial_spike');

-- ----------------------------
-- DK spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (48792,	'spell_dk_icebound_fortitude');
REPLACE INTO `spell_script_names` VALUES (196782, 'aura_dk_outbreak_periodic');
REPLACE INTO `spell_script_names` VALUES (115994, 'spell_dk_unholy_blight');
REPLACE INTO `spell_script_names` VALUES (55090, 'spell_dk_scourge_strike');
REPLACE INTO `spell_script_names` VALUES (152280, 'aura_dk_defile');

REPLACE INTO `areatrigger_scripts` VALUES (6212, 'at_dk_defile');

REPLACE INTO `creature_template` VALUES (82521, 0, 0, 'Defile', '', '', NULL, '', 0, 0, 1, 0, 1, 1, 1, 0, 0, 2000, 2000, 1, 1, 1, 17826816, 16, 0, 0, 0, 10, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_dk_defile', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (156004, 'spell_dk_defile_aura');
REPLACE INTO `spell_script_names` VALUES (215969, 'spell_dk_epidemic');
REPLACE INTO `spell_script_names` VALUES (215969, 'spell_dk_epidemic_aoe');

-- ----------------------------
-- Evoker spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (369536, 'spell_evo_soar');
REPLACE INTO `spell_script_names` VALUES (351239, 'spell_evo_cosmic_visage');
REPLACE INTO `spell_script_names` VALUES (359073, 'spell_evo_eternity_surge');

-- ----------------------------
-- Hunter spell fixes
-- ----------------------------
REPLACE INTO `areatrigger_create_properties` VALUES (4424, 0, 9170, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_freezing_trap', 48999);
REPLACE INTO `areatrigger_create_properties` VALUES (510, 0, 3678, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 20000, 4, 10, 10, 7, 7, 3, 3, 0, 0, 'at_hun_flare', 40120);

REPLACE INTO `spell_script_names` VALUES (34026, 'spell_hun_kill_command');
REPLACE INTO `spell_script_names` VALUES (259489, 'spell_hun_kill_command');
REPLACE INTO `spell_script_names` VALUES (83381, 'spell_hun_kill_command_proc');
REPLACE INTO `spell_script_names` VALUES (19577, 'spell_hun_intimidation');
REPLACE INTO `spell_script_names` VALUES (19574, 'spell_hun_bestial_wrath');
REPLACE INTO `spell_script_names` VALUES (217200, 'spell_hun_barbed_shot');
REPLACE INTO `spell_script_names` VALUES (120679, 'spell_hun_dire_beast');

REPLACE INTO `areatrigger_create_properties` VALUES (1524, 0, 5972, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 4, 5, 5, 2, 2, 0.3, 0.3, 0, 0, 'at_hun_binding_shot', 31478);

REPLACE INTO `spell_script_names` VALUES (321530, 'spell_hun_bloodshed');
REPLACE INTO `spell_script_names` VALUES (260243, 'spell_hun_volley');
REPLACE INTO `spell_script_names` VALUES (186387, 'spell_bursting_shot');

REPLACE INTO `areatrigger_create_properties` VALUES (2392, 0, 6966, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_steel_trap', 48999);

REPLACE INTO `spell_script_names` VALUES (120361, 'spell_hun_barrage');
REPLACE INTO `spell_script_names` VALUES (269751, 'spell_hun_flanking_strike');
REPLACE INTO `spell_script_names` VALUES (360966, 'spell_hun_spearhead');
REPLACE INTO `spell_script_names` VALUES (259495, 'spell_hunter_wildfire_bomb');
REPLACE INTO `spell_script_names` VALUES (271014, 'spell_hunter_wildfire_infusion_talent');
REPLACE INTO `spell_script_names` VALUES (271615, 'spell_hunter_wildfire_infusion_dummy');

REPLACE INTO `areatrigger_scripts` VALUES (12863, 'at_hunter_wildfire_bomb');

REPLACE INTO `areatrigger_template` VALUES (265163, 0, 0, 0, 0, 0);

REPLACE INTO `areatrigger_create_properties` VALUES (12863, 0, 265163, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 'at_hunter_wildfire_bomb', 0);

-- ----------------------------
-- Rogue spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (115191, 'spell_rog_stealth_with_subterfuge');
REPLACE INTO `spell_script_names` VALUES (115191, 'spell_rog_stealth');
REPLACE INTO `spell_script_names` VALUES (14062, 'spell_rog_nightstalker');
REPLACE INTO `spell_script_names` VALUES (5171, 'spell_rog_slice_and_dice');
REPLACE INTO `spell_script_names` VALUES (315496, 'spell_rog_slice_and_dice');
REPLACE INTO `spell_script_names` VALUES (385616, 'spell_rog_echoing_reprimand');
REPLACE INTO `spell_script_names` VALUES (2823, 'spell_rog_deadly_poison_instant_damage');
REPLACE INTO `spell_script_names` VALUES (51723, 'spell_rog_fan_of_knives');
REPLACE INTO `spell_script_names` VALUES (195457, 'spell_rog_grappling_hook');
REPLACE INTO `spell_script_names` VALUES (271877, 'spell_rog_blade_rush');
REPLACE INTO `spell_script_names` VALUES (197835, 'spell_rog_shuriken_storm');

-- ----------------------------
-- Paladin spell fixes
-- ----------------------------

-- ----------------------------
-- Monk spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (126892, 'spell_monk_zen_pilgrimage');
REPLACE INTO `spell_script_names` VALUES (293866, 'spell_monk_zen_pilgrimage');
REPLACE INTO `spell_script_names` VALUES (126895, 'spell_monk_zen_pilgrimage_return');
REPLACE INTO `spell_script_names` VALUES (100780, 'spell_monk_tiger_palm');
REPLACE INTO `spell_script_names` VALUES (125883, 'spell_monk_zen_flight_check');
REPLACE INTO `spell_script_names` VALUES (116095, 'spell_monk_disable');
REPLACE INTO `spell_script_names` VALUES (116705, 'spell_monk_spear_hand_strike');
REPLACE INTO `spell_script_names` VALUES (115203, 'spell_monk_fortifying_brew');
REPLACE INTO `spell_script_names` VALUES (119582, 'spell_monk_purifying_brew');
REPLACE INTO `spell_script_names` VALUES (115181, 'spell_monk_breath_of_fire');
REPLACE INTO `spell_script_names` VALUES (122278, 'spell_monk_dampen_harm');
REPLACE INTO `spell_script_names` VALUES (122280, 'spell_monk_healing_elixirs_aura');

REPLACE INTO `areatrigger_scripts` VALUES (3983, 'at_monk_ring_of_peace');
REPLACE INTO `areatrigger_scripts` VALUES (5484, 'at_monk_song_of_chi_ji');

REPLACE INTO `areatrigger_create_properties` VALUES (718, 0, 3983, 0, 0, 0, 0, 0, 0, -256, 255, 0, 0, 0, 5000, 0, 8, 8, 0, 0, 0, 0, 0, 0, 'at_monk_ring_of_peace', 40120);
REPLACE INTO `areatrigger_create_properties` VALUES (5484, 0, 10191, 0, 0, 0, 1656, 0, 0, -1, 0, 0, 0, 5716, 5000, 0, 5, 5, 0, 0, 0, 0, 0, 0, 'at_monk_song_of_chi_ji', 48838);

REPLACE INTO `spell_script_names` VALUES (115098, 'spell_monk_chi_wave');
REPLACE INTO `spell_script_names` VALUES (132467, 'spell_monk_chi_wave_damage_missile');
REPLACE INTO `spell_script_names` VALUES (132464, 'spell_monk_chi_wave_heal_missile');
REPLACE INTO `spell_script_names` VALUES (132464, 'spell_monk_chi_wave_healing_bolt');

REPLACE INTO `areatrigger_scripts` VALUES (5300, 'at_monk_chi_burst');

REPLACE INTO `areatrigger_create_properties` VALUES (1316, 0, 5300, 0, 0, 392, 0, 0, 0, -1, 0, 0, 0, 931, 1000, 0, 5, 5, 0, 0, 0, 0, 0, 0, 'at_monk_chi_burst', 40120);

REPLACE INTO `spell_script_names` VALUES (130654, 'spell_monk_chi_burst_heal');
REPLACE INTO `spell_script_names` VALUES (115399, 'spell_monk_black_ox_brew');
REPLACE INTO `spell_script_names` VALUES (115313, 'spell_monk_jade_serpent_statue');

REPLACE INTO `creature_template` VALUES (60849, 0, 0, 'Jade Serpent Statue', '', '', NULL, '', 0, 0, 5, 0, 1, 1.14286, 1, 0, 0, 1798, 2000, 1, 1, 1, 512, 32800, 0, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_monk_jade_serpent_statue', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (101643, 'spell_monk_transcendence');
REPLACE INTO `spell_script_names` VALUES (101643, 'aura_monk_transcendence');
REPLACE INTO `spell_script_names` VALUES (119996, 'spell_monk_transcendence_transfer');
REPLACE INTO `spell_script_names` VALUES (116670, 'spell_monk_vivify');
REPLACE INTO `spell_script_names` VALUES (115175, 'spell_monk_soothing_mist');
REPLACE INTO `spell_script_names` VALUES (116680, 'spell_focused_thunder_talent_thunder_focus_tea');
REPLACE INTO `spell_script_names` VALUES (124081, 'spell_monk_zen_pulse');
REPLACE INTO `spell_script_names` VALUES (115151, 'spell_monk_renewing_mist');
REPLACE INTO `spell_script_names` VALUES (115151, 'spell_monk_renewing_mist_hot');
REPLACE INTO `spell_script_names` VALUES (119607, 'spell_monk_renewing_mist_jump');
REPLACE INTO `spell_script_names` VALUES (191837, 'spell_monk_essence_font');
REPLACE INTO `spell_script_names` VALUES (191840, 'spell_monk_essence_font_heal');
REPLACE INTO `spell_script_names` VALUES (124682, 'spell_monk_enveloping_mist');
REPLACE INTO `spell_script_names` VALUES (122470, 'spell_monk_touch_of_karma');
REPLACE INTO `spell_script_names` VALUES (125174, 'spell_monk_touch_of_karma_buff');
REPLACE INTO `spell_script_names` VALUES (113656, 'spell_monk_fists_of_fury');
REPLACE INTO `spell_script_names` VALUES (117418, 'spell_monk_fists_of_fury_damage');
REPLACE INTO `spell_script_names` VALUES (120086, 'spell_monk_fists_of_fury_stun');
REPLACE INTO `spell_script_names` VALUES (123154, 'spell_monk_fists_of_fury_visual');
REPLACE INTO `spell_script_names` VALUES (117418, 'spell_monk_fists_of_fury_visual_filter');

REPLACE INTO `creature_template` VALUES (63508, 0, 0, 'Xuen', '', NULL, NULL, NULL, 0, 0, 35, 0, 1, 1.54286, 1, 0, 0, 721, 2000, 1, 1, 1, 32784, 2048, 0, 0, 0, 1, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, 'npc_monk_xuen', NULL, 53040);

REPLACE INTO `spell_script_names` VALUES (115057, 'spell_monk_flying_serpent_kick');

REPLACE INTO `spell_linked_spell` VALUES (113656, 165144, 0, 'Fists of Fury visual fix');
REPLACE INTO `spell_linked_spell` VALUES (324312, 324383, 0, 'Monk Clash spell fix');
REPLACE INTO `spell_linked_spell` VALUES (152175, 158221, 0, 'Monk Whirling Dragon Punch Damage');

REPLACE INTO `spell_script_names` VALUES (113656, 'spell_fist_of_fury_proc');
REPLACE INTO `spell_script_names` VALUES (107428, 'spell_rising_sun_kick_proc');
REPLACE INTO `spell_script_names` VALUES (152175, 'spell_monk_whirling_dragon_punch');

-- ----------------------------
-- DH spell fixes
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (195072, 'spell_dh_fel_rush');
REPLACE INTO `spell_script_names` VALUES (197923, 'spell_dh_fel_rush_dash');
REPLACE INTO `spell_script_names` VALUES (197922, 'spell_dh_fel_rush_dash_ground');
REPLACE INTO `spell_script_names` VALUES (223107, 'spell_dh_fel_rush_damage');
REPLACE INTO `spell_script_names` VALUES (203556, 'spell_dh_master_of_the_glaive');
REPLACE INTO `spell_script_names` VALUES (211881, 'spell_dh_fel_eruption');
REPLACE INTO `spell_script_names` VALUES (209258, 'spell_dh_last_resort');
REPLACE INTO `spell_script_names` VALUES (191427, 'spell_dh_metamorphosis');
REPLACE INTO `spell_script_names` VALUES (201453, 'spell_dh_metamorphosis_immunity');
REPLACE INTO `spell_script_names` VALUES (206473, 'spell_dh_bloodlet');
REPLACE INTO `spell_script_names` VALUES (211053, 'spell_dh_fel_barrage');
REPLACE INTO `spell_script_names` VALUES (222703, 'spell_dh_fel_barrage_damage');
REPLACE INTO `spell_script_names` VALUES (222703, 'spell_dh_fel_barrage_aura');
REPLACE INTO `spell_script_names` VALUES (206491, 'spell_dh_nemesis');
REPLACE INTO `spell_script_names` VALUES (189110, 'spell_dh_infernal_strike');
REPLACE INTO `spell_script_names` VALUES (228477, 'spell_dh_soul_cleave');
REPLACE INTO `spell_script_names` VALUES (228478, 'spell_dh_soul_cleave_damage');
REPLACE INTO `spell_script_names` VALUES (204021, 'spell_dh_fiery_brand');
REPLACE INTO `spell_script_names` VALUES (207771, 'spell_dh_fiery_brand_dot');
REPLACE INTO `spell_script_names` VALUES (209400, 'spell_dh_razor_spikes');
REPLACE INTO `spell_script_names` VALUES (263648, 'spell_dh_soul_barrier');
REPLACE INTO `spell_script_names` VALUES (207810, 'spell_dh_nether_bond');
REPLACE INTO `spell_script_names` VALUES (207811, 'spell_dh_nether_bond_periodic');
REPLACE INTO `spell_script_names` VALUES (211509, 'spell_dh_solitude');
REPLACE INTO `spell_script_names` VALUES (205598, 'spell_dh_awaken_the_demon');
REPLACE INTO `spell_script_names` VALUES (205604, 'spell_dh_reverse_magic');
REPLACE INTO `spell_script_names` VALUES (206649, 'spell_dh_eye_of_leotheras');
REPLACE INTO `spell_script_names` VALUES (258920, 'spell_dh_immolation_aura');
REPLACE INTO `spell_script_names` VALUES (258922, 'spell_dh_immolation_aura_damage');
REPLACE INTO `spell_script_names` VALUES (208796, 'spell_dh_jagged_spikes');
REPLACE INTO `spell_script_names` VALUES (206966, 'spell_dh_fel_lance');
REPLACE INTO `spell_script_names` VALUES (206891, 'spell_dh_intimidated');
REPLACE INTO `spell_script_names` VALUES (203753, 'spell_dh_blade_turning');
REPLACE INTO `spell_script_names` VALUES (209651, 'spell_dh_shattered_souls_missile');
REPLACE INTO `spell_script_names` VALUES (203783, 'spell_dh_shear_proc');
REPLACE INTO `spell_script_names` VALUES (210047, 'spell_dh_consume_soul_missile');
REPLACE INTO `spell_script_names` VALUES (209426, 'spell_dh_darkness_absorb');
REPLACE INTO `spell_script_names` VALUES (203650, 'spell_dh_prepared');
REPLACE INTO `spell_script_names` VALUES (206478, 'spell_dh_demonic_appetite');
REPLACE INTO `spell_script_names` VALUES (228532, 'spell_dh_soul_fragment_heals');
REPLACE INTO `spell_script_names` VALUES (206475, 'spell_dh_chaos_cleave');
REPLACE INTO `spell_script_names` VALUES (205411, 'spell_dh_desperate_instincts');
REPLACE INTO `spell_script_names` VALUES (209795, 'spell_dh_fracture');
REPLACE INTO `spell_script_names` VALUES (224509, 'spell_dh_frailty');
REPLACE INTO `spell_script_names` VALUES (247454, 'spell_dh_spirit_bomb');
REPLACE INTO `spell_script_names` VALUES (236189, 'spell_dh_demonic_infusion');
REPLACE INTO `spell_script_names` VALUES (206803, 'spell_demon_hunter_rain_from_above');
REPLACE INTO `spell_script_names` VALUES (162264, 'spell_demon_hunter_metamorphosis_buffs');
REPLACE INTO `spell_script_names` VALUES (212105, 'spell_dh_fel_devastation_damage');
REPLACE INTO `spell_script_names` VALUES (162794, 'spell_demon_hunter_chaos_strike');
REPLACE INTO `spell_script_names` VALUES (185244, 'spell_demon_hunter_pain');
REPLACE INTO `spell_script_names` VALUES (203704, 'spell_demon_hunter_mana_break');
REPLACE INTO `spell_script_names` VALUES (258881, 'spell_demon_hunter_trail_of_ruin');
REPLACE INTO `spell_script_names` VALUES (213480, 'spell_demon_hunter_unending_hatred');
REPLACE INTO `spell_script_names` VALUES (203720, 'spell_dh_demon_spikes');
REPLACE INTO `spell_script_names` VALUES (201427, 'spell_dh_annihilation');
REPLACE INTO `spell_script_names` VALUES (344862, 'spell_dh_chaos_strike_specless');
REPLACE INTO `spell_script_names` VALUES (344865, 'spell_dh_fel_rush_specless');

REPLACE INTO `areatrigger_scripts` VALUES (6615, 'at_dh_darkness');
REPLACE INTO `areatrigger_scripts` VALUES (9695, 'at_demon_hunter_mana_rift');
REPLACE INTO `areatrigger_scripts` VALUES (6482, 'at_demon_hunter_demonic_trample');
REPLACE INTO `areatrigger_scripts` VALUES (10666, 'at_shattered_soul_fragment');

REPLACE INTO `areatrigger_create_properties` VALUES (6482, 1, 11107, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'at_demon_hunter_demonic_trample', 40120);
REPLACE INTO `areatrigger_create_properties` VALUES (6007, 1, 10666, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 20000, 0, 1, 1, 0, 0, 0, 0, 0, 0, 'at_shattered_soul_fragment', 32750);

-- ----------------------------
-- Misc fix or changes
-- ----------------------------

REPLACE INTO `creature_template` VALUES (102199, 0, 0, 'Stampede', '', '', NULL, '',	0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 1028, 2000, 1, 1, 1, 33554944, 0, 16777216, 0, 0, 10, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, '', NULL, 53040);
REPLACE INTO `creature_template` VALUES (73967, 0, 0, 'Niuzao', '', '', NULL, '', 0, 0, 35, 0, 1, 0.857143, 1, 0, 0, 1989, 2000, 1, 1, 1, 32768, 2048, 0, 0, 0, 1, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, '', NULL, 53040);

ALTER TABLE `scrapping_loot_template` ADD `ItemType` tinyint NOT NULL DEFAULT 0 AFTER `Entry`;

-- ----------------------------
-- Toys fix
-- ----------------------------

REPLACE INTO `spell_script_names` VALUES (340110, 'spell_necronom_i_nom');
REPLACE INTO `spell_script_names` VALUES (291106, 'spell_bowl_of_glowing_pufferfish');
REPLACE INTO `spell_script_names` VALUES (232592, 'spell_twelve_string_guitar');

-- ----------------------------
-- Advanced fly
-- ----------------------------

REPLACE INTO `spell_linked_spell` VALUES (372771, 372773, 0, 'Dragonriding energy aura');

REPLACE INTO `spell_script_names` VALUES (373646, 'spell_af_skyriding');
REPLACE INTO `spell_script_names` VALUES (406095, 'spell_af_skyriding');
REPLACE INTO `spell_script_names` VALUES (430747, 'spell_af_skyriding');
REPLACE INTO `spell_script_names` VALUES (430833, 'spell_af_skyriding');
REPLACE INTO `spell_script_names` VALUES (372771, 'spell_af_energy');
REPLACE INTO `spell_script_names` VALUES (372773, 'spell_af_energy');
REPLACE INTO `spell_script_names` VALUES (372610, 'spell_af_skyward_ascent');
REPLACE INTO `spell_script_names` VALUES (374763, 'spell_af_skyward_ascent');
REPLACE INTO `spell_script_names` VALUES (386451, 'spell_af_skyward_ascent');
REPLACE INTO `spell_script_names` VALUES (372608, 'spell_af_surge_forward');
REPLACE INTO `spell_script_names` VALUES (386449, 'spell_af_surge_forward');
REPLACE INTO `spell_script_names` VALUES (361584, 'spell_af_whirling_surge');
REPLACE INTO `spell_script_names` VALUES (436854, 'spell_switch_flight');