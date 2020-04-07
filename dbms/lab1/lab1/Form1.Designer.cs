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
            this.dataGridViewMaster = new System.Windows.Forms.DataGridView();
            this.dataGridViewDetail = new System.Windows.Forms.DataGridView();
            this.addDetailButton = new System.Windows.Forms.Button();
            this.updateDetailButton = new System.Windows.Forms.Button();
            this.deleteDetailButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewMaster)).BeginInit();
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewDetail)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewMaster
            // 
            this.dataGridViewMaster.ColumnHeadersHeightSizeMode =
                System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewMaster.Location = new System.Drawing.Point(10, 29);
            this.dataGridViewMaster.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.dataGridViewMaster.MultiSelect = false;
            this.dataGridViewMaster.Name = "dataGridViewMaster";
            this.dataGridViewMaster.RowTemplate.Height = 24;
            this.dataGridViewMaster.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewMaster.Size = new System.Drawing.Size(518, 612);
            this.dataGridViewMaster.TabIndex = 0;
            // 
            // dataGridViewDetail
            // 
            this.dataGridViewDetail.ColumnHeadersHeightSizeMode =
                System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewDetail.Location = new System.Drawing.Point(532, 29);
            this.dataGridViewDetail.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.dataGridViewDetail.MultiSelect = false;
            this.dataGridViewDetail.Name = "dataGridViewDetail";
            this.dataGridViewDetail.RowTemplate.Height = 24;
            this.dataGridViewDetail.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewDetail.Size = new System.Drawing.Size(720, 612);
            this.dataGridViewDetail.TabIndex = 1;
            // 
            // addDetailButton
            // 
            this.addDetailButton.Location = new System.Drawing.Point(882, 642);
            this.addDetailButton.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.addDetailButton.Name = "addDetailButton";
            this.addDetailButton.Size = new System.Drawing.Size(131, 29);
            this.addDetailButton.TabIndex = 2;
            this.addDetailButton.Text = "Add detail";
            this.addDetailButton.UseVisualStyleBackColor = true;
            this.addDetailButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // updateDetailButton
            // 
            this.updateDetailButton.Location = new System.Drawing.Point(1017, 642);
            this.updateDetailButton.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.updateDetailButton.Name = "updateDetailButton";
            this.updateDetailButton.Size = new System.Drawing.Size(125, 29);
            this.updateDetailButton.TabIndex = 3;
            this.updateDetailButton.Text = "Update detail";
            this.updateDetailButton.UseVisualStyleBackColor = true;
            this.updateDetailButton.Click += new System.EventHandler(this.button2_Click);
            // 
            // deleteDetailButton
            // 
            this.deleteDetailButton.Location = new System.Drawing.Point(1146, 642);
            this.deleteDetailButton.Margin = new System.Windows.Forms.Padding(2, 1, 2, 1);
            this.deleteDetailButton.Name = "deleteDetailButton";
            this.deleteDetailButton.Size = new System.Drawing.Size(106, 29);
            this.deleteDetailButton.TabIndex = 4;
            this.deleteDetailButton.Text = "Delete detail";
            this.deleteDetailButton.UseVisualStyleBackColor = true;
            this.deleteDetailButton.Click += new System.EventHandler(this.button3_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(10, 9);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Master";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(532, 9);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 16);
            this.label2.TabIndex = 6;
            this.label2.Text = "Detail";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1263, 681);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.deleteDetailButton);
            this.Controls.Add(this.updateDetailButton);
            this.Controls.Add(this.addDetailButton);
            this.Controls.Add(this.dataGridViewDetail);
            this.Controls.Add(this.dataGridViewMaster);
            this.Margin = new System.Windows.Forms.Padding(2, 3, 2, 3);
            this.Name = "Form1";
            this.Text = "Master Detail";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewMaster)).EndInit();
            ((System.ComponentModel.ISupportInitialize) (this.dataGridViewDetail)).EndInit();
            this.ResumeLayout(false);
        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button deleteDetailButton;
        private System.Windows.Forms.Button updateDetailButton;
        private System.Windows.Forms.Button addDetailButton;
        private System.Windows.Forms.DataGridView dataGridViewMaster;
        private System.Windows.Forms.DataGridView dataGridViewDetail;
    }
}