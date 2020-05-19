using System;
using System.Data.SqlClient;
using System.Threading;

namespace lab4
{
    internal static class Program
    {
        private const string ConnectionString = "Server=DESKTOP-6A450E7;Database=Youtube;Integrated Security=true";
        private const int MaxRetryCount = 5;

        private static void RetryOnDeadlock(Action action)
        {
            var retryCount = MaxRetryCount;
            while (retryCount > 0) 
            {
                try
                {
                    action();
                    break;
                } 
                catch (SqlException exception)
                {
                    if (exception.Number != 1205)
                    {
                        throw; 
                    }
                    
                    retryCount--;
                    
                    PrintForThread($"Action caused deadlock, retrying. Retries left: {retryCount}");

                    if (retryCount == 0) throw;
                }
            }
        }

        private static void UpdateUser(SqlConnection connection, SqlTransaction transaction, int userId, string userName)
        {
            var command = new SqlCommand("update Users set UserName = @UserName where UserId = @UserId;", connection, transaction);
            command.Parameters.AddWithValue("@UserName", userName);
            command.Parameters.AddWithValue("@UserId", userId);
            command.ExecuteNonQuery();
        }

        private static void UpdateVideo(SqlConnection connection, SqlTransaction transaction, int videoId, string title)
        {
            var command = new SqlCommand("update Videos set Title = @Title where VideoId = @VideoId;", connection, transaction);
            command.Parameters.AddWithValue("@Title", title);
            command.Parameters.AddWithValue("@VideoId", videoId);
            command.ExecuteNonQuery();
        }

        private static void PrintForThread(string message)
        {
            Console.WriteLine(Thread.CurrentThread.Name + ": " + message);
        }

        private static void UpdateFirstOrder()
        {
            using var connection = new SqlConnection(ConnectionString);
            connection.Open();
            
            PrintForThread("Opened connection");

            using var transaction = connection.BeginTransaction();
            PrintForThread("Began transaction");

            UpdateUser(connection, transaction, 1, "deadlocked");
            PrintForThread("Updated user");

            Thread.Sleep(15000);
                
            UpdateVideo(connection, transaction, 1, "deadlocked");
            PrintForThread("Updated video");

            transaction.Commit();
            PrintForThread("Committed transaction");
        }

        private static void UpdateSecondOrder()
        {
            using var connection = new SqlConnection(ConnectionString);
            connection.Open();

            PrintForThread("Opened connection");

            using var transaction = connection.BeginTransaction();
            PrintForThread("Began transaction");

            UpdateVideo(connection, transaction, 1, "deadlocked");
            PrintForThread("Updated video");

            Thread.Sleep(15000);
                
            UpdateUser(connection, transaction, 1, "deadlocked");
            PrintForThread("Updated user");

            transaction.Commit();
            PrintForThread("Committed transaction");
        }

        private static void RunBrokenThreads()
        {
            var firstThread = new Thread(UpdateFirstOrder) {Name = "Thread 1"};
            var secondThread = new Thread(UpdateSecondOrder) {Name = "Thread 2"};
            firstThread.Start();
            secondThread.Start();
        }

        private static void RunAvoidedThreads()
        {
            var firstThread = new Thread(() =>
            {
                try
                {
                    RetryOnDeadlock(UpdateFirstOrder);
                }
                catch (SqlException e)
                {
                    Console.WriteLine(e);
                }
            }) {Name = "Thread 1"};
            var secondThread = new Thread(() =>
            {
                try
                {
                    RetryOnDeadlock(UpdateSecondOrder);
                }
                catch (SqlException e)
                {
                    Console.WriteLine(e);
                }
            }) {Name = "Thread 2"};
            firstThread.Start();
            secondThread.Start();
        }
        
        private static void Main(string[] args)
        {
            // RunBrokenThreads();
            RunAvoidedThreads();
        }
    }
}