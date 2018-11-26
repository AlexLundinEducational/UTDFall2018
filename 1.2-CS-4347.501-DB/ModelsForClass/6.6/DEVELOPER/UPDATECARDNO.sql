--------------------------------------------------------
--  DDL for Trigger UPDATECARDNO
--------------------------------------------------------

  CREATE OR REPLACE NONEDITIONABLE TRIGGER "CS4347F18"."UPDATECARDNO" 
AFTER UPDATE OF CARDNO ON BORROWER FOR EACH ROW
    BEGIN
    -- update BOOK_LOANS table with new foreign key
    -- the new. and old. are part of the trigger variables under the hood
    -- you don't have to define new and old, you can use them in your trigger though
    UPDATE BOOK_LOANS
      SET cardno = :new.cardno
     WHERE cardno = :old.cardno;
END;
/
ALTER TRIGGER "CS4347F18"."UPDATECARDNO" ENABLE;
