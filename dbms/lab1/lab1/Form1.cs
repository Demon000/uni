using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;

namespace lab1
{
    public partial class Form1 : Form
    {
        // private readonly Dictionary<String, SqlDbType> namesToDbType;
        private readonly MasterDetailConfiguration _configuration;
        private readonly DataSet _dataset;
        private SqlDataAdapter _masterAdapter;
        private SqlDataAdapter _detailAdapter;

        public Form1(MasterDetailConfiguration configuration)
        {
            _configuration = configuration;
            _dataset = new DataSet();

            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (var connection = new SqlConnection(_configuration.ConnectionString))
                {
                    _masterAdapter = new SqlDataAdapter(_configuration.MasterAdapterCommand, connection);
                    _detailAdapter = new SqlDataAdapter(_configuration.DetailAdapterCommand, connection);

                    _masterAdapter.Fill(_dataset, _configuration.MasterTableName);
                    _detailAdapter.Fill(_dataset, _configuration.DetailTableName);

                    var masterBinding = new BindingSource {DataSource = _dataset.Tables[_configuration.MasterTableName]};
                    dataGridViewMaster.DataSource = masterBinding;
                    dataGridViewMaster.AllowUserToAddRows = false;
                    dataGridViewMaster.RowHeadersVisible = false;
                    dataGridViewMaster.ReadOnly = true;
                    dataGridViewMaster.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                    dataGridViewMaster.BackgroundColor = Color.White;

                    var masterPrimaryKeyColumn = _dataset.Tables[_configuration.MasterTableName]
                            .Columns[_configuration.MasterPrimaryKey];
                    var detailForeignKeyColumn = _dataset.Tables[_configuration.DetailTableName]
                            .Columns[_configuration.DetailForeignKey];
                    var userVideosRelation = new DataRelation(_configuration.DataRelationName,
                        masterPrimaryKeyColumn, detailForeignKeyColumn);
                    _dataset.Relations.Add(userVideosRelation);

                    var detailsBinding = new BindingSource {DataSource = masterBinding, DataMember = _configuration.DataRelationName};
                    dataGridViewDetail.DataSource = detailsBinding;
                    dataGridViewDetail.Columns[_configuration.DetailForeignKey].Visible = false;
                    dataGridViewDetail.RowHeadersVisible = false;
                    dataGridViewDetail.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                    dataGridViewDetail.BackgroundColor = Color.White;
                    
                    // _detailAdapter.DeleteCommand = new SqlCommand(_configuration.DetailDeleteCommandString);
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                using (var connection = new SqlConnection(_configuration.ConnectionString))
                using (var deleteCommand = connection.CreateCommand())
                {
                    connection.Open();

                    deleteCommand.CommandText = _configuration.DetailDeleteCommandText;
                    var selectedDetail = dataGridViewDetail.CurrentRow;
                    if (selectedDetail == null)
                    {
                        MessageBox.Show("Please select a detail");
                        return;
                    }

                    var detailId = selectedDetail.Cells[_configuration.DetailPrimaryKey].Value;
                    deleteCommand.AddRowValues(selectedDetail);
                    var deletedRowCount = deleteCommand.ExecuteNonQuery();
                    if (deletedRowCount == 0) return;
                    
                    _dataset.Tables[_configuration.DetailTableName].Clear();
                    _detailAdapter.SelectCommand.Connection = connection;
                    _detailAdapter.Fill(_dataset, _configuration.DetailTableName);
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                using (var connection = new SqlConnection(_configuration.ConnectionString))
                using (var updateCommand = connection.CreateCommand())
                {
                    connection.Open();
                    
                    updateCommand.CommandText = _configuration.DetailUpdateCommandText;
                    var selectedDetail = dataGridViewDetail.CurrentRow;
                    if (selectedDetail == null)
                    {
                        MessageBox.Show("Please select a detail");
                        return;
                    }

                    updateCommand.AddRowValues(selectedDetail);
                    var updateRowCount = updateCommand.ExecuteNonQuery();
                    if (updateRowCount == 0) return;
                    
                    _dataset.Tables[_configuration.DetailTableName].Clear();
                    _detailAdapter.SelectCommand.Connection = connection;
                    _detailAdapter.Fill(_dataset, _configuration.DetailTableName);
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                using (var connection = new SqlConnection(_configuration.ConnectionString))
                using (var insertCommand = connection.CreateCommand())
                {
                    connection.Open();

                    insertCommand.CommandText = _configuration.DetailInsertCommandText;
                    
                    var selectedDetail = dataGridViewDetail.CurrentRow;
                    if (selectedDetail == null)
                    {
                        MessageBox.Show("Please select a detail");
                        return;
                    }

                    insertCommand.AddRowValues(selectedDetail);

                    var insertRowCount = insertCommand.ExecuteNonQuery();
                    if (insertRowCount == 0) return;
                    
                    _dataset.Tables[_configuration.DetailTableName].Clear();
                    _detailAdapter.SelectCommand.Connection = connection;
                    _detailAdapter.Fill(_dataset, _configuration.DetailTableName);
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }
    }
}
