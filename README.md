	CB_update_boot0

This is a modified version of update_boot0 found in an H3 SoC release called Draco.

Apparently there are two versions of boot records (boot0.h and boot_v2.h).  However,
the only difference I can see is the format of the NAND parameters in the storage
area in the private header.

One change made here is that the dram_para array size is 20 while the original record
had an array size of 32.  Not sure why 32 is specified as all files I checked had the
smaller array.

This modified program also has code to load the NAND chip details.  boot0 will not load
from NAND unless these details are correct.  Programs such as Livesuit and Phoenixsuit
load these details but I haven't found any other programs that do so.


	Fixing boot0, boot1.

This program is primarily used to customise boot0 before writing it to NAND.

The run command is update_boot0 <boot0 file ID> <script file ID> NAND [NAND chip ID].

e.g. update_boot0  boot0.bin  script.bin  NAND  ADD794DA

The script file is parsed for DRAM and NAND details.

If the optional NAND ID (e.g. ADD794DA) is included then update_boot0 will update the chip ID
and details included in the boot0 file.

