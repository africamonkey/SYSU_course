<?php
function crypto_rand_secure($min, $max) {
    $range = $max - $min;
    if ($range < 0) return $min; // not so random...
    $log = log($range, 2);
    $bytes = (int) ($log / 8) + 1; // length in bytes
    $bits = (int) $log + 1; // length in bits
    $filter = (int) (1 << $bits) - 1; // set all lower bits to 1
    do {
        if(function_exists("openssl_random_pseudo_bytes")){
            $rnd = hexdec(bin2hex(openssl_random_pseudo_bytes($bytes)));
        }else{
            $rnd = hexdec(bin2hex(rand()."_".rand()));
        }
        $rnd = $rnd & $filter; // discard irrelevant bits
    } while ($rnd >= $range);
    return $min + $rnd;
}

function pwGen($password,$md5ed=False)
{
    if (!$md5ed) $password=md5($password);
    $salt = sha1(rand());
    $salt = substr($salt, 0, 4);
    $hash = base64_encode( sha1($password . $salt, true) . $salt );
    return $hash;
}

function pwCheck($password,$saved)
{
    $svd=base64_decode($saved);
    $salt=substr($svd,20);
    $password=md5($password);
    $hash = base64_encode( sha1(($password) . $salt, true) . $salt );
    if (strcmp($hash,$saved)==0) return True;
    else return False;
}

function is_valid_user_name($user_name){
    $len=strlen($user_name);
    for ($i=0;$i<$len;$i++){
        if (
            ($user_name[$i]>='a' && $user_name[$i]<='z') ||
            ($user_name[$i]>='A' && $user_name[$i]<='Z') ||
            ($user_name[$i]>='0' && $user_name[$i]<='9') ||
            $user_name[$i]=='_'||
            ($i==0 && $user_name[$i]=='*')
        );
        else return false;
    }
    return true;
}

function check_login($user_id,$password){
    session_destroy();
    session_start();
    $sql = "SELECT `username`, `password` FROM `user` WHERE `username`=?";
    $result = pdo_query($sql, $user_id);
    if (count($result)==1) {
        $row = $result[0];
        if( pwCheck($password,$row['password'])){
            $user_id=$row['username'];
            return $user_id;
        }
    }
    return false;
}
?>