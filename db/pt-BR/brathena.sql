/*_________________________________________________________________________
 /                                                                         \
 |                  _           _   _   _                                  |
 |                 | |__  _ __ / \ | |_| |__   ___ _ __   __ _             |
 |                 | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |            |
 |                 | |_) | | / ___ \ |_| | | |  __/ | | | (_| |            |
 |                 |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|            |
 |                                                                         |
 |                       brAthena � 2013 - Banco de Dados                  |
 |      Cont�m as tabelas para funcionamento dos sistemas do emulador      |
 \_________________________________________________________________________/
*/

--
-- Estrutura da tabela `auction`
--

CREATE TABLE IF NOT EXISTS `auction` (
  `auction_id` bigint(20) unsigned NOT NULL auto_increment,
  `seller_id` int(11) unsigned NOT NULL default '0',
  `seller_name` varchar(30) NOT NULL default '',
  `buyer_id` int(11) unsigned NOT NULL default '0',
  `buyer_name` varchar(30) NOT NULL default '',
  `price` int(11) unsigned NOT NULL default '0',
  `buynow` int(11) unsigned NOT NULL default '0',
  `hours` smallint(6) NOT NULL default '0',
  `timestamp` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) unsigned NOT NULL default '0',
  `item_name` varchar(50) NOT NULL default '',
  `type` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) unsigned NOT NULL default '0',
  `card0` smallint(11) NOT NULL default '0',
  `card1` smallint(11) NOT NULL default '0',
  `card2` smallint(11) NOT NULL default '0',
  `card3` smallint(11) NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`auction_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `cart_inventory`
--

CREATE TABLE IF NOT EXISTS `cart_inventory` (
  `id` int(11) NOT NULL auto_increment,
  `char_id` int(11) NOT NULL default '0',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) NOT NULL default '0',
  `card0` smallint(11) NOT NULL default '0',
  `card1` smallint(11) NOT NULL default '0',
  `card2` smallint(11) NOT NULL default '0',
  `card3` smallint(11) NOT NULL default '0',
  `expire_time` int(11) unsigned NOT NULL default '0',
  `bound` tinyint(1) unsigned NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `char`
--

CREATE TABLE IF NOT EXISTS `char` (
  `char_id` int(11) unsigned NOT NULL auto_increment,
  `account_id` int(11) unsigned NOT NULL default '0',
  `char_num` tinyint(1) NOT NULL default '0',
  `name` varchar(30) NOT NULL DEFAULT '',
  `class` smallint(6) unsigned NOT NULL default '0',
  `base_level` smallint(6) unsigned NOT NULL default '1',
  `job_level` smallint(6) unsigned NOT NULL default '1',
  `base_exp` bigint(20) unsigned NOT NULL default '0',
  `job_exp` bigint(20) unsigned NOT NULL default '0',
  `zeny` int(11) unsigned NOT NULL default '0',
  `str` smallint(4) unsigned NOT NULL default '0',
  `agi` smallint(4) unsigned NOT NULL default '0',
  `vit` smallint(4) unsigned NOT NULL default '0',
  `int` smallint(4) unsigned NOT NULL default '0',
  `dex` smallint(4) unsigned NOT NULL default '0',
  `luk` smallint(4) unsigned NOT NULL default '0',
  `max_hp` mediumint(8) unsigned NOT NULL default '0',
  `hp` mediumint(8) unsigned NOT NULL default '0',
  `max_sp` mediumint(6) unsigned NOT NULL default '0',
  `sp` mediumint(6) unsigned NOT NULL default '0',
  `status_point` int(11) unsigned NOT NULL default '0',
  `skill_point` int(11) unsigned NOT NULL default '0',
  `option` int(11) NOT NULL default '0',
  `karma` tinyint(3) NOT NULL default '0',
  `manner` smallint(6) NOT NULL default '0',
  `party_id` int(11) unsigned NOT NULL default '0',
  `guild_id` int(11) unsigned NOT NULL default '0',
  `pet_id` int(11) unsigned NOT NULL default '0',
  `homun_id` int(11) unsigned NOT NULL default '0',
  `elemental_id` int(11) unsigned NOT NULL default '0',
  `hair` tinyint(4) unsigned NOT NULL default '0',
  `hair_color` smallint(5) unsigned NOT NULL default '0',
  `clothes_color` smallint(5) unsigned NOT NULL default '0',
  `weapon` smallint(6) unsigned NOT NULL default '0',
  `shield` smallint(6) unsigned NOT NULL default '0',
  `head_top` smallint(6) unsigned NOT NULL default '0',
  `head_mid` smallint(6) unsigned NOT NULL default '0',
  `head_bottom` smallint(6) unsigned NOT NULL default '0',
  `robe` SMALLINT(6) UNSIGNED NOT NULL DEFAULT '0',
  `last_map` varchar(11) NOT NULL default '',
  `last_x` smallint(4) unsigned NOT NULL default '53',
  `last_y` smallint(4) unsigned NOT NULL default '111',
  `save_map` varchar(11) NOT NULL default '',
  `save_x` smallint(4) unsigned NOT NULL default '53',
  `save_y` smallint(4) unsigned NOT NULL default '111',
  `partner_id` int(11) unsigned NOT NULL default '0',
  `online` tinyint(2) NOT NULL default '0',
  `father` int(11) unsigned NOT NULL default '0',
  `mother` int(11) unsigned NOT NULL default '0',
  `child` int(11) unsigned NOT NULL default '0',
  `fame` int(11) unsigned NOT NULL default '0',
  `rename` SMALLINT(3) unsigned NOT NULL default '0',
  `delete_date` INT(11) unsigned NOT NULL DEFAULT '0',
  `slotchange` SMALLINT(3) unsigned NOT NULL default '0',
  `char_opt` INT( 11 ) unsigned NOT NULL default '0',
  `font` TINYINT( 3 ) UNSIGNED NOT NULL DEFAULT  '0',
  `unban_time` int(11) unsigned NOT NULL default '0',
  `uniqueitem_counter` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`char_id`),
  UNIQUE KEY `name_key` (`name`),
  KEY `account_id` (`account_id`),
  KEY `party_id` (`party_id`),
  KEY `guild_id` (`guild_id`),
  KEY `online` (`online`)
) ENGINE=MyISAM AUTO_INCREMENT=150000; 

--
-- Estrutura da tabela `charlog`
--

CREATE TABLE IF NOT EXISTS `charlog` (
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `char_msg` varchar(255) NOT NULL default 'personagem selecionado',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) unsigned NOT NULL default '0',
  `char_num` tinyint(4) NOT NULL default '0',
  `name` varchar(23) NOT NULL default '',
  `str` int(11) unsigned NOT NULL default '0',
  `agi` int(11) unsigned NOT NULL default '0',
  `vit` int(11) unsigned NOT NULL default '0',
  `int` int(11) unsigned NOT NULL default '0',
  `dex` int(11) unsigned NOT NULL default '0',
  `luk` int(11) unsigned NOT NULL default '0',
  `hair` tinyint(4) NOT NULL default '0',
  `hair_color` int(11) NOT NULL default '0'
) ENGINE=MyISAM; 

--
-- Estrutura da tabela `elemental`
--

CREATE TABLE IF NOT EXISTS `elemental` (
  `ele_id` int(11) unsigned NOT NULL auto_increment,
  `char_id` int(11) NOT NULL,
  `class` mediumint(9) unsigned NOT NULL default '0',
  `mode` int(11) unsigned NOT NULL default '1',
  `hp` int(12) NOT NULL default '1',
  `sp` int(12) NOT NULL default '1',
  `max_hp` mediumint(8) unsigned NOT NULL default '0',
  `max_sp` mediumint(6) unsigned NOT NULL default '0',
  `atk1` mediumint(6) unsigned NOT NULL default '0',
  `atk2` mediumint(6) unsigned NOT NULL default '0',
  `matk` mediumint(6) unsigned NOT NULL default '0',
  `aspd` smallint(4) unsigned NOT NULL default '0',
  `def` smallint(4) unsigned NOT NULL default '0',
  `mdef` smallint(4) unsigned NOT NULL default '0',
  `flee` smallint(4) unsigned NOT NULL default '0',
  `hit` smallint(4) unsigned NOT NULL default '0',
  `life_time` int(11) NOT NULL default '0',
  PRIMARY KEY  (`ele_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `friends`
