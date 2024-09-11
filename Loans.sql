
drop table Loans;

CREATE table Loans(
	Loan_ID varchar(20) primary key,
	Loan_Date date,
	Return_Date date,
	MemID varchar(20),
	foreign key (MemID) references BibMem(Member_ID) on DELETE cascade,
	BookID varchar(10),
	foreign key (BookID) references Book(Book_ID) on DELETE cascade
);

show tables from Bibliothek;

INSERT INTO Loans (Loan_ID , Loan_Date , Return_Date , MemID , BookID) VALUES
    (001,"2024-09-09","2024-09-16",1234567890123, 'ET004'),
    (002,"2024-09-02","2024-09-9",1234567890123, 'IT002');

INSERT INTO Loans (Loan_ID , Loan_Date , Return_Date , MemID , BookID) VALUES
    (003,"2024-09-02","2024-09-9",987654321098765, 'MB002'),
    (004,"2024-09-02","2024-09-9",987654321098765, 'ET001');

INSERT INTO Loans (Loan_ID , Loan_Date , Return_Date , MemID , BookID) VALUES
    (005,"2024-09-02","2024-09-9",1597532584561, 'RW005'),
    (006,"2024-09-02","2024-09-9",1597532584561, 'BW001');

INSERT INTO Loans (Loan_ID , Loan_Date , Return_Date , MemID , BookID) VALUES
    (007,"2024-09-09","2024-09-16",753951456852, 'BW004'),
    (008,"2024-09-02","2024-09-9",753951456852, 'IT005');

INSERT INTO Loans (Loan_ID , Loan_Date , Return_Date , MemID , BookID) VALUES
    (009,"2024-09-02","2024-09-9",3216549876543, 'MB005'),
    (010,"2024-09-02","2024-09-9",3216549876543, 'BW002');

INSERT INTO Loans (Loan_ID , Loan_Date , Return_Date , MemID , BookID) VALUES
    (011,"2024-09-02","2024-09-9",789456123098, 'RW002'),
    (012,"2024-09-02","2024-09-9",789456123098, 'RW003');



SELECT * from Loans;


