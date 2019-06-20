<?php
require_once("./include/database_config.php");
$view_title = "图书管理系统 - 书目检索";
$keyword = isset($_GET['keyword']) ? $_GET['keyword'] : '';
$len = strlen($keyword);
if ($len > 30) {
?>
    <script language="javascript">
    window.location.href = 'index.php?wa=30';
    </script>
<?php
    exit(0);
} else if ($len == 0) {
?>
    <script language="javascript">
    window.location.href = 'index.php?wa=0';
    </script>
<?php
    exit(0);
}
$old_keyword = $keyword;
$keyword = '%'.$keyword.'%';
$sql = "select `title`, `author`, `press`, `publish_year`, `isbn`, `visit_id`".
    " from `BookInfo`".
    " where (`title` like ?) or (`author` like ?) or (`isbn` = ?) or (`visit_id` = ?)".
    " limit 1000";
$result = pdo_query($sql, $keyword, $keyword, $old_keyword, $old_keyword);
require("./template/search_result.php");
?>
