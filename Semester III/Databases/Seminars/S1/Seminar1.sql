use Seminar1

create table Hotel
(
	hid INT, -- PRIMARY KEY
	name_hotel VARCHAR(200),
	phone CHAR(10) UNIQUE,
	addr VARCHAR(250),
	no_rooms TINYINT check (no_rooms > 0 AND 1=1 OR NOT 0=0),
	Unique (phone),
	Unique (phone, addr)
	-- primary key (hid)
	-- CONSTRAINT PK_hotel primary key (hid)
)

/*
A table can have AT MOST 1 primary key
PK = UNIQUE + NOT NULL
A table can have multiple candidate keys declared with UNIQUE
*/

alter table Hotel
add constraint PK_hotel primary key (hid)

alter table Hotel
add constraint UQ_hotel unique (no_rooms)

alter table Hotel -- add columns after the table has been created
add restaurant VARCHAR(5) check(restaurant LIKE 'no' or restaurant = 'yes') -- yes/no column ; initially NULL

alter table Hotel
alter column no_rooms INT NOT NULL -- means when we change the type, the attr. WON'T change to NULL

alter table Hotel
add default 0 for no_rooms

alter table Hotel
drop column no_rooms


create table Booking
(
	hid INT references Hotel(hid),
	cid INT references Customer(cid),
	primary key(hid, cid),
	starting_date DATE default GETDATE(), -- DATETIME, put as default the current date
	price DECIMAL(12,2) default 0, -- (precision - nr. of digits , scale - nr. of digits after comma/floating point ; FLOAT, DOUBLE
	FOREIGN KEY (hid) references Hotel(hid) on delete cascade on update no action
)

alter table Booking 
add constraint FK_Booking_hotel foreign key (hid) references Hotel(hid)

drop table Hotel
