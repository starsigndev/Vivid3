﻿namespace TextureTools
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            panel1 = new Panel();
            button3 = new Button();
            button2 = new Button();
            FacePreview = new Panel();
            button1 = new Button();
            label1 = new Label();
            openFileDialog1 = new OpenFileDialog();
            saveFileDialog1 = new SaveFileDialog();
            panel1.SuspendLayout();
            SuspendLayout();
            // 
            // panel1
            // 
            panel1.BorderStyle = BorderStyle.FixedSingle;
            panel1.Controls.Add(button3);
            panel1.Controls.Add(button2);
            panel1.Controls.Add(FacePreview);
            panel1.Controls.Add(button1);
            panel1.Controls.Add(label1);
            panel1.Location = new Point(12, 12);
            panel1.Name = "panel1";
            panel1.Size = new Size(853, 172);
            panel1.TabIndex = 0;
            // 
            // button3
            // 
            button3.Location = new Point(12, 144);
            button3.Name = "button3";
            button3.Size = new Size(125, 23);
            button3.TabIndex = 4;
            button3.Text = "Export";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button2
            // 
            button2.Location = new Point(143, 32);
            button2.Name = "button2";
            button2.Size = new Size(75, 23);
            button2.TabIndex = 3;
            button2.Text = "Cycle";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // FacePreview
            // 
            FacePreview.BorderStyle = BorderStyle.FixedSingle;
            FacePreview.Location = new Point(12, 32);
            FacePreview.Name = "FacePreview";
            FacePreview.Size = new Size(125, 106);
            FacePreview.TabIndex = 2;
            // 
            // button1
            // 
            button1.Location = new Point(3, 3);
            button1.Name = "button1";
            button1.Size = new Size(154, 23);
            button1.TabIndex = 1;
            button1.Text = "Convert To Cubemap";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(392, 0);
            label1.Name = "label1";
            label1.Size = new Size(67, 15);
            label1.TabIndex = 0;
            label1.Text = "Cube Maps";
            // 
            // openFileDialog1
            // 
            openFileDialog1.FileName = "openFileDialog1";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(877, 517);
            Controls.Add(panel1);
            Name = "Form1";
            Text = "V3 - Texture Tools";
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private Panel panel1;
        private Button button1;
        private Label label1;
        private OpenFileDialog openFileDialog1;
        private Button button2;
        private Panel FacePreview;
        private Button button3;
        private SaveFileDialog saveFileDialog1;
    }
}
