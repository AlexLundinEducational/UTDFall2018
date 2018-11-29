--- these lines deletes existing tables
DROP TABLE AIRPORT;
DROP TABLE FLIGHT;
DROP TABLE FLIGHT_LEG;
DROP TABLE LEG_INSTANCE;
DROP TABLE FARE;
DROP TABLE AIRPLANE_TYPE;
DROP TABLE CAN_LAND;
DROP TABLE AIRPLANE;
DROP TABLE SEAT_RESERVATION;

--- these lines clear data in tables
TRUNCATE TABLE AIRPORT;
TRUNCATE TABLE FLIGHT;
TRUNCATE TABLE FLIGHT_LEG;
TRUNCATE TABLE LEG_INSTANCE;
TRUNCATE TABLE FARE;
TRUNCATE TABLE AIRPLANE_TYPE;
TRUNCATE TABLE CAN_LAND;
TRUNCATE TABLE AIRPLANE;
TRUNCATE TABLE SEAT_RESERVATION;

CREATE TABLE AIRPORT
  (Airport_code INT     	 NOT NULL,
   Name      VARCHAR(40)     NOT NULL,
   City      VARCHAR(40)     NOT NULL,
   State     VARCHAR(2)      NOT NULL,
   PRIMARY KEY(Airport_code));
   
CREATE TABLE FLIGHT
  (Flight_number 	INT     	 	NOT NULL,
   Airline      	VARCHAR(40)     NOT NULL,
   Weekdays      	VARCHAR(40)     NOT NULL,
   PRIMARY KEY(Flight_number));

CREATE TABLE FLIGHT_LEG
  (Flight_number 				INT     	 		NOT NULL,
   Leg_number      				INT     			NOT NULL,
   Departure_airport_code      	INT     			NOT NULL,
   Scheduled_departure_time     TIMESTAMP(6)     	NOT NULL,
   Arrival_airport_code      	INT     			NOT NULL,
   Scheduled_arrival_time     	TIMESTAMP(6)     	NOT NULL,
   PRIMARY KEY(Flight_number, Leg_number),
   FOREIGN KEY(Flight_number) REFERENCES FLIGHT(Flight_number),
   UNIQUE(Leg_number)); 
   
   
CREATE TABLE LEG_INSTANCE
  (Flight_number 				INT     	 	NOT NULL,
   Leg_number      				INT     		NOT NULL,
   Date1						DATE			NOT NULL,
   Number_of_avaiable_seats     INT     		NOT NULL,
   Airplane_id      			INT     		NOT NULL,
   Departure_airport_code      	INT     		NOT NULL,
   Departure_time     			TIMESTAMP(6)    NOT NULL,
   Arrival_airport_code      	INT     		NOT NULL,
   Arrival_time     			TIMESTAMP(6)    NOT NULL,
   PRIMARY KEY(Flight_number, Leg_number, Date1),
   FOREIGN KEY(Flight_number) REFERENCES FLIGHT(Flight_number),
   FOREIGN KEY(Leg_number) REFERENCES FLIGHT_LEG(Leg_number)); 
   
   
CREATE TABLE FARE
  (Flight_number 	INT     	 	NOT NULL,
   Fare_code 		INT     	 	NOT NULL,
   Amount     		DECIMAL(10,2)	NOT NULL,
   Restrictions     VARCHAR(40)     NOT NULL,
   PRIMARY KEY(Flight_number,Fare_code),
   FOREIGN KEY(Flight_number) REFERENCES FLIGHT(Flight_number),
   UNIQUE(Fare_code)); 
   
CREATE TABLE AIRPLANE_TYPE
  (Airplane_type_name   VARCHAR(40)     NOT NULL,
   Max_seats 			INT     	 	NOT NULL,
   Company     			VARCHAR(40)     NOT NULL,
   PRIMARY KEY(Airplane_type_name));    
   
CREATE TABLE CAN_LAND
  (Airport_code 		INT     	 NOT NULL,
   Airplane_type_name   VARCHAR(40)  NOT NULL,
   PRIMARY KEY(Airport_code,Airplane_type_name),
   FOREIGN KEY(Airport_code) REFERENCES AIRPORT(Airport_code),
   FOREIGN KEY(Airplane_type_name) REFERENCES AIRPLANE_TYPE(Airplane_type_name));

CREATE TABLE AIRPLANE
  (Airplane_id 				INT     	 	NOT NULL,
   Total_number_of_seats 	INT     	 	NOT NULL,
   Airplane_type  			VARCHAR(40)     NOT NULL,
   PRIMARY KEY(Airplane_id)); 
   
CREATE TABLE SEAT_RESERVATION
  (Flight_number 		INT     	 	NOT NULL,
   Leg_number      		INT     		NOT NULL,
   Date1				DATE			NOT NULL,
   Seat_number      	INT     		NOT NULL,
   Customer_name     	VARCHAR(40)     NOT NULL,
   Customer_phone     	VARCHAR(40)     NOT NULL,
   PRIMARY KEY(Flight_number,Leg_number, Date1, Seat_number),
   FOREIGN KEY(Flight_number) REFERENCES FLIGHT(Flight_number),
   FOREIGN KEY(Leg_number) REFERENCES FLIGHT_LEG(Leg_number),
   UNIQUE(Seat_number));   
   