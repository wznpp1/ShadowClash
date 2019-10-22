import os
import platform

if __name__ == "__main__":
    print("[-] delete old files...")
    if platform.system() == "Windows":
        os.system("del /f /q ./resources/Country.mmdb")
        os.system("del /f /q ./resources/clashxdashboard")
        os.system("del /f /q ./resources/yacddashboard")
        os.system("del /f /q GeoLite2-Country.*")
    else:
        os.system("rm -f ./resources/Country.mmdb")
        os.system("rm -rf ./resources/clashxdashboard")
        os.system("rm -rf ./resources/yacddashboard")
        os.system("rm -f GeoLite2-Country.*")
    print("[+] install mmdb...")
    if platform.system() == "Windows":
        os.system("certutil")
    else:
        os.chdir("resources")
    print("[+] install clashx dashboard...")
    os.system("git clone -b gh-pages https://github.com/Dreamacro/clash-dashboard.git clashxdashboard")
    print("[+] install yacd dashboard...")
    os.system("git clone -b gh-pages https://github.com/haishanh/yacd.git yacddashboard")
    os.chdir("..")
    