using System;
using System.Threading;
using System.IO.Ports;


namespace TestBoardDLL{

    public enum PinState{
        Reset,
        Set
    }

    public enum PinName{
        D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13
    }

    public enum BoardOperation{
        Control_Discrete,
        Control_I2C,
        Control_SPI,
        Handshake
    }

    public enum HandshakeCode{
        PC_Code = 0xFD00,
        TestBoard_Code = 0xFDAA
    }

    public class TestBoard{

        public TestBoard(){
        }

        public SerialPort SerialPort { get; private set; }
        public byte NumberOfControlPins { get; } = 14;

        public PinState[] ControlPins { get; private set; } = new PinState[14];

        public PinName SelectedControlPin { get; private set; }

        public BoardOperation SelectedBoardOperation { get; private set; }

        public CommunicationElement SelectedCommunicationElement { get; private set; }

        public CommunicationMission SelectedCommunicationMission { get; private set; }

        public CommunicationItem I2C { get; private set; } = new CommunicationItem(CommunicationElement.I2C);
        public CommunicationItem SPI2 { get; private set; } = new CommunicationItem(CommunicationElement.SPI2);
        public CommunicationItem SPI4 { get; private set; } = new CommunicationItem(CommunicationElement.SPI4);
        public CommunicationItem SPI5 { get; private set; } = new CommunicationItem(CommunicationElement.SPI5);

        public byte[] ControlMessage { get; private set; } = new byte[4];
        
        public int ReceivedMessage { get; private set; }

        private bool MessageReceived { get; set; } = false;

        public bool BoardConnected { get; private set; } = false;

        public void InitializeSerialPort(string portName){

            this.SerialPort = new SerialPort(portName, 12000000, Parity.None, 8, StopBits.One){
                WriteTimeout = 500,
                ReadTimeout = 500
            };

            if (this.BoardConnected == true)
                this.CloseSerialPort();

            this.SerialPort.Open();
            this.SerialPort.DataReceived += SerialPort_DataReceived;

            if (this.SerialPort.IsOpen){
                if(HandshakeWithTestBoard() == true)
                    BoardConnected = true;
                else
                    BoardConnected = false;
            }
            else{
                BoardConnected = false;
            }

        }

        public void CloseSerialPort(){
            this.SerialPort.Close();
            BoardConnected = false;
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e){

            byte[] ReceivedBuffer = new byte[128];
            int length = 0;

            if (this.SelectedBoardOperation == BoardOperation.Control_SPI)
                length = 4;
            else if (this.SelectedBoardOperation == BoardOperation.Control_I2C)
                length = 4;
            else if (this.SelectedBoardOperation == BoardOperation.Handshake)
                length = 4;

            if(e.EventType == SerialData.Eof){
                bool ForChecking = SerialPort.IsOpen;
            }
            else{
                this.SerialPort.Read(ReceivedBuffer, 0, length);
                this.ReceivedMessage = 0;

                for (int i = 0; i < length; i++)
                    this.ReceivedMessage += ReceivedBuffer[i] << (8 * i);

                this.MessageReceived = true;

            }

        }

        public bool HandshakeWithTestBoard(){

            ChangeSelectedBoardOperation(BoardOperation.Handshake);
            UpdateMessage();
            this.MessageReceived = false;

            if (this.SerialPort.IsOpen == false)
                this.SerialPort.Open();

            this.SerialPort.Write(this.ControlMessage, 0, this.ControlMessage.Length);

            while (!this.MessageReceived) { }

            if((this.ReceivedMessage & 0x03) != 3)
                return false;

            if(((this.ReceivedMessage >> 2) & 0xFFFF) == (int)HandshakeCode.TestBoard_Code)
                return true;
            else
                return false;

        }

        public void ChangeSelectedBoardOperation(BoardOperation boardOperation){
            this.SelectedBoardOperation = boardOperation;
        }

        public void ChangeSelectedControlPin(PinName pinName){
            this.SelectedControlPin = pinName;
        }

        public void ChangeSelectedCommunicationElement(CommunicationElement communicationElement){
            this.SelectedCommunicationElement = communicationElement;
        }

        public void ChangeSelectedCommuicationMission(CommunicationMission communicationMission){
            this.SelectedCommunicationMission = communicationMission;
        }

        public PinState GetControlPinState(PinName pinName){
            return this.ControlPins[(int)pinName];
        }

        public void ChangeControlPinState(PinName pinName, PinState pinState){

            if (this.ControlPins[(int)pinName] == pinState)
                return;

            ChangeSelectedBoardOperation(BoardOperation.Control_Discrete);
            ChangeSelectedControlPin(pinName);

            this.ControlPins[(int)pinName] = pinState;
            UpdateMessage();

            if (this.SerialPort.IsOpen == false)
                this.SerialPort.Open();

            this.SerialPort.Write(this.ControlMessage, 0, this.ControlMessage.Length);

        }

