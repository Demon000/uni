drop view if exists UsersView;
drop view if exists UsersVideosView;
drop view if exists VideoVotesUsersVideosView;

drop procedure if exists InsertUsers;
drop procedure if exists InsertVideos;
drop procedure if exists InsertVideoVotes;

drop procedure if exists DeleteUsers;
drop procedure if exists DeleteVideos;
drop procedure if exists DeleteVideoVotes;

drop procedure if exists InsertAll;
drop procedure if exists DeleteAll;
drop procedure if exists EvaluateAll;

drop procedure if exists Main;

go

create view UsersView
as
select Users.Email, Users.FirstName, Users.LastName
from Users;
go

create view UsersVideosView
as
select Users.Email, Videos.Title
from Users
inner join Videos on Users.UserId = Videos.UserId;
go

create view VideoVotesUsersVideosView
as
select VideoVotes.UserId, VideoVotes.VideoId, count(*) as "Number of comments (User/Video)"
from VideoVotes
inner join Users on VideoVotes.UserId = Users.UserId
inner join Videos on VideoVotes.VideoId = Videos.VideoId
group by VideoVotes.UserId, VideoVotes.VideoId;
go

create procedure InsertUsers(@rows int)
as
begin
	declare @i int;
	set @i = 1;

	declare @UserName nvarchar(50);
	declare @Email nvarchar(50);
	declare @FirstName nvarchar(50);
	declare @LastName nvarchar(50);
	
	while @i <= @rows
	begin
		set @UserName = concat('UserName', convert(nvarchar(10), @i));
		set @Email = concat('Email', convert(nvarchar(10), @i));
		set @FirstName = concat('FirstName', convert(nvarchar(10), @i));
		set @LastName = concat('LastName', convert(nvarchar(10), @i));

		insert into Users(UserName, Email, FirstName, LastName)
				values(@UserName, @Email, @FirstName, @LastName);

		set @i = @i + 1;
	end
end
go

create procedure DeleteUsers(@rows int)
as
begin
	declare @i int;
	set @i = 1;

	declare @LastUserId int;
	declare @CurrentUserId int;

	select top 1 @LastUserId = Users.UserId from Users order by Users.UserId desc;

	while @i <= @rows
	begin
		set @CurrentUserId = @LastUserId - @i + 1;

		delete from Users where Users.UserId = @CurrentUserId;

		set @i = @i + 1;
	end
end
go

create procedure InsertVideos(@rows int)
as
begin
	declare @i int;
	set @i = 1;

	declare @CurrentUserId int;
	declare @LastUserId int;

	declare @Title nvarchar(50);
	declare @UploadTime date;
	declare @Description nvarchar(50);
	

	select top 1 @LastUserId = Users.UserId from Users order by Users.UserId desc;

	while @i <= @rows
	begin
		set @CurrentUserId = @LastUserId - @rows + @i;

		set @Title = concat('Title', convert(nvarchar(10), @i));
		set @UploadTime = getdate();
		set @Description = concat('Description', convert(nvarchar(10), @i));

		insert into Videos(UserId, Title, UploadTime, Description)
				values(@CurrentUserId, @Title, @UploadTime, @Description);

		set @i = @i + 1;
	end
end
go

create procedure DeleteVideos(@rows int)
as
begin
	declare @i int;
	set @i = 1;

	declare @LastVideoId int;
	declare @CurrentVideoId int;

	select top 1 @LastVideoId = Videos.VideoId from Videos order by Videos.VideoId desc;

	while @i <= @rows
	begin
		set @CurrentVideoId = @LastVideoId - @i + 1;

		delete from Videos where Videos.VideoId = @CurrentVideoId;

		set @i = @i + 1;
	end
end
go

