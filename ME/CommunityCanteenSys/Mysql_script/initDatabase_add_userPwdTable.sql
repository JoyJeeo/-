create database GraduationProject_CommunityCanteenSys;
use GraduationProject_CommunityCanteenSys;

create table loginInfo
(
	username varchar(10),
    pwd varchar(20),
    curid int
);
 
insert into loginInfo values('admin','admin','0');

create table userName_userIconPath
(
	username varchar(10),
    userIconPath varchar(1024)
);

create table dishesInfo
(
	DishName varchar(50),
    DishMoney varchar(50),
    DishNum varchar(50),
    DishImagePath varchar(1024),
    DishIndex int
);

create table AnnoInfo
(
    AnnoImagePath varchar(1024),
	AnnoIndex int
);

create table if not exists adminBuyCar
(
	DishName varchar(50),
    DishMoney varchar(50),
    DishBuyNum varchar(50),
	DishImagePath varchar(1024),
	DishIndex int -- 排序时必须以数字排序，而不是字符串
);

create table if not exists adminOrderDetail
(
	DishName varchar(50),
    DishMoney varchar(50),
    DishBuyNum varchar(50),
	DishImagePath varchar(1024),
    TakeOrderTime datetime
);



