#include "DMA.h"

void DMA::runDMA(){
	
	baseAddr = 0x10000;
	SOURCE = 0x0;
	TARGET = 0x0;
	SIZE = 0x0;
	START = 0;
	interrupt.write(0);
	cout << "Reset Detected !" << endl;
	
	while(1){
		wait();
		if(interrupt == 0){
			if(START == 1){
				for(int i=0; i<SIZE; i++){
					mRW.write(0);
					mAddr.write(SOURCE + (i<<2));
					dataReg = mData.read();
					wait();
					
					mRW.write(1);
					mAddr.write(TARGET + (i<<2));
					mData.write(dataReg);
					wait();
				}
				mData = 0x0;
				mAddr = 0x0;
				mRW = 0;
				START = 0;
				interrupt.write(1);
			}
				
			else{
				if(sAddr.read() == baseAddr + 0x0)
					SOURCE = sData.read();
				else if(sAddr.read() == baseAddr + 0x4)
					TARGET = sData.read();
				else if(sAddr.read() == baseAddr + 0x8)
					SIZE = sData.read();
				else if(sAddr.read() == baseAddr + 0xc)
					START = sData.read();
				
			}
		}
			
	}
}