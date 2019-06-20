<?php
function pdo_query($sql) {
    $num_args = func_num_args();
    $args = func_get_args();       //获得传入的所有参数的数组
    $args = array_slice($args,1,--$num_args);

    global $DB_HOST,$DB_PORT,$DB_NAME,$DB_USER,$DB_PASS,$dbh;
    if(!$dbh){
        $dbh = new PDO("mysql:host=".$DB_HOST.";port=".$DB_PORT.";dbname=".$DB_NAME,
            $DB_USER,
            $DB_PASS,
            array(PDO::MYSQL_ATTR_INIT_COMMAND => "set names utf8")
        );
    }

    $sth = $dbh->prepare($sql);
    $sth->execute($args);
    $result=array();
    if(stripos($sql,"select") === 0) {
        $result=$sth->fetchAll();
    } else if(stripos($sql,"insert") === 0) {
        $result=$dbh->lastInsertId();
    } else {
        $result=$sth->rowCount();
    }
    $sth->closeCursor();
    return $result;
}
?>