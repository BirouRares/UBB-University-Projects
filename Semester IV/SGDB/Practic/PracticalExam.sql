CREATE TABLE Neighborhood
(
	NID INT PRIMARY KEY,
	NName VARCHAR(50),
	NLocation VARCHAR(50) 
);

CREATE TABLE MainResident
(
	MID INT PRIMARY KEY,
	MName VARCHAR(50),
	Phone VARCHAR(50)
);

CREATE TABLE SmartHome
(
	SHID INT PRIMARY KEY,
	SName VARCHAR(50),
	SAddress VARCHAR(50),
	NID INT REFERENCES Neighborhood(NID),
	MID INT REFERENCES MainResident(MID)
);

CREATE TABLE Devices
(
	DID INT PRIMARY KEY,
	DName VARCHAR(50)
);

CREATE TABLE SmartHomeDevices
(
	SHDID INT PRIMARY KEY,
	SHID INT REFERENCES SmartHome(SHID),
	DID INT REFERENCES Devices(DID)
);



INSERT INTO Neighborhood (NID, NName, NLocation)
VALUES 
(1, 'Greenwood', 'Northside'),
(2, 'Sunnyvale', 'Eastside'),
(3, 'Hilltop', 'Westside');

INSERT INTO MainResident (MID, MName, Phone)
VALUES 
(1, 'John Doe', '123-456-7890'),
(2, 'Jane Smith', '234-567-8901'),
(3, 'Alice Johnson', '345-678-9012');

INSERT INTO SmartHome (SHID, SName, SAddress, NID, MID)
VALUES 
(1, 'Doe Smart Home', '123 Elm Street', 1, 1),
(2, 'Smith Residence', '456 Oak Avenue', 2, 2),
(3, 'Johnson Home', '789 Pine Road', 3, 3);

INSERT INTO Devices (DID, DName)
VALUES 
(1, 'Smart Thermostat'),
(2, 'Smart Light Bulb'),
(3, 'Smart Lock'),
(4, 'Smart Camera'),
(5, 'Smart Speaker');


DELETE FROM SmartHomeDevices




SELECT * FROM Neighborhood
SELECT * FROM SmartHome

SELECT * FROM MainResident
SELECT * FROM Devices
SELECT * FROM SmartHomeDevices