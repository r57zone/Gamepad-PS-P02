#include <iostream>
#include <windows.h>
#include <hidapi.h>

#define SONY_DS4_VENDOR 0x054C
#define SONY_DS4_USB 0x05C4

hid_device *HidHandle;

int main()
{
	struct hid_device_info *cur_dev;
	cur_dev = hid_enumerate(SONY_DS4_VENDOR, 0x0);
	
	unsigned char USBPacket[31];

	unsigned char featureRep[17] = { 0x14, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //PS3
	
	//unsigned char featureRep4[24] = { 0x09, 0x14, 0x03, 0, 0, 0x11, 0, 0x14, 0x02, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //?
	//unsigned char featureRep5[53] = { 0x1c, 0x00, 0xd0, 0xb2, 0x4b, 0x75, 0x81, 0xda, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	//									0x1b, 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x02, 0x19, 0x00, 0x00, 0x00, 0x00, 0x21, 0x09, 0x14, 0x03,
	//									0x00, 0x00, 0x11, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//									0x00, 0x00, 0x00, 0x00, 0x00 }; //?
	
	//unsigned char featureRep4[23] = { 0x13, 0xAC, 0x9E, 0x17, 0x94, 0x05, 0xB0, 0x56, 0xE8, 0x81, 0x38, 0x08, 0x06, 0x51, 0x41, 0xC0, 0x7F, 0x12, 0xAA, 0xD9, 0x66, 0x3C, 0xCE }; //Handshake test
	unsigned char featureRep2[8] = { 0, 0x09, 0x01, 0, 0, 0,  0,  0 }; //Set configuration request
	unsigned char featureRep3[8] = { 0x21, 0x0A, 0, 0, 0, 0, 0,  0}; //Set idle request


	/*rumblePacket[0] = 0x05;
	rumblePacket[1] = 0x03; //0xff
	rumblePacket[4] = 1; //0 .. 65535
	rumblePacket[5] = 1; //0 .. 65535
	// RGB, soon
	rumblePacket[6] = 255;
	rumblePacket[7] = 0;
	rumblePacket[8] = 0;
	// flash 1 // flash on
	rumblePacket[9] = 0x00;
	// flash 2 // flash off?
	rumblePacket[10] = 0x00;*/

	bool DS4Found = false;

	int packetC = 0;

	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {

		if (DS4Found == false) {
			cur_dev = hid_enumerate(SONY_DS4_VENDOR, 0x0);
			while (cur_dev) {
				if (cur_dev->product_id == SONY_DS4_USB)
				{
					HidHandle = hid_open(cur_dev->vendor_id, cur_dev->product_id, cur_dev->serial_number);
					hid_set_nonblocking(HidHandle, 1);
					printf("DS4 found\n");

					DS4Found = true;
				}
			cur_dev = cur_dev->next;
			}
			

		}

		if (DS4Found) {
			packetC++;
			memset(USBPacket, 0, 31);
			USBPacket[0] = 0x05;
			USBPacket[1] = 0x01;

			if (packetC >= 1 && packetC <= 3) { USBPacket[1] = 0x03; } //} USBPacket[7] = 255; //If set a color, it starts in the xbox controller mode 
			if (packetC == 4) {USBPacket[1] = 0x01;}
			
			if (packetC == 5) {USBPacket[1] = 0x02; USBPacket[8] = 0x40;}
			if (packetC == 6) {USBPacket[0] = 0x05; USBPacket[1] = 0x01;}
			if (packetC == 7 && packetC == 8) { USBPacket[0] = 0x05; USBPacket[1] = 0x02; USBPacket[7] = 0xFB;}
			if (packetC == 9) {USBPacket[1] = 0x01; }
			if (packetC == 10) {USBPacket[1] = 0x02; USBPacket[7] = 0xFB; }
			
			if (packetC == 12) { USBPacket[1] = 0x03; USBPacket[7] = 0xFC; }
			if (packetC == 14) { USBPacket[1] = 0x02; USBPacket[7] = 0xFC; }
			if (packetC == 16) { USBPacket[1] = 0x02; USBPacket[7] = 0xFC; }
			if (packetC == 18) { USBPacket[1] = 0x02; USBPacket[7] = 0xFC; }

			if (packetC == 20) { USBPacket[1] = 0x02; USBPacket[7] = 0xFD; }
			if (packetC == 22) { USBPacket[1] = 0x02; USBPacket[7] = 0xFD; }
			if (packetC == 24) { USBPacket[1] = 0x02; USBPacket[7] = 0xFD; }
			if (packetC == 26) { USBPacket[1] = 0x02; USBPacket[7] = 0xFD; }
			if (packetC == 28) { USBPacket[1] = 0x02; USBPacket[7] = 0xFD; }

			if (packetC == 30) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 32) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 34) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }

			if (packetC == 30) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 32) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 34) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 36) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 38) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 40) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 42) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }
			if (packetC == 44) { USBPacket[1] = 0x02; USBPacket[7] = 0xFE; }

			if (packetC == 46) { USBPacket[1] = 0x02; USBPacket[8] = 0x40; }

			hid_write(HidHandle, USBPacket, 31);

			if (packetC == 3)
				hid_send_feature_report(HidHandle, featureRep, 17); //PS3

			printf("%d sended\n", packetC);
			//if (packetC > 100)
				//break;
		}

	}

	if (cur_dev)
		hid_free_enumeration(cur_dev);

    std::cout << "Done\n"; 
}
