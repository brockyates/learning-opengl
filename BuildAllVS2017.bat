call %~dp0vendor\bin\premake\premake5.exe vs2017
msbuild.exe %~dp0Graphics.sln /t:Clean /p:Configuration=Debug
msbuild.exe %~dp0Graphics.sln /t:Clean /p:Configuration=Release

msbuild.exe %~dp0Graphics.sln /t:Rebuild /p:Configuration=Debug
msbuild.exe %~dp0Graphics.sln /t:Rebuild /p:Configuration=Release

%~dp0bin\Debug-windows-x86_64\Graphics.UnitTests\Graphics.UnitTests.exe
%~dp0bin\Release-windows-x86_64\Graphics.UnitTests\Graphics.UnitTests.exe
