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