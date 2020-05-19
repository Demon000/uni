drop procedure if exists select_users_routine;
go

create procedure select_users_routine
as
begin
	begin transaction;
	insert into HistoryEntries (TableName, ActionName, [Time]) values
		('Transactions', 'TRANSACTION_BEGIN_THREAD_2', GetDate());

	select * from Users;
	insert into HistoryEntries (TableName, ActionName, [Time]) values
		('Users', 'USERS_SELECTED', GetDate());

	waitfor delay '00:00:15';
	select * from Users;
	insert into HistoryEntries (TableName, ActionName, [Time]) values
		('Users', 'USERS_SELECTED', GetDate());

	commit transaction;
	insert into HistoryEntries (TableName, ActionName, [Time]) values
		('Transactions', 'TRANSACTION_COMMITTED_THREAD_2', GetDate());
end
go

/*
Dirty read, second thread
Problem: the second thread can read uncommited data
Solution: set transaction isolation level to read commited
*/

/* Broken */
set transaction isolation level read uncommitted;
exec select_users_routine

/* Working */
set transaction isolation level read committed;
exec select_users_routine

/*
Non repeatable read, second thread
Problem: the second thread makes two selects in a row and reads different data for the same rows
Solution: set transaction isolation level to repeatable read
*/

/* Broken */
set transaction isolation level read committed;
exec select_users_routine

/* Working */
set transaction isolation level repeatable read;
begin transaction;
exec select_users_routine

/*
Phantom read, second thread
Problem: the second thread makes two selects in a row and reads new data
Solution: set transaction level to serializable
*/

/* Broken */
set transaction isolation level repeatable read;
exec select_users_routine

/* Working */
set transaction isolation level serializable;
exec select_users_routine

/*
Deadlock, second thread
Problem: resources are changed in a different order, causing statements to lock eachother
Solution: access resources in the same order
*/

/* Broken */
begin transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_BEGIN_THREAD_1', GetDate());

update Videos set Title = 'dirty_read' where VideoId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Videos', 'VIDEO_UPDATED', GetDate());

waitfor delay '00:00:15';

update Users set UserName = 'dirty_read' where UserId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_UPDATED', GetDate());

commit transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_COMMITTED_THREAD_1', GetDate());

/* Working */
begin transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_BEGIN_THREAD_2', GetDate());

update Users set UserName = 'deadlock' where UserId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Users', 'USER_UPDATED_THREAD_2', GetDate());

waitfor delay '00:00:15';

update Videos set Title = 'deadlock' where VideoId = 1;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Videos', 'VIDEO_UPDATED_THREAD_2', GetDate());

commit transaction;
insert into HistoryEntries (TableName, ActionName, [Time]) values
	('Transactions', 'TRANSACTION_COMMITTED_THREAD_2', GetDate());
