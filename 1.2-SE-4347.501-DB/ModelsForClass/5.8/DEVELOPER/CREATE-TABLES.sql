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
  (Flight_number 				INT     	 	NOT NULL,
   Leg_number      				INT     		NOT NULL,
   Departure_airport_code      	INT     		NOT NULL,
   Scheduled_departure_time     TIMESTAMP     	NOT NULL,
   Arival_airport_code      	INT     		NOT NULL,
   Scheduled_arival_time     	TIMESTAMP     	NOT NULL,
   PRIMARY KEY(Leg_number)); 