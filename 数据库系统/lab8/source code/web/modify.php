<?php
require_once('./include/database_config.php');
require_once("./include/loginutil.php");
$view_title= "用户密码修改";
$err_str="";
$err_cnt=0;

$user_id=$_SESSION['user_id'];
$password=$_POST['opassword'];
$sql="SELECT `username`, `password` FROM `user` WHERE `username`=?";
$result=pdo_query($sql, $user_id);
$row=$result[0];
if ($row && pwCheck($password,$row['password'])) $rows_cnt = 1;
else $rows_cnt = 0;

if ($rows_cnt==0){
	$err_str=$err_str."Old Password Wrong";
	$err_cnt++;
}

$len=strlen($_POST['npassword']);
if ($len<6 && $len>0){
	$err_cnt++;
	$err_str=$err_str."Password should be Longer than 6!\\n";
}else if (strcmp($_POST['npassword'],$_POST['rptpassword'])!=0){
	$err_str=$err_str."Two Passwords Not Same!";
	$err_cnt++;
}
if ($err_cnt>0){
	print "<script language='javascript'>\n";
	echo "alert('";
	echo $err_str;
	print "');\n history.go(-1);\n</script>";
	exit(0);
	
}

if (strlen($_POST['npassword'])==0) $password=pwGen($_POST['opassword']);
else $password=pwGen($_POST['npassword']);
$sql = "UPDATE `user` SET `password`=? WHERE `username`=?";
pdo_query($sql, $password, $user_id);
header("Location: ./");
?>
