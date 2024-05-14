#pragma once
#include "rc522.h"
#include "mbed.h"
#include <vector>
#include "flash/flash.h"

//============ASK COMMAND=============
#define NEW_UID 0x01
#define OPEN 0x02
#define ERASE_CHIP 0x03
#define ADMIN 0x04
#define ASK_NUM 0x05

//===========REPLY COMMAND============
#define NEW_UID_DONE 0x01
#define NEW_UID_FAIL 0x02
#define OPEN_DONE 0x03
#define CLOSE_DONE 0x04
#define ERASE_DONE 0x05
#define LOAD_FINISH 0x06
#define ADMIN_OK 0x07
#define ADMIN_FAIL 0x08

uint8_t* RC522_ReadIC_UID();
uint8_t UID_Verify(vector<uint32_t>& UID_Table);
bool single_Verify(uint32_t UID);
void LED_demo(vector<uint32_t>& UID_Table);
void add_UID();
void BUZZ_ok();
void BUZZ_fail();
void open();
bool admin();