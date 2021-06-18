# GTA Radio Arduino
Arduino project to make a "radio" that plays the music from GTA radio stations. After lots of work & time, all GTA V and GTA IV stations have been ripped and work!

# Useful notes
File and directory names cannot be longer than 8 characters. A full path can be longer than 8 characters.

- someaudiofile.wav won't work
- someaudio/file.wav won't work
- some/audio/file.wav will work

Adding the full folder as an album to Groove Music can really bug playback, and wrong files can be played!

# Requesting audio
As none of the audio belongs to me, I cannot make the converted audio files publicly available. However you can email me and I'll give you a link to the converted & organized files, that have also had the appropriate Metadata added to them.

# Converting files yourself
## Converting Audio
The audio library used needs a very specific wav format, or it won't work as intended. Only WAV files are accepted, they must be Mono (unless configuring Stereo), they must have a sample rate between 8-32kHz and encoded in Unsigned 8-BIT PCM. (GTA V is encoded at 48 kHz, some at 44100Hz, with 32 bit something)
- Converting Stereo to mono : https://forum.audacityteam.org/viewtopic.php?t=57821

- Not really helpful but in case : https://github.com/TMRh20/TMRpcm/issues/125

## Desired audio directory structure
https://stackoverflow.com/questions/19699059/representing-directory-file-structure-in-markdown-syntax
```
root
└───ADS                 : all the ads in their own seperate files (from GTA V & IV), renamed to increasing numbers starting at 0
│   │   0.wav
│   │   1.wav
│   │   2.wav
│   └───...
│
└───unsplit station     : unsplit stations have a single SRC.wav file for their audio
│   └───SRC.wav
│ 
└───talkshow station    : talkshow stations have ID audio introducing the station, and MONO which are the talkshows
│   └───ID
│   │   │   ID_1.wav
│   │   │   ID_2.wav
│   │   └───...
│   │
│   └───MONO    : talkshows audio snippets
│       │   0.wav
│       │   1.wav
│       └───...
│
└───split station
    └───HOST    : radio host audio snippets, for file naming see talkshow MONO
    └───ID      : see talkshow ID
    └───INTRO   : host audio snippets that introduce SPECIFIC SONGS. Named by song number _ intro number i.e 0_1.wav. Song numbers start at 0 but intro numbers start at 1 (the latter numbering is taken from GTA filenames).
    │   │   0_1.wav
    │   │   0_2.wav
    │   │   1_1.wav
    │   └───...
    │
    └───SONGS   : songs duh, for file naming see talkshow MONO
    │   │   0.wav
    │   │   1.wav
    │   └───...
    │
    └───TIME    : more host audio, but specifically saying time of day. CURRENTLY UNUSED.
    └───TO
        └───AD      : host audio snippets introducing ad intermission
        └───NEWS    : host audio snippets introducing news intermission
        └───WEATH   : host audio snippets introducing news intermission (optional, for GTA IV stations ONLY). CURRENTLY UNUSED.
```

## Commands used to organise stations & songs
Both GENERAL and MONO in Split stations are the same : the station host just talking.
They have hence both been put into HOST
All songs were ripped with OpenIV

If you have ripped the songs, you will need to organise them to be usable in this program with the commands below, IN THE ORDER THEY APPEAR. Be warned that you will also need about 30 GB for storage before converting them to lower sample rates etc which should only take 6-7 GB.

Unfortunately, there are three types of stations:
- Ones with host voicelines, general voicelines, and songs split into files     - Split stations
- Ones with host voicelines, general voicelines, and songs split into files     - Talkshow stations
- Ones with voicelines, songs, etc. mixed all into one or multiple files        - Unsplit stations

Additional note: most files that start with 0x can be removed, except for unsplit stations.

There are a few things we want to do: 
- Seperate the songs from everything else
- Move files out of their subfolders

