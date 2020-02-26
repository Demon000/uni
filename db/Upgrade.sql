drop table if exists Version;
drop procedure if exists uspUpgrade1;
drop procedure if exists uspUpgrade2;
drop procedure if exists uspUpgrade3;
drop procedure if exists uspUpgrade4;
drop procedure if exists uspUpgrade5;
drop procedure if exists uspDowngrade1;
drop procedure if exists uspDowngrade2;
drop procedure if exists uspDowngrade3;
drop procedure if exists uspDowngrade4;
drop procedure if exists uspDowngrade5;
drop procedure if exists uspGoToVersion;

go
create procedure uspUpgrade1
as
begin
    create table UserVideoHistory(
		UserId int foreign key references Users(UserId) not null,
		VideoId int foreign key references Videos(VideoId) not null,
	);
end;

go
create procedure uspDowngrade1
as
begin
    drop table UserVideoHistory;
end;

go
create procedure uspUpgrade2
as begin
    alter table UserVideoHistory
    add WatchTimeSeconds int;
end;

go
create procedure uspDowngrade2
as begin
    alter table UserVideoHistory
    drop column WatchTimeSeconds;
end;

go
create procedure uspUpgrade3
as
begin
	alter table UserVideoHistory
	alter column WatchTimeSeconds float;
end

go
create procedure uspDowngrade3
as begin
	alter table UserVideoHistory
	alter column WatchTimeSeconds int;
end

go
create procedure uspUpgrade4
as
begin
	alter table UserVideoHistory
	add constraint WatchTimeSecondsDefaultConstraint
	default 0 for WatchTimeSeconds;
end

go
create procedure uspDowngrade4
as begin
	alter table UserVideoHistory
	drop constraint WatchTimeSecondsDefaultConstraint;
end

go
create procedure uspUpgrade5
as
begin
    alter table UserVideoHistory
    add PlaylistId int;

    alter table UserVideoHistory
    add constraint PlaylistIdForeignKey
    foreign key (PlaylistId) references Playlist(PlaylistId);
end

go
create procedure uspDowngrade5
as begin
    alter table UserVideoHistory
    drop constraint PlaylistIdForeignKey;

	alter table UserVideoHistory
	drop column PlaylistId;
end

go
create table Version(
	version int
);
insert into Version (version) values(
	0
);

go
create procedure uspGoToVersion
@version int
as begin
    if @version < 0 or @version > 5
    begin
        raiserror('Invalid version. Must be between 0 and 5', 10, 1)
        return
    end
    declare @currentVersion int
    declare @uspName nvarchar(100)
    set @currentVersion = (select version from Version)

    while @currentVersion < @version
    begin
        set @currentVersion = @currentVersion + 1
        set @uspName = 'uspUpgrade' + convert(nvarchar(100), @currentVersion);
        execute @uspName
    end

    while @currentVersion > @version
    begin
        set @uspName = 'uspDowngrade' + convert(nvarchar(100), @currentVersion);
        execute @uspName
        set @currentVersion = @currentVersion - 1
    end

    update Version set version=@version
end
go

exec uspGoToVersion 0;
