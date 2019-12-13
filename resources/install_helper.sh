cd "$1";
sudo chown root:admin "ProxyConfig"
sudo chown root:admin "tun2socks"
sudo chown root:admin "tun2socksHelper"
sudo chmod +s "ProxyConfig"
sudo chmod +s "tun2socks"
sudo chmod +x "ProxyConfig"
sudo chmod +x "tun2socks"
sudo chmod +x "tun2socksHelper"
sudo chmod 4755 "tun2socksHelper"
echo done
