@echo off
rem
rem PostBuild step examples: 
rem
rem   call _VERSION.BAT /RELEASEU $(TargetName) "$(TargetPath)"
rem   call _VERSION.BAT /RELEASE  $(TargetName) "$(TargetPath)"
rem   call _VERSION.BAT /DEBUGU   $(TargetName) "$(TargetPath)"
rem   call _VERSION.BAT /DEBUG    $(TargetName) "$(TargetPath)"

echo Version update %1...

if "/RELEASEU"=="%1" call j:\vr\key\env /PCS %2 %3 FULL NONE ANY SRSTools\SRSLogView
