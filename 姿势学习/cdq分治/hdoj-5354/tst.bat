:loop
python mkdata.py
main
main2
fc 1.out 2.out
if errorlevel==1 pause
goto loop