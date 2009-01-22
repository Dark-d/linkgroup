SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for creature_link
-- ----------------------------
CREATE TABLE `creature_link` (
  `guid` int(10) unsigned NOT NULL default '0',
  `linkid` int(10) unsigned NOT NULL default '0',
  `respawn` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
