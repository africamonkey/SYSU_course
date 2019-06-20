<?php
require_once("./include/loginutil.php");
require_once("./include/database_config.php");

$user_id=trim($_POST['user_id']);
$len=strlen($user_id);
$err_str = "注册失败\\n";
$err_cnt = 0;

if($len>15) {
	$err_str = $err_str."用户名太长（不能多于15个字符）\\n";
	$err_cnt += 1;
} else if ($len<4) {
	$err_str = $err_str."用户名太短（不能少于4个字符）\\n";
    $err_cnt += 1;
}

if (!is_valid_user_name($user_id)) {
	$err_str = $err_str."用户名只能包含字母和数字\\n";
    $err_cnt += 1;
}

$name=trim($_POST['name']);
$len=strlen($name);
if ($len>48) {
	$err_str = $err_str."姓名太长\\n";
    $err_cnt += 1;
} else if ($len==0) {
    $name = $user_id;
}

if (strcmp($_POST['password'],$_POST['rptpassword'])!=0){
	$err_str=$err_str."两次输入的密码不一致\\n";
	$err_cnt++;
}
if (strlen($_POST['password'])<6){
	$err_cnt++;
	$err_str=$err_str."密码太短（不能少于6个字符）\\n";
}
if (strlen($_POST['password'])>30){
	$err_cnt++;
	$err_str=$err_str."密码太长（不能多于30个字符）\\n";
}

if ($err_cnt > 0){
	print "<script language='javascript'>\n";
	print "alert('";
	print $err_str;
	print "');\n history.go(-1);\n</script>";
	exit(0);
	
}

$password = pwGen($_POST['password']);
$sql="SELECT `username` FROM `user` WHERE `user`.`username` = ?";
$result=pdo_query($sql,$user_id);
$rows_cnt=count($result);

if ($rows_cnt == 1){
	print "<script language='javascript'>\n";
	print "alert('用户已存在\\n');\n";
	print "history.go(-1);\n</script>";
	exit(0);
}

$name=(htmlentities ($name,ENT_QUOTES,"UTF-8"));
$sql="INSERT INTO `user`(`username`, `password`, `name`) VALUES (?, ?, ?)";
$rows=pdo_query($sql, $user_id, $password, $name);
$login = check_login($user_id, $_POST['password']);
$_SESSION['user_id'] = $user_id;
?>
<script language="javascript">
    window.location.href = 'index.php';
</script>
