#define SERIAL_COM1_BASE                0x3F8
void configure_com1_base();
int serial_is_transmit_fifo_empty(unsigned int com);