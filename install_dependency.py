import os
import shutil
import platform

if __name__ == "__main__":
    print("[+] Making dir...")
    try:
        os.mkdir("framework")
    except:
        pass
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
    if platform.system() == "Windows":
        os.system("msbuild YAML_CPP.sln /p:Configuration=Release /p:Platform=\"Win32\"")
    else:
        os.system("make -j8")
    if platform.system() == "Windows":
        shutil.move("./Release/yaml-cpp.lib", "../../../framework/")
    else:
        os.system("mv libyaml-cpp.a ../../../framework/")
    os.chdir("..")
    os.chdir("..")
    shutil.rmtree("yaml-cpp", ignore_errors=True)
