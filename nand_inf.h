/*
        Structures relevant to NAND chip info.

        Obtained mainly from sunxi-linux kernel.

        -- Steven Saunderson 2016-01-17
*/

//==============================================================================
//  define the data structure for physic layer module
//==============================================================================

typedef struct      // boot0 1.5.0              // 128 bytes
{
    __u16               ChipCnt;                // 0020 0x01
    __u16               ChipConnectInfo;        // 0022 0x01
    __u8                RbCnt;                  // 0024 0x01
    __u8                RbConnectInfo;          // 0025 0x01
    __u8                RbConnectMode;          // 0026 0x01
    __u8                BankCntPerChip;         // 0027 0x01
    __u8                DieCntPerChip;          // 0028 0x01
    __u8                PlaneCountPerDie;       // 0029 0x02
    __u16               SectorCountPerPage;     // 002A 0x0010
    __u16               PageCountPerPhyBlk;     // 002C 0x0100
    __u16               BlockCountPerDie;       // 002E 0x0800
    __u16               OperationOpt;           // 0030 0x1188
    __u8                FrequencePar;           // 0032 0x1E
    __u8                EccMode;                // 0033 0x03
    __u8                NandChipID [8];         // 0034 0xDA94D7AD 0xFFFFFFFF
    __u32               ValidBlockRatio;        // 003C 0x03B0
    __u32               GoodBlockRatio;         // 0040 0x03B0
    __u32               ReadRetryType;          // 0044 0x010604
    __u32               DDRType;                // 0048 0x0
    __u32               Reserved [21];
}__attribute__ ((packed)) boot_nand_para_v1_t;


typedef struct      // boot0 2.0.0              // 128 bytes
{
    __u32               ChipCnt;                //the count of the total nand flash chips are currently connecting on the CE pin
    __u32               ChipConnectInfo;        //chip connect information, bit == 1 means there is a chip connecting on the CE pin
    __u32               RbCnt;
    __u32               RbConnectInfo;          //the connect  information of the all rb  chips are connected
    __u32               RbConnectMode;          //the rb connect  mode
    __u32               BankCntPerChip;         //the count of the banks in one nand chip, multiple banks can support Inter-Leave
    __u32               DieCntPerChip;          //the count of the dies in one nand chip, block management is based on Die
    __u32               PlaneCountPerDie;       //the count of planes in one die, multiple planes can support multi-plane operation
    __u32               SectorCountPerPage;     //the count of sectors in one single physic page, one sector is 0.5k
    __u32               PageCountPerPhyBlk;     //the count of physic pages in one physic block
    __u32               BlockCountPerDie;       //the count of the physic blocks in one die, include valid block and invalid block
    __u32               OperationOpt;           //the mask of the operation types which current nand flash can support support
    __u32               FrequencePar;           //the parameter of the hardware access clock, based on 'MHz'
    __u32               EccMode;                //the Ecc Mode for the nand flash chip, 0: bch-16, 1:bch-28, 2:bch_32   
    __u8                NandChipID [8];         //the nand chip id of current connecting nand chip
    __u32               ValidBlockRatio;        //the ratio of the valid physical blocks, based on 1024
    __u32               GoodBlockRatio;         //good block ratio get from hwscan
    __u32               ReadRetryType;          //the read retry type
    __u32               DDRType;
    __u32               Reserved[12];
}boot_nand_para_v2_t;


typedef struct          // doesn't match layout in boot0 record
{
    __u8        ChipCnt;                            //the count of the total nand flash chips are currently connecting on the CE pin
    __u16       ChipConnectInfo;                    //chip connect information, bit == 1 means there is a chip connecting on the CE pin
	__u8		RbCnt;
	__u8		RbConnectInfo;						//the connect  information of the all rb  chips are connected
    __u8        RbConnectMode;						//the rb connect  mode
	__u8        BankCntPerChip;                     //the count of the banks in one nand chip, multiple banks can support Inter-Leave
    __u8        DieCntPerChip;                      //the count of the dies in one nand chip, block management is based on Die
    __u8        PlaneCntPerDie;                     //the count of planes in one die, multiple planes can support multi-plane operation
    __u8        SectorCntPerPage;                   //the count of sectors in one single physic page, one sector is 0.5k
    __u16       PageCntPerPhyBlk;                   //the count of physic pages in one physic block
    __u16       BlkCntPerDie;                       //the count of the physic blocks in one die, include valid block and invalid block
    __u16       OperationOpt;                       //the mask of the operation types which current nand flash can support support
    __u8        FrequencePar;                       //the parameter of the hardware access clock, based on 'MHz'
    __u8        EccMode;                            //the Ecc Mode for the nand flash chip, 0: bch-16, 1:bch-28, 2:bch_32
    __u8        NandChipId[8];                      //the nand chip id of current connecting nand chip
    __u16       ValidBlkRatio;                      //the ratio of the valid physical blocks, based on 1024
	__u32 		good_block_ratio;					//good block ratio get from hwscan
	__u32		ReadRetryType;						//the read retry type
	__u32       DDRType;
	__u32		Reserved[32];
}boot_nand_para_t;


typedef struct boot_flash_info{
	__u32 chip_cnt;
	__u32 blk_cnt_per_chip;
	__u32 blocksize;
	__u32 pagesize;
	__u32 pagewithbadflag; /*bad block flag was written at the first byte of spare area of this page*/
}boot_flash_info_t;


