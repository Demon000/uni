using System;
using System.Windows.Forms;

namespace lab1
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        public static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            // var configuration = MasterDetailConfiguration.ReadFromFile("UserVideos.xml");
            var configuration = MasterDetailConfiguration.ReadFromFile("VideoVotes.xml");
            Application.Run(new Form1(configuration));
        }
    }
}
