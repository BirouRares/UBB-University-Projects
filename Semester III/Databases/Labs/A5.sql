use A1

select * from Customers
select * from Orders
select * from Manufacturers
select * from Products
select * from OrderDetails 
select * from Employees
select * from EmployeeRoles
select * from EmployeeAssignments
select * from Discount
select * from CustomerDiscount
select * from RatingsAndReviews
select * from BestSellingDays

DELETE FROM Manufacturers
DELETE FROM Products
DELETE FROM OrderDetails 
DELETE FROM Employees
DELETE FROM EmployeeRoles
DELETE FROM EmployeeAssignments
DELETE FROM Discount
DELETE FROM CustomerDiscount
DELETE FROM RatingsAndReviews
DELETE FROM BestSellingDays
DELETE FROM Customers
DELETE FROM Orders

DROP TABLE EmployeeAssignments
DROP TABLE Employees
DROP TABLE EmployeeRoles

 --Ta(aid, a2, …) aid=EmployeeID, a2=EmployeePhone
create table Employees
(
	EmployeeID INT NOT NULL PRIMARY KEY,
	EmployeeName VARCHAR(50) NOT NULL,
	EmployeePhone INT UNIQUE NOT NULL
);

--Tb(bid, b2, …)  bid=RoleID, b2=RoleLevel
create table EmployeeRoles
(
	RoleID INT NOT NULL PRIMARY KEY,
	RoleLevel INT NOT NULL,
	RoleName VARCHAR(50) NOT NULL
);
--Tc(cid, aid, bid, …) cid=AssignmentID, aid=EmployeeID, bid=RoleID
create table EmployeeAssignments
(
	AssignmentID INT NOT NULL PRIMARY KEY,
	EmployeeID INT references Employees(EmployeeID) ON DELETE CASCADE ON UPDATE CASCADE,
	RoleID INT references EmployeeRoles(RoleID) ON DELETE CASCADE ON UPDATE CASCADE
);


-- insert random data

--insert into Employees
GO
CREATE OR ALTER PROC insertIntoEmployees (@n INT) AS
BEGIN
	DECLARE @EmployeeID INT =1;
	DECLARE @EmployeeName VARCHAR(50)='Marcel';
	DECLARE @EmployeePhone INT = 402142413;

	WHILE @n > 0
	BEGIN
		INSERT INTO Employees(EmployeeID,EmployeeName,EmployeePhone)
		VALUES(@EmployeeID,@EmployeeName,@EmployeePhone);
		SET @EmployeeID=@EmployeeID+1;
		SET @EmployeePhone=@EmployeePhone+25;
		SET @n= @n-1;
	END
END
GO



--insert into EmployeeRoles
GO
CREATE OR ALTER PROC insertIntoEmployeeRoles (@n INT) AS
BEGIN
	DECLARE @RoleID INT =1;
	DECLARE @RoleName VARCHAR(50)='Worker';
	DECLARE @RoleLevel INT = 1;

	WHILE @n > 0
	BEGIN
		INSERT INTO EmployeeRoles(RoleID,RoleLevel,RoleName)
		VALUES(@RoleID,@RoleLevel,@RoleName);
		SET @RoleID=@RoleID+1;
		SET @RoleLevel=@RoleLevel+1;
		SET @n=@n-1;
	END
END
GO

--insert into EmployeeAssignments
GO
CREATE OR ALTER PROC insertIntoEmployeeAssignments (@n INT) AS
BEGIN
	DECLARE @AssignmentID INT =1;
	DECLARE @EmployeeID INT =1;
	DECLARE @RoleID INT = 1;

	WHILE @n > 0
	BEGIN
		INSERT INTO EmployeeAssignments(AssignmentID,EmployeeID,RoleID)
		VALUES(@AssignmentID,@EmployeeID,@RoleID);
		SET @RoleID=@RoleID+1;
		SET @AssignmentID=@AssignmentID+1;
		SET @EmployeeID=@EmployeeID+1;
		SET @n=@n-1;
	END
END
GO


