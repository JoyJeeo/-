create database GraduationProject_CommunityCanteenSys;
use GraduationProject_CommunityCanteenSys;

create table loginInfo
(
	username varchar(10),
    pwd varchar(20),
    curid varchar(20)
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
    DishIndex varchar(50)
);

create table AnnoInfo
(
    AnnoImagePath varchar(1024),
	AnnoIndex varchar(50)
);