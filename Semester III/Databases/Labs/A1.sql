use A1


--Assigment 1
create table RatingsAndReviews
(
	ReviewID INT PRIMARY KEY,
	CustomerID INT REFERENCES Customers(CustomerID),
	ProductID INT REFERENCES Products(ProductID),
	Rating TINYINT,
	Review VARCHAR(150)
);
create table Discount
(
	DiscountID INT PRIMARY KEY,
	DiscountName VARCHAR(50),
	Discount TINYINT
);
create table CustomerDiscount
(
	CustomerDiscountID  INT PRIMARY KEY,
	CustomerID INT REFERENCES Customers(CustomerID),
	DiscountID INT REFERENCES Discount(DiscountID)
);

create table Customers
(
	CustomerID INT PRIMARY KEY,
	ClientName VARCHAR(50),
	ClientEmail VARCHAR(50),
	ClientPhone CHAR(10) UNIQUE,
	ClinetAddress VARCHAR(100)
);


create table Orders
(
	OrderID INT PRIMARY KEY,
	OrderDate VARCHAR(50),
	CustomerID INT references Customers(CustomerID)
);

create table Manufacturers
(
	ManufacturerID INT PRIMARY KEY,
	ManufacturerName VARCHAR(50)
);

create table Products
(
	ProductID INT PRIMARY KEY,
	ProductName VARCHAR(50),
	Descript VARCHAR(100),
	Price INT,
	ManufacturerID INT references Manufacturers(ManufacturerID)
);

create table OrderDetails
(
	OrderDetailID INT PRIMARY KEY,
	OrderID INT references Orders(OrderID),
	ProductID INT references Products(ProductID),
	Quantity TINYINT
);

create table Employees
(
	EmployeeID INT PRIMARY KEY,
	EmployeeName VARCHAR(50),
	EmployeeEmail VARCHAR(100),
	EmployeePhone CHAR(10) UNIQUE
);

create table EmployeeRoles
(
	RoleID INT PRIMARY KEY,
	RoleName VARCHAR(50)
);

create table EmployeeAssignments
(
	AssignmentID INT PRIMARY KEY,
	EmployeeID INT references Employees(EmployeeID),
	RoleID INT references EmployeeRoles(RoleID)
);


ALTER TABLE Products
ADD Quantity TINYINT;

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


-- Assigment 2

--
--INSERT/UPDATE/DELETE
--


INSERT INTO Manufacturers (ManufacturerID, ManufacturerName)
VALUES
	(3, 'Acer');
    (1, 'Manufacturer A'),
    (2, 'Manufacturer B');


UPDATE Manufacturers
SET ManufacturerName ='ASUS'
WHERE ManufacturerID=2;


INSERT INTO Customers (CustomerID, ClientName, ClientEmail, ClientPhone, ClinetAddress)
VALUES
	(5,'martin','','1233567891','romania, cluj'),
	(4, 'dad', '', '1234567098','214 str'),
    (1, 'John Doe', 'john@example.com', '1234567890', '123 Main St'),
    (2, 'Jane Smith', 'jane@example.com', '9876543210', '456 Elm St'),
	(3,'Darius', 'darius.ion@yahoo.com','1243567890', 'Dorobantilor nr.40');

INSERT INTO Discount (DiscountID, DiscountName, Discount)
VALUES
    (1, '10% Off', 10),
    (2, '15% Off', 15);

INSERT INTO CustomerDiscount(CustomerDiscountID, CustomerID,DiscountID)
VALUES
	(10,1,1),
	(15,3,2);

INSERT INTO Products (ProductID, ProductName, Descript, Price, ManufacturerID, Quantity)
VALUES
    (1, 'Laptop Acer Aspire 5', 'Office laptop, has poor gaming performance', 1500, 3, 25),
    (2, 'Lenovo Legion', 'Very performant gaming laptop', 3500, 1, 15),
	(3, 'Acer Zenbook' , 'Light weight laptop', 3000, 3,50);

