using System;
using System.Runtime.InteropServices;

using NiHandle = System.UInt64;

namespace NI8452{
    public class NI845x_ScriptFunctions{

        /*
         * These functions call status.
         * Status code      Meaning
         *  Negative        Error       - Function did not perform expected behaviour.
         *  Positive        Warning     - Function execuated, but a condition arose that may require attention.
         *    Zero          Success     - Function completed successfully.
         */

        /* SPI Basic Functions */
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptOpen(NiHandle* ScriptHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptClose(NiHandle ScriptHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptEnableSPI(NiHandle ScriptHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptDisableSPI(NiHandle ScriptHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptClockPolarityPhase(NiHandle ScriptHandle, int Polarity, int Phase);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptClockRate(NiHandle ScriptHandle, UInt16 ClockRate);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptCSLow(NiHandle ScriptHandle, UInt32 ChipSelectNum);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptCSHigh(NiHandle ScriptHandle, UInt32 ChipSelectNum);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptRun(NiHandle ScriptHandle, NiHandle DeviceHandle, byte PortNumber);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptExtractReadDataSize(NiHandle ScriptHandle, UInt32 ScriptReadIndex, UInt32* pReadDataSize);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptExtractReadData(NiHandle ScriptHandle, UInt32 ScriptReadIndex, byte[] ReadData);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSpiScriptWriteRead(NiHandle DeviceHandle, UInt32 WriteSize, byte[] WriteData, UInt32* pScriptReadIndex);

        static NiHandle deviceHandle = 0;
        static NiHandle scriptHandle = 0;
        const byte DioPort = 0x00;
        NI8452_SPI_ClockPolarity scriptPolarity;
        NI8452_SPI_ClockPhase scriptPhase;
        NI8452_SPI_ClockRate scriptFrequency;

        public bool SPIScript_OpenConfiguration(NI8452_SPI_ClockPolarity polarity, NI8452_SPI_ClockPhase phase, NI8452_SPI_ClockRate frequency){

            int OpenCheck, EnableCheck, PolarityPhaseCheck, FrequencyCheck;

            scriptPolarity = polarity;
            scriptPhase = phase;
            scriptFrequency = frequency;

            unsafe{
                fixed(NiHandle* scriptHandlePtr = &scriptHandle){
                    OpenCheck = ni845xSpiScriptOpen(scriptHandlePtr);
                }
            }

            if (OpenCheck == 0){
                EnableCheck = ni845xSpiScriptEnableSPI(scriptHandle);
                if (EnableCheck == 0){
                    PolarityPhaseCheck = ni845xSpiScriptClockPolarityPhase(scriptHandle, (Int32)polarity, (Int32)phase);
                    if (PolarityPhaseCheck == 0){
                        FrequencyCheck = ni845xSpiScriptClockRate(scriptHandle, (UInt16)frequency);
                        if (FrequencyCheck == 0)
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

        public bool SPIScript_CloseConfiguration(){

            int CloseCheck = ni845xSpiScriptClose(scriptHandle);
            if (CloseCheck == 0)
                return true;
            else
                return false;

        }

        public bool SPIScript_Write(byte RegisterAddress, UInt16 Data, NI8452_SPI_ChipSelect chipSelect){

            int WriteCheck = 0, CSLowCheck = 0, CSHighCheck = 0, DisableCheck = 0, RunCheck = 0, CloseCheck = 0;
            byte[] WriteData = new byte[3] { 0x00, 0x00, 0x00 };

            WriteData[0] = (byte)(((int)(Device1_SPI_Specification.WriteBit) << 7) | (int)RegisterAddress);
            WriteData[1] = (byte)((Data >> 8) & 0xFF);
            WriteData[2] = (byte)(Data & 0xFFFF);

            UInt32 WriteSize = (UInt32)(Device1_SPI_Specification.RegisterAddressLength) + (UInt32)(Device1_SPI_Specification.WriteDataLength);
            UInt32 ScriptReadSize = 0;

            CSLowCheck = ni845xSpiScriptCSLow(scriptHandle, (UInt32)chipSelect);
            if (CSLowCheck == 0){
                unsafe{ WriteCheck = ni845xSpiScriptWriteRead(deviceHandle, WriteSize, WriteData, &ScriptReadSize); }
                if(WriteCheck == 0){
                    CSHighCheck = ni845xSpiScriptCSHigh(scriptHandle, (UInt32)chipSelect);
                    if(CSHighCheck == 0){
                        DisableCheck = ni845xSpiScriptDisableSPI(scriptHandle);
                        if(DisableCheck == 0){
                            RunCheck = ni845xSpiScriptRun(scriptHandle, deviceHandle, DioPort);
                            if(RunCheck == 0){
                                CloseCheck = ni845xSpiScriptClose(scriptHandle);
                                if(CloseCheck == 0){
                                    if (SPIScript_OpenConfiguration(scriptPolarity, scriptPhase, scriptFrequency))
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
            else
                return false;

        }

        public int SPIScript_Read(byte RegisterAddress, NI8452_SPI_ChipSelect chipSelect){

            int WriteCheck = 0, CSLowCheck = 0, CSHighCheck = 0, DisableCheck = 0, RunCheck = 0, ExtraReadDataSizeCheck = 0, ExtraReadDataCheck = 0, CloseCheck = 0;
            byte[] WriteData = new byte[4] { 0x00, 0x00, 0x00, 0x00 };
            byte[] ReadData = new byte[4];

            WriteData[0] = (byte)(((int)(Device1_SPI_Specification.ReadBit) << 7) | (int)RegisterAddress);

            UInt32 WriteSize = (UInt32)(Device1_SPI_Specification.RegisterAddressLength) + (UInt32)(Device1_SPI_Specification.ReadDataLength) + 1;
            UInt32 ReadSize = 0;
            UInt32 ScriptReadIndex = 0;

            CSLowCheck = ni845xSpiScriptCSLow(scriptHandle, (UInt32)chipSelect);
            if (CSLowCheck == 0){
                unsafe { WriteCheck = ni845xSpiScriptWriteRead(deviceHandle, WriteSize, WriteData, &ScriptReadIndex); }
                if (WriteCheck == 0){
                    CSHighCheck = ni845xSpiScriptCSHigh(scriptHandle, (UInt32)chipSelect);
                    if (CSHighCheck == 0){
                        DisableCheck = ni845xSpiScriptDisableSPI(scriptHandle);
                        if (DisableCheck == 0){
                            RunCheck = ni845xSpiScriptRun(scriptHandle, deviceHandle, DioPort);
                            if (RunCheck == 0){
                                unsafe { ExtraReadDataSizeCheck = ni845xSpiScriptExtractReadDataSize(scriptHandle, ScriptReadIndex, &ReadSize); }
                                if(ExtraReadDataSizeCheck == 0){
                                    unsafe { ExtraReadDataCheck = ni845xSpiScriptExtractReadData(scriptHandle, ScriptReadIndex, ReadData); }
                                    if (ExtraReadDataCheck == 0) {
                                        CloseCheck = ni845xSpiScriptClose(scriptHandle);
                                        if (CloseCheck == 0){
                                            if (SPIScript_OpenConfiguration(scriptPolarity, scriptPhase, scriptFrequency)){
                                                if (ReadData[3] == 255)
                                                    return ((((((int)ReadData[1]) << 8) | (((int)ReadData[2]))) << 1) + 1);
                                                else if (ReadData[3] == 0)
                                                    return (((((int)ReadData[1]) << 8) | (((int)ReadData[2]))) << 1);
                                                else
                                                    return (-1);
                                            }
                                            else
                                                return (-1);
                                        }
                                        else
                                            return (-1);
                                    }
                                    else
                                        return (-1);
                                }
                                else
                                    return (-1);
                            }
                            else
                                return (-1);
                        }
                        else
                            return (-1);
                    }
                    else
                        return (-1);
                }
                else
                    return (-1);
            }
            else
                return (-1);

        }

    }
}
