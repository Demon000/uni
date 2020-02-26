drop table if exists [testruntables];
drop table if exists [testrunviews];
drop table if exists [testruns];
drop table if exists [testtables];
drop table if exists [testviews];
drop table if exists [tests];
drop table if exists [views];
drop table if exists [tables];

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestRunTables_Tables]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testruntables] 
    DROP CONSTRAINT fk_testruntables_tables 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestTables_Tables]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testtables] 
    DROP CONSTRAINT fk_testtables_tables 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestRunTables_TestRuns]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testruntables] 
    DROP CONSTRAINT fk_testruntables_testruns 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestRunViews_TestRuns]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testrunviews] 
    DROP CONSTRAINT fk_testrunviews_testruns 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestTables_Tests]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testtables] 
    DROP CONSTRAINT fk_testtables_tests 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestViews_Tests]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testviews] 
    DROP CONSTRAINT fk_testviews_tests 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestRunViews_Views]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testrunviews] 
    DROP CONSTRAINT fk_testrunviews_views 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[FK_TestViews_Views]') 
                  AND Objectproperty(id, N'IsForeignKey') = 1) 
  ALTER TABLE [testviews] 
    DROP CONSTRAINT fk_testviews_views 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[Tables]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [tables] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[TestRunTables]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [testruntables] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[TestRunViews]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [testrunviews] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[TestRuns]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [testruns] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[TestTables]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [testtables] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[TestViews]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [testviews] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[Tests]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [tests] 

go 

IF EXISTS (SELECT * 
           FROM   dbo.sysobjects 
           WHERE  id = Object_id(N'[Views]') 
                  AND Objectproperty(id, N'IsUserTable') = 1) 
  DROP TABLE [views] 

go 

CREATE TABLE [tables] 
  ( 
     [tableid] [INT] IDENTITY (1, 1) NOT NULL, 
     [name]    [NVARCHAR] (50) COLLATE sql_latin1_general_cp1_ci_as NOT NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [testruntables] 
  ( 
     [testrunid] [INT] NOT NULL, 
     [tableid]   [INT] NOT NULL, 
     [startat]   [DATETIME] NOT NULL, 
     [endat]     [DATETIME] NOT NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [testrunviews] 
  ( 
     [testrunid] [INT] NOT NULL, 
     [viewid]    [INT] NOT NULL, 
     [startat]   [DATETIME] NOT NULL, 
     [endat]     [DATETIME] NOT NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [testruns] 
  ( 
     [testrunid]   [INT] IDENTITY (1, 1) NOT NULL, 
     [description] [NVARCHAR] (2000) COLLATE sql_latin1_general_cp1_ci_as NULL, 
     [startat]     [DATETIME] NULL, 
     [endat]       [DATETIME] NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [testtables] 
  ( 
     [testid]   [INT] NOT NULL, 
     [tableid]  [INT] NOT NULL, 
     [noofrows] [INT] NOT NULL, 
     [position] [INT] NOT NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [testviews] 
  ( 
     [testid] [INT] NOT NULL, 
     [viewid] [INT] NOT NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [tests] 
  ( 
     [testid] [INT] IDENTITY (1, 1) NOT NULL, 
     [name]   [NVARCHAR] (50) COLLATE sql_latin1_general_cp1_ci_as NOT NULL 
  ) 
ON [PRIMARY] 

go 

CREATE TABLE [views] 
  ( 
     [viewid] [INT] IDENTITY (1, 1) NOT NULL, 
     [name]   [NVARCHAR] (50) COLLATE sql_latin1_general_cp1_ci_as NOT NULL 
  ) 
ON [PRIMARY] 

go 

ALTER TABLE [tables] 
  WITH NOCHECK ADD CONSTRAINT [PK_Tables] PRIMARY KEY CLUSTERED ( [tableid] ) ON 
  [PRIMARY] 

go 

ALTER TABLE [testruntables] 
  WITH NOCHECK ADD CONSTRAINT [PK_TestRunTables] PRIMARY KEY CLUSTERED ( 
  [testrunid], [tableid] ) ON [PRIMARY] 

go 

ALTER TABLE [testrunviews] 
  WITH NOCHECK ADD CONSTRAINT [PK_TestRunViews] PRIMARY KEY CLUSTERED ( 
  [testrunid], [viewid] ) ON [PRIMARY] 

go 

ALTER TABLE [testruns] 
  WITH NOCHECK ADD CONSTRAINT [PK_TestRuns] PRIMARY KEY CLUSTERED ( [testrunid] 
  ) ON [PRIMARY] 

go 

ALTER TABLE [testtables] 
  WITH NOCHECK ADD CONSTRAINT [PK_TestTables] PRIMARY KEY CLUSTERED ( [testid], 
  [tableid] ) ON [PRIMARY] 

go 

ALTER TABLE [testviews] 
  WITH NOCHECK ADD CONSTRAINT [PK_TestViews] PRIMARY KEY CLUSTERED ( [testid], 
  [viewid] ) ON [PRIMARY] 

go 

ALTER TABLE [tests] 
  WITH NOCHECK ADD CONSTRAINT [PK_Tests] PRIMARY KEY CLUSTERED ( [testid] ) ON 
  [PRIMARY] 

go 

ALTER TABLE [views] 
  WITH NOCHECK ADD CONSTRAINT [PK_Views] PRIMARY KEY CLUSTERED ( [viewid] ) ON 
  [PRIMARY] 

go 

ALTER TABLE [testruntables] 
  ADD CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY ( [tableid] ) REFERENCES 
  [tables] ( [tableid] ) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT 
  [FK_TestRunTables_TestRuns] FOREIGN KEY ( [testrunid] ) REFERENCES [testruns] 
  ( [testrunid] ) ON DELETE CASCADE ON UPDATE CASCADE 

go 

ALTER TABLE [testrunviews] 
  ADD CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY ( [testrunid] ) 
  REFERENCES [testruns] ( [testrunid] ) ON DELETE CASCADE ON UPDATE CASCADE, 
  CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY ( [viewid] ) REFERENCES [views] 
  ( [viewid] ) ON DELETE CASCADE ON UPDATE CASCADE 

go 

ALTER TABLE [testtables] 
  ADD CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY ( [tableid] ) REFERENCES 
  [tables] ( [tableid] ) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT 
  [FK_TestTables_Tests] FOREIGN KEY ( [testid] ) REFERENCES [tests] ( [testid] ) 
  ON DELETE CASCADE ON UPDATE CASCADE 

go 

ALTER TABLE [testviews] 
  ADD CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY ( [testid] ) REFERENCES 
  [tests] ( [testid] ), CONSTRAINT [FK_TestViews_Views] FOREIGN KEY ( [viewid] ) 
  REFERENCES [views] ( [viewid] ) 

go
