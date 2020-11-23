g++ bmpHex.cpp -o bmpHex
./bmpHex brasiil.bmp
cp brasiil.hex verilog/
cd verilog
iverilog minHardware.sv minHardwareTest.sv -g2012 -gno-specify -o a
vvp a
