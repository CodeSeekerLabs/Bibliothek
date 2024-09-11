drop table BibMem;


CREATE TABLE BibMem(
	Member_ID varchar(20) primary key,
	First_Name varchar(255),
	Last_Name varchar(255),
	Phone_Num varchar(255),
	Street varchar(255),
	Post_Code varchar(255),
	City varchar(255),
	Email varchar(255)
	
)

show tables from Bibliothek;

INSERT INTO BibMem (Member_ID , First_Name , Last_Name , Phone_Num , Street , post_code, city, email) VALUES
(1234567890123, 'Anna', 'Müller', '0123456789', 'Hauptstraße 1', '10115', 'Berlin', 'anna.mueller@example.com'),
(987654321098765, 'Max', 'Schneider', '0987654321', 'Bahnhofstraße 23', '80331', 'München', 'max.schneider@example.com'),
(1597532584561, 'Lisa', 'Weber', '01512345678', 'Gartenweg 5', '50667', 'Köln', 'lisa.weber@example.com'),
(753951456852, 'Paul', 'Fischer', '01719876543', 'Musterstraße 10', '70173', 'Stuttgart', 'paul.fischer@example.com'),
(3216549876543, 'Sophie', 'Wagner', '0301234567', 'Lindenallee 8', '20095', 'Hamburg', 'sophie.wagner@example.com'),
(789456123098, 'Lukas', 'Becker', '01601234567', 'Rosenweg 12', '40213', 'Düsseldorf', 'lukas.becker@example.com');



select * from BibMem;















