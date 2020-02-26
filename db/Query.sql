select count(Videos.VideoId) as NumberOfVideos, Users.FirstName, Users.LastName
from Videos
inner join Users on Users.UserId = Videos.UserId
group by Videos.UserId, Users.FirstName, Users.LastName
having count(Videos.VideoId) > 1;

select Playlist.Title as PlaylistTitle, Videos.Title as VideoTitle, Videos.UploadTime 
from PlaylistVideo
inner join Videos on Videos.VideoId = PlaylistVideo.VideoId
inner join Playlist on Playlist.PlaylistId = PlaylistVideo.PlaylistId;

select distinct Videos.UploadTime
from Videos
left outer join VideoComment on VideoComment.VideoId = Videos.VideoId
where VideoComment.CommentId is null;

select Users.UserName
from Users
left outer join VideoComment on VideoComment.UserId = Users.UserId
where VideoComment.UserId is null;

select count(*) as NumberOfVideos, Playlist.Title
from PlaylistVideo
inner join Playlist on PlaylistVideo.PlaylistId = Playlist.PlaylistId
group by Playlist.PlaylistId, Playlist.Title
having count(*) > 1;

select count(*) as NumberOfComments, Playlist.Title
from PlaylistVideo
inner join Playlist on Playlist.PlaylistId = PlaylistVideo.PlaylistId
inner join VideoComment on VideoComment.VideoId = PlaylistVideo.VideoId
group by Playlist.PlaylistId, Playlist.Title
having count(*) > 1;

select distinct VideoComment.CreateTime
from VideoComment
where VideoComment.UserId = 1;

select Users.UserName, Users.LastName, Videos.Title
from VideoVote
inner join Users on Users.UserId = VideoVote.UserId
inner join Videos on Videos.VideoId = VideoVote.VideoId
where VideoVote.Vote = 0;

select *
from PlaylistVideo
inner join Videos on PlaylistVideo.VideoId = Videos.VideoId
inner join Playlist on PlaylistVideo.PlaylistId = Playlist.PlaylistId;
