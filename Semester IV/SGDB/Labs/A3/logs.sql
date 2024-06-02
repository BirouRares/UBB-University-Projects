
CREATE TABLE LogChanges(
	currentTime DATETIME,
	info VARCHAR(100),
	newData VARCHAR(100)
)


CREATE OR ALTER PROCEDURE sp_log_changes
	@newData VARCHAR(100),
	@info VARCHAR(100)
AS
BEGIN
	INSERT INTO LogChanges (currentTime, newData, info) VALUES
	(GETDATE(), @newData, @info)
END
GO

select * from LogChanges