--add to tabels
EXEC insertIntoEmployees 10000;
EXEC insertIntoEmployeeRoles 10000;
EXEC insertIntoEmployeeAssignments 10000;

SELECT * FROM Employees
SELECT * FROM EmployeeRoles
SELECT * FROM EmployeeAssignments



---------a------------

EXEC sp_helpindex Employees;

-- PK: EmployeeID => automatically created clustered index
-- unique: EmployeePhone => automatically created unclustered index

-- clustered index scan => touch every row in the table

SELECT * FROM Employees


-- clustered index seek => returns a specific subset from the clustered index

SELECT * FROM Employees
WHERE EmployeeID<412;





-- nonclustered index scan => scan the entire nonclustered index

SELECT EmployeeName FROM Employees;




-- nonclustered index seek => returns a specific subset from the nonclustered index

SELECT EmployeeName FROM Employees
WHERE EmployeePhone = 402142413;




-- key lookup => nonclustered index seek

SELECT EmployeeName, EmployeePhone FROM Employees
WHERE EmployeeID < 324;





--------------------------------------------------

--b

-- first it's a clustered index scan 

SELECT RoleLevel FROM EmployeeRoles
WHERE RoleLevel<34;


DROP INDEX IF EXISTS EmployeeRolesNonClustered ON EmployeeRoles

CREATE NONCLUSTERED INDEX EmployeeRolesNonClustered ON EmployeeRoles(RoleLevel)


-- now we have a nonclustered index seek, which is more efficient

SELECT RoleID FROM EmployeeRoles
WHERE RoleLevel<34;


-----------------------------------------------------------------------------------------------

--c

DROP VIEW IF EXISTS view1;
GO


CREATE OR ALTER VIEW   view1 AS
	SELECT C.AssignmentID, C.RoleID, B.RoleLevel, B.RoleName FROM EmployeeAssignments C
	INNER JOIN EmployeeRoles B ON C.RoleID = B.RoleID
	WHERE B.RoleLevel < 112;
GO

DECLARE @start1 DATETIME = GETDATE();
SELECT * FROM view1
DECLARE @end1 DATETIME = GETDATE();
PRINT 'WITHOUT INDEXES: start: ' + CONVERT(NVARCHAR(MAX), @start1) + ', end: ' + CONVERT(NVARCHAR(MAX), @end1) 
		+ ', total time: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start1, @end1)) + ' milliseconds';

DROP INDEX IF EXISTS Nonclustered1 ON EmployeeRoles
DROP INDEX IF EXISTS Nonclustered2 ON EmployeeRoles
DROP INDEX IF EXISTS Nonclustered3 ON EmployeeRoles
DROP INDEX IF EXISTS Nonclustered4 ON EmployeeAssignments
DROP INDEX IF EXISTS Nonclustered5 ON EmployeeAssignments


CREATE NONCLUSTERED INDEX Nonclustered1 ON EmployeeRoles(RoleLevel) 
CREATE NONCLUSTERED INDEX Nonclustered2 ON EmployeeRoles(RoleName) 
CREATE NONCLUSTERED INDEX Nonclustered3 ON EmployeeRoles(RoleID) 
CREATE NONCLUSTERED INDEX Nonclustered4 ON EmployeeAssignments(RoleID)
CREATE NONCLUSTERED INDEX Nonclustered5 ON EmployeeAssignments(AssignmentID)

DROP VIEW IF EXISTS view2;
GO

CREATE OR ALTER VIEW view2 AS
	SELECT C.AssignmentID, C.RoleID, B.RoleLevel, B.RoleName FROM EmployeeAssignments C
	INNER JOIN EmployeeRoles B ON C.RoleID = B.RoleID
	WHERE B.RoleLevel < 112;
GO

DECLARE @start2 DATETIME = GETDATE();
SELECT * FROM view2
DECLARE @end2 DATETIME = GETDATE();

PRINT 'Total time: ' + CONVERT(NVARCHAR(MAX), DATEDIFF(millisecond, @start2, @end2)) + ' milliseconds';