INSERT INTO RatingsAndReviews (ReviewID, CustomerID, ProductID, Rating, Review)
VALUES
    (1, 1, 1, 5, 'Great product!'),
    (2, 2, 3, 4, 'Good product, but could be better.'),
	(3, 2, 1, 3, 'Poor performance');

INSERT INTO Orders (OrderID, OrderDate, CustomerID)
VALUES
	(3, '2022-01-10', 1),
    (1, '2023-11-01', 1),
    (2, '2023-10-04', 2);

INSERT INTO OrderDetails (OrderDetailID, OrderID, ProductID, Quantity)
VALUES
    (1, 1, 1, 1),
    (2, 2, 2, 3);


INSERT INTO Employees (EmployeeID, EmployeeName, EmployeeEmail, EmployeePhone)
VALUES
    (1, 'Pricope Ion', 'Ion@gmail.com', '1112223333'),
    (2, 'Constantinescu Florin', 'Florin@yahoo.com', '4445556666'),
	(3, 'Doru Mihes', 'doru.Mihes@yahoo.,com' , '0755841454'),
	(4, 'Matias', 'matias.sefubanilor@gmail.com', '0745804531');

INSERT INTO EmployeeRoles (RoleID, RoleName)
VALUES
    (1, 'Manager'),
    (2, 'Employee'),
	(3, 'Boss'),
	(4, 'Somer');

INSERT INTO EmployeeAssignments (AssignmentID, EmployeeID, RoleID)
VALUES
    (1, 1, 2),
    (2, 2, 2),
	(3, 4, 3);

INSERT INTO Orders (OrderID, OrderDate, CustomerID)
VALUES (1, '2023-11-03', 5); -- This will violate the referential integrity constraint


UPDATE Products
SET Price = Price + 10
WHERE Price < 100;

UPDATE Customers
SET ClinetAddress = 'Cluj'
WHERE ClientName LIKE 'J%';

UPDATE OrderDetails
SET Quantity = 5
WHERE Quantity BETWEEN 2 AND 3;

UPDATE Customers
SET ClientEmail = NULL
WHERE CustomerID = 4;

UPDATE Customers
SET ClinetAddress = '456 Elm St'
WHERE CustomerID = 1;


UPDATE Products
SET Price = Price + 10
WHERE ProductID = 1;

UPDATE EmployeeAssignments
SET RoleID = 1
WHERE EmployeeID = 1;


DELETE FROM Orders
WHERE OrderID = 3;

DELETE FROM Customers
WHERE ClientEmail IS NULL;

DELETE FROM Orders
WHERE CustomerID IN (SELECT CustomerID FROM Customers WHERE ClientEmail IS NULL);




--
-- 2 queries with the union operation; use UNION [ALL] and OR;
--



--we use OR to filter records in the Customers table based on non-null email addresses or customers whose names match employees 
--with non-null email addresses from the Employees table and order by name
SELECT ClientName, ClientEmail
FROM Customers
WHERE ClientEmail IS NOT NULL
OR ClientName IN (SELECT EmployeeName FROM Employees WHERE EmployeeEmail IS NOT NULL)
ORDER BY ClientName ;



--Take  the distinct ID and the name of the clients which starts with J and makes a union with the Employee ID and name 
--which starts with M OR J
SELECT DISTINCT CustomerID, ClientName
FROM Customers
WHERE ClientName LIKE 'J%'
UNION ALL
SELECT EmployeeID, EmployeeName
FROM Employees
WHERE (EmployeeName LIKE 'M%' or EmployeeName LIKE '%J');






--
--2 queries with the intersection operation; use INTERSECT and IN;
--


