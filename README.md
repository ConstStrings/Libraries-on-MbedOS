# Libraries on MbedOS

## < 0 > __Introduction__

### What is this repository?

​		**This repository is for developers who use ** ***MbedOS*** . **I list some components **

**I have used and the library it related to below, you can copy them your own ** ***MbedOS***  

**project and download the program to STM32.**



| Component | Library |
| :-------: | :-----: |
|  W25Q64   | flash.h |
|   RC522   | RC522.h |



### What can I do with this repository?

​		**Some applications have been accomplished using the libraries above, I will organize them**

 **later and upload them to github.**



## < 1 > Libraries Description

---

### flash.h

#### API List

```c++
uint16_t W25Q64_GetID(void);
void W25Q64_SectorErase(uint32_t addr);
void W25Q64_ReadData(uint32_t addr,uint8_t *data,uint16_t size);
void W25Q64_PageWrite(uint32_t addr,uint8_t *data,uint16_t size);
void Write_UID(uint32_t UID);
void Flash_Init();
void Update_UIDTable(vector<uint32_t>& table);
void Chip_Erase();
bool W25Q64_BusyState();
```



#### Common Used API

---

```c++
void Flash_Init();
```

***Maintain a memory address in the first sector, check whether the address exists on the chip power-on, if not, create the address of the next sector (0x00000FFF)***



---

```c++
void Write_UID(uint32_t UID);
```

***Writes 32-bit data to the sector after the last written data (the address is saved by sector 0)***



---

```cpp
bool W25Q64_BusyState();
```

***Check whether the chip is currently busy***



---

```cpp
void Chip_Erase();
```

***Erases all data on the chip, complete when checking the busy status returns a bit false***



---

```cpp
void Update_UIDTable(vector<uint32_t>& table);
```

***Load flash data into a vector table***



---



---

### rc522.h

#### API List

```cpp
char PcdRequest(uint8_t req_code,uint8_t *pTagType);
char PcdAnticoll(uint8_t *pSnr);
char PcdSelect(uint8_t *pSnr);
char PcdAuthState(uint8_t auth_mode,uint8_t addr,uint8_t *pKey,uint8_t *pSnr);
char PcdRead(uint8_t addr,uint8_t *pData);
char PcdWrite(uint8_t addr,uint8_t *pData);
char PcdValue(uint8_t dd_mode,uint8_t addr,uint8_t *pValue);
char PcdBakValue(uint8_t sourceaddr, uint8_t goaladdr);
char PcdHalt(void);
void CalulateCRC(uint8_t *pIndata,uint8_t len,uint8_t *pOutData);
char PcdReset(void);
uint8_t ReadRawRC(uint8_t Address);
void WriteRawRC(uint8_t Address, uint8_t value);
void SetBitMask(uint8_t reg,uint8_t mask);
void ClearBitMask(uint8_t reg,uint8_t mask);
char PcdComMF522(uint8_t Command,uint8_t *pInData,uint8_t InLenByte,uint8_t *pOutData,unsigned int *pOutLenBit);
void PcdAntennaOn(void);
void PcdAntennaOff(void);
void RC522_Config(uint8_t Card_Type);
```



#### Common Used API

```
SEE DOCUMENT VERIFY.H
```



---



---

### verify.h

#### API List

```cpp
uint8_t* RC522_ReadIC_UID();
uint8_t UID_Verify(vector<uint32_t>& UID_Table);
bool single_Verify(uint32_t UID);
void LED_demo(vector<uint32_t>& UID_Table);
void add_UID();
void BUZZ_ok();
void BUZZ_fail();
void open();
bool admin();
```



#### Common Used API

```
Under Construction...
```



---



## < 2 > Project Application

### Project: NFC Access Lock Control System

**main.cpp**

```cpp
#include "mbed.h"
#include "sys.h"
#include "rc522.h" 
#include "verify.h"
#include "flash/flash.h"
#include <cstdio>
#include <vector>

#define USB_DEBUG 1

extern BufferedSerial serial_port;
vector<uint32_t> UID_Table;

int main(void)
{		  
    RC522_Init();
    Flash_Init();
    Update_UIDTable(UID_Table);

	while(1)
	{
        uint8_t command = 0;
        uint8_t reply = 0;
        if(serial_port.readable())
            serial_port.read(&command,1);
        switch (command)
        {
            case NEW_UID:
                add_UID();
                Update_UIDTable(UID_Table);

                #if USB_DEBUG
                    printf("NEW_UID_DONE\n");
                #endif

                reply = NEW_UID_DONE;
                serial_port.write(&reply,1);
                break;

            case ERASE_CHIP:
                Chip_Erase();
                while(W25Q64_BusyState());
                Flash_Init();
                Update_UIDTable(UID_Table);

                #if USB_DEBUG
                    printf("ERASE_DONE\n");
                #endif

                reply = ERASE_DONE;
                serial_port.write(&reply,1);
                break;
            
            case ADMIN:
                if(admin())
                {
                    #if USB_DEBUG
                    printf("ADMIN_OK\n");
                    #endif
                    
                    reply = ADMIN_OK;
                    serial_port.write(&reply,1);
                }
                else
                {
                    #if USB_DEBUG
                    printf("ADMIN_FAIL\n");
                    #endif
                    
                    reply = ADMIN_FAIL;
                    serial_port.write(&reply,1);                
                }
                break;

            case ASK_NUM:
                break;

            case OPEN:
                open();
                break;
        }
        LED_demo(UID_Table);
		ThisThread::sleep_for(100ms);       
	}	 
}
```

 









