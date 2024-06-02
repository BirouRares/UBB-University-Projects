--WAITFOR DELAY
--Putem folosi la teme sa sincronizam tranzactiile sa ruleze cum vrem noi

--BEGIN TRAN
--Incepe o tranzactie

--COMMIT TRAN
--Comite o tranzatie

--ROLLBACK TRAN
--Abandoneaza toate tranzactiile

--select @@TRANCOUNT 
--Returneaza numarul de tranzactii active
--Doar cand se da commit la ultima tranzactie, adica atunci cand trancount e 1 atunci se comit toate schimbarile, altfel niciuna
--Incepatorii uita des sa faca commit atunci trebuie folosit des select @@TRANCOUNT


DROP TABLE EmployeeAssignments
DROP TABLE Employees
DROP TABLE EmployeeRoles

CREATE TABLE Employees
(
	EmployeeID INT PRIMARY KEY,
	EmployeeName VARCHAR(50),
	EmployeePhone VARCHAR(10) 
);

CREATE TABLE EmployeeRoles
(
	RoleID INT PRIMARY KEY,
	RoleName VARCHAR(50)
);

CREATE TABLE EmployeeAssignments
(
	EmployeeID INT references Employees(EmployeeID),
	RoleID INT references EmployeeRoles(RoleID),
	PRIMARY KEY (EmployeeID,RoleID)
);



--start 

GO
CREATE OR ALTER PROCEDURE addRowEmployees(@name VARCHAR(50), @phone VARCHAR(10) ) AS
	DECLARE @id INT
		SET @id=0
		SELECT TOP 1 @id=EmployeeID+1 FROM Employees ORDER BY EmployeeID DESC
		IF (@name is null)
		BEGIN
			RAISERROR('Name must not be null',24,1);
		END
		IF (@phone is null)
		BEGIN
			RAISERROR('Phone must not be null',24,1);
		END

		INSERT INTO Employees(EmployeeID,EmployeeName,EmployeePhone) VALUES (@id,@name,@phone)
	EXEC sp_log_changes @name, 'Added row to Employees'
GO

GO
CREATE OR ALTER PROCEDURE addRowEmployeeRoles(@name VARCHAR(50)) AS
	DECLARE @id INT
		SET @id=0
		SELECT TOP 1 @id=RoleID+1 FROM EmployeeRoles ORDER BY RoleID DESC

		IF (@name is null)
		BEGIN
			RAISERROR('Name must not be null',24,1);
		END

		INSERT INTO EmployeeRoles(RoleID,RoleName) VALUES (@id,@name)
	EXEC sp_log_changes  @name, 'Added row to EmployeeRoles'
GO


GO 
CREATE OR ALTER PROCEDURE addRowEmployeeAssignments(@EName VARCHAR(50), @RName VARCHAR(50)) AS
	IF(@EName IS NULL)
	BEGIN
		RAISERROR('ERROR',24,1);
	END

	IF(@RName IS NULL)
	BEGIN
		RAISERROR('ERROR',24,1);
	END


	DECLARE @EID INT
	SET @EID = (SELECT EmployeeID FROM Employees WHERE EmployeeName=@EName)

	DECLARE @RID INT
	SET @RID = (SELECT RoleID FROM EmployeeRoles WHERE RoleName=@RName)

	IF(@EID IS NULL)
	BEGIN
		RAISERROR('ERROR',24,1);
	END
	IF(@RID IS NULL)
	BEGIN
		RAISERROR('ERROR',24,1);
	END

	INSERT INTO EmployeeAssignments(EmployeeID, RoleID) VALUES (@EID,@RID)

	DECLARE @newData VARCHAR(100)
	SET @newData =@EName+ ' ' +@RName
	EXEC sp_log_changes @newData, 'Connected Employees with EmployeeAssignments'
GO


GO
CREATE OR ALTER PROCEDURE	rollbackScenarioNoFail
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC addRowEmployees 'Mihai', '0123456789'
		EXEC addRowEmployeeRoles 'Manager'
		EXEC addRowEmployeeAssignments 'Mihai', 'Manager'
	END TRY

	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
	COMMIT TRAN
GO


GO
CREATE OR ALTER PROCEDURE rollbackScenarioFail
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC addRowEmployees 'Mihai', '0123456789'
		EXEC addRowEmployeeRoles 'Manager'
		EXEC addRowEmployeeAssignments 'Mihai', 'Liber'
	END TRY


	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
	COMMIT TRAN
GO


GO
CREATE OR ALTER PROCEDURE noRollbackScenarioManyToManyNoFail
AS
	DECLARE @ERRORS INT
	SET @ERRORS = 0


	BEGIN TRY
		EXEC addRowEmployees 'Ana', '0123456789'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH

	BEGIN TRY
		EXEC addRowEmployeeRoles 'Free'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH


	IF (@ERRORS = 0) BEGIN
		BEGIN TRY
			EXEC addRowEmployeeAssignments 'Ana', 'Free'
		END TRY
		BEGIN CATCH
		END CATCH
	END
GO


GO
CREATE OR ALTER PROCEDURE noRollbackScenarioManyToManyFail
AS
	DECLARE @ERRORS INT
	SET @ERRORS = 0


	BEGIN TRY
		EXEC addRowEmployees 'Eusebiu', '0123456789'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH

	BEGIN TRY
		EXEC addRowEmployeeRoles 'Sef'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH


	IF (@ERRORS = 0) BEGIN
		BEGIN TRY
			EXEC addRowEmployeeAssignments 'Eusebiu', 'liber'
		END TRY
		BEGIN CATCH
		END CATCH
	END
GO


EXEC rollbackScenarioNoFail
EXEC rollbackScenarioFail

EXEC noRollbackScenarioManyToManyNoFail
EXEC noRollbackScenarioManyToManyFail


DELETE FROM EmployeeAssignments
DELETE FROM EmployeeRoles
DELETE FROM Employees
DELETE FROM LogChanges
DELETE FROM LogLocks

SELECT * FROM Employees
SELECT * FROM EmployeeAssignments
SELECT * FROM EmployeeRoles
SELECT * FROM LogChanges