-- Intersect the distinct Customers who's name start with letter J or lives in Romania with the ones that do not have an email 
--and sort them alphabetically
SELECT DISTINCT CustomerID, ClientName
FROM Customers
WHERE (ClientName LIKE 'J%' OR ClinetAddress LIKE 'Romania%')
INTERSECT
SELECT DISTINCT CustomerID, ClientName
FROM Customers
WHERE ClientEmail IS NOT NULL
ORDER BY ClientName; 

select * from Customers

--query returns list of employees (top 3 most importants) who have been assigned roles as Manager or Boss and sort by name
SELECT TOP 3 EmployeeID, EmployeeName
FROM Employees
WHERE EmployeeID IN (
    SELECT EmployeeID
    FROM EmployeeAssignments
    WHERE RoleID IN (
        SELECT RoleID
        FROM EmployeeRoles
        WHERE RoleName IN ('Manager', 'Boss')
    )
)
ORDER BY EmployeeName;


--2 queries with the difference operation; use EXCEPT and NOT IN;

-- find customers who have not made any orders
SELECT DISTINCT ClientName FROM Customers
EXCEPT
SELECT DISTINCT ClientName FROM Customers
WHERE CustomerID IN (SELECT CustomerID FROM Orders);


-- find products that have not been reviewed
SELECT ProductName FROM Products
WHERE ProductID NOT IN (SELECT ProductID FROM RatingsAndReviews);



--4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); 
--one query will join at least 3 tables, while another one will join at least two many-to-many relationships;


-- get customer names and associated discount names from two many-to-many relationships: CustomerDiscount and Discount
SELECT Customers.ClientName, Discount.DiscountName
FROM Customers
LEFT JOIN CustomerDiscount ON Customers.CustomerID = CustomerDiscount.CustomerID
LEFT JOIN Discount ON CustomerDiscount.DiscountID = Discount.DiscountID;


--This query ensures that all records from the "Orders," "OrderDetails," and "Products" tables are included in the result
SELECT Customers.ClientName, Orders.OrderID, Products.ProductName
FROM Customers
RIGHT JOIN Orders ON Customers.CustomerID = Orders.CustomerID
RIGHT JOIN OrderDetails ON Orders.OrderID = OrderDetails.OrderID
RIGHT JOIN Products ON OrderDetails.ProductID = Products.ProductID;



-- combine data from the Customers, Orders, OrderDetails, and Products tables to retrieve customer names, order IDs 
--and product names 
--for products in the orders
SELECT Customers.ClientName, Orders.OrderID, Products.ProductName
FROM Customers
INNER JOIN Orders ON Customers.CustomerID = Orders.CustomerID
INNER JOIN OrderDetails ON Orders.OrderID = OrderDetails.OrderID
INNER JOIN Products ON OrderDetails.ProductID = Products.ProductID;



--combine data from the Customers, Orders, OrderDetails, and Products tables. 
--This retrieves all customer names, order IDs, and product names, including cases 
--where there are no matches between the tables.
SELECT Customers.ClientName, Orders.OrderID, Products.ProductName
FROM Customers
FULL JOIN Orders ON Customers.CustomerID = Orders.CustomerID
FULL JOIN OrderDetails ON Orders.OrderID = OrderDetails.OrderID
FULL JOIN Products ON OrderDetails.ProductID = Products.ProductID;




--
-- 2 queries with the IN operator and a subquery in the WHERE clause; 
--in at least one case, the subquery must include a subquery in its own WHERE clause;
--



--it uses nested subqueries to first find the order IDs placed by the customer and 
--then the corresponding products in those orders
SELECT ProductName, Price, ProductID
FROM Products
WHERE ProductID IN (
    SELECT ProductID
    FROM OrderDetails
    WHERE OrderID IN (
        SELECT OrderID
        FROM Orders
        WHERE CustomerID = 1
    )
);




