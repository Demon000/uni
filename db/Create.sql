drop table if exists VideoReports;
drop table if exists VideoReportTypeLookup;
drop table if exists VideoReportStatusLookup;
drop table if exists PlaylistVideos;
drop table if exists Playlists;
drop table if exists PlaylistSortOrderLookup;
drop table if exists VideoCommentVotes;
drop table if exists VideoComments;
drop table if exists VideoVotes;
drop table if exists Videos;
drop table if exists UserSubscriptions;
drop table if exists Users;
drop table if exists HistoryEntries;

create table Users(
	UserId int primary key not null identity(1, 1),

	UserName nvarchar(MAX) not null,
	Email nvarchar(MAX) not null,
	FirstName nvarchar(MAX) not null,
	LastName nvarchar(MAX) not null,
);

create table UserSubscriptions(
	UserId int not null,
	TargetUserId int not null,
	primary key (UserId, TargetUserId),
	foreign key (UserId) references Users(UserId),
	foreign key (TargetUserId) references Users(UserId)
);

create table Videos(
	VideoId int primary key not null identity(1, 1),
	UserId int foreign key references Users(UserId) not null,

	Title nvarchar(MAX) not null,
	UploadTime date not null,
	[Description] nvarchar(MAX) not null, /* Avoid Description keyword usage */
);

create table VideoVotes(
	UserId int not null,
	VideoId int not null,
	primary key (UserId, VideoId),
	foreign key (UserId) references Users(UserId),
	foreign key (VideoId) references Videos(VideoId),

	Vote bit not null,
);

create table VideoComments(
	CommentId int primary key not null identity(1, 1),
	UserId int foreign key references Users(UserId) not null,
	VideoId int foreign key references Videos(VideoId) not null,
	RepliedCommentId int foreign key references VideoComments(CommentId),

	[Description] nvarchar(MAX) not null, /* Avoid Description keyword usage */
	CreateTime date not null,
);

create table VideoCommentVotes(
	UserId int not null,
	CommentId int,
	primary key (UserId, CommentId),
	foreign key (UserId) references Users(UserId),
	foreign key (CommentId) references VideoComments(CommentId),

	Vote bit not null,
);

create table PlaylistSortOrderLookup(
	SortOrderId int primary key not null,
	SortOrderName nvarchar(MAX) not null,
);

create table Playlists(
	PlaylistId int primary key not null identity(1, 1),
	UserId int foreign key references Users(UserId) not null,

	Title nvarchar(MAX) not null,
	SortOrderId int foreign key references PlaylistSortOrderLookup(SortOrderId) not null,
);

create table PlaylistVideos(
	PlaylistId int not null,
	VideoId int not null,
	primary key(PlaylistId, VideoId),
	foreign key(PlaylistId) references Playlists(PlaylistId),
	foreign key(VideoId) references Videos(VideoId),

	AddTime date not null,
);

create table VideoReportTypeLookup(
	VideoReportsTypeId int primary key,
	VideoReportsTypeName nvarchar(MAX) not null,
);

create table VideoReportStatusLookup(
	VideoReportsStatusId int primary key not null,
	VideoReportsStatusName nvarchar(MAX) not null,
);

create table VideoReports(
	VideoReportsId int primary key not null identity(1, 1),
	UserId int foreign key references Users(UserId) not null,

	ReportTime date not null,
	[Description] nvarchar(MAX) not null, /* Avoid Description keyword usage */
	VideoReportsTypeId int foreign key references VideReportTypeLookup(VideoReportsTypeId),
	VideoReportStatusLookup int foreign key references VideoReportStatusLookup(VideoReportsStatusId),
);

create table HistoryEntries(
	HistoryEntryId int primary key identity,
	TableName nvarchar(MAX),
	ActionName nvarchar(MAX),
	[Time] datetime,
);