//define the optional physical operation parameter
struct __OptionalPhyOpPar_t
{
    __u8        MultiPlaneReadCmd[2];               //the command for multi-plane read, the sequence is [0] -ADDR- [0] -ADDR- [1] - DATA
    __u8        MultiPlaneWriteCmd[2];              //the command for multi-plane program, the sequence is 80 -ADDR- DATA - [0] - [1] -ADDR- DATA - 10/15
    __u8        MultiPlaneCopyReadCmd[3];           //the command for multi-plane page copy-back read, the sequence is [0] -ADDR- [1] -ADDR- [2]
    __u8        MultiPlaneCopyWriteCmd[3];          //the command for multi-plane page copy-back program, the sequence is [0] -ADDR- [1] - [2] -ADDR- 10
    __u8        MultiPlaneStatusCmd;                //the command for multi-plane operation status read, the command may be 0x70/0x71/0x78/...
    __u8        InterBnk0StatusCmd;                 //the command for inter-leave bank0 operation status read, the command may be 0xf1/0x78/...
    __u8        InterBnk1StatusCmd;                 //the command for inter-leave bank1 operation status read, the command may be 0xf2/0x78/...
    __u8        BadBlockFlagPosition;               //the flag that marks the position of the bad block flag,0x00-1stpage/ 0x01-1st&2nd page/ 0x02-last page/ 0x03-last 2 page
    __u16       MultiPlaneBlockOffset;              //the value of the block number offset between the left-plane block and the right pane block
};


//define the nand flash storage system information
struct __NandStorageInfo_t              // doesn't match layout in boot0 record
{
    __u8        ChipCnt;                            //the count of the total nand flash chips are currently connecting on the CE pin
    __u16       ChipConnectInfo;                    //chip connect information, bit == 1 means there is a chip connecting on the CE pin
	__u8		RbCnt;
	__u8		RbConnectInfo;						//the connect  information of the all rb  chips are connected
    __u8        RbConnectMode;						//the rb connect  mode
	__u8        BankCntPerChip;                     //the count of the banks in one nand chip, multiple banks can support Inter-Leave
    __u8        DieCntPerChip;                      //the count of the dies in one nand chip, block management is based on Die
    __u8        PlaneCntPerDie;                     //the count of planes in one die, multiple planes can support multi-plane operation
    __u8        SectorCntPerPage;                   //the count of sectors in one single physic page, one sector is 0.5k
    __u16       PageCntPerPhyBlk;                   //the count of physic pages in one physic block
    __u16       BlkCntPerDie;                       //the count of the physic blocks in one die, include valid block and invalid block
    __u16       OperationOpt;                       //the mask of the operation types which current nand flash can support support
    __u8        FrequencePar;                       //the parameter of the hardware access clock, based on 'MHz'
    __u8        EccMode;                            //the Ecc Mode for the nand flash chip, 0: bch-16, 1:bch-28, 2:bch_32
    __u8        NandChipId[8];                      //the nand chip id of current connecting nand chip
    __u16       ValidBlkRatio;                         //the ratio of the valid physical blocks, based on 1024
    __u32		ReadRetryType;						//the read retry type
    __u32       DDRType;
    struct __OptionalPhyOpPar_t OptPhyOpPar;        //the parameters for some optional operation
};


//define the nand flash physical information parameter type
struct __NandPhyInfoPar_t
{
    __u8        NandID[8];                          //the ID number of the nand flash chip
    __u8        DieCntPerChip;                      //the count of the Die in one nand flash chip
    __u8        SectCntPerPage;                     //the count of the sectors in one single physical page
    __u16       PageCntPerBlk;                      //the count of the pages in one single physical block
    __u16       BlkCntPerDie;                       //the count fo the physical blocks in one nand flash Die
    __u16       OperationOpt;                       //the bitmap that marks which optional operation that the nand flash can support
    __u16       ValidBlkRatio;                      //the valid block ratio, based on 1024 blocks
    __u16       AccessFreq;                         //the highest access frequence of the nand flash chip, based on MHz
    __u16       EccMode;                            //the Ecc Mode for the nand flash chip, 0: bch-16, 1:bch-28, 2:bch_32
    __u32 		ReadRetryType;
    __u32       DDRType;
    struct __OptionalPhyOpPar_t *OptionOp;          //the pointer point to the optional operation parameter
};


//==============================================================================
//  define nand flash manufacture ID number
//==============================================================================

#define TOSHIBA_NAND            0x98                //Toshiba nand flash manufacture number
#define SAMSUNG_NAND            0xec                //Samsunt nand flash manufacture number
#define HYNIX_NAND              0xad                //Hynix nand flash manufacture number
#define MICRON_NAND             0x2c                //Micron nand flash manufacture number
#define ST_NAND                 0x20                //ST nand flash manufacture number
#define INTEL_NAND              0x89                //Intel nand flash manufacture number
#define SPANSION_NAND           0x01                //spansion nand flash manufacture number
#define POWER_NAND              0x92                //power nand flash manufacture number
#define SANDISK                 0x45                //sandisk nand flash manufacture number

//==============================================================================
// define the optional operation parameter for different kindes of nand flash
//==============================================================================

//the physical architecture parameter for Samsung 2K page SLC nand flash
static struct __OptionalPhyOpPar_t PhysicArchiPara0 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x81},           //multi-plane program command
    {0x00, 0x00, 0x35},     //multi-plane page copy-back read command
    {0x85, 0x11, 0x81},     //multi-plane page copy-back program command
    0x70,                   //multi-plane operation status read command
    0xf1,                   //inter-leave bank0 operation status read command
    0xf2,                   //inter-leave bank1 operation status read command
    0x01,                   //bad block flag position, in the fist 2 page
    1                       //multi-plane block address offset
};

//the physical architecture parameter for Samsung 4K page SLC nand flash
static struct __OptionalPhyOpPar_t PhysicArchiPara1 =
{
    {0x60, 0x30},           //multi-plane read command
    {0x11, 0x81},           //multi-plane program command
    {0x60, 0x60, 0x35},     //multi-plane page copy-back read command
    {0x85, 0x11, 0x81},     //multi-plane page copy-back program command
    0x70,                   //multi-plane operation status read command
    0xf1,                   //inter-leave bank0 operation status read command
    0xf2,                   //inter-leave bank1 operation status read command
    0x00,                   //bad block flag position, in the fist page
    1                       //multi-plane block address offset
};

