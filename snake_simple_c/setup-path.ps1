# setup-path.ps1
# Run once to add SDL3.dll's folder to your User PATH.

$sdlBin = "C:\libs\SDL3-3.4.4\x86_64-w64-mingw32\bin"

$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
$entries = if ($userPath) { $userPath -split ';' } else { @() }

if ($entries -contains $sdlBin) {
  Write-Host "Already on User PATH: $sdlBin"
}
else {
  $newPath = if ($userPath) { "$userPath;$sdlBin" } else { $sdlBin }
  [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
  Write-Host "Added to User PATH: $sdlBin"
  Write-Host "Open a new terminal for the change to take effect."
}
