create database GraduationProject_CommunityCanteenSys;
use GraduationProject_CommunityCanteenSys;

create table loginInfo
(
	username varchar(10) not null unique primary key ,
    pwd varchar(20) not null
);
 
insert into loginInfo values('admin','admin');