        public void Reset_SPI(){
            ChangeSelectedCommuicationMission(CommunicationMission.Reset);
            Control_SPI(0, 0);
        }

        public void Control_SPI(UInt16 registerAddress){
            Control_SPI(registerAddress, 0);
        }

        public void Write_E2prom(UInt16 registerAddress, byte data){

            ChangeSelectedBoardOperation(BoardOperation.Control_I2C);
            ChangeSelectedCommunicationElement(CommunicationElement.I2C);
            ChangeSelectedCommuicationMission(CommunicationMission.Transmit);

            this.I2C.SetMission(this.SelectedCommunicationMission);
            this.I2C.SetRegisterAddress(registerAddress);
            this.I2C.SetMessage(data);

            UpdateMessage();
            this.MessageReceived = false;

            if (this.SerialPort.IsOpen == false)
                this.SerialPort.Open();

            this.SerialPort.Write(this.ControlMessage, 0, this.ControlMessage.Length);

        }

        public void Read_E2prom(UInt16 registerAddress, byte data){

            ChangeSelectedBoardOperation(BoardOperation.Control_I2C);
            ChangeSelectedCommunicationElement(CommunicationElement.I2C);
            ChangeSelectedCommuicationMission(CommunicationMission.Receive);

            this.I2C.SetMission(this.SelectedCommunicationMission);
            this.I2C.SetRegisterAddress(registerAddress);

            UpdateMessage();
            this.MessageReceived = false;

            if (this.SerialPort.IsOpen == false)
                this.SerialPort.Open();

            this.SerialPort.Write(this.ControlMessage, 0, this.ControlMessage.Length);

            while (!this.MessageReceived) { }

            if ((this.ReceivedMessage & 0x03) != 2)
                return;

            if(((this.ReceivedMessage >> 8) & 0xFFFF) == this.I2C.RegisterAddress){
                this.I2C.SetReceivedMessage((byte)((this.ReceivedMessage >> 24) & 0xFF));
            }

        }

        public void Control_SPI(UInt16 registerAddress, byte data){
            ChangeSelectedBoardOperation(BoardOperation.Control_SPI);

            if (SelectedCommunicationElement == CommunicationElement.SPI2){

                this.SPI2.SetMission(this.SelectedCommunicationMission);
                this.SPI2.SetRegisterAddress(registerAddress);

                if(this.SPI2.Mission == CommunicationMission.Transmit)
                    this.SPI2.SetMessage(data);

            }
            else if (SelectedCommunicationElement == CommunicationElement.SPI4){

                this.SPI4.SetMission(this.SelectedCommunicationMission);
                this.SPI4.SetRegisterAddress(registerAddress);

                if (this.SPI4.Mission == CommunicationMission.Transmit)
                    this.SPI4.SetMessage(data);

            }
            else if (SelectedCommunicationElement == CommunicationElement.SPI5){

                this.SPI5.SetMission(this.SelectedCommunicationMission);
                this.SPI5.SetRegisterAddress(registerAddress);

                if (this.SPI5.Mission == CommunicationMission.Transmit)
                    this.SPI5.SetMessage(data);

            }

            UpdateMessage();
            this.MessageReceived = false;

            if (this.SerialPort.IsOpen == false)
                this.SerialPort.Open();

            this.SerialPort.Write(this.ControlMessage, 0, this.ControlMessage.Length);

            if(this.SelectedCommunicationMission == CommunicationMission.Receive){
               
                while (!MessageReceived) { }

                if ((this.ReceivedMessage & 0x3) != 1)
                    return;

                if((SelectedCommunicationElement == CommunicationElement.SPI2) && (((this.ReceivedMessage >>2) & 0x3) == 0)){
                    if (((this.ReceivedMessage >> 14) & 0x3FF) == this.SPI2.RegisterAddress){
                        this.SPI2.SetReceivedMessage((byte)((this.ReceivedMessage >> 24) & 0xFF));
                    }
                }
                else if ((SelectedCommunicationElement == CommunicationElement.SPI4) && (((this.ReceivedMessage >> 2) & 0x3) == 1)){
                    if (((this.ReceivedMessage >> 14) & 0x3FF) == this.SPI4.RegisterAddress){
                        this.SPI4.SetReceivedMessage((byte)((this.ReceivedMessage >> 24) & 0xFF));
                    }
                }
                else if ((SelectedCommunicationElement == CommunicationElement.SPI5) && (((this.ReceivedMessage >> 2) & 0x3) == 2)){
                    if (((this.ReceivedMessage >> 14) & 0x3FF) == this.SPI5.RegisterAddress){
                        this.SPI5.SetReceivedMessage((byte)((this.ReceivedMessage >> 24) & 0xFF));
                    }
                }

            }

        }

