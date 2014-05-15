/*_________________________________________________________________________
 /                                                                         \
 |                  _           _   _   _                                  |
 |                 | |__  _ __ / \ | |_| |__   ___ _ __   __ _             |
 |                 | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |            |
 |                 | |_) | | / ___ \ |_| | | |  __/ | | | (_| |            |
 |                 |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|            |
 |                                                                         |
 |                       brAthena � 2013 - Banco de Dados                  |
 |             Cont�m as tabelas de logs para a��es no emulador            |
 \_________________________________________________________________________/
*/

# PickLog tipos (M)onstros - Itens Derrubados, Jogador - Itens Derrubados (P) / Obtidos, Monstros Ladr�es Itens (L) - Dropados / Obtidos,
# Jogadores (N)egocia��es Recebidos / Entregues, (V) Jogadores Venda / Compra, (S) Loja de NPCs Venda / Compra, (N)PC Compra / Venda,
# (C)onsum�veis, (A)dministrador Criado/Deletado,(R) Armaz�m, (G) Armaz�m do Cl�, 
# Itens E-mail (E),(B) Com�rcio,(O) Itens Produzidos / Engredientes, (I) Itens Leil�o,
# (X) Outros, (D) Itens roubados de Monstros, (U) MVP Pr�mios

#Database: ragnarok
#Table: picklog
CREATE TABLE IF NOT EXISTS `picklog` (
  `id` int(11) NOT NULL auto_increment,
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `char_id` int(11) NOT NULL default '0',
  `type` enum('M','P','L','T','V','S','N','C','A','R','G','E','B','O','I','X','D','U') NOT NULL default 'P',
  `nameid` int(11) NOT NULL default '0',
  `amount` int(11) NOT NULL default '1',
  `refine` tinyint(3) unsigned NOT NULL default '0',
  `card0` int(11) NOT NULL default '0',
  `card1` int(11) NOT NULL default '0',
  `card2` int(11) NOT NULL default '0',
  `card3` int(11) NOT NULL default '0',
  `unique_id` bigint(20) unsigned NOT NULL default '0',
  `map` varchar(11) NOT NULL default '',
  PRIMARY KEY  (`id`),
  INDEX (`type`)
) ENGINE=MyISAM AUTO_INCREMENT=1;

#ZenyLog tipos (M)onstros,(T)roca,(V) Venda / Compra,(S)hop Venda / Compra,(N)PC Quantidade,(A)dministradores,(E)Mail,(B)Com�rcio
#Database: ragnarok
#Table: zenylog
CREATE TABLE IF NOT EXISTS `zenylog` (
  `id` int(11) NOT NULL auto_increment,
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `char_id` int(11) NOT NULL default '0',
  `src_id` int(11) NOT NULL default '0',
  `type` enum('T','V','P','M','S','N','D','C','A','E','I','B') NOT NULL default 'S',
  `amount` int(11) NOT NULL default '0',
  `map` varchar(11) NOT NULL default '',
  PRIMARY KEY  (`id`),
  INDEX (`type`)
) ENGINE=MyISAM AUTO_INCREMENT=1 ;

#Database: ragnarok
#Table: branchlog
CREATE TABLE IF NOT EXISTS `branchlog` (
  `branch_id` mediumint(9) unsigned NOT NULL auto_increment,
  `branch_date` datetime NOT NULL default '0000-00-00 00:00:00',
  `account_id` int(11) NOT NULL default '0',
  `char_id` int(11) NOT NULL default '0',
  `char_name` varchar(25) NOT NULL default '',
  `map` varchar(11) NOT NULL default '',
  PRIMARY KEY  (`branch_id`),
  INDEX (`account_id`),
  INDEX (`char_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1;

#Database: ragnarok
#Table: mvplog
CREATE TABLE IF NOT EXISTS `mvplog` (
  `mvp_id` mediumint(9) unsigned NOT NULL auto_increment,
  `mvp_date` datetime NOT NULL default '0000-00-00 00:00:00',
  `kill_char_id` int(11) NOT NULL default '0',
  `monster_id` smallint(6) NOT NULL default '0',
  `prize` int(11) NOT NULL default '0',
  `mvpexp` mediumint(9) NOT NULL default '0',
  `map` varchar(11) NOT NULL default '',
  PRIMARY KEY  (`mvp_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 ;

#Database: ragnarok
#Table: atcommandlog
CREATE TABLE IF NOT EXISTS `atcommandlog` (
  `atcommand_id` mediumint(9) unsigned NOT NULL auto_increment,
  `atcommand_date` datetime NOT NULL default '0000-00-00 00:00:00',
  `account_id` int(11) unsigned NOT NULL default '0',
  `char_id` int(11) unsigned NOT NULL default '0',
  `char_name` varchar(25) NOT NULL default '',
  `map` varchar(11) NOT NULL default '',
  `command` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`atcommand_id`),
  INDEX (`account_id`),
  INDEX (`char_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1;

#Database: ragnarok
#Table: npclog
CREATE TABLE IF NOT EXISTS `npclog` (
  `npc_id` mediumint(9) unsigned NOT NULL auto_increment,
  `npc_date` datetime NOT NULL default '0000-00-00 00:00:00',
  `account_id` int(11) unsigned NOT NULL default '0',
  `char_id` int(11) unsigned NOT NULL default '0',
  `char_name` varchar(25) NOT NULL default '',
  `map` varchar(11) NOT NULL default '',
  `mes` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`npc_id`),
  INDEX (`account_id`),
  INDEX (`char_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1;

#ChatLog tipos (O) Global,(W)hisper / PM,Grupo (P),(G) Cl�,(M) Chat P�blico
#Database: ragnarok
#Table: chatlog
CREATE TABLE IF NOT EXISTS `chatlog` (
  `id` bigint(20) NOT NULL auto_increment,
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `type` enum('O','W','P','G','M') NOT NULL default 'O',
  `type_id` int(11) NOT NULL default '0',
  `src_charid` int(11) NOT NULL default '0',
  `src_accountid` int(11) NOT NULL default '0',
  `src_map` varchar(11) NOT NULL default '',
  `src_map_x` smallint(4) NOT NULL default '0',
  `src_map_y` smallint(4) NOT NULL default '0',
  `dst_charname` varchar(25) NOT NULL default '',
  `message` varchar(150) NOT NULL default '',
  PRIMARY KEY  (`id`),
  INDEX (`src_accountid`),
  INDEX (`src_charid`)
) ENGINE=MyISAM AUTO_INCREMENT=1;

#Database: ragnarok
#Table: loginlog
CREATE TABLE IF NOT EXISTS `loginlog` (
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `ip` varchar(15) NOT NULL default '',
  `user` varchar(23) NOT NULL default '',
  `rcode` tinyint(4) NOT NULL default '0',
  `log` varchar(255) NOT NULL default '',
  INDEX (`ip`)
) ENGINE=MyISAM;
