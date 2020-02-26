if exists (select * from dbo.sysobjects where id=object_id('Users_UserName_Length_CK'))
	alter table Users drop constraint Users_UserName_Length_CK;
if exists (select * from dbo.sysobjects where id=object_id('Users_UserName_Unique_CK'))
	alter table Users drop constraint Users_UserName_Unique_CK;

if exists (select * from dbo.sysobjects where id=object_id('Users_FirstName_Length_CK'))
	alter table Users drop constraint Users_FirstName_Length_CK;

if exists (select * from dbo.sysobjects where id=object_id('Users_LastName_Length_CK'))
	alter table Users drop constraint Users_LastName_Length_CK;

if exists (select * from dbo.sysobjects where id=object_id('Users_Email_Length_CK'))
	alter table Users drop constraint Users_Email_Length_CK;

if exists (select * from dbo.sysobjects where id=object_id('Users_Email_Unique_CK'))
	alter table Users drop constraint Users_Email_Unique_CK;

if exists (select * from dbo.sysobjects where id=object_id('Videos_Title_Length_CK'))
	alter table Videos drop constraint Videos_Title_Length_CK;
if exists (select * from dbo.sysobjects where id=object_id('Videos_Title_Description_CK'))
	alter table Videos drop constraint Videos_Title_Description_CK;
if exists (select * from dbo.sysobjects where id=object_id('Videos_UploadTime_Today_CK'))
	alter table Videos drop constraint Videos_UploadTime_Today_CK;

alter table Users alter column UserName nvarchar(80);
alter table Users add constraint Users_UserName_Length_CK check(len(UserName) >= 8);
alter table Users add constraint Users_UserName_Unique_CK unique(UserName);
alter table Users add constraint Users_FirstName_Length_CK check(len(FirstName) >= 2);
alter table Users add constraint Users_LastName_Length_CK check(len(LastName) >= 2);
alter table Users alter column Email nvarchar(80);
alter table Users add constraint Users_Email_Length_CK check(len(Email) >= 8);
alter table Users add constraint Users_Email_Unique_CK unique(Email);

alter table Videos add constraint Videos_Title_Length_CK check(len(Title) >= 8);
alter table Videos add constraint Videos_Title_Description_CK check(len([Description]) >= 16);
alter table Videos add constraint Videos_UploadTime_Today_CK check(UploadTIme < GetDate());

/* User CRUD */

drop procedure if exists CreateUser;
go
create procedure CreateUser(
		@UserName nvarchar(80),
		@Email nvarchar(160),
		@FirstName nvarchar(MAX),
		@LastName nvarchar(MAX))
as
begin
	insert into Users(UserName, Email, FirstName, LastName) values
		(@UserName, @Email, @FirstName, @LastName);
end
go

drop function if exists GetUser;
go
create function GetUser(@UserName nvarchar(80))
returns table
as
return select * from Users
	where UserName = @UserName;
go

drop procedure if exists UpdateUser;
go
create procedure UpdateUser(
		@UserId int,
		@UserName nvarchar(80),
		@Email nvarchar(160),
		@FirstName nvarchar(MAX),
		@LastName nvarchar(MAX))
as
begin
	update Users
	set UserName = @UserName, Email = @Email, FirstName = @FirstName, LastName = @LastName
	where UserId = @UserId;
end
go

drop procedure if exists DeleteUser;
go
create procedure DeleteUser(@UserId int)
as
begin
	delete from Users
	where UserId = @UserId;
end
go

/* Subscribtion CRUD */

drop procedure if exists SubscribeUser;
go
create procedure SubscribeUser(
		@UserId int,
		@ChannelId int)
as
begin
	insert into UserSubscriptions(UserId, TargetUserId) values
		(@UserId, @ChannelId);
end
go

drop procedure if exists UnsubscribeUser;
go
create procedure UnsubscribeUser(
		@UserId int,
		@ChannelId int)
as
begin
	delete from UserSubscriptions
	where UserId = @UserId and TargetUserId = @ChannelId;
end
go

drop function if exists IsUserSubscribed;
go
create function IsUserSubscribed(
		@UserId int,
		@ChannelId int)
returns bit
as
begin
	if exists(select * from UserSubscriptions
	where UserId = @UserId and TargetUserId = @ChannelId)
		return 1;
	return 0;
end
go

/* Videos CRUD */

drop procedure if exists CreateVideo;
go
create procedure CreateVideo(
		@UserId int,
		@Title nvarchar(MAX),
		@Description nvarchar(MAX))
