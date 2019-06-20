/*=================================================*/
/* Table: BookInfo
/* Definition: 
/* Author: gzez2012@163.com
/*=================================================*/
CREATE TABLE IF NOT EXISTS `BookInfo` (
	`isbn`	VARCHAR(50)	NOT NULL	COMMENT 'ISBN',
	`class`	VARCHAR(50)	COMMENT '分类',
	`title`	VARCHAR(50)	COMMENT '书名',
	`author`	VARCHAR(50)	COMMENT '作者',
	`press`	VARCHAR(50)	COMMENT '出版社',
	`publish_date`	VARCHAR(50)	COMMENT '出版日期',
	`intro`	TEXT	COMMENT '简介',
	PRIMARY KEY (`isbn`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE=utf8_bin
COMMENT='书籍信息';
/*=================================================*/
/* Table: Reader
/* Definition: 
/* Author: gzez2012@163.com
/*=================================================*/
CREATE TABLE IF NOT EXISTS `Reader` (
	`id`	INTEGER	NOT NULL	COMMENT '学号',
	`name`	VARCHAR(50)	NOT NULL	COMMENT '姓名',
	`department`	VARCHAR(50)	COMMENT '所在系',
	`penalty`	INTEGER	NOT NULL	DEFAULT '0'	COMMENT '累计违章次数',
	`borrowed_book`	INTEGER	NOT NULL	DEFAULT '0'	COMMENT '累计借书次数',
	`gender`	VARCHAR(1)	COMMENT '性别||CU0097',
	`phone`	VARCHAR(50)	COMMENT '联系电话',
	`remark`	TEXT	COMMENT '备注',
	PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE=utf8_bin
COMMENT='读者';
/*=================================================*/
/* Table: Admin
/* Definition: 
/* Author: gzez2012@163.com
/*=================================================*/
CREATE TABLE IF NOT EXISTS `Admin` (
	`id`	INTEGER	NOT NULL	COMMENT '工作号',
	`name`	VARCHAR(50)	NOT NULL	COMMENT '姓名',
	`gender`	VARCHAR(1)	COMMENT '性别||CU0097',
	`phone`	VARCHAR(50)	COMMENT '电话',
	`address`	VARCHAR(50)	COMMENT '家庭住址',
	`remark`	TEXT	COMMENT '备注',
	PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE=utf8_bin
COMMENT='管理员';
/*=================================================*/
/* Table: Book
/* Definition: 
/* Author: gzez2012@163.com
/*=================================================*/
CREATE TABLE IF NOT EXISTS `Book` (
	`id`	VARCHAR(50)	NOT NULL	COMMENT '索书号',
	`isbn`	VARCHAR(50)	NOT NULL	COMMENT 'ISBN',
	`remark`	TEXT	COMMENT '备注',
	PRIMARY KEY (`id`),
	CONSTRAINT `fk_Book_4` FOREIGN KEY (`isbn`) REFERENCES `BookInfo`(`isbn`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE=utf8_bin
COMMENT='书本';
/*=================================================*/
/* Table: Borrows
/* Definition: 
/* Author: gzez2012@163.com
/*=================================================*/
CREATE TABLE IF NOT EXISTS `Borrows` (
	`rec_id`	INTEGER	NOT NULL	COMMENT '借书记录编号',
	`stu_id`	INTEGER	NOT NULL	COMMENT '读者学号',
	`book_id`	VARCHAR(50)	NOT NULL	COMMENT '索书号',
	`admin_id`	INTEGER	NOT NULL	COMMENT '操作者工作号',
	`continue_debit`	VARCHAR(1)	NOT NULL	DEFAULT 'N'	COMMENT '是否续借',
	`borrow_date`	DATE	NOT NULL	COMMENT '借书日期',
	`return_date`	DATE	NOT NULL	COMMENT '应还日期',
	`actual_return_date`	DATE	COMMENT '实际还书日期',
	PRIMARY KEY (`rec_id`),
	CONSTRAINT `fk_Borrows_2` FOREIGN KEY (`book_id`) REFERENCES `Book`(`book_id`),
	CONSTRAINT `fk_Borrows_3` FOREIGN KEY (`stu_id`) REFERENCES `Reader`(`stu_id`),
	CONSTRAINT `fk_Borrows_4` FOREIGN KEY (`admin_id`) REFERENCES `Admin`(`admin_id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE=utf8_bin
COMMENT='借阅关系';
