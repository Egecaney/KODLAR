using System;
using System.Runtime.InteropServices;

using NiHandle = System.UInt64;

/*  National Instrument Device Drivers (August 2011)
 *      NI-DAQmx 9.3.5 -> Application Dev Support -> Net Framework 2.0 Language -> Example
 *      Instrument Control -> NI-VISA 5.1 -> Dev Support -> Net Framework 2.0 Language -> Example
 *      Instrument Control -> NI-4882 2.8.1 -> Dev Support -> Net Framework 2.0 Language -> Example
 */
public enum NI8452_DIO_DriverType{
    OpenDrain,
    PushPull
}

public enum NI8452_DIO_Direction{
    Input,
    Output,
}

public enum NI8452_DIO_PortNumber{
    TX_Enable, RX_Enable, Reset, DIO3, DIO4, DIO5, DIO6, DIO7
}

public enum NI8452_DIO_VoltageLevel{
    Low,
    High,
    IncorrectVL
}

namespace NI8452{

    public class NI845x_GeneralFunctions{

        /*
        * These functions call status.
        * Status code      Meaning
        *  Negative        Error       - Function did not perform expected behaviour.
        *  Positive        Warning     - Function execuated, but a condition arose that may require attention.
        *    Zero          Success     - Function completed successfully.
        */

        /* General Devices */
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xOpen(string ResourceName, NiHandle* DeviceHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xClose(NiHandle DeviceHandle);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xSetIoVoltageLevel(NiHandle DeviceHandle, byte VoltageLevel);

        /* Digital Input Output Functions (DIO) */
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioReadLine(NiHandle DeviceHandle, byte PortNumber, byte LineNumber, int* pReadData);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioSetPortLineDirectionMap(NiHandle DeviceHandle, byte DioPort, byte DioMap);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioSetDriverType(NiHandle DeviceHandle, byte DioPort, byte Type);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioWriteLine(NiHandle DeviceHandle, byte PortNumber, byte LineNumber, int WriteData);
        [DllImport("Ni845x.dll")] unsafe public static extern int ni845xDioWritePort(NiHandle DeviceHandle, byte PortNumber, int WriteData);

        static NiHandle deviceHandle = 0;
        const byte DioPort = 0x00;
        byte LineDirectionMap = 0b_1111_1111;

        public bool NI8452_Open(string SourceName){

            int ConnectionCheck;
            unsafe{
                fixed (NiHandle* deviceHandlePtr = &deviceHandle){
                    ConnectionCheck = ni845xOpen(SourceName, deviceHandlePtr);
                }
            }

            if (ConnectionCheck == 0)
                return true;
            else
                return false;

        }

        public bool NI8452_Close(){

            int ConnectionCheck = ni845xClose(deviceHandle);
            if (ConnectionCheck == 0)
                return true;
            else
                return false;

        }

        public bool NI8452_SetIOVoltage(byte VoltageLevel){

            int StatusCheck = ni845xSetIoVoltageLevel(deviceHandle, VoltageLevel);
            if (StatusCheck == 0)
                return true;
            else
                return false;

        }

        public bool NI8452_DIO_SetTypeAndDirection(NI8452_DIO_PortNumber DIOPort, NI8452_DIO_DriverType Type, NI8452_DIO_Direction Map){

            LineDirectionMap &= (byte)(~(0x01 << (int)DIOPort));
            LineDirectionMap |= (byte)((int)Map << (int)DIOPort);
            int StatusCheckType, StatusCheckMap;

            StatusCheckType = ni845xDioSetDriverType(deviceHandle, DioPort, (byte)Type);
            if (StatusCheckType == 0){
                StatusCheckMap = ni845xDioSetPortLineDirectionMap(deviceHandle, DioPort, LineDirectionMap);
                if (StatusCheckMap == 0)
                    return true;
                else
                    return false;
            }
            else
                return false;

        }

        public bool NI8452_DIO_Write(NI8452_DIO_PortNumber DIOPort, NI8452_DIO_VoltageLevel VLevel){

            int StatusCheck = ni845xDioWriteLine(deviceHandle, DioPort, (byte)DIOPort, (int)VLevel);
            if (StatusCheck == 0)
                return true;
            else
                return false;

        }

        public bool NI8452_DIO_AllWrite(NI8452_DIO_VoltageLevel VLevelDIO0, NI8452_DIO_VoltageLevel VLevelDIO1, NI8452_DIO_VoltageLevel VLevelDIO2, NI8452_DIO_VoltageLevel VLevelDIO3,
                                        NI8452_DIO_VoltageLevel VLevelDIO4, NI8452_DIO_VoltageLevel VLevelDIO5, NI8452_DIO_VoltageLevel VLevelDIO6, NI8452_DIO_VoltageLevel VLevelDIO7){

            byte vLevel = (byte)(((int)VLevelDIO0 << 0) | ((int)VLevelDIO1 << 1) | ((int)VLevelDIO2 << 2) | ((int)VLevelDIO3 << 3) |
                                 ((int)VLevelDIO4 << 4) | ((int)VLevelDIO5 << 5) | ((int)VLevelDIO6 << 6) | ((int)VLevelDIO7 << 7));

            int StatusCheck = ni845xDioWritePort(deviceHandle, DioPort, vLevel);
            if (StatusCheck == 0)
                return true;
            else
                return false;

        }

        public NI8452_DIO_VoltageLevel NI8452_DIO_Read(NI8452_DIO_PortNumber DIOPort){

            int DIOValue = 0;
            int StatusCheck;
            unsafe{
                StatusCheck = ni845xDioReadLine(deviceHandle, DioPort, (byte)DIOPort, &DIOValue);   // You can not use the fixed statement to take the address of an already fixed experssion
            }

            if (StatusCheck == 0){
                if (DIOValue == 1)
                    return NI8452_DIO_VoltageLevel.High;
                else if (DIOValue == 0)
                    return NI8452_DIO_VoltageLevel.Low;
                else
                    return NI8452_DIO_VoltageLevel.IncorrectVL;
            }
            else{
                return NI8452_DIO_VoltageLevel.IncorrectVL;
            }
        }

    }
}
