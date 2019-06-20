# 图书管理系统

## 简要介绍

图书管理系统是一个 Web 应用，主要支持图书检索、借书、还书、借阅记录查询功能。

## 环境要求

操作系统： Ubuntu 18.04 / Windows 10 ，跨平台。

Mysql 8.0

PHP 7.2

JetBrain PhpStorm 2018.3.2 / Apache / Ngnix

## 部署

图书管理系统由 2 个服务器构成，一个是 Mysql 服务器，一个是 Web 服务器。

在 Mysql 服务器上，需导入 sql/1.sql 创建表，然后导入书籍信息 Book.sql, BookInfo 。最后，需手动创建管理员账户

```
insert into `user` values ('root', '28m4K90kCaycfosklrtD2TSoq1hkMmY3', 'root');
insert into `Admin` values ('root');
```

创建完成后，管理员账户为 root ，密码为 123456 。

在 Web 服务器上，首先需在 web/include/database_config.php 中配置数据库用户名/密码，方可使用。
