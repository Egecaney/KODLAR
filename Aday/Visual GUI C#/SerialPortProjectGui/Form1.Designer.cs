namespace SerialPortProjectGui
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
            this.components = new System.ComponentModel.Container();
            this.txtSend = new System.Windows.Forms.TextBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.btnClearDataIN = new System.Windows.Forms.Button();
            this.textReceive = new System.Windows.Forms.TextBox();
            this.Send = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox14 = new System.Windows.Forms.GroupBox();
            this.RButtonWrite = new System.Windows.Forms.RadioButton();
            this.RButtonWriteLine = new System.Windows.Forms.RadioButton();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.RButtonUsingButton = new System.Windows.Forms.RadioButton();
            this.RButtonUsingEnter = new System.Windows.Forms.RadioButton();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.lbDataTransmitControl = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lbDataTransmitLength = new System.Windows.Forms.Label();
            this.btnClearDataOut = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.lbDataReceiveLength = new System.Windows.Forms.Label();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.chBoxAlwaysUpdate = new System.Windows.Forms.CheckBox();
            this.chBoxAddtoOldData = new System.Windows.Forms.CheckBox();
            this.buttonConnectClose = new System.Windows.Forms.Button();
            this.buttonConnectOpen = new System.Windows.Forms.Button();
            this.comboBoxPorts = new System.Windows.Forms.ComboBox();
            this.chBoxDtrEnable = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.chBoxRtsEnable = new System.Windows.Forms.CheckBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.lbStatusCom = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxStopBit = new System.Windows.Forms.ComboBox();
            this.comboBoxParityBit = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.comboBoxData = new System.Windows.Forms.ComboBox();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.textBoxI2CRegAdd = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.RButtonI2CWrite = new System.Windows.Forms.RadioButton();
            this.RButtonI2CRead = new System.Windows.Forms.RadioButton();
            this.label11 = new System.Windows.Forms.Label();
            this.comboBoxConnectivityI2C = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.comboBoxI2CDevAdd = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.textBoxSPIRegAdd = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.comboBoxSPIDevAdd = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.comboBoxConnectivitySPI = new System.Windows.Forms.ComboBox();
            this.label13 = new System.Windows.Forms.Label();
            this.comboBoxProtocols = new System.Windows.Forms.ComboBox();
            this.groupBox2.SuspendLayout();
            this.groupBox14.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox13.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtSend
            // 
            this.txtSend.Location = new System.Drawing.Point(56, 33);
            this.txtSend.Multiline = true;
            this.txtSend.Name = "txtSend";
            this.txtSend.Size = new System.Drawing.Size(337, 47);
            this.txtSend.TabIndex = 4;
            this.txtSend.TextChanged += new System.EventHandler(this.txtSend_TextChanged);
            this.txtSend.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtSend_KeyDown);
            // 
            // buttonSend
            // 
            this.buttonSend.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonSend.Location = new System.Drawing.Point(56, 89);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(154, 37);
            this.buttonSend.TabIndex = 5;
            this.buttonSend.Text = "Send Data";
            this.buttonSend.UseVisualStyleBackColor = false;
            this.buttonSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // btnClearDataIN
            // 
            this.btnClearDataIN.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.btnClearDataIN.Location = new System.Drawing.Point(56, 84);
            this.btnClearDataIN.Name = "btnClearDataIN";
            this.btnClearDataIN.Size = new System.Drawing.Size(154, 71);
            this.btnClearDataIN.TabIndex = 7;
            this.btnClearDataIN.Text = "Clear Data IN";
            this.btnClearDataIN.UseVisualStyleBackColor = false;
            this.btnClearDataIN.Click += new System.EventHandler(this.btnClearDataIN_Click);
            // 
            // textReceive
            // 
            this.textReceive.Location = new System.Drawing.Point(56, 27);
            this.textReceive.Multiline = true;
            this.textReceive.Name = "textReceive";
            this.textReceive.Size = new System.Drawing.Size(337, 47);
            this.textReceive.TabIndex = 6;
            // 
            // Send
            // 
            this.Send.AutoSize = true;
            this.Send.ForeColor = System.Drawing.Color.Black;
            this.Send.Location = new System.Drawing.Point(21, 33);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(35, 13);
            this.Send.TabIndex = 8;
            this.Send.Text = "Send:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(6, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Receive:";
            // 
            // serialPort
            // 
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox14);
            this.groupBox2.Controls.Add(this.groupBox5);
            this.groupBox2.Controls.Add(this.groupBox6);
            this.groupBox2.Controls.Add(this.btnClearDataOut);
            this.groupBox2.Controls.Add(this.txtSend);
            this.groupBox2.Controls.Add(this.buttonSend);
            this.groupBox2.Controls.Add(this.Send);
            this.groupBox2.Location = new System.Drawing.Point(301, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(413, 319);
            this.groupBox2.TabIndex = 21;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Transmitter Control";
            // 
            // groupBox14
            // 
            this.groupBox14.Controls.Add(this.RButtonWrite);
            this.groupBox14.Controls.Add(this.RButtonWriteLine);
            this.groupBox14.Location = new System.Drawing.Point(56, 200);
            this.groupBox14.Name = "groupBox14";
            this.groupBox14.Size = new System.Drawing.Size(109, 64);
            this.groupBox14.TabIndex = 24;
            this.groupBox14.TabStop = false;
            // 
            // RButtonWrite
            // 
            this.RButtonWrite.AutoSize = true;
            this.RButtonWrite.Location = new System.Drawing.Point(6, 36);
            this.RButtonWrite.Name = "RButtonWrite";
            this.RButtonWrite.Size = new System.Drawing.Size(50, 17);
            this.RButtonWrite.TabIndex = 23;
            this.RButtonWrite.TabStop = true;
            this.RButtonWrite.Text = "Write";
            this.RButtonWrite.UseVisualStyleBackColor = true;
            this.RButtonWrite.CheckedChanged += new System.EventHandler(this.RButtonWrite_CheckedChanged);
            // 
            // RButtonWriteLine
            // 
            this.RButtonWriteLine.AutoSize = true;
            this.RButtonWriteLine.Location = new System.Drawing.Point(6, 13);
            this.RButtonWriteLine.Name = "RButtonWriteLine";
            this.RButtonWriteLine.Size = new System.Drawing.Size(73, 17);
            this.RButtonWriteLine.TabIndex = 22;
            this.RButtonWriteLine.TabStop = true;
            this.RButtonWriteLine.Text = "Write Line";
            this.RButtonWriteLine.UseVisualStyleBackColor = true;
            this.RButtonWriteLine.CheckedChanged += new System.EventHandler(this.RButtonWriteLine_CheckedChanged);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.RButtonUsingButton);
            this.groupBox5.Controls.Add(this.RButtonUsingEnter);
            this.groupBox5.Location = new System.Drawing.Point(56, 134);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(108, 64);
            this.groupBox5.TabIndex = 23;
            this.groupBox5.TabStop = false;
            // 
            // RButtonUsingButton
            // 
            this.RButtonUsingButton.AutoSize = true;
            this.RButtonUsingButton.Location = new System.Drawing.Point(6, 13);
            this.RButtonUsingButton.Name = "RButtonUsingButton";
            this.RButtonUsingButton.Size = new System.Drawing.Size(86, 17);
            this.RButtonUsingButton.TabIndex = 19;
            this.RButtonUsingButton.TabStop = true;
            this.RButtonUsingButton.Text = "Using Button";
            this.RButtonUsingButton.UseVisualStyleBackColor = true;
            this.RButtonUsingButton.CheckedChanged += new System.EventHandler(this.RButtonUsingButton_CheckedChanged);
            // 
            // RButtonUsingEnter
            // 
            this.RButtonUsingEnter.AutoSize = true;
            this.RButtonUsingEnter.Location = new System.Drawing.Point(6, 36);
            this.RButtonUsingEnter.Name = "RButtonUsingEnter";
            this.RButtonUsingEnter.Size = new System.Drawing.Size(80, 17);
            this.RButtonUsingEnter.TabIndex = 20;
            this.RButtonUsingEnter.TabStop = true;
            this.RButtonUsingEnter.Text = "Using Enter";
            this.RButtonUsingEnter.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.lbDataTransmitControl);
            this.groupBox6.Controls.Add(this.label15);
            this.groupBox6.Controls.Add(this.label7);
            this.groupBox6.Controls.Add(this.lbDataTransmitLength);
            this.groupBox6.Location = new System.Drawing.Point(56, 270);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(338, 38);
            this.groupBox6.TabIndex = 18;
            this.groupBox6.TabStop = false;
            // 
            // lbDataTransmitControl
            // 
            this.lbDataTransmitControl.AutoSize = true;
            this.lbDataTransmitControl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.lbDataTransmitControl.Location = new System.Drawing.Point(270, 14);
            this.lbDataTransmitControl.Name = "lbDataTransmitControl";
            this.lbDataTransmitControl.Size = new System.Drawing.Size(37, 16);
            this.lbDataTransmitControl.TabIndex = 17;
            this.lbDataTransmitControl.Text = "OFF";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(180, 16);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(95, 13);
            this.label15.TabIndex = 16;
            this.label15.Text = "Transmitter Status:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(23, 16);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(95, 13);
            this.label7.TabIndex = 14;
            this.label7.Text = "Data OUT Length:";
            // 
            // lbDataTransmitLength
            // 
            this.lbDataTransmitLength.AutoSize = true;
            this.lbDataTransmitLength.Location = new System.Drawing.Point(124, 16);
            this.lbDataTransmitLength.Name = "lbDataTransmitLength";
            this.lbDataTransmitLength.Size = new System.Drawing.Size(19, 13);
            this.lbDataTransmitLength.TabIndex = 15;
            this.lbDataTransmitLength.Text = "00";
            // 
            // btnClearDataOut
            // 
            this.btnClearDataOut.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.btnClearDataOut.Location = new System.Drawing.Point(239, 89);
            this.btnClearDataOut.Name = "btnClearDataOut";
            this.btnClearDataOut.Size = new System.Drawing.Size(154, 37);
            this.btnClearDataOut.TabIndex = 9;
            this.btnClearDataOut.Text = "Clear Data OUT";
            this.btnClearDataOut.UseVisualStyleBackColor = false;
            this.btnClearDataOut.Click += new System.EventHandler(this.btnClearDataOut_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox9);
            this.groupBox3.Controls.Add(this.groupBox8);
            this.groupBox3.Controls.Add(this.textReceive);
            this.groupBox3.Controls.Add(this.btnClearDataIN);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Location = new System.Drawing.Point(301, 343);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(413, 288);
            this.groupBox3.TabIndex = 22;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Receiver Control";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.label8);
            this.groupBox9.Controls.Add(this.lbDataReceiveLength);
            this.groupBox9.Location = new System.Drawing.Point(56, 227);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(338, 38);
            this.groupBox9.TabIndex = 19;
            this.groupBox9.TabStop = false;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(108, 16);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(83, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Data IN Length:";
            // 
            // lbDataReceiveLength
            // 
            this.lbDataReceiveLength.AutoSize = true;
            this.lbDataReceiveLength.Location = new System.Drawing.Point(209, 16);
            this.lbDataReceiveLength.Name = "lbDataReceiveLength";
            this.lbDataReceiveLength.Size = new System.Drawing.Size(19, 13);
            this.lbDataReceiveLength.TabIndex = 15;
            this.lbDataReceiveLength.Text = "00";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.chBoxAlwaysUpdate);
            this.groupBox8.Controls.Add(this.chBoxAddtoOldData);
            this.groupBox8.Location = new System.Drawing.Point(56, 161);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(109, 60);
            this.groupBox8.TabIndex = 18;
            this.groupBox8.TabStop = false;
            // 
            // chBoxAlwaysUpdate
            // 
            this.chBoxAlwaysUpdate.AutoSize = true;
            this.chBoxAlwaysUpdate.Location = new System.Drawing.Point(6, 13);
            this.chBoxAlwaysUpdate.Name = "chBoxAlwaysUpdate";
            this.chBoxAlwaysUpdate.Size = new System.Drawing.Size(97, 17);
            this.chBoxAlwaysUpdate.TabIndex = 12;
            this.chBoxAlwaysUpdate.Text = "Always Update";
            this.chBoxAlwaysUpdate.UseVisualStyleBackColor = true;
            this.chBoxAlwaysUpdate.CheckedChanged += new System.EventHandler(this.chBoxAlwaysUpdate_CheckedChanged);
            // 
            // chBoxAddtoOldData
            // 
            this.chBoxAddtoOldData.AutoSize = true;
            this.chBoxAddtoOldData.Location = new System.Drawing.Point(6, 36);
            this.chBoxAddtoOldData.Name = "chBoxAddtoOldData";
            this.chBoxAddtoOldData.Size = new System.Drawing.Size(102, 17);
            this.chBoxAddtoOldData.TabIndex = 13;
            this.chBoxAddtoOldData.Text = "Add to Old Data";
            this.chBoxAddtoOldData.UseVisualStyleBackColor = true;
            this.chBoxAddtoOldData.CheckedChanged += new System.EventHandler(this.chBoxAddtoOldData_CheckedChanged);
            // 
            // buttonConnectClose
            // 
            this.buttonConnectClose.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonConnectClose.Location = new System.Drawing.Point(150, 537);
            this.buttonConnectClose.Name = "buttonConnectClose";
            this.buttonConnectClose.Size = new System.Drawing.Size(75, 33);
            this.buttonConnectClose.TabIndex = 3;
            this.buttonConnectClose.Text = "Close";
            this.buttonConnectClose.UseVisualStyleBackColor = false;
            this.buttonConnectClose.Click += new System.EventHandler(this.buttonConnectClose_Click);
            // 
            // buttonConnectOpen
            // 
            this.buttonConnectOpen.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.buttonConnectOpen.Location = new System.Drawing.Point(47, 537);
            this.buttonConnectOpen.Name = "buttonConnectOpen";
            this.buttonConnectOpen.Size = new System.Drawing.Size(79, 33);
            this.buttonConnectOpen.TabIndex = 2;
            this.buttonConnectOpen.Text = "Open";
            this.buttonConnectOpen.UseVisualStyleBackColor = false;
            this.buttonConnectOpen.Click += new System.EventHandler(this.buttonConnectOpen_Click);
            // 
            // comboBoxPorts
            // 
            this.comboBoxPorts.FormattingEnabled = true;
            this.comboBoxPorts.Location = new System.Drawing.Point(118, 41);
            this.comboBoxPorts.Name = "comboBoxPorts";
            this.comboBoxPorts.Size = new System.Drawing.Size(122, 21);
            this.comboBoxPorts.TabIndex = 1;
            // 
            // chBoxDtrEnable
            // 
            this.chBoxDtrEnable.AutoSize = true;
            this.chBoxDtrEnable.Location = new System.Drawing.Point(47, 514);
            this.chBoxDtrEnable.Name = "chBoxDtrEnable";
            this.chBoxDtrEnable.Size = new System.Drawing.Size(85, 17);
            this.chBoxDtrEnable.TabIndex = 18;
            this.chBoxDtrEnable.Text = "DTR Enable";
            this.chBoxDtrEnable.UseVisualStyleBackColor = true;
            this.chBoxDtrEnable.CheckedChanged += new System.EventHandler(this.chBoxDtrEnable_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(45, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Serial Ports:";
            // 
            // chBoxRtsEnable
            // 
            this.chBoxRtsEnable.AutoSize = true;
            this.chBoxRtsEnable.Location = new System.Drawing.Point(150, 514);
            this.chBoxRtsEnable.Name = "chBoxRtsEnable";
            this.chBoxRtsEnable.Size = new System.Drawing.Size(84, 17);
            this.chBoxRtsEnable.TabIndex = 19;
            this.chBoxRtsEnable.Text = "RTS Enable";
            this.chBoxRtsEnable.UseVisualStyleBackColor = true;
            this.chBoxRtsEnable.CheckedChanged += new System.EventHandler(this.chBoxRtsEnable_CheckedChanged);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.lbStatusCom);
            this.groupBox7.Location = new System.Drawing.Point(66, 576);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(138, 38);
            this.groupBox7.TabIndex = 23;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Com Port Status";
            // 
            // lbStatusCom
            // 
            this.lbStatusCom.AutoSize = true;
            this.lbStatusCom.Font = new System.Drawing.Font("Britannic Bold", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbStatusCom.Location = new System.Drawing.Point(47, 16);
            this.lbStatusCom.Name = "lbStatusCom";
            this.lbStatusCom.Size = new System.Drawing.Size(44, 23);
            this.lbStatusCom.TabIndex = 23;
            this.lbStatusCom.Text = "OFF";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.ForeColor = System.Drawing.Color.Black;
            this.label9.Location = new System.Drawing.Point(25, 22);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(83, 13);
            this.label9.TabIndex = 25;
            this.label9.Text = "Serial Protocols:";
            // 
            // groupBox10
            // 
            this.groupBox10.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.groupBox10.Controls.Add(this.comboBoxBaudRate);
            this.groupBox10.Controls.Add(this.label4);
            this.groupBox10.Controls.Add(this.comboBoxStopBit);
            this.groupBox10.Controls.Add(this.comboBoxParityBit);
            this.groupBox10.Controls.Add(this.label5);
            this.groupBox10.Controls.Add(this.label3);
            this.groupBox10.Controls.Add(this.label6);
            this.groupBox10.Controls.Add(this.comboBoxData);
            this.groupBox10.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.groupBox10.Location = new System.Drawing.Point(14, 76);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(238, 137);
            this.groupBox10.TabIndex = 26;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "For UART";
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Items.AddRange(new object[] {
            "600",
            "1200",
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "56000",
            "57600",
            "115200"});
            this.comboBoxBaudRate.Location = new System.Drawing.Point(104, 19);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.Size = new System.Drawing.Size(121, 21);
            this.comboBoxBaudRate.TabIndex = 15;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Black;
            this.label4.Location = new System.Drawing.Point(42, 108);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Stop Bits:";
            // 
            // comboBoxStopBit
            // 
            this.comboBoxStopBit.FormattingEnabled = true;
            this.comboBoxStopBit.Items.AddRange(new object[] {
            "One",
            "One and Half",
            "Two"});
            this.comboBoxStopBit.Location = new System.Drawing.Point(104, 100);
            this.comboBoxStopBit.Name = "comboBoxStopBit";
            this.comboBoxStopBit.Size = new System.Drawing.Size(121, 21);
            this.comboBoxStopBit.TabIndex = 13;
            // 
            // comboBoxParityBit
            // 
            this.comboBoxParityBit.FormattingEnabled = true;
            this.comboBoxParityBit.Items.AddRange(new object[] {
            "None",
            "Odd",
            "Even"});
            this.comboBoxParityBit.Location = new System.Drawing.Point(104, 73);
            this.comboBoxParityBit.Name = "comboBoxParityBit";
            this.comboBoxParityBit.Size = new System.Drawing.Size(121, 21);
            this.comboBoxParityBit.TabIndex = 11;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.Black;
            this.label5.Location = new System.Drawing.Point(36, 27);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(61, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Baud Rate:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Black;
            this.label3.Location = new System.Drawing.Point(43, 81);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Parity Bit:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.Color.Black;
            this.label6.Location = new System.Drawing.Point(61, 54);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 13);
            this.label6.TabIndex = 16;
            this.label6.Text = "Data:";
            // 
            // comboBoxData
            // 
            this.comboBoxData.FormattingEnabled = true;
            this.comboBoxData.Items.AddRange(new object[] {
            "6",
            "7",
            "8"});
            this.comboBoxData.Location = new System.Drawing.Point(104, 46);
            this.comboBoxData.Name = "comboBoxData";
            this.comboBoxData.Size = new System.Drawing.Size(121, 21);
            this.comboBoxData.TabIndex = 17;
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.textBoxI2CRegAdd);
            this.groupBox11.Controls.Add(this.label16);
            this.groupBox11.Controls.Add(this.groupBox13);
            this.groupBox11.Controls.Add(this.label11);
            this.groupBox11.Controls.Add(this.comboBoxConnectivityI2C);
            this.groupBox11.Controls.Add(this.label10);
            this.groupBox11.Controls.Add(this.comboBoxI2CDevAdd);
            this.groupBox11.Location = new System.Drawing.Point(14, 219);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(238, 165);
            this.groupBox11.TabIndex = 27;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "For I2C";
            // 
            // textBoxI2CRegAdd
            // 
            this.textBoxI2CRegAdd.Location = new System.Drawing.Point(104, 78);
            this.textBoxI2CRegAdd.Multiline = true;
            this.textBoxI2CRegAdd.Name = "textBoxI2CRegAdd";
            this.textBoxI2CRegAdd.Size = new System.Drawing.Size(122, 22);
            this.textBoxI2CRegAdd.TabIndex = 27;
            this.textBoxI2CRegAdd.TextChanged += new System.EventHandler(this.textBoxI2CRegAdd_TextChanged);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.ForeColor = System.Drawing.Color.Black;
            this.label16.Location = new System.Drawing.Point(5, 87);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(90, 13);
            this.label16.TabIndex = 26;
            this.label16.Text = "Register Address:";
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.RButtonI2CWrite);
            this.groupBox13.Controls.Add(this.RButtonI2CRead);
            this.groupBox13.Location = new System.Drawing.Point(28, 112);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(191, 46);
            this.groupBox13.TabIndex = 25;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "Read/Write";
            // 
            // RButtonI2CWrite
            // 
            this.RButtonI2CWrite.AutoSize = true;
            this.RButtonI2CWrite.Location = new System.Drawing.Point(105, 19);
            this.RButtonI2CWrite.Name = "RButtonI2CWrite";
            this.RButtonI2CWrite.Size = new System.Drawing.Size(50, 17);
            this.RButtonI2CWrite.TabIndex = 24;
            this.RButtonI2CWrite.TabStop = true;
            this.RButtonI2CWrite.Text = "Write";
            this.RButtonI2CWrite.UseVisualStyleBackColor = true;
            this.RButtonI2CWrite.CheckedChanged += new System.EventHandler(this.RButtonI2CWrite_CheckedChanged);
            // 
            // RButtonI2CRead
            // 
            this.RButtonI2CRead.AutoSize = true;
            this.RButtonI2CRead.Location = new System.Drawing.Point(39, 19);
            this.RButtonI2CRead.Name = "RButtonI2CRead";
            this.RButtonI2CRead.Size = new System.Drawing.Size(51, 17);
            this.RButtonI2CRead.TabIndex = 23;
            this.RButtonI2CRead.TabStop = true;
            this.RButtonI2CRead.Text = "Read";
            this.RButtonI2CRead.UseVisualStyleBackColor = true;
            this.RButtonI2CRead.CheckedChanged += new System.EventHandler(this.RButtonI2CRead_CheckedChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.ForeColor = System.Drawing.Color.Black;
            this.label11.Location = new System.Drawing.Point(26, 22);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(68, 13);
            this.label11.TabIndex = 19;
            this.label11.Text = "Connectivity:";
            // 
            // comboBoxConnectivityI2C
            // 
            this.comboBoxConnectivityI2C.AutoCompleteCustomSource.AddRange(new string[] {
            "I2C1",
            "I2C2",
            "I2C3"});
            this.comboBoxConnectivityI2C.FormattingEnabled = true;
            this.comboBoxConnectivityI2C.Items.AddRange(new object[] {
            "I2C1",
            "I2C2"});
            this.comboBoxConnectivityI2C.Location = new System.Drawing.Point(104, 14);
            this.comboBoxConnectivityI2C.Name = "comboBoxConnectivityI2C";
            this.comboBoxConnectivityI2C.Size = new System.Drawing.Size(121, 21);
            this.comboBoxConnectivityI2C.TabIndex = 18;
            this.comboBoxConnectivityI2C.SelectedIndexChanged += new System.EventHandler(this.comboBoxConnectivityI2C_SelectedIndexChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.ForeColor = System.Drawing.Color.Black;
            this.label10.Location = new System.Drawing.Point(6, 54);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(88, 13);
            this.label10.TabIndex = 17;
            this.label10.Text = " Device Address:";
            // 
            // comboBoxI2CDevAdd
            // 
            this.comboBoxI2CDevAdd.FormattingEnabled = true;
            this.comboBoxI2CDevAdd.Items.AddRange(new object[] {
            "0xEC",
            "0xFF"});
            this.comboBoxI2CDevAdd.Location = new System.Drawing.Point(104, 46);
            this.comboBoxI2CDevAdd.Name = "comboBoxI2CDevAdd";
            this.comboBoxI2CDevAdd.Size = new System.Drawing.Size(121, 21);
            this.comboBoxI2CDevAdd.TabIndex = 16;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox12);
            this.groupBox1.Controls.Add(this.groupBox11);
            this.groupBox1.Controls.Add(this.groupBox10);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.comboBoxProtocols);
            this.groupBox1.Controls.Add(this.groupBox7);
            this.groupBox1.Controls.Add(this.chBoxRtsEnable);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.chBoxDtrEnable);
            this.groupBox1.Controls.Add(this.comboBoxPorts);
            this.groupBox1.Controls.Add(this.buttonConnectOpen);
            this.groupBox1.Controls.Add(this.buttonConnectClose);
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(270, 619);
            this.groupBox1.TabIndex = 20;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Com Port Control";
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.textBoxSPIRegAdd);
            this.groupBox12.Controls.Add(this.label17);
            this.groupBox12.Controls.Add(this.label14);
            this.groupBox12.Controls.Add(this.comboBoxSPIDevAdd);
            this.groupBox12.Controls.Add(this.label12);
            this.groupBox12.Controls.Add(this.comboBoxConnectivitySPI);
            this.groupBox12.Controls.Add(this.label13);
            this.groupBox12.Location = new System.Drawing.Point(14, 390);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(237, 118);
            this.groupBox12.TabIndex = 28;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "For SPI";
            // 
            // textBoxSPIRegAdd
            // 
            this.textBoxSPIRegAdd.Location = new System.Drawing.Point(103, 78);
            this.textBoxSPIRegAdd.Multiline = true;
            this.textBoxSPIRegAdd.Name = "textBoxSPIRegAdd";
            this.textBoxSPIRegAdd.Size = new System.Drawing.Size(122, 22);
            this.textBoxSPIRegAdd.TabIndex = 29;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.ForeColor = System.Drawing.Color.Black;
            this.label17.Location = new System.Drawing.Point(3, 87);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(90, 13);
            this.label17.TabIndex = 27;
            this.label17.Text = "Register Address:";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.ForeColor = System.Drawing.Color.Black;
            this.label14.Location = new System.Drawing.Point(16, 87);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(0, 13);
            this.label14.TabIndex = 24;
            // 
            // comboBoxSPIDevAdd
            // 
            this.comboBoxSPIDevAdd.AutoCompleteCustomSource.AddRange(new string[] {
            "I2C1",
            "I2C2",
            "I2C3"});
            this.comboBoxSPIDevAdd.FormattingEnabled = true;
            this.comboBoxSPIDevAdd.Location = new System.Drawing.Point(103, 49);
            this.comboBoxSPIDevAdd.Name = "comboBoxSPIDevAdd";
            this.comboBoxSPIDevAdd.Size = new System.Drawing.Size(121, 21);
            this.comboBoxSPIDevAdd.TabIndex = 23;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.ForeColor = System.Drawing.Color.Black;
            this.label12.Location = new System.Drawing.Point(6, 57);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(85, 13);
            this.label12.TabIndex = 22;
            this.label12.Text = "Device Address:";
            // 
            // comboBoxConnectivitySPI
            // 
            this.comboBoxConnectivitySPI.AutoCompleteCustomSource.AddRange(new string[] {
            "I2C1",
            "I2C2",
            "I2C3"});
            this.comboBoxConnectivitySPI.FormattingEnabled = true;
            this.comboBoxConnectivitySPI.Items.AddRange(new object[] {
            "SPI1",
            "SPI2"});
            this.comboBoxConnectivitySPI.Location = new System.Drawing.Point(104, 19);
            this.comboBoxConnectivitySPI.Name = "comboBoxConnectivitySPI";
            this.comboBoxConnectivitySPI.Size = new System.Drawing.Size(121, 21);
            this.comboBoxConnectivitySPI.TabIndex = 21;
            this.comboBoxConnectivitySPI.SelectedIndexChanged += new System.EventHandler(this.comboBoxConnectivitySPI_SelectedIndexChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.ForeColor = System.Drawing.Color.Black;
            this.label13.Location = new System.Drawing.Point(26, 27);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(68, 13);
            this.label13.TabIndex = 20;
            this.label13.Text = "Connectivity:";
            // 
            // comboBoxProtocols
            // 
            this.comboBoxProtocols.FormattingEnabled = true;
            this.comboBoxProtocols.Items.AddRange(new object[] {
            "UART",
            "I2C",
            "SPI"});
            this.comboBoxProtocols.Location = new System.Drawing.Point(118, 14);
            this.comboBoxProtocols.Name = "comboBoxProtocols";
            this.comboBoxProtocols.Size = new System.Drawing.Size(121, 21);
            this.comboBoxProtocols.TabIndex = 24;
            this.comboBoxProtocols.SelectedIndexChanged += new System.EventHandler(this.comboBoxProtocols_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.ClientSize = new System.Drawing.Size(722, 638);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox14.ResumeLayout(false);
            this.groupBox14.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox10.ResumeLayout(false);
            this.groupBox10.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.groupBox13.ResumeLayout(false);
            this.groupBox13.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox12.ResumeLayout(false);
            this.groupBox12.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.TextBox txtSend;
        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.Button btnClearDataIN;
        private System.Windows.Forms.TextBox textReceive;
        private System.Windows.Forms.Label Send;
        private System.Windows.Forms.Label label2;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnClearDataOut;
        private System.Windows.Forms.Label lbDataTransmitLength;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.CheckBox chBoxAlwaysUpdate;
        private System.Windows.Forms.CheckBox chBoxAddtoOldData;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label lbDataReceiveLength;
        private System.Windows.Forms.Button buttonConnectClose;
        private System.Windows.Forms.Button buttonConnectOpen;
        private System.Windows.Forms.ComboBox comboBoxPorts;
        private System.Windows.Forms.CheckBox chBoxDtrEnable;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chBoxRtsEnable;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBoxStopBit;
        private System.Windows.Forms.ComboBox comboBoxParityBit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBoxData;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox comboBoxConnectivityI2C;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBoxProtocols;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.ComboBox comboBoxConnectivitySPI;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBox13;
        private System.Windows.Forms.ComboBox comboBoxI2CDevAdd;
        private System.Windows.Forms.ComboBox comboBoxSPIDevAdd;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label lbStatusCom;
        private System.Windows.Forms.RadioButton RButtonI2CRead;
        private System.Windows.Forms.RadioButton RButtonI2CWrite;
        private System.Windows.Forms.RadioButton RButtonUsingEnter;
        private System.Windows.Forms.RadioButton RButtonUsingButton;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox14;
        private System.Windows.Forms.RadioButton RButtonWrite;
        private System.Windows.Forms.RadioButton RButtonWriteLine;
        private System.Windows.Forms.Label lbDataTransmitControl;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox textBoxI2CRegAdd;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBoxSPIRegAdd;
    }
}