--

CREATE TABLE IF NOT EXISTS `friends` (
  `char_id` int(11) NOT NULL default '0',
  `friend_account` int(11) NOT NULL default '0',
  `friend_id` int(11) NOT NULL default '0',
  KEY  `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `hotkey`
--

CREATE TABLE IF NOT EXISTS `hotkey` (
	`char_id` INT(11) NOT NULL,
	`hotkey` TINYINT(2) unsigned NOT NULL,
	`type` TINYINT(1) unsigned NOT NULL default '0',
	`itemskill_id` INT(11) unsigned NOT NULL default '0',
	`skill_lvl` TINYINT(4) unsigned NOT NULL default '0',
	PRIMARY KEY (`char_id`,`hotkey`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild`
--

CREATE TABLE IF NOT EXISTS `guild` (
  `guild_id` int(11) unsigned NOT NULL auto_increment,
  `name` varchar(24) NOT NULL default '',
  `char_id` int(11) unsigned NOT NULL default '0',
  `master` varchar(24) NOT NULL default '',
  `guild_lv` tinyint(6) unsigned NOT NULL default '0',
  `connect_member` tinyint(6) unsigned NOT NULL default '0',
  `max_member` tinyint(6) unsigned NOT NULL default '0',
  `average_lv` smallint(6) unsigned NOT NULL default '1',
  `exp` bigint(20) unsigned NOT NULL default '0',
  `next_exp` int(11) unsigned NOT NULL default '0',
  `skill_point` tinyint(11) unsigned NOT NULL default '0',
  `mes1` varchar(60) NOT NULL default '',
  `mes2` varchar(120) NOT NULL default '',
  `emblem_len` int(11) unsigned NOT NULL default '0',
  `emblem_id` int(11) unsigned NOT NULL default '0',
  `emblem_data` blob,
  PRIMARY KEY  (`guild_id`,`char_id`),
  UNIQUE KEY `guild_id` (`guild_id`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_alliance`
--

CREATE TABLE IF NOT EXISTS `guild_alliance` (
  `guild_id` int(11) unsigned NOT NULL default '0',
  `opposition` int(11) unsigned NOT NULL default '0',
  `alliance_id` int(11) unsigned NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  PRIMARY KEY  (`guild_id`,`alliance_id`),
  KEY `alliance_id` (`alliance_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_castle`
--

CREATE TABLE IF NOT EXISTS `guild_castle` (
  `castle_id` int(11) unsigned NOT NULL default '0',
  `guild_id` int(11) unsigned NOT NULL default '0',
  `economy` int(11) unsigned NOT NULL default '0',
  `defense` int(11) unsigned NOT NULL default '0',
  `triggerE` int(11) unsigned NOT NULL default '0',
  `triggerD` int(11) unsigned NOT NULL default '0',
  `nextTime` int(11) unsigned NOT NULL default '0',
  `payTime` int(11) unsigned NOT NULL default '0',
  `createTime` int(11) unsigned NOT NULL default '0',
  `visibleC` int(11) unsigned NOT NULL default '0',
  `visibleG0` int(11) unsigned NOT NULL default '0',
  `visibleG1` int(11) unsigned NOT NULL default '0',
  `visibleG2` int(11) unsigned NOT NULL default '0',
  `visibleG3` int(11) unsigned NOT NULL default '0',
  `visibleG4` int(11) unsigned NOT NULL default '0',
  `visibleG5` int(11) unsigned NOT NULL default '0',
  `visibleG6` int(11) unsigned NOT NULL default '0',
  `visibleG7` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`castle_id`),
  KEY `guild_id` (`guild_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_expulsion`
--

CREATE TABLE IF NOT EXISTS `guild_expulsion` (
  `guild_id` int(11) unsigned NOT NULL default '0',
  `account_id` int(11) unsigned NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `mes` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`guild_id`,`name`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_member`
--

CREATE TABLE IF NOT EXISTS `guild_member` (
  `guild_id` int(11) unsigned NOT NULL default '0',
  `account_id` int(11) unsigned NOT NULL default '0',
  `char_id` int(11) unsigned NOT NULL default '0',
  `hair` tinyint(6) unsigned NOT NULL default '0',
  `hair_color` smallint(6) unsigned NOT NULL default '0',
  `gender` tinyint(6) unsigned NOT NULL default '0',
  `class` smallint(6) unsigned NOT NULL default '0',
  `lv` smallint(6) unsigned NOT NULL default '0',
  `exp` bigint(20) unsigned NOT NULL default '0',
  `exp_payper` tinyint(11) unsigned NOT NULL default '0',
  `online` tinyint(4) unsigned NOT NULL default '0',
  `position` tinyint(6) unsigned NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  PRIMARY KEY  (`guild_id`,`char_id`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_position`
--

CREATE TABLE IF NOT EXISTS `guild_position` (
  `guild_id` int(9) unsigned NOT NULL default '0',
  `position` tinyint(6) unsigned NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `mode` tinyint(11) unsigned NOT NULL default '0',
  `exp_mode` tinyint(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`guild_id`,`position`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_skill`
--

CREATE TABLE IF NOT EXISTS `guild_skill` (
  `guild_id` int(11) unsigned NOT NULL default '0',
  `id` smallint(11) unsigned NOT NULL default '0',
  `lv` tinyint(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`guild_id`,`id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `guild_storage`
--

CREATE TABLE IF NOT EXISTS `guild_storage` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `guild_id` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) unsigned NOT NULL default '0',
  `amount` int(11) unsigned NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` smallint(6) unsigned NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) unsigned NOT NULL default '0',
  `card0` smallint(11) NOT NULL default '0',
  `card1` smallint(11) NOT NULL default '0',
  `card2` smallint(11) NOT NULL default '0',
  `card3` smallint(11) NOT NULL default '0',
  `expire_time` int(11) unsigned NOT NULL default '0',
  `bound` tinyint(1) unsigned NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `guild_id` (`guild_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `homunculus`
--

CREATE TABLE IF NOT EXISTS `homunculus` (
  `homun_id` int(11) NOT NULL auto_increment,
  `char_id` int(11) NOT NULL,
  `class` mediumint(9) unsigned NOT NULL default '0',
  `prev_class` mediumint(9) NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `level` smallint(4) NOT NULL default '0',
  `exp` int(12) NOT NULL default '0',
  `intimacy` int(12) NOT NULL default '0',
  `hunger` smallint(4) NOT NULL default '0',
  `str` smallint(4) unsigned NOT NULL default '0',
  `agi` smallint(4) unsigned NOT NULL default '0',
  `vit` smallint(4) unsigned NOT NULL default '0',
  `int` smallint(4) unsigned NOT NULL default '0',
  `dex` smallint(4) unsigned NOT NULL default '0',
  `luk` smallint(4) unsigned NOT NULL default '0',
  `hp` int(12) NOT NULL default '1',
  `max_hp` int(12) NOT NULL default '1',
  `sp` int(12) NOT NULL default '1',
  `max_sp` int(12) NOT NULL default '1',
  `skill_point` smallint(4) unsigned NOT NULL default '0',
  `alive` tinyint(2) NOT NULL default '1',
  `rename_flag` tinyint(2) NOT NULL default '0',
  `vaporize` tinyint(2) NOT NULL default '0',
  PRIMARY KEY  (`homun_id`)
) ENGINE=MyISAM;

-- 
-- Estrutura da tabela `interlog`
--

CREATE TABLE IF NOT EXISTS `interlog` (
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `log` varchar(255) NOT NULL default ''
) ENGINE=MyISAM; 

--
-- Estrutura da tabela `inventory`
--

CREATE TABLE IF NOT EXISTS `inventory` (
  `id` int(11) unsigned NOT NULL auto_increment,
  `char_id` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) unsigned NOT NULL default '0',
  `amount` int(11) unsigned NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) unsigned NOT NULL default '0',
  `card0` smallint(11) NOT NULL default '0',
  `card1` smallint(11) NOT NULL default '0',
  `card2` smallint(11) NOT NULL default '0',
  `card3` smallint(11) NOT NULL default '0',
  `expire_time` int(11) unsigned NOT NULL default '0',
  `favorite` tinyint(3) unsigned NOT NULL default '0',
  `bound` tinyint(1) unsigned NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `ipbanlist`
--

CREATE TABLE IF NOT EXISTS `ipbanlist` (
  `list` varchar(255) NOT NULL default '',
  `btime` datetime NOT NULL default '0000-00-00 00:00:00',
  `rtime` datetime NOT NULL default '0000-00-00 00:00:00',
  `reason` varchar(255) NOT NULL default '',
  KEY (`list`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `login`
--

CREATE TABLE IF NOT EXISTS `login` (
  `account_id` int(11) unsigned NOT NULL auto_increment,
  `userid` varchar(23) NOT NULL default '',
  `user_pass` varchar(32) NOT NULL default '',
  `sex` enum('M','F','S') NOT NULL default 'M',
  `email` varchar(39) NOT NULL default '',
  `group_id` tinyint(3) NOT NULL default '0',
  `state` int(11) unsigned NOT NULL default '0',
  `unban_time` int(11) unsigned NOT NULL default '0',
  `expiration_time` int(11) unsigned NOT NULL default '0',
  `logincount` mediumint(9) unsigned NOT NULL default '0',
  `lastlogin` datetime NOT NULL default '0000-00-00 00:00:00',
  `last_ip` varchar(100) NOT NULL default '',
  `birthdate` DATE NOT NULL DEFAULT '0000-00-00',
  `character_slots` TINYINT( 3 ) unsigned NOT NULL default '0',
  `pincode` varchar(4) NOT NULL default '',
  `pincode_change` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`account_id`),
  KEY `name` (`userid`)
) ENGINE=MyISAM AUTO_INCREMENT=2000000; 

-- Adicionar a conta de comunica��o com dados padr�es � ALTAMENTE INSEGURO!!!

INSERT INTO `login` (`account_id`, `userid`, `user_pass`, `sex`, `email`) VALUES ('1', 's1', 'p1', 'S','brathena@brathena.org');

--
-- Estrutura da tabela `mapreg`
--

CREATE TABLE IF NOT EXISTS `mapreg` (
  `varname` varchar(32) BINARY NOT NULL,
  `index` int(11) unsigned NOT NULL default '0',
  `value` varchar(255) NOT NULL,
  PRIMARY KEY  (`varname`,`index`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `sc_data`
--

CREATE TABLE IF NOT EXISTS `sc_data` (
  `account_id` int(11) unsigned NOT NULL,
  `char_id` int(11) unsigned NOT NULL,
  `type` smallint(11) unsigned NOT NULL,
  `tick` int(11) NOT NULL,
  `val1` int(11) NOT NULL default '0',
  `val2` int(11) NOT NULL default '0',
  `val3` int(11) NOT NULL default '0',
  `val4` int(11) NOT NULL default '0',
  KEY (`account_id`),
  KEY (`char_id`),
  PRIMARY KEY  (`account_id`,`char_id`,`type`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `mail`
--

CREATE TABLE IF NOT EXISTS `mail` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `send_name` varchar(30) NOT NULL default '',
  `send_id` int(11) unsigned NOT NULL default '0',
  `dest_name` varchar(30) NOT NULL default '',
  `dest_id` int(11) unsigned NOT NULL default '0',
  `title` varchar(45) NOT NULL default '',
  `message` varchar(255) NOT NULL default '',
  `time` int(11) unsigned NOT NULL default '0',
  `status` tinyint(2) NOT NULL default '0',
  `zeny` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) unsigned NOT NULL default '0',
  `amount` int(11) unsigned NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) unsigned NOT NULL default '0',
  `identify` smallint(6) NOT NULL default '0',
  `card0` smallint(11) NOT NULL default '0',
  `card1` smallint(11) NOT NULL default '0',
  `card2` smallint(11) NOT NULL default '0',
  `card3` smallint(11) NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `memo`
--

CREATE TABLE IF NOT EXISTS `memo` (
  `memo_id` int(11) unsigned NOT NULL auto_increment,
  `char_id` int(11) unsigned NOT NULL default '0',
  `map` varchar(11) NOT NULL default '',
  `x` smallint(4) unsigned NOT NULL default '0',
  `y` smallint(4) unsigned NOT NULL default '0',
  PRIMARY KEY  (`memo_id`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `mercenary`
--

CREATE TABLE IF NOT EXISTS `mercenary` (
  `mer_id` int(11) unsigned NOT NULL auto_increment,
  `char_id` int(11) NOT NULL,
  `class` mediumint(9) unsigned NOT NULL default '0',
  `hp` int(12) NOT NULL default '1',
  `sp` int(12) NOT NULL default '1',
  `kill_counter` int(11) NOT NULL,
  `life_time` int(11) NOT NULL default '0',
  PRIMARY KEY  (`mer_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `mercenary_owner`
--

CREATE TABLE IF NOT EXISTS `mercenary_owner` (
  `char_id` int(11) NOT NULL,
  `merc_id` int(11) NOT NULL default '0',
  `arch_calls` int(11) NOT NULL default '0',
  `arch_faith` int(11) NOT NULL default '0',
  `spear_calls` int(11) NOT NULL default '0',
  `spear_faith` int(11) NOT NULL default '0',
  `sword_calls` int(11) NOT NULL default '0',
  `sword_faith` int(11) NOT NULL default '0',
  PRIMARY KEY  (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `party`
--

CREATE TABLE IF NOT EXISTS `party` (
  `party_id` int(11) unsigned NOT NULL auto_increment,
  `name` varchar(24) NOT NULL default '',
  `exp` tinyint(11) unsigned NOT NULL default '0',
  `item` tinyint(11) unsigned NOT NULL default '0',
  `leader_id` int(11) unsigned NOT NULL default '0',
  `leader_char` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`party_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `pet`
--

CREATE TABLE IF NOT EXISTS `pet` (
  `pet_id` int(11) unsigned NOT NULL auto_increment,
  `class` mediumint(9) unsigned NOT NULL default '0',
  `name` varchar(24) NOT NULL default '',
  `account_id` int(11) unsigned NOT NULL default '0',
  `char_id` int(11) unsigned NOT NULL default '0',
  `level` smallint(4) unsigned NOT NULL default '0',
  `egg_id` smallint(11) unsigned NOT NULL default '0',
  `equip` mediumint(8) unsigned NOT NULL default '0',
  `intimate` smallint(9) unsigned NOT NULL default '0',
  `hungry` smallint(9) unsigned NOT NULL default '0',
  `rename_flag` tinyint(4) unsigned NOT NULL default '0',
  `incuvate` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`pet_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `quest`
--

CREATE TABLE IF NOT EXISTS `quest` (
  `char_id` int(11) unsigned NOT NULL default '0',
  `quest_id` int(10) unsigned NOT NULL,
  `state` enum('0','1','2') NOT NULL default '0',
  `time` int(11) unsigned NOT NULL default '0',
  `count1` mediumint(8) unsigned NOT NULL default '0',
  `count2` mediumint(8) unsigned NOT NULL default '0',
  `count3` mediumint(8) unsigned NOT NULL default '0',
  PRIMARY KEY  (`char_id`,`quest_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `ragsrvinfo`
--

CREATE TABLE IF NOT EXISTS `ragsrvinfo` (
  `index` int(11) NOT NULL default '0',
  `name` varchar(255) NOT NULL default '',
  `exp` int(11) unsigned NOT NULL default '0',
  `jexp` int(11) unsigned NOT NULL default '0',
  `drop` int(11) unsigned NOT NULL default '0'
) ENGINE=MyISAM;

--
-- Estrutura da tabela `skill`
--

CREATE TABLE IF NOT EXISTS `skill` (
  `char_id` int(11) unsigned NOT NULL default '0',
  `id` smallint(11) unsigned NOT NULL default '0',
  `lv` tinyint(4) unsigned NOT NULL default '0',
  `flag` TINYINT(1) UNSIGNED NOT NULL default 0,
  PRIMARY KEY  (`char_id`,`id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `skill_homunculus`
--

CREATE TABLE IF NOT EXISTS `skill_homunculus` (
  `homun_id` int(11) NOT NULL,
  `id` int(11) NOT NULL,
  `lv` smallint(6) NOT NULL,
  PRIMARY KEY  (`homun_id`,`id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `brathena_updates`
--
CREATE TABLE IF NOT EXISTS `brathena_updates` (
  `sql_name` varchar(24) NOT NULL default '',
  PRIMARY KEY (`sql_name`)
) ENGINE=MyISAM;

REPLACE INTO `brathena_updates` VALUES('brathena_r1371');
REPLACE INTO `brathena_updates` VALUES('brathena_r1453');
REPLACE INTO `brathena_updates` VALUES('brathena_r1512');
REPLACE INTO `brathena_updates` VALUES('brathena_r1582');
REPLACE INTO `brathena_updates` VALUES('brathena_r1583');
REPLACE INTO `brathena_updates` VALUES('brathena_r1736');
REPLACE INTO `brathena_updates` VALUES('brathena_r1812');
REPLACE INTO `brathena_updates` VALUES('brathena_r1816');
REPLACE INTO `brathena_updates` VALUES('brathena_r1824');
REPLACE INTO `brathena_updates` VALUES('brathena_r1864');
REPLACE INTO `brathena_updates` VALUES('brathena_r1893');
REPLACE INTO `brathena_updates` VALUES('brathena_r1960');
REPLACE INTO `brathena_updates` VALUES('brathena_r1974');
REPLACE INTO `brathena_updates` VALUES('brathena_r2026');
REPLACE INTO `brathena_updates` VALUES('brathena_r2061');
REPLACE INTO `brathena_updates` VALUES('brathena_r2459');
REPLACE INTO `brathena_updates` VALUES('brathena_r2490');
REPLACE INTO `brathena_updates` VALUES('brathena_r2495');
REPLACE INTO `brathena_updates` VALUES('brathena_r2508');
REPLACE INTO `brathena_updates` VALUES('brathena_r2519');
REPLACE INTO `brathena_updates` VALUES('brathena_r2532');
REPLACE INTO `brathena_updates` VALUES('brathena_r2566');
REPLACE INTO `brathena_updates` VALUES('brathena_r2569');
REPLACE INTO `brathena_updates` VALUES('brathena_r2657');
REPLACE INTO `brathena_updates` VALUES('brathena_r2679');
REPLACE INTO `brathena_updates` VALUES('brathena_r2770');
REPLACE INTO `brathena_updates` VALUES('brathena_r2802');
REPLACE INTO `brathena_updates` VALUES('brathena_r2806');
REPLACE INTO `brathena_updates` VALUES('brathena_r2808');

--
-- Estrutura da tabela `sstatus`
--

CREATE TABLE IF NOT EXISTS `sstatus` (
  `index` tinyint(4) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL default '',
  `user` int(11) unsigned NOT NULL default '0'
) ENGINE=MyISAM;

--
-- Estrutura da tabela `storage`
--

CREATE TABLE IF NOT EXISTS `storage` (
  `id` int(11) unsigned NOT NULL auto_increment,
  `account_id` int(11) unsigned NOT NULL default '0',
  `nameid` int(11) unsigned NOT NULL default '0',
  `amount` smallint(11) unsigned NOT NULL default '0',
  `equip` int(11) unsigned NOT NULL default '0',
  `identify` smallint(6) unsigned NOT NULL default '0',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `attribute` tinyint(4) unsigned NOT NULL default '0',
  `card0` smallint(11) NOT NULL default '0',
  `card1` smallint(11) NOT NULL default '0',
  `card2` smallint(11) NOT NULL default '0',
  `card3` smallint(11) NOT NULL default '0',
  `expire_time` int(11) unsigned NOT NULL default '0',
  `bound` tinyint(1) unsigned NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `account_id` (`account_id`)
) ENGINE=MyISAM;

--
--  Estrutura da tabela `interreg`
--

CREATE TABLE IF NOT EXISTS `interreg` (
  `varname` varchar(11) NOT NULL,
  `value` varchar(20) NOT NULL,
   PRIMARY KEY (`varname`)
) ENGINE=InnoDB;

--
-- Estrutura da tabela `account_data`
--

CREATE TABLE IF NOT EXISTS `account_data` (
  `account_id` int(11) unsigned NOT NULL default '0',
  `bank_vault` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`account_id`)
) ENGINE=MyISAM; 

--
-- Estrutura da tabela `npc_market_data`
--

CREATE TABLE IF NOT EXISTS `npc_market_data` (
  `name` varchar(24) NOT NULL default '',
  `itemid` int(11) unsigned NOT NULL default '0',
  `amount` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`name`,`itemid`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `acc_reg_num_db`
--

CREATE TABLE IF NOT EXISTS `acc_reg_num_db` (
  `account_id` int(11) unsigned NOT NULL default '0',
  `key` varchar(32) BINARY NOT NULL default '',
  `index` int(11) unsigned NOT NULL default '0',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY  (`account_id`,`key`,`index`),
  KEY `account_id` (`account_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela table `acc_reg_str_db`
--

CREATE TABLE IF NOT EXISTS `acc_reg_str_db` (
  `account_id` int(11) unsigned NOT NULL default '0',
  `key` varchar(32) BINARY NOT NULL default '',
  `index` int(11) unsigned NOT NULL default '0',
  `value` varchar(254) NOT NULL default '0',
  PRIMARY KEY  (`account_id`,`key`,`index`),
  KEY `account_id` (`account_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `char_reg_num_db`
--

CREATE TABLE IF NOT EXISTS `char_reg_num_db` (
  `char_id` int(11) unsigned NOT NULL default '0',
  `key` varchar(32) BINARY NOT NULL default '',
  `index` int(11) unsigned NOT NULL default '0',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY  (`char_id`,`key`,`index`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela table `char_reg_str_db`
--

CREATE TABLE IF NOT EXISTS `char_reg_str_db` (
  `char_id` int(11) unsigned NOT NULL default '0',
  `key` varchar(32) BINARY NOT NULL default '',
  `index` int(11) unsigned NOT NULL default '0',
  `value` varchar(254) NOT NULL default '0',
  PRIMARY KEY  (`char_id`,`key`,`index`),
  KEY `char_id` (`char_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `global_acc_reg_num_db`
--

CREATE TABLE IF NOT EXISTS `global_acc_reg_num_db` (
  `account_id` int(11) unsigned NOT NULL default '0',
  `key` varchar(32) BINARY NOT NULL default '',
  `index` int(11) unsigned NOT NULL default '0',
  `value` int(11) NOT NULL default '0',
  PRIMARY KEY  (`account_id`,`key`,`index`),
  KEY `account_id` (`account_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `global_acc_reg_str_db`
--


CREATE TABLE IF NOT EXISTS `global_acc_reg_str_db` (
  `account_id` int(11) unsigned NOT NULL default '0',
  `key` varchar(32) BINARY NOT NULL default '',
  `index` int(11) unsigned NOT NULL default '0',
  `value` varchar(254) NOT NULL default '0',
  PRIMARY KEY  (`account_id`,`key`,`index`),
  KEY `account_id` (`account_id`)
) ENGINE=MyISAM;

--
-- Estrutura da tabela `autotrade_merchants`
--

CREATE TABLE IF NOT EXISTS `autotrade_merchants` (
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `sex` tinyint(2) NOT NULL default '0',
  `title` varchar(80) NOT NULL default 'Buy From Me!',
  PRIMARY KEY  (`account_id`,`char_id`)
) ENGINE=MyISAM; 

--
-- Estrutura da tabela `autotrade_data`
--

CREATE TABLE IF NOT EXISTS `autotrade_data` (
  `char_id` int(11) NOT NULL default '0',
  `itemkey` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '0',
  `price` int(11) NOT NULL default '0',
  PRIMARY KEY  (`char_id`,`itemkey`)
) ENGINE=MyISAM; 

