--- https://stackoverflow.com/questions/19609649/does-the-foreign-keys-automatically-get-updated-as-primary-table-is-updated
--- https://docs.oracle.com/cd/B19306_01/server.102/b14220/triggers.htm#i6052
--- trigger tests of the BOOK SCHEMA

--- backup your tables
create table PUBLISHER_BACKUP as select * from PUBLISHER where 1=0;

--- clear the tables
TRUNCATE TABLE PUBLISHER; 
TRUNCATE TABLE BOOK; 
TRUNCATE TABLE BOOK_AUTHORS; 


--- start new inserts
INSERT INTO "PUBLISHER" (NAME, ADDRESS, PHONE) VALUES ('pub1', 'addy1', '1235557729');
INSERT INTO "PUBLISHER" (NAME, ADDRESS, PHONE) VALUES ('pub2', 'addy2', '1235557729');
INSERT INTO "PUBLISHER" (NAME, ADDRESS, PHONE) VALUES ('pub3', 'addy3', '1235557729');
INSERT INTO "PUBLISHER" (NAME, ADDRESS, PHONE) VALUES ('pub4', 'addy4', '1235557729');
INSERT INTO "BOOK" (BOOKID, TITLE, PUBLISHERNAME) VALUES ('b1', 'Art of War', 'pub1');
INSERT INTO "BOOK" (BOOKID, TITLE, PUBLISHERNAME) VALUES ('b2', 'Think and Grow Rich', 'pub2');
INSERT INTO "BOOK" (BOOKID, TITLE, PUBLISHERNAME) VALUES ('b3', 'The Kybalion', 'pub3');
INSERT INTO "BOOK_AUTHORS" (BOOKID, AUTHORNAME) VALUES ('b1', 'Sun Tzu');
INSERT INTO "BOOK_AUTHORS" (BOOKID, AUTHORNAME) VALUES ('b2', 'Napoleon Hill');
INSERT INTO "BOOK_AUTHORS" (BOOKID, AUTHORNAME) VALUES ('b3', 'Three Initiates');

--- this test script is separated into updates and deletes

--- update query for BOOK.BOOKID
--- this tests the UPDATE AFTER Trigger called UPDATEBOOKID
--- the Trigger will update all references from the:
--- BOOK_AUTHORS Table
--- BOOK_COPIES Table
--- BOOK_LOANS Table
UPDATE BOOK SET BOOKID = 'b90'
   WHERE BOOKID = 'b1';
   
--- I LEFT THIS TRIGGER OUT INTENTIONALLY 
--- SO YOU CAN PRACTICE WRITING ONE
--- try running this query so you can see what happens when a trigger is not in place
--- update query for PUBLISHER.NAME
UPDATE PUBLISHER SET NAME = 'publisher2'
   WHERE NAME = 'pub2';

--- delete query for BOOK.BOOKID
--- this tests the ON DELETE CASCADE statement in the BOOK TABLE
--- the cascade should remove all references from the:
--- BOOK_AUTHORS Table
--- BOOK_COPIES Table
--- BOOK_LOANS Table
DELETE FROM BOOK
  WHERE BOOKID = 'b90';
  
--- delete query for PUBLISHER.NAME
--- this tests the ON DELETE CASCADE statement in the BOOK TABLE
--- the cascade should remove all references in the BOOK_AUTHORS Table
DELETE FROM PUBLISHER
  WHERE NAME = 'publisher2';