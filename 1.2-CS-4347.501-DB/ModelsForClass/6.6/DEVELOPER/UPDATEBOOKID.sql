--------------------------------------------------------
--  DDL for Trigger UPDATEBOOKID
--------------------------------------------------------

  CREATE OR REPLACE NONEDITIONABLE TRIGGER "CS4347F18"."UPDATEBOOKID" 
 AFTER UPDATE OF BOOKID ON BOOK FOR EACH ROW
    BEGIN
    -- update BOOK_AUTHORS table with new foreign key
    -- the new. and old. are part of the trigger variables under the hood
    -- you don't have to define new and old, you can use them in your trigger though
    UPDATE BOOK_AUTHORS
      SET bookid = :new.bookid
     WHERE bookid = :old.bookid;
    -- same for other two tables referencing BOOKID
    UPDATE BOOK_COPIES
      SET bookid = :new.bookid
     WHERE bookid = :old.bookid;
    UPDATE BOOK_LOANS
      SET bookid = :new.bookid
     WHERE bookid = :old.bookid;
END;
/
ALTER TRIGGER "CS4347F18"."UPDATEBOOKID" ENABLE;
