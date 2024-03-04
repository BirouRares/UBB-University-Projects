use exam

create table Researchers (
	Rid INT PRIMARY KEY, 
	Rname VARCHAR(50),
	Age INT
);

DROP TABLE Researchers

INSERT INTO Researchers(Rid,Rname,Age) 
VALUES
	(1,'gEORGE',12),
	(2,'ana',15),
	(3,'anas',30),
	(4,'saasd',23)

SELECT * FROM Researchers

SELECT R.Rname,R.Age
FROM Researchers R
WHERE R.Age = (SELECT MAX(R2.AGE)
				FROM Researchers)


-- Create the table
CREATE TABLE S2 (
    FK1 INT,
    FK2 INT,
    A VARCHAR(50),
    B VARCHAR(50),
    C VARCHAR(50),
    D INT,
    E INT
);

-- Insert data into the table
INSERT INTO S (FK1, FK2, A, B, C, D, E) VALUES
(1, 1, 'a1', 'b1', 'c1', 7, 2),
(1, 2, 'a_', 'b3', 'c1', 5, 2),
(1, 3, 'a2', 'b1', 'c2', NULL, 2),
(2, 1, 'a3', 'b3', 'c2', NULL, 100),
(2, 2, 'a3', 'b3', 'c3', NULL, 100);

INSERT INTO S2(FK1, FK2, A, B, C, D, E) VALUES
(1, 1, 'a1', 'b1', 'c1', 7, 2),
(1, 2, 'a_', 'b3', 'c1', 5, 2),
(1, 3, 'a2', 'b1', 'c2', NULL, 2),
(2, 1, 'a3', 'b3', 'c2', NULL, 100),
(2, 2, 'a3', 'b3', 'c3', NULL, 100);

SELECT *
FROM S s1 RIGHT JOIN S s2 ON s1.FK1 = s2.E

SELECT DISTINCT *
FROM S s1 INNER JOIN S s2 ON s1.FK1 = s2.E

SELECT FK2, FK1, COUNT(DISTINCT B)
FROM S
GROUP BY FK2, FK1
HAVING FK1 = 0

SELECT FK2, FK1, COUNT(C)
FROM S
GROUP BY FK2, FK1
HAVING MAX(E) < 0

select * from S

select A , COUNT(DISTINCT E)
FROM S

CREATE TABLE YourTableName (
    RID INT PRIMARY KEY,
    A INT,
    B INT,
    C INT,
    D INT,
    E INT,
    F INT
);

DROP table YourTableName
INSERT INTO YourTableName (RID, A, B, C, D, E, F) VALUES
(1, 100, 200, 5, 200, 20, 11),
(2, 101, 50, 11, 200, 5, 12),
(3, 100, 100, 7, 200, 5, 13),
(4, 200, 200, 6, 200, 20, 14),
(5, 200, 100, 2, 200, 5, 9),
(6, 300, 50, 11, 200, 5, 10);

SELECT r1.RID, r1.A + r2.A C2, r1.A * r2.A C3
FROM YourTableName r1 LEFT JOIN YourTableName r2 ON r1.RID = r2.RID
WHERE r1.A > ANY (SELECT B
FROM YourTableName
WHERE C < 10)


SELECT S.*
FROM (SELECT * FROM YourTableName WHERE F<13) S  INNER JOIN YourTableName ON S.D=YourTableName.D


SELECT YourTableName.*,t.*
FROM
(SELECT r1.RID, r2.A, r3.B
FROM YourTableName r1 INNER JOIN YourTableName r2 ON r1.A = r2.B
INNER JOIN YourTableName r3 ON r2.B > r3.D
WHERE r1.F > 10) t
RIGHT JOIN YourTableName ON t.RID = YourTableName.RID

DROP TABLE S
-- Create table S
CREATE TABLE S (
    FK1 INT,
    FK2 INT,
    A VARCHAR(50),
    B VARCHAR(50),
    C VARCHAR(50),
    D INT,
    E INT,
    PRIMARY KEY (FK1, FK2)
);

-- Insert data into S
INSERT INTO S (FK1, FK2, A, B, C, D, E) VALUES
(1, 1, 'a1', 'b1', 'c1', 7, 2),
(1, 2, 'a_', 'b3', 'c1', 5, 2),
(1, 3, 'a2', 'b1', 'c2', NULL, 2),
(2, 1, 'a3', 'b3', 'c2', NULL, 100),
(2, 2, 'a3', 'b3', 'c3', NULL, 100);


