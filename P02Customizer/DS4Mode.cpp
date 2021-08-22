#include <iostream>
#include <windows.h>
#include <hidapi.h>
#include <string>

#define SONY_DS4_VENDOR 0x054C
#define SONY_DS4_USB 0x05C4

hid_device *HidHandle;

int main(int argc, char *argv[])
{
	SetConsoleTitle("Controller PS-P02 Customizer");
	struct hid_device_info *cur_dev;
	cur_dev = hid_enumerate(SONY_DS4_VENDOR, 0x0);
	
	bool DS4Found = false;

	printf("Connect or reconnect PS-P02 controller\n");

	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000) && DS4Found == false) {

		if (DS4Found == false) {
			cur_dev = hid_enumerate(SONY_DS4_VENDOR, 0x0);
			while (cur_dev) {
				if (cur_dev->product_id == SONY_DS4_USB)
				{
					HidHandle = hid_open(cur_dev->vendor_id, cur_dev->product_id, cur_dev->serial_number);
					hid_set_nonblocking(HidHandle, 1);
					printf("PS-P02 controller found\n");

					DS4Found = true;
					break;
				}
			cur_dev = cur_dev->next;
			}
		}
	}

	unsigned char USBPacket[31];

	if (DS4Found) {

		memset(USBPacket, 0, 31);
		USBPacket[0] = 0x05;
		USBPacket[1] = 0x03; 

		if ((argc == 2) && _stricmp(argv[1], "-d") == 0) {
			USBPacket[6] = 1;
			USBPacket[7] = 1;
			USBPacket[8] = 1;
			printf("Lightbar disabled\n");
		}
		else if (argc == 4) {
			// Color
			USBPacket[6] = std::stof(argv[1]);
			USBPacket[7] = std::stof(argv[2]);
			USBPacket[8] = std::stof(argv[3]);
			printf("Lightbar changed\n");
		} else if ((argc == 2) && _stricmp(argv[1], "-e") == 0) {
			USBPacket[1] = 0x01;
			USBPacket[9] = 0xff;
			USBPacket[10] = 0xff;
			printf("Lightbar enabled\n");
		}
		else {
			USBPacket[7] = 255;
			USBPacket[8] = 255;
			printf("Lightbar changed\n");
		}

		hid_write(HidHandle, USBPacket, 31);
		hid_write(HidHandle, USBPacket, 31);
		hid_write(HidHandle, USBPacket, 31);
	}

	if (cur_dev)
		hid_free_enumeration(cur_dev);

    std::cout << "Done\n"; 
}
