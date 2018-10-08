-- a)
-- there are no COSC in the Tables
SELECT Name FROM STUDENT
  WHERE Major='COSC';
  
-- a) modified  
-- 2 students with CS major
SELECT Name FROM STUDENT 
  WHERE Major='CS';

-- b)
-- these don't exist
SELECT CourseName
  FROM COURSE, SECTION
  WHERE COURSE.CourseNumber=SECTION.CourseNumber AND SECTION.Instructor='King'
  AND (Year=85 OR Year=86);
 
-- b) modified  
-- shows all the course name King teaches in 07 and 08
SELECT CourseName
  FROM COURSE, SECTION
  WHERE COURSE.CourseNumber=SECTION.CourseNumber AND SECTION.Instructor='King'
  AND (Year=07 OR Year=08);

-- c)
SELECT CourseNumber, Semester, Year, COUNT(*)
  FROM SECTION, GRADE_REPORT
  WHERE Instructor='King' AND SECTION.SectionIdentifier=GRADE_REPORT.SectionIdentifier
  GROUP BY CourseNumber, Semester, Year;


-- d)
-- there are no COSC majors in the data with class level 5
SELECT Name, CourseName, C.CourseNumber, CreditHours, Semester, Year, Grade
  FROM STUDENT ST, COURSE C, SECTION S, GRADE_REPORT G
  WHERE Class=5 AND Major='COSC' AND ST.StudentNumber=G.StudentNumber AND
  G.SectionIdentifier=S.SectionIdentifier AND S.CourseNumber=C.CourseNumber;

-- d) modified
-- search for class level 1, CS majors
SELECT Name, CourseName, C.CourseNumber, CreditHours, Semester, Year, Grade
  FROM STUDENT ST, COURSE C, SECTION S, GRADE_REPORT G
  WHERE Class=1 AND Major='CS' AND ST.StudentNumber=G.StudentNumber AND
  G.SectionIdentifier=S.SectionIdentifier AND S.CourseNumber=C.CourseNumber;
  
-- e) select all student's who do have straight A's  
SELECT Name, Major
FROM STUDENT
WHERE NOT EXISTS ( SELECT *
FROM GRADE_REPORT
WHERE StudentNumber= STUDENT.StudentNumber AND NOT(Grade='A'));

  
-- f) select all student's do not have straight A's
SELECT Name, Major
  FROM STUDENT
  WHERE EXISTS ( SELECT *
  FROM GRADE_REPORT
  WHERE StudentNumber= STUDENT.StudentNumber AND NOT(Grade='A'));

-- select student's who have atleast 1 A
SELECT Name, Major
  FROM STUDENT
  WHERE NOT EXISTS ( SELECT *
  FROM GRADE_REPORT
  WHERE StudentNumber= STUDENT.StudentNumber AND Grade='A' );

