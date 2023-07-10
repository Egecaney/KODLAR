using System;
using System.Runtime.InteropServices;

using NiHandle = System.UInt64;

public enum NI8452_SPI_ChipSelect{
    CS0, CS1, CS2, CS3, CS4, CS5, CS6, CS7
}

public enum NI8452_SPI_ClockPhase{
    FirstEdge,
    SecondEdge
}

public enum NI8452_SPI_ClockPolarity{
    Low,
    High
}

public enum NI8452_SPI_ClockRate{
    Frequency_5MHz  = 5000,
    Frequency_10MHz = 10000,
    Frequency_20MHz = 20000,
    Frequency_25MHz = 25000,
    Frequency_50MHz = 50000,
}

public enum Device1_SPI_Specification{
    ReadBit = 0,
    WriteBit = 1,
    RegisterAddressLength = 1,
    WriteDataLength = 2,
    ReadDataLength = 2,
    RegAddress_WriteDefault = 7,
    RegAddress_ReadIDE = 5,
    WriteNumBitsPerSample = 24,
    ReadNumBitsPerSample = 25
}

public enum Device2_SPI_Specification{
    ReadRegisterCommand = 0x3D,
    RegisterAddressLength = 2,
    WriteDataLength = 6,
    ReadDataLength = 6,
    WriteReadNumBitsPerSample = 60
}

public enum TRModes{
    Standby,
    TX_Mode,
    RX_Mode,
    Sleep
}

namespace NI8452{
    public class NI845x_BasicFunctions{

        /*
         * These functions call status.
         * Status code      Meaning
         *  Negative        Error       - Function did not perform expected behaviour.
         *  Positive        Warning     - Function execuated, but a condition arose that may require attention.
         *    Zero          Success     - Function completed successfully.
         */

        /* Digital Input Output Functions (DIO) */
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioSetPortLineDirectionMap(NiHandle DeviceHandle, byte DioPort, byte DioMap);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioSetDriverType(NiHandle DeviceHandle, byte DioPort, byte Type);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioWritePort(NiHandle DeviceHandle, byte PortNumber, int WriteData);

