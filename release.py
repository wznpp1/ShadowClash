import os
import platform

if __name__ == "__main__":
    if platform.system() == "Windows":
        print("[+] Release type -> Windows")
        os.system("move ./resources/clashxdashboard ./build/clashxdashboard")
        os.system("move ./resources/yacddashboard ./build/yacddashboard")
        os.chdir("build")
        os.system("windeployqt ShadowClash.exe")
        os.system("del *.o *.h *.cpp *.stash *.qrc Makefile")
        os.system("zip -r ShadowClash-windows.zip *")
        print("[+] Release Windows -> Done")
    elif platform.system() == "Darwin":
        print("[+] Release type -> Darwin")
        os.chdir("build")
        os.system("macdeployqt ShadowClash.app")
        os.system("rm -rf *.o *.h *.cpp *.stash *.qrc Makefile")
        os.system("zip -r ShadowClash-osx.zip ShadowClash.app")
        print("[+] Release Darwin -> Done")
    elif platform.system() == "Linux":
        print("[+] Release type -> Linux")
        os.system("cp ./resources/clashxdashboard ./build/clashxdashboard")
        os.system("cp ./resources/yacddashboard ./build/yacddashboard")
        os.chdir("build")
        os.system("rm -rf *.o *.h *.cpp *.stash *.qrc Makefile")
        os.system("zip -r ShadowClash-linux.zip *")
        print("[+] Release Linux -> Done")