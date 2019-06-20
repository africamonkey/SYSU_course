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
                <h3>修改密码</h3>
            </div>
            <form action="register.php" method="post">
                <div class="form-group">
                    <label for="UserID">用户名</label>
                    <input type="text" readonly class="form-control" id="UserID" value=<?php echo $_SESSION['user_id']?>>
                </div>
                <div class="form-group">
                    <label for="inputOPassword">原密码</label>
                    <input name="user_id" type="text" class="form-control" id="inputOPassword">
                </div>
                <div class="form-group">
                    <label for="inputPassword">新密码</label>
                    <input name="password" type="password" class="form-control" id="inputPassword">
                </div>
                <div class="form-group">
                    <label for="repeatPassword">重复新密码</label>
                    <input name="rptpassword" type="password" class="form-control" id="repeatPassword">
                </div>
                <div class="row">
                    <div class="col">
                        <button type="submit" class="btn btn-primary">修改</button>
                    </div>
                    <div class="col">
                        <button type="reset" class="btn btn-secondary">重置</button>
                    </div>
                </div>
            </form>
        </div>
        <div id="foot">
            <?php require_once("./template/footer.php"); ?>
        </div>
    </div>
</div>
</body>
</html>
