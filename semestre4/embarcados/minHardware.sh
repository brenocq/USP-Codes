g++ bmpHex.cpp -o bmpHex
./bmpHex icmc.bmp
cp icmc.hex verilog/
cd verilog
iverilog minHardware.sv minHardwareTest.sv -g2012 -gno-specify -o a
vvp a
