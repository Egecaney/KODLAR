`timescale 1ns / 1ps

module TestBench_VerilogSlave(
    );
    
    localparam  AddressLength       = 7;
    localparam  DataLength          = 16;
    localparam  LoadDefault_Value   = 7'b0000111;
    localparam  ProductID           = 16'b0000010100000000;
    
    wire[3:0]   FirstChannel_Spare;
    wire        FirstChannel_RxTx;
    wire[5:0]   FirstChannel_Phase;
    wire[4:0]   FirstChannel_Gain;
    
    wire[3:0]   SecondChannel_Spare;
    wire        SecondChannel_RxTx;
    wire[5:0]   SecondChannel_Phase;
    wire[4:0]   SecondChannel_Gain;
    
    wire[3:0]   ThirdChannel_Spare;
    wire        ThirdChannel_RxTx;
    wire[5:0]   ThirdChannel_Phase;
    wire[4:0]   ThirdChannel_Gain;
    
    wire[3:0]   ForthChannel_Spare;
    wire        ForthChannel_RxTx;
    wire[5:0]   ForthChannel_Phase;
    wire[4:0]   ForthChannel_Gain;
    
    wire[15:0]  FifthChannel;

    reg         ResetButton;
    reg         SlaveClock;
    reg         SlaveChipSelect;
    
    integer         ErrorCount;
    integer         Index1, Index2;
    reg[16*8 : 0]   Test;
    reg[1*8  : 0]   Operation;
    
    wire        SlaveDataOut;
    wire        SlaveDataOutBuffer;
    wire        SlaveDataIn;
    reg         SlaveDataInBuffer;
    
    buf(SlaveDataOutBuffer, SlaveDataOut);
    buf(SlaveDataIn, SlaveDataInBuffer);
    
    reg[DataLength-1 : 0]       SPI_Data;
    reg[AddressLength-1 : 0]    SPI_Address;
    reg                         SPI_Mode;
    reg[DataLength-1 : 0]       SPI_DataRead;
    
    VerilogSlave VerilogSlave_DUT(.SlaveClock(SlaveClock), .SlaveChipSelect(SlaveChipSelect), .SlaveDataIn(SlaveDataIn), .SlaveDataOut(SlaveDataOut), .ResetButton(ResetButton),
                                  .FirstChannel_Spare(FirstChannel_Spare),   .FirstChannel_RxTx(FirstChannel_RxTx),   .FirstChannel_Phase(FirstChannel_Phase),   .FirstChannel_Gain(FirstChannel_Gain),
                                  .SecondChannel_Spare(SecondChannel_Spare), .SecondChannel_RxTx(SecondChannel_RxTx), .SecondChannel_Phase(SecondChannel_Phase), .SecondChannel_Gain(SecondChannel_Gain),
                                  .ThirdChannel_Spare(ThirdChannel_Spare),   .ThirdChannel_RxTx(ThirdChannel_RxTx),   .ThirdChannel_Phase(ThirdChannel_Phase),   .ThirdChannel_Gain(ThirdChannel_Gain),
                                  .ForthChannel_Spare(ForthChannel_Spare),   .ForthChannel_RxTx(ForthChannel_RxTx),   .ForthChannel_Phase(ForthChannel_Phase),   .ForthChannel_Gain(ForthChannel_Gain),
                                  .FifthChannel(FifthChannel));
                                  
    initial
    begin
    
        // Set time format to ns
        $timeformat(-9, 0, "ns");
        
        ResetButton = 1'b0;
        SlaveChipSelect = 1'b1;
        SlaveDataInBuffer = 1'b0;
        
        SPI_Mode = 1'b1;
        SPI_Address = 3'b000;
        SPI_Data = 16'b0000000000000000;
        SPI_DataRead = 16'b0000000000000000;
        
        ErrorCount = 0;
        Index1 = 0;
        Index2 = 0;
        
        $display("Simulation Started");
        
        Test = "Reset";
        Operation = " ";
        
        // Wait 4 clock edges for reset
        repeat(4)
        @(negedge SlaveClock);
        #10;
        ResetButton = 1'b1;
        
        #400;
        @(posedge SlaveClock);
        
        Test = "Reg Sweep";
        
        // Register 0
        
        // Send ABCD
        WriteReg(.Address(0), .Data(16'hABCD));
        ReadReg(.Address(0));
        CheckData;
              
        // Send 4567
        WriteReg(.Address(0), .Data(16'h4567));
        ReadReg(.Address(0));
        CheckData;
        
        // Register 1
        
        // Send 0123
        WriteReg(.Address(1), .Data(16'h0123));
        ReadReg(.Address(1));
        CheckData;
        
        // Send 89AB
        WriteReg(.Address(1), .Data(16'h89AB));
        ReadReg(.Address(1));
        CheckData;
        
        // Register 2
        
        // Send 0246
        WriteReg(.Address(2), .Data(16'h0246));
        ReadReg(.Address(2));
        CheckData;
        
        // Send 8ACE
        WriteReg(.Address(2), .Data(16'h8ACE));
        ReadReg(.Address(2));
        CheckData;
        
        // Register 3
        
        // Send 0246
        WriteReg(.Address(3), .Data(16'h1357));
        ReadReg(.Address(3));
        CheckData;
        
        // Send 8ACE
        WriteReg(.Address(3), .Data(16'h9BDF));
        ReadReg(.Address(3));
        CheckData;
        
        // Register 4
        
        // Send 0000
        WriteReg(.Address(4), .Data(16'h0000));
        ReadReg(.Address(4));
        CheckData;
        
        // Send FFFF
        WriteReg(.Address(4), .Data(16'hFFFF));
        ReadReg(.Address(4));
        CheckData;
        
        #1500;
        Test = "Product ID";
        
        ReadReg(.Address(7'b0000101));
        SPI_Data = ProductID;
        CheckData;
        $display("Product ID Value");
        $display("Serial Number: %0d", SPI_DataRead[DataLength-1 : 0]);
        
        #1500
        Test = "Reset 2";
        Operation = " ";
        
        ResetButton = 1'b0;
        repeat(4)
        @(negedge SlaveClock);
        ResetButton = 1'b1;
        
        // Send Program Command
        Test = "Defaults";
        WriteReg(.Address(LoadDefault_Value), .Data(16'h0000));
        
        #1500
        
        $display("Continuous Write Zero");
        Test = "Continuous Write Zero";
        @(negedge SlaveClock);
        SlaveChipSelect = 1'b0;
        for(Index1 = 0; Index1 <= 3; Index1 = Index1+1) begin
            WriteRegCont(.Address(Index1), .Data(16'h0000));
        end
        
        $display("Continuous Write Zero");
        Test = "Continuous Write One";
        for(Index1 = 0; Index1 <= 3; Index1 = Index1+1) begin
            WriteRegCont(.Address(Index1), .Data(16'hFFFF));
        end
        
        $display("Continuous Read");
        Test = "Continuous Read";
        for(Index1 = 0; Index1 <= 4; Index1 = Index1+1) begin
            ReadRegCont(.Address(Index1));
        end
        
        Test = "Continuous Reg Sweep";
        
        // Register 0
        
        // Send ABCD
        WriteRegCont(.Address(0), .Data(16'hABCD));
        ReadRegCont(.Address(0));
        CheckData;
        
        // Send 4567
        WriteRegCont(.Address(0), .Data(16'h4567));
        ReadRegCont(.Address(0));
        CheckData;
        
        // Register 1
        
        // Send 0123
        WriteRegCont(.Address(1), .Data(16'h0123));
        ReadRegCont(.Address(1));
        CheckData;
        
        // Send 89AB
        WriteRegCont(.Address(1), .Data(16'h89AB));
        ReadRegCont(.Address(1));
        CheckData;
        
        // Register 2
        
        // Send 0246
        WriteRegCont(.Address(2), .Data(16'h0246));
        ReadRegCont(.Address(2));
        CheckData;
        
        // Send 8ACE
        WriteRegCont(.Address(2), .Data(16'h8ACE));
        ReadRegCont(.Address(2));
        CheckData;
        
        // Register 3
        
        // Send 0246
        WriteRegCont(.Address(3), .Data(16'h1357));
        ReadRegCont(.Address(3));
        CheckData;
        
        // Send 8ACE
        WriteRegCont(.Address(3), .Data(16'h9BDF));
        ReadRegCont(.Address(3));
        CheckData;
        
        // Register 4
        
        // Send 0000
        WriteRegCont(.Address(4), .Data(16'h0000));
        ReadRegCont(.Address(4));
        CheckData;
        
        // Send FFFF
        WriteRegCont(.Address(4), .Data(16'hFFFF));
        ReadRegCont(.Address(4));
        CheckData;
        
        
        $display("Simulation Finished");
        $display("Error Count : %d", ErrorCount);
        
        $finish();
        
        end
        
        always begin: ClockGenerator
            SlaveClock = 1'b0;
            #10;
            SlaveClock = 1'b1;
            #10;
        end
        
        task WriteReg;
            input[AddressLength-1 : 0] Address;
            input[DataLength-1 : 0]    Data;
        begin
            @(posedge SlaveClock);
            Operation = "W";
            SPI_Mode= 1'b1;
            SPI_Address = Address;
            SPI_Data = Data;
            @(negedge SlaveClock);
            SlaveChipSelect = 1'b0;
            SlaveDataInBuffer = SPI_Mode;
            @(negedge SlaveClock);
            for(Index2 = AddressLength-1; Index2 >= 0; Index2 = Index2-1) begin
                SlaveDataInBuffer = SPI_Address[Index2];
                @(negedge SlaveClock);
            end
            for(Index2 = DataLength-1; Index2 >= 0; Index2 = Index2-1) begin
                SlaveDataInBuffer = SPI_Data[Index2];
                @(negedge SlaveClock);
            end
            SlaveChipSelect = 1'b1;
        end
        endtask
        
        task ReadReg;
            input[AddressLength-1 : 0] Address;
        begin
            @(posedge SlaveClock);
            Operation = "R";
            SPI_Mode= 1'b0;
            SPI_Address = Address;
            @(negedge SlaveClock);
            SlaveChipSelect = 1'b0;
            SlaveDataInBuffer = SPI_Mode;
            @(negedge SlaveClock);
            for(Index2 = AddressLength-1; Index2 >= 0; Index2 = Index2-1) begin
                SlaveDataInBuffer = SPI_Address[Index2];
                @(negedge SlaveClock);
            end
            for(Index2 = DataLength-1; Index2 >= 0; Index2 = Index2-1) begin
                @(posedge SlaveClock);
                SPI_DataRead[Index2] = SlaveDataOutBuffer;
            end
            @(negedge SlaveClock);
            SlaveChipSelect = 1'b1;
        end
        endtask
            
        task WriteRegCont;
            input[AddressLength-1 : 0] Address;
            input[DataLength-1 : 0] Data;
        begin
            Operation = "W";
            SPI_Mode= 1'b1;
            SPI_Address = Address;
            SPI_Data = Data;
            SlaveDataInBuffer = SPI_Mode;
            @(negedge SlaveClock);
            for(Index2 = AddressLength-1; Index2 >= 0; Index2 = Index2-1) begin
                SlaveDataInBuffer = SPI_Address[Index2];
                @(negedge SlaveClock);
            end
            for(Index2 = DataLength-1; Index2 >= 0; Index2 = Index2-1) begin
                SlaveDataInBuffer = SPI_Data[Index2];
                @(negedge SlaveClock);
            end
        end
        endtask
        
        task ReadRegCont;
            input[AddressLength-1 : 0] Address;
        begin
            Operation = "R";
            SPI_Mode= 1'b0;
            SPI_Address = Address;
            SlaveDataInBuffer = SPI_Mode;
            @(negedge SlaveClock);
            for(Index2 = AddressLength-1; Index2 >= 0; Index2 = Index2-1) begin
                SlaveDataInBuffer = SPI_Address[Index2];
                @(negedge SlaveClock);
            end
            for(Index2 = DataLength-1; Index2 >= 0; Index2 = Index2-1) begin
                @(posedge SlaveClock);
                SPI_DataRead[Index2] = SlaveDataOutBuffer;
            end
            @(negedge SlaveClock);
        end
        endtask
        
        task CheckData;
        begin
            if(SPI_Data != SPI_DataRead) begin
                $display("Data Mismatch for 0 at %0d: Expected: %h Received:%h", SPI_Address, SPI_Data, SPI_DataRead);
                ErrorCount = ErrorCount +1;
            end
        end
        endtask
                                            
endmodule