--uses a subquery within a subquery to first find the RoleID associated with the 'Manager' role 
--and then the EmployeeIDs assigned to that role
SELECT EmployeeName, EmployeeEmail
FROM Employees
WHERE EmployeeID IN (
    SELECT EmployeeID
    FROM EmployeeAssignments
    WHERE RoleID IN (
        SELECT RoleID
        FROM EmployeeRoles
        WHERE RoleName = 'Manager'
    )
);





--
--2 queries with the EXISTS operator and a subquery in the WHERE clause
--


--The subquery in the WHERE clause checks whether there are any matching records in the "Orders" table for each customer.
-- If at least one order exists for a customer, that customer's information is selected
SELECT ClientName, ClientEmail
FROM Customers
WHERE EXISTS (
    SELECT 1
    FROM Orders
    WHERE Orders.CustomerID = Customers.CustomerID
);


--The subquery in the WHERE clause checks whether there are any matching records in the "EmployeeAssignments" table 
--for employees who are assigned the role of 'Manager' based on the subquery within the EXISTS condition
SELECT EmployeeName, EmployeeEmail
FROM Employees
WHERE EXISTS (
    SELECT 1
    FROM EmployeeAssignments
    WHERE EmployeeAssignments.EmployeeID = Employees.EmployeeID
    AND EmployeeAssignments.RoleID = (
        SELECT RoleID
        FROM EmployeeRoles
        WHERE RoleName = 'Manager'
    )
);


--
--2 queries with a subquery in the FROM clause
--


-- selects the name and email of an employee with a name which starts with C or a romania phone number 
SELECT *
FROM (
    SELECT EmployeeName, EmployeeEmail
    FROM Employees
    WHERE EmployeeName LIKE 'C%' OR EmployeePhone LIKE '07%'
) AS SubqueryResult;



--calculates and displays top 2 the product names and their total sales quantities and the Total price
--using a subquery to aggregate sales data from the "OrderDetails" table
--joins the result with the "Products" table to associate the product names with the calculated total sales
SELECT TOP 2 PD.ProductName, OD.TotalSales, PD.Price * OD.TotalSales AS TotalPrice
FROM (
    SELECT ProductID, SUM(Quantity) AS TotalSales
    FROM OrderDetails
    GROUP BY ProductID
) OD
JOIN Products PD ON OD.ProductID = PD.ProductID;





--
-- 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;
--

--groups products by ManufacturerID and counts the total products for each manufacturer. 
--The HAVING clause filters out manufacturers with less than 1 product
SELECT ManufacturerID, COUNT(*) AS TotalProducts
FROM Products
GROUP BY ManufacturerID
HAVING COUNT(*) >= 1;


--calculates the average price of products for each manufacturer
--and filter out manufacturers with an average product price higher than the overall average product price
SELECT ManufacturerID, AVG(Price) AS AvgProductPrice
FROM Products
GROUP BY ManufacturerID
HAVING AVG(Price) > (SELECT AVG(Price) FROM Products);


-- calculates the maximum price for each manufacturer. 
--The HAVING clause uses a subquery to filter out manufacturers whose maximum product price exceeds 90% of the overall maximum product price.

SELECT ManufacturerID, MAX(Price) AS MaxPrice
FROM Products
GROUP BY ManufacturerID
HAVING MAX(Price) > (SELECT MAX(Price) * 0.9 FROM Products);

--groups orders by CustomerID and calculates the latest order date for each customer
-- HAVING clause uses a subquery to filter out customers who have placed orders within the last six months

SELECT CustomerID, MAX(OrderDate) AS LatestOrderDate
FROM Orders
GROUP BY CustomerID
HAVING MAX(OrderDate) > (SELECT DATEADD(MONTH, -6, GETDATE()));




--
--4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
--rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.
--

--find employees whose EmployeeID matches the EmployeeID in the subquery for a specific role
SELECT EmployeeName
FROM Employees
WHERE EmployeeID = ANY (SELECT EmployeeID FROM EmployeeAssignments WHERE RoleID = 1);

