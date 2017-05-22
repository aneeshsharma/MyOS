void ISR0(){
	write_status("Division By Zero Error Ocurred!!");
	return;
}

void ISR1(){
	write_status("## Single Step Interrupt occured [Debugger]");
	return;
}

void ISR3(){
	write_status("## Breakpoint [Debugger]");
	return;
}

void ISR4(){
	write_status("Overflow!!");
	return;
}

void ISR5(){
	write_status("Bounds Check");
	return;
}

void ISR11(){
	write_status("Segment Not Present");
	return;
}