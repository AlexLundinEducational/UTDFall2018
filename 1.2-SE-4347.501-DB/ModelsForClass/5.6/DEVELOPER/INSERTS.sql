INSERT INTO DEPARTMENT (Dname, Dnumber, Mgr_ssn, Mgr_start_date)
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship)
INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation)
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno)
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum)
INSERT INTO WORKS_ON (Essn, Pno, Hours)


INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('John', 'B', 'Smith', 123456789, '09-JAN-1965', '731 Fondren, Houston, TX', 'M', 30000, 333445555, 5);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('Franklin', 'T', 'Wong', 333445555, '08-DEC-1955', '638 Voss, Houston, TX', 'M', 40000, 888665555, 5);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('Alicia', 'J', 'Zelaya', 999887777, '19-JAN-1968', '3321 Castle, Spring, TX', 'F', 25000, 987654321, 4);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('Jennifer', 'S', 'Wallace', 987654321, '20-MAY-1941', '291 Berry, Bellaire, TX', 'F', 43000, 888665555, 4);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('Ramesh', 'K', 'Narayan', 666884444, '15-SEP-1962', '975 Fire Oak, Humble, TX', 'M', 38000, 333445555, 5);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('Joyce', 'A', 'English', 453453453, '31-JUL-1972', '5631 Rice, Houston, TX', 'F', 25000, 333445555, 5);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('Ahmad', 'V', 'Jabbar', 987987987, '29-MAR-1969', '980 Dallas, Houston, TX', 'M', 25000, 987654321, 4);
INSERT INTO EMPLOYEE (Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) VALUES('James', 'E', 'Borg', 888665555, '11-NOV-1937', '450 Stone, Houston, TX', 'M', 55000, NULL, 1);
INSERT INTO DEPARTMENT (Dname, Dnumber, Mgr_ssn, Mgr_start_date) VALUES ('Research', 5, 333445555, '22-MAY-1988');
INSERT INTO DEPARTMENT (Dname, Dnumber, Mgr_ssn, Mgr_start_date) VALUES ('Administration', 4, 987654321, '01-JAN-1995');
INSERT INTO DEPARTMENT (Dname, Dnumber, Mgr_ssn, Mgr_start_date) VALUES ('Headquarters', 1, 888665555, '19-JUL-1981');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('333445555', 'Alice', 'F', '05-APR-1986', 'Daughter');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('333445555', 'Theodore', 'M', '25-OCT-1983', 'Son');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('333445555', 'Joy', 'F', '03-MAY-1958', 'Spouse');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('987654321', 'Abner', 'M', '28-FEB-1942', 'Spouse');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('123456789', 'Michael', 'M', '04-JAN-1988', 'Son');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('123456789', 'Alice', 'F', '30-DEC-1988', 'Daughter');
INSERT INTO DEPENDENT (Essn, Dependent_name, Sex, Bdate, Relationship) VALUES ('123456789', 'Elizabeth', 'F', '05-MAY-1967', 'Spouse');
INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation) VALUES (1, 'Houston');
INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation) VALUES (4, 'Stafford');
INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation) VALUES (5, 'Bellaire');
INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation) VALUES (5, 'Sugarland');
INSERT INTO DEPT_LOCATIONS (Dnumber, Dlocation) VALUES (5, 'Houston');
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES ('ProductX', 1, 'Bellaire', 5);
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES ('ProductY', 2, 'Sugarland', 5);
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES ('ProductZ', 3, 'Houston', 5);
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES ('Computerization', 10, 'Stafford', 4);
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES ('Reorganization', 20, 'Houston', 1);
INSERT INTO PROJECT (Pname, Pnumber, Plocation, Dnum) VALUES ('Newbenefits', 30, 'Stafford', 4);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (123456789, 1, 32.5);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (123456789, 2, 7.5);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (666884444, 3, 40.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (453453453, 1, 20.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (453453453, 2, 20.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (333445555, 2, 10.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (333445555, 3, 10.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (333445555, 10, 10.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (333445555, 20, 10.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (999887777, 30, 30.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (999887777, 10, 10.5);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (987987987, 10, 35.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (987987987, 30, 5.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (987654321, 30, 20.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (987654321, 20, 15.0);
INSERT INTO WORKS_ON (Essn, Pno, Hours) VALUES (888665555, 20, NULL);