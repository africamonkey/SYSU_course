<?php
require_once('./include/database_config.php');
$view_title= "用户密码修改";
if (!isset($_SESSION['user_id'])) {
    http_response_code(404);
    exit(0);
}
require("template/modifypage.php");
?>