        public void UpdateMessage(){

            int tempMessage = 0;
            int parityBitControl = 0;

            Array.Clear(this.ControlMessage, 0, this.ControlMessage.Length);

            if(this.SelectedBoardOperation == BoardOperation.Control_Discrete){
                tempMessage |= 0x00 << 0;

                if (this.ControlPins[(int)this.SelectedControlPin] == PinState.Reset)
                    tempMessage |= 0x00 << 2;
                else if (this.ControlPins[(int)this.SelectedControlPin] == PinState.Set)
                    tempMessage |= 0x01 << 2;

                tempMessage |= (byte)((int)this.SelectedControlPin << 3);
            }
            else if(this.SelectedBoardOperation == BoardOperation.Control_SPI){
                tempMessage |= 0x01 << 0;

                if(this.SelectedCommunicationElement == CommunicationElement.SPI2){
                    tempMessage |= 0x00 << 2;

                    if(this.SPI2.Mission == CommunicationMission.Transmit)
                        tempMessage |= 0x00 << 4;
                    else if (this.SPI2.Mission == CommunicationMission.Receive)
                        tempMessage |= 0x01 << 4;
                    else if (this.SPI2.Mission == CommunicationMission.Reset)
                        tempMessage |= 0x02 << 4;

                    tempMessage |= this.SPI2.RegisterAddress << 14;

                    if (this.SPI2.Mission == CommunicationMission.Receive)
                        tempMessage |= this.SPI2.Message << 24;
                }
                else if (this.SelectedCommunicationElement == CommunicationElement.SPI4){
                    tempMessage |= 0x01 << 2;

                    if (this.SPI4.Mission == CommunicationMission.Transmit)
                        tempMessage |= 0x00 << 4;
                    else if (this.SPI4.Mission == CommunicationMission.Receive)
                        tempMessage |= 0x01 << 4;
                    else if (this.SPI4.Mission == CommunicationMission.Reset)
                        tempMessage |= 0x02 << 4;

                    tempMessage |= this.SPI4.RegisterAddress << 14;

                    if (this.SPI4.Mission == CommunicationMission.Receive)
                        tempMessage |= this.SPI4.Message << 24;
                }
                else if (this.SelectedCommunicationElement == CommunicationElement.SPI5)
                {
                    tempMessage |= 0x02 << 2;

                    if (this.SPI5.Mission == CommunicationMission.Transmit)
                        tempMessage |= 0x00 << 4;
                    else if (this.SPI5.Mission == CommunicationMission.Receive)
                        tempMessage |= 0x01 << 4;
                    else if (this.SPI5.Mission == CommunicationMission.Reset)
                        tempMessage |= 0x02 << 4;

                    tempMessage |= this.SPI5.RegisterAddress << 14;

                    if (this.SPI5.Mission == CommunicationMission.Receive)
                        tempMessage |= this.SPI5.Message << 24;
                }
            }
            else if(this.SelectedBoardOperation == BoardOperation.Control_I2C){
                tempMessage |= 0x02 << 0;

                if (this.SelectedCommunicationElement == CommunicationElement.I2C){

                    if (this.I2C.Mission == CommunicationMission.Transmit)
                        tempMessage |= 0x00 << 2;
                    else if (this.I2C.Mission == CommunicationMission.Receive)
                        tempMessage |= 0x01 << 2;

                    tempMessage |= this.I2C.RegisterAddress << 8;

                    if (this.I2C.Mission == CommunicationMission.Receive)
                        tempMessage |= this.I2C.Message << 24;
                }
            }
            else if(this.SelectedBoardOperation == BoardOperation.Handshake){
                tempMessage |= 0x03 << 0;
                tempMessage |= (int)(HandshakeCode.PC_Code) << 2; 
            }

            for(int i = 0; i < this.ControlMessage.Length * 8; i++){
                if ((tempMessage & (0x1 << i)) != 0)
                    parityBitControl++;
            }

            if(parityBitControl %2 == 1){
                if (this.SelectedBoardOperation == BoardOperation.Control_Discrete)
                    tempMessage |= 0x1 << 7;
                else if (this.SelectedBoardOperation == BoardOperation.Control_SPI)
                    tempMessage |= 0x1 << 6;
                else if (this.SelectedBoardOperation == BoardOperation.Control_I2C)
                    tempMessage |= 0x1 << 3;
                else if (this.SelectedBoardOperation == BoardOperation.Handshake)
                    tempMessage |= 0x1 << 18;
            }

            for(int i = 0; i < this.ControlMessage.Length; i++){
                this.ControlMessage[i] = (byte)((tempMessage >> (8 * i)) & 0xFF);
            }
        }

    }
}
