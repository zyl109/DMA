//some comment

#include "systemc.h"

SC_MODULE(DMA) {
	
	sc_inout<sc_int<32> > mData;	//master port
	sc_out<sc_uint<32> > mAddr;
	sc_out<bool> mRW;
	sc_inout<sc_int<32> > sData;	//slave port
	sc_in<sc_uint<32> > sAddr;
	sc_in<bool> sRW;
	sc_out<bool> interrupt;			//interrupt
	sc_in<bool> clear;				//clear
	sc_in<bool> clk;				//clock
	
	int baseAddr;
	int SOURCE, TARGET, SIZE;
	int dataReg;
	bool START;
	bool interruptReg;
	void runDMA();
	
	SC_CTOR(DMA) {
		SC_CTHREAD (runDMA, clk.pos());
		reset_signal_is(clear, true);
	}
	
	
	
};
