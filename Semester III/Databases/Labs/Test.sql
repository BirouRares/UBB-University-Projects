CREATE DATABASE Test
USE Test


--1
Drop table Prescriptions

CREATE TABLE Prescriptions(
	PrescriptionId INT PRIMARY KEY,
	Diagnose VARCHAR(50),
	REye DECIMAL(4,2),
	LEye DECIMAL(4,2)
);
CREATE TABLE Manufacturers(
	ManufacturerId  INT PRIMARY KEY,
	CompanyName VARCHAR(50) UNIQUE, 
	Adress VARCHAR(50),
	Email VARCHAR(50)
);
CREATE TABLE Frames(
	FrameId INT PRIMARY KEY,
	FrameName VARCHAR(50),
	FrameDescription VARCHAR(50),
	FrameColor VARCHAR(50),
	FrameShape VARCHAR(50),
	FramePrice INT,
	ManufacturerId INT FOREIGN KEY REFERENCES  Manufacturers(ManufacturerId),

);
CREATE TABLE Lenses(
	LenseId INT PRIMARY KEY,
	LenseType VARCHAR(50),
	LensePrice INT,
	ManufacturerId INT FOREIGN KEY REFERENCES  Manufacturers(ManufacturerId),
);
CREATE TABLE Orders(
	OrderId INT PRIMARY KEY,
	LensesId INT FOREIGN KEY REFERENCES Lenses(LenseID),
	FrameId INT FOREIGN KEY REFERENCES Frames(FrameId),
	PrescriptionId INT FOREIGN KEY REFERENCES Prescriptions(PrescriptionId),
	DateOfOrder DATE
);


INSERT INTO Prescriptions (PrescriptionId, Diagnose, REye, LEye)
VALUES
    (1, 'M', -2.5, -1.75),
    (2, 'H', 1.25, 3.0),
    (3, 'A', -3.75, -2.0);

INSERT INTO Manufacturers (ManufacturerId, CompanyName, Adress, Email)
VALUES
    (1, 'LensCo', '123 ', 'i.com'),
    (2, 'Frah', 'akt', 'inh.com'),
    (3, 'Cleaion', 'ne St', 'in.com');


INSERT INTO Frames (FrameId, FrameName, FrameDescription, FrameColor, FrameShape, FramePrice, ManufacturerId)
VALUES
	(4, 'Cl', 'Sl', 'Black', 'square', 150.00, 2),
    (1, 'Ck', 'Sl', 'Black', 'Rectangle', 150.00, 2),
    (2, 'ue', 'Is', 'Blue', 'Oval', 120.00, 3),
    (3, 'se', 'Fy', 'Tortoise', 'Round', 180.00, 1);

INSERT INTO Lenses (LenseId, LenseType, LensePrice, ManufacturerId)
VALUES
    (1, 'Single', 50.00, 1),
    (2, 'Bi', 80.00, 2),
    (3, 'P', 120.00, 3);

INSERT INTO Orders (OrderId, LensesId, FrameId, PrescriptionId, DateOfOrder)
VALUES
    (1, 2, 3, 1, '2024-01-09'),
    (2, 1, 2, 2, '2024-01-10'),
    (3, 3, 1, 3, '2024-01-11');


Select * FROM Orders
Select * FROM Lenses
Select * FROM Manufacturers
Select * FROM Frames
Select * FROM Prescriptions


--3


CREATE OR ALTER VIEW SquareFrames AS
SELECT
    O.OrderId,
    O.DateOfOrder,
    (SELECT FrameName FROM Frames WHERE FrameId = O.FrameId) AS Frame,
    (SELECT LenseType FROM Lenses WHERE LenseId = O.LensesId) AS Lenses
FROM
    Orders O
WHERE
    EXISTS (SELECT FrameId FROM Frames WHERE FrameId = O.FrameId AND FrameShape = 'Oval')
    OR
    EXISTS (SELECT LensesId FROM Lenses WHERE LenseId = O.LensesId AND LenseType = 'Bi');


select * from SquareFrames


--2

GO
CREATE OR ALTER PROC updateLam (@ManId INT) AS
BEGIN
	DECLARE @ID INT = (SELECT  F.FrameId FROM Frames F WHERE F.ManufacturerId = @ManId)
	IF @ID IS NOT NULL
	BEGIN
		UPDATE Frames
		SET FramePrice=FramePrice+0.1*FramePrice
		WHERE FrameId=@ID
	END

	DECLARE @ID2 INT = (SELECT  L.LenseId FROM Lenses L WHERE L.ManufacturerId = @ManId)
	IF @ID2 IS NOT NULL
	BEGIN
		UPDATE Lenses
		SET LensePrice=LensePrice+0.1*LensePrice
		WHERE LenseId=@ID2
	END
END
GO

EXEC updateLam 1

Select * FROM Frames
Select * FROM Lenses
/*ManufacturerId  INT PRIMARY KEY,
	CompanyName VARCHAR(50) UNIQUE, 
	Adress VARCHAR(50),
	Email VARCHAR(50)
	
	
	FrameId INT PRIMARY KEY,
	FrameName VARCHAR(50),
	FrameDescription VARCHAR(50),
	FrameColor VARCHAR(50),
	FrameShape VARCHAR(50),
	FramePrice INT,
	ManufacturerId INT FOREIGN KEY REFERENCES  Manufacturers(ManufacturerId),
	
	LenseId INT PRIMARY KEY,
	LenseType VARCHAR(50),
	LensePrice INT,
	ManufacturerId INT FOREIGN KEY REFERENCES  Manufacturers(ManufacturerId),*/

	

