`timescale 1ns / 1ps


module VerilogSlave(
    input       SlaveClock,
    input       SlaveChipSelect,
    input       SlaveDataIn,
    output reg  SlaveDataOut,
    input       ResetButton,
    
    output[3:0] FirstChannel_Spare,
    output      FirstChannel_RxTx,
    output[5:0] FirstChannel_Phase,
    output[4:0] FirstChannel_Gain,
    
    output[3:0] SecondChannel_Spare,
    output      SecondChannel_RxTx,
    output[5:0] SecondChannel_Phase,
    output[4:0] SecondChannel_Gain,
    
    output[3:0] ThirdChannel_Spare,
    output      ThirdChannel_RxTx,
    output[5:0] ThirdChannel_Phase,
    output[4:0] ThirdChannel_Gain,
    
    output[3:0] ForthChannel_Spare,
    output      ForthChannel_RxTx,
    output[5:0] ForthChannel_Phase,
    output[4:0] ForthChannel_Gain,
    
    output[15:0] FifthChannel);
    
    reg[3:0]    FirstChannel_Spare_Reg;
    reg         FirstChannel_RxTx_Reg;
    reg[5:0]    FirstChannel_Phase_Reg;
    reg[4:0]    FirstChannel_Gain_Reg;
    
    reg[3:0]    SecondChannel_Spare_Reg;
    reg         SecondChannel_RxTx_Reg;
    reg[5:0]    SecondChannel_Phase_Reg;
    reg[4:0]    SecondChannel_Gain_Reg;
    
    reg[3:0]    ThirdChannel_Spare_Reg;
    reg         ThirdChannel_RxTx_Reg;
    reg[5:0]    ThirdChannel_Phase_Reg;
    reg[4:0]    ThirdChannel_Gain_Reg;
    
    reg[3:0]    ForthChannel_Spare_Reg;
    reg         ForthChannel_RxTx_Reg;
    reg[5:0]    ForthChannel_Phase_Reg;
    reg[4:0]    ForthChannel_Gain_Reg;
    
    reg[15:0]   FifthChannel_Reg;
    
    localparam  AddressLength       = 7;
    localparam  DataLength          = 16;
    localparam  LoadDefault_Value   = 7'b0000111;
    localparam  ProductID           = 16'b0000010100000000;
    
    localparam  DefaultSpareValue   = 4'b0110;
    localparam  DefaultRxTxValue    = 1'b1;
    localparam  DefaultPhaseValue   = 6'b010101;
    localparam  DefaultGainValue    = 5'b01010;
    localparam  FifthChannelDefaultValue = 16'b0110101010101010; 
    
    wire        SlaveChipSelect_ResetButton;
    assign      SlaveChipSelect_ResetButton = (SlaveChipSelect == 1 || ResetButton == 0) ?1'b1 : 1'b0;       // Active low chip select signal
    
    reg[1:0]    SPI_State;
    localparam  IDLE            = 2'b00;
    localparam  ReadAddress     = 2'b01;
    localparam  ReadWriteData   = 2'b11;
    localparam  NonReach        = 2'b10;
    
    reg                         ReadWriteBuffer;
    reg[AddressLength-1 : 0]    RxAddressBuffer;
    reg[DataLength-1 : 0]       RxDataBuffer;
    reg[DataLength-1 : 0]       TxDataBuffer;
    
    reg[4:0]    BitNumber;
    reg         SDatadirint;
    
    always @(posedge SlaveClock or posedge SlaveChipSelect_ResetButton)
        if (SlaveChipSelect_ResetButton == 1) begin
            SDatadirint <= 1'b1;
            SPI_State <= IDLE;
            if (ResetButton == 0) begin
                RxDataBuffer = 0;
                TxDataBuffer <= 0;
                ResetRegisters;
                ReadWriteBuffer <= 0;
                RxAddressBuffer = 0;
                BitNumber <= 0;
            end
        end
        else begin      //  SlaveChipSelect = 0, ResetButton = 1
            case(SPI_State)
                
                IDLE: begin
                    ReadWriteBuffer <= SlaveDataIn;
                    SPI_State <= ReadAddress;
                    BitNumber <= AddressLength - 1;
                    SDatadirint <= 1'b1;
                end
                
                ReadAddress : begin
                    if (BitNumber > 0) begin
                        RxAddressBuffer = {RxAddressBuffer[AddressLength-2 : 0], SlaveDataIn};
                        BitNumber <= BitNumber - 1;
                    end
                    else begin
                        RxAddressBuffer = {RxAddressBuffer[AddressLength-2 : 0], SlaveDataIn};
                        SPI_State <= ReadWriteData;
                        BitNumber <= DataLength - 1;
                        if (ReadWriteBuffer == 1)
                            SDatadirint <= 1'b1;
                        else
                            SDatadirint <= 1'b0;
                        ReadRegister(RxAddressBuffer);
                    end
                end
                
                ReadWriteData: begin
                    BitNumber <= BitNumber - 1;
                    if (BitNumber > 0) begin
                        RxDataBuffer = {RxDataBuffer[DataLength-2 : 0], SlaveDataIn};
                    end
                    else begin
                        if (ReadWriteBuffer == 1) begin
                            RxDataBuffer = {RxDataBuffer[DataLength-2 : 0], SlaveDataIn};
                            WriteRegister(RxAddressBuffer, RxDataBuffer);
                        end
                        SPI_State <= IDLE;
                        SDatadirint <= 1'b1;
                    end
                end
                
                NonReach: begin
                    SPI_State <= IDLE;
                    SDatadirint <= 1'b1;
                end
            endcase
        end
    
       
    always @(negedge SlaveClock or posedge SlaveChipSelect_ResetButton)
        if (SlaveChipSelect_ResetButton == 1)
            SlaveDataOut <= 1'b0;
        else
            if(SDatadirint == 0 && SPI_State == ReadWriteData)
                 SlaveDataOut <= TxDataBuffer[BitNumber[3:0]];
    
      
    task ReadRegister;
        input[AddressLength - 1 : 0] Address;
    begin
        case (Address)
            0: begin TxDataBuffer <= {FirstChannel_Spare_Reg[3:0],  FirstChannel_RxTx,  FirstChannel_Phase[5:0],  FirstChannel_Gain[4:0]}; end
            1: begin TxDataBuffer <= {SecondChannel_Spare_Reg[3:0], SecondChannel_RxTx, SecondChannel_Phase[5:0], SecondChannel_Gain[4:0]}; end
            2: begin TxDataBuffer <= {ThirdChannel_Spare_Reg[3:0],  ThirdChannel_RxTx,  ThirdChannel_Phase[5:0],  ThirdChannel_Gain[4:0]}; end
            3: begin TxDataBuffer <= {ForthChannel_Spare_Reg[3:0],  ForthChannel_RxTx,  ForthChannel_Phase[5:0],  ForthChannel_Gain[4:0]}; end
            4: begin TxDataBuffer <= {FifthChannel_Reg[15:0]}; end
            5: begin TxDataBuffer <= ProductID; end
        endcase
    end
    endtask         
    
    
    task WriteRegister;
        input[AddressLength - 1 : 0] Address;
        input[DataLength - 1 : 0] Data;
    begin
        case(Address)
            0: begin
                FirstChannel_Spare_Reg  <= Data[15:12];
                FirstChannel_RxTx_Reg   <= Data[11];
                FirstChannel_Phase_Reg  <= Data[10:5];
                FirstChannel_Gain_Reg   <= Data[4:0];
            end
            1: begin
                SecondChannel_Spare_Reg <= Data[15:12];
                SecondChannel_RxTx_Reg  <= Data[11];
                SecondChannel_Phase_Reg <= Data[10:5];
                SecondChannel_Gain_Reg  <= Data[4:0];
            end
            2: begin
                ThirdChannel_Spare_Reg  <= Data[15:12];
                ThirdChannel_RxTx_Reg   <= Data[11];
                ThirdChannel_Phase_Reg  <= Data[10:5];
                ThirdChannel_Gain_Reg   <= Data[4:0];
            end
            3: begin
                ForthChannel_Spare_Reg  <= Data[15:12];
                ForthChannel_RxTx_Reg   <= Data[11];
                ForthChannel_Phase_Reg  <= Data[10:5];
                ForthChannel_Gain_Reg   <= Data[4:0];
            end
            4: begin
                FifthChannel_Reg  <= Data[15:0];
            end
            LoadDefault_Value: begin
                SetRegisterDefaults;
            end
        endcase
    end
    endtask


    task SetRegisterDefaults;
    begin
        FirstChannel_Spare_Reg  <= DefaultSpareValue;
        FirstChannel_RxTx_Reg   <= DefaultRxTxValue;
        FirstChannel_Phase_Reg  <= DefaultPhaseValue;
        FirstChannel_Gain_Reg   <= DefaultGainValue;
        
        SecondChannel_Spare_Reg <= DefaultSpareValue;
        SecondChannel_RxTx_Reg  <= DefaultRxTxValue;
        SecondChannel_Phase_Reg <= DefaultPhaseValue;
        SecondChannel_Gain_Reg  <= DefaultGainValue;

        ThirdChannel_Spare_Reg  <= DefaultSpareValue;
        ThirdChannel_RxTx_Reg   <= DefaultRxTxValue;
        ThirdChannel_Phase_Reg  <= DefaultPhaseValue;
        ThirdChannel_Gain_Reg   <= DefaultGainValue;
        
        ForthChannel_Spare_Reg  <= DefaultSpareValue;
        ForthChannel_RxTx_Reg   <= DefaultRxTxValue;
        ForthChannel_Phase_Reg  <= DefaultPhaseValue;
        ForthChannel_Gain_Reg   <= DefaultGainValue;

        FifthChannel_Reg  <= FifthChannelDefaultValue;
    end
    endtask


    task ResetRegisters;
    begin
        FirstChannel_Spare_Reg  <= 0;
        FirstChannel_RxTx_Reg   <= 0;
        FirstChannel_Phase_Reg  <= 0;
        FirstChannel_Gain_Reg   <= 0;

        SecondChannel_Spare_Reg <= 0;
        SecondChannel_RxTx_Reg  <= 0;
        SecondChannel_Phase_Reg <= 0;
        SecondChannel_Gain_Reg  <= 0;

        ThirdChannel_Spare_Reg  <= 0;
        ThirdChannel_RxTx_Reg   <= 0;
        ThirdChannel_Phase_Reg  <= 0;
        ThirdChannel_Gain_Reg   <= 0;

        ForthChannel_Spare_Reg  <= 0;
        ForthChannel_RxTx_Reg   <= 0;
        ForthChannel_Phase_Reg  <= 0;
        ForthChannel_Gain_Reg   <= 0;

        FifthChannel_Reg  <= 0;
    end
    endtask
    
    
    assign FirstChannel_Spare[3:0]  = FirstChannel_Spare_Reg[3:0];
    assign FirstChannel_RxTx        = FirstChannel_RxTx_Reg;
    assign FirstChannel_Phase[5:0]  = FirstChannel_Phase_Reg[5:0];
    assign FirstChannel_Gain[4:0]   = FirstChannel_Gain_Reg[4:0];
        
    assign SecondChannel_Spare[3:0] = SecondChannel_Spare_Reg[3:0];
    assign SecondChannel_RxTx       = SecondChannel_RxTx_Reg;
    assign SecondChannel_Phase[5:0] = SecondChannel_Phase_Reg[5:0];
    assign SecondChannel_Gain[4:0]  = SecondChannel_Gain_Reg[4:0];

    assign ThirdChannel_Spare[3:0]  = ThirdChannel_Spare_Reg[3:0];
    assign ThirdChannel_RxTx        = ThirdChannel_RxTx_Reg;
    assign ThirdChannel_Phase[5:0]  = ThirdChannel_Phase_Reg[5:0];
    assign ThirdChannel_Gain[4:0]   = ThirdChannel_Gain_Reg[4:0];
        
    assign ForthChannel_Spare[3:0]  = ForthChannel_Spare_Reg[3:0];
    assign ForthChannel_RxTx        = ForthChannel_RxTx_Reg;
    assign ForthChannel_Phase[5:0]  = ForthChannel_Phase_Reg[5:0];
    assign ForthChannel_Gain[4:0]   = ForthChannel_Gain_Reg[4:0];

    assign FifthChannel[15:0]       = FifthChannel_Reg[15:0];
    
endmodule