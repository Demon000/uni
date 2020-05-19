/*
Dirty read, first thread
*/
begin transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_BEGIN_THREAD_1', GetDate());

update Users set UserName = 'dirty_read' where UserId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_UPDATED', GetDate());

waitfor delay '00:00:10';
rollback transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_ROLLBACK_THREAD_1', GetDate());

/*
Non repeatable read, first thread
*/
insert into Users(UserName, Email, FirstName, LastName) values
	('non_repeatable_read', 'example@gmail.com', 'non_repeatable', 'read');
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_ADDED', GetDate());

begin transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_BEGIN_THREAD_1', GetDate());

waitfor delay '00:00:15';
update Users set UserName = 'non_repeatable_read_error' where UserName = 'non_repeatable_read';
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_UPDATED', GetDate());

commit transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_COMMITTED_THREAD_1', GetDate());

/*
Phantom read, first thread
*/
begin transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_BEGIN_THREAD_1', GetDate());

waitfor delay '00:00:15';
insert into Users(UserName, Email, FirstName, LastName) values
	('phantom read', 'example@gmail.com', 'phantom', 'read');
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_ADDED', GetDate());

commit transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_COMMITTED_THREAD_1', GetDate());

/*
Deadlock, first thread
*/
begin transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_BEGIN_THREAD_1', GetDate());
update Users set UserName = 'deadlock' where UserId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_UPDATED_THREAD_1', GetDate());

waitfor delay '00:00:15';

update Videos set Title = 'deadlock' where VideoId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Videos', 'VIDEO_UPDATED_THREAD_1', GetDate());

commit transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_COMMITTED_THREAD_1', GetDate());