        /* SPI Basic Functions */
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationOpen(NiHandle* ConfigurationHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationClose(NiHandle ConfigurationHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationSetChipSelect(NiHandle ConfigurationHandle, UInt32 ChipSelect);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationSetClockPhase(NiHandle ConfigurationHandle, Int32 ClockPhase);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationSetClockPolarity(NiHandle ConfigurationHandle, Int32 ClockPolarity);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationSetClockRate(NiHandle ConfigurationHandle, UInt16 ClockRate);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationSetNumBitsPerSample(NiHandle ConfigurationHandle, UInt16 NumBitsPerSample);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationGetChipSelect(NiHandle ConfigurationHandle, UInt32* pChipSelect);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationGetClockPhase(NiHandle ConfigurationHandle, Int32* pClockPhase);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationGetClockPolarity(NiHandle ConfigurationHandle, Int32* pClockPolarity);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationGetClockRate(NiHandle ConfigurationHandle, UInt16* pClockRate);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiConfigurationGetNumBitsPerSample(NiHandle ConfigurationHandle, UInt16* pNumBitsPerSample);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiWriteRead(NiHandle DeviceHandle, NiHandle ConfigurationHandle, UInt32 WriteSize, byte[] WriteData, UInt32* pReadSize, byte[] ReadData);

        static NiHandle deviceHandle = 0;
        static NiHandle configurationHandle = 0;
        const byte DioPort = 0x00;

        public bool Device1_Adjusmtment_TR_Mode(TRModes mode){

            NI8452_DIO_VoltageLevel TX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            NI8452_DIO_VoltageLevel RX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            NI8452_DIO_VoltageLevel Reset_Status = NI8452_DIO_VoltageLevel.High;

            if (mode == TRModes.Standby){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            }
            else if (mode == TRModes.TX_Mode){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.High;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            }
            else if (mode == TRModes.RX_Mode){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.High;
            }
            if (mode == TRModes.Sleep){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.High;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.High;
            }

            byte vLevel = (byte)(((int)TX_Enable_Status << 0) | ((int)RX_Enable_Status << 1) | ((int)Reset_Status << 2));
            byte DirectionMap = 0b_0000_0111;

            if (ni845xDioSetDriverType(deviceHandle, DioPort, (byte)NI8452_DIO_DriverType.PushPull) == 0){
                if (ni845xDioSetPortLineDirectionMap(deviceHandle, DioPort, DirectionMap) == 0)
                {
                    if (ni845xDioWritePort(deviceHandle, DioPort, vLevel) == 0)
                        return true;
                    else
                        return false;
                }
                else
                    return false; 
            }
            else
                return false;

        }

        public bool Device2_Adjusmtment_TR_Mode(TRModes mode){

            NI8452_DIO_VoltageLevel TX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            NI8452_DIO_VoltageLevel RX_Enable_Status = NI8452_DIO_VoltageLevel.Low;

            if (mode == TRModes.Standby){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            }
            else if (mode == TRModes.TX_Mode){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.High;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
            }
            else if (mode == TRModes.RX_Mode){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.Low;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.High;
            }
            if (mode == TRModes.Sleep){
                TX_Enable_Status = NI8452_DIO_VoltageLevel.High;
                RX_Enable_Status = NI8452_DIO_VoltageLevel.High;
            }

            byte vLevel = (byte)(((int)TX_Enable_Status << 0) | ((int)RX_Enable_Status << 1));
            byte DirectionMap = 0b_0000_0111;

            if (ni845xDioSetDriverType(deviceHandle, DioPort, (byte)NI8452_DIO_DriverType.PushPull) == 0){
                if (ni845xDioSetPortLineDirectionMap(deviceHandle, DioPort, DirectionMap) == 0){
                    if (ni845xDioWritePort(deviceHandle, DioPort, vLevel) == 0)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;

        }

        public bool Devices_Open_SPIConfiguration(){

            int ConfigurationCheck;
            unsafe{
                fixed (NiHandle* configurationHandlePtr = &configurationHandle){
                    ConfigurationCheck = ni845xSpiConfigurationOpen(configurationHandlePtr);
                }
            }

            if (ConfigurationCheck == 0)
                return true;
            else
                return false;

        }

        public bool Devices_Close_SPIConfiguration(){

            int ConfigurationCheck = ni845xSpiConfigurationClose(configurationHandle);
            if (ConfigurationCheck == 0)
                return true;
            else
                return false;

        }

        public bool Device1_SPI_SetConfiguration(NI8452_SPI_ClockPolarity polarity, NI8452_SPI_ClockPhase phase, NI8452_SPI_ClockRate frequency, NI8452_SPI_ChipSelect chipSelect){

            int OpenCheck, PolarityCheck, PhaseCheck, FrequencyCheck, ChipSelectCheck, NumBitsPerSampleCheck;

            unsafe{
                fixed (NiHandle* configurationHandlePtr = &configurationHandle){
                    OpenCheck = ni845xSpiConfigurationOpen(configurationHandlePtr);
                }
            }

            if(OpenCheck == 0){
                PolarityCheck = ni845xSpiConfigurationSetClockPolarity(configurationHandle, (Int32)polarity);
                if(PolarityCheck == 0){
                    PhaseCheck = ni845xSpiConfigurationSetClockPhase(configurationHandle, (Int32)phase);
                    if (PhaseCheck == 0){
                        FrequencyCheck = ni845xSpiConfigurationSetClockRate(configurationHandle, (UInt16)frequency);
                        if (FrequencyCheck == 0){
                            ChipSelectCheck = ni845xSpiConfigurationSetChipSelect(configurationHandle, (UInt32)chipSelect);
                            if (ChipSelectCheck == 0){
                                NumBitsPerSampleCheck = ni845xSpiConfigurationSetNumBitsPerSample(configurationHandle, (UInt16)Device1_SPI_Specification.WriteNumBitsPerSample);
                                if (NumBitsPerSampleCheck == 0)
                                    return true;
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;

        }

        public bool Device2_SPI_SetConfiguration(NI8452_SPI_ClockPolarity polarity, NI8452_SPI_ClockPhase phase, NI8452_SPI_ClockRate frequency, NI8452_SPI_ChipSelect chipSelect){

            int OpenCheck, PolarityCheck, PhaseCheck, FrequencyCheck, ChipSelectCheck, NumBitsPerSampleCheck;

            unsafe{
                fixed (NiHandle* configurationHandlePtr = &configurationHandle){
                    OpenCheck = ni845xSpiConfigurationOpen(configurationHandlePtr);
                }
            }

            if (OpenCheck == 0){
                PolarityCheck = ni845xSpiConfigurationSetClockPolarity(configurationHandle, (Int32)polarity);
                if (PolarityCheck == 0){
                    PhaseCheck = ni845xSpiConfigurationSetClockPhase(configurationHandle, (Int32)phase);
                    if (PhaseCheck == 0){
                        FrequencyCheck = ni845xSpiConfigurationSetClockRate(configurationHandle, (UInt16)frequency);
                        if (FrequencyCheck == 0){
                            ChipSelectCheck = ni845xSpiConfigurationSetChipSelect(configurationHandle, (UInt32)chipSelect);
                            if (ChipSelectCheck == 0){
                                NumBitsPerSampleCheck = ni845xSpiConfigurationSetNumBitsPerSample(configurationHandle, (UInt16)Device2_SPI_Specification.WriteReadNumBitsPerSample);
                                if (NumBitsPerSampleCheck == 0)
                                    return true;
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;

        }

        public string Devices_SPI_GetConfiguration(){

            int GetPolarityCheck, GetPhaseCheck, GetFrequencyCheck, GetChipSelectCheck, GetNumberBitsPerSampleCheck;
            string polarityMessage = "---", phaseMessage = "---", frequencyMessage = "---", chipSelectMessage = "---", numberBitsPerSample = "---";

            UInt32 chipSelectValues;
            Int32 polarityValue, phaseValue;
            UInt16 frequencyValue, numberBitPerSampleValue;

            unsafe{
                GetPolarityCheck = ni845xSpiConfigurationGetClockPolarity(configurationHandle, &polarityValue);
                if (GetPolarityCheck == 0){
                    polarityMessage = polarityValue.ToString();
                    GetPhaseCheck = ni845xSpiConfigurationGetClockPhase(configurationHandle, &phaseValue);
                    if (GetPhaseCheck == 0){
                        phaseMessage = phaseValue.ToString();
                        GetFrequencyCheck = ni845xSpiConfigurationGetClockRate(configurationHandle, &frequencyValue);
                        if (GetFrequencyCheck == 0){
                            frequencyMessage = frequencyValue.ToString();
                            GetChipSelectCheck = ni845xSpiConfigurationGetChipSelect(configurationHandle, &chipSelectValues);
                            if (GetChipSelectCheck == 0){
                                chipSelectMessage = chipSelectValues.ToString();
                                GetNumberBitsPerSampleCheck = ni845xSpiConfigurationGetNumBitsPerSample(configurationHandle, &numberBitPerSampleValue);
                                if (GetNumberBitsPerSampleCheck == 0){
                                    numberBitsPerSample = numberBitPerSampleValue.ToString();
                                }
                            }
                        }
                    }
                }
            }

            string FinalMessage = $"Polarity: " + polarityMessage + "\nPhase: " + phaseMessage + "\nFrequency: " + frequencyMessage + "\nChip Select: " + chipSelectMessage + "\nNumber Bits per Sample: " + numberBitsPerSample;
            return FinalMessage;

        }

        public bool Device1_SPI_Write(byte RegisterAddress, UInt16 Data){

            int WriteCheck = 0, NumberBitsPerSampleCheck = 0;
            byte[] WriteData = new byte[3];
            byte[] ReadData = new byte[3];
            UInt16 NumBitsPerSample = (UInt16)Device1_SPI_Specification.WriteNumBitsPerSample;

            WriteData[0] = (byte)(((int)(Device1_SPI_Specification.WriteBit) << 7) | (int)RegisterAddress);
            WriteData[1] = (byte)((Data >> 8) & 0xFF);
            WriteData[2] = (byte)(Data & 0x00FF);

            UInt32 WriteSize = (UInt32)(Device1_SPI_Specification.RegisterAddressLength) + (UInt32)(Device1_SPI_Specification.WriteDataLength);
            UInt32 ReadSize = 0;

            NumberBitsPerSampleCheck = ni845xSpiConfigurationSetNumBitsPerSample(configurationHandle, NumBitsPerSample);
            if (NumberBitsPerSampleCheck == 0){
                unsafe { 
                    WriteCheck = ni845xSpiWriteRead(deviceHandle, configurationHandle, WriteSize, WriteData, &ReadSize, ReadData); 
                }
            }

            if (WriteCheck == 0)
                return true;
            else
                return false;

        }

        public bool Device2_SPI_Write(UInt16 RegisterAddress, byte[] Data){

            int WriteCheck = 0;
            byte[] WriteData = new byte[(int)Device2_SPI_Specification.WriteDataLength + (int)Device2_SPI_Specification.RegisterAddressLength];
            byte[] ReadData = new byte[(int)Device2_SPI_Specification.ReadDataLength + (int)Device2_SPI_Specification.RegisterAddressLength];

            WriteData[0] = (byte)((RegisterAddress & 0x0F00) >> 8);
            WriteData[1] = (byte)(RegisterAddress & 0x00FF);
            for (int Index = 0; Index <= 5; Index++)
                WriteData[Index + 2] = Data[Index];

            UInt32 WriteSize = (UInt32)(Device2_SPI_Specification.WriteDataLength) + (UInt32)(Device2_SPI_Specification.RegisterAddressLength);
            UInt32 ReadSize = 0;

            unsafe{
                WriteCheck = ni845xSpiWriteRead(deviceHandle, configurationHandle, WriteSize, WriteData, &ReadSize, ReadData);
            }
            
            if (WriteCheck == 0)
                return true;
            else
                return false;

        }

        public int Device1_SPI_Read(byte RegisterAddress){

            int ReadCheck = 0, NumberBitsPerSampleCheck = 0;
            int ReturnDataValue;
            byte[] WriteData = new byte[4] {0x00, 0x00, 0x00, 0x00};
            byte[] ReadData = new byte[4];
            UInt16 NumBitsPerSample = (UInt16)Device1_SPI_Specification.ReadNumBitsPerSample;

            WriteData[0] = (byte)(Device1_SPI_Specification.ReadBit);
            WriteData[1] = (byte)((int)RegisterAddress << 1);

            UInt32 WriteSize = (UInt32)(Device1_SPI_Specification.RegisterAddressLength) + (UInt32)(Device1_SPI_Specification.ReadDataLength) + 1;
            UInt32 ReadSize = 0;

            NumberBitsPerSampleCheck = ni845xSpiConfigurationSetNumBitsPerSample(configurationHandle, NumBitsPerSample);
            if (NumberBitsPerSampleCheck == 0){
                unsafe{ ReadCheck = ni845xSpiWriteRead(deviceHandle, configurationHandle, WriteSize, WriteData, &ReadSize, ReadData); }
                if (ReadCheck == 0 && ReadSize == 4){
                        ReturnDataValue = (((((int)ReadData[2]) << 8) | (((int)ReadData[3]))) << 0);
                        return ReturnDataValue;
                }
                else
                    return (-1);
            }
            else
                return (-1);

        }

        public string Device2_SPI_Read(UInt16 RegisterAddress){

            int ReadCheck1 = 0, ReadCheck2 = 0;
            byte[] WriteData = new byte[(int)Device2_SPI_Specification.WriteDataLength + (int)Device2_SPI_Specification.RegisterAddressLength] { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
            byte[] ReadData1 = new byte[(int)Device2_SPI_Specification.ReadDataLength + (int)Device2_SPI_Specification.RegisterAddressLength];
            byte[] ReadData2 = new byte[(int)Device2_SPI_Specification.ReadDataLength + (int)Device2_SPI_Specification.RegisterAddressLength];

            WriteData[1] = (byte)(Device2_SPI_Specification.ReadRegisterCommand);
            WriteData[6] = (byte)((RegisterAddress & 0x0F00) >> 8);
            WriteData[7] = (byte)(RegisterAddress & 0x00FF);

            UInt32 WriteSize = (UInt32)(Device2_SPI_Specification.WriteDataLength) + (UInt32)(Device2_SPI_Specification.RegisterAddressLength);
            UInt32 ReadSize = 0;

            unsafe { 
                ReadCheck1 = ni845xSpiWriteRead(deviceHandle, configurationHandle, WriteSize, WriteData, &ReadSize, ReadData1);
                if(ReadCheck1 ==  0 && ReadSize == ((UInt32)Device2_SPI_Specification.ReadDataLength + (UInt32)Device2_SPI_Specification.RegisterAddressLength)){
                    ReadCheck2 = ni845xSpiWriteRead(deviceHandle, configurationHandle, WriteSize, WriteData, &ReadSize, ReadData2);
                    if (ReadCheck2 == 0 && ReadSize == ((UInt32)Device2_SPI_Specification.ReadDataLength + (UInt32)Device2_SPI_Specification.RegisterAddressLength)){
                        return (ReadData2[0].ToString() + "-" + ReadData2[1].ToString() + "-" + ReadData2[2].ToString() + "-" + ReadData2[3].ToString() + "-" +
                                 ReadData2[4].ToString() + "-" + ReadData2[5].ToString() + "-" + ReadData2[6].ToString() + "-" + ReadData2[7].ToString() + "-");
                    }
                    else
                        return "None";
                }
                else
                    return "None";
            }   
        }

    }
}
