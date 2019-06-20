<html>
<head>
    <meta http-equiv="Content-Type" content="text/html" charset="utf-8">
    <title><?php echo $view_title; ?></title>
    <link rel="stylesheet" href="./css/bootstrap.css" type="text/css">
    <link rel="stylesheet" href="./css/container.css" type="text/css">
<!--    <script type="text/javascript" src="./js/bootstrap.js"></script>-->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
</head>
<body>
    <div id="wrapper">
        <?php require_once("./template/header.php"); ?>
        <div id="main">
            <div class="container">
                <div class="py-4 text-center">
                    <h3>登录</h3>
                </div>
                <?php if (isset($_GET['wrong'])) { ?>
                    <div class="alert alert-danger" role="alert">
                        用户名或密码错误
                    </div>
                <?php } ?>
                <form action="login.php" method="post">
                    <div class="form-group">
                        <label for="inputUserID">用户名</label>
                        <input name="user_id" type="text" class="form-control" id="inputUserID" placeholder="输入用户名">
                    </div>
                    <div class="form-group">
                        <label for="inputPassword">密码</label>
                        <input name="password" type="password" class="form-control" id="inputPassword" placeholder="输入密码">
                    </div>
                    <button type="submit" class="btn btn-primary">登录</button>
                </form>
            </div>
            <div id="foot">
                <?php require_once("./template/footer.php"); ?>
            </div>
        </div>
    </div>
</body>
</html>
