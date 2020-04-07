namespace lab1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewUsers = new System.Windows.Forms.DataGridView();
            this.dataGridViewVideos = new System.Windows.Forms.DataGridView();
            this.addVideoButton = new System.Windows.Forms.Button();
            this.updateVideoButton = new System.Windows.Forms.Button();
            this.deleteVideoButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewUsers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewVideos)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewUsers
            // 
            this.dataGridViewUsers.ColumnHeadersHeightSizeMode =
                System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewUsers.Location = new System.Drawing.Point(10, 29);
            this.dataGridViewUsers.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.dataGridViewUsers.MultiSelect = false;
            this.dataGridViewUsers.Name = "dataGridViewUsers";
            this.dataGridViewUsers.RowTemplate.Height = 24;
            this.dataGridViewUsers.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewUsers.Size = new System.Drawing.Size(518, 611);
            this.dataGridViewUsers.TabIndex = 0;
            // 
            // dataGridViewVideos
            // 
            this.dataGridViewVideos.ColumnHeadersHeightSizeMode =
                System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewVideos.Location = new System.Drawing.Point(532, 29);
            this.dataGridViewVideos.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.dataGridViewVideos.MultiSelect = false;
            this.dataGridViewVideos.Name = "dataGridViewVideos";
            this.dataGridViewVideos.RowTemplate.Height = 24;
            this.dataGridViewVideos.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewVideos.Size = new System.Drawing.Size(720, 611);
            this.dataGridViewVideos.TabIndex = 1;
            // 
            // addVideoButton
            // 
            this.addVideoButton.Location = new System.Drawing.Point(882, 642);
            this.addVideoButton.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.addVideoButton.Name = "addVideoButton";
            this.addVideoButton.Size = new System.Drawing.Size(131, 29);
            this.addVideoButton.TabIndex = 2;
            this.addVideoButton.Text = "Add video";
            this.addVideoButton.UseVisualStyleBackColor = true;
            this.addVideoButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // updateVideoButton
            // 
            this.updateVideoButton.Location = new System.Drawing.Point(1017, 642);
            this.updateVideoButton.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.updateVideoButton.Name = "updateVideoButton";
            this.updateVideoButton.Size = new System.Drawing.Size(125, 29);
            this.updateVideoButton.TabIndex = 3;
            this.updateVideoButton.Text = "Update video";
            this.updateVideoButton.UseVisualStyleBackColor = true;
            this.updateVideoButton.Click += new System.EventHandler(this.button2_Click);
            // 
            // deleteVideoButton
            // 
            this.deleteVideoButton.Location = new System.Drawing.Point(1146, 642);
            this.deleteVideoButton.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.deleteVideoButton.Name = "deleteVideoButton";
            this.deleteVideoButton.Size = new System.Drawing.Size(106, 29);
            this.deleteVideoButton.TabIndex = 4;
            this.deleteVideoButton.Text = "Delete video";
            this.deleteVideoButton.UseVisualStyleBackColor = true;
            this.deleteVideoButton.Click += new System.EventHandler(this.button3_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(10, 9);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Users";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(532, 9);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 16);
            this.label2.TabIndex = 6;
            this.label2.Text = "Videos";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1263, 681);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.deleteVideoButton);
            this.Controls.Add(this.updateVideoButton);
            this.Controls.Add(this.addVideoButton);
            this.Controls.Add(this.dataGridViewVideos);
            this.Controls.Add(this.dataGridViewUsers);
            this.Margin = new System.Windows.Forms.Padding(2, 3, 2, 3);
            this.Name = "Form1";
            this.Text = "User Videos";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewUsers)).EndInit();
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewVideos)).EndInit();
            this.ResumeLayout(false);
        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridView dataGridViewVideos;
        private System.Windows.Forms.DataGridView dataGridViewUsers;
        private System.Windows.Forms.Button addVideoButton;
        private System.Windows.Forms.Button updateVideoButton;
        private System.Windows.Forms.Button deleteVideoButton;
    }
}