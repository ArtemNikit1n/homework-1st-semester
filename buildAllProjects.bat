@echo off
setlocal EnableDelayedExpansion

set "ScriptDir=%~dp0"

for /f "tokens=1,2 delims==*" %%a in (config.txt) do (
  set "SolutionName=%%a"
  set "RelativePath=%%b"
  set "FullPath=!ScriptDir!!RelativePath!"

  echo Processing solution: !SolutionName! (!FullPath!)

  if exist "!FullPath!" (
    msbuild "!FullPath!" /t:Rebuild /p:Configuration=Release /p:Platform=x64 /clp:Summary  
    if !errorlevel! neq 0 (
      echo Error building "!SolutionName!".
    ) else (
      echo Successfully built "!SolutionName!"
    )
  ) else (
    echo Error: Solution file "!FullPath!" not found.
  )
)

endlocal
echo Done. 