as
begin
	insert into Videos(UserId, Title, UploadTime, [Description]) values
		(@UserId, @Title, GetDate(), @Description);
end
go

drop function if exists GetVideo;
go
create function GetVideo(@VideoId int)
returns table
as
return select * from Videos
	where VideoId = @VideoId;
go

drop procedure if exists UpdateVideo;
go
create procedure UpdateVideo(
		@UserId int,
		@VideoId int,
		@Title nvarchar(MAX),
		@Description nvarchar(MAX))
as
begin
	update Videos
	set Title = @Title, [Description] = @Description
	where VideoId = @VideoId and UserId = @UserId;
end
go

drop procedure if exists DeleteVideo;
go
create procedure DeleteVideo(
	@UserId int,
	@VideoId int)
as
begin
	delete from Videos
	where VideoId = @Videoid and UserId = @UserId;
end
go

/* Votes CRUD */

drop procedure if exists VoteVideo;
go
create procedure VoteVideo(
	@UserId int,
	@VideoId int,
	@Vote int)
as
begin
	if exists (select * from VideoVotes
			where VideoId = @VideoId and UserId = @UserId)
	begin
		if @Vote = -1
			update VideoVotes
			set Vote = 0
			where VideoId = @VideoId and UserId = @UserId;
		else if @Vote = 1
			update VideoVotes
			set Vote = 1
			where VideoId = @VideoId and UserId = @UserId;
		else if @Vote = 0
			delete from VideoVotes
			where VideoId = @VideoId and UserId = @UserId;
	end
	else
	begin
		if @Vote = -1
			update VideoVotes
			set Vote = 0
			where VideoId = @VideoId and UserId = @UserId;
		else if @Vote = 1
			update VideoVotes
			set Vote = 1
			where VideoId = @VideoId and UserId = @UserId;
	end
end
go

drop procedure if exists UnvoteVideo;
go
create procedure UnvoteVideo(
	@UserId int,
	@VideoId int)
as
begin
	exec VoteVideo @UserId, @VideoId, 0;
end
go


/* Comments CRUD */

drop procedure if exists CreateComment;
go
create procedure CreateComment(
		@UserId int,
		@VideoId int,
		@Description nvarchar(MAX))
as
begin
	insert into VideoComments(UserId, VideoId, [Description], CreateTime) values
		(@UserId, @VideoId, @Description, GetDate());
end
go

drop procedure if exists CreateCommentReply;
go
create procedure CreateCommentReply(
		@UserId int,
		@VideoId int,
		@CommentId int,
		@Description nvarchar(MAX))
as
begin
	insert into VideoComments(UserId, VideoId, RepliedCommentId, [Description], CreateTime) values
		(@UserId, @VideoId, @CommentId, @Description, GetDate());
end
go

drop function if exists GetComment;
go
create function GetComment(@CommentId int)
returns table
as
return select * from VideoComments
	where CommentId = @CommentId;
go

drop procedure if exists UpdateComment;
go
create procedure UpdateComment(
		@UserId int,
		@VideoId int,
		@CommentId int,
		@Description nvarchar(max))
as
begin
	update VideoComments
	set [Description] = @Description
	where CommentId = @CommentId and VideoId = @VideoId and UserId = @UserId;
end
go

drop procedure if exists DeleteComment;
go
create procedure DeleteComment(
	@UserId int,
	@VideoId int,
	@CommentId int)
as
begin
	delete from VideoComments
	where CommentId = @CommentId and VideoId = @Videoid and UserId = @UserId;
end
go

if exists(select name from sys.indexes where name='N_idx_YoutubeUsers_name')
	drop index N_idx_YoutubeUsers_name on Users;
create nonclustered index N_idx_YoutubeUsers_name on Users(UserName)
go

if exists(select name from sys.indexes where name='N_idx_YoutubeUsers_email')
	drop index N_idx_YoutubeUsers_email on Users;
create nonclustered index N_idx_YoutubeUsers_email on Users(Email)
go

drop view if exists UsersWithUserNameA;
go
create view UsersWithUserNameA
as
	select * from Users
	where UserName like 'A%';
go

drop view if exists UsersWithEmailA;
go
create view UsersWithEmailA
as
	select * from Users
	where Email like 'a%';
go

exec CreateUser 'ANameStartingWithA', 'emailnotstartingwitha@gmail.com', 'Cosmin', 'Tanislav';
exec CreateUser 'NameNotStartingWithA', 'anemailstartingwitha@gmail.com', 'Teodor', 'Spiridon';

select * from UsersWithUserNameA order by UserName;
select * from UsersWithEmailA order by Email;
