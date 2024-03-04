CREATE DATABASE ZOOS
USE ZOOS

CREATE TABLE Zoos(
	ZooId INT PRIMARY KEY,
	Administrator VARCHAR(50),
	ZooName VARCHAR(50)
);

CREATE TABLE Animals(
	AnimalId INT PRIMARY KEY,
	AnimalName VARCHAR(50),
	DateOfBirth DATE,
	ZooID INT FOREIGN KEY REFERENCES Zoos(ZooId)
);

CREATE TABLE Foods(
	FoodId INT PRIMARY KEY,
	FoodName VARCHAR(50)
);

CREATE TABLE AnimalFoods(
	AnimalId INT FOREIGN KEY REFERENCES Animals(AnimalId),
	FoodId INT FOREIGN KEY REFERENCES Foods(FoodId),
	PRIMARY KEY (AnimalId, FoodId),
	DailyQuota INT
);

CREATE TABLE Visitors(
	VisitorId INT PRIMARY KEY,
	VisitorName VARCHAR(50),
	Age INT
);

CREATE TABLE Visits(
	VisitId INT PRIMARY KEY,
	ZooId INT FOREIGN KEY REFERENCES Zoos(ZooId),
	VisitorsId INT FOREIGN KEY REFERENCES Visitors(VisitorId),
	VisitDay DATE,
	Price MONEY
);

-- Inserting data into Zoos table
INSERT INTO Zoos (ZooId, Administrator, ZooName) VALUES
(1, 'John Doe', 'City Zoo'),
(2, 'Jane Smith', 'Wildlife Sanctuary'),
(3, 'Bob Johnson', 'Nature Park'),
(4, 'Alice Williams', 'Safari Adventure'),
(5, 'Charlie Brown', 'Oceanarium');

-- Inserting data into Animals table
INSERT INTO Animals (AnimalId, AnimalName, DateOfBirth, ZooId) VALUES
(1, 'Lion', '2020-05-15', 1),
(2, 'Elephant', '2018-12-10', 2),
(3, 'Giraffe', '2019-02-20', 1),
(4, 'Penguin', '2021-07-03', 5),
(5, 'Tiger', '2017-09-25', 3);

-- Inserting data into Foods table
INSERT INTO Foods (FoodId, FoodName) VALUES
(1, 'Meat'),
(2, 'Hay'),
(3, 'Fish'),
(4, 'Bamboo'),
(5, 'Insects');

-- Inserting data into AnimalFoods table
INSERT INTO AnimalFoods (AnimalId, FoodId, DailyQuota) VALUES
(1, 1, 5),
(2, 2, 10),
(3, 4, 8),
(4, 3, 3),
(5, 1, 6);

-- Inserting data into Visitors table
INSERT INTO Visitors (VisitorId, VisitorName, Age) VALUES
(1, 'Mike Johnson', 25),
(2, 'Emily Davis', 30),
(3, 'Alex Turner', 22),
(4, 'Sophie White', 40),
(5, 'Mark Miller', 28);

-- Inserting data into Visits table
INSERT INTO Visits (VisitId, ZooId, VisitorsId, VisitDay, Price) VALUES
(1, 1, 1, '2023-01-10', 15.50),
(2, 2, 2, '2023-02-05', 20.00),
(3, 3, 3, '2023-03-15', 12.75),
(4, 4, 4, '2023-04-20', 18.00),
(5, 5, 5, '2023-05-25', 25.50);


--b

GO
CREATE OR ALTER PROC deleteFooDQuotas(@Name VARCHAR(50)) AS
BEGIN
	DECLARE @Id INT = (SELECT A.AnimalId FROM Animals A WHERE @Name = A.AnimalName)
	DELETE FROM AnimalFoods
	WHERE AnimalFoods.AnimalId=@Id
END
GO

EXEC deleteFooDQuotas 'Tiger'
SELECT * FROM AnimalFoods


--c

GO
CREATE OR ALTER VIEW zoosVisits AS
	SELECT z.ZooId, COUNT(v.VisitId) AS NumVisits
	FROM Zoos z
	LEFT JOIN Visits v ON z.ZooId = v.ZooId
	GROUP BY z.ZooId
	ORDER BY NumVisits ASC;
GO

GO
CREATE OR ALTER VIEW zoosVisitsView AS
	SELECT Z.ZooId
	FROM Zoos Z
	WHERE Z.ZooId IN
		(SELECT V.ZooId
		FROM Visits V
		GROUP BY V.ZooId
		HAVING COUNT(*) = (SELECT MIN(VisitCount)
				FROM (
				SELECT COUNT(*) AS VisitCount
				FROM Visits
				GROUP BY ZooId
			 )AS MinVisitCounts)
		)
GO
select * from zoosVisitsView



--4

/*GO
CREATE OR ALTER FUNCTION showVisitorId (@N INT) RETURNS TABLE AS RETURN
	(SELECT V.VisitorId 
	 FROM Visitors V
	 WHERE V.ZooId IN
		(SELECT A.ZooId
		 FROM Animals A
		 GROUP BY A.ZooID
		 HAVING COUNT(*)>=@N
		)
	)
GO

SELECT * FROM showVisitorId (1)*/

GO
CREATE OR ALTER FUNCTION showVisitorId_f (@N int) RETURNS TABLE AS RETURN
	(SELECT V.VisitorsId
	FROM Visits V
	WHERE V.ZooId IN
		(SELECT A.ZooId
		FROM Animals A
		GROUP BY A.ZooId
		HAVING COUNT(*) >= @N)
	)
GO

select * from showVisitorId_f(1)



