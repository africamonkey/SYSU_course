<html>
<head>
    <meta http-equiv="Content-Type" content="text/html" charset="utf-8">
    <title><?php echo $view_title; ?></title>
    <link rel="stylesheet" href="./css/bootstrap.css" type="text/css">
    <link rel="stylesheet" href="./css/container_table.css" type="text/css">
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
                    <h3>借阅记录</h3>
                </div>
                <div id="r1">
                    <p class="text-center">
                        <?php echo $_SESSION['user_id']; ?>的当前借阅情况
                    </p>
                    <table class="table" id="borrow_info_1">
                        <thead class="thead-light">
                        <tr>
                            <th>#</th>
                            <th>题名</th>
                            <th>作者</th>
                            <th>出版年</th>
                            <th>应还日期</th>
                            <th>索书号</th>
                        </tr>
                        </thead>
                        <tbody>
                        <?php
                        foreach($result_1 as $row) {
                            ?>
                            <tr>
                                <td><?php echo $row['rec_id']; ?></td>
                                <td><?php echo $row['title']; ?></td>
                                <td><?php echo $row['author']; ?></td>
                                <td><?php echo $row['publish_year']; ?></td>
                                <td><?php echo $row['return_date']; ?></td>
                                <td><?php echo $row['visit_id']; ?></td>
                            </tr>
                            <?php
                        }
                        if (count($result_1) == 0) {
                            ?>
                            <tr>
                                <td colspan="0">无记录</td>
                            </tr>
                            <?php
                        }
                        ?>
                        </tbody>
                    </table>
                </div>
                <div id="r2">
                    <p class="text-center">
                        <?php echo $_SESSION['user_id']; ?>的历史借阅情况
                    </p>
                    <table class="table" id="borrow_info_2">
                        <thead class="thead-light">
                        <tr>
                            <th>#</th>
                            <th>题名</th>
                            <th>作者</th>
                            <th>出版年</th>
                            <th>借书日期</th>
                            <th>还书日期</th>
                            <th>索书号</th>
                        </tr>
                        </thead>
                        <tbody>
                        <?php
                        foreach($result_2 as $row) {
                            ?>
                            <tr>
                                <td><?php echo $row['rec_id']; ?></td>
                                <td><?php echo $row['title']; ?></td>
                                <td><?php echo $row['author']; ?></td>
                                <td><?php echo $row['publish_year']; ?></td>
                                <td><?php echo $row['borrow_date']; ?></td>
                                <td><?php echo $row['actual_return_date']; ?></td>
                                <td><?php echo $row['visit_id']; ?></td>
                            </tr>
                            <?php
                        }
                        if (count($result_2) == 0) {
                            ?>
                            <tr>
                                <td colspan="0">无记录</td>
                            </tr>
                            <?php
                        }
                        ?>
                        </tbody>
                    </table>
                </div>
            </div>
            <div id="foot">
                <?php require_once("./template/footer.php"); ?>
            </div>
        </div>
    </div>
</body>
</html>