--find roles whose RoleID matches the RoleID in the subquery for a specific employee
SELECT RoleName
FROM EmployeeRoles
WHERE RoleID = ANY (SELECT RoleID FROM EmployeeAssignments WHERE EmployeeID = 1);

-- find employees whose EmployeeID matches all EmployeeIDs in the subquery for a specific role
SELECT EmployeeName
FROM Employees
WHERE EmployeeID = ALL (SELECT EmployeeID FROM EmployeeAssignments WHERE RoleID = 2);

-- find roles whose RoleID matches all RoleIDs in the subquery for a specific employee
SELECT RoleName
FROM EmployeeRoles
WHERE RoleID = ALL (SELECT RoleID FROM EmployeeAssignments WHERE EmployeeID = 1);


--rewrite

-- find employees or roles based on the maximum value from the subquery
SELECT EmployeeName
FROM Employees
WHERE EmployeeID = ANY (SELECT MAX(EmployeeID) FROM EmployeeAssignments WHERE RoleID = 1);

-- find employees or roles based on the minimum value from the subquery
SELECT RoleName
FROM EmployeeRoles
WHERE RoleID = ANY (SELECT MIN(RoleID) FROM EmployeeAssignments WHERE EmployeeID = 2);


-- operator to find employees whose EmployeeID matches any EmployeeID in the subquery for a specific role.
SELECT EmployeeName
FROM Employees
WHERE EmployeeID IN (SELECT EmployeeID FROM EmployeeAssignments WHERE RoleID = 2);

-- find roles whose RoleID does not match any RoleID in the subquery for a specific employee
SELECT RoleName
FROM EmployeeRoles
WHERE RoleID  IN (SELECT RoleID FROM EmployeeAssignments WHERE EmployeeID = 1);




--
--Use arithmetic expressions in the SELECT clause
--


-- calculates the total price of each order by multiplying the Price and Quantity columns and then summing them up
SELECT Orders.OrderID, SUM(Products.Price * OrderDetails.Quantity) AS TotalPrice
FROM Orders
JOIN OrderDetails ON Orders.OrderID = OrderDetails.OrderID
JOIN Products ON OrderDetails.ProductID = Products.ProductID
GROUP BY Orders.OrderID;


--Calculate the total price of  each product in the hole stock
SELECT ProductID, ProductName, (Price * Quantity) AS TotalPrice
FROM Products;

--Calculate the average rating of products from the RatingsAndReviews table
SELECT ProductID, AVG(Rating) AS AverageRating
FROM RatingsAndReviews
GROUP BY ProductID;





--Assigment 3

--a. modify the type of a column
GO
CREATE OR ALTER PROC changeQuantity
AS 
BEGIN
	ALTER TABLE OrderDetails 
	ALTER COLUMN Quantity DECIMAL(10,2)
	PRINT 'OrderDetails table Quantity from TINYINT to DECIMAL'
END
GO

--a.undo

GO
CREATE OR ALTER PROC UNDOchangeQuantity
AS 
BEGIN
	ALTER TABLE OrderDetails 
	ALTER COLUMN Quantity TINYINT
	PRINT '(UNDO) OrderDetails table Quantity from DECIMAL to TINYINT'
END
GO


-- b. add/remove a column

CREATE OR ALTER PROC removeClientEmail
AS
BEGIN
	ALTER TABLE Customers
	DROP COLUMN ClientEmail
	PRINT 'Customers table remove column ClientEmail'
END
GO

-- b.undo
CREATE OR ALTER PROC UNDOremoveClientEmail
AS
BEGIN
	ALTER TABLE Customers
	ADD ClientEmail VARCHAR(50)
	PRINT '(UNDO) Customers table add column ClientEmail'
END
GO

--c. add/remove a DEFAULT constraint

CREATE OR ALTER PROC addDefaultConstraint
AS
BEGIN
	ALTER TABLE Products
	ADD CONSTRAINT default_quantity DEFAULT 0 FOR Quantity
	PRINT 'Set the default quantity for a product as 0'
