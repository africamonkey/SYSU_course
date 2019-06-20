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
                    <h3>归还书本</h3>
                </div>
                <?php if (isset($_GET['wa'])) { ?>
                    <div class="alert alert-danger" role="alert">
                        <?php echo $_GET['wa']; ?>
                    </div>
                <?php } ?>
                <?php if (isset($_GET['tle'])) { ?>
                    <div class="alert alert-warning" role="alert">
                        <?php echo $_GET['tle']; ?>
                    </div>
                <?php } ?>
                <?php if (isset($_GET['success'])) { ?>
                    <div class="alert alert-success" role="alert">
                        <?php echo $_GET['success']; ?>
                    </div>
                <?php } ?>
                <form action="return.php" method="post">
                    <div class="form-group">
                        <label for="inputBookID">书本序列号</label>
                        <input name="book_id" type="text" class="form-control" id="inputBookID">
                    </div>
                    <button type="submit" class="btn btn-primary">还书</button>
                </form>
            </div>
<!--            <form action="return.php" method="post">-->
<!--                <table>-->
<!--                    <tr>-->
<!--                        <td>书本序列号：</td>-->
<!--                        <td><input name="book_id" type="text" size="15"></td>-->
<!--                    </tr>-->
<!--                    --><?php //if (isset($_GET['wa'])) { ?>
<!--                    <tr>-->
<!--                        <td colspan="3">--><?php //echo $_GET['wa']; ?><!--</td>-->
<!--                    </tr>-->
<!--                    --><?php //} ?>
<!--                    --><?php //if (isset($_GET['tle'])) { ?>
<!--                    <tr>-->
<!--                        <td colspan="3">--><?php //echo $_GET['tle']; ?><!--</td>-->
<!--                    </tr>-->
<!--                    --><?php //} ?>
<!--                    --><?php //if (isset($_GET['success'])) { ?>
<!--                    <tr>-->
<!--                        <td colspan="3">--><?php //echo $_GET['success']; ?><!--</td>-->
<!--                    </tr>-->
<!--                    --><?php //} ?>
<!--                    <tr>-->
<!--                        <td colspan="3"><input name="submit" type="submit" value="还书"></td>-->
<!--                    </tr>-->
<!--                </table>-->
<!--            </form>-->
            <div id="foot">
                <?php require_once("./template/footer.php"); ?>
            </div>
        </div>
    </div>
</body>
</html>
