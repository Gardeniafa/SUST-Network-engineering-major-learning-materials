/*
 Navicat Premium Data Transfer

 Source Server         : kdms
 Source Server Type    : MySQL
 Source Server Version : 80024 (8.0.24)
 Source Host           : ms.minmin.cloud:6933
 Source Schema         : kdms

 Target Server Type    : MySQL
 Target Server Version : 80024 (8.0.24)
 File Encoding         : 65001

 Date: 20/09/2023 18:26:33
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for deans
-- ----------------------------
DROP TABLE IF EXISTS `deans`;
CREATE TABLE `deans`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `age` int NOT NULL,
  `sex` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `phone` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  CONSTRAINT `ck_dean_age` CHECK (`age` > 18),
  CONSTRAINT `ck_dean_sex` CHECK (`sex` in (_utf8mb4'男',_utf8mb4'女'))
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for schools
-- ----------------------------
DROP TABLE IF EXISTS `schools`;
CREATE TABLE `schools`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `address` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `numberOfChildren` int NOT NULL,
  `numberOfEmployee` int NOT NULL,
  `deanName` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `deanPhone` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for system
-- ----------------------------
DROP TABLE IF EXISTS `system`;
CREATE TABLE `system`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `permission` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- View structure for schoolsinformation
-- ----------------------------
DROP VIEW IF EXISTS `schoolsinformation`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `schoolsinformation` AS select `schools`.`id` AS `schID`,`schools`.`name` AS `schName`,`schools`.`address` AS `address`,`schools`.`numberOfChildren` AS `numberOfChildren`,`schools`.`numberOfEmployee` AS `numberOfEmployee`,`deans`.`name` AS `deansName`,`deans`.`age` AS `deansAge`,`deans`.`sex` AS `deansSex`,`deans`.`phone` AS `deansPhone` from (`schools` join `deans` on((`schools`.`deanID` = `deans`.`id`)));

SET FOREIGN_KEY_CHECKS = 1;
