call vendor\bin\premake\premake5.exe vs2017
msbuild.exe Graphics.sln /t:Clean /p:Configuration=Debug
msbuild.exe Graphics.sln /t:Clean /p:Configuration=Release

msbuild.exe Graphics.sln /t:Rebuild /p:Configuration=Debug
msbuild.exe Graphics.sln /t:Rebuild /p:Configuration=Release

bin\Debug-windows-x86_64\Graphics.UnitTests\Graphics.UnitTests.exe
bin\Release-windows-x86_64\Graphics.UnitTests\Graphics.UnitTests.exe
