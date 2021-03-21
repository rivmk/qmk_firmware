@ECHO OFF

choice /C YNXD /T 2 /D X /M "Flash LED too? [Y]es | [N]o | [D]ev" /N
if %ERRORLEVEL% EQU 3 goto flashKey
timeout 10 /nobreak
if %ERRORLEVEL% EQU 1 goto flashLED
if %ERRORLEVEL% EQU 2 goto flashKey
if %ERRORLEVEL% EQU 4 goto flashKey

:flashKey
C:\AnnePro2-Tools-master\target\release\annepro2_tools.exe \\wsl$\Ubuntu-20.04\home\tmb\git\tmb_qmk\annepro2_c18_default.bin -i=-1 --boot
goto end

:flashDev
C:\AnnePro2-Tools-master\target\release\annepro2_tools.exe \\wsl$\Ubuntu-20.04\home\tmb\git\tmb_qmk\annepro2_c18_default-dev.bin -i=-1 --boot
goto end

:flashLED
C:\AnnePro2-Tools-master\target\release\annepro2_tools.exe \\wsl$\Ubuntu-20.04\home\tmb\git\tmb_qmk\annepro2_c18_default.bin -i=-1
C:\AnnePro2-Tools-master\target\release\annepro2_tools.exe --boot -t led \\wsl$\Ubuntu-20.04\home\tmb\git\annepro2-shine\build\annepro2-shine-C18.bin -i=-1

:end