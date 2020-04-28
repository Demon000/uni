drop function if exists IsStringValid;
drop function if exists IsTitleValid;
drop function if exists IsDescriptionValid;
drop procedure if exists CreatePlaylistAndVideoFull;
drop procedure if exists CreatePlaylistAndVideoPartial;
drop table if exists HistoryEntries;

go
create function IsStringValid(@String nvarchar(MAX), @MinLength int)
returns bit
as begin
	if @String is null
		return 0;

	if len(@String) < @MinLength
		return 0;

	return 1;
end

go
create function IsTitleValid(@Title nvarchar(MAX))
returns bit
as begin
	declare @Validity bit;
	exec @Validity = IsStringValid @Title, 8;
	return @Validity;
end

go
create function IsDescriptionValid(@Description nvarchar(MAX))
returns bit
as begin
	declare @Validity bit;
	exec @Validity = IsStringValid @Description, 16;
	return @Validity;
end

go
create table HistoryEntries(
	HistoryEntryId int primary key identity,
	TableName nvarchar(MAX),
	ActionName nvarchar(MAX),
	[Time] datetime,
)

go
create procedure CreatePlaylistAndVideoFull(
	@UserId int,
	@PlaylistTitle nvarchar(MAX),
	@VideoTitle nvarchar(MAX),
	@VideoDescription nvarchar(MAX)
)
as begin
	begin transaction;
	begin try
		if dbo.IsTitleValid(@PlaylistTitle) = 0
			raiserror('PLAYLIST_TITLE_INVALID', 14, 1);
		
		insert into Playlists (UserId, Title, SortOrderId) values
			(@UserId, @PlaylistTitle, 1);
		declare @PlaylistId int;
		set @PlaylistId = (select max(PlaylistId) from Playlists);

		if dbo.IsTitleValid(@VideoTitle) = 0
			raiserror('VIDEO_TITLE_INVALID', 14, 1);

		if dbo.IsDescriptionValid(@VideoDescription) = 0
			raiserror('VIDEO_DESCRIPTION_INVALID', 14, 1);

		insert into Videos (UserId, Title, UploadTime, [Description]) values
			(5, @VideoTitle, GetDate(), @VideoDescription);
		declare @VideoId int;
		set @VideoId = (select max(VideoId) from Videos);

		insert into PlaylistVideos (PlaylistId, VideoId, AddTime) values
			(@PlaylistId, @VideoId, GetDate());

		commit transaction;

		insert into HistoryEntries (TableName, ActionName, [Time]) values
			('Playlists', 'CREATE_PLAYLIST_SUCCESS', GetDate()),
			('Videos', 'CREATE_VIDEO_SUCCESS', GetDate()),
			('PlaylistVideos', 'CREATE_PLATLIST_VIDEO_SUCCESS', GetDate());
	end try
	begin catch
		rollback transaction;

		insert into HistoryEntries (TableName, ActionName, [Time]) values
			('Playlists', 'CREATE_PLAYLIST_AND_VIDEO_FAIL', GetDate()),
			('Videos', 'CREATE_VIDEO_FAIL', GetDate()),
			('PlaylistVideos', 'CREATE_PLATLIST_VIDEO_FAIL', GetDate());
	end catch
end

go
create procedure CreatePlaylistAndVideoPartial(
	@UserId int,
	@PlaylistTitle nvarchar(MAX),
	@VideoTitle nvarchar(MAX),
	@VideoDescription nvarchar(MAX)
)
as begin
	declare @PlaylistId int;
	declare @VideoId int;
	declare @PlayListAndVideoInserted bit = 1;

	begin try
		begin transaction;

		if dbo.IsTitleValid(@PlaylistTitle) = 0
			raiserror('PLAYLIST_TITLE_INVALID', 14, 1);
		
		insert into Playlists (UserId, Title, SortOrderId) values
			(@UserId, @PlaylistTitle, 1);
		set @PlaylistId = (select max(PlaylistId) from Playlists);

		commit transaction;

		insert into HistoryEntries (TableName, ActionName, [Time]) values
			('Playlists', 'CREATE_PLAYLIST_SUCCESS', GetDate());
	end try
	begin catch
		rollback transaction;

		insert into HistoryEntries (TableName, ActionName, [Time]) values
			('Playlists', 'CREATE_PLAYLIST_FAIL', GetDate());

		set @PlayListAndVideoInserted = 0;
	end catch


	begin try
		begin transaction

		if dbo.IsTitleValid(@VideoTitle) = 0
			raiserror('VIDEO_TITLE_INVALID', 14, 1);

		if dbo.IsDescriptionValid(@VideoDescription) = 0
			raiserror('VIDEO_DESCRIPTION_INVALID', 14, 1);

		insert into Videos (UserId, Title, UploadTime, [Description]) values
			(5, @VideoTitle, GetDate(), @VideoDescription);
		set @VideoId = (select max(VideoId) from Videos);

		commit transaction;

		insert into HistoryEntries (TableName, ActionName, [Time]) values
			('Videos', 'CREATE_VIDEO_SUCCESS', GetDate());
	end try
	begin catch
		rollback transaction;

		insert into HistoryEntries (TableName, ActionName, [Time]) values
			('Videos', 'CREATE_VIDEO_FAIL', GetDate());

		set @PlayListAndVideoInserted = 0;
	end catch

	if @PlayListAndVideoInserted = 1
	begin
		begin try
			begin transaction

			insert into PlaylistVideos (PlaylistId, VideoId, AddTime) values
				(@PlaylistId, @VideoId, GetDate());

			commit transaction;

			insert into HistoryEntries (TableName, ActionName, [Time]) values
				('PlaylistVideos', 'CREATE_PLATLIST_VIDEO_SUCCESS', GetDate());
		end try
		begin catch
			rollback transaction;

			insert into HistoryEntries (TableName, ActionName, [Time]) values
				('PlaylistVideos', 'CREATE_PLATLIST_VIDEO_FAIL', GetDate());
		end catch
	end
end

go

/*
exec CreatePlaylistAndVideoFull 1, 'Created now 1', 'Long enough title 1', 'This is a long enough description';
exec CreatePlaylistAndVideoFull 1, 'Created now 2', 'Not 2', 'This is a long enough description';
exec CreatePlaylistAndVideoFull 1, 'Not 3', 'Long enough title 3', 'This is a long enough description';

exec CreatePlaylistAndVideoPartial 1, 'Created now 4', 'Long enough title 4', 'This is a long enough description';
exec CreatePlaylistAndVideoPartial 1, 'Created now 5', 'Not 5', 'This is a long enough description';
exec CreatePlaylistAndVideoPartial 1, 'Not 6', 'Long enough title 6', 'This is a long enough description';\

select * from Playlists;
select * from Videos;
select * from PlaylistVideos;
select * from HistoryEntries;
*/