//the physical architecture parameter for Samsung 2K page MLC nand flash
static struct __OptionalPhyOpPar_t PhysicArchiPara2 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x81},           //multi-plane program command
    {0x00, 0x00, 0x35},     //multi-plane page copy-back read command
    {0x85, 0x11, 0x81},     //multi-plane page copy-back program command
    0x70,                   //multi-plane operation status read command
    0xf1,                   //inter-leave bank0 operation status read command
    0xf2,                   //inter-leave bank1 operation status read command
    0x02,                   //bad block flag position, in the last page
    1                       //multi-plane block address offset
};

//the physical architecture parameter for Samsung 4K page MLC nand flash
static struct __OptionalPhyOpPar_t PhysicArchiPara3 =
{
    {0x60, 0x60},           //multi-plane read command
    {0x11, 0x81},           //multi-plane program command
    {0x60, 0x60, 0x35},     //multi-plane page copy-back read command
    {0x85, 0x11, 0x81},     //multi-plane page copy-back program command
    0x70,                   //multi-plane operation status read command
    0xf1,                   //inter-leave bank0 operation status read command
    0xf2,                   //inter-leave bank1 operation status read command
    0x02,                   //bad block flag position, in the last page
    1                       //multi-plane block address offset
};

//the physical architecture parameter for Micon nand flash
static struct __OptionalPhyOpPar_t PhysicArchiPara4 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x80},           //multi-plane program command
    {0x00, 0x00, 0x35},     //multi-plane page copy-back read command
    {0x85, 0x11, 0x80},     //multi-plane page copy-back program command
    0x70,                   //multi-plane operation status read command
    0x78,                   //inter-leave bank0 operation status read command
    0x78,                   //inter-leave bank1 operation status read command
    0x01,                   //bad block flag position, in the fist 2 page
    1                       //multi-plane block address offset
};

//the physical architecture parameter for Toshiba SLC nand flash
static struct __OptionalPhyOpPar_t PhysicArchiPara5 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x80},           //multi-plane program command
    {0x00, 0x00, 0x30},     //multi-plane page copy-back read command
    {0x8c, 0x11, 0x8c},     //multi-plane page copy-back program command
    0x71,                   //multi-plane operation status read command
    0x70,                   //inter-leave bank0 operation status read command
    0x70,                   //inter-leave bank1 operation status read command
    0x00,                   //bad block flag position, in the fist page
    0                       //multi-plane block address offset
};

//the physical architecture parameter for Toshiba MLC nand flash which multi-plane offset is 1024
static struct __OptionalPhyOpPar_t PhysicArchiPara6 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x80},           //multi-plane program command
    {0x00, 0x00, 0x30},     //multi-plane page copy-back read command
    {0x8c, 0x11, 0x8c},     //multi-plane page copy-back program command
    0x71,                   //multi-plane operation status read command
    0x70,                   //inter-leave bank0 operation status read command
    0x70,                   //inter-leave bank1 operation status read command
    0x00,                   //bad block flag position, in the fist page
    1024                    //multi-plane block address offset
};

//the physical architecture parameter for Toshiba MLC nand flash which multi-plane offset is 2048
static struct __OptionalPhyOpPar_t PhysicArchiPara7 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x80},           //multi-plane program command
    {0x00, 0x00, 0x30},     //multi-plane page copy-back read command
    {0x8c, 0x11, 0x8c},     //multi-plane page copy-back program command
    0x71,                   //multi-plane operation status read command
    0x70,                   //inter-leave bank0 operation status read command
    0x70,                   //inter-leave bank1 operation status read command
    0x00,                   //bad block flag position, in the fist page
    2048                    //multi-plane block address offset
};

static struct __OptionalPhyOpPar_t PhysicArchiPara8 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x80},           //multi-plane program command
    {0x00, 0x00, 0x30},     //multi-plane page copy-back read command
    {0x8c, 0x11, 0x8c},     //multi-plane page copy-back program command
    0x71,                   //multi-plane operation status read command
    0x70,                   //inter-leave bank0 operation status read command
    0x70,                   //inter-leave bank1 operation status read command
    0x02,                   //bad block flag position, in the last page
    1                       //multi-plane block address offset
};

static struct __OptionalPhyOpPar_t PhysicArchiPara9 =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x81},           //multi-plane program command
    {0x00, 0x00, 0x30},     //multi-plane page copy-back read command
    {0x8c, 0x11, 0x8c},     //multi-plane page copy-back program command
    0x71,                   //multi-plane operation status read command
    0x70,                   //inter-leave bank0 operation status read command
    0x70,                   //inter-leave bank1 operation status read command
    0x02,                   //bad block flag position, in the last page
    1                       //multi-plane block address offset
};

static struct __OptionalPhyOpPar_t DefualtPhysicArchiPara =
{
    {0x00, 0x30},           //multi-plane read command
    {0x11, 0x81},           //multi-plane program command
    {0x00, 0x00, 0x35},     //multi-plane page copy-back read command
    {0x85, 0x11, 0x81},     //multi-plane page copy-back program command
    0x70,                   //multi-plane operation status read command
    0xf1,                   //inter-leave bank0 operation status read command
    0xf2,                   //inter-leave bank1 operation status read command
    0x00,                   //bad block flag position, in the fist 2 page
    1                       //multi-plane block address offset
};


//==============================================================================
// define the physical architecture parameter for all kinds of nand flash
//==============================================================================

