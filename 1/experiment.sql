/*
 Navicat Premium Data Transfer

 Source Server         : MySQL5.5
 Source Server Type    : MySQL
 Source Server Version : 50528
 Source Host           : localhost:3306
 Source Schema         : experiment

 Target Server Type    : MySQL
 Target Server Version : 50528
 File Encoding         : 65001

 Date: 18/05/2023 16:30:18
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course`  (
  `id` int(32) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `hours` int(32) NULL DEFAULT NULL,
  `school` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `picture` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of course
-- ----------------------------
INSERT INTO `course` VALUES (1, 'C语言程序设计', 70, '计算机学院', 'c.jpg');
INSERT INTO `course` VALUES (2, '大学英语', 96, '外国语学院', 'english.jpg');
INSERT INTO `course` VALUES (3, '操作系统', 32, '计算机学院', 'os.jpg');
INSERT INTO `course` VALUES (4, '高级web技术', 32, '计算机学院', 'web.jpg');
INSERT INTO `course` VALUES (5, '高等数学', 48, '数学学院', 'math.jpg');
INSERT INTO `course` VALUES (8, 'Python程序设计', 70, '计算机学院', 'f2ceaaf5-3298-4bbb-8fd3-acb4ccbff53a.jpg');
INSERT INTO `course` VALUES (9, '毛概', 32, '马克思学院', 'ab5c6783-2f9b-4d6e-90c3-3dac6c084030.jpg');
INSERT INTO `course` VALUES (10, '数据结构', 48, '计算机学院', '77fbaee9-91a2-4032-bdf0-cfbfab5dba69.jpg');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int(32) NOT NULL AUTO_INCREMENT,
  `email` varchar(32) CHARACTER SET gbk COLLATE gbk_chinese_ci NULL DEFAULT NULL,
  `password` varchar(32) CHARACTER SET gbk COLLATE gbk_chinese_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = gbk COLLATE = gbk_chinese_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'admin@qq.com', '123456');

SET FOREIGN_KEY_CHECKS = 1;
