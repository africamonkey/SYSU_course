<?php
require_once('./include/database_config.php');
$view_title = "图书管理系统 - 借书";
if (!isset($_SESSION['administrator'])) {
    http_response_code(404);
    exit(0);
}
require("./template/borrow_page.php");
?>