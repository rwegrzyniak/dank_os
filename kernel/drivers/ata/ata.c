#include "./ata.h"
#include "../ports.h"



ata_devices_t devices = {.primary_m = 0,.primary_s=0,.secondary_m=0,.secondary_s=0};
u8 ata_identify(u8 primary, u8 master){
		u8 drive_port;
		ata_select(primary, master);
		if(primary) drive_port = ATA_PRIMARY_IO;
		else drive_port = ATA_SECONDARY_IO;
		for (int i=ATA_REG_LBA0; i<=ATA_REG_LBA2; i++) port_byte_out(drive_port+i, 0x0);
		//now we can send IDENTIFY command
		port_byte_out(drive_port+ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
		//check if status is not 0
		if(port_byte_in(drive_port+ATA_REG_STATUS)==0) PANIC("DRIVE DONT EXIST");
		while(port_byte_in)
}

void ata_select(u8 primary, u8 master){
		u8 drive_port;
		u8 packet;
		if(primary) drive_port=ATA_PRIMARY_IO;
		else drive_port=ATA_SECONDARY_IO;
		if(master) packet = 0xA0;
		else packet = 0xB0;
		port_byte_out(drive_port + ATA_REG_HDDEVSEL, packet);


}
