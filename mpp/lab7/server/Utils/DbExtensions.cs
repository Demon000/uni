using System.Data.Common;

namespace lab5.utils
{
    public static class DbExtensions
    {
        public static void AddParameterWithValue(this DbCommand command, string parameterName, object parameterValue)
        {
            var parameter = command.CreateParameter();
            parameter.ParameterName = parameterName;
            parameter.Value = parameterValue;
            command.Parameters.Add(parameter);
        }

        public static DbCommand CreateCommand(this DbConnection connection, string commandText)
        {
            var command = connection.CreateCommand();
            command.CommandText = commandText;
            return command;
        }
    }
}
