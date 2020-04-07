using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace lab1
{
    public partial class Form1 : Form
    {
        private readonly DataSet _dataset;
        private readonly string _connectionString;
        private SqlDataAdapter _usersAdapter;
        private SqlDataAdapter _videosAdapter;

        public Form1()
        {
            InitializeComponent();
            _dataset = new DataSet();
            _connectionString = "Server=DESKTOP-6A450E7;Database=Youtube;Integrated Security=true";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (var connection = new SqlConnection(_connectionString))
                {
                    _usersAdapter = new SqlDataAdapter
                    (@"
                        select * from Users;
                    ", connection);
                    _videosAdapter = new SqlDataAdapter
                    (@"
                        select * from Videos;
                    ", connection);

                    _usersAdapter.Fill(_dataset, "Users");
                    _videosAdapter.Fill(_dataset, "Videos");

                    var usersBinding = new BindingSource {DataSource = _dataset.Tables["Users"]};
                    dataGridViewUsers.DataSource = usersBinding;
                    dataGridViewUsers.Columns["UserId"].Visible = false;
                    dataGridViewUsers.Columns["FirstName"].DisplayIndex = 0;
                    dataGridViewUsers.Columns["LastName"].DisplayIndex = 1;
                    dataGridViewUsers.Columns["UserName"].DisplayIndex = 2;
                    dataGridViewUsers.Columns["Email"].DisplayIndex = 3;
                    dataGridViewUsers.AllowUserToAddRows = false;
                    dataGridViewUsers.RowHeadersVisible = false;
                    dataGridViewUsers.ReadOnly = true;
                    dataGridViewUsers.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                    dataGridViewUsers.BackgroundColor = Color.White;

                    var usersIdColumn = _dataset.Tables["Users"].Columns["UserId"];
                    var videosUserIdColumn = _dataset.Tables["Videos"].Columns["UserId"];
                    var userVideosRelation = new DataRelation("fk_users_videos",
                        usersIdColumn, videosUserIdColumn);
                    _dataset.Relations.Add(userVideosRelation);

                    var videosBinding = new BindingSource {DataSource = usersBinding, DataMember = "fk_users_videos"};
                    dataGridViewVideos.DataSource = videosBinding;
                    dataGridViewVideos.Columns["UserId"].Visible = false;
                    dataGridViewVideos.Columns["VideoId"].Visible = false;
                    dataGridViewVideos.Columns["Title"].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
                    dataGridViewVideos.Columns["Description"].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
                    dataGridViewVideos.RowHeadersVisible = false;
                    dataGridViewVideos.BackgroundColor = Color.White;

                    dataGridViewVideos.DefaultValuesNeeded +=
                        dataGridViewVideos_DefaultValuesNeeded;
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        private static void dataGridViewVideos_DefaultValuesNeeded(object sender, DataGridViewRowEventArgs e)
        {
            e.Row.Cells["UploadTime"].Value = DateTime.Now.ToShortDateString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                using (var connection = new SqlConnection(_connectionString))
                using (var deleteCommand = connection.CreateCommand())
                {
                    connection.Open();

                    deleteCommand.CommandText =
                        @"
                            delete from Videos where VideoId=@VideoId;
                        ";
                    var selectedVideo = dataGridViewVideos.CurrentRow;
                    if (selectedVideo == null)
                    {
                        MessageBox.Show("Please select a video");
                        return;
                    }

                    var videoId = (int) selectedVideo.Cells["VideoId"].Value;
                    deleteCommand.Parameters.AddWithValue("@VideoId", videoId);
                    var deletedRowCount = deleteCommand.ExecuteNonQuery();
                    if (deletedRowCount == 0) return;
                    
                    _dataset.Tables["Videos"].Clear();
                    _videosAdapter.SelectCommand.Connection = connection;
                    _videosAdapter.Fill(_dataset, "Videos");
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
                using (var connection = new SqlConnection(_connectionString))
                using (var updateCommand = connection.CreateCommand())
                {
                    connection.Open();
                    
                    updateCommand.CommandText =
                        @"
                            update Videos set
                                Title = @Title,
                                [Description] = @Description
	                        where
	                            VideoId = @VideoId and
	                            UserId = @UserId;
                        ";
                    var selectedVideo = dataGridViewVideos.CurrentRow;
                    if (selectedVideo == null)
                    {
                        MessageBox.Show("Please select a video");
                        return;
                    }

                    var videoIdColumn = (int) selectedVideo.Cells["VideoId"].Value;
                    var userIdColumn = (int) selectedVideo.Cells["UserId"].Value;
                    var titleColumn = selectedVideo.Cells["Title"].Value.ToString();
                    var descriptionColumn = selectedVideo.Cells["Description"].Value.ToString();

                    updateCommand.Parameters.AddWithValue("@VideoId", videoIdColumn);
                    updateCommand.Parameters.AddWithValue("@UserId", userIdColumn);
                    updateCommand.Parameters.AddWithValue("@Title", titleColumn);
                    updateCommand.Parameters.AddWithValue("@Description", descriptionColumn);

                    var updateRowCount = updateCommand.ExecuteNonQuery();
                    if (updateRowCount == 0) return;
                    
                    _dataset.Tables["Videos"].Clear();
                    _videosAdapter.SelectCommand.Connection = connection;
                    _videosAdapter.Fill(_dataset, "Videos");
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
                using (var connection = new SqlConnection(_connectionString))
                using (var insertCommand = connection.CreateCommand())
                {
                    connection.Open();

                    insertCommand.CommandText =
                        @"
                    	    insert into Videos (
                    	        UserId,
                    	        Title,
                    	        UploadTime,
                    	        [Description]
                    	    ) values (
                    	        @UserId,
                    	        @Title,
                    	        GetDate(),
                    	        @Description
                    	    );
                        ";
                    var selectedUser = dataGridViewUsers.CurrentRow;
                    if (selectedUser == null)
                    {
                        MessageBox.Show("Please select an user");
                        return;
                    }

                    var selectedVideo = dataGridViewVideos.CurrentRow;
                    if (selectedVideo == null)
                    {
                        MessageBox.Show("Please select a video");
                        return;
                    }

                    var userId = (int) selectedUser.Cells["UserId"].Value;
                    var title = selectedVideo.Cells["Title"].Value.ToString();
                    var description = selectedVideo.Cells["Description"].Value.ToString();

                    insertCommand.Parameters.AddWithValue("@UserId", userId);
                    insertCommand.Parameters.AddWithValue("@Title", title);
                    insertCommand.Parameters.AddWithValue("@Description", description);

                    var insertRowCount = insertCommand.ExecuteNonQuery();
                    if (insertRowCount == 0) return;
                    
                    _dataset.Tables["Videos"].Clear();
                    _videosAdapter.SelectCommand.Connection = connection;
                    _videosAdapter.Fill(_dataset, "Videos");
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }
    }
}
