//main.cpp
#include "DMA.h"

int sc_main(int argc, char* argv[]) {

    FILE *fp_o;

    sc_signal<sc_int<32> > mData;
	sc_signal<sc_uint<32> > mAddr;
	sc_signal<bool> mRW;
	sc_signal<sc_int<32> > sData;
	sc_signal<sc_uint<32> > sAddr;
	sc_signal<bool> sRW;
	sc_signal<bool> interrupt;
	sc_signal<bool> clear;	
    sc_time clkPrd(20, SC_NS);
    sc_clock clk("clk", clkPrd, 0.5, SC_ZERO_TIME, true);

    DMA DMA1("DMA");

    // input, output, clock and reset
    DMA1.mData(mData);
	DMA1.mAddr(mAddr);
	DMA1.mRW(mRW);
	DMA1.sData(sData);
	DMA1.sAddr(sAddr);
	DMA1.sRW(sRW);
	DMA1.interrupt(interrupt);
	DMA1.clear(clear);
	DMA1.clk(clk);
	
	//trace signal
    sc_trace_file *tf = sc_create_vcd_trace_file("RESULT");
    sc_trace(tf, mData, "mData");
	sc_trace(tf, mAddr, "mAddr");
	sc_trace(tf, mRW, "mRW");
	sc_trace(tf, sData, "sData");
	sc_trace(tf, sAddr, "sAddr");
	sc_trace(tf, sRW, "sRW");
	sc_trace(tf, interrupt, "interrupt");
	sc_trace(tf, clear, "clear");
	sc_trace(tf, clk, "clk");
	sc_trace(tf, DMA1.SOURCE, "SOURCE");
	sc_trace(tf, DMA1.TARGET, "TARGET");
	sc_trace(tf, DMA1.SIZE, "SIZE");
	sc_trace(tf, DMA1.START, "START");
    
	//simulatiuon
    sc_start(0, SC_NS);
    clear.write(0);
    sc_start(clkPrd);
    clear.write(1);
    sc_start(clkPrd*2);
	cout << "reset success\n";
	//write SOURCE
    clear.write(0);
	sData.write(0x20000);
	sAddr.write(0x10000);
	sRW.write(1);
    sc_start(clkPrd);
	cout << "write SOURCE success\n";
	//write TARGET
	sData.write(0x30000);
	sAddr.write(0x10004);
	sRW.write(1);
    sc_start(clkPrd);
	cout << "write TARGET success\n";
	//write SIZE
	sData.write(0x4);
	sAddr.write(0x10008);
	sRW.write(1);
	sc_start(clkPrd);
	cout << "write SIZE success\n";
	//write START
	sData.write(0x1);
	sAddr.write(0x1000c);
	sRW.write(1);
    sc_start(clkPrd);
	cout << "write START success\n";
	
	//1st
	sRW.write(0);
	sData.write(0x0);
	sAddr.write(0x0);
	mAddr.read();
	mRW.read();
	mData.write(0x2019);
	sc_start(clkPrd);
	cout << "read 1st success\n";
	mAddr.read();
	mRW.read();
	mData.read();
	sc_start(clkPrd);
	cout << "write 1st success\n";
	//2nd
	mAddr.read();
	mRW.read();
	mData.write(0x2020);
	sc_start(clkPrd);
	cout << "read 2nd success\n";
	mAddr.read();
	mRW.read();
	mData.read();
	sc_start(clkPrd);
	cout << "write 2nd success\n";
	//3rd
	mAddr.read();
	mRW.read();
	mData.write(0x2021);
	sc_start(clkPrd);
	cout << "read 3rd success\n";
	mAddr.read();
	mRW.read();
	mData.read();
	sc_start(clkPrd);
	cout << "write 3rd success\n";
	//4th
	mAddr.read();
	mRW.read();
	mData.write(0x2022);
	sc_start(clkPrd);
	cout << "read 4th success\n";
	mAddr.read();
	mRW.read();
	mData.read();
	sc_start(clkPrd*10);
	cout << "write 4th success\n";
	//reset
	clear.write(1);
	sc_start(clkPrd*10);
    cout << "DMA done\n" << endl;
    sc_close_vcd_trace_file(tf);

    return(0);
}