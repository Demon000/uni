insert into Users (UserName, Email, FirstName, LastName) values
		/* 1 - Users */
		('cozzmy13', 'cozzmy13@gmail.com', 'Cosmin-Gabriel', 'Tanislav'),
		('tanislav000', 'tanislav000@gmail.com', 'Cosmin-Gabriel', 'Tanislav'),
		('solcanmihai', 'solcan.mihaiandrei@yahoo.com', 'Mihai-Andrei', 'Solcan'),
		('raduzx', 'radu99@gmail.com', 'Cristian-Radu', 'Stefanescu'),
		/* 5 - Channels */
		('pewds', 'pewdiepie@gmail.com', 'Felix', 'Arvid Ulf Kjellberg'),
		('callmekevin', 'callmekevin@gmail.com', 'Kevin', 'O''Reilly'),
		('linustechtips', 'ltt@linustechtips.com', 'Sebastian', 'Linus'),
		('techlinked', 'techlinked@linustechtips.com', 'Sebastian', 'Linux'),
		('cnestat', 'caseynestat@gmail.com', 'Casey', 'Nestat'),
		('sucre', 'sucre@gmail.com', 'Sucre', 'Sucre');
		
insert into UserSubscriptions (UserId, TargetUserId) values
		(1, 5),
		(1, 6),
		(1, 7),
		(1, 8),
		(1, 9),
		(1, 10),
		(2, 5),
		(2, 6),
		(3, 5),
		(3, 6),
		(3, 10),
		(4, 10),
		(5, 6),
		(6, 5),
		(7, 8),
		(8, 7),
		(10, 9);

insert into Videos (UserId, Title, UploadTime, [Description]) values
	(5, 'How to make a Minecraft Creeper NEVER EXPLODE again. (Tutorial) Minecraft - Part 35', '2019-10-13', 'I make minecraft creeper regret what he''s done'),
	(5, 'This building will change Minecraft FOREVER Minecraft - Part 34', '2019-09-22', 'My new minecraft invention is patented DONT STEAL!'),
	(5, 'What does 10 000 BELLS in Minecraft sound like? - Part 33', '2019-09-14', 'new bell update in minecraft epicly attempts'),
	(5, 'Minecraft just became 10x better! - Part 32', '2019-09-09', 'Trying out the Elytra in minecraft for the first time flying epicly')

insert into Videos (UserId, Title, UploadTime, [Description]) values
	(5, 'Rip Ohio /r/softwaregore #48 [REDDIT REVIEW]', '2019-10-06', 'ohio will be taken over by computers. subscribe for more reddit reviews epicly'),
	(5, 'This video is Mildly Infuriating.. /r/mildlyinfuriating #47 [REDDIT REVIEW]', '2019-10-17', 'Thank you');

insert into Videos (UserId, Title, UploadTime, [Description]) values
	(6, 'A MURDERER IN THE VALLEY | Stardew Valley', '2017-02-27', 'If you enjoyed the video please leave a like, thank you!'),
	(6, 'MONSTERS IN THE VALLEY | Stardew Valley', '2017-03-1', 'If you enjoyed the video please leave a like, thank you!');

insert into Videos (UserId, Title, UploadTime, [Description]) values
	(6, 'THE FOREARM GOD | Sims 4 City Life', '2016-11-25', 'If you enjoyed the video please leave a like, thank you!'),
	(6, 'CRAZY BABIES | Sims 4 City Life', '2016-11-29', 'If you enjoyed the video please leave a like, thank you!');

insert into VideoVotes (UserId, VideoId, Vote) values
	(1, 1, 1),
	(1, 2, 1),
	(1, 3, 0),
	(1, 4, 1),
	(1, 5, 1),
	(1, 8, 1);

insert into VideoComments (UserId, VideoId, [Description], CreateTime) values
	(1, 1, 'Awesome video!', '2019-10-14'),
	(1, 2, 'Another awesome video!', '2019-09-22');

insert into VideoComments (UserId, VideoId, RepliedCommentId, [Description], CreateTime) values
	(2, 1, 1, 'I agree!', '2019-10-14'),
	(3, 1, 1, 'Meh.', '2019-10-14');

insert into PlaylistSortOrderLookup (SortOrderId, SortOrderName) values
	(1, 'Date added (newest)'),
	(2, 'Date added (oldest)'),
	(3, 'Date published (newesr)'),
	(4, 'Date published (oldest)');
	
insert into Playlists (UserId, Title, SortOrderId) values
	(5, 'EPIC MINECRAFT', 1),
	(5, 'REDDIT REVIEW', 2),
	(6, 'MINECRAFT', 1),
	(6, 'JIM PICKENS', 2),
	(6, 'ALL VIDEOS', 1);

insert into PlaylistVideos (PlaylistsId, VideoId, AddTime) values
	(1, 1, '2019-10-13'),
	(1, 2, '2019-09-22'),
	(1, 3, '2019-09-14'),
	(1, 4, '2019-09-09'),
	(2, 5, '2019-10-17'),
	(2, 6, '2019-10-17'),
	(3, 7, '2017-03-01'),
	(3, 8, '2017-03-01'),
	(4, 9, '2016-11-29'),
	(4, 10, '2016-11-29'),
	(5, 7, '2017-03-01'),
	(5, 8, '2017-03-01'),
	(5, 9, '2016-11-29'),
	(5, 10, '2016-11-29');
