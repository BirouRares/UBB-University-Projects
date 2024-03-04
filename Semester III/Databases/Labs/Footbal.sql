CREATE DATABASE Cup
USE Cup

CREATE TABLE  Cities(
	CityId INT PRIMARY KEY,
	CityName VARCHAR(50) UNIQUE
);

CREATE TABLE Stadiums (
	StadiumId INT PRIMARY KEY,
	StadiumName VARCHAR(50),
	CityId INT FOREIGN KEY REFERENCES Cities(CityId)
);

CREATE TABLE Teams (
	TeamId INT PRIMARY KEY,
	Country VARCHAR(50) UNIQUE
);

CREATE TABLE Players (
	PlayerId INT PRIMARY KEY,
	PlayerName VARCHAR(50),
	DateOfBirth DATE,
	Nationality VARCHAR(50),
	Position VARCHAR(50),
	Captain VARCHAR(50), --Yes or No
	TeamId INT FOREIGN KEY REFERENCES Teams(TeamId)
);

CREATE TABLE Coaches (
	CoachID INT PRIMARY KEY,
	CoachName VARCHAR(50),
	CoachNationality VARCHAR(50),
	TeamId INT FOREIGN KEY REFERENCES Teams(TeamId)
);

CREATE TABLE Games (
	GameId INT PRIMARY KEY,
	GameDate DATE,
	Team1Id INT FOREIGN KEY REFERENCES Teams(TeamId),
	Team2Id INT FOREIGN KEY REFERENCES Teams(TeamId),
	StadiumId INT FOREIGN KEY REFERENCES Stadiums(StadiumId),
	Score1 INT,
	Score2 INT,
	Winner VARCHAR(50),
	Overtime VARCHAR(50) --Yes or No
);

Drop table Games

-- Populate Cities table
INSERT INTO Cities (CityId, CityName)
VALUES
    (1, 'New York'),
    (2, 'London'),
    (3, 'Paris');

-- Populate Stadiums table
INSERT INTO Stadiums (StadiumId, StadiumName, CityId)
VALUES
    (101, 'Yankee Stadium', 1),
    (102, 'Wembley Stadium', 2),
    (103, 'Parc des Princes', 3);

-- Populate Teams table
INSERT INTO Teams (TeamId, Country)
VALUES
    (201, 'USA'),
    (202, 'England'),
    (203, 'France');

-- Populate Players table
INSERT INTO Players (PlayerId, PlayerName, DateOfBirth, Nationality, Position, Captain, TeamId)
VALUES
    (301, 'John Smith', '1990-05-15', 'USA', 'Forward', 'Yes', 201),
    (302, 'David Johnson', '1985-08-22', 'England', 'Midfielder', 'No', 202),
    (303, 'Claire Dubois', '1995-12-10', 'France', 'Defender', 'Yes', 203);

-- Populate Coaches table
INSERT INTO Coaches (CoachID, CoachName, CoachNationality, TeamId)
VALUES
    (401, 'Michael Brown', 'USA', 201),
    (402, 'Emma White', 'England', 202),
    (403, 'Pierre Martin', 'France', 203);

-- Populate Games table
INSERT INTO Games (GameId, GameDate, Team1Id, Team2Id, StadiumId, Score1,Score2, Winner, Overtime)
VALUES
    (501, '2024-01-09', 201, 202, 101, 2,1, 'USA', 'No'),
    (502, '2024-01-10', 202, 203, 102, 3,3, 'Draw', 'Yes'),
    (503, '2024-01-11', 201, 203, 103, 1,0, 'France', 'No');


--2

GO
CREATE OR ALTER PROC addGame(@Id INT, @GameDate DATE,@Team1Id INT,@Team2Id INT,@StadiumId INT,@Score1 INT,@Score2 INT,@Winner VARCHAR(50), @OverTime VARCHAR(50)) AS
BEGIN
	DECLARE @Idd INT = (  SELECT G.GameId
						FROM Games G
						WHERE G.GameDate=@GameDate AND G.Team1Id=@Team1Id AND G.Team2Id=@Team2Id)
	
	IF @Idd IS NOT NULL
	BEGIN
		UPDATE GAMES
		SET Score1=@Score1,
			Score2=@Score2,
			Winner=@Winner,
			Overtime= @OverTime
		WHERE GameId=@Idd
	END

	ELSE
	BEGIN
		INSERT INTO Games (GameId, GameDate, Team1Id, Team2Id, StadiumId, Score1,Score2, Winner, Overtime)
        VALUES (@Id, @GameDate, @Team1Id, @Team2Id, @StadiumId, @Score1,@Score2, @Winner, @OverTime);
	END
END
GO
-- Execute the stored procedure
EXEC addGame 504,'2024-01-12',201,203,103,2,0,'USA','No';


Select * from Games

--3
GO
CREATE OR ALTER VIEW namesOfStadium AS
	SELECT S.StadiumName
	FROM Stadiums S
	WHERE StadiumId IN 
		(SELECT G.StadiumId
		 FROM Games G
		 WHERE G.Overtime='Yes')
GO

SELECT * FROM namesOfStadium


--4

-- Create or alter the function
-- Create or alter the function
CREATE OR ALTER FUNCTION numberOfTeams(@StadiumId INT, @Dif INT)
RETURNS INT
AS
BEGIN
    DECLARE @NumberOfTeams INT;

    -- Count the number of teams that won all games played on the specified stadium with a score difference greater than @Dif
    SELECT @NumberOfTeams = COUNT(DISTINCT TeamId)
    FROM (
        SELECT Team1Id AS TeamId
        FROM Games
        WHERE StadiumId = @StadiumId
              AND Winner IS NOT NULL
              AND (Score1 > Score2 AND Score1 - Score2 > @Dif
                    OR Score2 > Score1 AND Score2 - Score1 > @Dif)
        UNION
        SELECT Team2Id AS TeamId
        FROM Games
        WHERE StadiumId = @StadiumId
              AND Winner IS NOT NULL
              AND (Score1 > Score2 AND Score1 - Score2 > @Dif
                    OR Score2 > Score1 AND Score2 - Score1 > @Dif)
    ) AS WinningTeams;

    RETURN @NumberOfTeams;
END;

DECLARE @Result INT;
SET @Result = dbo.numberOfTeams(101, 1);
PRINT @Result;  -- Output the result
