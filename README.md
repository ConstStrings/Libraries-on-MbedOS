# Libraries on MbedOS

## < 0 > __Introduction__

### What is this repository?

​		**This repository is for developers who use ** ***MbedOS*** . **I list some components **

**I have used and the library it related to below, you can copy them your own ** ***MbedOS***  **

**project and download the program to STM32.**



| Component | Library |
| :-------: | :-----: |
|  W25Q64   | flash.h |
|   RC522   | RC522.h |



### What can I do with this repository?

​		**Some applications have been accomplished using the libraries above, I will organize them**

 **later and upload them to github.**



## < 1 > Libraries Description

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











