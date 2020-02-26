insert into Tables(Name) values 
('Users'),
('Videos'),
('VideoVotes');
go

insert into Views(Name) values
('UsersView'),
('UsersVideosView'),
('VideoVotesUsersVideosView');
go

insert into Tests(Name) values 
('Insert'),
('Insert'),
('Insert'),
('Delete'),
('Delete'),
('Delete'),
('Evaluate');
go

insert into TestTables(TestId, TableId, NoOfRows, Position) values
/* Add Users */
(1, 1, 10, 1),
(2, 1, 100, 4),
(3, 1, 1000, 7),
/* Add Videos */
(1, 2, 10, 2),
(2, 2, 100, 5),
(3, 2, 1000, 8),
/* Add VideoVotes */
(1, 3, 10, 3),
(2, 3, 100, 6),
(3, 3, 1000, 9),

/* Delete VideoVotes */
(4, 3, 1000, 10),
(5, 3, 100, 13),
(6, 3, 10, 16),
/* Delete Videos */
(4, 2, 1000, 11),
(5, 2, 100, 14),
(6, 2, 10, 17),
/* Delete Users */
(4, 1, 1000, 12),
(5, 1, 100, 15),
(6, 1, 10, 18);
go

insert into TestViews(TestId, ViewId) values
(7, 1),
(7, 2),
(7, 3);
go
