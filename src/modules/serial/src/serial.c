 #include <io.h>
 #include <serial.h>
 #include <stdint.h>

static uint16_t port;

void serialinit(uint16_t portin, uint16_t divisor) {

    port = portin;

    outb( SERIAL_INTERRUPT(port)     , 0x00);        // Disable Interrupts
    outb( SERIAL_LINE_COMMAND(port)  , SERIAL_DLAB); // Enable DLAB
    outb( SERIAL_DATA(port)          , 0x01);        // Divisor (lo-byte) => 115200 Baud Rate
    outb( SERIAL_INTERRUPT(port)     , divisor & 0xFF00); // (hi-byte)
    outb( SERIAL_LINE_COMMAND(port)  , divisor & 0x00FF); // 8-bits, no parity , one stop bit
    outb( SERIAL_FIFO_COMMAND(port)  , 0xC7);        // Enable FIFO
    outb( SERIAL_MODEM_COMMAND(port) , 0x0B);        // Enable IRQ
}

uint8_t serialrecieved() {
    return inb(SERIAL_LINE_STATUS(port)) & 1;
}

char read_serial() {
    while (serialrecieved() == 0);
    return inb(SERIAL_DATA(port)); 
}

uint8_t serialready() {
   return inb(SERIAL_LINE_STATUS(port)) & 0x20;
}
 
void write_serial(char c) {
   while (serialready() == 0);
   outb(SERIAL_DATA(port),c);
}

