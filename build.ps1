<###
.USAGE
  pwsh ./build.ps1                 # Debug build
  pwsh ./build.ps1 -Config Release # Release build
  pwsh ./build.ps1 -Run            # Build + run
  pwsh ./build.ps1 -Test           # Build + ctest
  pwsh ./build.ps1 -Clean          # Remove build dir

#>

param(
  [ValidateSet('Debug','Release','RelWithDebInfo','MinSizeRel')]
  [string]$Config = 'Debug',

  [switch]$Run,
  [switch]$Test,
  [switch]$Clean,

  [int]$Jobs = 0
)

$ErrorActionPreference = 'Stop'

function Require-Command($name) {
  if (-not (Get-Command $name -ErrorAction SilentlyContinue)) {
    throw "$name not found on PATH. Install it to build from source."
  }
}

Require-Command cmake

$buildDir = Join-Path -Path 'build' -ChildPath $Config

if ($Clean) {
  Write-Host "[clean] Removing $buildDir"
  if (Test-Path $buildDir) { Remove-Item -Recurse -Force $buildDir }
}

Write-Host "[configure] $Config -> $buildDir"
cmake -S . -B $buildDir -DCMAKE_BUILD_TYPE=$Config

Write-Host "[build] $Config"
if ($Jobs -gt 0) {
  cmake --build $buildDir --parallel $Jobs --config $Config
} else {
  cmake --build $buildDir --parallel --config $Config
}

if ($Test) {
  Write-Host "[test]"
  ctest --test-dir $buildDir --output-on-failure -C $Config
}

if ($Run) {
  $candidates = @(
    (Join-Path $buildDir 'HexPip.exe'),
    (Join-Path $buildDir (Join-Path $Config 'HexPip.exe')),
    (Join-Path $buildDir (Join-Path 'Debug' 'HexPip.exe')),
    (Join-Path $buildDir (Join-Path 'Release' 'HexPip.exe'))
  )

  $exe = $candidates | Where-Object { Test-Path $_ } | Select-Object -First 1
  if (-not $exe) {
    throw "Could not find built executable. Look inside $buildDir."
  }

  Write-Host "[run] $exe"
  $exeDir = Split-Path -Parent $exe
  Push-Location $exeDir
  try {
    & (Split-Path -Leaf $exe)
  } finally {
    Pop-Location
  }
}
