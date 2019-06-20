<?php
require_once('./include/database_config.php');
$view_title = "图书管理系统 - 还书";
if (!$_SESSION['administrator']) {
    http_response_code(404);
    exit(0);
}
$book_id = $_POST['book_id'];

$sql = "select `id`, `title`, `status`, `rec_id` from `Book` natural join `BookInfo` where `id` = ?";
$result = pdo_query($sql, $book_id);
if (count($result) < 1) {
    header("Location:return_page.php?wa=".urlencode("书本序列号不存在"));
    exit(0);
}
if ($result[0]['status'] != 'Borrowed') {
    header("Location:return_page.php?wa=".urlencode("书本已在馆，无需归还"));
    exit(0);
}
$rec_id = $result[0]['rec_id'];
$book_title = $result[0]['title'];
if ($rec_id == 0) {
    header("Location:return_page.php?wa=".urlencode("未知错误，请联系管理员"));
    exit(0);
}
$sql = "select `book_id`, `borrow_date`, `return_date`, `actual_return_date` from `Borrows` where `rec_id` = ?"; 
$result = pdo_query($sql, $rec_id);
if (count($result) == 0) {
    header("Location:return_page.php?wa=".urlencode("未知错误，请联系管理员"));
    exit(0);
}
$expect_return_date = $result[0]['return_date'];
$actual_return_date = date('Y-m-d');
$expire_days = (strtotime($actual_return_date) - strtotime($expect_return_date)) / 86400;
if ($expire_days < 0) $expire_days = 0;
$sql = "update `Borrows` set `actual_return_date` = ? where `rec_id` = ?";
$result = pdo_query($sql, $actual_return_date, $rec_id);
$sql = "update `Book` set `rec_id` = ?, `status` = ? where `id` = ?";
pdo_query($sql, 0, 'Library', $book_id);
$sql = "update `Reader` set `borrowed_book` = `borrowed_book` - 1, `penalty` = `penalty` + ? where `username` = ?";
pdo_query($sql, $expire_days, $user_id);
if ($expire_days <= 0) {
	$message = $user_id." 已成功归还 ".$book_title."，记录号为 ".$rec_id;
	header("Location:return_page.php?success=".urlencode($message));
} else {
	$message = $user_id." 已成功归还 ".$book_title."，逾期 ".$expire_days." 天，记录号为 ".$rec_id;
	header("Location:return_page.php?tle=".urlencode($message));
}
exit(0);
?>
