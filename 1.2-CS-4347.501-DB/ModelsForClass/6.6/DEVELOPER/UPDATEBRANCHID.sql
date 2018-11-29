--------------------------------------------------------
--  DDL for Trigger UPDATEBRANCHID
--------------------------------------------------------

  CREATE OR REPLACE NONEDITIONABLE TRIGGER "CS4347F18"."UPDATEBRANCHID" 
AFTER UPDATE OF BRANCHID ON LIBRARY_BRANCH FOR EACH ROW
    BEGIN
    -- update BOOK_AUTHORS table with new foreign key
    -- the new. and old. are part of the trigger variables under the hood
    -- you don't have to define new and old, you can use them in your trigger though
    UPDATE BOOK_COPIES
      SET branchid = :new.branchid
     WHERE branchid = :old.branchid;
    -- same for other table referencing BRANCHID
    UPDATE BOOK_LOANS
      SET branchid = :new.branchid
     WHERE branchid = :old.branchid;
END;
/
ALTER TRIGGER "CS4347F18"."UPDATEBRANCHID" ENABLE;
