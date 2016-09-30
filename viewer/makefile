
all:	free checked

checked:
	msbuild /p:Configuration=Debug VidUSB2.vcproj 

free:
	msbuild /p:Configuration=Release VidUSB2.vcproj "Release|Win32"

clean:
	erase /q Release
	erase /q Debug
