using System;

namespace TestBoardDLL{

    public enum CommunicationMission{
        Stop,
        Transmit,
        Receive,
        Reset
    }

    public enum CommunicationElement{
        I2C,
        SPI2,
        SPI4,
        SPI5
    }

    public class CommunicationItem{

        public CommunicationItem(CommunicationElement port){
            this.Port = port;
            this.Mission = CommunicationMission.Stop;
            this.RegisterAddress = 0;
        }

        public CommunicationElement Port { get; protected set; }

        public CommunicationMission Mission { get; protected set; }

        public byte Message { get; protected set; }

        public byte ReceivedMessage { get; protected set; }

        public UInt16 RegisterAddress { get; protected set; }

        public void SetMessage(byte message){
            this.Message = message;
        }

        public byte GetMessage(){
            return this.Message;
        }

        public void SetReceivedMessage(byte receivedMessage){
            this.ReceivedMessage = receivedMessage;
        }

        public byte GetReceivedMessagee(){
            return this.ReceivedMessage;
        }

        public void SetMission(CommunicationMission mission){
            this.Mission = mission;
        }

        public void SetRegisterAddress(UInt16 registerAddress){
            this.RegisterAddress = registerAddress;
        }

    }

    /*
     * using TestBoardDLL;
     * 
     * TestBoard XXX = new TestBoard();
     *
     * SPI Write:
     *      this.XXX.ChangeSelectedCommunicationElement(CommunicationElement.SPI2);
     *      this.XXX.ChangeSelectedCommunicationMission(CommunicationMission.Transmit);
     *      this.XXX.Control(0, 60);
     * 
     * SPI Read:
     *      this.XXX.ChangeSelectedCommunicationElement(CommunicationElement.SPI2);
     *      this.XXX.ChangeSelectedCommunicationMission(CommunicationMission.Receive);
     *      this.XXX.Control(0);
     *      int receivedData = this.XXX.SPI2.GetReceivedMessage();
     *      
     * IIC Write:
     *      this.XXX.Write_E2prom(registerAddress, data);
     *      
     * IIC Read:
     *      this.XXX.Read_E2prom(registerAddress);
     *      int receivedData = this.XXX.I2C.GetReceivedMessage();
     *      
     * DIO
     *  Set     -> this.XXX.ChangeControlPinState(PinName.DO, PinState.Set)
     *  Reset   -> this.XXX.ChangeControlPinState(PinName.DO, PinState.Reset)
     *      
     */



}
