	CB_update_boot0

This is a modified version of update_boot0 found in an H3 SoC release called Draco.

The original update_boot0 program uses version 2 boot records.  These are used for A20
and H3 (and many others) setups.

The modified program uses version 1 boot records as used in A10 releases.

This modified program also has code to load the NAND chip details.  boot0 will not load
from NAND unless these details are correct.  Programs such as Livesuit and Phoenixsuit
load these details but I haven't found any other programs that do so.


	Running update_boot0

This program is primarily used to customise boot0 before writing it to NAND.

The run command is update_boot0 &lt;boot0 file ID&gt; &lt;script file ID&gt; NAND [NAND chip ID].

e.g. update_boot0  boot0.bin  script.bin  NAND  ADD794DA

The script file is parsed for DRAM and NAND details.

If the optional NAND ID (e.g. ADD794DA) is included then update_boot0 will update the chip ID
and details included in the boot0 file.

