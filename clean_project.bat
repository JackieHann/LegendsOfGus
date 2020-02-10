@echo off
rmdir /s /q Binaries
rmdir /s /q Build
rmdir /s /q build
rmdir /s /q DerivedDataCache
rmdir /s /q Debug
rmdir /s /q Saved
rmdir /s /q Intermediate
rmdir /s /q .vs
del /s /q *.log
del /s /q *.VC.db
del /s /q *.sln