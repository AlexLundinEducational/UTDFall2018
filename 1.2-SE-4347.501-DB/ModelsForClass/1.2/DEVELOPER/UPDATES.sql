-- a)
INSERT INTO STUDENT VALUES ('Johnson', 25, 1, 'MATH');

  

-- b)
UPDATE STUDENT
  SET CLASS = 2
  WHERE Name='Smith';


-- c)
INSERT INTO COURSE VALUES ('Knowledge Engineering','COSC4390', 3,'COSC');


-- d)
-- won't work because there are foreign key references to STUDENT
DELETE FROM STUDENT
  WHERE Name='Smith' AND StudentNumber=17;

