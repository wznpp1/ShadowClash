import os
import shutil
import platform

if __name__ == "__main__":
    print("[+] Making dir...")
    try:
        os.mkdir("framework")
    except:
        pass
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
        os.system("certutil.exe -urlcache -split -f http://geolite.maxmind.com/download/geoip/database/GeoLite2-Country.tar.gz")
        os.system("7z.exe x GeoLite2-Country.tar.gz")
        os.system("move GeoLite2-Country_*/GeoLite2-Country.mmdb ./resources/Country.mmdb")
        os.system("del /f /q GeoLite2-Country.tar.gz")
        os.system("del /f /q GeoLite2-Country_*")
    else:
        os.system("curl -O http://geolite.maxmind.com/download/geoip/database/GeoLite2-Country.tar.gz")
        os.system("tar -zxvf GeoLite2-Country.tar.gz")
        os.system("mv GeoLite2-Country_*/GeoLite2-Country.mmdb ./resources/Country.mmdb")
        os.system("rm GeoLite2-Country.tar.gz")
        os.system("rm -r GeoLite2-Country_*")
    os.chdir("resources")
    print("[+] install clashx dashboard...")
    os.system("git clone -b gh-pages https://github.com/Dreamacro/clash-dashboard.git clashxdashboard")
    print("[+] install yacd dashboard...")
    os.system("git clone -b gh-pages https://github.com/haishanh/yacd.git yacddashboard")
    print("[+] Compiling yaml-cpp...")
    os.system("git clone https://github.com/jbeder/yaml-cpp.git")
    os.chdir("yaml-cpp")
    os.mkdir("build")
    os.chdir("build")
    os.system("cmake ../")
    os.system("make -j8")
    if platform.system() == "Windows":
        if os.environ.get("CI", False):
            print("[*] Debug: %s"%os.getcwd())
        os.system("move ibyaml-cpp.a ../../../framework/")
    else:
        if os.environ.get("CI", False):
            print("[*] Debug: %s"%os.getcwd())
        os.system("mv libyaml-cpp.a ../../../framework/")
    os.chdir("..")
    os.chdir("..")
    shutil.rmtree("yaml-cpp", ignore_errors=True)