SELECT FK1, FK2, COUNT(DISTINCT B)
FROM S
GROUP BY FK2, FK1


-- Table for instrument categories
CREATE TABLE Category (
    category_id INT PRIMARY KEY,
    Categoryname VARCHAR(50),
    Categorydescription VARCHAR(50)
);

-- Table for instrument subcategories
CREATE TABLE Subcategory (
    subcategory_id INT PRIMARY KEY,
    SubcategoryName VARCHAR(50),
    category_id INT FOREIGN KEY REFERENCES Category(category_id)
);

-- Table for instruments
CREATE TABLE Instrument (
    serial_number INT PRIMARY KEY,
    date_manufacture DATE,
    color VARCHAR(20),
    price INT,
	subcategory_id INT FOREIGN KEY REFERENCES Subcategory(subcategory_id)
);

-- Table for customers
CREATE TABLE Customer (
    customer_id INT PRIMARY KEY,
    Customername VARCHAR(100) ,
    score INT,
    Customertype VARCHAR(50)
);

-- Table for orders
CREATE TABLE Orders (
    order_id INT PRIMARY KEY,
    order_date DATE,
    honor_date DATE,
    placed_online_or_not VARCHAR(50),
    customer_id INT FOREIGN KEY REFERENCES Customer(customer_id)
);

-- Table for order details
CREATE TABLE OrderDetail (
	OrderDetailID INT PRIMARY KEY,
    quantity INT,
    order_id INT FOREIGN KEY REFERENCES Orders(order_id),
    instrumentId INT FOREIGN KEY REFERENCES Instrument(serial_number)
);
-- Insert data into OrderDetail
INSERT INTO OrderDetail (OrderDetailID, quantity, order_id, instrumentId) VALUES
(1, 5, 101, 1001),   -- Red Violin, 5 quantity, Order ID: 101
(2, 2, 101, 1002),   -- Black Piano, 2 quantity, Order ID: 101
(3, 3, 102, 1002),   -- White Piano, 3 quantity, Order ID: 102
(4, 4, 103, 1003),   -- Blue Drums, 4 quantity, Order ID: 103
(5, 2, 104, 1001),   -- Red Violin, 2 quantity, Order ID: 104 (added for orchestra)
(6, 3, 104, 1001),   -- White Violin, 3 quantity, Order ID: 104 (added for orchestra)
(7, 4, 104, 1002),   -- Black Piano, 4 quantity, Order ID: 104 (added for orchestra)
(8, 1, 105, 1001),   -- Blue Violin, 1 quantity, Order ID: 105 (added for orchestra)
(9, 2, 105, 1001),   -- White Violin, 2 quantity, Order ID: 105 (added for orchestra)
(10, 3, 106, 1001),  -- Red Violin, 3 quantity, Order ID: 106 (added for orchestra)
(11, 1, 106, 1002),  -- Black Piano, 1 quantity, Order ID: 106 (added for orchestra)
(12, 2, 106, 1002);  -- Blue Piano, 2 quantity, Order ID: 106 (added for orchestra)



-- Insert data into Category
INSERT INTO Category (category_id, Categoryname, Categorydescription) VALUES
(1, 'String', 'String instruments category'),
(2, 'Percussion', 'Percussion instruments category'),
(3, 'Woodwind', 'Woodwind instruments category');

-- Insert data into Subcategory
INSERT INTO Subcategory (subcategory_id, SubcategoryName, category_id) VALUES
(1, 'Violin', 1),
(2, 'Piano', 1),
(3, 'Drums', 2),
(4, 'Flute', 3);

-- Insert data into Instrument
INSERT INTO Instrument (serial_number, date_manufacture, color, price, subcategory_id) VALUES
(1001, '2022-01-01', 'Red', 500, 1),
(1002, '2022-02-01', 'Black', 1000, 2),
(1003, '2022-03-01', 'White', 800, 2),
(1004, '2022-04-01', 'Blue', 700, 3);

-- Insert data into Customer
INSERT INTO Customer (customer_id, Customername, score, Customertype) VALUES
(1, 'Music Academy', 80, 'Academy'),
(2, 'City Orchestra', 90, 'Orchestra'),
(3, 'Individual Customer', 70, 'Individual');