END
GO

--c.undo


CREATE OR ALTER PROC UNDOaddDefaultConstraint
AS
BEGIN
	ALTER TABLE Products
	DROP CONSTRAINT default_quantity 
	PRINT '(UNDO)  Undo the creation of the default quantity for a product as 0'
END
GO



-- d. add/remove a primary key


CREATE OR ALTER PROC removePrimaryKey
AS
BEGIN
	DECLARE @ConstraintName NVARCHAR(128);

    -- Find the name of the primary key constraint
    SELECT @ConstraintName = CONSTRAINT_NAME
    FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE
    WHERE TABLE_NAME = 'OrderDetails' AND COLUMN_NAME = 'OrderDetailID';

    IF @ConstraintName IS NOT NULL
    BEGIN
        -- Drop the primary key constraint
        EXEC('ALTER TABLE OrderDetails DROP CONSTRAINT ' + @ConstraintName);
        PRINT 'Primary key constraint dropped for OrderDetails table';
    END
    ELSE
    BEGIN
        PRINT 'Primary key constraint not found for OrderDetails table';
    END
END
GO

--d.undo


CREATE OR ALTER PROCEDURE UNDOremovePrimaryKey
AS
BEGIN
    ALTER TABLE OrderDetails
	ADD CONSTRAINT pk_ID PRIMARY KEY (OrderDetailID)
	PRINT '(UNDO) Primary key constraint added back to OrderDetails table'
END
GO


-- e. add/remove a candidate key

CREATE OR ALTER PROC addCandidateKey
AS
BEGIN
	ALTER TABLE Employees
	ADD CONSTRAINT UQ_Name UNIQUE(EmployeeName)
	PRINT 'Set the Employee Name to be unique'
END
GO

--e. undo

CREATE OR ALTER PROC UNDOaddCandidateKey
AS
BEGIN 
	ALTER TABLE Employees
	DROP CONSTRAINT UQ_Name
	PRINT '(UNDO) Drop the constraint for the Employee Name'
END
GO


-- f. add/remove a foreign key


CREATE OR ALTER PROC removeForeignKey
AS
BEGIN 
	DECLARE @ConstraintName NVARCHAR(128);

    -- Find the name of the primary key constraint
    SELECT @ConstraintName = CONSTRAINT_NAME
    FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE
    WHERE TABLE_NAME = 'RatingsAndReviews' AND COLUMN_NAME = 'ProductID';

    IF @ConstraintName IS NOT NULL
    BEGIN
        -- Drop the primary key constraint
        EXEC('ALTER TABLE RatingsAndReviews DROP CONSTRAINT ' + @ConstraintName);
        PRINT 'Foreign key constraint dropped for RatingsAndReviews table';
    END
    ELSE
    BEGIN
        PRINT 'Foreign key constraint not found for RatingsAndReviews table';
    END
END
GO

--f. undo


CREATE OR ALTER PROC UNDOremoveForeignKey
AS
BEGIN	
	ALTER TABLE RatingsAndReviews
	ADD CONSTRAINT ProductID FOREIGN KEY(ProductID) REFERENCES Products(ProductID)
	PRINT '(UNDO)  Added back the foreign key constraint'
END
GO




-- g. create/drop a table


CREATE OR ALTER PROC createTable
AS
BEGIN
	CREATE TABLE statisticsTable(stID INT NOT NULL PRIMARY KEY, ProductID INT REFERENCES Products(ProductID), productDescp VARCHAR(100) )
	PRINT 'Table created: statisticsTable'
END
GO

--g. undo

CREATE OR ALTER PROC UNDOcreateTable
AS
BEGIN
	DROP TABLE IF EXISTS statisticsTable
	PRINT '(UNDO)  statisticsTable DROPED'
END
GO

