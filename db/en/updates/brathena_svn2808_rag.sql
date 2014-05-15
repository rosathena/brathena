#2808
ALTER TABLE `char` ADD COLUMN `uniqueitem_counter`  bigint(20) NOT NULL AFTER `unban_time`;
REPLACE INTO `brathena_updates` VALUES('brathena_r2808');
