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
                    <h3>书目检索</h3>
                </div>
                <?php if (isset($_GET['wa']) and $_GET['wa'] == '30') { ?>
                    <div class="alert alert-danger" role="alert">
                        检索关键词不得超过 30 个字符
                    </div>
                <?php } ?>

                <?php if (isset($_GET['wa']) and $_GET['wa'] == '0') { ?>
                    <div class="alert alert-danger" role="alert">
                        空的搜索行
                    </div>
                <?php } ?>

                <form action="search.php" method="get" class="form">
                    <div class="form-group">
                        <label for="inputKeyword">关键词</label>
                        <input name="keyword" type="text" class="form-control" id="inputKeyword">
                    </div>
                    <button name="submit" type="submit" class="btn btn-primary">书目检索</button>
                </form>
            </div>
            <div id="foot">
                <?php require_once("./template/footer.php"); ?>
            </div>
        </div>
<!--        <div id="main">-->
<!--            <form action="search.php" method="get">-->
<!--                <table>-->
<!--                    <tr>-->
<!--                        <td><input name="keyword" type="text" size="30"></td>-->
<!--                        <td><input name="submit" type="submit" value="书目检索"></td>-->
<!--                    </tr>-->
<!--                    --><?php //if (isset($_GET['wa']) and $_GET['wa'] == '30') {
//                    ?>
<!--                        <tr>-->
<!--                            <td>检索关键词不得超过 30 个字符</td>-->
<!--                            <td></td>-->
<!--                        </tr>-->
<!--                    --><?php
//                    }
//                    ?>
<!---->
<!--                    --><?php //if (isset($_GET['wa']) and $_GET['wa'] == '0') {
//                        ?>
<!--                        <tr>-->
<!--                            <td>空的搜索行</td>-->
<!--                            <td></td>-->
<!--                        </tr>-->
<!--                        --><?php
//                    }
//                    ?>
<!--                </table>-->
<!--            </form>-->
<!--            <div id="foot">-->
<!--                --><?php //require_once("./template/footer.php"); ?>
<!--            </div>-->
<!--        </div>-->
    </div>
</body>
</html>