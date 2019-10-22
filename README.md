<h1 align="center">
  <img src="https://github.com/Dreamacro/clash/raw/master/docs/logo.png" alt="Clash" width="200">
  <br>
  ShadowClash
  <br>
</h1>


A rule based proxy For Window, Mac and Linux base on [Clash](https://github.com/Dreamacro/clash).



## Features

- HTTP/HTTPS and SOCKS protocol
- Surge like configuration
- GeoIP rule support
- Support Vmess/Shadowsocks/Socks5
- Support for Netfilter TCP redirect

## Install

You can download from [release](https://github.com/TheWanderingCoel/ShadowClash/releases) page

## Build
- Download deps
  ```
  bash install_dependency.sh
  ```
- Build clash core. 
  ```
  cd ClashX
  python3 build_clash.py
  ```
- Build and run.

## Config


The default configuration directory is `$HOME/.config/clash`

The default name of the configuration file is `config.ymal`. You can use your custom config name and switch config in menu `Config` section.

To Change the ports of ClashX, you need to modify the `config.ymal` file. The `General` section settings in your custom config file would be ignored.

Checkout [Clash](https://github.com/Dreamacro/clash) or [SS-Rule-Snippet for Clash](https://github.com/Hackl0us/SS-Rule-Snippet/blob/master/LAZY_RULES/clash.yml) for more detail.