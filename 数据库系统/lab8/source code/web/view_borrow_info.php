<?php
require_once('./include/database_config.php');
$view_title = "图书管理系统 - 借阅记录";
if (!isset($_SESSION['user_id'])) {
    http_response_code(404);
    exit(0);
}
$sql_1 = "select B1.rec_id, B1.return_date, B3.title, B3.author, B3.publish_year, B3.visit_id ".
    "from Borrows as B1, Book as B2, BookInfo as B3 ".
    "where B1.reader_username = ? and B1.book_id = B2.id and B2.isbn = B3.isbn and B1.actual_return_date is null";
$result_1 = pdo_query($sql_1, $_SESSION['user_id']);

$sql_2 = "select B1.rec_id, B1.borrow_date, B1.actual_return_date, B3.title, B3.author, B3.publish_year, B3.visit_id ".
    "from Borrows as B1, Book as B2, BookInfo as B3 ".
    "where B1.reader_username = ? and B1.book_id = B2.id and B2.isbn = B3.isbn and B1.actual_return_date is not null";
$result_2 = pdo_query($sql_2, $_SESSION['user_id']);

require('./template/view_borrow_info.php');
?>
