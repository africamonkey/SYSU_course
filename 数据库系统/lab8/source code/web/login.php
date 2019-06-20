<?php
require_once("./include/loginutil.php");
require_once('./include/database_config.php');
$user_id = $_POST['user_id'];
$password = $_POST['password'];
$login = check_login($user_id, $password);
if ( $login ) {
    $_SESSION['user_id'] = $login;
    $sql = "SELECT `username` FROM `Admin` where `username`=?";
    $result = pdo_query($sql, $login);
    if (count($result) >= 1) {
        $_SESSION['administrator'] = true;
    }
?>
    <script language="javascript">
        window.location.href = 'index.php';
    </script>
<?php
} else {
?>
    <script language="javascript">
        window.location.href = 'login_page.php?wrong=1';
    </script>
<?php
}
?>
