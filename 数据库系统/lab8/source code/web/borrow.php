<?php
require_once('./include/database_config.php');
$view_title = "图书管理系统 - 借书";
if (!$_SESSION['administrator']) {
    http_response_code(404);
    exit(0);
}
$user_id = $_POST['user_id'];
$book_id = $_POST['book_id'];

$sql = "select `username` from `user` where `username` = ?";
$result = pdo_query($sql, $user_id);
if (count($result) < 1) {
    header("Location:borrow_page.php?wa=".urlencode("用户名不存在"));
    exit(0);
}
$sql = "select `username` from `Reader` where `username` = ?";
$result = pdo_query($sql, $user_id);
if (count($result) < 1) {
    $sql = "insert into `Reader`(`username`) values (?)";
    pdo_query($sql, $user_id);
}
$sql = "select `id`, `title`, `status` from `Book` natural join `BookInfo` where `id` = ?";
$result = pdo_query($sql, $book_id);
if (count($result) < 1) {
    header("Location:borrow_page.php?wa=".urlencode("书本序列号不存在"));
    exit(0);
}
if ($result[0]['status'] != 'Library') {
    header("Location:borrow_page.php?wa=".urlencode("书本已借出，不可重复借阅"));
    exit(0);
}
$book_title = $result[0]['title'];
$sql = "insert into `Borrows`(`reader_username`, `admin_username`, `book_id`, `continue_debit`, `borrow_date`, `return_date`, `actual_return_date`) values (?, ?, ?, ?, ?, ?, ?)";
$rec_id = pdo_query($sql, $user_id, $_SESSION['user_id'], $book_id, 'N', date('Y-m-d'), date("Y-m-d",strtotime(date('Y-m-d')." +1 month")), NULL);
if ($rec_id == 0) {
    header("Location:borrow_page.php?wa=".urlencode("未知错误，请联系管理员"));
    exit(0);
}
$sql = "update `Book` set `rec_id` = ?, `status` = ? where `id` = ?";
pdo_query($sql, $rec_id, 'Borrowed', $book_id);
$sql = "update `Reader` set `borrowed_book` = `borrowed_book` + 1 where `username` = ?";
pdo_query($sql, $user_id);
$message = $user_id." 已成功借阅 ".$book_title."，记录号为 ".$rec_id;
header("Location:borrow_page.php?success=".urlencode($message));
exit(0);
?>