First, we want to move all the non-song files into their seperate folders. For some of them, this is already done: general, intro, time, to
```
set PATH_TO_YOUR_FILES=DRIVE:\PATH\TO\YOUR\FILES
```

News, Ads, Weather, ID, MONO. 
```
FOR /R "%PATH_TO_YOUR_FILES%\ADS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\ADS"
FOR /R "%PATH_TO_YOUR_FILES%\NEWS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\NEWS"
FOR /R "%PATH_TO_YOUR_FILES%\WEATHER" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\WEATHER" (specific to GTA IV)

set stationName=18_90S_ROCK

FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\mono_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\%stationName%\MONO"
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%" %i IN (\id_*.wav) DO COPY "%i" "%PATH_TO_YOUR_FILES%\%stationName%\ID"
```

In the SONGS folder, execute the following command:
```
set stationName=01_CLASS_ROCK
FOR /R "%PATH_TO_YOUR_FILES%\%stationName%\SONGS" %i IN (*.wav) DO MOVE "%i" "%PATH_TO_YOUR_FILES%\%stationName%\SONGS"
```

GTA V Stations
```
set stationName=01_CROCK
set stationName=02_POP
set stationName=03_HH_N
set stationName=04_PUNK
set stationName=05_T1
set stationName=06_CUNT
set stationName=09_HH_O
set stationName=11_T2
set stationName=12_REGG
set stationName=15_MTWN
set stationName=16_SILK
set stationName=17_FUNK
set stationName=18_90RK
```

GTA IV Stations
```
set stationName=A_AFRO
set stationName=B_BBYLN
set stationName=C_BEAT
set stationName=D_BK
set stationName=E_CLASS
set stationName=F_DANM
set stationName=G_DANR
set stationName=8_EXTRA_TRACKS
set stationName=H_FUS
set stationName=I_HARD
set stationName=J_JAZZ
set stationName=K_K109
set stationName=L_LZLW
set stationName=M_LIBR
set stationName=N_MED
set stationName=O_NYCL
set stationName=P_PLR
set stationName=Q_RJFM
set stationName=R_SJS
set stationName=S_VIBE
set stationName=T_VCFM
set stationName=U_VLAD
set stationName=V_WKTT
```


## Commands to bulk rename files
After having reorganised the files & folders, all of the files & folders must also be renamed. This is because the Arduino SD package that handles reading audio files uses the (8.3 filename)[https://en.wikipedia.org/wiki/8.3_filename] convention, which only supports file and directory names up to 8 characters long.

The files that can be renamed by bulk command are those in GENERAL, MONO, TIME, and TO. INTRO and SONGS have to be done manually. ID doesn't need any renaming.

In the root directory of your audio files, execute the following commands
```
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "GENERAL","GEN"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "MONO_SOLO","MONO"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "EVENING","EVE"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "MORNING","MORN"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "TO_AD","TAD"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "TO_NEWS","TNEW"}
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "TO_WEATHER","TWET"}
```

News and Ad files don't need any sort of name, so can be renamed just by incrementing number:

```
$i = 0
Get-ChildItem -Path D:\(ADS or NEWS) -Filter *.wav |
ForEach-Object {
   $extension = $_.Extension
   $newName = "{0:d3}{1}" -f  $i, $extension
   $i++
   Rename-Item -Path $_.FullName -NewName $newName
}
```

News, Ads, MONO, TIME, and TO files need their leading zeroes removed, which can be done with either:
- Running the following command twice
```
dir | rename-item -NewName {$_.name -replace "^0",""}
```

- Running the following once, but renaming the zero-th file from ".wav" to "0.wav"
```
Get-ChildItem -Recurse | rename-item -NewName {$_.name -replace "_0","_"}
```

The hardest is renaming BOTH songs & intros to match. As I wanted meta data to be added as well (Song Name, Artist, Year), this has to all be done manually.

Songs are just numbered starting at 0. Each song's intro is then named by the song's number, and the number of the intro. I.e. for song 6, the second intro's filename would be
```
6_2.wav
```