using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SerialPortProjectGui
{
    public partial class Form1 : Form
    {
        private string sendwith;
        private string dataReceive;
        private string dataTransmit;
        private int    dataIntTransmit;
        private string ProtocolSelection;

        private int    Selection_Data_Address;

        private string I2CConnectivity;
        private int    I2CDeviceAddress;
        private string I2CRegisterAddress;
        private int    I2CINTRegisterAddress;
        private bool   I2CControl;
        private bool   I2CReadWriteControl;

        private int    SPIINTRegisterAddress;
        private string SPIRegisterAddress;
        private bool   SPIControl;

        private int    TempDataIntTransmit;
        private bool   DataControl;

        public Form1(){
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e){
            foreach(var seriPort in SerialPort.GetPortNames()){
                comboBoxPorts.Items.Add(seriPort);
            }
            comboBoxPorts.SelectedIndex = 0;

            buttonConnectClose.Enabled = false;
            buttonSend.Enabled = false;
            btnClearDataIN.Enabled = false;

            chBoxDtrEnable.Checked = false;
            serialPort.DtrEnable = false;
            chBoxRtsEnable.Checked = false;
            serialPort.RtsEnable = false;

            buttonSend.Enabled = false;
            RButtonWriteLine.Checked = false;
            RButtonWrite.Checked = false;
            sendwith = "Write";

            chBoxAlwaysUpdate.Checked = false;
            chBoxAddtoOldData.Checked = true;

            #region UART Disconnected
            comboBoxBaudRate.Enabled = false;
            comboBoxData.Enabled = false;
            comboBoxParityBit.Enabled = false;
            comboBoxStopBit.Enabled = false;
            #endregion
            #region I2C Disconnected
            comboBoxConnectivityI2C.Text = "";
            comboBoxConnectivityI2C.Enabled = false;
            comboBoxI2CDevAdd.Text = "";
            comboBoxI2CDevAdd.Enabled = false;
            textBoxI2CRegAdd.Text = "";
            textBoxI2CRegAdd.Enabled = false;
            RButtonI2CRead.Enabled = false;
            RButtonI2CWrite.Enabled = false;
            #endregion
            #region SPI Disconnected
            comboBoxConnectivitySPI.Text = "";
            comboBoxConnectivitySPI.Enabled = false;
            comboBoxSPIDevAdd.Text = "";
            comboBoxSPIDevAdd.Enabled = false;
            textBoxSPIRegAdd.Text = "";
            textBoxSPIRegAdd.Enabled = false;
            #endregion

        }


        private void buttonConnectOpen_Click(object sender, EventArgs e){

            if (ProtocolSelection == "UART"){
                try{ 
                    serialPort.PortName = comboBoxPorts.Text;
                    #region FOR OPEN TO UART
                    serialPort.BaudRate = Convert.ToInt32(comboBoxBaudRate.Text);
                    serialPort.DataBits = Convert.ToInt32(comboBoxData.Text);
                    serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), comboBoxStopBit.Text);
                    serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), comboBoxParityBit.Text);
                    #endregion
                    serialPort.Open();
                }
                catch(Exception ex){
                    MessageBox.Show($"Serial(UART) Port Connection Failed. \n Warning: {ex.Message}", "Problem", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    lbStatusCom.Text = "OFF";
                }
            }
            else if(ProtocolSelection == "I2C"){
                serialPort.BaudRate = 115200;
                // This region is depended on the whatever you choose. Connectivity and Device Address is related each other. We can combine the these two specifications due to the device.
                I2CConnectivity = comboBoxConnectivityI2C.Text;
                I2CDeviceAddress = Convert.ToInt32(comboBoxI2CDevAdd.Text,16);

                if (comboBoxConnectivityI2C.Text == "I2C2"){
                    I2CRegisterAddress = textBoxI2CRegAdd.Text;
                    if (!(String.IsNullOrEmpty(I2CRegisterAddress))) {
                        I2CINTRegisterAddress = Convert.ToUInt16(I2CRegisterAddress, 16);
                    }
                    else{
                        MessageBox.Show($"(WARNING) I2C Register Address is empty!");
                        lbStatusCom.Text = "OFF";
                    }
                    Selection_Data_Address |= (I2CINTRegisterAddress << 10);
                    Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");
                }               

                #region To Control Connectivity and Device Address
                switch (I2CConnectivity){
                    case "I2C1" when I2CDeviceAddress == 236:
                        I2CControl = true;
                        SPIControl = false;
                        break;
                    case "I2C2" when I2CDeviceAddress == 255:
                        I2CControl = true;
                        SPIControl = false;
                        break;
                    default:
                        I2CControl = false;
                        break;
                }
                #endregion
                // Are the read and write operation selection compose in the INTERFACE?
                #region I2C Control
                if (I2CControl){
                    serialPort.PortName = comboBoxPorts.Text;
                    serialPort.Open();
                }
                else{
                    MessageBox.Show($"Serial(I2C) Port Connection Failed.");
                    lbStatusCom.Text = "OFF";
                }
                #endregion 
            }
            else if(ProtocolSelection == "SPI"){
                serialPort.BaudRate = 115200;
                SPIRegisterAddress = textBoxSPIRegAdd.Text;
                if (!(String.IsNullOrEmpty(SPIRegisterAddress))){
                    SPIINTRegisterAddress = Convert.ToUInt16(SPIRegisterAddress, 16);
                    Selection_Data_Address |= (SPIINTRegisterAddress << 10);
                    SPIControl = true;
                }
                else{
                    MessageBox.Show($"(WARNING) SPI Register Address is empty!");
                    lbStatusCom.Text = "OFF";
                    SPIControl = false;
                }
                Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");

                #region SPI Control
                if (SPIControl){
                    serialPort.PortName = comboBoxPorts.Text;
                    serialPort.Open();
                }
                else{
                    MessageBox.Show($"Serial(SPI) Port Connection Failed.");
                    lbStatusCom.Text = "OFF";
                }
                #endregion

            }
            else
            {
                MessageBox.Show($"Serial Port Connection Failed. \n");
                lbStatusCom.Text = "OFF";
            }
            
            if (serialPort.IsOpen){
                buttonConnectOpen.Enabled = false;
                buttonConnectClose.Enabled = true;
                buttonSend.Enabled = true;
                btnClearDataIN.Enabled = true;
                lbStatusCom.Text = "ON";
            }
        }

        private void buttonConnectClose_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen){
                serialPort.Close();
                buttonConnectOpen.Enabled = true;
                buttonConnectClose.Enabled = false;
                buttonSend.Enabled = false;
                btnClearDataIN.Enabled = false;
                lbStatusCom.Text = "OFF";
                lbDataTransmitControl.Text = "OFF";
            }
        }

        private void btnSend_Click(object sender, EventArgs e){

            byte[] Transmitter;

            if (ProtocolSelection == "UART" || (ProtocolSelection == "I2C" && (I2CReadWriteControl)) || ProtocolSelection == "SPI"){

                dataTransmit = txtSend.Text;
                dataIntTransmit = Convert.ToInt32(dataTransmit,10);
                Selection_Data_Address |= (dataIntTransmit << 2);
                Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}"); 

                /*
                 * Göndereceğim Data 0000 0000 - 1111 1111 arasında olacak.
                 *                        0x00 - 0xFF
                 *                         000 - 255
                 * */

                #region DataControl
                TempDataIntTransmit = dataIntTransmit;
                if(TempDataIntTransmit>= 0 && TempDataIntTransmit <= 255){
                    DataControl = true;
                }
                else{
                    DataControl = false;
                }
                #endregion

                if (DataControl){
                    if (serialPort.IsOpen){

                        if (ProtocolSelection == "UART"){
                            Console.WriteLine("UART");

                            Selection_Data_Address |= (0x80 << 10);
                            Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");
                            Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 10)}");

                            Transmitter = BitConverter.GetBytes(Selection_Data_Address);
                            if (sendwith == "Write"){
                                serialPort.Write(Transmitter,0,3);
                            }

                            lbDataTransmitControl.Text = "ON";
                            Selection_Data_Address &= (0xFF00 << 2);

                        }
                        else if (ProtocolSelection == "I2C"){
                            Console.WriteLine("I2CWrite");

                            if (comboBoxConnectivityI2C.Text == "I2C2"){

                                I2CINTRegisterAddress = Convert.ToUInt16(textBoxI2CRegAdd.Text, 16);
                                Selection_Data_Address |= (I2CINTRegisterAddress << 10);
                                Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");

                                Selection_Data_Address |= 0x03 << 0;
                                Transmitter = BitConverter.GetBytes(Selection_Data_Address);
                                if (sendwith == "Write"){
                                    serialPort.Write(Transmitter, 0, 3);
                                }
                            }
                            lbDataTransmitControl.Text = "ON";
                            Selection_Data_Address &= (0x00003);     // (0000 0000 0000 0000 0011)b  = 0x00003

                        }
                        else if (ProtocolSelection == "SPI"){
                            Console.WriteLine("SPI");
                            Transmitter = BitConverter.GetBytes(Selection_Data_Address);
                            if (sendwith == "Write"){
                                serialPort.Write(Transmitter, 0, 3);
                            }
                            lbDataTransmitControl.Text = "ON";
                            Selection_Data_Address &= (0x00002);     // (0000 0000 0000 0000 0010)b  = 0x00000
                            Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");
                        }
                    }
                }
                else{
                    lbDataTransmitControl.Text = "OFF";
                    MessageBox.Show($"WARNING! Input(With Control Bit) is wrong.");
                    lbStatusCom.Text = "OFF";
                    serialPort.Close();
                    #region Starting Screen
                    buttonConnectOpen.Enabled = true;
                    buttonConnectClose.Enabled = false;
                    buttonSend.Enabled = false;
                    btnClearDataIN.Enabled = false;

                    chBoxDtrEnable.Checked = false;
                    serialPort.DtrEnable = false;
                    chBoxRtsEnable.Checked = false;
                    serialPort.RtsEnable = false;

                    buttonSend.Enabled = false;
                    RButtonWriteLine.Checked = false;
                    RButtonWrite.Checked = false;
                    sendwith = "Write";

                    chBoxAlwaysUpdate.Checked = false;
                    chBoxAddtoOldData.Checked = true;
                    #endregion
                    #region UART Disconnected
                    comboBoxBaudRate.Enabled = false;
                    comboBoxData.Enabled = false;
                    comboBoxParityBit.Enabled = false;
                    comboBoxStopBit.Enabled = false;
                    #endregion
                    #region I2C Disconnected
                    comboBoxConnectivityI2C.Text = "";
                    comboBoxConnectivityI2C.Enabled = false;
                    comboBoxI2CDevAdd.Text = "";
                    comboBoxI2CDevAdd.Enabled = false;
                    textBoxI2CRegAdd.Text = "";
                    textBoxI2CRegAdd.Enabled = false;
                    RButtonI2CRead.Enabled = false;
                    RButtonI2CWrite.Enabled = false;
                    #endregion
                    #region SPI Disconnected
                    comboBoxConnectivitySPI.Text = "";
                    comboBoxConnectivitySPI.Enabled = false;
                    textBoxSPIRegAdd.Text = "";
                    textBoxSPIRegAdd.Enabled = false;
                    #endregion
                }
            }
            else if ((ProtocolSelection == "I2C" && !(I2CReadWriteControl))){
                if (serialPort.IsOpen){
                    Console.WriteLine("I2Read");
                    Transmitter = BitConverter.GetBytes(Selection_Data_Address);
                    if (sendwith == "Write"){
                        serialPort.Write(Transmitter, 0, 3);
                    }
                    lbDataTransmitControl.Text = "ON";
                    Console.WriteLine(Selection_Data_Address);
                }
            }
            else{
                lbDataTransmitControl.Text = "OFF";
                MessageBox.Show($"WARNING! COM PORT is wrong.");
                lbStatusCom.Text = "OFF";
                serialPort.Close();
                #region Starting Screen
                buttonConnectOpen.Enabled = true;
                buttonConnectClose.Enabled = false;
                buttonSend.Enabled = false;
                btnClearDataIN.Enabled = false;

                chBoxDtrEnable.Checked = false;
                serialPort.DtrEnable = false;
                chBoxRtsEnable.Checked = false;
                serialPort.RtsEnable = false;

                buttonSend.Enabled = false;
                RButtonWriteLine.Checked = false;
                RButtonWrite.Checked = false;
                sendwith = "Write";

                chBoxAlwaysUpdate.Checked = false;
                chBoxAddtoOldData.Checked = true;
                #endregion
                #region UART Disconnected
                comboBoxBaudRate.Enabled = false;
                comboBoxData.Enabled = false;
                comboBoxParityBit.Enabled = false;
                comboBoxStopBit.Enabled = false;
                #endregion
                #region I2C Disconnected
                comboBoxConnectivityI2C.Text = "";
                comboBoxConnectivityI2C.Enabled = false;
                comboBoxI2CDevAdd.Text = "";
                comboBoxI2CDevAdd.Enabled = false;
                textBoxI2CRegAdd.Text = "";
                textBoxI2CRegAdd.Enabled = false;
                RButtonI2CRead.Enabled = false;
                RButtonI2CWrite.Enabled = false;
                #endregion
                #region SPI Disconnected
                comboBoxConnectivitySPI.Text = "";
                comboBoxConnectivitySPI.Enabled = false;
                textBoxSPIRegAdd.Text = "";
                textBoxSPIRegAdd.Enabled = false;
                #endregion
            }

            #region Kontrol Amaçlı
            //Console.WriteLine(dataTransmit);
            //Console.WriteLine(dataIntTransmit);
            //Console.WriteLine(I2CReadWriteControl);
            //Console.WriteLine(I2CControl);
            //Console.WriteLine(SPIControl);
            //Console.WriteLine(DataControl);
            #endregion

        }

        private void txtSend_TextChanged(object sender, EventArgs e){
            int DataTransmitLength = txtSend.TextLength;
            lbDataTransmitLength.Text = string.Format("{0:00}", DataTransmitLength);
            if (RButtonUsingEnter.Checked){
                txtSend.Text.Replace(Environment.NewLine, "");
            }
        }

        private void chBoxDtrEnable_CheckedChanged(object sender, EventArgs e){
            if (chBoxDtrEnable.Checked){
                serialPort.DtrEnable = true;
            }
            else{
                serialPort.DtrEnable = false;
            }
        }

        private void chBoxRtsEnable_CheckedChanged(object sender, EventArgs e){
            if (chBoxRtsEnable.Checked){
                serialPort.RtsEnable = true;
            }
            else{
                serialPort.RtsEnable = false;
            }
        }

        private void btnClearDataOut_Click(object sender, EventArgs e){
            if(txtSend.Text != ""){
                txtSend.Text = "";
            }
        }

        private void txtSend_KeyDown(object sender, KeyEventArgs e){
            if (RButtonUsingEnter.Checked){
                if(e.KeyCode  == Keys.Enter){
                    if (serialPort.IsOpen){
                        if (sendwith == "WriteLine"){
                            serialPort.WriteLine(txtSend.Text);
                        }
                        else if (sendwith == "Write"){
                            serialPort.Write(txtSend.Text);
                        }
                    }
                }
            }
        }

        private void RButtonWriteLine_CheckedChanged(object sender, EventArgs e){
            if (RButtonWriteLine.Checked){
                sendwith = "WriteLine";
                RButtonWrite.Checked = false;
                RButtonWriteLine.Checked = true;
            }
        }

        private void RButtonWrite_CheckedChanged(object sender, EventArgs e){
            if (RButtonWrite.Checked){
                sendwith = "Write";
                RButtonWrite.Checked = true;
                RButtonWriteLine.Checked = false;
            }
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e){

            byte[] Bytes = new byte[1];
            if(ProtocolSelection == "I2C" && !(I2CReadWriteControl)){
                dataReceive = serialPort.ReadExisting();
            }
            else if(ProtocolSelection == "UART" || (ProtocolSelection == "I2C" && (I2CReadWriteControl)) || ProtocolSelection == "SPI"){
                dataReceive = serialPort.ReadExisting();
            }
            this.Invoke(new EventHandler(ShowData));
        }

        
        private void ShowData(object sender, EventArgs e){

            int DataReceiveLength;

            if (comboBoxProtocols.Text == "I2C" && comboBoxConnectivityI2C.Text == "I2C1" && !(I2CReadWriteControl)){
                DataReceiveLength = dataReceive.Length;
                lbDataReceiveLength.Text = string.Format("{0:00}", DataReceiveLength);

                if (chBoxAlwaysUpdate.Checked){
                    textReceive.Text = dataReceive;
                }
                else if (chBoxAddtoOldData.Checked){
                    textReceive.Text += dataReceive;
                }
            }
            else if (ProtocolSelection == "UART" || (ProtocolSelection == "I2C" && (I2CReadWriteControl)) || ProtocolSelection == "SPI"){

                if (chBoxAlwaysUpdate.Checked){
                    textReceive.Text = dataReceive;
                }
                else if (chBoxAddtoOldData.Checked){
                    textReceive.Text += dataReceive;
                }
            }     
        }

        private void chBoxAlwaysUpdate_CheckedChanged(object sender, EventArgs e){
            if(chBoxAlwaysUpdate.Checked){
                chBoxAlwaysUpdate.Checked = true;
                chBoxAddtoOldData.Checked = false;
            }
            else{
                chBoxAddtoOldData.Checked = true;
            }
        }

        private void chBoxAddtoOldData_CheckedChanged(object sender, EventArgs e){
            if (chBoxAddtoOldData.Checked){
                chBoxAlwaysUpdate.Checked = false;
                chBoxAddtoOldData.Checked = true;
            }
            else{
                chBoxAlwaysUpdate.Checked = true;
            }
        }

        private void btnClearDataIN_Click(object sender, EventArgs e){
            if(textReceive.Text != ""){
                textReceive.Text = "";
            }
        }

        private void comboBoxProtocols_SelectedIndexChanged(object sender, EventArgs e){
            ProtocolSelection = comboBoxProtocols.Text;
            if (ProtocolSelection == "UART"){
                Selection_Data_Address |= 0x00 << 1;
                Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address,toBase:2)}"); 

                #region UART Connected
                comboBoxBaudRate.Enabled = true;
                comboBoxData.Enabled = true;
                comboBoxParityBit.Enabled = true;
                comboBoxStopBit.Enabled = true;
                #endregion

                #region I2C Disconnected
                comboBoxConnectivityI2C.Text = "";
                comboBoxConnectivityI2C.Enabled = false;
                comboBoxI2CDevAdd.Text = "";
                comboBoxI2CDevAdd.Enabled = false;
                textBoxI2CRegAdd.Text = "";
                textBoxI2CRegAdd.Enabled = false;
                RButtonI2CRead.Checked = false;
                RButtonI2CRead.Enabled = false;
                RButtonI2CWrite.Checked = false;
                RButtonI2CWrite.Enabled = false;
                #endregion

                #region SPI Disconnected
                comboBoxConnectivitySPI.Text = "";
                comboBoxConnectivitySPI.Enabled = false;
                comboBoxSPIDevAdd.Text = "";
                comboBoxSPIDevAdd.Enabled = false;
                textBoxSPIRegAdd.Text = "";
                textBoxSPIRegAdd.Enabled = false;
                #endregion

            }      
            else if(ProtocolSelection == "I2C"){

                #region I2C Connected
                comboBoxConnectivityI2C.Enabled = true;
                comboBoxI2CDevAdd.Enabled = true;
                RButtonI2CRead.Enabled = true;
                RButtonI2CWrite.Enabled = true;
                textBoxI2CRegAdd.Enabled = true;
                #endregion

                #region UART Disconnected
                comboBoxBaudRate.Text = "";
                comboBoxBaudRate.Enabled = false;
                comboBoxData.Text = "";
                comboBoxData.Enabled = false;
                comboBoxParityBit.Text = "";
                comboBoxParityBit.Enabled = false;
                comboBoxStopBit.Text = "";
                comboBoxStopBit.Enabled = false;
                #endregion

                #region SPI Disconnected
                comboBoxConnectivitySPI.Text = "";
                comboBoxConnectivitySPI.Enabled = false;
                comboBoxSPIDevAdd.Text = "";
                comboBoxSPIDevAdd.Enabled = false;
                textBoxSPIRegAdd.Text = "";
                textBoxSPIRegAdd.Enabled = false;
                #endregion
            }
            else if(ProtocolSelection == "SPI"){

                #region SPI Connected
                comboBoxConnectivitySPI.Enabled = true;
                comboBoxSPIDevAdd.Enabled = true;
                textBoxSPIRegAdd.Enabled = true;
                #endregion

                #region UART Disconnected
                comboBoxBaudRate.Text = "";
                comboBoxBaudRate.Enabled = false;
                comboBoxData.Text = "";
                comboBoxData.Enabled = false;
                comboBoxParityBit.Text = "";
                comboBoxParityBit.Enabled = false;
                comboBoxStopBit.Text = "";
                comboBoxStopBit.Enabled = false;
                #endregion

                #region I2C Disconnected
                comboBoxConnectivityI2C.Text = "";
                comboBoxConnectivityI2C.Enabled = false;
                comboBoxI2CDevAdd.Text = "";
                comboBoxI2CDevAdd.Enabled = false;
                textBoxI2CRegAdd.Text = "";
                textBoxI2CRegAdd.Enabled = false;
                RButtonI2CRead.Checked = false;
                RButtonI2CRead.Enabled = false;
                RButtonI2CWrite.Checked = false;
                RButtonI2CWrite.Enabled = false;
                #endregion

            }
        }

        private void RButtonI2CRead_CheckedChanged(object sender, EventArgs e){
            if(RButtonI2CRead.Checked){
                I2CReadWriteControl = true;
            }
        }

        private void RButtonI2CWrite_CheckedChanged(object sender, EventArgs e){
            if (RButtonI2CWrite.Checked){
                I2CReadWriteControl = false;
            }
        }

        private void RButtonUsingButton_CheckedChanged(object sender, EventArgs e){
            if (RButtonUsingButton.Checked){
                buttonSend.Enabled = true;
            }
            else{
                buttonSend.Enabled = false;
            }
        }

        private void comboBoxConnectivityI2C_SelectedIndexChanged(object sender, EventArgs e){
            if (comboBoxProtocols.Text == "I2C"){
                if (comboBoxConnectivityI2C.Text == "I2C1"){
                    comboBoxI2CDevAdd.Text = "0xEC";
                    comboBoxI2CDevAdd.Enabled = false;
                    textBoxI2CRegAdd.Text = "0xD0";
                    textBoxI2CRegAdd.Enabled = false;

                    RButtonI2CWrite.Checked = false;
                    RButtonI2CWrite.Enabled = false;
                    RButtonI2CRead.Checked = true;
                    RButtonI2CRead.Enabled = true;

                    Selection_Data_Address |= 0x01 << 0; 
                    Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");

                    I2CINTRegisterAddress = Convert.ToUInt16(textBoxI2CRegAdd.Text, 16);
                    Selection_Data_Address |= (I2CINTRegisterAddress << 10);
                    Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");

                    I2CControl = true;
                    I2CReadWriteControl = false; // Write Operation
                }
                else if(comboBoxConnectivityI2C.Text == "I2C2"){
                    comboBoxI2CDevAdd.Text = "0xFF";
                    comboBoxI2CDevAdd.Enabled = false;

                    RButtonI2CWrite.Checked = true;
                    RButtonI2CWrite.Enabled = true;
                    RButtonI2CRead.Checked = false;
                    RButtonI2CRead.Enabled = false;

                    textBoxI2CRegAdd.Text = "";
                    textBoxI2CRegAdd.Enabled = true;

                    Selection_Data_Address |= 0x03 << 0;
                    Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");

                    I2CControl = true;
                    SPIControl = false;
                    I2CReadWriteControl = true; // Read Operation
                }
                else{
                    I2CControl = false;
                }
                Console.WriteLine(I2CReadWriteControl);
            }
        }

        private void comboBoxConnectivitySPI_SelectedIndexChanged(object sender, EventArgs e){
            if (comboBoxProtocols.Text == "SPI"){

                Selection_Data_Address |= 0x01 << 1;
                Console.WriteLine($"Selection_Data_Address:{Convert.ToString(Selection_Data_Address, toBase: 2)}");

                if (comboBoxConnectivitySPI.Text == "SPI1"){
                    comboBoxSPIDevAdd.Text = "";
                    comboBoxSPIDevAdd.Enabled = false;
                    textBoxSPIRegAdd.Enabled = true;
                    SPIControl = true;
                    I2CControl = false;
                }
                else{
                    comboBoxSPIDevAdd.Text = "";
                    textBoxSPIRegAdd.Enabled = false;
                    comboBoxSPIDevAdd.Enabled = false;
                    SPIControl = false;
                    MessageBox.Show($"WARNING! SPI2 is not working.");
                }
            }
        }

        private void textBoxI2CRegAdd_TextChanged(object sender, EventArgs e){
            if(comboBoxProtocols.Text == "I2C"){
                if(comboBoxConnectivityI2C.Text == "I2C2"){
                    I2CRegisterAddress = textBoxI2CRegAdd.Text;
                }
            }
        }

        /* String To Binary
        public string ToBin(string input){
          StringBuilder StBuild = new StringBuilder();
          foreach(char L in input.ToCharArray()){
              StBuild.Append(Convert.ToString(L, 2).PadLeft(8, '0'));
          }
          return StBuild.ToString();
        }*/

    }
}
//}