.PHONY: clean All

All:
	@echo ----------Building project:[ test_lambda_mgw - Debug ]----------
	@"D:\MinGW\bin\mingw32-make.exe"  -j 4 -f -std=c++0x "test_lambda_mgw.mk"
clean:
	@echo ----------Cleaning project:[ test_lambda_mgw - Debug ]----------
	@"D:/MinGW/bin/mingw32-make.exe"  -j 4 -f -std=c++0x "test_lambda_mgw.mk" clean
