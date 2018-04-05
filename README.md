## Snes9xTYL Mod

Super Nintendo emulator for PlayStation Portable.

Download the latest compiled commit here: https://github.com/esmjanus/snes9xTYL/blob/mecm/Release/Versions.md

***Before updating, make sure to backup your SAVES and/or S9XTYLSAVES folders just in case something goes wrong.

### Help and Tips

- Some games run faster if "Ignore Palette writes" and/or "Simple Palette writes" are enabled on MISC->Hack/debug menu.
- If you get a black screen at loading a game, you can try to disable "Speed hacks" on MISC->Hack/debug menu, and then load the game again.

-------------------------------------------------------------------------------------------------------

### Features

- Standby/sleep mode on "me" version.
- Netplay (multiplayer) suppport.
- Zipped ROM support.
- IPS patch file (have to be the same name as game with .IPS extension : SOE.ZIP => SOE.IPS)
- Compressed Savestate with small screenshot.
- Auto save of SRAM on game change, exit & Snes reset so you should never lose them ;-).
- Autoskip.
- Gamma correction.
- VSync support.
- SDD1 encrypted roms (Star Ocean, Street Fight Alpha 2,...)
- SA1 (slow), SuperFX (slow), C4, DSP1, DSP2, DSP3, DSP4 support.
- Multiple sound frequencies : 22Khz, 32Khz, 44Khz.
- Multiple stretching mode with or without smoothing
- Detailed Battery informations.
- 222, 266, 300 & 333Mhz PSP frequency.
- Snapshot based Icon per game. Take a snapshot while ingame (using GUI) & then you'll have it in file browser.
- 5 Rendering mode:
	- Mode0 : Optimized Snes9x
	- Mode1 : Original Snes9x 
	- Mode2 : Hardware accelerated (using PSP's GU)
	- Mode3 : Adaptive rendering Mode 2 + Mode 1 (default)
	- Mode4 : Adaptive rendering Mode 2 + Mode 0
Yes you read well, this version support nearly all the graphics effects of the Snes accelerated with PSP hardware.
Except : offset mode & mode 7. Priority and blending are fully emulated.
For the moment a few graphic glitches remain, we did our best for the moment in our knowledge. Please understand.

-------------------------------------------------------------------------------------------------------

### Install

/PSP/GAME/snes9xTYL/ (or any other folder)
+ EBOOT.PBP
+ logo.bmp           

You can put the rom files anywhere you want, a "SAVES" subdirectory will be created in your install directory.
All savestate files, sram files & jpg snapshots will be written in the "SAVES" subdir.

-------------------------------------------------------------------------------------------------------

### Play

Default controls :

PSP								|SNES		
|-------------------------------|-------------------|
|pad							|pad				|
|LEFT TRIGGER + RIGHT TRIGGER	|menu (cm version)	|
|CROSS							|A					|
|CIRCLE							|B					|
|SQUARE							|X					|
|TRIANGLE						|Y					|
|START							|START				|
|SELECT							|SELECT				|
|LEFT TRIGGER					|L					|
|RIGHT TRIGGER					|R					|

-------------------------------------------------------------------------------------------------------

### Change History

v171023
- Added support for Far East of Eden - Tengai Makyou Zero english translation.

v171017
- Fixed a bug on snes9xTYL Mod 171008 that may corrupt savestates on some games.

v171008
- Fixed a bug on Super Mario RPG that was causing graphical glitches on battles if speedhacks from snesadvance.dat were not enabled.
- Improved accuracy of Super FX emulation.
- Replaced SA1 option on MISC->Hack/debug menu for SFX overclock to control speed/accuracy.
- Added a new option to adjust sound volume level on SOUND menu (Higher values can cause noise on some games).
- Added compatibility for SD Gundam GX, and Top Gear 3000/The Planet's Champ TG3000.
- Fixed Dungeon Master.
- Added speedhack for Ace o Nerae (and his english translation: Aim for the Ace v1.2) from snes9x 3DS.
- Added Brunnis input lag fix from snes9x2010 (Reduce input lag by 1 frame).

v170828
- Improved sound emulation.
- Fixed a bug on Super Double Dragon (If START button was pressed, the second player was activated and controlled by the same gamepad).
- Fixed Fire Emblem: Genealogy of the Holy War/Seisen no Keifu english translation.
- Fixed Mega Man X3: Zero Project romhack.
- Added some optimize compiler options.
- Minor changes and optimizations.

v170727
- Fixed Speed hacks option that wasn't saved separately for each game.
- Added optimizations for SA1 games.**
- Added support for Super Mario World VLDC 9 romhack.**
- Added code to apply hardcoded speedhack patches for the main CPU and SA1 games.**
- Added instructions to specifically allow games to wake the SA1 chip from the main CPU.**
- Implemented SA1 sleep speedhack on the following games:**
	- Super Mario RPG.
	- Kirby’s Dreamland.
	- Jikkyou Oshaberi Parodius.
	- Kirby Super Star.
	- Marvelous.
	- Super Robot Taisen.
	- Panic Bomber World.
	- Dragon Ball Hyper Dimension.
	- SD Gundam Next.
	- Power Rangers Zeo.
	- Daisenryaku Expert 2.
	- Masters New Augusta 3.
	- Bass Fishing.
	- J96 Dream Stadium.
	- Shining Scorpion.
	- Pebble Beach New.
	- PGA European Tour.
	- SD F1 Grand Prix.
- Minor changes and optimizations.
**Changes based on snes9x 3DS.

v170521
- Fixed getting back to XMB menu at starting the emulator due to a wrong Heap size on ME version.
- Fixed savestates.
- Fixed SAVES folder detection.
- Enabled PSP Clockspeed change on ME version.
- Enabled adhoc/netplay suppport.
- Added standby/sleep mode on ME version, but it is disabled during netplay to prevent losing adhoc connection.
- Optimized Offset per Tile renderer, this gives an speed boost on some games like StarFox, Tetris Attack, Kirby's Avalanche, Strike Gunner STG, etc. Thanks to snes9x_3DS by @bubble2k16.

-------------------------------------------------------------------------------------------------------

## Credits

### Special Thanks to
- Snes9x team for the fantastic SNES emulator.
- YoyoFR and Laxer3a for official Snes9xTYL.
- Ruka, 33(76) for mod of mecm.
- 173210 for mod of Snes9xTYLmecm 091127.
- bubble2k16 for his work on Snes9x3DS. Many optimisations were ported from his version.

### Notes by YoyoFR

snes9xTYL is based on:

Little John for PalmOS - SNES module
--> LJP : http://yoyofr92.free.fr

which is based on Snes9x 1.39
--> SNES9X : http://www.snes9x.com

unofficial PSPSDK from psp2dev community
--> www.ps2dev.org
great work!

Personal thanks to : smiths, chp, bifuteki.

Have fun!

http://yoyofr92.free.fr

yoyofr