-- Insert data into Orders
INSERT INTO Orders (order_id, order_date, honor_date, placed_online_or_not, customer_id) VALUES
(101, '2022-05-01', '2022-06-01', 'Online', 1),
(102, '2022-06-01', NULL, 'Phone', 2),
(103, '2022-07-01', NULL, 'Online', 3);

-- Insert data into OrderDetail
INSERT INTO OrderDetail (OrderDetailID, color, quantity, order_id, subcategory_id) VALUES
(1, 'Red', 5, 101, 1),
(2, 'Black', 2, 101, 2),
(3, 'White', 3, 102, 2),
(4, 'Blue', 4, 103, 3);

-- Insert additional data into Orders for orchestra
INSERT INTO Orders (order_id, order_date, honor_date, placed_online_or_not, customer_id) VALUES
(104, '2022-08-01', NULL, 'Online', 2),
(105, '2022-09-01', NULL, 'Phone', 2),
(106, '2022-10-01', NULL, 'Online', 2);

-- Insert additional data into OrderDetail for orchestra (order_id = 104, 105, 106)
INSERT INTO OrderDetail (OrderDetailID, color, quantity, order_id, subcategory_id) VALUES
(5, 'Red', 2, 104, 1),
(6, 'White', 3, 104, 1),
(7, 'Black', 4, 104, 2),
(8, 'Blue', 1, 105, 1),
(9, 'White', 2, 105, 1),
(10, 'Red', 3, 106, 1),
(11, 'Black', 1, 106, 2),
(12, 'Blue', 2, 106, 2);

-- Insert more data into Customer for orchestra
INSERT INTO Customer (customer_id, Customername, score, Customertype) VALUES
(4, 'City Orchestra 2', 85, 'Orchestra'),
(5, 'Symphony Orchestra', 88, 'Orchestra');

-- Insert more data into Orders for orchestra
INSERT INTO Orders (order_id, order_date, honor_date, placed_online_or_not, customer_id) VALUES
(107, '2022-11-01', NULL, 'Online', 4),
(108, '2022-12-01', NULL, 'Phone', 5),
(109, '2023-01-01', NULL, 'Online', 4);

-- Insert more data into OrderDetail for orchestra (order_id = 107, 108, 109)
INSERT INTO OrderDetail (OrderDetailID, quantity, order_id, instrumentId) VALUES
(13, 3, 107, 1001),   -- Red Violin, 3 quantity, Order ID: 107 (added for orchestra)
(14, 4, 107, 1002),   -- Black Piano, 4 quantity, Order ID: 107 (added for orchestra)
(15, 2, 108, 1001),   -- White Violin, 2 quantity, Order ID: 108 (added for orchestra)
(16, 3, 108, 1002),   -- Blue Piano, 3 quantity, Order ID: 108 (added for orchestra)
(17, 5, 109, 1001),   -- Red Violin, 5 quantity, Order ID: 109 (added for orchestra)
(18, 2, 109, 1002),   -- Black Piano, 2 quantity, Order ID: 109 (added for orchestra)
(19, 3, 109, 1001);   -- White Violin, 3 quantity, Order ID: 109 (added for orchestra)


SELECT C.customer_id,SUM(OD.quantity) AS TotalNumInstruments
FROM Customer C INNER JOIN Orders O ON C.customer_id=O.customer_id
				INNER JOIN OrderDetail OD ON O.order_id=OD.order_id
				INNER JOIN Instrument I ON OD.instrumentId=I.serial_number
				INNER JOIN Subcategory S ON S.subcategory_id=I.subcategory_id
WHERE C.Customertype='Orchestra' AND S.SubcategoryName='violin'
GROUP BY C.customer_id
HAVING COUNT(DISTINCT O.order_id) >=3 

-- Select all rows and columns from the Category table
SELECT * FROM Category;

-- Select all rows and columns from the Subcategory table
SELECT * FROM Subcategory;

-- Select all rows and columns from the Instrument table
SELECT * FROM Instrument;

-- Select all rows and columns from the Customer table
SELECT * FROM Customer;

-- Select all rows and columns from the Orders table
SELECT * FROM Orders;

-- Select all rows and columns from the OrderDetail table
SELECT quantity,OrderDetailID FROM OrderDetail GROUP BY quantity


SELECT SC.SubcategoryName,I.serial_number, I.price
FROM Instrument I INNER JOIN Subcategory SC ON I.subcategory_id=SC.subcategory_id
				  INNER JOIN Category C ON C.category_id=SC.category_id
WHERE I.price < 2000 AND C.Categoryname = 'string'





