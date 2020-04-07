using System.Data.SqlClient;
using System.Windows.Forms;

namespace lab1
{
    public static class DbUtils
    {
        private static string GetParameterName(string name)
        {
            return $"@{name}";
        }

        public static bool IsParameterExpected(this SqlCommand command, string parameter)
        {
            return command.CommandText.Contains(parameter);
        }
        
        public static void AddRowValue(this SqlCommand command, DataGridViewRow row, string name)
        {
            var parameterName = GetParameterName(name);
            if (!command.IsParameterExpected(parameterName))
            {
                return;
            }
            
            var cell = row.Cells[name];
            command.Parameters.AddWithValue(name, cell.Value);
        }

        public static void AddRowValues(this SqlCommand command, DataGridViewRow row)
        {
            for (var i = 0; i < row.DataGridView.Columns.Count; i++)
            {
                var name = row.DataGridView.Columns[i].Name;
                command.AddRowValue(row, name);
            }
        }
    }
}