exec changeQuantity
exec removeClientEmail
exec addDefaultConstraint
exec removePrimaryKey
exec addCandidateKey
exec removeForeignKey
exec createTable

exec UNDOchangeQuantity
exec UNDOremoveClientEmail
exec UNDOaddDefaultConstraint
exec UNDOremovePrimaryKey
exec UNDOaddCandidateKey
exec UNDOremoveForeignKey
exec UNDOcreateTable


exec changeQuantity
exec UNDOchangeQuantity

exec removeClientEmail
exec UNDOremoveClientEmail

exec addDefaultConstraint
exec UNDOaddDefaultConstraint

exec removePrimaryKey
exec UNDOremovePrimaryKey

exec addCandidateKey
exec UNDOaddCandidateKey

exec removeForeignKey
exec UNDOremoveForeignKey

exec createTable
exec UNDOcreateTable


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




--Create a table that holds the versions of the database schema (the version is an integer number)

CREATE TABLE VersionChanged
	(
		currentProcedure VARCHAR(100),
		backwardsProcedure VARCHAR(100),
		versionTO INT UNIQUE
	)
GO


INSERT INTO VersionChanged(currentProcedure,backwardsProcedure,versionTO)
VALUES
('changeQuantity','UNDOchangeQuantity',1),
('removeClientEmail','UNDOremoveClientEmail',2),
('addDefaultConstraint','UNDOaddDefaultConstraint',3),
('removePrimaryKey','UNDOremovePrimaryKey',4),
('addCandidateKey','UNDOaddCandidateKey',5),
('removeForeignKey','UNDOremoveForeignKey',6),
('createTable','UNDOcreateTable',7);
	
SELECT * FROM VersionChanged


-- create a table that keeps only the current version (the version is an integer number)

CREATE TABLE CurrentVersion (currentVersion INT DEFAULT 0);

INSERT INTO CurrentVersion VALUES(0)

SELECT * FROM CurrentVersion


GO
CREATE OR ALTER PROCEDURE goToVersion(@version INT)
AS
BEGIN
	 DECLARE @currentVersion INT
	 IF @version < 0 OR @version > 7  -- check if we are between limits
		BEGIN
			RAISERROR('Choose a number between 0 and 7 for the version number',17,1)
			--PRINT ('INVALID VERSION')
			RETURN
		END
	ELSE
		IF @version = @currentVersion -- check whether the version parameter is the current parameter
			BEGIN
				PRINT N'We are already on this version!'
				RETURN
			END
		ELSE
		DECLARE @currentProcedure NVARCHAR(50)
		SET @currentVersion = (SELECT currentVersion FROM CurrentVersion)  -- get the current version of the database
		IF @currentVersion < @version
			BEGIN
				WHILE @currentVersion < @version
					BEGIN 
						PRINT N'We are at version ' + CAST(@currentVersion as NVARCHAR(10))
						SET @currentProcedure = (SELECT currentProcedure
												 FROM VersionChanged
												 WHERE versionTO = @currentVersion + 1)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion + 1
					END
			END
		ELSE
		IF @currentVersion > @version  -- if we have to do UNDO operations
			BEGIN
				WHILE @currentVersion > @version
					BEGIN
						PRINT N'We are at version ' + CAST(@currentVersion as NVARCHAR(10))
						SET @currentProcedure = (SELECT backwardsProcedure
												FROM VersionChanged
												WHERE versionTO = @currentVersion)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion - 1
					END
			END
		UPDATE CurrentVersion
			SET currentVersion = @currentVersion
		PRINT N'Current version updated!'
		PRINT N'We reached the desired version: ' + CAST(@currentVersion as NVARCHAR(10))
END

Select * FROM VersionChanged

GO
EXEC goToVersion 3
EXEC goToVersion 6
EXEC goToVersion 5
EXEC goToVersion 2
EXEC goToVersion 0
EXEC goToVersion -1