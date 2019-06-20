-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema sql_big_project
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema sql_big_project
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `sql_big_project` DEFAULT CHARACTER SET utf8 ;
USE `sql_big_project` ;

-- -----------------------------------------------------
-- Table `sql_big_project`.`user`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sql_big_project`.`user` (
  `username` VARCHAR(16) NOT NULL,
  `password` VARCHAR(32) NOT NULL,
  `name` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`username`));


-- -----------------------------------------------------
-- Table `sql_big_project`.`BookInfo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sql_big_project`.`BookInfo` (
  `isbn` VARCHAR(50) NOT NULL,
  `title` VARCHAR(50) NOT NULL,
  `author` VARCHAR(50) NULL,
  `press` VARCHAR(50) NULL,
  `publish_year` VARCHAR(4) NULL,
  `visit_id` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`isbn`));


-- -----------------------------------------------------
-- Table `sql_big_project`.`Reader`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sql_big_project`.`Reader` (
  `username` VARCHAR(16) NOT NULL,
  `penalty` INT(11) NOT NULL DEFAULT 0,
  `borrowed_book` INT(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`username`),
  CONSTRAINT `fk_Reader_user1`
    FOREIGN KEY (`username`)
    REFERENCES `sql_big_project`.`user` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sql_big_project`.`Admin`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sql_big_project`.`Admin` (
  `username` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`username`),
  CONSTRAINT `fk_Admin_user1`
    FOREIGN KEY (`username`)
    REFERENCES `sql_big_project`.`user` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sql_big_project`.`Book`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sql_big_project`.`Book` (
  `id` INT(11) NOT NULL auto_increment,
  `isbn` VARCHAR(50) NOT NULL,
  `rec_id` INT(11) NOT NULL,
  `status` VARCHAR(10) NOT NULL DEFAULT 'Library',
  PRIMARY KEY (`id`),
  INDEX `fk_Book_BookInfo1_idx` (`isbn` ASC),
  CONSTRAINT `fk_Book_BookInfo1`
    FOREIGN KEY (`isbn`)
    REFERENCES `sql_big_project`.`BookInfo` (`isbn`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sql_big_project`.`Borrows`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sql_big_project`.`Borrows` (
  `rec_id` INT(11) NOT NULL auto_increment,
  `reader_username` VARCHAR(16) NOT NULL,
  `admin_username` VARCHAR(16) NOT NULL,
  `book_id` INT(11) NOT NULL,
  `continue_debit` VARCHAR(1) NOT NULL DEFAULT 'N',
  `borrow_date` DATE NOT NULL,
  `return_date` DATE NOT NULL,
  `actual_return_date` DATE NOT NULL,
  PRIMARY KEY (`rec_id`),
  INDEX `fk_Borrows_Book1_idx` (`book_id` ASC),
  INDEX `fk_Borrows_Reader1_idx` (`reader_username` ASC),
  INDEX `fk_Borrows_Admin1_idx` (`admin_username` ASC),
  CONSTRAINT `fk_Borrows_Book1`
    FOREIGN KEY (`book_id`)
    REFERENCES `sql_big_project`.`Book` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Borrows_Reader1`
    FOREIGN KEY (`reader_username`)
    REFERENCES `sql_big_project`.`Reader` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Borrows_Admin1`
    FOREIGN KEY (`admin_username`)
    REFERENCES `sql_big_project`.`Admin` (`username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
