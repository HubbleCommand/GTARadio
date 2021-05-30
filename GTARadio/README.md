# GTA Radio Arduino
Code for the GTA Radio project.

Arduino project to make a "radio" that plays the music from GTA radio stations. Currently, only GTA V stations have been ripped & confirmed to work.

# Useful notes
- file and directory names cannot be longer than 8 characters. A full path can be longer than 8 characters thought.

someaudiofile.wav won't work
someaudio/file.wav won't work
some/audio/file.wav will work

Adding the full folder as an album to Groove Music can really bug playback. The wrong file can be played, so don't add it as an album to Groove Music

# Requesting audio
As none of the audio belongs to me, I cannot make the converted audio files publicly available. However you can email me and I'll give you a link to download the converted & organized files.

# Converting files yourself
## Converting Audio
The library used needs a very specific wav format, or it won't work as intended. Only WAV files are accepted, and they must have a sample rate between 8-32kHz and encoded in Unsigned 8-BIT PCM.
- Converting Stereo to mono : https://forum.audacityteam.org/viewtopic.php?t=57821

- Not really helpful but in case : https://github.com/TMRh20/TMRpcm/issues/125

## Commands to bulk rename files
After having reorganised the files & folders (see the appropriate section), all of the files & folders must also be renamed. This is because the file utility only supports files with names up to 8 characters long.

The files that can be renamed by bulk command are those in GENERAL, MONO, TIME, and TO. INTRO and SONGS have to be done more manually. ID doesn't need any renaming.

dir | rename-item -NewName {$_.name -replace "GENERAL","GEN"}
dir | rename-item -NewName {$_.name -replace "MONO_SOLO","MONO"}
dir | rename-item -NewName {$_.name -replace "EVENING","EVE"}
dir | rename-item -NewName {$_.name -replace "MORNING","MORN"}
dir | rename-item -NewName {$_.name -replace "TO_AD","TAD"}
dir | rename-item -NewName {$_.name -replace "TO_NEWS","TNEW"}

News and Ad files don't need any sort of name, so can be renamed just by incrementing number:

$i = 0
Get-ChildItem -Path D:\(ADS or NEWS) -Filter *.wav |
ForEach-Object {
   $extension = $_.Extension
   $newName = "{0:d3}{1}" -f  $i, $extension
   $i++
   Rename-Item -Path $_.FullName -NewName $newName
}


The hardest is renaming BOTH songs & intros to match! As I wanted meta data to be added as well (Song Name, Artist, Year), this has to all be done manually.


## Commands used to organise stations & songs
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

set PATH_TO_YOUR_FILES=DRIVE:\PATH\TO\YOUR\FILES

News & Ads
FOR /R "%PATH_TO_YOUR_FILES%\ADS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\ADS"
FOR /R "%PATH_TO_YOUR_FILES%\NEWS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\NEWS"

Secondly, we want to move all the other non-song files: id and mono
FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\mono_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK" %i IN (\id_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\01_CLASS_ROCK\ID"

set stationName=18_90S_ROCK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\mono_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\%stationName%\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\id_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\%stationName%\ID"

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
