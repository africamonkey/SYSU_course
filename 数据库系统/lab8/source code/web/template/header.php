<nav class="navbar navbar-expand-md fixed-top navbar-dark bg-primary">
    <a class="navbar-brand" href="./index.php">图书管理系统</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarCollapse" aria-controls="navbarCollapse" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarCollapse">
        <ul class="navbar-nav">
            <li class="nav-item">
                <a class="nav-link" href="./index.php">主页</a>
            </li>
            <?php if (isset($_SESSION['user_id'])) { ?>
                <li class="nav-item">
                    <a class="nav-link" href="./view_borrow_info.php">借阅记录</a>
                </li>
            <?php } ?>
            <?php if (isset($_SESSION['administrator'])) { ?>
                <li class="nav-item">
                    <a class="nav-link" href="./borrow_page.php">借书</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="./return_page.php">还书</a>
                </li>
            <?php } ?>
        </ul>
        <ul class="navbar-nav ml-auto ">
            <?php if (isset($_SESSION['user_id'])) { ?>
                <li class="navbar-text">
                    <b> <?php echo $_SESSION['user_id'] ?></b>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="./modifypage.php">修改密码</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="./logout.php">退出</a>
                </li>
            <?php } else { ?>
                <li class="nav-item">
                    <a class="nav-link" href="./login_page.php">登录</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="./register_page.php">注册</a>
                </li>
            <?php } ?>
        </ul>
    </div>
</nav>
