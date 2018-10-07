--------------------------------------------------------
--  File created - Sunday-October-07-2018   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table AIRPORT
--------------------------------------------------------

  CREATE TABLE "CS4347F18"."AIRPORT" 
   (	"AIRPORT_CODE" NUMBER(*,0), 
	"NAME" VARCHAR2(40 BYTE), 
	"CITY" VARCHAR2(40 BYTE), 
	"STATE" VARCHAR2(2 BYTE), 
	"T1" TIMESTAMP (6)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
REM INSERTING into CS4347F18.AIRPORT
SET DEFINE OFF;
--------------------------------------------------------
--  DDL for Index SYS_C009896
--------------------------------------------------------

  CREATE UNIQUE INDEX "CS4347F18"."SYS_C009896" ON "CS4347F18"."AIRPORT" ("AIRPORT_CODE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  Constraints for Table AIRPORT
--------------------------------------------------------

  ALTER TABLE "CS4347F18"."AIRPORT" MODIFY ("AIRPORT_CODE" NOT NULL ENABLE);
  ALTER TABLE "CS4347F18"."AIRPORT" MODIFY ("NAME" NOT NULL ENABLE);
  ALTER TABLE "CS4347F18"."AIRPORT" MODIFY ("CITY" NOT NULL ENABLE);
  ALTER TABLE "CS4347F18"."AIRPORT" MODIFY ("STATE" NOT NULL ENABLE);
  ALTER TABLE "CS4347F18"."AIRPORT" ADD PRIMARY KEY ("AIRPORT_CODE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
