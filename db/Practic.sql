drop table if exists SportmanGameDuration;
drop table if exists SportCompetition;
drop table if exists SportGame;
drop table if exists Sportsman;
drop table if exists SportClub;

create table SportClub(
	SportClubId int primary key not null identity(1, 1),

	[Name] nvarchar(MAX) not null,
	CategoryName nvarchar(MAX) not null,
);

create table Sportsman(
	SportsmanId int primary key not null identity(1, 1),
	SportsGroupId int foreign key references SportClub(SportClubId) not null,

	[Name] nvarchar(MAX) not null,
	Ranking int not null,
);

create table SportGame(
	SportGameId int primary key not null identity(1, 1),

	[Name] nvarchar(MAX) not null,
);

create table SportCompetition(
	SportCompetitionId int primary key not null identity(1, 1),
	SportGameId int foreign key references SportGame(SportGameId) not null,

	[Name] nvarchar(MAX) not null,
	[Location] nvarchar(MAX) not null,
);

create table SportmanGameDuration(
	SportsmanId int not null,
	SportGameId int not null,
	primary key(SportsmanId, SportGameId),
	foreign key(SportGameId) references SportGame(SportGameId),
	foreign key(SportsmanId) references Sportsman(SportsmanId),

	Duration datetime not null,
);

insert into SportClub([Name], CategoryName) values
	('Club Sportiv Fotbal Cluj', 'Juniori'),
	('Club Sportiv Handbal Cluj', 'Juniori');

insert into Sportsman(SportsGroupId, [Name], Ranking) values
	(1, 'Teodor Spiridor', 10),
	(1, 'Mihai Solcan', 11),
	(1, 'Christian Tatoiu', 15),
	(2, 'Cosmin Tanislav', 1),
	(2, 'Mihai Solcan', 2);

insert into SportGame([Name]) values
	('Fotbal'),
	('Handbal');

insert into SportCompetition(SportGameId, [Name], [Location]) values
	(1, 'Competitie Nationala Fotbal Masculin', 'Romania, Bucuresti'),
	(1, 'Competitie Nationala Fotbal Feminin', 'Romania, Cluj-Napoca'),
	(2, 'Competitie Nationala Handbal Masculin', 'Romania, Craiova'),
	(2, 'Competitie Nationala Handbal Feminin', 'Romania, Iasi');

drop procedure if exists SetSportmanGameDuration;

go

create procedure SetSportmanGameDuration(@SportsmanId int, @SportGameId int, @StartTime datetime, @EndTime datetime)
as
begin
	declare @Duration datetime;

	set @Duration = @EndTime - @StartTime;

	if exists (select * from SportmanGameDuration
			where SportsmanId = @SportsmanId and SportGameId = @SportGameId)
	begin
		update SportmanGameDuration
		set Duration = @Duration
		where SportsmanId = @SportsmanId and SportGameId = @SportGameId;
	end
	else
	begin
		insert into SportmanGameDuration(SportsmanId, SportGameId, Duration) values
			(@SportsmanId, @SportGameId, @Duration);
	end
end
go

exec SetSportmanGameDuration @SportsmanId = 1, @SportGameId = 1, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 13:30:30';
exec SetSportmanGameDuration @SportsmanId = 1, @SportGameId = 1, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';

exec SetSportmanGameDuration @SportsmanId = 1, @SportGameId = 1, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';
exec SetSportmanGameDuration @SportsmanId = 1, @SportGameId = 2, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';

exec SetSportmanGameDuration @SportsmanId = 2, @SportGameId = 1, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';
exec SetSportmanGameDuration @SportsmanId = 2, @SportGameId = 2, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';

exec SetSportmanGameDuration @SportsmanId = 3, @SportGameId = 1, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';

/*
exec SetSportmanGameDuration @SportsmanId = 4, @SportGameId = 2, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';

exec SetSportmanGameDuration @SportsmanId = 5, @SportGameId = 1, @StartTime = '2019/10/10 12:30:00', @EndTime = '2019/10/10 15:30:30';
*/

drop view if exists SportsmanWithAllGamesView;

go

create view SportsmanWithAllGamesView
as
	select Sportsman.[Name] from Sportsman
	where Sportsman.SportsmanId in (
		select SportmanGameDuration.SportsmanId from SportmanGameDuration
		where (
			select count(*) from SportmanGameDuration as InnerSportmanGameDuration
			where InnerSportmanGameDuration.SportsmanId = SportmanGameDuration.SportsmanId
		) = (
			select count(*) from SportGame
		)
	);
go

select * from SportsmanWithAllGamesView;

drop function if exists GetSportsmanWithRankingAndGames;

go

create function GetSportsmanWithRankingAndGames(@NoGames int)
returns table
as
return select Sportsman.[Name] from Sportsman
	where Sportsman.Ranking > 10 and Sportsman.SportsmanId in (
		select SportmanGameDuration.SportsmanId from SportmanGameDuration
		where @NoGames <= (
			select count(*) from SportmanGameDuration as InnerSportmanGameDuration
			where InnerSportmanGameDuration.SportsmanId = SportmanGameDuration.SportsmanId
		)
	);
go

select * from GetSportsmanWithRankingAndGames(0);
select * from GetSportsmanWithRankingAndGames(1);
