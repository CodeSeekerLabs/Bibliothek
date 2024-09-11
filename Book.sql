drop table Book;


CREATE TABLE Book(
	Book_ID varchar(10) primary key,
	Status enum('available', 'on loan'),
	Title varchar(255),
	Author varchar(255),
	Publisher varchar(255),
	ISBN varchar(20),
	Year_Pub year,
	Category enum('Elektrotechnik','Maschinenbau','Informatik','Betriebswirtschaft','Rechtswissenschaften')
)

show tables from Bibliothek;




insert into Book (Book_ID,Status,Title,Author,Publisher,ISBN,Year_Pub,Category)
values
	('ET001','on loan', 'Grundlagen der Elektrotechnik', 'Max Müller', 'TechBooks', 'E78-3-16-148410-0', 2023, 'Elektrotechnik'),
	('ET002','available', 'Schaltungstechnik 101', 'Anna Schmidt', 'ElektroVerlag', 'E78-1-23-456789-7', 2022, 'Elektrotechnik'),
	('ET003','available', 'Moderne Stromkreise', 'Peter Weber', 'FutureTech', 'E78-0-12-345678-9', 2021, 'Elektrotechnik'),
	('ET004','on loan', 'Digitaltechnik Grundlagen', 'Laura Braun', 'ElectroBooks', 'E78-3-45-678901-2', 2020, 'Elektrotechnik'),
	('ET005','available', 'Elektromagnetische Felder', 'Tom Fischer', 'SciencePub', 'E78-4-56-789012-3', 2019, 'Elektrotechnik');

insert into Book (Book_ID,Status,Title,Author,Publisher,ISBN,Year_Pub,Category)
values
	('MB001','available', 'Einführung in den Maschinenbau', 'Sophie Meyer', 'MachinePress', 'M78-3-16-148411-7', 2023, 'Maschinenbau'),
	('MB002','on loan', 'Werkstoffkunde', 'Lukas Klein', 'EngineeringBooks', 'M78-1-23-456790-4', 2022, 'Maschinenbau'),
	('MB003','available', 'Fertigungstechnik Basics', 'Eva Müller', 'TechPublish', 'M78-0-12-345679-6', 2021, 'Maschinenbau'),
	('MB004','available', 'Maschinenbau für Einsteiger', 'Maximilian Fischer', 'MechBooks', 'M78-3-45-678902-1', 2020, 'Maschinenbau'),
	('MB005','on loan', 'Konstruktionslehre', 'Nina Weber', 'MachineVerlag', 'M78-4-56-789013-4', 2019, 'Maschinenbau');

insert into Book (Book_ID,Status,Title,Author,Publisher,ISBN,Year_Pub,Category)
values
	('IT001','available', 'Grundlagen der Programmierung', 'Alex Schmidt', 'CodePress', 'I78-3-16-148412-4', 2023, 'Informatik'),
	('IT002','on loan', 'Datenbanken und SQL', 'Lena Meyer', 'TechVerlag', 'I78-1-23-456791-1', 2022, 'Informatik'),
	('IT003','available', 'Algorithmen und Datenstrukturen', 'Jonas Braun', 'ProgrammingBooks', 'I78-0-12-345680-3', 2021, 'Informatik'),
	('IT004','available', 'Webentwicklung für Anfänger', 'Marie Fischer', 'WebTech', 'I78-3-45-678903-0', 2020, 'Informatik'),
	('IT005','on loan', 'Künstliche Intelligenz', 'Robert Weber', 'AIBooks', 'I78-4-56-789014-5', 2019, 'Informatik');

insert into Book (Book_ID,Status,Title,Author,Publisher,ISBN,Year_Pub,Category)
values
	('BW001','on loan', 'Einführung in die BWL', 'Julia Schmidt', 'BWLVerlag', 'B78-3-16-148413-1', 2023, 'Betriebswirtschaft'),
	('BW002','on loan', 'Marketing Strategien', 'Thomas Meyer', 'BusinessPress', 'B78-1-23-456792-8', 2022, 'Betriebswirtschaft'),
	('BW003','available', 'Finanzmanagement', 'Claudia Weber', 'FinanceBooks', 'B78-0-12-345681-0', 2021, 'Betriebswirtschaft'),
	('BW004','on loan', 'Personalwirtschaft', 'David Fischer', 'HRBooks', 'B78-3-45-678904-7', 2020, 'Betriebswirtschaft'),
	('BW005','available', 'Unternehmensführung', 'Anna Braun', 'ManagementVerlag', 'B78-4-56-789015-6', 2019, 'Betriebswirtschaft');

insert into Book (Book_ID,Status,Title,Author,Publisher,ISBN,Year_Pub,Category)
values
	('RW001','available', 'Grundzüge des Rechts', 'Michael Weber', 'LawPress', 'R78-3-16-148414-8', 2023, 'Rechtswissenschaften'),
	('RW002','on loan', 'Strafrecht Einführung', 'Laura Müller', 'LegalBooks', 'R78-1-23-456793-5', 2022, 'Rechtswissenschaften'),
	('RW003','on loan', 'Zivilrecht Basics', 'Paul Fischer', 'JusticePress', 'R78-0-12-345682-7', 2021, 'Rechtswissenschaften'),
	('RW004','available', 'Öffentliches Recht', 'Sophia Braun', 'LawVerlag', 'R78-3-45-678905-4', 2020, 'Rechtswissenschaften'),
	('RW005','on loan', 'Verwaltungsrecht', 'Maximilian Meyer', 'LegalVerlag', 'R78-4-56-789016-7', 2019, 'Rechtswissenschaften');
	


select * from Book;

























