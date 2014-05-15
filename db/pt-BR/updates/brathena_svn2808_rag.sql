#2808
ALTER TABLE `char` ADD COLUMN `uniqueitem_counter`  bigint(20) unsigned NOT NULL default '0';
REPLACE INTO `brathena_updates` VALUES('brathena_r2808');
