CREATE DATABASE Bank
USE Bank



--1


DROP TABLE Customers
DROP TABLE BankAccounts
DROP TABLE Cards
DROP TABLE ATMs
DROP TABLE Transactions

CREATE TABLE Customers(
	CustomerId INT PRIMARY KEY,
	CustomerName VARCHAR(50),
	DateOfBirth DATE
);

CREATE TABLE BankAccounts(
	AccountId INT PRIMARY KEY,
	IBAN VARCHAR(30),
	Balance INT,
	CustomerId INT FOREIGN KEY REFERENCES Customers(CustomerId)
);

CREATE TABLE Cards (
	CardId INT PRIMARY KEY,
	CardNumber VARCHAR(30),
	CVV VARCHAR(5),
	AccountId INT FOREIGN KEY REFERENCES BankAccounts(AccountId)
);

CREATE TABLE ATMs(
	ATMId INT PRIMARY KEY,
	ATMAddress VARCHAR(50)
);

CREATE TABLE Transactions(
	TransactionId INT PRIMARY KEY,
	Amount INT,
	TransactionDate DATE,
	ATMId INT FOREIGN KEY REFERENCES ATMs(ATMId),
	CardId INT FOREIGN KEY REFERENCES Cards(CardId)
);


-- Insert data into Customers table
INSERT INTO Customers (CustomerId, CustomerName, DateOfBirth)
VALUES
    (1, 'John Doe', '1990-05-15'),
    (2, 'Jane Smith', '1985-08-22'),
    (3, 'Bob Johnson', '1978-12-10');

-- Insert data into BankAccounts table
INSERT INTO BankAccounts (AccountId, IBAN, Balance, CustomerId)
VALUES
    (101, 'US12345678901234567890', 5000, 1),
    (102, 'US98765432109876543210', 7500, 2),
    (103, 'US55555555555555555555', 3000, 3);

-- Insert data into Cards table
INSERT INTO Cards (CardId, CardNumber, CVV, AccountId)
VALUES
    (201, '1234567890123456', '123', 101),
    (202, '9876543210987654', '456', 102),
    (203, '5555555555555555', '789', 103);

-- Insert data into ATMs table
INSERT INTO ATMs (ATMId, ATMAddress)
VALUES
    (301, '123 Main St ATM'),
    (302, '456 Oak St ATM'),
    (303, '789 Elm St ATM');

-- Insert data into Transactions table
INSERT INTO Transactions (TransactionId, Amount, TransactionDate, ATMId, CardId)
VALUES
	(404, 200, '2024-01-05', 302, 201),
	(405, 200, '2024-01-01', 303, 201),
    (401, 200, '2024-01-09', 301, 201),
    (402, 300, '2024-01-10', 302, 202),
    (403, 150, '2024-01-11', 303, 203);


--2

GO
CREATE OR ALTER PROC deteleTransactions (@Name VARCHAR(50)) AS
BEGIN
	DECLARE @Id INT = (SELECT C.CardID FROM Cards C WHERE @Name = C.CardNumber )
	DELETE FROM Transactions
	WHERE  Transactions.CardId=@Id
END
GO

EXEC deteleTransactions '5555555555555555'
SELECT * FROM Transactions


--3

GO 
CREATE OR ALTER VIEW cardShowing AS
	SELECT C.CardNumber
	FROM Cards C
	WHERE C.CardId IN
		(SELECT T.CardID
		 FROM Transactions T
		 GROUP BY CardId
		 HAVING COUNT(DISTINCT T.ATMId)= (SELECT COUNT(*) FROM ATMs) 
		)
GO

SELECT * FROM cardShowing



--d

GO
CREATE OR ALTER FUNCTION listCards () RETURNS TABLE AS RETURN
	(SELECT C.Cardnumber, C.CVV
	 FROM Cards C
	 WHERE C.CardId IN
		(SELECT T.CardID
		FROM Transactions T
		GROUP BY T.CardId
		HAVING SUM(T.Amount)>200
		 
		)
		
	)
GO

SELECT * FROM listCards()

SELECT * FROM Customers
SELECT * FROM BankAccounts
SELECT * FROM Cards
SELECT * FROM ATMs
SELECT * FROM Transactions