//==============================================================================
//============================ SAMSUNG NAND FLASH ==============================
//==============================================================================
struct __NandPhyInfoPar_t SamsungNandTbl[] =
{
    //                NAND_CHIP_ID                     DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq   EccMode ReadRetry DDRType OperationPar
    //--------------------------------------------------------------------------------------------------------------------------------
    { {0xec, 0xf1, 0xff, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    15,     0,       0,        0,     &PhysicArchiPara0 },   // K9F1G08
    { {0xec, 0xf1, 0x00, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    15,     0,       0,        0,     &PhysicArchiPara0 },   // K9F1G08
    { {0xec, 0xda, 0xff, 0x15, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     1024,   0x0000,   974,    15,     0,       0,        0,     &PhysicArchiPara0 },   // K9K2G08
    { {0xec, 0xda, 0x10, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0008,   974,    15,     0,       0,        0,     &PhysicArchiPara0 },   // K9F2G08
    { {0xec, 0xdc, 0xc1, 0x15, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     2048,   0x0000,   974,    15,     0,       0,        0,     &PhysicArchiPara0 },   // K9K4G08
    { {0xec, 0xdc, 0x10, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     4096,   0x0008,   974,    15,     0,       0,        0,     &PhysicArchiPara0 },   // K9F4G08
    { {0xec, 0xd3, 0x51, 0x95, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     4096,   0x0008,   974,    30,     0,       0,        0,     &PhysicArchiPara0 },   // K9K8G08
    //-----------------------------------------------------------------------------------------------------------------------------------
    { {0xec, 0xd3, 0x50, 0xa6, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0018,   974,    30,     0,       0,        0,     &PhysicArchiPara1 },   // K9F8G08
    { {0xec, 0xd5, 0x51, 0xa6, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0038,   974,    30,     0,       0,        0,     &PhysicArchiPara1 },   // K9KAG08
    //-----------------------------------------------------------------------------------------------------------------------------------
    { {0xec, 0xdc, 0x14, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0008,   974,    20,     0,       0,        0,     &PhysicArchiPara2 },   // K9G4G08
    { {0xec, 0xdc, 0x14, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0008,   974,    30,     0,       0,        0,     &PhysicArchiPara2 },   // K9G4G08
    { {0xec, 0xd3, 0x55, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     2048,   0x0008,   974,    20,     0,       0,        0,     &PhysicArchiPara2 },   // K9L8G08
    { {0xec, 0xd3, 0x55, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     2048,   0x0008,   974,    30,     0,       0,        0,     &PhysicArchiPara2 },   // K9L8G08
    { {0xec, 0xd3, 0x14, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    20,     0,       0,        0,     &PhysicArchiPara2 },   // K9G8G08
    { {0xec, 0xd3, 0x14, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    30,     0,       0,        0,     &PhysicArchiPara2 },   // K9G8G08
    { {0xec, 0xd5, 0x55, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0028,   974,    30,     0,       0,        0,     &PhysicArchiPara2 },   // K9LAG08
    { {0xec, 0xd5, 0x55, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0028,   974,    30,     0,       0,        0,     &PhysicArchiPara2 },   // K9LAG08
    //-----------------------------------------------------------------------------------------------------------------------------------
    { {0xec, 0xd5, 0x14, 0xb6, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   974,    30,     0,       0,        0,     &PhysicArchiPara3 },   // K9GAG08
    { {0xec, 0xd7, 0x55, 0xb6, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0028,   974,    30,     0,       0,        0,     &PhysicArchiPara3 },   // K9LBG08
    { {0xec, 0xd7, 0xd5, 0x29, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0028,   974,    30,     0,       0,        0,     &PhysicArchiPara3 },   // K9LBG08
    { {0xec, 0xd7, 0x94, 0x72, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     4096,   0x0008,   974,    30,     2,       0,        0,     &PhysicArchiPara3 },   // K9GBG08
    { {0xec, 0xd5, 0x98, 0x71, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     2048,   0x0008,   950,    30,     3,       0,        0,     &PhysicArchiPara3 },   // K9AAG08

    { {0xec, 0xd5, 0x94, 0x29, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   974,    30,     0,       0,        0,     &PhysicArchiPara3 },   // K9GAG08U0D
    { {0xec, 0xd5, 0x84, 0x72, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     2048,   0x0000,   950,    24,     2,       0,        0,     &PhysicArchiPara3 },   // K9GAG08U0E
    { {0xec, 0xd5, 0x94, 0x76, 0x54, 0xff, 0xff, 0xff }, 1,    16,     128,     2048,   0x0408,   950,    30,     2,       0,        0,     &PhysicArchiPara3 },   // K9GAG08U0E
    { {0xec, 0xd3, 0x84, 0x72, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     1024,   0x0000,   950,    24,     2,       0,        0,     &PhysicArchiPara3 },   // K9G8G08U0C
    { {0xec, 0xd7, 0x94, 0x76, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     4096,   0x0088,   974,    30,     3,       0,        0,     &PhysicArchiPara3 },   // K9GBG08U0A
    { {0xec, 0xd7, 0x94, 0x7A, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     4096,   0x0088,   974,    30,     3,       0,        0,     &PhysicArchiPara3 },   // K9GBG08U0A
    { {0xec, 0xde, 0xd5, 0x7A, 0x58, 0xff, 0xff, 0xff }, 2,    16,     128, 	4096,	0x0888,   974,	  30,	  3,	   0,	     0,     &PhysicArchiPara3 },   // K9LCG08U0A

    { {0xec, 0xd7, 0x94, 0x7A, 0x54, 0xc3, 0xff, 0xff }, 1,    16,     128,     4096,   0x0088,   974,    60,     1,       0,        3,     &PhysicArchiPara3 },   // toogle nand 1.0
    { {0xec, 0xde, 0xa4, 0x7a, 0x68, 0xc4, 0xff, 0xff }, 1,    16,     128,     8192,   0x0588,   974,    60,     4,   0x200e04,     3,     &PhysicArchiPara3 },   // toogle nand 2.0 K9GCGD8U0A
    { {0xec, 0xd7, 0x94, 0x7E, 0x64, 0xc4, 0xff, 0xff }, 1,    16,     128,     4096,   0x0588,   974,    60,     4,   0x200e04,     3,     &PhysicArchiPara3 },   // toogle nand 2.0 K9GBGD8U0B
    { {0xec, 0xd7, 0x94, 0x7e, 0x64, 0x44, 0xff, 0xff }, 1,    16,     128,     4096,   0x0188,   974,    40,     4,   0x200e04,     0,     &PhysicArchiPara3 },   // 21nm sdr K9GBG08U0B
    { {0xec, 0xde, 0xd5, 0x7e, 0x68, 0x44, 0xff, 0xff }, 2,    16,     128,     4096,   0x0188,   974,    40,     4,   0x200e04,     0,     &PhysicArchiPara3 },   // 21nm sdr K9LCG08U0B
    { {0xec, 0xd7, 0x14, 0x76, 0x54, 0xc2, 0xff, 0xff }, 1,    16,     128,     4096,   0x0088,   974,    40,     3,       0,        3,     &PhysicArchiPara3 },   // K9GBG08U0M

    //-----------------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,       0,        0,      0                 },   // NULL
};


//==============================================================================
//============================= HYNIX NAND FLASH ===============================
//==============================================================================
struct __NandPhyInfoPar_t HynixNandTbl[] =
{
    //                  NAND_CHIP_ID                  DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode  ReadRetry  OperationPar
    //---------------------------------------------------------------------------------------------------------------------------
    { {0xad, 0xf1, 0x80, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    15,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF081G2M
    { {0xad, 0xf1, 0x80, 0x1d, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF081G2A
    { {0xad, 0xf1, 0x00, 0x1d, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // H27U1G8F2B
    { {0xad, 0xda, 0x80, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    15,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF082G2M
    { {0xad, 0xda, 0x80, 0x1d, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF082G2A
    { {0xad, 0xda, 0x10, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF082G2B
    { {0xad, 0xdc, 0x80, 0x15, 0xff, 0xff, 0xff, 0xff }, 4,     4,      64,     1024,   0x0000,   974,    15,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UH084G2M
    { {0xad, 0xdc, 0x80, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     4096,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF084G2M, HY27UG088G5M
    { {0xad, 0xdc, 0x10, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     4096,   0x0008,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UF084G2B, HY27UG088G5B
    { {0xad, 0xd3, 0x80, 0x15, 0xff, 0xff, 0xff, 0xff }, 4,     4,      64,     2048,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UG084G2M, HY27H088G2M
    { {0xad, 0xd3, 0xc1, 0x95, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     4096,   0x0000,   974,    20,     0,      0,         0,    &PhysicArchiPara0 },   // HY27UG088G2M, HY27UH08AG5M
    //---------------------------------------------------------------------------------------------------------------------------
    { {0xad, 0xdc, 0x84, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0000,   974,    12,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UT084G2M, HY27UU088G5M
    { {0xad, 0xdc, 0x14, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0008,   974,    15,     0,      0,         0,    &PhysicArchiPara2 },   // HY27U4G8T2BTR
    { {0xad, 0xd3, 0x85, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     2048,   0x0000,   974,    10,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UV08AG5M, HY27UW08BGFM
    { {0xad, 0xd3, 0x14, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    12,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UT088G2M, HY27UU08AG5M
    { {0xad, 0xd3, 0x14, 0x2d, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    25,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UT088G2M, HY27UU08AG5M
    { {0xad, 0xd3, 0x14, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    15,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UT088G2M, HY27UU08AG5M
    { {0xad, 0xd5, 0x55, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0008,   974,    15,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UV08BG5M, HY27UW08CGFM
    { {0xad, 0xd5, 0x55, 0x2d, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0008,   974,    25,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UV08BG5M, HY27UW08CGFM
    { {0xad, 0xd5, 0x55, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     8192,   0x0008,   974,    30,     0,      0,         0,    &PhysicArchiPara2 },   // HY27UV08BG5M, HY27UW08CGFM
    //---------------------------------------------------------------------------------------------------------------------------
    { {0xad, 0xd3, 0x14, 0xb6, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     2048,   0x0008,   974,    30,     0,      0,         0,    &PhysicArchiPara3 },   // H27U8G8T2B
    { {0xad, 0xd5, 0x14, 0xb6, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   974,    30,     0,      0,         0,    &PhysicArchiPara3 },   // H27UAG8T2M, H27UBG8U5M
    { {0xad, 0xd7, 0x55, 0xb6, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0008,   974,    30,     0,      0,         0,    &PhysicArchiPara3 },   // H27UCG8V5M
    //---------------------------------------------------------------------------------------------------------------------------
    { {0xad, 0xd5, 0x94, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   974,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UBG8U5A
    { {0xad, 0xd7, 0x95, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0008,   974,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UCG8V5A
    { {0xad, 0xd5, 0x95, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0008,   974,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UCG8VFA
    { {0xad, 0xd5, 0x94, 0x9A, 0xff, 0xff, 0xff, 0xff }, 1,    16,     256,     1024,   0x0000,   950,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UAG8T2B
    { {0xad, 0xd7, 0x94, 0x9A, 0xff, 0xff, 0xff, 0xff }, 1,    16,     256,     2048,   0x0008,   950,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UBG8T2A H27UCG8U5(D)A H27UDG8VF(D)A
    { {0xad, 0xde, 0xd5, 0x9A, 0xff, 0xff, 0xff, 0xff }, 2,    16,     256,     2048,   0x0008,   950,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UDG8V5A
    { {0xad, 0xd7, 0x94, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     8192,   0x0008,   974,    30,     2,      0,         0,    &PhysicArchiPara3 },   // H27UBG8T2M
    { {0xad, 0xde, 0x94, 0xd2, 0xff, 0xff, 0xff, 0xff }, 1,    16,     256,     4096,   0x0188,   950,    30,     2,  0x000604,      0,    &PhysicArchiPara3 },   // H27UCG8T2M
    { {0xad, 0xd7, 0x18, 0x8d, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     4096,   0x0188,   950,    30,     3,  0x000604,      0,    &PhysicArchiPara3 },   // H27UBG8M2A
    { {0xad, 0xd7, 0x94, 0xda, 0xff, 0xff, 0xff, 0xff }, 1,    16,     256,     2048,   0x0188,   950,    30,     3,  0x010604,      0,    &PhysicArchiPara3 },   // H27UBG8M2A
    { {0xad, 0xde, 0x94, 0xda, 0x74, 0xff, 0xff, 0xff }, 1,    16,     256,     4096,   0x0188,   918,    40,     4,  0x020708,      0,    &PhysicArchiPara3 },   // H27UCG8T2A 20nm 8G
    { {0xad, 0xd7, 0x94, 0x91, 0x60, 0xff, 0xff, 0xff }, 1,    16,     256,     2048,   0x0188,   918,    40,     4,  0x030708,      0,    &PhysicArchiPara3 },   // H27UBG8T2C 20nm 4G
    { {0xad, 0xde, 0x94, 0xeb, 0x74, 0xff, 0xff, 0xff }, 1,    32,     256,     2048,   0x0188,   918,    40,     4,  0x030708,      0,    &PhysicArchiPara3 },   // H27UCG8T2B 20nm 8G
    //---------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,      0,         0,   0                 },   // NULL
};


//==============================================================================
//============================= TOSHIBA NAND FLASH =============================
//==============================================================================
struct __NandPhyInfoPar_t ToshibaNandTbl[] =
{
    //                    NAND_CHIP_ID                 DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq   EccMode ReadRetry   OperationPar
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x98, 0xf1, 0x80, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    20,     0,     0,      0,   &PhysicArchiPara5 },   // TC58NVG0S3B
    { {0x98, 0xda, 0xff, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    20,     0,     0,      0,   &PhysicArchiPara5 },   // TC58NVG1S3B
    { {0x98, 0xdc, 0x81, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     4096,   0x0000,   974,    20,     0,     0,      0,   &PhysicArchiPara5 },   // TC58NVG2S3B
    { {0x98, 0xd1, 0x90, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    20,     0,     0,      0,   &PhysicArchiPara5 },   // TC58NVG0S3E
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x98, 0xda, 0x84, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     1024,   0x0000,   974,    20,     0,     0,      0,   &PhysicArchiPara6 },   // TC58NVG1D4B
    { {0x98, 0xdc, 0x84, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0008,   974,    20,     0,     0,      0,   &PhysicArchiPara6 },   // TC58NVG2D4B
    { {0x98, 0xd3, 0x84, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    20,     0,     0,      0,   &PhysicArchiPara7 },   // TC58NVG3D4C
    { {0x98, 0xd5, 0x85, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0008,   974,    20,     0,     0,      0,   &PhysicArchiPara7 },   // TC58NVG4D4C, TC58NVG5D4C
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x98, 0xd3, 0x94, 0xba, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     2048,   0x0008,   974,    20,     0,     0,      0,   &PhysicArchiPara6 },   // TC58NVG3D1DTG00
    { {0x98, 0xd7, 0x95, 0xba, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     8192,   0x0008,   918,    30,     2,     0,      0,   &PhysicArchiPara7 },   // TC58NVG6D1DTG20
    { {0x98, 0xd5, 0x94, 0xba, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   918,    30,     2,     0,      0,   &PhysicArchiPara7},    // TH58NVG5D1DTG20
    { {0x98, 0xd5, 0x94, 0x32, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     2048,   0x0008,   918,    25,     1,     0,      0,   &PhysicArchiPara8},    // TH58NVG4D2ETA20 TH58NVG4D2FTA20 TH58NVG5D2ETA00
    { {0x98, 0xd7, 0x94, 0x32, 0xff, 0xff, 0xff, 0xff }, 1,    16,     128,     4096,   0x0008,   918,    25,     2,     0,      0,   &PhysicArchiPara8},    // TH58NVG5D2FTA00 TH58NVG6D2FTA20
    { {0x98, 0xd7, 0x95, 0x32, 0xff, 0xff, 0xff, 0xff }, 2,    16,     128,     4096,   0x0008,   454,    25,     1,     0,      0,   &PhysicArchiPara8},    // TH58NVG6D2ETA20
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x98, 0xde, 0x94, 0x82, 0x76, 0xff, 0xff, 0xff }, 1,    16,     256,     4096,   0x0588,   918,    40,     4, 0x100504,   0,   &PhysicArchiPara9},    // TH58NVG6D2ETA20
    { {0x98, 0xd7, 0x94, 0x32, 0x76, 0x56, 0xff, 0xff }, 1,    16,     128,     4096,   0x0588,   918,    40,     4, 0x100504,   0,   &PhysicArchiPara9},    // TH58NVG5D2HTA20
    { {0x98, 0xd5, 0x84, 0x32, 0x72, 0x56, 0xff, 0xff }, 1,    16,     128,     2048,   0x0580,   918,    40,     4, 0x100504,   0,   &PhysicArchiPara9},    // TH58NVG4D2HTA20
	{ {0x98, 0xde, 0x84, 0x93, 0x72, 0x57, 0xff, 0xff }, 1,    32,     256,     2048,   0x0580,   918,    40,     4, 0x100504,   0,   &PhysicArchiPara9},    // TC58NVG6DCJTA00
    { {0x98, 0xd7, 0x84, 0x93, 0x72, 0x57, 0xff, 0xff }, 1,    32,     256,     1024,   0x0580,   918,    40,     4, 0x100504,   0,   &PhysicArchiPara9},    // TC58TEG5DCJTA00
    { {0x98, 0xde, 0x94, 0x93, 0x76, 0x57, 0xff, 0xff }, 1,    32,     256,     2048,   0x0588,   918,    40,     4, 0x100504,   0,   &PhysicArchiPara9},    // TC58TEG6DCJTA00
    { {0x98, 0xde, 0x84, 0x93, 0x72, 0xd7, 0xff, 0xff }, 1,    32,     256,     2048,   0x0580,   918,    40,     4, 0x100504,   3,   &PhysicArchiPara9},    // TC58TEG6DDJTA00
    //-------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,     0,      0,        0         },   // NULL
};


//==============================================================================
//============================= MICON NAND FLASH ===============================
//==============================================================================
struct __NandPhyInfoPar_t MicronNandTbl[] =
{
    //                   NAND_CHIP_ID                 DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode  ReadRetry  OperationPar
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x2c, 0xda, 0xff, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    25,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F2G08AAC, JS29F02G08AAN
    { {0x2c, 0xdc, 0xff, 0x15, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     2048,   0x0000,   974,    25,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F4G08BAB, MT29F8G08FAB, JS29F04G08BAN, JS29F08G08FAN
    { {0x2c, 0xdc, 0x90, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     4096,   0x0008,   974,    25,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F4G08AAA, MT29F8G08DAA, JS29F04G08AAN
    { {0x2c, 0xd3, 0xd1, 0x95, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     4096,   0x0008,   974,    25,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F8G08BAB, MT29F16G08FAB, JS29F08G08BAN, JS29F16G08FAN
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x2c, 0xdc, 0x84, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0000,   974,    20,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F4G08MAA, MT29F8G08QAA
    { {0x2c, 0xd3, 0x85, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     2048,   0x0000,   974,    20,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F16GTAA
    { {0x2c, 0xd3, 0x94, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    30,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F8G08MAA, MT29F16G08QAA, JS29F08G08AAM, JS29F16G08CAM
    { {0x2c, 0xd5, 0x95, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0008,   974,    20,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F32G08TAA, JS29F32G08FAM
    { {0x2c, 0xd5, 0xd5, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0028,   974,    20,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F32G08TAA, JS29F32G08FAM
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x2c, 0xd5, 0x94, 0x3e, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   974,    30,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F16G08MAA, MT29F32G08QAA, JS29F32G08AAM, JS29F32G08CAM
    { {0x2c, 0xd5, 0xd5, 0x3e, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0008,   974,    30,     0,     0,     0,   &PhysicArchiPara4 },   // MT29F64G08TAA, JS29F64G08FAM
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x2c, 0xd7, 0x94, 0x3e, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     8192,   0x0208,   950,    30,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F32G08CBAAA,MT29F64G08CFAAA
    { {0x2c, 0xd7, 0xd5, 0x3e, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     4096,   0x0008,   950,    30,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F64G08CTAA
    { {0x2c, 0xd9, 0xd5, 0x3e, 0xff, 0xff, 0xff, 0xff }, 2,     8,     128,     8192,   0x0008,   950,    30,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F128G08,
    { {0x2c, 0x68, 0x04, 0x46, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     4096,   0x0208,   950,    30,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F32G08CBABA
    { {0x2c, 0x88, 0x05, 0xC6, 0xff, 0xff, 0xff, 0xff }, 2,     8,     256,     4096,   0x0208,   950,    30,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F128G08CJABA
    { {0x2c, 0x88, 0x04, 0x4B, 0xff, 0xff, 0xff, 0xff }, 1,    16,     256,     4096,   0x0208,   950,    40,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F64G08CBAAA
    { {0x2c, 0x68, 0x04, 0x4A, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     4096,   0x0208,   950,    40,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F32G08CBACA
    { {0x2c, 0x48, 0x04, 0x4A, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     2048,   0x0208,   950,    40,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F16G08CBACA
    { {0x2c, 0x48, 0x04, 0x46, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     2048,   0x0208,   950,    30,     2,     0,     0,   &PhysicArchiPara4 },   // MT29F16G08CBABA
    { {0x2c, 0x64, 0x44, 0x4B, 0xa9, 0xff, 0xff, 0xff }, 1,	   16,	   256,	    4096,	0x0788,   950,    30,     5, 0x400a01,  0,   &PhysicArchiPara4 },	// MT29F64G08CBABA
    { {0x2c, 0x44, 0x44, 0x4B, 0xA9, 0xff, 0xff, 0xff }, 1,    16,     256,     2048,   0x0788,   944,    30,     5,   0x400a01,     0,   &PhysicArchiPara4 },   // MT29F32G08CBADA
	//-------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,    0,     0,      0,      0              },   // NULL
};


//==============================================================================
//============================= INTEL NAND FLASH ===============================
//==============================================================================
struct __NandPhyInfoPar_t IntelNandTbl[] =
{
    //                 NAND_CHIP_ID                   DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode  ReadRetry  OperationPar
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x89, 0xd3, 0x94, 0xa5, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     4096,   0x0008,   974,    30,     0,     0,    0,   &PhysicArchiPara4 },   // 29F08G08AAMB2, 29F16G08CAMB2
    { {0x89, 0xd5, 0xd5, 0xa5, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     4096,   0x0028,   974,    20,     0,     0,    0,   &PhysicArchiPara4 },   // 29F32G08FAMB2
    //-------------------------------------------------------------------------------------------------------------------------
	{ {0x89, 0xd7, 0x94, 0x3e, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     8192,   0x0008,   918,    30,     2,     0,    0,   &PhysicArchiPara4 },   // MLC32GW8IMA,MLC64GW8IMA, 29F32G08AAMD2, 29F64G08CAMD2
	{ {0x89, 0xd5, 0x94, 0x3e, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     4096,   0x0008,   918,    30,     2,     0,    0,   &PhysicArchiPara4 },   // 29F32G08CAMC1
	{ {0x89, 0xd7, 0xd5, 0x3e, 0xff, 0xff, 0xff, 0xff }, 1,     8,     128,     8192,   0x0008,   918,    30,     2,     0,    0,   &PhysicArchiPara4 },   // 29F64G08FAMC1
	{ {0x89, 0x68, 0x04, 0x46, 0xff, 0xff, 0xff, 0xff }, 1,     8,     256,     4096,   0x0208,   918,    30,     2,     0,    0,   &PhysicArchiPara4 },   // 29F32G08AAMDB
	{ {0x89, 0x88, 0x24, 0x4B, 0xff, 0xff, 0xff, 0xff }, 1,    16,     256,     4096,   0x0208,   918,    30,     2,     0,    0,   &PhysicArchiPara4 },    //  29F64G08CBAAA 29F64G083AME1
	{ {0x89, 0xA8, 0x25, 0xCB, 0xff, 0xff, 0xff, 0xff }, 2,    16,     256,     4096,   0x0208,   918,    30,     2,     0,    0,   &PhysicArchiPara4 },    //  29F64G08CBAAA 29F64G083AME1
	{ {0x89, 0x88, 0x24, 0x4B, 0xa9, 0x84, 0x00, 0x00 }, 1,    16,     256,     4096,   0x0788,   918,    40,     4,  0x500701,    0,   &PhysicArchiPara4 },    // JS29F64G08ACMF3 JS29F16B08CCMF3 JS29F32B08JCMF3
	//-------------------------------------------------------------------------------------------------------------------------
	{ {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,     0,    0,          0        },   // NULL
};


//==============================================================================
//=============================== ST NAND FLASH ================================
//==============================================================================
struct __NandPhyInfoPar_t StNandTbl[] =
{
    //              NAND_CHIP_ID                       DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode  ReadRetry  OperationPar
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x20, 0xf1, 0x80, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara0 },  // NAND01GW3B
    { {0x20, 0xf1, 0x00, 0x1d, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara0 },  // NAND01G001
    { {0x20, 0xda, 0x80, 0x15, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara0 },  // NAND02GW3B
    { {0x20, 0xda, 0x10, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara0 },  // NAND02GW3B2DN6
    { {0x20, 0xdc, 0x80, 0x95, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     4096,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara0 },  // NAND04GW3B
    { {0x20, 0xd3, 0xc1, 0x95, 0xff, 0xff, 0xff, 0xff }, 2,     4,      64,     4096,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara0 },  // NAND08GW3B
    //-------------------------------------------------------------------------------------------------------------------------
    { {0x20, 0xdc, 0x84, 0x25, 0xff, 0xff, 0xff, 0xff }, 1,     4,     128,     2048,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara2 },  // NAND04GW3C
    { {0x20, 0xd3, 0x85, 0x25, 0xff, 0xff, 0xff, 0xff }, 2,     4,     128,     2048,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara2 },  // NAND08GW3C
    { {0x20, 0xd3, 0x85, 0x25, 0xff, 0xff, 0xff, 0xff }, 4,     4,     128,     2048,   0x0000,   974,    15,    0,       0,   0,   &PhysicArchiPara2 },  // NAND16GW3C
    //-------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,    0,       0,   0,           0          },   // NULL
};

//==============================================================================
//============================ SPANSION NAND FLASH ==============================
//==============================================================================
struct __NandPhyInfoPar_t SpansionNandTbl[] =
{
    //                   NAND_CHIP_ID                 DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode   ReadRetry OperationPar
    //------------------------------------------------------------------------------------------------------------------------
    { {0x01, 0xaa, 0x10, 0x00, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     2048,   0x0000,   974,    30,     0,      0,   0,   &PhysicArchiPara0 },   // S39MS02G
    { {0x01, 0xa1, 0x10, 0x00, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    30,     0,      0,   0,   &PhysicArchiPara0 },   // S39MS01G
    { {0x01, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    30,     0,      0,   0,   &PhysicArchiPara0 },   // DFT01GR08P1PM0
    //------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,      0,   0,          0        },   // NULL
};

//==============================================================================
//============================ POWER NAND FLASH ==============================
//==============================================================================
struct __NandPhyInfoPar_t PowerNandTbl[] =
{
    //                   NAND_CHIP_ID                 DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode   ReadRetry OperationPar
    //------------------------------------------------------------------------------------------------------------------------
    { {0x92, 0xf1, 0x80, 0x95, 0x40, 0xff, 0xff, 0xff }, 1,     4,      64,     1024,   0x0000,   974,    30,     0,      0,   0,   &PhysicArchiPara0 },   // ASU1GA
    //------------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,      0,   0,          0        },   // NULL
};


//==============================================================================
//============================ SANDISK NAND FLASH ==============================
//==============================================================================
struct __NandPhyInfoPar_t SandiskNandTbl[] =
{
	//					 NAND_CHIP_ID				  DieCnt SecCnt  PagCnt   BlkCnt	OpOpt	DatBlk	Freq  EccMode	ReadRetry OperationPar
	//------------------------------------------------------------------------------------------------------------------------
	{ {0x45, 0xde, 0x94, 0x93, 0xff, 0xff, 0xff, 0xff }, 1, 	32,		256, 	2048,	0x0188,   950,	  40,	  4,	  0x301409,   0,	&PhysicArchiPara0 },   // SDTNQGAMA-008G
	{ {0x45, 0xd7, 0x84, 0x93, 0xff, 0xff, 0xff, 0xff }, 1, 	32,		256, 	1024,	0x0180,   950,	  40,	  4,	  0x301409,   0,	&PhysicArchiPara0 },   // SDTNQFAMA-004G
	{ {0x45, 0xde, 0xa4, 0x82, 0x76, 0xd7, 0xff, 0xff }, 1, 	16,		256, 	4096,	0x0188,   950,	  40,	  4,	  0x301409,   3,	&PhysicArchiPara0 },   // 008G
	//------------------------------------------------------------------------------------------------------------------------
	{ {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0, 	0,		 0, 	   0,	0x0000, 	0,	   0,	  0,	  0,   0,		   0		},	 // NULL
};


//==============================================================================
//============================= DEFAULT NAND FLASH =============================
//==============================================================================
struct __NandPhyInfoPar_t DefaultNandTbl[] =
{
    //                    NAND_CHIP_ID                DieCnt SecCnt  PagCnt   BlkCnt    OpOpt   DatBlk  Freq  EccMode  ReadRetry  OperationPar
    //-----------------------------------------------------------------------------------------------------------------------
    { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }, 0,     0,       0,        0,   0x0000,     0,     0,     0,     0,    0,  &DefualtPhysicArchiPara }, //default
};



