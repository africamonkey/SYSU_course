<?php
@session_start();
static $DB_HOST = ""; // Mysql database host (IP address), default 127.0.0.1
static $DB_PORT = ""; // Mysql database port, default 3306
static $DB_NAME = ""; // Mysql database schema name, default sql_big_project
static $DB_USER = ""; // Mysql database username
static $DB_PASS = ""; // Mysql database password

require_once(dirname(__FILE__)."/pdo.php");
?>
