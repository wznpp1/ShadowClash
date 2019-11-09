<h1 align="center">
  <img src="https://github.com/Dreamacro/clash/raw/master/docs/logo.png" alt="Clash" width="200">
  <br>
  ShadowClash
  <br>
</h1>


A rule based proxy For Window, Mac and Linux base on [Clash](https://github.com/Dreamacro/clash).


[![Build status](https://travis-ci.org/TheWanderingCoel/ShadowClash.svg?branch=master)](https://travis-ci.org/TheWanderingCoel/ShadowClash)
[![Build status](https://ci.appveyor.com/api/projects/status/gf5b5rffa5esbey5?svg=true)](https://ci.appveyor.com/project/CoelWu/shadowclash)
[![HitCount](http://hits.dwyl.io/TheWanderingCoel/ShadowClash.svg)](http://hits.dwyl.io/TheWanderingCoel/ShadowClash)
[![Download status](https://img.shields.io/github/downloads/TheWanderingCoel/ShadowClash/total.svg)]()
[![](https://img.shields.io/badge/license-GPL%20V3-blue.svg?longCache=true)](https://www.gnu.org/licenses/gpl-3.0.en.html)



## Features
- Cross platform Support
- HTTP/HTTPS and SOCKS protocol
- Surge like configuration
- GeoIP rule support
- Support Vmess/Shadowsocks/Socks5
- Support for Netfilter TCP redirect
- EnhanceMode support(tun2socks)

## Install

You can download from [release](https://github.com/TheWanderingCoel/ShadowClash/releases) page

## Build
- Download and build deps
  ```
  python3 install_dependency.py
  ```
- Build clash core. 
  ```
  cd clash
  python3 build_clash.py
  ```
- Run qmake
  ```
  mkdir build && cd build
  qmake ../
  ```
- Run make
  ```
  make -j8
  ```

## Config


The default configuration directory is `$HOME/.config/clash`

The default name of the configuration file is `config.ymal`. You can use your custom config name and switch config in menu `Config` section.

To Change the ports of ClashX, you need to modify the `config.ymal` file. The `General` section settings in your custom config file would be ignored.

Checkout [Clash](https://github.com/Dreamacro/clash) or [SS-Rule-Snippet for Clash](https://github.com/Hackl0us/SS-Rule-Snippet/blob/master/LAZY_RULES/clash.yml) for more detail.

## Special Thanks

- [clash](https://github.com/Dreamacro/clash) Under GPLv3 license

- [yaml-cpp](https://github.com/jbeder/yaml-cpp) Under MIT

- [plog](https://github.com/SergiusTheBest/plog) Under MPL-2.0

- [clashX](https://github.com/yichengchen/clashX)

- [openVPN(Tap Driver)](https://github.com/DanStevens/ieproxy) Under MIT and GPLv2 license

- [tun2socks](https://github.com/eycorsican/go-tun2socks)

- [ieproxy](https://github.com/DanStevens/ieproxy)