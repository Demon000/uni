using System.Windows.Forms;
using System.Xml.Linq;
using System.Xml.XPath;

namespace lab1
{
    public class MasterDetailConfiguration
    {
        public string ConnectionString { get;  }
        public string MasterAdapterCommand { get; }
        public string DetailAdapterCommand { get; }
        public string MasterTableName { get; }
        public string DetailTableName { get; }
        public string MasterPrimaryKey { get; }
        public string DetailPrimaryKey { get; }
        public string DetailForeignKey { get; }
        public string DataRelationName { get; }
        public string DetailInsertCommandText { get; }
        public string DetailUpdateCommandText { get; }
        public string DetailDeleteCommandText { get; }

        public MasterDetailConfiguration(string connectionString, string masterTableName, string detailTableName,
                string masterPrimaryKey, string detailPrimaryKey, string detailForeignKey,
                string detailInsertCommandText,
                string detailUpdateCommandText,
                string detailDeleteCommandText)
        {
            ConnectionString = connectionString;
            DetailTableName = detailTableName;
            MasterTableName = masterTableName;
            MasterPrimaryKey = masterPrimaryKey;
            DetailPrimaryKey = detailPrimaryKey;
            DetailForeignKey = detailForeignKey;
            DetailUpdateCommandText = detailUpdateCommandText;
            DetailDeleteCommandText = detailDeleteCommandText;
            DetailInsertCommandText = detailInsertCommandText;

            DataRelationName = $"fk_{masterTableName}_{detailTableName}";
            MasterAdapterCommand = $@"
                        select * from {masterTableName};
                    ";
            DetailAdapterCommand = $@"
                        select * from {detailTableName};
                    ";
        }
        
        public static MasterDetailConfiguration ReadFromFile(string path)
        {
            var doc = XDocument.Load(path);
            var connection = doc.Root?.Element("Connection");
            var masterTable = doc.Root?.Element("MasterTable");
            var detailTable = doc.Root?.Element("DetailTable");
            var insert = doc.Root?.Element("Insert");
            var update = doc.Root?.Element("Update");
            var delete = doc.Root?.Element("Delete");
            return new MasterDetailConfiguration(
                    connection.GetAttributeValue("string"),
                    masterTable.GetAttributeValue("name"),
                    detailTable.GetAttributeValue("name"),
                    masterTable.GetAttributeValue("primaryKey"),
                    detailTable.GetAttributeValue("primaryKey"),
                    detailTable.GetAttributeValue("foreignKey"),
                    insert.GetAttributeValue("commandText"),
                    update.GetAttributeValue("commandText"),
                    delete.GetAttributeValue("commandText")
                );
        }
    }
}
