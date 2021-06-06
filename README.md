# GTA Radio Arduino
Arduino project to make a "radio" that plays the music from GTA radio stations. Currently, only GTA V stations have been ripped & confirmed to work.

# Useful notes
File and directory names cannot be longer than 8 characters. A full path can be longer than 8 characters.

- someaudiofile.wav won't work
- someaudio/file.wav won't work
- some/audio/file.wav will work

Adding the full folder as an album to Groove Music can really bug playback, and wrong files can be played!

# TODOs
- calculate used ram? https://forum.arduino.cc/t/measure-sram-memory-use/415346

# Requesting audio
As none of the audio belongs to me, I cannot make the converted audio files publicly available. However you can email me and I'll give you a link to the converted & organized files. Not all stations have been prepared, as some require vast amounts of manual conversion.

# Converting files yourself
## Converting Audio
The audio library used needs a very specific wav format, or it won't work as intended. Only WAV files are accepted, and they must have a sample rate between 8-32kHz and encoded in Unsigned 8-BIT PCM. (GTA V is encoded at 48 kHz, some at 44100Hz, with 32 bit something)
- Converting Stereo to mono : https://forum.audacityteam.org/viewtopic.php?t=57821

- Not really helpful but in case : https://github.com/TMRh20/TMRpcm/issues/125

## Commands to bulk rename files
After having reorganised the files & folders (see the appropriate section), all of the files & folders must also be renamed. This is because the file utility only supports files with names up to 8 characters long.

The files that can be renamed by bulk command are those in GENERAL, MONO, TIME, and TO. INTRO and SONGS have to be done manually. ID doesn't need any renaming.

In the root directory of your audio files, execute the following commands

Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "GENERAL","GEN"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "MONO_SOLO","MONO"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "EVENING","EVE"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "MORNING","MORN"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "TO_AD","TAD"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "TO_NEWS","TNEW"}

In the MONO, TIME, and TO directories, you will also need to run
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "_0","_"}

News and Ad files don't need any sort of name, so can be renamed just by incrementing number:

$i = 0
Get-ChildItem -Path D:\(ADS or NEWS) -Filter *.wav |
ForEach-Object {
   $extension = $_.Extension
   $newName = "{0:d3}{1}" -f  $i, $extension
   $i++
   Rename-Item -Path $_.FullName -NewName $newName
}

You can then remove the leading zeroes by running the following command twice
dir | rename-item -NewName {$_.name -replace "^0",""}

The hardest is renaming BOTH songs & intros to match. As I wanted meta data to be added as well (Song Name, Artist, Year), this has to all be done manually.


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
FOR /R "%PATH_TO_YOUR_FILES%\WEATHER" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\WEATHER" (specific to GTA IV)

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
set stationName=02_POP
set stationName=03_HIPHOP_NEW
set stationName=04_PUNK
set stationName=05_TALK_01
set stationName=06_COUNTRY
set stationName=09_HIPHOP_OLD
set stationName=11_TALK_02
set stationName=12_REGGAE
set stationName=15_MOTOWN
set stationName=16_SILVERLAKE
set stationName=17_FUNK
set stationName=18_90S_ROCK

For GTA IV

FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\SOLO_*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\id_*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\ID"

set stationName=10_HARDCORE
set stationName=11_INDEPENDENCE (is this even a station)
set stationName=12_JAZZ_NATION
set stationName=13_K109
set stationName=14_LAZLOW
set stationName=15_LIBERTY_ROCK
set stationName=16_MEDITATION
set stationName=17_NY_CLASSICS
set stationName=18_PLR
set stationName=19_RAMJAM_FM
set stationName=1_AFRO_BEAT
set stationName=20_SAN_JUAN_SOUNDS
set stationName=21_THE_VIBE
set stationName=22_VCFM
set stationName=23_VLADIVOSTOK
set stationName=24_WKTT
set stationName=2_BABYLON
set stationName=3_BEAT
set stationName=4_BOBBY_KONDERS
set stationName=5_CLASSICAL_AMBIENT
set stationName=6_DANCE_MIX
set stationName=7_DANCE_ROCK
set stationName=8_EXTRA_TRACKS
set stationName=9_FUSION

FOR EXTRA TRACKS
FOR /R "%PATH_TO_YOUR_FILES%\8_EXTRA_TRACKS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\8_EXTRA_TRACKS"