create procedure InsertVideoVotes(@rows int)
as
begin
	declare @i int;
	set @i = 1;

	declare @CurrentUserId int;
	declare @LastUserId int;

	declare @CurrentVideoId int;
	declare @LastVideoId int;

	declare @Vote bit;

	select top 1 @LastUserId = Users.UserId from Users order by Users.UserId desc;
	select top 1 @LastVideoId =  Videos.VideoId from Videos order by Videos.VideoId desc;

	while @i <= @rows
	begin
		set @CurrentUserId = @LastUserId - @rows + @i;
		set @CurrentVideoId = @LastVideoId - @rows + @i;

		set @Vote = @CurrentUserId % 2;

		insert into VideoVotes(UserId, VideoId, Vote)
				values(@CurrentUserId, @CurrentVideoId, @Vote);

		set @i = @i + 1;
	end
end
go

create procedure DeleteVideoVotes(@rows int)
as
begin
	declare @i int;
	set @i = 1;

	declare @CurrentUserId int;
	declare @LastUserId int;

	declare @CurrentVideoId int;
	declare @LastVideoId int;

	declare @Vote bit;

	select top 1 @LastUserId = Users.UserId from Users order by Users.UserId desc;
	select top 1 @LastVideoId =  Videos.VideoId from Videos order by Videos.VideoId desc;

	while @i <= @rows
	begin
		set @CurrentUserId = @LastUserId - @i + 1;
		set @CurrentVideoId = @LastVideoId - @i + 1;

		delete from VideoVotes where VideoVotes.UserId = @CurrentUserId and VideoVotes.VideoId = @CurrentVideoId;

		set @i = @i + 1;
	end
end
go

create procedure InsertAll(@Table varchar(256), @rows int)
as
begin
	if @Table = 'Users'
		exec InsertUsers @rows;

	if @Table = 'Videos'
		exec InsertVideos @rows;

	if @Table  = 'VideoVotes'
		exec InsertVideoVotes @rows;
end
go

create procedure DeleteAll(@Table varchar(256), @rows int)
as
begin
	if @Table = 'Users'
		exec DeleteUsers @rows;

	if @Table = 'Videos'
		exec DeleteVideos @rows;

	if @Table  = 'VideoVotes'
		exec DeleteVideoVotes @rows;
end
go

create procedure EvaluateAll(@View varchar(256))
as
begin
	if @View = 'Users'
		select * from UsersView;

	if @View = 'Videos'
		select * from UsersVideosView;

	if @View  = 'VideoVotes'
		select * from VideoVotesUsersVideosView;
end
go

create procedure Main
as
begin
	declare @TestTableCursor cursor;

	declare @TestId int;
	declare @TestName nvarchar(256);
	declare @TableId int;
	declare @TableName nvarchar(256);
	declare @NoOfRows int;

	declare @TestProcedureName nvarchar(256);

	declare @TestRunId int;
	declare @StartTime datetime;
	declare @MidTime datetime;
	declare @EndTime datetime;
	declare @Description nvarchar(256);

	set @TestTableCursor = cursor for select TestId, TableId, NoOfRows from TestTables order by TestTables.Position asc;

	open @TestTableCursor;
	fetch next from @TestTableCursor into @TestId, @TableId, @NoOfRows;

	while @@fetch_status = 0
	begin
		select @TestName=name from Tests where Tests.TestId = @TestId;
		select @TableName=name from Tables where Tables.TableId = @TableId;

		print @TableName;
		print @TestName;
		print @NoOfRows;

		set @TestProcedureName = @TestName + 'All';

		set @StartTime = getdate();
		exec @TestProcedureName @TableName, @NoOfRows;
		set @MidTime = getdate();
		exec EvaluateAll @TableName;
		set @EndTime = getdate();

		set @Description = 'Test: ' + @TestName + ' ' +  convert(nvarchar(10), @NoOfRows) + ' ' + @TableName;

		insert into TestRuns values(@Description, @StartTime, @EndTime);
		select @TestRunId=TestRuns.TestRunId from TestRuns order by TestRuns.TestRunId desc;

		insert into TestRunTables Values(@TestId, @TableId, @StartTime, @MidTime);
		insert into TestRunViews Values(@TestId, @TableId, @MidTime, @EndTime);

		fetch next from @TestTableCursor into @TestId, @TableId, @NoOfRows;
	end
end
go

exec Main;

select * from testruntables;
select * from TestRunViews;
select * from TestRuns;
