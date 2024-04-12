namespace First
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
            this.sd = new System.Windows.Forms.TextBox();
            this.welcomeToMyFormLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // sd
            // 
            this.sd.Location = new System.Drawing.Point(182, 42);
            this.sd.Multiline = true;
            this.sd.Name = "sd";
            this.sd.Size = new System.Drawing.Size(172, 81);
            this.sd.TabIndex = 0;
            // 
            // welcomeToMyFormLabel
            // 
            this.welcomeToMyFormLabel.AutoSize = true;
            this.welcomeToMyFormLabel.Location = new System.Drawing.Point(27, 45);
            this.welcomeToMyFormLabel.Name = "welcomeToMyFormLabel";
            this.welcomeToMyFormLabel.Size = new System.Drawing.Size(102, 13);
            this.welcomeToMyFormLabel.TabIndex = 1;
            this.welcomeToMyFormLabel.Text = "WelcomeToMyForm";
            this.welcomeToMyFormLabel.Click += new System.EventHandler(this.label1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.welcomeToMyFormLabel);
            this.Controls.Add(this.sd);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox sd;
        private System.Windows.Forms.Label welcomeToMyFormLabel;
    }
}

