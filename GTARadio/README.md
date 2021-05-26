# GTA Radio Arduino
Code for the GTA Radio project.

Arduino project to make a "radio" that plays the music from GTA radio stations. Currently, only GTA V stations have been ripped & confirmed to work.

# Commands used to organise stations & songs
All songs were ripped with OpenIV

If you have ripped the songs as well, you will need to organise them to be usable in this program with the commands below, IN THE ORDER THEY APPEAR. Be warned that you will also need about 17GB for storage.

Unfortunately, there are two types of stations:
- Ones with host voicelines, general voicelines, and songs split into files     - Split stations
- Ones with voicelines, songs, etc. mixed all into one or multiple files        - Unsplit stations

Additional note: most files that start with 0x can be removed, except for unsplit stations.

For Unsplit stations, we just need to use a tool like Audacity to merge the files together (as well as audio channels).

For Split stations, we need to manually 

There are a few things we want to do: 
- Seperate the songs from everything else
- Move files out of their subfolders

First, we want to move all the non-song files into their seperate folders. For some of them, this is already done: general, intro, time, to

set path=PATH_TO_YOUR_FILES

Secondly, we want to move all the other non-song files: id and mono
FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\mono_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\id_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\ID"

set stationName=18_90S_ROCK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\mono_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\%stationName%\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\id_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\%stationName%\ID"

Move the song folders manually (unfortunately) into the SONGS folder.

In the SONGS folder, execute the following command:
set stationName=01_CLASS_ROCK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"

Bulk command
set path=PATH_TO_YOUR_FILES
set stationName=01_CLASS_ROCK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=02_POP
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=03_HIPHOP_NEW
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=04_PUNK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=05_TALK_01
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=06_COUNTRY
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=09_HIPHOP_OLD
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=11_TALK_02
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=12_REGGAE
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=15_MOTOWN
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=16_SILVERLAKE
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=17_FUNK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
set stationName=18_90S_ROCK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"

There is no easy way

FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK"

//want to 
	- ignore folder general, time, to
	- put mono, id into 1 folder
	- rest into songs folder

FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN ([] ![]*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\SONGS"

FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\mono_*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\id_*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\ID" WORKS

JUST DO SONGS LAST AFTER MOVE
FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\![id_*, mono_*, general_*, to_*, time_*].wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\SONGS"