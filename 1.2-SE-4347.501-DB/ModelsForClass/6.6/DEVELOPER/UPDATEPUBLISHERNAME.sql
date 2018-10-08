--------------------------------------------------------
--  DDL for Trigger UPDATEPUBLISHERNAME
--------------------------------------------------------

  CREATE OR REPLACE NONEDITIONABLE TRIGGER "CS4347F18"."UPDATEPUBLISHERNAME" 
 AFTER UPDATE OF NAME ON PUBLISHER FOR EACH ROW
    BEGIN
    -- update BOOK table with new foreign key
    -- the new. and old. are part of the trigger variables under the hood
    -- you don't have to define new and old, you can use them in your trigger though
    UPDATE BOOK
      SET publishername = :new.name
     WHERE publishername = :old.name;
END;
/
ALTER TRIGGER "CS4347F18"."UPDATEPUBLISHERNAME" ENABLE;
